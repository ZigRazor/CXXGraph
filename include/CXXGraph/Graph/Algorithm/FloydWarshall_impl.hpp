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

#ifndef __CXXGRAPH_FLOYDWARSHALL_IMPL_H__
#define __CXXGRAPH_FLOYDWARSHALL_IMPL_H__

#pragma once

#include "CXXGraph/Graph/Graph_decl.h"

namespace CXXGraph {
template <typename T>
const FWResult Graph<T>::floydWarshall() const {
  FWResult result;
  result.success = false;
  result.errorMessage = "";
  std::unordered_map<std::pair<std::string, std::string>, double,
                     CXXGraph::pair_hash>
      pairwise_dist;
  //const auto &nodeSet = Graph<T>::getNodeSet();
  const auto &nodeSet = Graph<T>::getNodeVector();
  // create a pairwise distance matrix with distance node distances
  // set to inf. Distance of node to itself is set as 0.
  for (const auto &elem1 : nodeSet) {
    for (const auto &elem2 : nodeSet) {
      auto key = std::make_pair(elem1->getUserId(), elem2->getUserId());
      if (elem1 != elem2)
        pairwise_dist[key] = INF_DOUBLE;
      else
        pairwise_dist[key] = 0.0;
    }
  }

  //const auto &edgeSet = Graph<T>::getEdgeSet();
  const auto &edgeSet = Graph<T>::getEdgeVector();
  // update the weights of nodesfloydWarshall
  // connected by edges
  for (const auto &edge : edgeSet) {
    const auto &elem = edge->getNodePair();
    if (edge->isWeighted().has_value() && edge->isWeighted().value()) {
      auto edgeWeight =
          (std::dynamic_pointer_cast<const Weighted>(edge))->getWeight();
      auto key =
          std::make_pair(elem.first->getUserId(), elem.second->getUserId());
      pairwise_dist[key] = edgeWeight;
      if (edge->isDirected() == false) {
        auto reverseKey =
            std::make_pair(elem.second->getUserId(), elem.first->getUserId());
        pairwise_dist[reverseKey] = edgeWeight;
      }
    } else {
      // if an edge exists but has no weight associated
      // with it, we return an error message
      result.errorMessage = ERR_NO_WEIGHTED_EDGE;
      return result;
    }
  }

  for (const auto &k : nodeSet) {
    // set all vertices as source one by one
    for (const auto &src : nodeSet) {
      // iterate through all vertices as destination for the
      // current source
      auto src_k = std::make_pair(src->getUserId(), k->getUserId());
      for (const auto &dst : nodeSet) {
        // If vertex k provides a shorter path than
        // src to dst, update the value of
        // pairwise_dist[src_to_dst]
        auto src_dst = std::make_pair(src->getUserId(), dst->getUserId());
        auto k_dst = std::make_pair(k->getUserId(), dst->getUserId());
        if (pairwise_dist[src_dst] >
                (pairwise_dist[src_k] + pairwise_dist[k_dst]) &&
            (pairwise_dist[k_dst] != INF_DOUBLE &&
             pairwise_dist[src_k] != INF_DOUBLE))
          pairwise_dist[src_dst] = pairwise_dist[src_k] + pairwise_dist[k_dst];
      }
    }
  }

  result.success = true;
  // presense of negative number in the diagonal indicates
  // that that the graph contains a negative cycle
  for (const auto &node : nodeSet) {
    auto diag = std::make_pair(node->getUserId(), node->getUserId());
    if (pairwise_dist[diag] < 0.) {
      result.negativeCycle = true;
      return result;
    }
  }
  result.result = std::move(pairwise_dist);
  return result;
}
}  // namespace CXXGraph
#endif  // __CXXGRAPH_FLOYDWARSHALL_IMPL_H__
