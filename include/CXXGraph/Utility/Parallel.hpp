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
#include <algorithm>
#include <execution>
#include <functional>
#include <numeric>
#ifdef CXXGRAPH_WITH_OPENMP
#include <omp.h>
#else
#include <thread>
#endif

namespace CXXGraph {
namespace Parallel {

// ── parallel_for_each ────────────────────────────────────────────────────────
// Applies f to every element of [first, last) in parallel.
// The execution order is unspecified; f must not write shared state without
// synchronisation.

template <typename RandomIt, typename UnaryFn>
void parallel_for_each(RandomIt first, RandomIt last, UnaryFn f) {
#ifdef CXXGRAPH_WITH_OPENMP
#pragma omp parallel for schedule(dynamic)
  for (auto it = first; it < last; ++it) f(*it);
#else
  std::for_each(std::execution::par_unseq, first, last, f);
#endif
}

// ── parallel_for ─────────────────────────────────────────────────────────────
// Parallel loop over integer index range [begin, end).
// Preserves the existing manual-thread API feel from concurrency_bfs.

template <typename IndexT, typename UnaryFn>
void parallel_for(IndexT begin, IndexT end, UnaryFn f) {
#ifdef CXXGRAPH_WITH_OPENMP
#pragma omp parallel for schedule(dynamic)
  for (IndexT i = begin; i < end; ++i) f(i);
#else
  // Build an index range and dispatch via par_unseq
  std::vector<IndexT> indices(static_cast<std::size_t>(end - begin));
  std::iota(indices.begin(), indices.end(), begin);
  std::for_each(std::execution::par_unseq, indices.begin(), indices.end(), f);
#endif
}

// ── parallel_sort
// ───────────────────────────────────────────────────────────── Sorts [first,
// last) in parallel using comp.

template <typename RandomIt, typename Compare>
void parallel_sort(RandomIt first, RandomIt last, Compare comp) {
#ifdef CXXGRAPH_WITH_OPENMP
  // OpenMP doesn't provide sort; fall through to std::execution
  std::sort(std::execution::par_unseq, first, last, comp);
#else
  std::sort(std::execution::par_unseq, first, last, comp);
#endif
}

// Default comparator overload
template <typename RandomIt>
void parallel_sort(RandomIt first, RandomIt last) {
  parallel_sort(first, last, std::less<>{});
}

// ── parallel_transform
// ──────────────────────────────────────────────────────── Applies f to each
// element of [first, last) and writes results to d_first.

template <typename InputIt, typename OutputIt, typename UnaryFn>
void parallel_transform(InputIt first, InputIt last, OutputIt d_first,
                        UnaryFn f) {
#ifdef CXXGRAPH_WITH_OPENMP
#pragma omp parallel for schedule(static)
  for (auto it = first; it < last; ++it) {
    *(d_first + std::distance(first, it)) = f(*it);
  }
#else
  std::transform(std::execution::par_unseq, first, last, d_first, f);
#endif
}

// ── available_threads
// ───────────────────────────────────────────────────────── Returns the number
// of threads the runtime will use. Mirrors the Globals::threads pattern used by
// the partitioning layer.

inline unsigned int available_threads() {
#ifdef CXXGRAPH_WITH_OPENMP
  return static_cast<unsigned int>(omp_get_max_threads());
#else
  return std::thread::hardware_concurrency();
#endif
}

}  // namespace Parallel
}  // namespace CXXGraph