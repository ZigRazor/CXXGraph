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
/***	 License: AGPL v3.0 ***/
/***********************************************************/

#ifndef __CXXGRAPH_BELLMANFORD_IMPL_H__
#define __CXXGRAPH_BELLMANFORD_IMPL_H__

#pragma once

#include "CXXGraph/Graph/Graph_decl.h"

namespace CXXGraph {
template <typename T>
const BellmanFordResult Graph<T>::bellmanford(const Node<T> &source,
                                              const Node<T> &target) const {
  BellmanFordResult result;
  result.success = false;
  result.errorMessage = "";
  result.result = INF_DOUBLE;
  auto nodeSet = Graph<T>::getNodeSet();
  auto source_node_it = std::find_if(
      nodeSet.begin(), nodeSet.end(),
      [&source](auto node) { return node->getUserId() == source.getUserId(); });
  if (source_node_it == nodeSet.end()) {
    // check if source node exist in the graph
    result.errorMessage = ERR_SOURCE_NODE_NOT_IN_GRAPH;
    return result;
  }
  auto target_node_it = std::find_if(
      nodeSet.begin(), nodeSet.end(),
      [&target](auto node) { return node->getUserId() == target.getUserId(); });
  if (target_node_it == nodeSet.end()) {
    // check if target node exist in the graph
    result.errorMessage = ERR_TARGET_NODE_NOT_IN_GRAPH;
    return result;
  }
  // setting all the distances initially to INF_DOUBLE
  std::unordered_map<shared<const Node<T>>, double, nodeHash<T>> dist,
      currentDist;
  // n denotes the number of vertices in graph
  auto n = nodeSet.size();
  for (const auto &elem : nodeSet) {
    dist[elem] = INF_DOUBLE;
    currentDist[elem] = INF_DOUBLE;
  }

  // marking the distance of source as 0
  dist[*source_node_it] = 0;
  // set if node distances in two consecutive
  // iterations remain the same.
  auto earlyStopping = false;
  // outer loop for vertex relaxation
  for (int i = 0; i < n - 1; ++i) {
    auto edgeSet = Graph<T>::getEdgeSet();
    // inner loop for distance updates of
    // each relaxation
    for (const auto &edge : edgeSet) {
      auto elem = edge->getNodePair();
      if (edge->isWeighted().has_value() && edge->isWeighted().value()) {
        auto edge_weight =
            (std::dynamic_pointer_cast<const Weighted>(edge))->getWeight();
        if (dist[elem.first] + edge_weight < dist[elem.second])
          dist[elem.second] = dist[elem.first] + edge_weight;
      } else {
        // No Weighted Edge
        result.errorMessage = ERR_NO_WEIGHTED_EDGE;
        return result;
      }
    }
    auto flag = true;
    for (const auto &[key, value] : dist) {
      if (currentDist[key] != value) {
        flag = false;
        break;
      }
    }
    for (const auto &[key, value] : dist) {
      currentDist[key] = value;  // update the current distance
    }
    if (flag) {
      earlyStopping = true;
      break;
    }
  }

  // check if there exists a negative cycle
  if (!earlyStopping) {
    auto edgeSet = Graph<T>::getEdgeSet();
    for (const auto &edge : edgeSet) {
      auto elem = edge->getNodePair();
      auto edge_weight =
          (std::dynamic_pointer_cast<const Weighted>(edge))->getWeight();
      if (dist[elem.first] + edge_weight < dist[elem.second]) {
        result.success = true;
        result.negativeCycle = true;
        result.errorMessage = "";
        return result;
      }
    }
  }

  if (dist[*target_node_it] != INF_DOUBLE) {
    result.success = true;
    result.errorMessage = "";
    result.negativeCycle = false;
    result.result = dist[*target_node_it];
    return result;
  }
  result.errorMessage = ERR_TARGET_NODE_NOT_REACHABLE;
  result.result = -1;
  return result;
}
}  // namespace CXXGraph
#endif  // __CXXGRAPH_BELLMANFORD_IMPL_H__