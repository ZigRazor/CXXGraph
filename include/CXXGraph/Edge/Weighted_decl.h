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

#ifndef CXXGRAPH_WEIGHTED_DECL_H_
#define CXXGRAPH_WEIGHTED_DECL_H_

#pragma once

namespace CXXGraph {
class Weighted {
 private:
  double weight = 0.0;

 public:
  constexpr Weighted() noexcept;
  constexpr explicit Weighted(const double weight) noexcept;
  virtual ~Weighted() noexcept = default;
  constexpr double getWeight() const noexcept;
  constexpr void setWeight(const double weight);
};
}  // namespace CXXGraph

#endif  // CXXGRAPH_WEIGHTED_DECL_H_