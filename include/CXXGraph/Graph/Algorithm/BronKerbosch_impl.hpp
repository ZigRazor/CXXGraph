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

#ifndef __CXXGRAPH_BRONKERBOSCH_IMPL_H__
#define __CXXGRAPH_BRONKERBOSCH_IMPL_H__

#pragma once

#include "CXXGraph/Graph/Graph_decl.h"

namespace CXXGraph {

template <typename T>
const BronKerboschResult<T> Graph<T>::bron_kerbosch() const {
  std::vector<T_NodeSet<T>> maximalCliques{};
  BronKerboschResult<T> result;

  if (!isUndirectedGraph()) {
    result.success = false;
    result.errorMessage = ERR_DIR_GRAPH;
    return result;
  }

  T_NodeSet<T> _X, _R, _P(getNodeSet());

  std::function<void(T_NodeSet<T>, T_NodeSet<T>, T_NodeSet<T>)> rec =
      [&maximalCliques, &rec, this](T_NodeSet<T> R, T_NodeSet<T> P,
                                    T_NodeSet<T> X) {
        if (P.empty() && X.empty()) {
          maximalCliques.push_back(R);
        }

        auto it = P.begin();
        while (it != P.end()) {
          const auto v = *it;
          T_NodeSet<T> X2, R2(R), P2, nbd(inOutNeighbors(v));
          R2.insert(v);
          for (const auto &u : nbd) {
            if (X.count(u) > 0 && u != v) {
              X2.insert(u);
            }
            if (P.count(u) > 0 && u != v) {
              P2.insert(u);
            }
          }
          rec(R2, P2, X2);
          X.insert(v);
          it = P.erase(it);
        }
      };

  rec(_R, _P, _X);
  result.success = true;
  result.maximalCliques = maximalCliques;
  return result;
}

}  // namespace CXXGraph
#endif