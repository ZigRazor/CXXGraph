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
const MstResult Graph<T>::kruskal_parallel() const {
  MstResult result;
  result.success = false;

  if (!isUndirectedGraph()) {
    result.errorMessage = ERR_DIR_GRAPH;
    return result;
  }

  // ── Materialise weighted edge list ────────────────────────────────────────
  struct WEdge {
    double w;
    std::string u, v;
  };
  std::vector<WEdge> wEdges;
  wEdges.reserve(getEdgeSet().size());

  for (const auto& edge : getEdgeSet()) {
    if (!edge->isWeighted().value_or(false)) {
      result.errorMessage = ERR_NO_WEIGHTED_EDGE;
      return result;
    }
    const double w =
        std::dynamic_pointer_cast<const Weighted>(edge)->getWeight();
    wEdges.push_back({w, edge->getNodePair().first->getUserId(),
                      edge->getNodePair().second->getUserId()});
  }

  // ── Parallel sort ─────────────────────────────────────────────────────────
  // This is where the speedup lives: O(E log E / p) instead of O(E log E).
  Parallel::parallel_sort(
      wEdges.begin(), wEdges.end(),
      [](const WEdge& a, const WEdge& b) { return a.w < b.w; });

  // ── Sequential union-find ─────────────────────────────────────────────────
  // Union-find with path compression cannot be safely parallelised without
  // a lock-free DSU (e.g. Rem's algorithm) — out of scope here.
  std::unordered_map<std::string, std::string> parent;
  std::unordered_map<std::string, int> rank;

  for (const auto& node : getNodeSet()) {
    const std::string& uid = node->getUserId();
    parent[uid] = uid;
    rank[uid] = 0;
  }

  std::function<std::string(const std::string&)> find =
      [&](const std::string& x) -> std::string {
    if (parent.at(x) != x) parent[x] = find(parent.at(x));
    return parent.at(x);
  };

  auto unite = [&](const std::string& a, const std::string& b) {
    const std::string ra = find(a), rb = find(b);
    if (ra == rb) return false;
    if (rank[ra] < rank[rb])
      parent[ra] = rb;
    else if (rank[ra] > rank[rb])
      parent[rb] = ra;
    else {
      parent[rb] = ra;
      rank[ra]++;
    }
    return true;
  };

  for (const auto& e : wEdges) {
    if (unite(e.u, e.v)) {
      result.mst.emplace_back(e.u, e.v);
      result.mstCost += e.w;
    }
  }

  result.success = true;
  return result;
}
}  // namespace CXXGraph