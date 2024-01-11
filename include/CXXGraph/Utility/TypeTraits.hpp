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

// is_node type trait
template <typename T>
struct is_node
    : std::integral_constant<
          bool, std::is_same<Node<typename T::Node_t>,
                             typename std::remove_const<T>::type>::value> {};

template <typename T>
struct is_node<T*>
    : std::integral_constant<
          bool, std::is_same<Node<typename T::Node_t>,
                             typename std::remove_const<T>::type>::value> {};

template <typename T>
struct is_node<shared<T>>
    : std::integral_constant<
          bool, std::is_same<Node<typename T::Node_t>,
                             typename std::remove_const<T>::type>::value> {};

template <typename T>
inline constexpr bool is_node_v = is_node<T>::value;

// is_node_ptr type trait
template <typename T>
struct is_node_ptr : std::false_type {};

template <typename T>
struct is_node_ptr<T*> : std::integral_constant<bool, is_node<T>::value> {};

template <typename T>
struct is_node_ptr<shared<T>>
    : std::integral_constant<bool, is_node<T>::value> {};

template <typename T>
inline constexpr bool is_node_ptr_v = is_node_ptr<T>::value;

// is_edge type trait
template <typename T>
struct is_edge
    : std::integral_constant<
          bool, std::is_base_of<Edge<typename T::Node_t>,
                                typename std::remove_const<T>::type>::value> {};

template <typename T>
struct is_edge<T*>
    : std::integral_constant<
          bool, std::is_base_of<Edge<typename T::Node_t>,
                                typename std::remove_const<T>::type>::value> {};

template <typename T>
struct is_edge<shared<T>>
    : std::integral_constant<
          bool, std::is_base_of<Edge<typename T::Node_t>,
                                typename std::remove_const<T>::type>::value> {};

template <typename T>
inline constexpr bool is_edge_v = is_edge<T>::value;

// is_edge_ptr type trait
template <typename T>
struct is_edge_ptr : std::false_type {};

template <typename T>
struct is_edge_ptr<T*> : std::integral_constant<bool, is_edge<T>::value> {};

template <typename T>
struct is_edge_ptr<shared<T>>
    : std::integral_constant<bool, is_edge<T>::value> {};

template <typename T>
inline constexpr bool is_edge_ptr_v = is_edge_ptr<T>::value;

}  // namespace CXXGraph

#endif
