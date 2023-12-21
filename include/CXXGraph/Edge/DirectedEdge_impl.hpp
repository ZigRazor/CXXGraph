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

#ifndef __CXXGRAPH_DIRECTEDEDGE_IMPL_H__
#define __CXXGRAPH_DIRECTEDEDGE_IMPL_H__

#pragma once

#include "DirectedEdge_decl.h"

namespace CXXGraph {
  
using std::make_unique;
using std::make_shared;

template <typename T>
DirectedEdge<T>::DirectedEdge(const CXXGraph::id_t id, const Node<T> &node1,
                              const Node<T> &node2)
    : Edge<T>(id, node1, node2) {}

template <typename T>
DirectedEdge<T>::DirectedEdge(const CXXGraph::id_t id, shared<const Node<T>> node1,
			 shared<const Node<T>> node2) : Edge<T>(id, node1, node2) {}

template <typename T>
DirectedEdge<T>::DirectedEdge(
    const CXXGraph::id_t id,
    const std::pair<const Node<T> *, const Node<T> *> &nodepair)
    : Edge<T>(id, nodepair) {}

template <typename T>
DirectedEdge<T>::DirectedEdge(
    const CXXGraph::id_t id,
    const std::pair<shared<const Node<T>>, shared<const Node<T>>> &nodepair)
    : Edge<T>(id, nodepair) {}

template <typename T>
DirectedEdge<T>::DirectedEdge(const Edge<T> &edge)
    : DirectedEdge(edge.getId(), *(edge.getNodePair().first),
                   *(edge.getNodePair().second)) {}

template <typename T>
const Node<T> &DirectedEdge<T>::getFrom() const {
  return *(Edge<T>::getNodePair().first);
}

template <typename T>
const Node<T> &DirectedEdge<T>::getTo() const {
  return *(Edge<T>::getNodePair().second);
}

template <typename T>
const std::optional<bool> DirectedEdge<T>::isDirected() const {
  return true;
}

template <typename T>
const std::optional<bool> DirectedEdge<T>::isWeighted() const {
  return false;
}

template <typename T>
std::ostream &operator<<(std::ostream &os, const DirectedEdge<T> &edge) {
  os << "((Node: " << edge.getFrom().getId() << ")) +----- |Edge: #"
     << edge.getId() << "|-----> ((Node: " << edge.getTo().getId() << "))";
  return os;
}
}  // namespace CXXGraph

#endif  // __CXXGRAPH_DIRECTEDEDGE_IMPL_H__
