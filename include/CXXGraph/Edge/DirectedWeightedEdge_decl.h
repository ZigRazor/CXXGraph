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
#ifndef CXXGRAPH_DIRECTEDWEIGHTEDEDGE_DECL_H_
#define CXXGRAPH_DIRECTEDWEIGHTEDEDGE_DECL_H_

#pragma once

#include "DirectedEdge_decl.h"
#include "Weighted.h"

namespace CXXGraph {
// Smart pointers alias
template <typename T>
using unique = std::unique_ptr<T>;
template <typename T>
using shared = std::shared_ptr<T>;

// Forward Declaration
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
  constexpr DirectedWeightedEdge(const CXXGraph::id_t id, const Node<T> &node1,
                       const Node<T> &node2, const double weight);
  constexpr DirectedWeightedEdge(const CXXGraph::id_t id,
                                 shared<const Node<T>> node1,
                       shared<const Node<T>> node2, const double weight);
  constexpr DirectedWeightedEdge(
      const CXXGraph::id_t id,
      const std::pair<const Node<T> *, const Node<T> *> &nodepair,
      const double weight);
  constexpr DirectedWeightedEdge(
      const CXXGraph::id_t id,
      const std::pair<shared<const Node<T>>, shared<const Node<T>>> &nodepair,
      const double weight);
  constexpr DirectedWeightedEdge(const DirectedEdge<T> &edge,
                                 const double weight);
  constexpr DirectedWeightedEdge(const Edge<T> &edge, const double weight);
  constexpr DirectedWeightedEdge(const DirectedEdge<T> &edge);
  constexpr DirectedWeightedEdge(const Edge<T> &edge);
  constexpr DirectedWeightedEdge(const UndirectedWeightedEdge<T> &edge);
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

}  // namespace CXXGraph

#endif  // CXXGRAPH_DIRECTEDWEIGHTEDEDGE_DECL_H_
