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

#ifndef __CXXGRAPH_TOPOLOGICALSORT_IMPL_H__
#define __CXXGRAPH_TOPOLOGICALSORT_IMPL_H__

#pragma once

#include "CXXGraph/Graph/Graph_decl.h"

namespace CXXGraph {

template <typename T>
TopoSortResult<T> Graph<T>::topologicalSort() const {
  TopoSortResult<T> result;
  result.success = false;

  if (!isDirectedGraph()) {
    result.errorMessage = ERR_UNDIR_GRAPH;
    return result;
  } else if (isCyclicDirectedGraphBFS()) {
    result.errorMessage = ERR_CYCLIC_GRAPH;
    return result;
  } else {
    //const auto &nodeSet = getNodeSet();
    const auto &nodeSet = getNodeVector();
    std::unordered_map<shared<const Node<T>>, bool, nodeHash<T>> visited;

    std::function<void(shared<const Node<T>>)> postorder_helper =
        [this, &postorder_helper, &visited,
         &result](shared<const Node<T>> curNode) {
          visited[curNode] = true;

          if (cachedAdjMatrix->find(curNode) != cachedAdjMatrix->end()) {
            for (const auto &edge : cachedAdjMatrix->at(curNode)) {
              const auto &nextNode = edge.first;
              if (false == visited[nextNode]) {
                postorder_helper(nextNode);
              }
            }
          }

          result.nodesInTopoOrder.push_back(*curNode);
        };

    auto numNodes = cachedAdjMatrix->size();
    result.nodesInTopoOrder.reserve(numNodes);

    for (const auto &node : nodeSet) {
      if (false == visited[node]) {
        postorder_helper(node);
      }
    }

    result.success = true;
    std::reverse(result.nodesInTopoOrder.begin(),
                 result.nodesInTopoOrder.end());
    return result;
  }
}

}  // namespace CXXGraph
#endif  // __CXXGRAPH_TOPOLOGICALSORT_IMPL_H__
