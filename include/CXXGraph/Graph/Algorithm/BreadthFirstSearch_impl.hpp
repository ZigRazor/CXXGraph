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
#include <queue>
#include <vector>

#include "CXXGraph/Graph/Graph_decl.h"

namespace CXXGraph {

template <typename T>
const std::vector<Node<T>> Graph<T>::breadth_first_search(
    const Node<T> &start) const {
  // vector to keep track of visited nodes
  std::vector<Node<T>> visited;
  // std::unordered_set<CXXGraph::id_t> visited_ids;

  // check is exist node in the graph

  auto start_node = Graph<T>::getNode(start.getId());
  if (!start_node.has_value()) {
    return visited;
  }
  // queue that stores vertices that need to be further explored
  std::queue<shared<const Node<T>>> tracker;

  // mark the starting node as visited
  visited.push_back(start);
  // visited_ids.insert(start.getId());
  tracker.push(start_node.value());
  while (!tracker.empty()) {
    shared<const Node<T>> node = tracker.front();
    tracker.pop();
    if (cachedAdjListOut->find(node) != cachedAdjListOut->end()) {
      for (const auto &elem : cachedAdjListOut->at(node)) {
        if (std::find_if(visited.begin(), visited.end(),
                         [&elem](const auto &node) {
                           return node.getId() == elem.first->getId();
                         }) == visited.end()) {
          // if (visited_ids.find(elem.first->getId()) == visited_ids.end()) {
          visited.push_back(*(elem.first));
          // visited_ids.insert(elem.first->getId());
          tracker.push(elem.first);
        }
      }
    }
  }

  return visited;
}

}  // namespace CXXGraph
#endif  // __CXXGRAPH_BREADTHFIRSTSEARCH_IMPL_H__
