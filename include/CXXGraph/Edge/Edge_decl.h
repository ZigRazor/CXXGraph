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

#ifndef __CXXGRAPH_EDGE_DECL_H__
#define __CXXGRAPH_EDGE_DECL_H__

#pragma once

#include <memory>
#include <optional>
#include <utility>

#include "CXXGraph/Node/Node.h"

namespace CXXGraph {
// Smart pointers alias
template <typename T>
using unique = std::unique_ptr<T>;
template <typename T>
using shared = std::shared_ptr<T>;

template <typename T>
class Edge;
// ostream operator
template <typename T>
std::ostream &operator<<(std::ostream &o, const Edge<T> &edge);
template <typename T>
class Edge {
 private:
  CXXGraph::id_t id = 0;
  std::pair<shared<const Node<T>>, shared<const Node<T>>> nodePair;

 public:
  typedef T Node_t;

  Edge(const CXXGraph::id_t id, const Node<T> &node1, const Node<T> &node2);
  Edge(const CXXGraph::id_t id, shared<const Node<T>> node1,
       shared<const Node<T>> node2);
  Edge(const CXXGraph::id_t id,
       const std::pair<const Node<T> *, const Node<T> *> &nodepair);
  Edge(const CXXGraph::id_t id,
       const std::pair<shared<const Node<T>>, shared<const Node<T>>> &nodepair);
  virtual ~Edge() = default;
  void setFirstNode(shared<const Node<T>> node);
  void setSecondNode(shared<const Node<T>> node);
  const unsigned long long getId() const;
  const std::pair<shared<const Node<T>>, shared<const Node<T>>> &getNodePair()
      const;
  shared<const Node<T>> getOtherNode(shared<const Node<T>> node) const;
  virtual const std::optional<bool> isDirected() const;
  virtual const std::optional<bool> isWeighted() const;
  // operator
  virtual bool operator==(const Edge<T> &b) const;
  bool operator<(const Edge<T> &b) const;

  friend std::ostream &operator<< <>(std::ostream &os, const Edge<T> &edge);
};

}  // namespace CXXGraph

#endif  // __CXXGRAPH_EDGE_DECL_H__
