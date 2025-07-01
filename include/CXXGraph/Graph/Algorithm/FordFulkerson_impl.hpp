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

#ifndef __CXXGRAPH_FORDFULKERSON_IMPL_H__
#define __CXXGRAPH_FORDFULKERSON_IMPL_H__

#pragma once

#include <algorithm>

#include "CXXGraph/Graph/Graph_decl.h"

namespace CXXGraph {

template <typename T>
double Graph<T>::fordFulkersonMaxFlow(const Node<T> &source,
                                      const Node<T> &target) const {
  if (!isDirectedGraph()) {
    return -1;
  }
  double maxFlow = 0;
  std::unordered_map<shared<const Node<T>>, shared<const Node<T>>, nodeHash<T>>
      parent;
  std::unordered_map<
      shared<const Node<T>>,
      std::unordered_map<shared<const Node<T>>, double, nodeHash<T>>,
      nodeHash<T>>
      weightMap;
  // build weight map
  auto edgeSet = this->getEdgeSet();
  for (const auto &edge : edgeSet) {
    // The Edge are all Directed at this point because is checked at the
    // start
    if (edge->isWeighted().value_or(false)) {
      shared<const DirectedWeightedEdge<T>> dw_edge =
          std::static_pointer_cast<const DirectedWeightedEdge<T>>(edge);
      weightMap[edge->getNodePair().first][edge->getNodePair().second] =
          dw_edge->getWeight();
    } else {
      weightMap[edge->getNodePair().first][edge->getNodePair().second] =
          0;  // No Weighted Edge are assumed to be 0 weigthed
    }
  }

  // Constuct iterators for source and target nodes in nodeSet
  auto nodeSet = getNodeSet();
  auto source_node_ptr = *std::find_if(
      nodeSet.begin(), nodeSet.end(),
      [&source](auto node) { return node->getUserId() == source.getUserId(); });
  auto target_node_ptr = *std::find_if(
      nodeSet.begin(), nodeSet.end(),
      [&target](auto node) { return node->getUserId() == target.getUserId(); });

  auto bfs_helper = [&source_node_ptr, &target_node_ptr, &parent,
                     &weightMap]() -> bool {
    std::unordered_map<shared<const Node<T>>, bool, nodeHash<T>> visited;
    std::queue<shared<const Node<T>>> queue;
    queue.push(source_node_ptr);
    visited[source_node_ptr] = true;
    parent[source_node_ptr] = nullptr;
    while (!queue.empty()) {
      auto u = queue.front();
      queue.pop();
      for (auto &v : weightMap[u]) {
        if (!visited[v.first] && v.second > 0) {
          queue.push(v.first);
          visited[v.first] = true;
          parent[v.first] = u;
        }
      }
    }

    return (visited[target_node_ptr]);
  };
  // Updating the residual values of edges
  while (bfs_helper()) {
    double pathFlow = std::numeric_limits<double>::max();
    for (auto v = target_node_ptr; v != source_node_ptr; v = parent[v]) {
      auto u = parent[v];
      pathFlow = std::min(pathFlow, weightMap[u][v]);
    }
    for (auto v = target_node_ptr; v != source_node_ptr; v = parent[v]) {
      auto u = parent[v];
      weightMap[u][v] -= pathFlow;
      weightMap[v][u] += pathFlow;
    }
    // Adding the path flows
    maxFlow += pathFlow;
  }

  return maxFlow;
}
}  // namespace CXXGraph
#endif  // __CXXGRAPH_FORDFULKERSON_IMPL_H__
