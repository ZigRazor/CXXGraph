/***********************************************************/
/***      ______  ____  ______                 _         ***/
/***     / ___\ \/ /\ \/ / ___|_ __ __ _ _ __ | |__	     ***/
/***    | |    \  /  \  / |  _| '__/ _` | '_ \| '_ \	    ***/
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

#ifndef __CXXGRAPH_EULERIAN_PATH_IMPL_H__
#define __CXXGRAPH_EULERIAN_PATH_IMPL_H__

#pragma once

#include "CXXGraph/Graph/Graph_decl.h"

namespace CXXGraph {

template <typename T>
std::shared_ptr<std::vector<Node<T>>> Graph<T>::eulerianPath() const {
  const auto nodeSet = Graph<T>::getNodeSet();

  std::shared_ptr<std::vector<Node<T>>> eulerPath =
      std::make_shared<std::vector<Node<T>>>();

  // unused
  // bool undirected = this->isUndirectedGraph();

  std::vector<shared<const Node<T>>> currentPath;
  // The starting node is the only node which has more outgoing than ingoing
  // links
  auto firstNodeIt = std::max_element(nodeSet.begin(), nodeSet.end(),
                                      [this](auto n1, auto n2) {
                                        return cachedAdjListOut->at(n1).size() <
                                               cachedAdjListOut->at(n2).size();
                                      });
  auto currentNode = *(firstNodeIt);
  currentPath.push_back(currentNode);

  while (currentPath.size() > 0) {
    auto &edges = cachedAdjListOut->at(currentNode);
    // we keep removing the edges that
    // have been traversed from the adjacency list
    if (edges.size()) {
      auto firstEdge = edges.back().second;

      shared<const Node<T>> nextNodeId;
      nextNodeId = firstEdge->getOtherNode(currentNode);

      currentPath.push_back(nextNodeId);
      currentNode = nextNodeId;
      edges.pop_back();
    } else {
      eulerPath->push_back(*currentNode);
      currentNode = currentPath.back();
      currentPath.pop_back();
    }
  }
  return eulerPath;
}
}  // namespace CXXGraph

#endif  // __CXXGRAPH_EULERIAN_PATH_IMPL_H__