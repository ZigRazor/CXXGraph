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
/***	 License: MPL v2.0***/
/***********************************************************/

#ifndef __CXXGRAPH_WEIGHTED_IMPL_H__
#define __CXXGRAPH_WEIGHTED_IMPL_H__

#pragma once

#include "Weighted_decl.h"

namespace CXXGraph {

// inline because the implementation of non-template function in header file
inline Weighted::Weighted() { weight = 0.0; }

// inline because the implementation of non-template function in header file
inline Weighted::Weighted(const double weight) { this->weight = weight; }

// inline because the implementation of non-template function in header file
inline double Weighted::getWeight() const { return weight; }

// inline because the implementation of non-template function in header file
inline void Weighted::setWeight(const double weight) { this->weight = weight; }

}  // namespace CXXGraph

#endif  // __CXXGRAPH_WEIGHTED_IMPL_H__