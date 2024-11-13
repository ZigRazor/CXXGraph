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

#ifndef __CXXGRAPH_DIJKSTRA_IMPL_H__
#define __CXXGRAPH_DIJKSTRA_IMPL_H__

#pragma once

#include <algorithm>

#include "CXXGraph/Graph/Graph_decl.h"

namespace CXXGraph {
template <typename T>
const DijkstraResult Graph<T>::dijkstra(const Node<T>& source,
                                        const Node<T>& target) const {
  DijkstraResult result;
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
  // n denotes the number of vertices in graph
  // unused
  // auto n = cachedAdjMatrix->size();

  // setting all the distances initially to INF_DOUBLE
  std::unordered_map<shared<const Node<T>>, double, nodeHash<T>> dist;

  for (const auto& node : nodeSet) {
    dist[node] = INF_DOUBLE;
  }

  // creating a min heap using priority queue
  // first element of pair contains the distance
  // second element of pair contains the vertex
  std::priority_queue<std::pair<double, shared<const Node<T>>>,
                      std::vector<std::pair<double, shared<const Node<T>>>>,
                      std::greater<std::pair<double, shared<const Node<T>>>>>
      pq;

  // pushing the source vertex 's' with 0 distance in min heap
  pq.push(std::make_pair(0.0, *source_node_it));

  // marking the distance of source as 0
  dist[*source_node_it] = 0;

  std::unordered_map<std::string, std::string> parent;
  parent[source.getUserId()] = "";

  while (!pq.empty()) {
    // second element of pair denotes the node / vertex
    shared<const Node<T>> currentNode = pq.top().second;
    // first element of pair denotes the distance
    double currentDist = pq.top().first;

    pq.pop();

    // for all the reachable vertex from the currently exploring vertex
    // we will try to minimize the distance
    if (cachedAdjMatrix->find(currentNode) != cachedAdjMatrix->end()) {
      for (const auto& elem : cachedAdjMatrix->at(currentNode)) {
        // minimizing distances
        if (elem.second->isWeighted().has_value() &&
            elem.second->isWeighted().value()) {
          if (elem.second->isDirected().has_value() &&
              elem.second->isDirected().value()) {
            shared<const DirectedWeightedEdge<T>> dw_edge =
                std::static_pointer_cast<const DirectedWeightedEdge<T>>(
                    elem.second);
            if (dw_edge->getWeight() < 0) {
              result.errorMessage = ERR_NEGATIVE_WEIGHTED_EDGE;
              return result;
            } else if (currentDist + dw_edge->getWeight() < dist[elem.first]) {
              dist[elem.first] = currentDist + dw_edge->getWeight();
              pq.push(std::make_pair(dist[elem.first], elem.first));
              parent[elem.first.get()->getUserId()] =
                  currentNode.get()->getUserId();
            }
          } else if (elem.second->isDirected().has_value() &&
                     !elem.second->isDirected().value()) {
            shared<const UndirectedWeightedEdge<T>> udw_edge =
                std::static_pointer_cast<const UndirectedWeightedEdge<T>>(
                    elem.second);
            if (udw_edge->getWeight() < 0) {
              result.errorMessage = ERR_NEGATIVE_WEIGHTED_EDGE;
              return result;
            } else if (currentDist + udw_edge->getWeight() < dist[elem.first]) {
              dist[elem.first] = currentDist + udw_edge->getWeight();
              pq.push(std::make_pair(dist[elem.first], elem.first));
              parent[elem.first.get()->getUserId()] =
                  currentNode.get()->getUserId();
            }
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
      }
    }
  }
  if (dist[*target_node_it] != INF_DOUBLE) {
    result.success = true;
    result.errorMessage = "";
    result.result = dist[*target_node_it];
    std::string id = target.getUserId();
    while (parent[id] != "") {
      result.path.push_back(id);
      id = parent[id];
    }
    result.path.push_back(source.getUserId());
    std::reverse(result.path.begin(), result.path.end());
    return result;
  }
  result.errorMessage = ERR_TARGET_NODE_NOT_REACHABLE;
  return result;
}

template <typename T>
const DijkstraResult Graph<T>::dijkstra_deterministic(
    const Node<T>& source, const Node<T>& target) const {
  DijkstraResult result;
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
  // n denotes the number of vertices in graph
  // unused
  // auto n = cachedAdjMatrix->size();

  // setting all the distances initially to INF_DOUBLE
  std::unordered_map<shared<const Node<T>>, double, nodeHash<T>> dist;
  std::map<std::string, shared<const Node<T>>> userIds;

  for (const auto& node : nodeSet) {
    dist[node] = INF_DOUBLE;
    userIds[node->getUserId()] = node;
  }

  std::unordered_map<shared<const Node<T>>, size_t, nodeHash<T>> stableIds;
  size_t index(0);
  for (const auto& it : userIds) stableIds[it.second] = index++;

  // creating a min heap using priority queue
  // first element of pair contains the distance
  // second element of pair contains the vertex

  struct VertexInfo {
    double distance = 0;
    size_t sumOfIds = 0;
    shared<const Node<T>> node;
  };

  struct VertexInfoGreater {
    bool operator()(const VertexInfo& a, const VertexInfo& b) const {
      if (a.distance == b.distance) return a.sumOfIds > b.sumOfIds;
      return a.distance > b.distance;
    };
  };

  std::priority_queue<VertexInfo, std::vector<VertexInfo>, VertexInfoGreater>
      pq;

  // pushing the source vertex 's' with 0 distance in min heap
  pq.push(VertexInfo{0.0, stableIds[*source_node_it], *source_node_it});

  // marking the distance of source as 0
  dist[*source_node_it] = 0;

  std::unordered_map<std::string, std::string> parent;
  parent[source.getUserId()] = "";

  while (!pq.empty()) {
    // second element of pair denotes the node / vertex
    shared<const Node<T>> currentNode = pq.top().node;
    // first element of pair denotes the distance
    double currentDist = pq.top().distance;
    auto currentNodesSum = pq.top().sumOfIds;

    pq.pop();

    // for all the reachable vertex from the currently exploring vertex
    // we will try to minimize the distance
    if (cachedAdjMatrix->find(currentNode) != cachedAdjMatrix->end()) {
      for (const auto& elem : cachedAdjMatrix->at(currentNode)) {
        // minimizing distances
        if (elem.second->isWeighted().has_value() &&
            elem.second->isWeighted().value()) {
          if (elem.second->isDirected().has_value() &&
              elem.second->isDirected().value()) {
            shared<const DirectedWeightedEdge<T>> dw_edge =
                std::static_pointer_cast<const DirectedWeightedEdge<T>>(
                    elem.second);
            if (dw_edge->getWeight() < 0) {
              result.errorMessage = ERR_NEGATIVE_WEIGHTED_EDGE;
              return result;
            } else if (currentDist + dw_edge->getWeight() < dist[elem.first]) {
              dist[elem.first] = currentDist + dw_edge->getWeight();
              pq.push(VertexInfo{dist[elem.first],
                                 currentNodesSum + stableIds[elem.first],
                                 elem.first});
              parent[elem.first.get()->getUserId()] =
                  currentNode.get()->getUserId();
            }
          } else if (elem.second->isDirected().has_value() &&
                     !elem.second->isDirected().value()) {
            shared<const UndirectedWeightedEdge<T>> udw_edge =
                std::static_pointer_cast<const UndirectedWeightedEdge<T>>(
                    elem.second);
            if (udw_edge->getWeight() < 0) {
              result.errorMessage = ERR_NEGATIVE_WEIGHTED_EDGE;
              return result;
            } else if (currentDist + udw_edge->getWeight() < dist[elem.first]) {
              dist[elem.first] = currentDist + udw_edge->getWeight();
              pq.push(VertexInfo{dist[elem.first],
                                 currentNodesSum + stableIds[elem.first],
                                 elem.first});
              parent[elem.first.get()->getUserId()] =
                  currentNode.get()->getUserId();
            }
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
      }
    }
  }
  if (dist[*target_node_it] != INF_DOUBLE) {
    result.success = true;
    result.errorMessage = "";
    result.result = dist[*target_node_it];
    std::string id = target.getUserId();
    while (parent[id] != "") {
      result.path.push_back(id);
      id = parent[id];
    }
    result.path.push_back(source.getUserId());
    std::reverse(result.path.begin(), result.path.end());
    return result;
  }
  result.errorMessage = ERR_TARGET_NODE_NOT_REACHABLE;
  return result;
}

template <typename T>
const DijkstraResult Graph<T>::dijkstra_deterministic2(
    const Node<T>& source, const Node<T>& target) const {
  DijkstraResult result;
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
  // n denotes the number of vertices in graph
  // unused
  // auto n = cachedAdjMatrix->size();

  // setting all the distances initially to INF_DOUBLE
  std::unordered_map<shared<const Node<T>>, double, nodeHash<T>> dist;
  std::map<std::string, shared<const Node<T>>> userIds;

  for (const auto& node : nodeSet) {
    dist[node] = INF_DOUBLE;
    userIds[node->getUserId()] = node;
  }

  std::unordered_map<shared<const Node<T>>, uint64_t, nodeHash<T>> stableIds;
  size_t index(0);
  for (const auto& it : userIds) stableIds[it.second] = index++;

  // creating a min heap using priority queue
  // first element of pair contains the distance
  // second element of pair contains the vertex

  struct VertexInfo {
    double distance = 0;
    std::vector<size_t> pathToVertex;
    shared<const Node<T>> node;
  };

  struct VertexInfoGreater {
    bool operator()(const VertexInfo& a, const VertexInfo& b) const {
      if (a.distance == b.distance)
        return std::lexicographical_compare(
            begin(b.pathToVertex), end(b.pathToVertex), begin(a.pathToVertex),
            end(a.pathToVertex));
      return a.distance > b.distance;
    };
  };

  auto addNode = [&](std::vector<size_t> v, const shared<const Node<T>>& node) {
    v.push_back(stableIds[node]);
    return v;
  };

  std::priority_queue<VertexInfo, std::vector<VertexInfo>, VertexInfoGreater>
      pq;

  // pushing the source vertex 's' with 0 distance in min heap
  pq.push(VertexInfo{0.0, addNode({}, *source_node_it), *source_node_it});

  // marking the distance of source as 0
  dist[*source_node_it] = 0;

  std::unordered_map<std::string, std::string> parent;
  parent[source.getUserId()] = "";

  while (!pq.empty()) {
    // second element of pair denotes the node / vertex
    shared<const Node<T>> currentNode = pq.top().node;
    // first element of pair denotes the distance
    double currentDist = pq.top().distance;
    auto currentNodesPath = pq.top().pathToVertex;

    pq.pop();

    // for all the reachable vertex from the currently exploring vertex
    // we will try to minimize the distance
    if (cachedAdjMatrix->find(currentNode) != cachedAdjMatrix->end()) {
      for (const auto& elem : cachedAdjMatrix->at(currentNode)) {
        // minimizing distances
        if (elem.second->isWeighted().has_value() &&
            elem.second->isWeighted().value()) {
          if (elem.second->isDirected().has_value() &&
              elem.second->isDirected().value()) {
            shared<const DirectedWeightedEdge<T>> dw_edge =
                std::static_pointer_cast<const DirectedWeightedEdge<T>>(
                    elem.second);
            if (dw_edge->getWeight() < 0) {
              result.errorMessage = ERR_NEGATIVE_WEIGHTED_EDGE;
              return result;
            } else if (currentDist + dw_edge->getWeight() < dist[elem.first]) {
              dist[elem.first] = currentDist + dw_edge->getWeight();
              pq.push(VertexInfo{dist[elem.first],
                                 addNode(currentNodesPath, elem.first),
                                 elem.first});
              parent[elem.first.get()->getUserId()] =
                  currentNode.get()->getUserId();
            }
          } else if (elem.second->isDirected().has_value() &&
                     !elem.second->isDirected().value()) {
            shared<const UndirectedWeightedEdge<T>> udw_edge =
                std::static_pointer_cast<const UndirectedWeightedEdge<T>>(
                    elem.second);
            if (udw_edge->getWeight() < 0) {
              result.errorMessage = ERR_NEGATIVE_WEIGHTED_EDGE;
              return result;
            } else if (currentDist + udw_edge->getWeight() < dist[elem.first]) {
              dist[elem.first] = currentDist + udw_edge->getWeight();
              pq.push(VertexInfo{dist[elem.first],
                                 addNode(currentNodesPath, elem.first),
                                 elem.first});
              parent[elem.first.get()->getUserId()] =
                  currentNode.get()->getUserId();
            }
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
      }
    }
  }
  if (dist[*target_node_it] != INF_DOUBLE) {
    result.success = true;
    result.errorMessage = "";
    result.result = dist[*target_node_it];
    std::string id = target.getUserId();
    while (parent[id] != "") {
      result.path.push_back(id);
      id = parent[id];
    }
    result.path.push_back(source.getUserId());
    std::reverse(result.path.begin(), result.path.end());
    return result;
  }
  result.errorMessage = ERR_TARGET_NODE_NOT_REACHABLE;
  return result;
}

}  // namespace CXXGraph
#endif  // __CXXGRAPH_DIJKSTRA_IMPL_H__
