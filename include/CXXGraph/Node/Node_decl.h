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

#ifndef CXXGRAPH_NODE_DECL_H_
#define CXXGRAPH_NODE_DECL_H_

#pragma once
#include <iostream>
#include <type_traits>
#include "CXXGraph/Utility/id_t.hpp"

namespace CXXGraph {
template <typename T, typename = std::string>
class Node;
template <typename T, typename UserID>
std::ostream &operator<<(std::ostream &os, const Node<T, UserID> &node);
template <typename T, typename UserID>
class Node {
 private:
  CXXGraph::id_t id = 0;
  UserID userId{};
  T data;
  constexpr void setId(const UserID &);

 public:
  using Node_t = T;

  constexpr Node(const UserID &, const T &data);
  // Move constructor
  constexpr explicit Node(const UserID &, T &&data) noexcept(std::is_nothrow_move_assignable<T>::value);
  ~Node() noexcept = default;
  constexpr const CXXGraph::id_t &getId() const;
  constexpr const UserID &getUserId() const;
  constexpr const T &getData() const;
  constexpr T& getData();
  constexpr void setData(T &&new_data);
  // operator
  constexpr bool operator==(const Node<T, UserID> &b) const;
  constexpr bool operator<(const Node<T, UserID> &b) const;
  
  friend std::ostream &operator<< <>(std::ostream &os, const Node<T, UserID> &node);
};

}  // namespace CXXGraph

#endif  // CXXGRAPH_NODE_DECL_H_
