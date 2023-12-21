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

#ifndef __CXXGRAPH_PRIM_IMPL_H__
#define __CXXGRAPH_PRIM_IMPL_H__

#pragma once

#include "CXXGraph/Graph/Graph_decl.h"

namespace CXXGraph {

template <typename T>
const MstResult Graph<T>::prim() const {
  MstResult result;
  result.success = false;
  result.errorMessage = "";
  result.mstCost = INF_DOUBLE;
  if (!isUndirectedGraph()) {
    result.errorMessage = ERR_DIR_GRAPH;
    return result;
  }
  if (!isConnectedGraph()) {
    result.errorMessage = ERR_NOT_STRONG_CONNECTED;
    return result;
  }
  auto nodeSet = Graph<T>::getNodeSet();
  auto n = nodeSet.size();

  // setting all the distances initially to INF_DOUBLE
  std::unordered_map<shared<const Node<T>>, double, nodeHash<T>> dist;
  for (const auto &elem : (*cachedAdjMatrix)) {
    dist[elem.first] = INF_DOUBLE;
  }

  // creating a min heap using priority queue
  // first element of pair contains the distance
  // second element of pair contains the vertex
  std::priority_queue<std::pair<double, shared<const Node<T>>>,
                      std::vector<std::pair<double, shared<const Node<T>>>>,
                      std::greater<std::pair<double, shared<const Node<T>>>>>
      pq;

  // pushing the source vertex 's' with 0 distance in min heap
  auto source = *(nodeSet.begin());
  pq.push(std::make_pair(0.0, source));
  result.mstCost = 0;
  std::vector<CXXGraph::id_t> doneNode;
  // mark source node as done
  // otherwise we get (0, 0) also in mst
  doneNode.push_back(source->getId());
  // stores the parent and corresponding child node
  // of the edges that are part of MST
  std::unordered_map<CXXGraph::id_t, std::string> parentNode;
  while (!pq.empty()) {
    // second element of pair denotes the node / vertex
    shared<const Node<T>> currentNode = pq.top().second;
    auto nodeId = currentNode->getId();
    if (std::find(doneNode.begin(), doneNode.end(), nodeId) == doneNode.end()) {
      auto pair = std::make_pair(parentNode[nodeId], currentNode->getUserId());
      result.mst.push_back(pair);
      result.mstCost += pq.top().first;
      doneNode.push_back(nodeId);
    }

    pq.pop();
    // for all the reachable vertex from the currently exploring vertex
    // we will try to minimize the distance
    if (cachedAdjMatrix->find(currentNode) != cachedAdjMatrix->end()) {
      for (const auto &elem : cachedAdjMatrix->at(currentNode)) {
        // minimizing distances
        if (elem.second->isWeighted().has_value() &&
            elem.second->isWeighted().value()) {
          shared<const UndirectedWeightedEdge<T>> udw_edge =
              std::static_pointer_cast<const UndirectedWeightedEdge<T>>(
                  elem.second);
          if ((udw_edge->getWeight() < dist[elem.first]) &&
              (std::find(doneNode.begin(), doneNode.end(),
                         elem.first->getId()) == doneNode.end())) {
            dist[elem.first] = udw_edge->getWeight();
            parentNode[elem.first->getId()] = currentNode->getUserId();
            pq.push(std::make_pair(dist[elem.first], elem.first));
          }
        } else {
          // No Weighted Edge
          result.errorMessage = ERR_NO_WEIGHTED_EDGE;
          return result;
        }
      }
    }
  }
  result.success = true;
  return result;
}
}  // namespace CXXGraph
#endif  // __CXXGRAPH_PRIM_IMPL_H__