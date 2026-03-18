/***********************************************************/
/***      ______  ____  ______                 _         ***/
/***     / ___\ \/ /\ \/ / ___|_ __ __ _ _ __ | |__	     ***/
/***    | |    \  /  \  / |  _| '__/ _` | '_ \| '_ \	 ***/
/***    | |___ /  \  /  \ |_| | | | (_| | |_) | | | |    ***/
/***     \____/_/\_\/_/\_\____|_|  \__,_| .__/|_| |_|    ***/
/***                                    |_|			     ***/
/***********************************************************/
/***     Header-Only C++ Library for Graph			     ***/
/***	 Representation and Algorithms				     ***/
/***********************************************************/
/***     Author: ZigRazor ***/
/***	 E-Mail: zigrazor@gmail.com 				     ***/
/***********************************************************/
/***	 Collaboration: ----------- 				     ***/
/***********************************************************/
/***	 License: MPL v2.0 ***/
/***********************************************************/

#pragma once

// ── Standard includes (always available) ──────────────────────────────────────
#include <algorithm>
#include <functional>
#include <numeric>
#include <vector>

// ── Backend selection ─────────────────────────────────────────────────────────
//
// Three backends are supported, in priority order:
//
//   1. OpenMP     — activated by -DCXXGRAPH_WITH_OPENMP.
//                   Uses #pragma omp for all loop primitives.
//                   parallel_sort falls back to sequential std::sort because
//                   OpenMP provides no parallel sort primitive.
//
//   2. PSTL/TBB   — activated automatically when <execution> + a parallel
//                   runtime (Intel oneTBB) are present, detected via the
//                   standard feature-test macro __cpp_lib_parallel_algorithm.
//                   Uses std::execution::par_unseq for all primitives.
//
//   3. Sequential — fallback when neither OpenMP nor PSTL is available
//                   (e.g. Apple Clang without TBB, or any platform lacking a
//                   parallel STL runtime). All primitives run single-threaded.
//
// IMPORTANT: Do NOT use std::execution::par_unseq unconditionally.
// Apple Clang / libc++ on macOS does NOT provide parallel execution policies
// unless TBB is linked AND detected via __cpp_lib_parallel_algorithm.
// Calling std::execution::par_unseq without that check is a hard compile error
// on macOS, arm64, and any libc++ build without a PSTL backend.

#if defined(CXXGRAPH_WITH_OPENMP)
// ── OpenMP path ───────────────────────────────────────────────────────────────
  #include <omp.h>
  // PSTL is not needed and must not be assumed present in OpenMP mode.
  #define CXXGRAPH_HAS_PSTL 0

#else
// ── PSTL / sequential path ────────────────────────────────────────────────────
  #include <thread>
  // <algorithm> already included above; it defines __cpp_lib_parallel_algorithm
  // when the implementation ships a parallel STL backend.
  // <execution> provides the std::execution policy objects themselves.
  #include <execution>

  // __cpp_lib_parallel_algorithm is defined by the standard library in
  // <algorithm> (and others) when parallel execution policies are available.
  // Value 201603L means the feature is present per P0024R2 (C++17).
  //
  // Compilers/platforms that define this but do NOT actually parallelise
  // (e.g. libstdc++ without TBB) will fall back to sequential at runtime,
  // which is still correct and safe.
  #if defined(__cpp_lib_parallel_algorithm) && \
      __cpp_lib_parallel_algorithm >= 201603L
    #define CXXGRAPH_HAS_PSTL 1
  #else
    #define CXXGRAPH_HAS_PSTL 0
  #endif

#endif  // CXXGRAPH_WITH_OPENMP

namespace CXXGraph {
namespace Parallel {

// ── parallel_for_each ─────────────────────────────────────────────────────────
// Applies f to every element of [first, last) in parallel.
// The execution order is unspecified; f must not write shared state without
// explicit synchronisation.
template <typename RandomIt, typename UnaryFn>
void parallel_for_each(RandomIt first, RandomIt last, UnaryFn f) {
#if defined(CXXGRAPH_WITH_OPENMP)
  #pragma omp parallel for schedule(dynamic)
  for (auto it = first; it < last; ++it) f(*it);
#elif CXXGRAPH_HAS_PSTL
  std::for_each(std::execution::par_unseq, first, last, f);
#else
  std::for_each(first, last, f);  // sequential fallback
#endif
}

// ── parallel_for ──────────────────────────────────────────────────────────────
// Parallel loop over an integer index range [begin, end).
// Preserves the existing manual-thread API feel from concurrency_bfs.
template <typename IndexT, typename UnaryFn>
void parallel_for(IndexT begin, IndexT end, UnaryFn f) {
#if defined(CXXGRAPH_WITH_OPENMP)
  #pragma omp parallel for schedule(dynamic)
  for (IndexT i = begin; i < end; ++i) f(i);
#elif CXXGRAPH_HAS_PSTL
  std::vector<IndexT> indices(static_cast<std::size_t>(end - begin));
  std::iota(indices.begin(), indices.end(), begin);
  std::for_each(std::execution::par_unseq, indices.begin(), indices.end(), f);
#else
  // Sequential fallback: plain loop — no index vector allocation needed.
  for (IndexT i = begin; i < end; ++i) f(i);
#endif
}

// ── parallel_sort ─────────────────────────────────────────────────────────────
// Sorts [first, last) using comp in parallel.
//
// OpenMP note: OpenMP (through 5.2) does not provide a parallel sort
// primitive. Using std::execution::par_unseq inside an OpenMP translation
// unit is dangerous on platforms where the PSTL backend is absent (Apple
// Clang / libc++ without TBB). We therefore use sequential std::sort in the
// OpenMP path. The calling algorithms (Kruskal, Welsh-Powell) already obtain
// their speedup from the parallel loop primitives above.
template <typename RandomIt, typename Compare>
void parallel_sort(RandomIt first, RandomIt last, Compare comp) {
#if defined(CXXGRAPH_WITH_OPENMP)
  // Sequential sort — OpenMP has no parallel sort primitive.
  // Do NOT fall through to std::execution here: par_unseq may be unavailable
  // (Apple Clang without TBB) and would cause a hard compile error.
  std::sort(first, last, comp);
#elif CXXGRAPH_HAS_PSTL
  std::sort(std::execution::par_unseq, first, last, comp);
#else
  std::sort(first, last, comp);  // sequential fallback
#endif
}

// Default comparator overload.
template <typename RandomIt>
void parallel_sort(RandomIt first, RandomIt last) {
  parallel_sort(first, last, std::less<>{});
}

// ── parallel_transform ────────────────────────────────────────────────────────
// Applies f to each element of [first, last) and writes results to d_first.
template <typename InputIt, typename OutputIt, typename UnaryFn>
void parallel_transform(InputIt first, InputIt last, OutputIt d_first,
                        UnaryFn f) {
#if defined(CXXGRAPH_WITH_OPENMP)
  #pragma omp parallel for schedule(static)
  for (auto it = first; it < last; ++it)
    *(d_first + std::distance(first, it)) = f(*it);
#elif CXXGRAPH_HAS_PSTL
  std::transform(std::execution::par_unseq, first, last, d_first, f);
#else
  std::transform(first, last, d_first, f);  // sequential fallback
#endif
}

// ── available_threads ─────────────────────────────────────────────────────────
// Returns the number of threads the runtime will use.
// Mirrors the Globals::threads pattern used by the partitioning layer.
inline unsigned int available_threads() {
#if defined(CXXGRAPH_WITH_OPENMP)
  return static_cast<unsigned int>(omp_get_max_threads());
#else
  return std::thread::hardware_concurrency();
#endif
}

}  // namespace Parallel
}  // namespace CXXGraph
