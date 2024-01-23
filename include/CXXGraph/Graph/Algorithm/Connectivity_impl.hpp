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

#ifndef __CXXGRAPH_CONNECTIVITY_IMPL_H__
#define __CXXGRAPH_CONNECTIVITY_IMPL_H__

#pragma once

#include "CXXGraph/Graph/Graph_decl.h"

namespace CXXGraph {

template <typename T>
bool Graph<T>::isConnectedGraph() const {
  if (!isUndirectedGraph()) {
    return false;
  } else {
    auto nodeSet = getNodeSet();
    // created visited map
    std::unordered_map<CXXGraph::id_t, bool> visited;
    for (const auto &node : nodeSet) {
      visited[node->getId()] = false;
    }
    std::function<void(shared<const Node<T>>)> dfs_helper =
        [this, &visited, &dfs_helper](shared<const Node<T>> source) {
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
        };
    // call dfs_helper for the first node
    dfs_helper(*(nodeSet.begin()));

    // check if all the nodes are visited
    for (const auto &node : nodeSet) {
      if (visited[node->getId()] == false) {
        return false;
      }
    }
    return true;
  }
}

template <typename T>
bool Graph<T>::isStronglyConnectedGraph() const {
  if (!isDirectedGraph()) {
    return false;
  } else {
    auto nodeSet = getNodeSet();
    for (const auto &start_node : nodeSet) {
      // created visited map
      std::unordered_map<CXXGraph::id_t, bool> visited;
      for (const auto &node : nodeSet) {
        visited[node->getId()] = false;
      }
      std::function<void(shared<const Node<T>>)> dfs_helper =
          [this, &visited, &dfs_helper](shared<const Node<T>> source) {
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
          };
      // call dfs_helper for the first node
      dfs_helper(start_node);

      // check if all the nodes are visited
      for (const auto &node : nodeSet) {
        if (visited[node->getId()] == false) {
          return false;
        }
      }
    }
    return true;
  }
}
}  // namespace CXXGraph
#endif  // __CXXGRAPH_CONNECTIVITY_IMPL_H__