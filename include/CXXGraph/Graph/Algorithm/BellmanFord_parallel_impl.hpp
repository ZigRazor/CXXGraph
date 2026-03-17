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

#include "CXXGraph/Graph/Graph_decl.h"
#include "CXXGraph/Utility/Parallel.hpp"
#include "CXXGraph/Utility/Typedef.hpp"

namespace CXXGraph {

template <typename T>
const BellmanFordResult Graph<T>::bellmanford_parallel(
    const Node<T>& source, const Node<T>& target) const {
  BellmanFordResult result;
  result.success = false;

  if (!isWeightedGraph()) {
    result.errorMessage = ERR_NO_WEIGHTED_EDGE;
    return result;
  }

  // ── Node indexing ─────────────────────────────────────────────────────────
  auto rawNodeSet = getNodeSet();
  std::vector<shared<const Node<T>>> nodes(rawNodeSet.begin(),
                                           rawNodeSet.end());
  const std::size_t V = nodes.size();
  std::unordered_map<CXXGraph::id_t, std::size_t> idx;
  idx.reserve(V);
  for (std::size_t i = 0; i < V; ++i) idx[nodes[i]->getId()] = i;

  // Find source index
  auto srcIt =
      std::find_if(nodes.begin(), nodes.end(), [&source](const auto& n) {
        return n->getUserId() == source.getUserId();
      });
  if (srcIt == nodes.end()) {
    result.errorMessage = ERR_SOURCE_NODE_NOT_IN_GRAPH;
    return result;
  }
  const std::size_t srcIdx =
      static_cast<std::size_t>(std::distance(nodes.begin(), srcIt));

  // ── Materialise edge list ─────────────────────────────────────────────────
  // std::unordered_set is not random-access; copy once for parallel_for.
  struct EdgeTriple {
    std::size_t u, v;
    double w;
  };
  std::vector<EdgeTriple> edges;
  edges.reserve(getEdgeSet().size());
  for (const auto& edge : getEdgeSet()) {
    if (!edge->isWeighted().value_or(false)) {
      result.errorMessage = ERR_NO_WEIGHTED_EDGE;
      return result;
    }
    const double w =
        std::dynamic_pointer_cast<const Weighted>(edge)->getWeight();
    const auto& [u, v] = edge->getNodePair();
    edges.push_back({idx.at(u->getId()), idx.at(v->getId()), w});
    if (!edge->isDirected().value_or(true)) {
      edges.push_back({idx.at(v->getId()), idx.at(u->getId()), w});
    }
  }
  const std::size_t E = edges.size();

  constexpr double INF = std::numeric_limits<double>::max() / 2.0;
  std::vector<double> dist(V, INF);
  dist[srcIdx] = 0.0;

  // ── Main relaxation loop ──────────────────────────────────────────────────
  // Each iteration reads from `dist` (prev) and writes to `next`.
  // Threads only write to next[edge.v] — but multiple edges can target the
  // same v. We use std::atomic per vertex to resolve write races safely.
  std::vector<std::atomic<double>> next_atomic(V);

  bool changed = true;
  for (std::size_t iter = 0; iter < V - 1 && changed; ++iter) {
    // Initialise next from current dist (atomic store)
    for (std::size_t i = 0; i < V; ++i)
      next_atomic[i].store(dist[i], std::memory_order_relaxed);

    // Parallel relaxation over edge set
    Parallel::parallel_for(std::size_t{0}, E, [&](std::size_t e) {
      const auto& [u, v, w] = edges[e];
      const double d_u = dist[u];  // read from frozen prev-iteration
      if (d_u >= INF) return;

      const double candidate = d_u + w;
      // Atomic compare-and-swap: update next[v] only if candidate is smaller
      double old_val = next_atomic[v].load(std::memory_order_relaxed);
      while (candidate < old_val &&
             !next_atomic[v].compare_exchange_weak(old_val, candidate,
                                                   std::memory_order_relaxed,
                                                   std::memory_order_relaxed)) {
        // old_val refreshed by compare_exchange_weak on failure
      }
    });

    // Flush atomics back into dist, check for change
    changed = false;
    for (std::size_t i = 0; i < V; ++i) {
      const double nv = next_atomic[i].load(std::memory_order_relaxed);
      if (nv != dist[i]) {
        dist[i] = nv;
        changed = true;
      }
    }
  }

  // ── Negative cycle check ──────────────────────────────────────────────────
  if (changed) {
    Parallel::parallel_for(std::size_t{0}, E, [&](std::size_t e) {
      // (a violation check — just need any one)
    });
    // Serial scan is fine here (one pass only)
    for (const auto& [u, v, w] : edges) {
      if (dist[u] < INF && dist[u] + w < dist[v]) {
        result.success = true;
        result.negativeCycle = true;
        return result;  // Note: returns from lambda, not from function
      }
    }
  }

  // ── Pack result ───────────────────────────────────────────────────────────
  auto tgtIt =
      std::find_if(nodes.begin(), nodes.end(), [&target](const auto& n) {
        return n->getUserId() == target.getUserId();
      });
  if (tgtIt == nodes.end()) {
    result.errorMessage = ERR_TARGET_NODE_NOT_IN_GRAPH;
    return result;
  }
  const std::size_t tgtIdx =
      static_cast<std::size_t>(std::distance(nodes.begin(), tgtIt));

  if (dist[tgtIdx] >= INF) {
    result.errorMessage = ERR_TARGET_NODE_NOT_REACHABLE;
    result.result = -1;
    return result;
  }

  result.success = true;
  result.negativeCycle = false;
  result.result = dist[tgtIdx];
  return result;
}
}