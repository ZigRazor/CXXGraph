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

#ifndef __CXXGRAPH_DEPTHFIRSTSEARCH_IMPL_H__
#define __CXXGRAPH_DEPTHFIRSTSEARCH_IMPL_H__

#pragma once

#include <algorithm>

#include "CXXGraph/Graph/Graph_decl.h"

namespace CXXGraph {

template <typename T>
const std::vector<Node<T>> Graph<T>::depth_first_search(
    const Node<T> &start) const {
  // vector to keep track of visited nodes
  std::vector<Node<T>> visited;
  auto nodeSet = Graph<T>::getNodeSet();
  // check is exist node in the graph
  auto start_node_it = std::find_if(
      nodeSet.begin(), nodeSet.end(),
      [&start](auto node) { return node->getUserId() == start.getUserId(); });
  if (start_node_it == nodeSet.end()) {
    return visited;
  }
  std::function<void(const std::shared_ptr<AdjacencyMatrix<T>>,
                     shared<const Node<T>>, std::vector<Node<T>> &)>
      explore;
  explore = [&explore](const std::shared_ptr<AdjacencyMatrix<T>> adj,
                       shared<const Node<T>> node,
                       std::vector<Node<T>> &visited) -> void {
    visited.push_back(*node);
    if (adj->find(node) != adj->end()) {
      for (const auto &x : adj->at(node)) {
        if (std::find(visited.begin(), visited.end(), *(x.first)) ==
            visited.end()) {
          explore(adj, x.first, visited);
        }
      }
    }
  };
  explore(cachedAdjMatrix, *start_node_it, visited);

  return visited;
}

}  // namespace CXXGraph
#endif  // __CXXGRAPH_DEPTHFIRSTSEARCH_IMPL_H__
