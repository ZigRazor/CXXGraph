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

#ifndef __CXXGRAPH_BORUVKA_IMPL_H__
#define __CXXGRAPH_BORUVKA_IMPL_H__

#pragma once

#include "CXXGraph/Graph/Graph_decl.h"

namespace CXXGraph {
    
template <typename T>
const MstResult Graph<T>::boruvka() const {
  MstResult result;
  result.success = false;
  result.errorMessage = "";
  result.mstCost = INF_DOUBLE;
  if (!isUndirectedGraph()) {
    result.errorMessage = ERR_DIR_GRAPH;
    return result;
  }
  const auto nodeSet = Graph<T>::getNodeSet();
  const auto n = nodeSet.size();

  // Use std map for storing n subsets.
  auto subsets = make_shared<std::unordered_map<CXXGraph::id_t, Subset>>();

  // Initially there are n different trees.
  // Finally there will be one tree that will be MST
  auto numTrees = n;

  // check if all edges are weighted and store the weights
  // in a map whose keys are the edge ids and values are the edge weights
  const auto edgeSet = Graph<T>::getEdgeSet();
  std::unordered_map<CXXGraph::id_t, double> edgeWeight;
  for (const auto &edge : edgeSet) {
    if (edge->isWeighted().has_value() && edge->isWeighted().value())
      edgeWeight[edge->getId()] =
          (std::dynamic_pointer_cast<const Weighted>(edge))->getWeight();
    else {
      // No Weighted Edge
      result.errorMessage = ERR_NO_WEIGHTED_EDGE;
      return result;
    }
  }

  for (const auto &node : nodeSet) {
    Subset set{node->getId(), 0};
    (*subsets)[node->getId()] = set;
  }

  result.mstCost = 0;  // we will store the cost here
  // exit when only 1 tree i.e. mst
  while (numTrees > 1) {
    // Everytime initialize cheapest map
    // It stores index of the cheapest edge of subset.
    std::unordered_map<CXXGraph::id_t, CXXGraph::id_t> cheapest;
    for (const auto &node : nodeSet) cheapest[node->getId()] = INT_MAX;

    // Traverse through all edges and update
    // cheapest of every component
    for (const auto &edge : edgeSet) {
      auto elem = edge->getNodePair();
      auto edgeId = edge->getId();
      // Find sets of two corners of current edge
      auto set1 = Graph<T>::setFind(subsets, elem.first->getId());
      auto set2 = Graph<T>::setFind(subsets, elem.second->getId());

      // If two corners of current edge belong to
      // same set, ignore current edge
      if (set1 == set2) continue;

      // Else check if current edge is closer to previous
      // cheapest edges of set1 and set2
      if (cheapest[set1] == INT_MAX ||
          edgeWeight[cheapest[set1]] > edgeWeight[edgeId])
        cheapest[set1] = edgeId;

      if (cheapest[set2] == INT_MAX ||
          edgeWeight[cheapest[set2]] > edgeWeight[edgeId])
        cheapest[set2] = edgeId;
    }

    // iterate over all the vertices and add picked
    // cheapest edges to MST
    for (const auto &[nodeId, edgeId] : cheapest) {
      // Check if cheapest for current set exists
      if (edgeId != INT_MAX) {
        auto cheapestNode = Graph<T>::getEdge(edgeId).value()->getNodePair();
        auto set1 = Graph<T>::setFind(subsets, cheapestNode.first->getId());
        auto set2 = Graph<T>::setFind(subsets, cheapestNode.second->getId());
        if (set1 == set2) continue;
        result.mstCost += edgeWeight[edgeId];
        auto newEdgeMST = std::make_pair(cheapestNode.first->getUserId(),
                                         cheapestNode.second->getUserId());
        result.mst.push_back(newEdgeMST);
        // take union of set1 and set2 and decrease number of trees
        Graph<T>::setUnion(subsets, set1, set2);
        numTrees--;
      }
    }
  }
  result.success = true;
  return result;
}

}  // namespace CXXGraph
#endif  // __CXXGRAPH_BORUVKA_IMPL_H__