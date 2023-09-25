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

#ifndef __CXXGRAPH_DIRECTEDEDGE_H__
#define __CXXGRAPH_DIRECTEDEDGE_H__

#pragma once

#include "Edge.hpp"

namespace CXXGraph {
// Smart pointers alias
template <typename T>
using unique = std::unique_ptr<T>;
template <typename T>
using shared= std::shared_ptr<T>;

using std::make_unique;
using std::make_shared;

template <typename T>
class UndirectedEdge;

template <typename T>
class DirectedEdge;
// ostream operator
template <typename T>
std::ostream &operator<<(std::ostream &o, const DirectedEdge<T> &edge);
template <typename T>
class DirectedEdge : public Edge<T> {
 public:
  DirectedEdge(const CXXGraph::id_t id, const Node<T> &node1,
               const Node<T> &node2);
  DirectedEdge(const CXXGraph::id_t id, shared<const Node<T>> node1,
               shared<const Node<T>> node2);
  DirectedEdge(const CXXGraph::id_t id,
               const std::pair<const Node<T> *, const Node<T> *> &nodepair);
  DirectedEdge(const CXXGraph::id_t id,
               const std::pair<shared<const Node<T>>, shared<const Node<T>>> &nodepair);
  DirectedEdge(const Edge<T> &edge);
  virtual ~DirectedEdge() = default;
  const Node<T> &getFrom() const;
  const Node<T> &getTo() const;
  const std::optional<bool> isDirected() const override;
  const std::optional<bool> isWeighted() const override;
  // operator
  explicit operator UndirectedEdge<T>() const {
    return UndirectedEdge<T>(Edge<T>::getId(), Edge<T>::getNodePair());
  }

  friend std::ostream &operator<< <>(std::ostream &os,
                                     const DirectedEdge<T> &edge);
};

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

#endif  // __CXXGRAPH_DIRECTEDEDGE_H__
