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

#ifndef CXXGRAPH_HYPEREDGE_DECL_H_
#define CXXGRAPH_HYPEREDGE_DECL_H_

#pragma once

#include <initializer_list>
#include <memory>
#include <optional>
#include <ostream>
#include <string>
#include <unordered_set>
#include <vector>

#include "CXXGraph/Node/Node.h"
#include "CXXGraph/Utility/id_t.hpp"

namespace CXXGraph {

// Smart pointer aliases (mirrors the rest of the codebase)
template <typename T>
using shared = std::shared_ptr<T>;

// ── Forward declarations ─────────────────────────────────────────────────────

template <typename T>
class HyperEdge;

template <typename T>
class WeightedHyperEdge;

template <typename T>
std::ostream& operator<<(std::ostream& o, const HyperEdge<T>& he);

// ── nodeHash (re-used from Typedef.hpp) ──────────────────────────────────────
// Declared here so HyperEdge_decl.h is self-contained even when included
// before Graph_decl.h.  The definition in Typedef.hpp still takes precedence
// because both expand to identical code; the compiler merges them via ODR.

template <typename T>
struct nodeHash;  // defined in Typedef.hpp — included transitively via Node.h

// ── T_HyperEdgeSet forward typedefs ──────────────────────────────────────────

template <typename T>
struct hyperEdgeHash {
  std::size_t operator()(const shared<const HyperEdge<T>>& he) const noexcept {
    return std::hash<CXXGraph::id_t>{}(he->getId());
  }
};

template <typename T>
using T_HyperEdgeSet =
    std::unordered_set<shared<const HyperEdge<T>>, hyperEdgeHash<T>>;

// ═══════════════════════════════════════════════════════════════════════════
// HyperEdge<T>
//
// An n-ary edge that connects an arbitrary, ordered collection of nodes.
// Unlike Edge<T> — which is locked to exactly two nodes — a HyperEdge<T>
// holds a std::vector<shared<const Node<T>>> of any size ≥ 1.
//
// Design note: HyperEdge<T> does NOT inherit from Edge<T>.  Edge<T> owns a
// std::pair<…>, making its interface contractually binary.  Inheriting would
// be a Liskov violation.  HyperEdge<T> reuses Node<T> and id_t but stands
// as an independent type.
// ═══════════════════════════════════════════════════════════════════════════

template <typename T>
class HyperEdge {
 public:
  // ── construction ──────────────────────────────────────────────────────────

  /**
   * @brief Construct from an explicit vector of node shared-pointers.
   * @param userId  User-supplied string identifier (hashed to produce getId()).
   * @param nodes   Ordered list of member nodes; may be of any size ≥ 1.
   */
  HyperEdge(const std::string& userId,
             std::vector<shared<const Node<T>>> nodes);

  /**
   * @brief Convenience constructor accepting a brace-enclosed initializer list.
   */
  HyperEdge(const std::string& userId,
             std::initializer_list<shared<const Node<T>>> nodes);

  virtual ~HyperEdge() = default;

  // ── identity ──────────────────────────────────────────────────────────────

  /** @return Numeric hash of the user-supplied id (mirrors Edge<T>::getId()). */
  CXXGraph::id_t     getId()     const noexcept { return id_; }

  /** @return The original string id supplied at construction time. */
  const std::string& getUserId() const noexcept { return userId_; }

  // ── content ───────────────────────────────────────────────────────────────

  /** @return Ordered vector of all member node shared-pointers. */
  const std::vector<shared<const Node<T>>>& getNodes() const noexcept {
    return nodes_;
  }

  /** @return Number of member nodes (the "cardinality" or "rank" of this edge). */
  std::size_t size() const noexcept { return nodes_.size(); }

  /**
   * @brief Test membership by shared pointer (compares node ids).
   * @return true if any member node has the same getId() as @p node.
   */
  bool contains(const shared<const Node<T>>& node) const noexcept;

  /**
   * @brief Test membership by user-supplied string id.
   * @return true if any member node has getUserId() == @p nodeUserId.
   */
  bool contains(const std::string& nodeUserId) const noexcept;

  // ── optional weight ───────────────────────────────────────────────────────

  /** @return std::nullopt for the base (unweighted) HyperEdge. */
  virtual std::optional<double> getWeight() const { return std::nullopt; }

  /** @return false for the base (unweighted) HyperEdge. */
  virtual bool isWeighted() const { return false; }

  // ── operators ─────────────────────────────────────────────────────────────

  /** Two HyperEdges are equal when they share the same numeric id. */
  bool operator==(const HyperEdge<T>& b) const noexcept {
    return id_ == b.id_;
  }

  bool operator!=(const HyperEdge<T>& b) const noexcept {
    return !(*this == b);
  }

  bool operator<(const HyperEdge<T>& b) const noexcept {
    return id_ < b.id_;
  }

  friend std::ostream& operator<< <>(std::ostream& os, const HyperEdge<T>& he);

 private:
  CXXGraph::id_t                     id_;
  std::string                        userId_;
  std::vector<shared<const Node<T>>> nodes_;

  /** Hash the user-supplied string to produce a stable numeric id. */
  void setId(const std::string& s) noexcept;
};

// ═══════════════════════════════════════════════════════════════════════════
// WeightedHyperEdge<T>
//
// A HyperEdge<T> augmented with a scalar double weight.  The weight is
// carried on the edge itself (not on individual node memberships).
// ═══════════════════════════════════════════════════════════════════════════

template <typename T>
class WeightedHyperEdge : public HyperEdge<T> {
 public:
  /**
   * @brief Construct a weighted hyperedge.
   * @param userId  User-supplied string identifier.
   * @param nodes   Member nodes.
   * @param weight  Scalar weight attached to this hyperedge.
   */
  WeightedHyperEdge(const std::string& userId,
                    std::vector<shared<const Node<T>>> nodes,
                    double weight);

  ~WeightedHyperEdge() override = default;

  std::optional<double> getWeight() const override { return weight_; }
  bool                  isWeighted() const override { return true; }

 private:
  double weight_;
};

}  // namespace CXXGraph

#endif  // CXXGRAPH_HYPEREDGE_DECL_H_
