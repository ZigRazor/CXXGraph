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

#ifndef CXXGRAPH_HYPERGRAPH_IMPL_HPP_
#define CXXGRAPH_HYPERGRAPH_IMPL_HPP_

#pragma once

#include <algorithm>
#include <functional>
#include <queue>
#include <stack>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

#include "CXXGraph/Hypergraph/Hypergraph_decl.h"

namespace CXXGraph {

// ============================================================================
// Private helpers
// ============================================================================

// ── findNodeInMap_ ───────────────────────────────────────────────────────────

template <typename T>
typename std::unordered_map<std::string, shared<const Node<T>>>::const_iterator
Hypergraph<T>::findNodeInMap_(const std::string& userId) const {
  return nodeMap_.find(userId);
}

// ── registerNodes_ ───────────────────────────────────────────────────────────
//
// Called by addHyperEdge after the edge has been inserted into hyperEdgeSet_.
// For each node in the hyperedge:
//   1. If not yet in nodeMap_, add it.
//   2. If it was an isolated node, remove it from isolatedNodes_.
//   3. Update incidence_: nodeId → {heId}.

template <typename T>
void Hypergraph<T>::registerNodes_(shared<const HyperEdge<T>> he) {
  const CXXGraph::id_t heId = he->getId();

  for (const auto& node : he->getNodes()) {
    const std::string& uid = node->getUserId();

    // Register in nodeMap_ if first time we see this node
    if (nodeMap_.find(uid) == nodeMap_.end()) {
      nodeMap_[uid] = node;
    }

    // If it was previously isolated, promote it
    auto isoIt = isolatedNodes_.find(node);
    if (isoIt == isolatedNodes_.end()) {
      // Not found by pointer equality — search by userId
      auto isoByUid =
          std::find_if(isolatedNodes_.begin(), isolatedNodes_.end(),
                       [&uid](const auto& n) { return n->getUserId() == uid; });
      if (isoByUid != isolatedNodes_.end()) {
        isolatedNodes_.erase(isoByUid);
      }
    } else {
      isolatedNodes_.erase(isoIt);
    }

    // Update incidence list
    incidence_[node->getId()].insert(heId);
  }
}

// ── unregisterEdgeFromIncidence_ ─────────────────────────────────────────────
//
// Remove @p he's id from every member node's incidence entry.
// Does NOT remove the node from nodeMap_ — nodes outlive individual edges.

template <typename T>
void Hypergraph<T>::unregisterEdgeFromIncidence_(const HyperEdge<T>& he) {
  const CXXGraph::id_t heId = he.getId();

  for (const auto& node : he.getNodes()) {
    auto incIt = incidence_.find(node->getId());
    if (incIt != incidence_.end()) {
      incIt->second.erase(heId);
      // If the node no longer belongs to any edge, make it isolated
      if (incIt->second.empty()) {
        incidence_.erase(incIt);
        // Re-insert into isolatedNodes_ using the pointer kept in nodeMap_
        auto mapIt = nodeMap_.find(node->getUserId());
        if (mapIt != nodeMap_.end()) {
          isolatedNodes_.insert(mapIt->second);
        }
      }
    }
  }
}

// ============================================================================
// Construction
// ============================================================================

template <typename T>
Hypergraph<T>::Hypergraph(const T_HyperEdgeSet<T>& edges) {
  for (const auto& he : edges) {
    addHyperEdge(he);
  }
}

// ============================================================================
// Structural mutations
// ============================================================================

// ── addHyperEdge ─────────────────────────────────────────────────────────────

template <typename T>
void Hypergraph<T>::addHyperEdge(shared<const HyperEdge<T>> he) {
  // Insert; if already present the unordered_set returns inserted=false
  auto [it, inserted] = hyperEdgeSet_.insert(he);
  if (!inserted) return;  // idempotent

  registerNodes_(he);
}

// ── removeHyperEdge ──────────────────────────────────────────────────────────

template <typename T>
void Hypergraph<T>::removeHyperEdge(const std::string& heUserId) {
  auto it = std::find_if(
      hyperEdgeSet_.begin(), hyperEdgeSet_.end(),
      [&heUserId](const auto& he) { return he->getUserId() == heUserId; });

  if (it == hyperEdgeSet_.end()) return;  // no-op

  // Update incidence before erasing
  unregisterEdgeFromIncidence_(**it);
  hyperEdgeSet_.erase(it);
}

// ── addNode ──────────────────────────────────────────────────────────────────

template <typename T>
void Hypergraph<T>::addNode(shared<const Node<T>> node) {
  const std::string& uid = node->getUserId();
  if (nodeMap_.find(uid) != nodeMap_.end()) return;  // already known

  nodeMap_[uid] = node;
  isolatedNodes_.insert(node);
}

// ── removeNode ───────────────────────────────────────────────────────────────
//
// Strategy:
//   1. Find the node in nodeMap_.
//   2. For every hyperedge that contains it (via incidence_):
//      a. Remove the node's entry from that edge's membership by rebuilding
//         the edge without that node.  We replace the hyperedge with a new
//         one that excludes the removed node.  (HyperEdge is immutable after
//         construction, so we must swap it out.)
//   3. Remove from incidence_, nodeMap_, isolatedNodes_.

template <typename T>
void Hypergraph<T>::removeNode(const std::string& nodeUserId) {
  auto mapIt = nodeMap_.find(nodeUserId);
  if (mapIt == nodeMap_.end()) return;  // no-op

  shared<const Node<T>> nodePtr = mapIt->second;
  const CXXGraph::id_t nodeId = nodePtr->getId();

  // Collect hyperedge ids that contain this node
  std::vector<CXXGraph::id_t> affectedHeIds;
  auto incIt = incidence_.find(nodeId);
  if (incIt != incidence_.end()) {
    affectedHeIds.assign(incIt->second.begin(), incIt->second.end());
  }

  // For each affected edge, rebuild it without the removed node
  for (const CXXGraph::id_t heId : affectedHeIds) {
    // Find the hyperedge in hyperEdgeSet_
    auto heIt =
        std::find_if(hyperEdgeSet_.begin(), hyperEdgeSet_.end(),
                     [heId](const auto& he) { return he->getId() == heId; });

    if (heIt == hyperEdgeSet_.end()) continue;

    shared<const HyperEdge<T>> oldHe = *heIt;

    // Build new node list without the removed node
    std::vector<shared<const Node<T>>> newNodes;
    newNodes.reserve(oldHe->getNodes().size());
    for (const auto& n : oldHe->getNodes()) {
      if (n->getId() != nodeId) newNodes.push_back(n);
    }

    // Remove old edge (also updates incidence for its members)
    unregisterEdgeFromIncidence_(*oldHe);
    hyperEdgeSet_.erase(heIt);

    // Re-insert the trimmed edge only if it is non-empty
    if (!newNodes.empty()) {
      // Preserve weight if applicable
      const WeightedHyperEdge<T>* whe =
          dynamic_cast<const WeightedHyperEdge<T>*>(oldHe.get());

      shared<const HyperEdge<T>> newHe;
      if (whe) {
        newHe = std::make_shared<const WeightedHyperEdge<T>>(
            oldHe->getUserId(), std::move(newNodes), whe->getWeight().value());
      } else {
        newHe = std::make_shared<const HyperEdge<T>>(oldHe->getUserId(),
                                                     std::move(newNodes));
      }

      auto [newIt, ins] = hyperEdgeSet_.insert(newHe);
      if (ins) {
        // Register remaining members (skipping the removed node which is gone)
        registerNodes_(newHe);
      }
    }
  }

  // Remove the node itself from all data structures
  incidence_.erase(nodeId);
  isolatedNodes_.erase(nodePtr);
  // Also attempt userId-based removal from isolatedNodes_ (pointer may differ)
  auto isoByUid = std::find_if(
      isolatedNodes_.begin(), isolatedNodes_.end(),
      [&nodeUserId](const auto& n) { return n->getUserId() == nodeUserId; });
  if (isoByUid != isolatedNodes_.end()) {
    isolatedNodes_.erase(isoByUid);
  }

  nodeMap_.erase(mapIt);
}

// ============================================================================
// Read-only accessors
// ============================================================================

template <typename T>
const T_HyperEdgeSet<T>& Hypergraph<T>::getHyperEdgeSet() const {
  return hyperEdgeSet_;
}

template <typename T>
T_NodeSet<T> Hypergraph<T>::getNodeSet() const {
  T_NodeSet<T> result;
  for (const auto& [uid, node] : nodeMap_) {
    result.insert(node);
  }
  return result;
}

template <typename T>
std::optional<shared<const HyperEdge<T>>> Hypergraph<T>::getHyperEdge(
    const std::string& heUserId) const {
  auto it = std::find_if(
      hyperEdgeSet_.begin(), hyperEdgeSet_.end(),
      [&heUserId](const auto& he) { return he->getUserId() == heUserId; });

  if (it != hyperEdgeSet_.end()) return *it;
  return std::nullopt;
}

template <typename T>
std::optional<shared<const Node<T>>> Hypergraph<T>::getNode(
    const std::string& nodeUserId) const {
  auto it = findNodeInMap_(nodeUserId);
  if (it != nodeMap_.end()) return it->second;
  return std::nullopt;
}

template <typename T>
std::vector<shared<const HyperEdge<T>>> Hypergraph<T>::getHyperEdgesOfNode(
    const std::string& nodeUserId) const {
  std::vector<shared<const HyperEdge<T>>> result;

  auto mapIt = findNodeInMap_(nodeUserId);
  if (mapIt == nodeMap_.end()) return result;

  auto incIt = incidence_.find(mapIt->second->getId());
  if (incIt == incidence_.end()) return result;

  for (const CXXGraph::id_t heId : incIt->second) {
    for (const auto& he : hyperEdgeSet_) {
      if (he->getId() == heId) {
        result.push_back(he);
        break;
      }
    }
  }

  return result;
}

template <typename T>
T_NodeSet<T> Hypergraph<T>::getNeighbors(const std::string& nodeUserId) const {
  T_NodeSet<T> neighbors;

  auto mapIt = findNodeInMap_(nodeUserId);
  if (mapIt == nodeMap_.end()) return neighbors;

  const CXXGraph::id_t queryNodeId = mapIt->second->getId();

  auto incIt = incidence_.find(queryNodeId);
  if (incIt == incidence_.end()) return neighbors;

  for (const CXXGraph::id_t heId : incIt->second) {
    for (const auto& he : hyperEdgeSet_) {
      if (he->getId() == heId) {
        for (const auto& n : he->getNodes()) {
          if (n->getId() != queryNodeId) {
            neighbors.insert(n);
          }
        }
        break;
      }
    }
  }

  return neighbors;
}

// ============================================================================
// Cardinality
// ============================================================================

template <typename T>
std::size_t Hypergraph<T>::nodeCount() const {
  return nodeMap_.size();
}

template <typename T>
std::size_t Hypergraph<T>::hyperEdgeCount() const {
  return hyperEdgeSet_.size();
}

// ============================================================================
// Structural properties
// ============================================================================

template <typename T>
std::size_t Hypergraph<T>::rank() const {
  std::size_t r = 0;
  for (const auto& he : hyperEdgeSet_) {
    r = std::max(r, he->size());
  }
  return r;
}

template <typename T>
bool Hypergraph<T>::isUniform() const {
  if (hyperEdgeSet_.empty()) return true;  // vacuously uniform

  const std::size_t firstSize = (*hyperEdgeSet_.begin())->size();
  for (const auto& he : hyperEdgeSet_) {
    if (he->size() != firstSize) return false;
  }
  return true;
}

// ============================================================================
// Dual hypergraph
// ============================================================================
//
// H* = (E, V):
//   Nodes of H*  ↔  hyperedges of H   (node userId = original edge userId)
//   Edges of H*  ↔  nodes of H        (for each original node v, a hyperedge
//                                       whose members are all dual nodes whose
//                                       original edge contained v)

template <typename T>
Hypergraph<std::string> Hypergraph<T>::dual() const {
  Hypergraph<std::string> dualGraph;

  // Build dual nodes: one per original hyperedge
  // dual node userId = original edge userId, data = original edge userId
  std::unordered_map<CXXGraph::id_t, shared<const Node<std::string>>>
      edgeIdToDualNode;

  for (const auto& he : hyperEdgeSet_) {
    auto dualNode = std::make_shared<const Node<std::string>>(he->getUserId(),
                                                              he->getUserId());
    edgeIdToDualNode[he->getId()] = dualNode;
  }

  // Build dual edges: one per original node
  // For original node v, the dual hyperedge contains all dual nodes
  // (original edges) whose original edge contained v.
  // std::size_t dualEdgeCounter = 0;

  for (const auto& [uid, node] : nodeMap_) {
    auto incIt = incidence_.find(node->getId());
    if (incIt == incidence_.end()) {
      // Original node is isolated → it produces an empty dual edge (skip)
      // Alternatively add an isolated dual node if the user wants completeness.
      // Following the strict mathematical definition we skip it.
      continue;
    }

    std::vector<shared<const Node<std::string>>> dualMembers;
    dualMembers.reserve(incIt->second.size());

    for (const CXXGraph::id_t heId : incIt->second) {
      auto it = edgeIdToDualNode.find(heId);
      if (it != edgeIdToDualNode.end()) {
        dualMembers.push_back(it->second);
      }
    }

    if (dualMembers.empty()) continue;

    // Use original node userId as the dual edge userId for traceability
    auto dualEdge = std::make_shared<const HyperEdge<std::string>>(
        uid, std::move(dualMembers));
    dualGraph.addHyperEdge(dualEdge);

    // ++dualEdgeCounter;
  }

  return dualGraph;
}

// ============================================================================
// 2-section projection
// ============================================================================

template <typename T>
std::unordered_map<std::string, std::unordered_set<std::string>>
Hypergraph<T>::toTwoSection() const {
  std::unordered_map<std::string, std::unordered_set<std::string>> adj;

  // Ensure every node appears as a key (even isolated ones)
  for (const auto& [uid, node] : nodeMap_) {
    adj[uid];  // value-initialise to empty set
  }

  // For each hyperedge, connect every pair of members
  for (const auto& he : hyperEdgeSet_) {
    const auto& nodes = he->getNodes();
    for (std::size_t i = 0; i < nodes.size(); ++i) {
      for (std::size_t j = i + 1; j < nodes.size(); ++j) {
        const std::string& uidI = nodes[i]->getUserId();
        const std::string& uidJ = nodes[j]->getUserId();
        adj[uidI].insert(uidJ);
        adj[uidJ].insert(uidI);
      }
    }
  }

  return adj;
}

// ============================================================================
// Incidence matrix
// ============================================================================
//
// B  is a |V| × |E| binary matrix.
// B[i][j] = 1  iff  nodeVec[i] ∈ edgeVec[j]
//
// Row order   = iteration order of getNodeSet()   (unspecified but stable)
// Column order = iteration order of hyperEdgeSet_ (unspecified but stable)

template <typename T>
std::vector<std::vector<int>> Hypergraph<T>::incidenceMatrix() const {
  if (nodeMap_.empty()) return {};

  // Materialise stable orderings
  T_NodeSet<T> nodeSetTmp = getNodeSet();
  std::vector<shared<const Node<T>>> nodeVec(nodeSetTmp.begin(),
                                             nodeSetTmp.end());
  std::vector<shared<const HyperEdge<T>>> edgeVec(hyperEdgeSet_.begin(),
                                                  hyperEdgeSet_.end());

  const std::size_t V = nodeVec.size();
  const std::size_t E = edgeVec.size();

  std::vector<std::vector<int>> B(V, std::vector<int>(E, 0));

  for (std::size_t j = 0; j < E; ++j) {
    for (std::size_t i = 0; i < V; ++i) {
      if (edgeVec[j]->contains(nodeVec[i])) {
        B[i][j] = 1;
      }
    }
  }

  return B;
}

// ============================================================================
// Traversal — BFS
// ============================================================================
//
// Expansion rule:
//   From a node  → visit all hyperedges it belongs to (incidence_)
//   From an edge → enqueue all unvisited member nodes
//
// The standard BFS loop over nodes is insufficient here because a single
// hyperedge can "jump" a node to many others at once.  We track visited
// nodes AND visited edges to avoid redundant expansion.

template <typename T>
std::vector<Node<T>> Hypergraph<T>::breadth_first_search(
    const Node<T>& start) const {
  std::vector<Node<T>> result;

  // Locate start node
  auto mapIt = findNodeInMap_(start.getUserId());
  if (mapIt == nodeMap_.end()) return result;

  std::unordered_set<CXXGraph::id_t> visitedNodes;
  std::unordered_set<CXXGraph::id_t> visitedEdges;
  std::queue<shared<const Node<T>>> queue;

  shared<const Node<T>> startPtr = mapIt->second;
  queue.push(startPtr);
  visitedNodes.insert(startPtr->getId());

  while (!queue.empty()) {
    shared<const Node<T>> current = queue.front();
    queue.pop();

    result.push_back(*current);

    // Expand through every hyperedge containing current
    auto incIt = incidence_.find(current->getId());
    if (incIt == incidence_.end()) continue;

    for (const CXXGraph::id_t heId : incIt->second) {
      if (visitedEdges.count(heId)) continue;
      visitedEdges.insert(heId);

      // Find the hyperedge and enqueue all unvisited members
      for (const auto& he : hyperEdgeSet_) {
        if (he->getId() != heId) continue;

        for (const auto& n : he->getNodes()) {
          if (!visitedNodes.count(n->getId())) {
            visitedNodes.insert(n->getId());
            queue.push(n);
          }
        }
        break;
      }
    }
  }

  return result;
}

// ============================================================================
// Traversal — DFS
// ============================================================================
//
// Same expansion rule as BFS; uses an explicit stack instead of a queue.

template <typename T>
std::vector<Node<T>> Hypergraph<T>::depth_first_search(
    const Node<T>& start) const {
  std::vector<Node<T>> result;

  auto mapIt = findNodeInMap_(start.getUserId());
  if (mapIt == nodeMap_.end()) return result;

  std::unordered_set<CXXGraph::id_t> visitedNodes;
  std::unordered_set<CXXGraph::id_t> visitedEdges;
  std::stack<shared<const Node<T>>> stack;

  shared<const Node<T>> startPtr = mapIt->second;
  stack.push(startPtr);
  visitedNodes.insert(startPtr->getId());

  while (!stack.empty()) {
    shared<const Node<T>> current = stack.top();
    stack.pop();

    result.push_back(*current);

    auto incIt = incidence_.find(current->getId());
    if (incIt == incidence_.end()) continue;

    for (const CXXGraph::id_t heId : incIt->second) {
      if (visitedEdges.count(heId)) continue;
      visitedEdges.insert(heId);

      for (const auto& he : hyperEdgeSet_) {
        if (he->getId() != heId) continue;

        // Push in reverse so that the first member is processed first
        const auto& members = he->getNodes();
        for (auto it = members.rbegin(); it != members.rend(); ++it) {
          if (!visitedNodes.count((*it)->getId())) {
            visitedNodes.insert((*it)->getId());
            stack.push(*it);
          }
        }
        break;
      }
    }
  }

  return result;
}

// ============================================================================
// Connected components — union-find
// ============================================================================
//
// Algorithm:
//   1. Initialise each node as its own root.
//   2. For each hyperedge, union the first node with every other member.
//   3. Group nodes by root → each group is one component.

template <typename T>
std::vector<std::vector<Node<T>>> Hypergraph<T>::connectedComponents() const {
  if (nodeMap_.empty()) return {};

  // ── Union-Find with path compression ──────────────────────────────────────
  std::unordered_map<CXXGraph::id_t, CXXGraph::id_t> parent;

  // Initialise: every node is its own parent
  for (const auto& [uid, node] : nodeMap_) {
    parent[node->getId()] = node->getId();
  }

  // Path-compressed find
  std::function<CXXGraph::id_t(CXXGraph::id_t)> find =
      [&](CXXGraph::id_t x) -> CXXGraph::id_t {
    if (parent.at(x) != x) parent[x] = find(parent.at(x));
    return parent.at(x);
  };

  // Union by id (no rank — simple but correct)
  auto unite = [&](CXXGraph::id_t a, CXXGraph::id_t b) {
    a = find(a);
    b = find(b);
    if (a != b) parent[a] = b;
  };

  // For each hyperedge, union all member nodes together
  for (const auto& he : hyperEdgeSet_) {
    const auto& members = he->getNodes();
    if (members.size() < 2) continue;

    const CXXGraph::id_t first = members[0]->getId();
    for (std::size_t i = 1; i < members.size(); ++i) {
      unite(first, members[i]->getId());
    }
  }

  // ── Group nodes by root ────────────────────────────────────────────────────
  // We need nodeId → Node<T> for the final collection step
  std::unordered_map<CXXGraph::id_t, shared<const Node<T>>> nodeById;
  for (const auto& [uid, node] : nodeMap_) {
    nodeById[node->getId()] = node;
  }

  std::unordered_map<CXXGraph::id_t, std::vector<Node<T>>> componentMap;
  for (const auto& [uid, node] : nodeMap_) {
    const CXXGraph::id_t root = find(node->getId());
    componentMap[root].push_back(*node);
  }

  // Convert map to vector
  std::vector<std::vector<Node<T>>> result;
  result.reserve(componentMap.size());
  for (auto& [root, comp] : componentMap) {
    result.push_back(std::move(comp));
  }

  return result;
}

// ============================================================================
// Stream operator
// ============================================================================

template <typename T>
std::ostream& operator<<(std::ostream& os, const Hypergraph<T>& hg) {
  os << "Hypergraph {\n";
  os << "  nodes (" << hg.nodeCount() << "): [";
  bool first = true;
  for (const auto& [uid, node] : hg.nodeMap_) {
    if (!first) os << ", ";
    os << uid;
    first = false;
  }
  os << "]\n";
  os << "  edges (" << hg.hyperEdgeCount() << "):\n";
  for (const auto& he : hg.hyperEdgeSet_) {
    os << "    " << *he << "\n";
  }
  os << "}";
  return os;
}

}  // namespace CXXGraph

#endif  // CXXGRAPH_HYPERGRAPH_IMPL_HPP_
