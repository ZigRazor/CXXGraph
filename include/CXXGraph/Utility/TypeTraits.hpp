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

#ifndef __CXXGRAPH_TYPE_TRAITS__
#define __CXXGRAPH_TYPE_TRAITS__

#pragma once

#include <memory>

#include "CXXGraph/Edge/DirectedEdge.hpp"
#include "CXXGraph/Edge/DirectedWeightedEdge.hpp"
#include "CXXGraph/Edge/Edge.hpp"
#include "CXXGraph/Edge/UndirectedEdge.hpp"
#include "CXXGraph/Edge/UndirectedWeightedEdge.hpp"
#include "CXXGraph/Edge/Weighted.hpp"
#include "CXXGraph/Node/Node.hpp"

namespace CXXGraph {

// define is_node type trait for Nodes, Nodes pointers and shared pointers
template <typename T>
struct is_node : std::false_type {};

template <typename T>
struct is_node<Node<T>> : std::true_type {};

template <typename T>
struct is_node<const Node<T>*> : std::true_type {};

template <typename T>
struct is_node<shared<const Node<T>>> : std::true_type {};

template <typename T>
inline constexpr bool is_node_v = is_node<T>::value;

// define is_edge type trait for Edges, Edges pointers and shared pointers
template <typename T>
struct is_edge : std::false_type {};

template <typename T>
struct is_edge<Edge<T>> : std::true_type {};

template <typename T>
struct is_edge<const Edge<T>*> : std::true_type {};

template <typename T>
struct is_edge<shared<const Edge<T>>> : std::true_type {};

template <typename T>
inline constexpr bool is_edge_v = is_edge<T>::value;
}  // namespace CXXGraph

#endif