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

#ifndef __CXXGRAPH_POINTER_HASH__
#define __CXXGRAPH_POINTER_HASH__

#pragma once

#include <memory>
#include <string>

#include "../Edge/DirectedEdge.hpp"
#include "../Edge/DirectedWeightedEdge.hpp"
#include "../Edge/Edge.hpp"
#include "../Edge/UndirectedEdge.hpp"
#include "../Edge/UndirectedWeightedEdge.hpp"
#include "../Edge/Weighted.hpp"
#include "../Node/Node.hpp"

namespace CXXGraph {
template <typename T>
using shared = std::shared_ptr<T>;

// Redefine the hash functions and equality operators for shared pointers of nodes and edges
template <typename T>
struct nodeHash {
  size_t operator()(const shared<const Node<T>>& node) const {
    return node->getId();
  }
  size_t operator()(const shared<Node<T>>& node) const {
    return node->getId();
  }
};

template <typename T>
struct edgeHash {
  size_t operator()(const shared<const Edge<T>>& edge) const {
    return (edge->getNodePair().first->getId()) ^ (edge->getNodePair().second->getId());
  }
};

template <typename T>
bool operator==(shared<const Node<T>> p1, shared<const Node<T>> p2) {
  return p1->getUserId() == p2->getUserId();
}

template <typename T>
bool operator==(shared<Node<T>> p1, shared<Node<T>> p2) {
  return p1->getUserId() == p2->getUserId();
}

template <typename T>
bool operator==(shared<const Edge<T>> p1, shared<const Edge<T>> p2) {
  return p1->getNodePair().first->getUserId() ==
             p2->getNodePair().first->getUserId() &&
         p1->getNodePair().second->getUserId() ==
             p2->getNodePair().second->getUserId();
}
}  // namespace CXXGraph

#endif
