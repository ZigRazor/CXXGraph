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
#include <atomic>
#include <vector>

#include "CXXGraph/Utility/Parallel.hpp"
#include "CXXGraph/Utility/Typedef.hpp"

namespace CXXGraph {

template <typename T>
const FWResult Graph<T>::floydWarshall_parallel() const {
  FWResult result;
  result.success = false;

  if (!isWeightedGraph()) {
    result.errorMessage = ERR_NO_WEIGHTED_EDGE;
    return result;
  }

  // ── Materialise a stable-ordered node vector ─────────────────────────────
  // std::unordered_set iteration is non-deterministic; we need a stable
  // index for the dense matrix below.
  auto rawNodeSet = getNodeSet();
  std::vector<shared<const Node<T>>> nodes(rawNodeSet.begin(),
                                           rawNodeSet.end());
  const std::size_t V = nodes.size();

  // Map nodeId → row/column index
  std::unordered_map<CXXGraph::id_t, std::size_t> idx;
  idx.reserve(V);
  for (std::size_t i = 0; i < V; ++i) idx[nodes[i]->getId()] = i;

  // ── Dense distance matrix ─────────────────────────────────────────────────
  // Stored row-major as a flat vector for cache friendliness.
  // dist[i*V + j] = shortest known distance from nodes[i] to nodes[j].
  constexpr double INF = std::numeric_limits<double>::max() / 2.0;
  std::vector<double> dist(V * V, INF);

  // Diagonal = 0
  for (std::size_t i = 0; i < V; ++i) dist[i * V + i] = 0.0;

  // Seed from edge set
  const auto& edgeSet = getEdgeSet();
  for (const auto& edge : edgeSet) {
    if (!edge->isWeighted().value_or(false)) {
      result.errorMessage = ERR_NO_WEIGHTED_EDGE;
      return result;
    }
    const double w =
        std::dynamic_pointer_cast<const Weighted>(edge)->getWeight();
    const auto& [u, v] = edge->getNodePair();
    const std::size_t ui = idx.at(u->getId());
    const std::size_t vi = idx.at(v->getId());
    dist[ui * V + vi] = w;
    if (!edge->isDirected().value_or(true)) {
      dist[vi * V + ui] = w;
    }
  }

  // ── Main loop ─────────────────────────────────────────────────────────────
  // k is sequential (strict data dependency: dist(k) depends on dist(k-1)).
  // The src loop is parallel: each src row is independent for a fixed k.
  for (std::size_t k = 0; k < V; ++k) {
    // Pre-read the k-th row into a local snapshot so parallel workers
    // see a consistent view (no torn reads across the k boundary).
    const std::vector<double> k_row(dist.begin() + k * V,
                                    dist.begin() + k * V + V);

    Parallel::parallel_for(std::size_t{0}, V, [&](std::size_t src) {
      const double dist_src_k = dist[src * V + k];
      if (dist_src_k >= INF) return;  // pruning: no path src→k

      for (std::size_t dst = 0; dst < V; ++dst) {
        const double via_k = dist_src_k + k_row[dst];
        if (via_k < dist[src * V + dst]) {
          // Each (src, dst) cell is written by exactly one thread
          // (the thread responsible for row src), so no race.
          dist[src * V + dst] = via_k;
        }
      }
    });
  }

  // ── Negative cycle detection ──────────────────────────────────────────────
  for (std::size_t i = 0; i < V; ++i) {
    if (dist[i * V + i] < 0.0) {
      result.success = true;
      result.negativeCycle = true;
      return result;
    }
  }

  // ── Repack into the existing FWResult map format ──────────────────────────
  for (std::size_t i = 0; i < V; ++i) {
    for (std::size_t j = 0; j < V; ++j) {
      auto key = std::make_pair(nodes[i]->getUserId(), nodes[j]->getUserId());
      result.result[key] = (dist[i * V + j] >= INF)
                               ? std::numeric_limits<double>::infinity()
                               : dist[i * V + j];
    }
  }

  result.success = true;
  result.negativeCycle = false;
  return result;
}

}  // namespace CXXGraph