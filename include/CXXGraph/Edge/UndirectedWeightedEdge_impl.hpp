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

#ifndef __CXXGRAPH_UNDIRECTEDWEIGHTEDEDGE_IMPL_H__
#define __CXXGRAPH_UNDIRECTEDWEIGHTEDEDGE_IMPL_H__

#pragma once

#include "UndirectedWeightedEdge_decl.h"

namespace CXXGraph {

using std::make_shared;
using std::make_unique;

template <typename T>
UndirectedWeightedEdge<T>::UndirectedWeightedEdge(const std::string &userId,
                                                  const Node<T> &node1,
                                                  const Node<T> &node2,
                                                  const double weight)
    : UndirectedEdge<T>(userId, node1, node2), Weighted(weight) {}

template <typename T>
UndirectedWeightedEdge<T>::UndirectedWeightedEdge(const std::string &userId,
                                                  shared<const Node<T>> node1,
                                                  shared<const Node<T>> node2,
                                                  const double weight)
    : UndirectedEdge<T>(userId, node1, node2), Weighted(weight) {}

template <typename T>
UndirectedWeightedEdge<T>::UndirectedWeightedEdge(
    const std::string &userId,
    const std::pair<const Node<T> *, const Node<T> *> &nodepair,
    const double weight)
    : UndirectedEdge<T>(userId, nodepair), Weighted(weight) {}

template <typename T>
UndirectedWeightedEdge<T>::UndirectedWeightedEdge(
    const std::string &userId,
    const std::pair<shared<const Node<T>>, shared<const Node<T>>> &nodepair,
    const double weight)
    : UndirectedEdge<T>(userId, nodepair), Weighted(weight) {}

template <typename T>
UndirectedWeightedEdge<T>::UndirectedWeightedEdge(const UndirectedEdge<T> &edge,
                                                  const double weight)
    : UndirectedEdge<T>(edge), Weighted(weight) {}

template <typename T>
UndirectedWeightedEdge<T>::UndirectedWeightedEdge(const Edge<T> &edge,
                                                  const double weight)
    : UndirectedEdge<T>(edge), Weighted(weight) {}

template <typename T>
UndirectedWeightedEdge<T>::UndirectedWeightedEdge(const UndirectedEdge<T> &edge)
    : UndirectedEdge<T>(edge), Weighted() {}

template <typename T>
UndirectedWeightedEdge<T>::UndirectedWeightedEdge(const Edge<T> &edge)
    : UndirectedEdge<T>(edge), Weighted() {}

template <typename T>
UndirectedWeightedEdge<T>::UndirectedWeightedEdge(
    const DirectedWeightedEdge<T> &edge)
    : UndirectedEdge<T>(edge), Weighted(edge.getWeight()) {}

template <typename T>
const std::optional<bool> UndirectedWeightedEdge<T>::isWeighted() const {
  return true;
}

template <typename T>
std::ostream &operator<<(std::ostream &os,
                         const UndirectedWeightedEdge<T> &edge) {
  os << "((Node: " << edge.getNode1().getId() << ")) <----- |Edge: #"
     << edge.getId() << " W:" << edge.getWeight()
     << "|-----> ((Node: " << edge.getNode2().getId() << "))";
  return os;
}

}  // namespace CXXGraph

#endif  // __CXXGRAPH_UNDIRECTEDWEIGHTEDEDGE_IMPL_H__
