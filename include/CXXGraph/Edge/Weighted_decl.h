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

#ifndef __CXXGRAPH_WEIGHTED_DECL_H__
#define __CXXGRAPH_WEIGHTED_DECL_H__

#pragma once

namespace CXXGraph {
class Weighted {
 private:
  double weight = 0.0;

 public:
  Weighted();
  explicit Weighted(const double weight);
  virtual ~Weighted() = default;
  double getWeight() const;
  void setWeight(const double weight);
};
}  // namespace CXXGraph

#endif  // __CXXGRAPH_WEIGHTED_DECL_H__