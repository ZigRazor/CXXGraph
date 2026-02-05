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

#ifndef __CXXGRAPH_DIRECTEDEDGE_DECL_H__
#define __CXXGRAPH_DIRECTEDEDGE_DECL_H__

#pragma once

#include <memory>
#include <string>
#include <utility>

#include "Edge_decl.h"

namespace CXXGraph {
// Smart pointers alias
template <typename T>
using unique = std::unique_ptr<T>;
template <typename T>
using shared = std::shared_ptr<T>;

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
  DirectedEdge(const std::string &userId, const Node<T> &node1,
               const Node<T> &node2);
  DirectedEdge(const std::string &userId, shared<const Node<T>> node1,
               shared<const Node<T>> node2);
  DirectedEdge(const std::string &userId,
               const std::pair<const Node<T> *, const Node<T> *> &nodepair);
  DirectedEdge(
      const std::string &userId,
      const std::pair<shared<const Node<T>>, shared<const Node<T>>> &nodepair);
  DirectedEdge(const Edge<T> &edge);
  ~DirectedEdge() override = default;
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
}  // namespace CXXGraph

#endif  // __CXXGRAPH_DIRECTEDEDGE_H__
