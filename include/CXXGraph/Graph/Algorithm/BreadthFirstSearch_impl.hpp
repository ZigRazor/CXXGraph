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

#ifndef __CXXGRAPH_BREADTHFIRSTSEARCH_IMPL_H__
#define __CXXGRAPH_BREADTHFIRSTSEARCH_IMPL_H__

#pragma once

#include <algorithm>

#include "CXXGraph/Graph/Graph_decl.h"

namespace CXXGraph {

template <typename T>
const std::vector<Node<T>> Graph<T>::breadth_first_search(
    const Node<T> &start) const {
  // vector to keep track of visited nodes
  std::vector<Node<T>> visited;
  auto &nodeSet = Graph<T>::getNodeSet();
  // check is exist node in the graph
  auto start_node_it = std::find_if(
      nodeSet.begin(), nodeSet.end(),
      [&start](auto &node) { return node->getUserId() == start.getUserId(); });
  if (start_node_it == nodeSet.end()) {
    return visited;
  }
  // queue that stores vertices that need to be further explored
  std::queue<shared<const Node<T>>> tracker;

  // mark the starting node as visited
  visited.push_back(start);
  tracker.push(*start_node_it);
  while (!tracker.empty()) {
    shared<const Node<T>> node = tracker.front();
    tracker.pop();
    if (cachedAdjMatrixOut->find(node) != cachedAdjMatrixOut->end()) {
      for (const auto &elem : cachedAdjMatrixOut->at(node)) {
        // if the node is not visited then mark it as visited
        // and push it to the queue
        if (std::find(visited.begin(), visited.end(), *(elem.first)) ==
            visited.end()) {
          visited.push_back(*(elem.first));
          tracker.push(elem.first);
        }
      }
    }
  }

  return visited;
}

}  // namespace CXXGraph
#endif  // __CXXGRAPH_BREADTHFIRSTSEARCH_IMPL_H__
