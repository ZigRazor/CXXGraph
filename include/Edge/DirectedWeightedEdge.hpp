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
#ifndef __CXXGRAPH_DIRECTEDWEIGHTEDEDGE_H__
#define __CXXGRAPH_DIRECTEDWEIGHTEDEDGE_H__

#pragma once

#include "DirectedEdge.hpp"
#include "Weighted.hpp"

namespace CXXGraph {
// Smart pointers alias
template <typename T>
using unique = std::unique_ptr<T>;
template <typename T>
using shared= std::shared_ptr<T>;

using std::make_unique;
using std::make_shared;

// Foward Declaration
template <typename T>
class UndirectedWeightedEdge;

template <typename T>
class DirectedWeightedEdge;

// ostream operator
template <typename T>
std::ostream &operator<<(std::ostream &o, const DirectedWeightedEdge<T> &edge);

template <typename T>
class DirectedWeightedEdge : public DirectedEdge<T>, public Weighted {
 public:
  DirectedWeightedEdge(const CXXGraph::id_t id, const Node<T> &node1,
                       const Node<T> &node2, const double weight);
  DirectedWeightedEdge(const CXXGraph::id_t id, shared<const Node<T>> node1,
                       shared<const Node<T>> node2, const double weight);
  DirectedWeightedEdge(
      const CXXGraph::id_t id,
      const std::pair<const Node<T> *, const Node<T> *> &nodepair,
      const double weight);
  DirectedWeightedEdge(
      const CXXGraph::id_t id,
      const std::pair<shared<const Node<T>>, shared<const Node<T>>> &nodepair,
      const double weight);
  DirectedWeightedEdge(const DirectedEdge<T> &edge, const double weight);
  DirectedWeightedEdge(const Edge<T> &edge, const double weight);
  DirectedWeightedEdge(const DirectedEdge<T> &edge);
  DirectedWeightedEdge(const Edge<T> &edge);
  DirectedWeightedEdge(const UndirectedWeightedEdge<T> &edge);
  virtual ~DirectedWeightedEdge() = default;
  const std::optional<bool> isWeighted() const override;
  // operator
  explicit operator UndirectedWeightedEdge<T>() const {
    return UndirectedWeightedEdge<T>(Edge<T>::getId(), Edge<T>::getNodePair(),
                                     Weighted::getWeight());
  }

  friend std::ostream &operator<< <>(std::ostream &os,
                                     const DirectedWeightedEdge<T> &edge);
};

template <typename T>
DirectedWeightedEdge<T>::DirectedWeightedEdge(const CXXGraph::id_t id,
                                              const Node<T> &node1,
                                              const Node<T> &node2,
                                              const double weight)
    : DirectedEdge<T>(id, node1, node2), Weighted(weight) {}

template <typename T>
DirectedWeightedEdge<T>::DirectedWeightedEdge(const CXXGraph::id_t id,
                                              shared<const Node<T>> node1,
                                              shared<const Node<T>> node2,
                                              const double weight)
    : DirectedEdge<T>(id, node1, node2), Weighted(weight) {}

template <typename T>
DirectedWeightedEdge<T>::DirectedWeightedEdge(
    const CXXGraph::id_t id,
    const std::pair<const Node<T> *, const Node<T> *> &nodepair,
    const double weight)
    : DirectedEdge<T>(id, nodepair), Weighted(weight) {}

template <typename T>
DirectedWeightedEdge<T>::DirectedWeightedEdge(
    const CXXGraph::id_t id,
    const std::pair<shared<const Node<T>>, shared<const Node<T>>> &nodepair,
    const double weight)
    : DirectedEdge<T>(id, nodepair), Weighted(weight) {}

template <typename T>
DirectedWeightedEdge<T>::DirectedWeightedEdge(const DirectedEdge<T> &edge,
                                              const double weight)
    : DirectedEdge<T>(edge), Weighted(weight) {}

template <typename T>
DirectedWeightedEdge<T>::DirectedWeightedEdge(const Edge<T> &edge,
                                              const double weight)
    : DirectedEdge<T>(edge), Weighted(weight) {}

template <typename T>
DirectedWeightedEdge<T>::DirectedWeightedEdge(const DirectedEdge<T> &edge)
    : DirectedEdge<T>(edge), Weighted() {}

template <typename T>
DirectedWeightedEdge<T>::DirectedWeightedEdge(const Edge<T> &edge)
    : DirectedEdge<T>(edge), Weighted() {}

template <typename T>
DirectedWeightedEdge<T>::DirectedWeightedEdge(
    const UndirectedWeightedEdge<T> &edge)
    : DirectedEdge<T>(edge), Weighted(edge.getWeight()) {}

template <typename T>
const std::optional<bool> DirectedWeightedEdge<T>::isWeighted() const {
  return true;
}

template <typename T>
std::ostream &operator<<(std::ostream &os,
                         const DirectedWeightedEdge<T> &edge) {
  os << "((Node: " << edge.getFrom().getId() << ")) +----- |Edge: #"
     << edge.getId() << " W:" << edge.getWeight()
     << "|-----> ((Node: " << edge.getTo().getId() << "))";
  return os;
}

}  // namespace CXXGraph

#endif  // __CXXGRAPH_DIRECTEDWEIGHTEDEDGE_H__
