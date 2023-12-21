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

#include "CXXGraph/Edge/DirectedEdge.h"
#include "CXXGraph/Edge/DirectedWeightedEdge.h"
#include "CXXGraph/Edge/Edge.h"
#include "CXXGraph/Edge/UndirectedEdge.h"
#include "CXXGraph/Edge/UndirectedWeightedEdge.h"
#include "CXXGraph/Edge/Weighted.h"
#include "CXXGraph/Node/Node.h"

namespace CXXGraph {

// define is_node type trait for Nodes, Nodes pointers and shared pointers
template <typename T>
struct is_node : std::false_type {};

template <typename T>
struct is_node<Node<T>> : std::true_type {};

// define is_node_ptr type trait for Node pointers and shared pointers
template <typename T>
struct is_node_ptr : std::false_type {};

template <typename T>
struct is_node_ptr<const Node<T>*> : std::true_type {};

template <typename T>
struct is_node_ptr<shared<const Node<T>>> : std::true_type {};

template <typename T>
inline constexpr bool is_node_ptr_v = is_node<T>::value;

// define is_edge type trait for Edges
template <typename T>
struct is_edge : std::false_type {};

template <typename T>
struct is_edge<Edge<T>> : std::true_type {};

// define is_edge_ptr type trait for Edge pointers and shared pointers
template <typename T>
struct is_edge_ptr : std::false_type {};

template <typename T>
struct is_edge_ptr<const Edge<T>*> : std::true_type {};

template <typename T>
struct is_edge_ptr<shared<const Edge<T>>> : std::true_type {};

template <typename T>
inline constexpr bool is_edge_ptr_v = is_edge<T>::value;
}  // namespace CXXGraph

#endif
