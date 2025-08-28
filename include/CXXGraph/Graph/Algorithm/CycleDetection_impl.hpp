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

#ifndef __CXXGRAPH_CYCLEDETECTION_IMPL_H__
#define __CXXGRAPH_CYCLEDETECTION_IMPL_H__

#pragma once

#include <algorithm>

#include "CXXGraph/Graph/Graph_decl.h"

namespace CXXGraph {
template <typename T>
bool Graph<T>::isCyclicDirectedGraphDFS() const {
  if (!isDirectedGraph()) {
    return false;
  }
  enum nodeStates : uint8_t { not_visited, in_stack, visited };
  auto nodeSet = Graph<T>::getNodeSet();

  /* State of the node.
   *
   * It is a vector of "nodeStates" which represents the state node is in.
   * It can take only 3 values: "not_visited", "in_stack", and "visited".
   *
   * Initially, all nodes are in "not_visited" state.
   */
  std::unordered_map<CXXGraph::id_t, nodeStates> state;
  for (const auto &node : nodeSet) {
    state[node->getId()] = not_visited;
  }

  // Start visiting each node.
  for (const auto &node : nodeSet) {
    // If a node is not visited, only then check for presence of cycle.
    // There is no need to check for presence of cycle for a visited
    // node as it has already been checked for presence of cycle.
    if (state[node->getId()] == not_visited) {
      // Check for cycle.
      std::function<bool(const std::shared_ptr<AdjacencyMatrix<T>>,
                         std::unordered_map<CXXGraph::id_t, nodeStates> &,
                         shared<const Node<T>>)>
          isCyclicDFSHelper;
      isCyclicDFSHelper =
          [&isCyclicDFSHelper](
              const std::shared_ptr<AdjacencyMatrix<T>> adjMatrix,
              std::unordered_map<CXXGraph::id_t, nodeStates> &states,
              shared<const Node<T>> node) {
            // Add node "in_stack" state.
            states[node->getId()] = in_stack;

            // If the node has children, then recursively visit all
            // children of the node.
            auto const it = adjMatrix->find(node);
            if (it != adjMatrix->end()) {
              for (const auto &child : it->second) {
                // If state of child node is "not_visited", evaluate that
                // child for presence of cycle.
                auto state_of_child = states.at((std::get<0>(child))->getId());
                if (state_of_child == not_visited) {
                  if (isCyclicDFSHelper(adjMatrix, states,
                                        std::get<0>(child))) {
                    return true;
                  }
                } else if (state_of_child == in_stack) {
                  // If child node was "in_stack", then that means that
                  // there is a cycle in the graph. Return true for
                  // presence of the cycle.
                  return true;
                }
              }
            }

            // Current node has been evaluated for the presence of cycle
            // and had no cycle. Mark current node as "visited".
            states[node->getId()] = visited;
            // Return that current node didn't result in any cycles.
            return false;
          };
      if (isCyclicDFSHelper(cachedAdjMatrixOut, state, node)) {
        return true;
      }
    }
  }

  // All nodes have been safely traversed, that means there is no cycle in
  // the graph. Return false.
  return false;
}

template <typename T>
bool Graph<T>::containsCycle(const T_EdgeSet<T> *edgeSet) const {
  auto edgeSet_ptr = make_shared<const T_EdgeSet<T>>(*edgeSet);
  auto subset = make_shared<std::unordered_map<CXXGraph::id_t, Subset>>();
  // initialize the subset parent and rank values
  for (const auto &edge : *edgeSet_ptr) {
    auto &[first, second] = edge->getNodePair();
    std::vector<CXXGraph::id_t> nodeId(2);
    nodeId.push_back(first->getId());
    nodeId.push_back(second->getId());
    for (const auto &id : nodeId) {
      auto nodeExists = [id](const auto &it) {
        return (id == (it.second).parent);
      };

      if (std::find_if((*subset).begin(), (*subset).end(), nodeExists) ==
          (*subset).end()) {
        Subset set;
        set.parent = id;
        set.rank = 0;
        (*subset)[id] = set;
      }
    }
  }
  return Graph<T>::containsCycle(edgeSet_ptr, subset);
}

template <typename T>
bool Graph<T>::containsCycle(shared<const T_EdgeSet<T>> edgeSet) const {
  auto subset = make_shared<std::unordered_map<CXXGraph::id_t, Subset>>();
  // initialize the subset parent and rank values
  for (const auto &edge : *edgeSet) {
    auto &[first, second] = edge->getNodePair();
    std::vector<CXXGraph::id_t> nodeId(2);
    nodeId.push_back(first->getId());
    nodeId.push_back(second->getId());
    for (const auto &id : nodeId) {
      auto nodeExists = [id](const auto &it) {
        return (id == (it.second).parent);
      };

      if (std::find_if((*subset).begin(), (*subset).end(), nodeExists) ==
          (*subset).end()) {
        Subset set;
        set.parent = id;
        set.rank = 0;
        (*subset)[id] = set;
      }
    }
  }
  return Graph<T>::containsCycle(edgeSet, subset);
}

template <typename T>
bool Graph<T>::containsCycle(
    shared<const T_EdgeSet<T>> edgeSet,
    shared<std::unordered_map<CXXGraph::id_t, Subset>> subset) const {
  for (const auto &edge : *edgeSet) {
    auto &[first, second] = edge->getNodePair();
    auto set1 = Graph<T>::setFind(subset, first->getId());
    auto set2 = Graph<T>::setFind(subset, second->getId());
    if (set1 == set2) return true;
    Graph<T>::setUnion(subset, set1, set2);
  }
  return false;
}

template <typename T>
bool Graph<T>::isCyclicDirectedGraphBFS() const {
  if (!isDirectedGraph()) {
    return false;
  }
  auto nodeSet = Graph<T>::getNodeSet();

  std::unordered_map<CXXGraph::id_t, unsigned int> indegree;
  for (const auto &node : nodeSet) {
    indegree[node->getId()] = 0;
  }
  // Calculate the indegree i.e. the number of incident edges to the node.
  for (auto const &list : (*cachedAdjMatrixOut)) {
    auto children = list.second;
    for (auto const &child : children) {
      indegree[std::get<0>(child)->getId()]++;
    }
  }

  std::queue<shared<const Node<T>>> can_be_solved;
  for (const auto &node : nodeSet) {
    // If a node doesn't have any input edges, then that node will
    // definately not result in a cycle and can be visited safely.
    if (!indegree[node->getId()]) {
      can_be_solved.emplace(node);
    }
  }

  // Vertices that need to be traversed.
  auto remain = nodeSet.size();
  // While there are safe nodes that we can visit.
  while (!can_be_solved.empty()) {
    auto solved = can_be_solved.front();
    // Visit the node.
    can_be_solved.pop();
    // Decrease number of nodes that need to be traversed.
    remain--;

    // Visit all the children of the visited node.
    auto it = cachedAdjMatrixOut->find(solved);
    if (it != cachedAdjMatrixOut->end()) {
      for (const auto &child : it->second) {
        // Check if we can visited the node safely.
        if (--indegree[std::get<0>(child)->getId()] == 0) {
          // if node can be visited safely, then add that node to
          // the visit queue.
          can_be_solved.emplace(std::get<0>(child));
        }
      }
    }
  }

  // If there are still nodes that we can't visit, then it means that
  // there is a cycle and return true, else return false.
  return !(remain == 0);
}
}  // namespace CXXGraph
#endif  // __CXXGRAPH_CYCLEDETECTION_IMPL_H__
