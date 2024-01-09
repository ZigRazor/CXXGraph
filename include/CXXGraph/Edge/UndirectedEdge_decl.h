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

#ifndef __CXXGRAPH_UNDIRECTEDEDGE_DECL_H__
#define __CXXGRAPH_UNDIRECTEDEDGE_DECL_H__

#pragma once

#include "Edge_decl.h"

namespace CXXGraph {
// Smart pointers alias
template <typename T>
using unique = std::unique_ptr<T>;
template <typename T>
using shared= std::shared_ptr<T>;

template <typename T>
class UndirectedEdge;

// ostream operator
template <typename T>
std::ostream &operator<<(std::ostream &o, const UndirectedEdge<T> &edge);

template <typename T>
class UndirectedEdge : public Edge<T> {
 public:
  UndirectedEdge(const CXXGraph::id_t id, const Node<T> &node1,
                 const Node<T> &node2);
  UndirectedEdge(const CXXGraph::id_t id, shared<const Node<T>> node1,
                 shared<const Node<T>> node2);
  UndirectedEdge(const CXXGraph::id_t id,
                 const std::pair<const Node<T> *, const Node<T> *> &nodepair);
  UndirectedEdge(const CXXGraph::id_t id,
                 const std::pair<shared<const Node<T>>, shared<const Node<T>>> &nodepair);
  UndirectedEdge(const Edge<T> &edge);
  virtual ~UndirectedEdge() = default;
  const Node<T> &getNode1() const;
  const Node<T> &getNode2() const;
  const std::optional<bool> isDirected() const override;
  const std::optional<bool> isWeighted() const override;
  // operator
  explicit operator DirectedEdge<T>() const {
    return DirectedEdge<T>(Edge<T>::getId(), Edge<T>::getNodePair());
  }

  friend std::ostream &operator<< <>(std::ostream &os,
                                     const UndirectedEdge<T> &edge);
};

}  // namespace CXXGraph

#endif  // __CXXGRAPH_UNDIRECTEDEDGE_DECL_H__
