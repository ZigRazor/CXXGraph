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

#ifndef __CXXGRAPH_DIAL_IMPL_H__
#define __CXXGRAPH_DIAL_IMPL_H__

#pragma once

#include <algorithm>

#include "CXXGraph/Graph/Graph_decl.h"

namespace CXXGraph {

template <typename T>
const DialResult Graph<T>::dial(const Node<T> &source, int maxWeight) const {
  DialResult result;
  result.success = false;

  auto nodeSet = getNodeSet();

  auto source_node_it = std::find_if(
      nodeSet.begin(), nodeSet.end(),
      [&source](auto node) { return node->getUserId() == source.getUserId(); });
  if (source_node_it == nodeSet.end()) {
    // check if source node exist in the graph
    result.errorMessage = ERR_SOURCE_NODE_NOT_IN_GRAPH;
    return result;
  }
  /* With each distance, iterator to that vertex in
          its bucket is stored so that vertex can be deleted
          in O(1) at time of updation. So
          dist[i].first = distance of ith vertex from src vertex
          dits[i].second = vertex i in bucket number */
  auto V = nodeSet.size();
  std::unordered_map<shared<const Node<T>>,
                     std::pair<long, shared<const Node<T>>>, nodeHash<T>>
      dist;

  // Initialize all distances as infinite (INF)
  for (const auto &node : nodeSet) {
    dist[node].first = std::numeric_limits<long>::max();
  }

  // Create buckets B[].
  // B[i] keep vertex of distance label i
  std::vector<std::deque<shared<const Node<T>>>> B((maxWeight * V + 1));

  B[0].push_back(*source_node_it);
  dist[*source_node_it].first = 0;

  std::size_t idx = 0;
  while (true) {
    // Go sequentially through buckets till one non-empty
    // bucket is found
    while (idx < B.size() && B[idx].size() == 0u && idx < maxWeight * V) {
      idx++;
    }

    // If all buckets are empty, we are done.
    if (idx == maxWeight * V) {
      break;
    }

    // Take top vertex from bucket and pop it
    auto u = B[idx].front();
    B[idx].pop_front();

    // Process all adjacents of extracted vertex 'u' and
    // update their distanced if required.
    for (const auto &i : (*cachedAdjMatrix)[u]) {
      auto v = i.first;
      int weight = 0;
      if (i.second->isWeighted().has_value() &&
          i.second->isWeighted().value()) {
        if (i.second->isDirected().has_value() &&
            i.second->isDirected().value()) {
          shared<const DirectedWeightedEdge<T>> dw_edge =
              std::static_pointer_cast<const DirectedWeightedEdge<T>>(i.second);
          weight = (int)dw_edge->getWeight();
        } else if (i.second->isDirected().has_value() &&
                   !i.second->isDirected().value()) {
          shared<const UndirectedWeightedEdge<T>> udw_edge =
              std::static_pointer_cast<const UndirectedWeightedEdge<T>>(
                  i.second);
          weight = (int)udw_edge->getWeight();
        } else {
          // ERROR it shouldn't never returned ( does not exist a Node
          // Weighted and not Directed/Undirected)
          result.errorMessage = ERR_NO_DIR_OR_UNDIR_EDGE;
          return result;
        }
      } else {
        // No Weighted Edge
        result.errorMessage = ERR_NO_WEIGHTED_EDGE;
        return result;
      }
      auto u_i = std::find_if(
          dist.begin(), dist.end(),
          [u](std::pair<shared<const Node<T>>,
                        std::pair<long, shared<const Node<T>>>> const &it) {
            return (*u == *(it.first));
          });

      auto v_i = std::find_if(
          dist.begin(), dist.end(),
          [v](std::pair<shared<const Node<T>>,
                        std::pair<long, shared<const Node<T>>>> const &it) {
            return (*v == *(it.first));
          });
      long du = u_i->second.first;
      long dv = v_i->second.first;

      // If there is shorted path to v through u.
      if (dv > du + weight) {
        // If dv is not INF then it must be in B[dv]
        // bucket, so erase its entry using iterator
        // in O(1)
        if (dv != std::numeric_limits<long>::max()) {
          auto findIter = std::find(B[dv].begin(), B[dv].end(), dist[v].second);
          B[dv].erase(findIter);
        }

        //  updating the distance
        dist[v].first = du + weight;
        dv = dist[v].first;

        // pushing vertex v into updated distance's bucket
        B[dv].push_front(v);

        // storing updated iterator in dist[v].second
        dist[v].second = *(B[dv].begin());
      }
    }
  }
  for (const auto &dist_i : dist) {
    result.minDistanceMap[dist_i.first->getId()] = dist_i.second.first;
  }
  result.success = true;

  return result;
}
}  // namespace CXXGraph
#endif  // __CXXGRAPH_DIAL_IMPL_H__
