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

#ifndef __CXXGRAPH_NODE_DECL_H__
#define __CXXGRAPH_NODE_DECL_H__

#pragma once
#include <iostream>

#include "CXXGraph/Utility/id_t.hpp"

namespace CXXGraph {
template <typename T>
class Node;
template <typename T>
std::ostream &operator<<(std::ostream &os, const Node<T> &node);
template <typename T>
class Node {
 private:
  CXXGraph::id_t id = 0;
  std::string userId = "";
  T data;
  void setId(const std::string &);

 public:
  Node(const std::string &, const T &data);
  // Move constructor
  Node(const std::string &, T &&data) noexcept;
  ~Node() = default;
  const CXXGraph::id_t &getId() const;
  const std::string &getUserId() const;
  const T &getData() const;
  void setData(T &&new_data);
  // operator
  bool operator==(const Node<T> &b) const;
  bool operator<(const Node<T> &b) const;
  friend std::ostream &operator<< <>(std::ostream &os, const Node<T> &node);
};

}  // namespace CXXGraph

#endif  // __CXXGRAPH_NODE_DECL_H__