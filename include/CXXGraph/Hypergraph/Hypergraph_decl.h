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

#ifndef CXXGRAPH_HYPERGRAPH_DECL_H_
#define CXXGRAPH_HYPERGRAPH_DECL_H_

#pragma once

#include <algorithm>
#include <functional>
#include <memory>
#include <optional>
#include <ostream>
#include <queue>
#include <stack>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

#include "CXXGraph/Edge/HyperEdge.h"
#include "CXXGraph/Node/Node.h"
#include "CXXGraph/Utility/Typedef.hpp"

namespace CXXGraph {

// Smart pointer aliases
template <typename T>
using shared = std::shared_ptr<T>;

template <typename T>
class Hypergraph;

template <typename T>
std::ostream& operator<<(std::ostream& os, const Hypergraph<T>& hg);

// ═══════════════════════════════════════════════════════════════════════════
// Hypergraph<T>
//
// A generalisation of Graph<T> in which every edge (hyperedge) connects
// an arbitrary subset of vertices instead of exactly two.
//
// Formally: H = (V, E) where each e ∈ E is a subset of V of any size ≥ 1.
//
// Internal representation
// ───────────────────────
//   hyperEdgeSet_  — primary storage of all HyperEdge<T> shared-pointers.
//   nodeMap_       — userId → shared<const Node<T>>  (O(1) lookup by string).
//   isolatedNodes_ — nodes not belonging to any hyperedge (mirrors Graph<T>'s
//                    isolatedNodesSet).
//   incidence_     — nodeId → set of hyperedge ids that contain it.
//                    Updated incrementally on add/remove; never rebuilt from
//                    scratch (mirrors Graph<T>'s cached adjacency lists).
//
// Note: Not thread-safe.  Wrap in ThreadSafeGraph-style subclass if needed.
// ═══════════════════════════════════════════════════════════════════════════

template <typename T>
class Hypergraph {
 public:
  // ── construction ──────────────────────────────────────────────────────────

  /** @brief Create an empty hypergraph. */
  Hypergraph() = default;

  /**
   * @brief Construct from a pre-built set of hyperedges.
   *        All nodes referenced by any hyperedge are registered automatically.
   */
  explicit Hypergraph(const T_HyperEdgeSet<T>& edges);

  virtual ~Hypergraph() = default;

  // Disable copy (same rationale as Graph<T> — shared_ptr ownership)
  Hypergraph(const Hypergraph&)            = default;
  Hypergraph& operator=(const Hypergraph&) = default;
  Hypergraph(Hypergraph&&)                 = default;
  Hypergraph& operator=(Hypergraph&&)      = default;

  // ── structural mutations ──────────────────────────────────────────────────

  /**
   * @brief Add a hyperedge to the graph.
   *        All nodes it references are registered automatically.
   *        If the hyperedge is already present (same getId()), this is a no-op.
   * Note: Not thread-safe.
   */
  virtual void addHyperEdge(shared<const HyperEdge<T>> he);

  /**
   * @brief Remove the hyperedge whose getUserId() == @p heUserId.
   *        The incidence list is updated; nodes that still belong to other
   *        edges remain; nodes that only belonged to this edge become isolated.
   *        No-op if the edge is not present.
   * Note: Not thread-safe.
   */
  virtual void removeHyperEdge(const std::string& heUserId);

  /**
   * @brief Add a node that belongs to no hyperedge (isolated node).
   *        If a node with the same userId already exists (whether isolated or
   *        as a member of an edge), this is a no-op.
   * Note: Not thread-safe.
   */
  virtual void addNode(shared<const Node<T>> node);

  /**
   * @brief Remove a node by userId.
   *        The node is removed from the node map, from isolatedNodes_ (if
   *        applicable), and from every hyperedge that referenced it.
   *        No-op if the node is not present.
   * Note: Not thread-safe.
   */
  virtual void removeNode(const std::string& nodeUserId);

  // ── read-only accessors ───────────────────────────────────────────────────

  /** @return The primary set of all hyperedges. */
  virtual const T_HyperEdgeSet<T>& getHyperEdgeSet() const;

  /**
   * @return The set of all nodes (both edge-members and isolated).
   *         Constructed on demand from nodeMap_ + isolatedNodes_.
   */
  virtual T_NodeSet<T> getNodeSet() const;

  /**
   * @brief Look up a hyperedge by userId.
   * @return An optional containing the shared-pointer if found, nullopt otherwise.
   */
  virtual std::optional<shared<const HyperEdge<T>>>
      getHyperEdge(const std::string& heUserId) const;

  /**
   * @brief Look up a node by userId.
   * @return An optional containing the shared-pointer if found, nullopt otherwise.
   */
  virtual std::optional<shared<const Node<T>>>
      getNode(const std::string& nodeUserId) const;

  /**
   * @brief Return all hyperedges that contain the given node.
   * @param nodeUserId  The userId of the node to query.
   * @return Vector of shared-pointers (empty if node is unknown or isolated).
   */
  virtual std::vector<shared<const HyperEdge<T>>>
      getHyperEdgesOfNode(const std::string& nodeUserId) const;

  /**
   * @brief The "s-walk" neighborhood of a node: all other nodes that share
   *        at least one hyperedge with it.
   * @param nodeUserId  The userId of the query node.
   * @return Set of neighbor node shared-pointers (never contains the node itself).
   */
  virtual T_NodeSet<T> getNeighbors(const std::string& nodeUserId) const;

  // ── cardinality ───────────────────────────────────────────────────────────

  /** @return Total number of nodes (both edge-members and isolated). */
  virtual std::size_t nodeCount() const;

  /** @return Total number of hyperedges. */
  virtual std::size_t hyperEdgeCount() const;

  // ── structural properties ─────────────────────────────────────────────────

  /**
   * @brief The rank of the hypergraph: the maximum cardinality over all edges.
   * @return 0 for an empty hypergraph.
   */
  virtual std::size_t rank() const;

  /**
   * @brief Test uniformity: every edge has the same cardinality.
   *        A hypergraph with no edges is vacuously uniform.
   *        A 2-uniform hypergraph is equivalent to an ordinary graph.
   */
  virtual bool isUniform() const;

  // ── derived structures ────────────────────────────────────────────────────

  /**
   * @brief Compute the dual hypergraph H* = (E, V).
   *
   *        Duality swaps the roles of nodes and hyperedges:
   *          - Each original hyperedge becomes a Node<std::string> in H*
   *            (node userId = original hyperedge userId).
   *          - For each original node v, a hyperedge is created in H* whose
   *            members are all dual nodes (original edges) that contained v.
   *
   *        The return type is Hypergraph<std::string> because the dual's nodes
   *        are labelled by the original edge ids (strings), regardless of T.
   *
   * @return The dual hypergraph.
   */
  virtual Hypergraph<std::string> dual() const;

  /**
   * @brief Project to a 2-section (ordinary graph adjacency list).
   *
   *        Two nodes are adjacent in the 2-section iff they co-appear in at
   *        least one hyperedge.  This is the standard way to reduce a
   *        hypergraph problem to a graph problem for use with CXXGraph's
   *        existing algorithms.
   *
   * @return Adjacency list: userId → set of neighbor userIds.
   *         Every node (including isolated ones) appears as a key.
   */
  virtual std::unordered_map<std::string, std::unordered_set<std::string>>
      toTwoSection() const;

  // ── matrix representations ────────────────────────────────────────────────

  /**
   * @brief Compute the |V| × |E| binary incidence matrix B.
   *
   *        B[i][j] = 1  iff  node i belongs to hyperedge j.
   *        B[i][j] = 0  otherwise.
   *
   *        Row ordering follows getNodeSet() iteration order.
   *        Column ordering follows getHyperEdgeSet() iteration order.
   *        Both are stable within a single call but may differ across calls
   *        if the graph is mutated between calls (unordered containers).
   *
   * @return Dense row-major matrix as vector<vector<int>>.
   *         Returns an empty vector for an empty hypergraph.
   */
  virtual std::vector<std::vector<int>> incidenceMatrix() const;

  // ── traversal ─────────────────────────────────────────────────────────────

  /**
   * @brief Breadth-first search on the hypergraph.
   *
   *        Expansion rule: from a node, visit every hyperedge it belongs to,
   *        then enqueue all unvisited nodes in those hyperedges.
   *        This generalises BFS on ordinary graphs (where each "hyperedge"
   *        is simply a pair).
   *
   * @param start  The node from which traversal begins.
   * @return       Nodes visited in BFS order; includes @p start.
   *               Returns an empty vector if @p start is not in the graph.
   * Note: Not thread-safe.
   */
  virtual std::vector<Node<T>> breadth_first_search(const Node<T>& start) const;

  /**
   * @brief Depth-first search on the hypergraph.
   *
   *        Same expansion rule as BFS but explored depth-first (LIFO stack).
   *
   * @param start  The node from which traversal begins.
   * @return       Nodes visited in DFS order; includes @p start.
   *               Returns an empty vector if @p start is not in the graph.
   * Note: Not thread-safe.
   */
  virtual std::vector<Node<T>> depth_first_search(const Node<T>& start) const;

  /**
   * @brief Compute all connected components using union-find.
   *
   *        Two nodes are in the same component iff there exists a sequence of
   *        hyperedges connecting them (hypergraph path).  Isolated nodes each
   *        form their own singleton component.
   *
   * @return Vector of components; each component is a vector of Node<T>.
   *         Order of components and nodes within components is unspecified.
   *         Returns an empty vector for an empty hypergraph.
   * Note: Not thread-safe.
   */
  virtual std::vector<std::vector<Node<T>>> connectedComponents() const;

  // ── stream operator ───────────────────────────────────────────────────────

  template <typename U>
  friend std::ostream& operator<<(std::ostream& os, const Hypergraph<U>& hg);

 private:
  // ── private state ─────────────────────────────────────────────────────────

  /** Primary store of all hyperedges. */
  T_HyperEdgeSet<T> hyperEdgeSet_;

  /** Nodes that belong to no hyperedge. */
  T_NodeSet<T> isolatedNodes_;

  /**
   * Fast lookup: userId (string) → shared<const Node<T>>.
   * Contains every node known to the graph, whether isolated or edge-member.
   */
  std::unordered_map<std::string, shared<const Node<T>>> nodeMap_;

  /**
   * Incidence list: node numeric id → set of hyperedge numeric ids.
   * Updated incrementally by addHyperEdge / removeHyperEdge / removeNode.
   */
  std::unordered_map<CXXGraph::id_t,
                     std::unordered_set<CXXGraph::id_t>> incidence_;

  // ── private helpers ───────────────────────────────────────────────────────

  /**
   * @brief Register all nodes of @p he into nodeMap_, promote them out of
   *        isolatedNodes_, and update incidence_.
   *        Called by addHyperEdge.
   */
  void registerNodes_(shared<const HyperEdge<T>> he);

  /**
   * @brief Remove @p he's id from every member node's incidence entry.
   *        Called by removeHyperEdge.
   */
  void unregisterEdgeFromIncidence_(const HyperEdge<T>& he);

  /**
   * @brief Helper: look up a node by userId in nodeMap_.
   * @return Iterator into nodeMap_, or nodeMap_.end() if not found.
   */
  typename std::unordered_map<std::string,
                              shared<const Node<T>>>::const_iterator
      findNodeInMap_(const std::string& userId) const;
};

}  // namespace CXXGraph

#endif  // CXXGRAPH_HYPERGRAPH_DECL_H_
