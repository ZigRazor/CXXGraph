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

#ifndef __CXXGRAPH_TRANSITIVEREDUCTION_IMPL_H__
#define __CXXGRAPH_TRANSITIVEREDUCTION_IMPL_H__

#pragma once

#include "CXXGraph/Graph/Graph_decl.h"

namespace CXXGraph {
/*
 * See Harry Hsu. "An algorithm for finding a minimal equivalent graph of a
 * digraph.", Journal of the ACM, 22(1):11-16, January 1975
 *
 * foreach x in graph.vertices
 *   foreach y in graph.vertices
 *     foreach z in graph.vertices
 *       delete edge xz if edges xy and yz exist
 */
template <typename T>
const Graph<T> Graph<T>::transitiveReduction() const {
  Graph<T> result(this->edgeSet);

  CXXGraph::id_t edgeId = 0;
  std::unordered_set<shared<const Node<T>>, nodeHash<T>> nodes =
      this->getNodeSet();
  for (auto x : nodes) {
    for (auto y : nodes) {
      if (this->findEdge(x, y, edgeId)) {
        for (auto z : nodes) {
          if (this->findEdge(y, z, edgeId)) {
            if (this->findEdge(x, z, edgeId)) {
              result.removeEdge(edgeId);
            }
          }
        }
      }
    }
  }

  return result;
}
}  // namespace CXXGraph
#endif  // __CXXGRAPH_TRANSITIVEREDUCTION_IMPL_H__