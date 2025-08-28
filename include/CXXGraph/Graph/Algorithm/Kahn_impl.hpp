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

#ifndef __CXXGRAPH_KAHN_IMPL_H__
#define __CXXGRAPH_KAHN_IMPL_H__

#pragma once

#include "CXXGraph/Graph/Graph_decl.h"

namespace CXXGraph {

template <typename T>
TopoSortResult<T> Graph<T>::kahn() const {
  TopoSortResult<T> result;

  if (!isDirectedGraph()) {
    result.errorMessage = ERR_UNDIR_GRAPH;
    return result;
  } else {
    const auto nodeSet = Graph<T>::getNodeSet();
    result.nodesInTopoOrder.reserve(cachedAdjMatrixOut->size());

    std::unordered_map<CXXGraph::id_t, unsigned int> indegree;
    for (const auto &node : nodeSet) {
      indegree[node->getId()] = 0;
    }
    for (const auto &list : *cachedAdjMatrixOut) {
      auto children = list.second;
      for (const auto &child : children) {
        indegree[std::get<0>(child)->getId()]++;
      }
    }

    std::queue<shared<const Node<T>>> topologicalOrder;

    for (const auto &node : nodeSet) {
      if (!indegree[node->getId()]) {
        topologicalOrder.emplace(node);
      }
    }

    size_t visited = 0;
    while (!topologicalOrder.empty()) {
      shared<const Node<T>> currentNode = topologicalOrder.front();
      topologicalOrder.pop();
      result.nodesInTopoOrder.push_back(*currentNode);

      if (cachedAdjMatrixOut->find(currentNode) != cachedAdjMatrixOut->end()) {
        for (const auto &child : cachedAdjMatrixOut->at(currentNode)) {
          if (--indegree[std::get<0>(child)->getId()] == 0) {
            topologicalOrder.emplace(std::get<0>(child));
          }
        }
      }
      visited++;
    }

    if (visited != nodeSet.size()) {
      result.errorMessage = ERR_CYCLIC_GRAPH;
      result.nodesInTopoOrder.clear();
      return result;
    }

    result.success = true;
    return result;
  }
}
}  // namespace CXXGraph
#endif  // __CXXGRAPH_KAHN_IMPL_H__