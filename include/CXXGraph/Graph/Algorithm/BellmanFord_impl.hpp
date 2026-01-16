/***********************************************************/
/***      ______  ____  ______   ___  __    __         ***/
/***     /" _  "\("  _ "\( __ "\|"  \|" |  |" \        ***/
/***    (: ______)|   __/\/"  \ |    \   |  ||  |       ***/
/***     \/    | (\  |  )  |/ \|  o  )  |  |:  |       ***/
/***     // ___)_ /\\ \ /  /    \.   /   :  |\  |___    ***/
/***    (:      "(  <_|:  /  //\\  \  //\\  \|  |:::|   ***/
/***     \_______)\_______/  (__)_(_)(__\_)_(__|___|   ***/
/***                                                     ***/
/***********************************************************/
/***     Header-Only C++ Library for Graph             ***/
/***     Representation and Algorithms                 ***/
/***********************************************************/
/***     Author: ZigRazor                              ***/
/***     E-Mail: zigrazor@gmail.com                    ***/
/***********************************************************/
/***     Collaboration: -----------                    ***/
/***********************************************************/
/***     License: MPL v2.0                             ***/
/***********************************************************/

#ifndef __CXXGRAPH_BELLMANFORD_IMPL_H__
#define __CXXGRAPH_BELLMANFORD_IMPL_H__

#pragma once

#include <algorithm>
#include <unordered_map>
#include <vector>
#include "CXXGraph/Graph/Graph_decl.h"
#include "CXXGraph/Utility/ConstString.hpp"

namespace CXXGraph {

template <typename T>
const BellmanFordResult Graph<T>::bellmanford(const Node<T> &source,
                                              const Node<T> &target) const {
  BellmanFordResult result;
  result.success = false;
  result.errorMessage = "";
  result.result = INF_DOUBLE;

  auto nodeSet = Graph<T>::getNodeSet();
  auto source_node_it = std::find_if(
      nodeSet.begin(), nodeSet.end(),
      [&source](auto node) { return node->getUserId() == source.getUserId(); });
  if (source_node_it == nodeSet.end()) {
    // check if source node exist in the graph
    result.errorMessage = ERR_SOURCE_NODE_NOT_IN_GRAPH;
    return result;
  }
  auto target_node_it = std::find_if(
      nodeSet.begin(), nodeSet.end(),
      [&target](auto node) { return node->getUserId() == target.getUserId(); });
  if (target_node_it == nodeSet.end()) {
    // check if target node exist in the graph
    result.errorMessage = ERR_TARGET_NODE_NOT_IN_GRAPH;
    return result;
  }

  // Map nodes to integer indices for efficient vector usage
  size_t n = nodeSet.size();
  std::vector<shared<const Node<T>>> nodes(n);
  std::unordered_map<shared<const Node<T>>, size_t, nodeHash<T>> node_to_idx;
  size_t idx = 0;
  for (const auto &node : nodeSet) {
    nodes[idx] = node;
    node_to_idx[node] = idx++;
  }

  auto source_ptr = *source_node_it;
  auto target_ptr = *target_node_it;
  size_t src_idx = node_to_idx[source_ptr];
  size_t tgt_idx = node_to_idx[target_ptr];

  // Prepare edges as struct for better cache and sorting
  struct MyEdge {
    size_t u, v;
    double w;
  };
  std::vector<MyEdge> edges;
  auto edgeSet = Graph<T>::getEdgeSet();
  for (const auto &edge : edgeSet) {
    if (!edge->isWeighted().value_or(false)) {
      result.errorMessage = ERR_NO_WEIGHTED_EDGE;
      return result;
    }
    auto elem = edge->getNodePair();
    double weight =
        (std::dynamic_pointer_cast<const Weighted>(edge))->getWeight();
    edges.push_back({node_to_idx[elem.first], node_to_idx[elem.second], weight});
  }
  size_t m = edges.size();

  // OPTIMIZATION: Sort edges by source for better cache locality, but only for larger graphs
  const size_t SORT_THRESHOLD = 10000;  // Adjust threshold as needed
  if (m > SORT_THRESHOLD) {
    std::sort(edges.begin(), edges.end(),
              [](const MyEdge &a, const MyEdge &b) { return a.u < b.u; });
  }

  // setting all the distances initially to INF_DOUBLE
  std::vector<double> dist(n, INF_DOUBLE);
  dist[src_idx] = 0.0;

  // outer loop for vertex relaxation with early stopping
  bool earlyStopping = false;
  for (size_t i = 0; i < n - 1; ++i) {
    bool relaxed = false;

    // OPTIMIZATION: Process in blocks for better cache utilization
    const int BLOCK_SIZE = 64;
    for (size_t block_start = 0; block_start < m; block_start += BLOCK_SIZE) {
      size_t block_end = std::min(block_start + BLOCK_SIZE, m);

      // OPTIMIZATION: Prefetch next block
      if (block_start + BLOCK_SIZE < m) {
        __builtin_prefetch(&edges[block_start + BLOCK_SIZE], 0, 3);
      }

      // Process current block
      for (size_t j = block_start; j < block_end; ++j) {
        const auto &e = edges[j];
        if (dist[e.u] < INF_DOUBLE) {
          double new_dist = dist[e.u] + e.w;
          if (new_dist < dist[e.v]) {
            dist[e.v] = new_dist;
            relaxed = true;
          }
        }
      }
    }

    if (!relaxed) {
      earlyStopping = true;
      break;
    }
  }

  // check if there exists a negative cycle
  if (!earlyStopping) {
    bool hasNegativeCycle = false;
    for (const auto &e : edges) {
      if (dist[e.u] < INF_DOUBLE && dist[e.u] + e.w < dist[e.v]) {
        hasNegativeCycle = true;
        break;
      }
    }
    if (hasNegativeCycle) {
      result.success = true;
      result.negativeCycle = true;
      result.errorMessage = "";
      return result;
    }
  }

  if (dist[tgt_idx] != INF_DOUBLE) {
    result.success = true;
    result.errorMessage = "";
    result.negativeCycle = false;
    result.result = dist[tgt_idx];
    return result;
  }

  result.errorMessage = ERR_TARGET_NODE_NOT_REACHABLE;
  result.result = -1;
  return result;
}

}  // namespace CXXGraph

#endif  // __CXXGRAPH_BELLMANFORD_IMPL_H__