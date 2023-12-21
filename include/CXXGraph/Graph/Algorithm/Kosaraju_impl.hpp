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

#ifndef __CXXGRAPH_KOSARAJU_IMPL_H__
#define __CXXGRAPH_KOSARAJU_IMPL_H__

#pragma once

#include "CXXGraph/Graph/Graph_decl.h"

namespace CXXGraph {

template <typename T>
SCCResult<T> Graph<T>::kosaraju() const {
  SCCResult<T> result;
  result.success = false;

  if (!isDirectedGraph()) {
    result.errorMessage = ERR_UNDIR_GRAPH;
    return result;
  } else {
    auto nodeSet = getNodeSet();
    // created visited map
    std::unordered_map<CXXGraph::id_t, bool> visited;
    for (const auto &node : nodeSet) {
      visited[node->getId()] = false;
    }

    std::stack<shared<const Node<T>>> st;
    std::function<void(shared<const Node<T>>)> dfs_helper =
        [this, &visited, &dfs_helper, &st](shared<const Node<T>> source) {
          // mark the vertex visited
          visited[source->getId()] = true;

          // travel the neighbors
          for (int i = 0; i < (*cachedAdjMatrix)[source].size(); i++) {
            shared<const Node<T>> neighbor =
                (*cachedAdjMatrix)[source].at(i).first;
            if (visited[neighbor->getId()] == false) {
              // make recursive call from neighbor
              dfs_helper(neighbor);
            }
          }

          st.push(source);
        };

    for (const auto &node : nodeSet) {
      if (visited[node->getId()] == false) {
        dfs_helper(node);
      }
    }

    // construct the transpose of the given graph
    AdjacencyMatrix<T> rev;
    auto addElementToAdjMatrix = [&rev](shared<const Node<T>> nodeFrom,
                                        shared<const Node<T>> nodeTo,
                                        shared<const Edge<T>> edge) {
      std::pair<shared<const Node<T>>, shared<const Edge<T>>> elem = {nodeTo,
                                                                      edge};
      rev[nodeFrom].push_back(std::move(elem));
    };
    for (const auto &edgeSetIt : edgeSet) {
      shared<const DirectedEdge<T>> d_edge =
          std::static_pointer_cast<const DirectedEdge<T>>(edgeSetIt);
      // Add the reverse edge to the reverse adjacency matrix
      addElementToAdjMatrix(d_edge->getNodePair().second,
                            d_edge->getNodePair().first, d_edge);
    }

    visited.clear();

    std::function<void(shared<const Node<T>>, SCCResult<T>, int)> dfs_helper1 =
        [this, &rev, &visited, &dfs_helper1](
            shared<const Node<T>> source, SCCResult<T> result, int sccLabel) {
          // mark the vertex visited
          visited[source->getId()] = true;
          // Add the current vertex to the strongly connected
          // component
          // comp.push_back(*source);
          result.sccMap[source->getId()] = sccLabel;

          // travel the neighbors
          for (int i = 0; i < rev[source].size(); i++) {
            shared<const Node<T>> neighbor = rev[source].at(i).first;
            if (visited[neighbor->getId()] == false) {
              // make recursive call from neighbor
              dfs_helper1(neighbor, result, sccLabel);
            }
          }
        };

    int sccLabel = 0;
    while (st.size() != 0) {
      auto rem = st.top();
      st.pop();
      if (visited[rem->getId()] == false) {
        // std::vector<Node<T>> comp;
        dfs_helper1(rem, result, sccLabel);
        sccLabel++;
        // result.stronglyConnectedComps.push_back(comp);
      }
    }
    result.noOfComponents = sccLabel;
    result.success = true;
    return result;
  }
}
}  // namespace CXXGraph
#endif  // __CXXGRAPH_KOSARAJU_IMPL_H__