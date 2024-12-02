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

#ifndef __CXXGRAPH_KRUSKAL_IMPL_H__
#define __CXXGRAPH_KRUSKAL_IMPL_H__

#pragma once

#include "CXXGraph/Graph/Graph_decl.h"

namespace CXXGraph {

template <typename T>
const MstResult Graph<T>::kruskal() const {
  MstResult result;
  result.success = false;
  result.errorMessage = "";
  result.mstCost = INF_DOUBLE;
  if (!isUndirectedGraph()) {
    result.errorMessage = ERR_DIR_GRAPH;
    return result;
  }
  const auto nodeSet = Graph<T>::getNodeSet();
  auto n = nodeSet.size();

  // check if all edges are weighted and store the weights
  // in a map whose keys are the edge ids and values are the edge weights
  auto edgeSet = Graph<T>::getEdgeSet();
  std::priority_queue<std::pair<double, shared<const Edge<T>>>,
                      std::vector<std::pair<double, shared<const Edge<T>>>>,
                      std::greater<std::pair<double, shared<const Edge<T>>>>>
      sortedEdges;
  for (const auto &edge : edgeSet) {
    if (edge->isWeighted().has_value() && edge->isWeighted().value()) {
      auto weight =
          (std::dynamic_pointer_cast<const Weighted>(edge))->getWeight();
      sortedEdges.push(std::make_pair(weight, edge));
    } else {
      // No Weighted Edge
      result.errorMessage = ERR_NO_WEIGHTED_EDGE;
      return result;
    }
  }

  auto subset = make_shared<std::unordered_map<CXXGraph::id_t, Subset>>();

  for (const auto &node : nodeSet) {
    Subset set{node->getId(), 0};
    (*subset)[node->getId()] = set;
  }
  result.mstCost = 0;
  while ((!sortedEdges.empty()) && (result.mst.size() < n)) {
    auto [edgeWeight, cheapestEdge] = sortedEdges.top();
    sortedEdges.pop();
    auto &[first, second] = cheapestEdge->getNodePair();
    auto set1 = Graph<T>::setFind(subset, first->getId());
    auto set2 = Graph<T>::setFind(subset, second->getId());
    if (set1 != set2) {
      result.mst.push_back(
          std::make_pair(first->getUserId(), second->getUserId()));
      result.mstCost += edgeWeight;
    }
    Graph<T>::setUnion(subset, set1, set2);
  }
  result.success = true;
  return result;
}
}  // namespace CXXGraph
#endif  // __CXXGRAPH_KRUSKAL_IMPL_H__