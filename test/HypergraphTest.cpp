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

#include <algorithm>
#include <memory>
#include <set>
#include <string>
#include <vector>

#include "CXXGraph/CXXGraph.hpp"
#include "gtest/gtest.h"

// Smart pointers alias
template <typename T>
using unique = std::unique_ptr<T>;
template <typename T>
using shared = std::shared_ptr<T>;

using std::make_shared;
using std::make_unique;

// ============================================================================
// Helpers
// ============================================================================

/** Return true if a node with the given userId appears in the vector. */
static bool containsNode(const std::vector<CXXGraph::Node<int>>& vec,
                         const std::string& userId) {
  return std::find_if(vec.begin(), vec.end(), [&](const auto& n) {
           return n.getUserId() == userId;
         }) != vec.end();
}

/** Return true if a node with the given userId appears in the T_NodeSet. */
static bool containsNodeInSet(const CXXGraph::T_NodeSet<int>& s,
                              const std::string& userId) {
  return std::find_if(s.begin(), s.end(), [&](const auto& n) {
           return n->getUserId() == userId;
         }) != s.end();
}

// ============================================================================
// Fixture — shared 5-node, 3-hyperedge topology used by algorithm tests
//
//   he1 = { alice, bob,   carol }       (project-alpha)
//   he2 = { carol, dave              }  (project-beta)   carol bridges he1/he2
//   he3 = { alice, bob,   carol, dave } (all-hands, weighted w=9.5)
//
//   eve  — isolated node (no hyperedge membership)
// ============================================================================

class HypergraphTest : public ::testing::Test {
 protected:
  void SetUp() override {
    alice = make_shared<CXXGraph::Node<int>>("alice", 1);
    bob = make_shared<CXXGraph::Node<int>>("bob", 2);
    carol = make_shared<CXXGraph::Node<int>>("carol", 3);
    dave = make_shared<CXXGraph::Node<int>>("dave", 4);
    eve = make_shared<CXXGraph::Node<int>>("eve", 5);

    he1 = make_shared<CXXGraph::HyperEdge<int>>(
        "project-alpha",
        std::vector<shared<const CXXGraph::Node<int>>>{alice, bob, carol});

    he2 = make_shared<CXXGraph::HyperEdge<int>>(
        "project-beta",
        std::vector<shared<const CXXGraph::Node<int>>>{carol, dave});

    he3 = make_shared<CXXGraph::WeightedHyperEdge<int>>(
        "all-hands",
        std::vector<shared<const CXXGraph::Node<int>>>{alice, bob, carol, dave},
        9.5);

    hg.addHyperEdge(he1);
    hg.addHyperEdge(he2);
    hg.addHyperEdge(he3);
    hg.addNode(eve);  // isolated
  }

  shared<CXXGraph::Node<int>> alice, bob, carol, dave, eve;
  shared<CXXGraph::HyperEdge<int>> he1, he2;
  shared<CXXGraph::WeightedHyperEdge<int>> he3;
  CXXGraph::Hypergraph<int> hg;
};

// ============================================================================
// HyperEdge construction
// ============================================================================

TEST(HyperEdgeTest, Constructor_vector) {
  auto n1 = make_shared<CXXGraph::Node<int>>("1", 1);
  auto n2 = make_shared<CXXGraph::Node<int>>("2", 2);
  auto n3 = make_shared<CXXGraph::Node<int>>("3", 3);

  CXXGraph::HyperEdge<int> he(
      "he-1", std::vector<shared<const CXXGraph::Node<int>>>{n1, n2, n3});

  ASSERT_EQ(he.getUserId(), "he-1");
  ASSERT_EQ(he.size(), 3u);
  ASSERT_FALSE(he.isWeighted());
  ASSERT_FALSE(he.getWeight().has_value());
}

TEST(HyperEdgeTest, Constructor_initializer_list) {
  auto n1 = make_shared<CXXGraph::Node<int>>("a", 10);
  auto n2 = make_shared<CXXGraph::Node<int>>("b", 20);

  CXXGraph::HyperEdge<int> he("he-init", {n1, n2});

  ASSERT_EQ(he.getUserId(), "he-init");
  ASSERT_EQ(he.size(), 2u);
}

TEST(HyperEdgeTest, SingleNodeHyperEdge) {
  // A hyperedge of size 1 is a valid self-loop equivalent.
  auto n1 = make_shared<CXXGraph::Node<int>>("solo", 99);
  CXXGraph::HyperEdge<int> he("solo-edge", {n1});

  ASSERT_EQ(he.size(), 1u);
  ASSERT_TRUE(he.contains("solo"));
}

TEST(HyperEdgeTest, LargeHyperEdge) {
  std::vector<shared<const CXXGraph::Node<int>>> nodes;
  for (int i = 0; i < 100; ++i)
    nodes.push_back(make_shared<CXXGraph::Node<int>>(std::to_string(i), i));

  CXXGraph::HyperEdge<int> he("big", nodes);
  ASSERT_EQ(he.size(), 100u);
}

TEST(HyperEdgeTest, IdIsStableAndDeterministic) {
  auto n1 = make_shared<CXXGraph::Node<int>>("x", 1);
  auto n2 = make_shared<CXXGraph::Node<int>>("y", 2);

  CXXGraph::HyperEdge<int> he_a("edge-42", {n1, n2});
  CXXGraph::HyperEdge<int> he_b("edge-42", {n1, n2});
  CXXGraph::HyperEdge<int> he_c("edge-43", {n1, n2});

  // Same userId → same id hash
  ASSERT_EQ(he_a.getId(), he_b.getId());
  // Different userId → different id hash (with very high probability)
  ASSERT_NE(he_a.getId(), he_c.getId());
}

TEST(HyperEdgeTest, EqualityOperator) {
  auto n1 = make_shared<CXXGraph::Node<int>>("1", 1);
  auto n2 = make_shared<CXXGraph::Node<int>>("2", 2);

  CXXGraph::HyperEdge<int> he_a("same-id", {n1, n2});
  CXXGraph::HyperEdge<int> he_b("same-id", {n1, n2});
  CXXGraph::HyperEdge<int> he_c("diff-id", {n1, n2});

  ASSERT_EQ(he_a, he_b);
  ASSERT_NE(he_a, he_c);
}

TEST(HyperEdgeTest, LessThanOperator) {
  auto n1 = make_shared<CXXGraph::Node<int>>("1", 1);
  CXXGraph::HyperEdge<int> he_a("aaa", {n1});
  CXXGraph::HyperEdge<int> he_b("zzz", {n1});
  // One of the two must be strictly less (hash ordering)
  ASSERT_TRUE((he_a < he_b) || (he_b < he_a));
}

// ============================================================================
// HyperEdge::contains
// ============================================================================

TEST(HyperEdgeTest, Contains_bySharedPtr_true) {
  auto n1 = make_shared<CXXGraph::Node<int>>("alpha", 1);
  auto n2 = make_shared<CXXGraph::Node<int>>("beta", 2);
  CXXGraph::HyperEdge<int> he("he", {n1, n2});

  ASSERT_TRUE(he.contains(n1));
  ASSERT_TRUE(he.contains(n2));
}

TEST(HyperEdgeTest, Contains_bySharedPtr_false) {
  auto n1 = make_shared<CXXGraph::Node<int>>("alpha", 1);
  auto n2 = make_shared<CXXGraph::Node<int>>("beta", 2);
  auto n3 = make_shared<CXXGraph::Node<int>>("gamma", 3);
  CXXGraph::HyperEdge<int> he("he", {n1, n2});

  ASSERT_FALSE(he.contains(n3));
}

TEST(HyperEdgeTest, Contains_byUserId_true) {
  auto n1 = make_shared<CXXGraph::Node<int>>("alice", 1);
  auto n2 = make_shared<CXXGraph::Node<int>>("bob", 2);
  CXXGraph::HyperEdge<int> he("he", {n1, n2});

  ASSERT_TRUE(he.contains("alice"));
  ASSERT_TRUE(he.contains("bob"));
}

TEST(HyperEdgeTest, Contains_byUserId_false) {
  auto n1 = make_shared<CXXGraph::Node<int>>("alice", 1);
  CXXGraph::HyperEdge<int> he("he", {n1});

  ASSERT_FALSE(he.contains("carol"));
  ASSERT_FALSE(he.contains(""));
}

// ============================================================================
// WeightedHyperEdge
// ============================================================================

TEST(WeightedHyperEdgeTest, IsWeightedAndReturnsWeight) {
  auto n1 = make_shared<CXXGraph::Node<int>>("1", 1);
  auto n2 = make_shared<CXXGraph::Node<int>>("2", 2);

  CXXGraph::WeightedHyperEdge<int> whe(
      "whe-1", std::vector<shared<const CXXGraph::Node<int>>>{n1, n2}, 3.14);

  ASSERT_TRUE(whe.isWeighted());
  ASSERT_TRUE(whe.getWeight().has_value());
  ASSERT_DOUBLE_EQ(whe.getWeight().value(), 3.14);
}

TEST(WeightedHyperEdgeTest, ZeroWeight) {
  auto n1 = make_shared<CXXGraph::Node<int>>("1", 1);
  CXXGraph::WeightedHyperEdge<int> whe(
      "whe-zero", std::vector<shared<const CXXGraph::Node<int>>>{n1}, 0.0);

  ASSERT_TRUE(whe.isWeighted());
  ASSERT_DOUBLE_EQ(whe.getWeight().value(), 0.0);
}

TEST(WeightedHyperEdgeTest, NegativeWeight) {
  auto n1 = make_shared<CXXGraph::Node<int>>("1", 1);
  auto n2 = make_shared<CXXGraph::Node<int>>("2", 2);
  CXXGraph::WeightedHyperEdge<int> whe(
      "whe-neg", std::vector<shared<const CXXGraph::Node<int>>>{n1, n2}, -7.5);

  ASSERT_DOUBLE_EQ(whe.getWeight().value(), -7.5);
}

TEST(WeightedHyperEdgeTest, ContainsWorksInherited) {
  auto n1 = make_shared<CXXGraph::Node<int>>("u", 1);
  auto n2 = make_shared<CXXGraph::Node<int>>("v", 2);
  CXXGraph::WeightedHyperEdge<int> whe(
      "whe", std::vector<shared<const CXXGraph::Node<int>>>{n1, n2}, 1.0);

  ASSERT_TRUE(whe.contains("u"));
  ASSERT_FALSE(whe.contains("w"));
}

TEST(WeightedHyperEdgeTest, UnweightedHyperEdgeHasNoWeight) {
  auto n1 = make_shared<CXXGraph::Node<int>>("1", 1);
  CXXGraph::HyperEdge<int> he(
      "unweighted", std::vector<shared<const CXXGraph::Node<int>>>{n1});

  ASSERT_FALSE(he.isWeighted());
  ASSERT_FALSE(he.getWeight().has_value());
}

// ============================================================================
// Hypergraph — construction & counts
// ============================================================================

TEST(HypergraphTest_Basic, EmptyGraph) {
  CXXGraph::Hypergraph<int> hg;
  ASSERT_EQ(hg.nodeCount(), 0u);
  ASSERT_EQ(hg.hyperEdgeCount(), 0u);
  ASSERT_EQ(hg.rank(), 0u);
  ASSERT_TRUE(hg.getNodeSet().empty());
  ASSERT_TRUE(hg.getHyperEdgeSet().empty());
}

TEST(HypergraphTest_Basic, ConstructFromEdgeSet) {
  auto n1 = make_shared<CXXGraph::Node<int>>("1", 1);
  auto n2 = make_shared<CXXGraph::Node<int>>("2", 2);
  auto n3 = make_shared<CXXGraph::Node<int>>("3", 3);

  auto he = make_shared<CXXGraph::HyperEdge<int>>(
      "he", std::vector<shared<const CXXGraph::Node<int>>>{n1, n2, n3});

  CXXGraph::T_HyperEdgeSet<int> edgeSet;
  edgeSet.insert(he);

  CXXGraph::Hypergraph<int> hg(edgeSet);
  ASSERT_EQ(hg.hyperEdgeCount(), 1u);
  ASSERT_EQ(hg.nodeCount(), 3u);
}

TEST_F(HypergraphTest, NodeCountIncludesIsolated) {
  // alice, bob, carol, dave (from edges) + eve (isolated) = 5
  ASSERT_EQ(hg.nodeCount(), 5u);
}

TEST_F(HypergraphTest, HyperEdgeCount) { ASSERT_EQ(hg.hyperEdgeCount(), 3u); }

// ============================================================================
// Hypergraph — addHyperEdge / removeHyperEdge
// ============================================================================

TEST(HypergraphMutationTest, AddHyperEdge_IncreasesCount) {
  CXXGraph::Hypergraph<int> hg;
  auto n1 = make_shared<CXXGraph::Node<int>>("1", 1);
  auto n2 = make_shared<CXXGraph::Node<int>>("2", 2);
  auto he = make_shared<CXXGraph::HyperEdge<int>>(
      "e1", std::vector<shared<const CXXGraph::Node<int>>>{n1, n2});

  hg.addHyperEdge(he);
  ASSERT_EQ(hg.hyperEdgeCount(), 1u);
  ASSERT_EQ(hg.nodeCount(), 2u);
}

TEST(HypergraphMutationTest, AddDuplicateHyperEdge_IsIdempotent) {
  CXXGraph::Hypergraph<int> hg;
  auto n1 = make_shared<CXXGraph::Node<int>>("1", 1);
  auto he = make_shared<CXXGraph::HyperEdge<int>>(
      "e1", std::vector<shared<const CXXGraph::Node<int>>>{n1});

  hg.addHyperEdge(he);
  hg.addHyperEdge(he);  // second add must be ignored
  ASSERT_EQ(hg.hyperEdgeCount(), 1u);
}

TEST(HypergraphMutationTest, RemoveHyperEdge_DecreasesCount) {
  CXXGraph::Hypergraph<int> hg;
  auto n1 = make_shared<CXXGraph::Node<int>>("1", 1);
  auto n2 = make_shared<CXXGraph::Node<int>>("2", 2);
  auto he = make_shared<CXXGraph::HyperEdge<int>>(
      "e1", std::vector<shared<const CXXGraph::Node<int>>>{n1, n2});

  hg.addHyperEdge(he);
  ASSERT_EQ(hg.hyperEdgeCount(), 1u);

  hg.removeHyperEdge("e1");
  ASSERT_EQ(hg.hyperEdgeCount(), 0u);
}

TEST(HypergraphMutationTest, RemoveNonExistentHyperEdge_IsNoOp) {
  CXXGraph::Hypergraph<int> hg;
  auto n1 = make_shared<CXXGraph::Node<int>>("1", 1);
  auto he = make_shared<CXXGraph::HyperEdge<int>>(
      "e1", std::vector<shared<const CXXGraph::Node<int>>>{n1});

  hg.addHyperEdge(he);
  hg.removeHyperEdge("does-not-exist");  // must not throw or corrupt state
  ASSERT_EQ(hg.hyperEdgeCount(), 1u);
}

TEST(HypergraphMutationTest, RemoveAndRe_add) {
  CXXGraph::Hypergraph<int> hg;
  auto n1 = make_shared<CXXGraph::Node<int>>("1", 1);
  auto he = make_shared<CXXGraph::HyperEdge<int>>(
      "e1", std::vector<shared<const CXXGraph::Node<int>>>{n1});

  hg.addHyperEdge(he);
  hg.removeHyperEdge("e1");
  hg.addHyperEdge(he);
  ASSERT_EQ(hg.hyperEdgeCount(), 1u);
}

// ============================================================================
// Hypergraph — addNode / removeNode
// ============================================================================

TEST(HypergraphMutationTest, AddIsolatedNode) {
  CXXGraph::Hypergraph<int> hg;
  auto n = make_shared<CXXGraph::Node<int>>("solo", 0);
  hg.addNode(n);

  ASSERT_EQ(hg.nodeCount(), 1u);
  ASSERT_TRUE(containsNodeInSet(hg.getNodeSet(), "solo"));
}

TEST(HypergraphMutationTest, RemoveIsolatedNode) {
  CXXGraph::Hypergraph<int> hg;
  auto n = make_shared<CXXGraph::Node<int>>("solo", 0);
  hg.addNode(n);
  hg.removeNode("solo");

  ASSERT_EQ(hg.nodeCount(), 0u);
}

TEST(HypergraphMutationTest, RemoveNodeAlsoUpdatesEdgeIncidence) {
  // After removing carol, he1 should no longer report carol as a member.
  CXXGraph::Hypergraph<int> hg;
  auto alice = make_shared<CXXGraph::Node<int>>("alice", 1);
  auto carol = make_shared<CXXGraph::Node<int>>("carol", 3);
  auto he1 = make_shared<CXXGraph::HyperEdge<int>>(
      "he1", std::vector<shared<const CXXGraph::Node<int>>>{alice, carol});

  hg.addHyperEdge(he1);
  hg.removeNode("carol");

  ASSERT_EQ(hg.nodeCount(), 1u);
  ASSERT_FALSE(containsNodeInSet(hg.getNodeSet(), "carol"));
}

TEST(HypergraphMutationTest, RemoveNonExistentNode_IsNoOp) {
  CXXGraph::Hypergraph<int> hg;
  auto n = make_shared<CXXGraph::Node<int>>("a", 1);
  hg.addNode(n);
  hg.removeNode("does-not-exist");
  ASSERT_EQ(hg.nodeCount(), 1u);
}

// ============================================================================
// Hypergraph — lookup queries
// ============================================================================

TEST_F(HypergraphTest, GetHyperEdge_Existing) {
  auto result = hg.getHyperEdge("project-alpha");
  ASSERT_TRUE(result.has_value());
  ASSERT_EQ(result.value()->getUserId(), "project-alpha");
}

TEST_F(HypergraphTest, GetHyperEdge_Missing) {
  auto result = hg.getHyperEdge("nonexistent");
  ASSERT_FALSE(result.has_value());
}

TEST_F(HypergraphTest, GetNode_Existing) {
  auto result = hg.getNode("alice");
  ASSERT_TRUE(result.has_value());
  ASSERT_EQ(result.value()->getUserId(), "alice");
}

TEST_F(HypergraphTest, GetNode_Missing) {
  auto result = hg.getNode("zara");
  ASSERT_FALSE(result.has_value());
}

TEST_F(HypergraphTest, GetNodeSet_ContainsAllNodes) {
  auto nodes = hg.getNodeSet();
  ASSERT_EQ(nodes.size(), 5u);
  ASSERT_TRUE(containsNodeInSet(nodes, "alice"));
  ASSERT_TRUE(containsNodeInSet(nodes, "bob"));
  ASSERT_TRUE(containsNodeInSet(nodes, "carol"));
  ASSERT_TRUE(containsNodeInSet(nodes, "dave"));
  ASSERT_TRUE(containsNodeInSet(nodes, "eve"));
}

TEST_F(HypergraphTest, GetHyperEdgesOfNode_Carol) {
  // carol is in he1 (project-alpha), he2 (project-beta), he3 (all-hands)
  auto edges = hg.getHyperEdgesOfNode("carol");
  ASSERT_EQ(edges.size(), 3u);
  std::set<std::string> ids;
  for (const auto& e : edges) ids.insert(e->getUserId());
  ASSERT_TRUE(ids.count("project-alpha"));
  ASSERT_TRUE(ids.count("project-beta"));
  ASSERT_TRUE(ids.count("all-hands"));
}

TEST_F(HypergraphTest, GetHyperEdgesOfNode_Dave) {
  // dave is in he2 and he3
  auto edges = hg.getHyperEdgesOfNode("dave");
  ASSERT_EQ(edges.size(), 2u);
  std::set<std::string> ids;
  for (const auto& e : edges) ids.insert(e->getUserId());
  ASSERT_TRUE(ids.count("project-beta"));
  ASSERT_TRUE(ids.count("all-hands"));
}

TEST_F(HypergraphTest, GetHyperEdgesOfNode_Isolated) {
  // eve has no hyperedge membership
  auto edges = hg.getHyperEdgesOfNode("eve");
  ASSERT_TRUE(edges.empty());
}

TEST_F(HypergraphTest, GetHyperEdgesOfNode_Unknown) {
  auto edges = hg.getHyperEdgesOfNode("nobody");
  ASSERT_TRUE(edges.empty());
}

// ============================================================================
// Hypergraph — neighbors
// ============================================================================

TEST_F(HypergraphTest, GetNeighbors_Alice) {
  // alice is in he1 {alice, bob, carol} and he3 {alice, bob, carol, dave}
  // neighbors = {bob, carol, dave}
  auto neighbors = hg.getNeighbors("alice");
  ASSERT_EQ(neighbors.size(), 3u);
  ASSERT_TRUE(containsNodeInSet(neighbors, "bob"));
  ASSERT_TRUE(containsNodeInSet(neighbors, "carol"));
  ASSERT_TRUE(containsNodeInSet(neighbors, "dave"));
  ASSERT_FALSE(containsNodeInSet(neighbors, "alice"));
  ASSERT_FALSE(containsNodeInSet(neighbors, "eve"));
}

TEST_F(HypergraphTest, GetNeighbors_Carol) {
  // carol is in all three edges; neighbors = {alice, bob, dave}
  auto neighbors = hg.getNeighbors("carol");
  ASSERT_EQ(neighbors.size(), 3u);
  ASSERT_TRUE(containsNodeInSet(neighbors, "alice"));
  ASSERT_TRUE(containsNodeInSet(neighbors, "bob"));
  ASSERT_TRUE(containsNodeInSet(neighbors, "dave"));
}

TEST_F(HypergraphTest, GetNeighbors_IsolatedNode) {
  auto neighbors = hg.getNeighbors("eve");
  ASSERT_TRUE(neighbors.empty());
}

TEST_F(HypergraphTest, GetNeighbors_UnknownNode) {
  auto neighbors = hg.getNeighbors("nobody");
  ASSERT_TRUE(neighbors.empty());
}

// ============================================================================
// Hypergraph — structural properties
// ============================================================================

TEST_F(HypergraphTest, Rank_IsMaxCardinality) {
  // he1 = 3, he2 = 2, he3 = 4  →  rank = 4
  ASSERT_EQ(hg.rank(), 4u);
}

TEST(HypergraphStructureTest, Rank_EmptyGraph) {
  CXXGraph::Hypergraph<int> hg;
  ASSERT_EQ(hg.rank(), 0u);
}

TEST(HypergraphStructureTest, Rank_AllSameCardinality) {
  auto n1 = make_shared<CXXGraph::Node<int>>("1", 1);
  auto n2 = make_shared<CXXGraph::Node<int>>("2", 2);
  auto n3 = make_shared<CXXGraph::Node<int>>("3", 3);
  auto n4 = make_shared<CXXGraph::Node<int>>("4", 4);

  auto he_a = make_shared<CXXGraph::HyperEdge<int>>(
      "a", std::vector<shared<const CXXGraph::Node<int>>>{n1, n2});
  auto he_b = make_shared<CXXGraph::HyperEdge<int>>(
      "b", std::vector<shared<const CXXGraph::Node<int>>>{n3, n4});

  CXXGraph::Hypergraph<int> hg;
  hg.addHyperEdge(he_a);
  hg.addHyperEdge(he_b);

  ASSERT_EQ(hg.rank(), 2u);
}

TEST_F(HypergraphTest, IsUniform_False) {
  // he1=3, he2=2, he3=4 — not uniform
  ASSERT_FALSE(hg.isUniform());
}

TEST(HypergraphStructureTest, IsUniform_True) {
  auto n1 = make_shared<CXXGraph::Node<int>>("1", 1);
  auto n2 = make_shared<CXXGraph::Node<int>>("2", 2);
  auto n3 = make_shared<CXXGraph::Node<int>>("3", 3);
  auto n4 = make_shared<CXXGraph::Node<int>>("4", 4);

  // Both edges have cardinality 2  →  2-uniform hypergraph (= ordinary graph)
  auto he_a = make_shared<CXXGraph::HyperEdge<int>>(
      "a", std::vector<shared<const CXXGraph::Node<int>>>{n1, n2});
  auto he_b = make_shared<CXXGraph::HyperEdge<int>>(
      "b", std::vector<shared<const CXXGraph::Node<int>>>{n3, n4});

  CXXGraph::Hypergraph<int> hg;
  hg.addHyperEdge(he_a);
  hg.addHyperEdge(he_b);

  ASSERT_TRUE(hg.isUniform());
}

TEST(HypergraphStructureTest, IsUniform_SingleEdge) {
  auto n1 = make_shared<CXXGraph::Node<int>>("1", 1);
  auto n2 = make_shared<CXXGraph::Node<int>>("2", 2);
  auto n3 = make_shared<CXXGraph::Node<int>>("3", 3);

  CXXGraph::Hypergraph<int> hg;
  hg.addHyperEdge(make_shared<CXXGraph::HyperEdge<int>>(
      "only", std::vector<shared<const CXXGraph::Node<int>>>{n1, n2, n3}));

  ASSERT_TRUE(hg.isUniform());
}

TEST(HypergraphStructureTest, IsUniform_EmptyGraph) {
  CXXGraph::Hypergraph<int> hg;
  // A hypergraph with no edges is vacuously uniform.
  ASSERT_TRUE(hg.isUniform());
}

// ============================================================================
// Hypergraph — incidence matrix
// ============================================================================

TEST(HypergraphMatrixTest, IncidenceMatrix_Dimensions) {
  auto n1 = make_shared<CXXGraph::Node<int>>("1", 1);
  auto n2 = make_shared<CXXGraph::Node<int>>("2", 2);
  auto n3 = make_shared<CXXGraph::Node<int>>("3", 3);
  auto he = make_shared<CXXGraph::HyperEdge<int>>(
      "he", std::vector<shared<const CXXGraph::Node<int>>>{n1, n2, n3});

  CXXGraph::Hypergraph<int> hg;
  hg.addHyperEdge(he);

  auto B = hg.incidenceMatrix();
  // 3 nodes × 1 edge
  ASSERT_EQ(B.size(), 3u);
  for (const auto& row : B) ASSERT_EQ(row.size(), 1u);
}

TEST(HypergraphMatrixTest, IncidenceMatrix_ValuesAreZeroOrOne) {
  auto n1 = make_shared<CXXGraph::Node<int>>("1", 1);
  auto n2 = make_shared<CXXGraph::Node<int>>("2", 2);
  auto n3 = make_shared<CXXGraph::Node<int>>("3", 3);
  auto n4 = make_shared<CXXGraph::Node<int>>("4", 4);

  // he1 covers n1, n2, n3;  he2 covers n3, n4
  auto he1 = make_shared<CXXGraph::HyperEdge<int>>(
      "he1", std::vector<shared<const CXXGraph::Node<int>>>{n1, n2, n3});
  auto he2 = make_shared<CXXGraph::HyperEdge<int>>(
      "he2", std::vector<shared<const CXXGraph::Node<int>>>{n3, n4});

  CXXGraph::Hypergraph<int> hg;
  hg.addHyperEdge(he1);
  hg.addHyperEdge(he2);

  auto B = hg.incidenceMatrix();
  for (const auto& row : B)
    for (int v : row) ASSERT_TRUE(v == 0 || v == 1);
}

TEST(HypergraphMatrixTest, IncidenceMatrix_ColumnSumEqualsEdgeCardinality) {
  auto n1 = make_shared<CXXGraph::Node<int>>("1", 1);
  auto n2 = make_shared<CXXGraph::Node<int>>("2", 2);
  auto n3 = make_shared<CXXGraph::Node<int>>("3", 3);

  auto he = make_shared<CXXGraph::HyperEdge<int>>(
      "he", std::vector<shared<const CXXGraph::Node<int>>>{n1, n2, n3});

  CXXGraph::Hypergraph<int> hg;
  hg.addHyperEdge(he);

  auto B = hg.incidenceMatrix();
  int colSum = 0;
  for (const auto& row : B) colSum += row[0];
  ASSERT_EQ(colSum, 3);  // exactly the three members of the edge
}

TEST(HypergraphMatrixTest, IncidenceMatrix_RowSumEqualsNodeDegree) {
  // n2 appears in both he1 and he2  →  row sum for n2 = 2
  auto n1 = make_shared<CXXGraph::Node<int>>("n1", 1);
  auto n2 = make_shared<CXXGraph::Node<int>>("n2", 2);
  auto n3 = make_shared<CXXGraph::Node<int>>("n3", 3);

  auto he1 = make_shared<CXXGraph::HyperEdge<int>>(
      "he1", std::vector<shared<const CXXGraph::Node<int>>>{n1, n2});
  auto he2 = make_shared<CXXGraph::HyperEdge<int>>(
      "he2", std::vector<shared<const CXXGraph::Node<int>>>{n2, n3});

  CXXGraph::Hypergraph<int> hg;
  hg.addHyperEdge(he1);
  hg.addHyperEdge(he2);

  auto B = hg.incidenceMatrix();
  auto ns = hg.getNodeSet();

  // Find the row corresponding to n2 and verify its sum = 2
  std::vector<shared<const CXXGraph::Node<int>>> nodeVec(ns.begin(), ns.end());
  int n2RowSum = -1;
  for (std::size_t i = 0; i < nodeVec.size(); ++i) {
    if (nodeVec[i]->getUserId() == "n2") {
      n2RowSum = 0;
      for (int v : B[i]) n2RowSum += v;
      break;
    }
  }
  ASSERT_EQ(n2RowSum, 2);
}

TEST(HypergraphMatrixTest, IncidenceMatrix_EmptyGraph) {
  CXXGraph::Hypergraph<int> hg;
  auto B = hg.incidenceMatrix();
  ASSERT_TRUE(B.empty());
}

// ============================================================================
// Hypergraph — toTwoSection
// ============================================================================

TEST(HypergraphTwoSectionTest, TwoSection_BinaryHyperedge_EqualsOrdinaryEdge) {
  // A hyperedge of size 2 is identical to an ordinary edge.
  auto n1 = make_shared<CXXGraph::Node<int>>("u", 1);
  auto n2 = make_shared<CXXGraph::Node<int>>("v", 2);

  CXXGraph::Hypergraph<int> hg;
  hg.addHyperEdge(make_shared<CXXGraph::HyperEdge<int>>(
      "e", std::vector<shared<const CXXGraph::Node<int>>>{n1, n2}));

  auto adj = hg.toTwoSection();
  ASSERT_EQ(adj.size(), 2u);
  ASSERT_TRUE(adj.at("u").count("v"));
  ASSERT_TRUE(adj.at("v").count("u"));
}

TEST_F(HypergraphTest, TwoSection_NodeCount) {
  auto adj = hg.toTwoSection();
  // Every node (including eve) appears as a key
  ASSERT_TRUE(adj.count("alice"));
  ASSERT_TRUE(adj.count("bob"));
  ASSERT_TRUE(adj.count("carol"));
  ASSERT_TRUE(adj.count("dave"));
  ASSERT_TRUE(adj.count("eve"));
}

TEST_F(HypergraphTest, TwoSection_AliceConnectedToAll_NonEve) {
  auto adj = hg.toTwoSection();
  // alice is in he1 and he3 with bob, carol, dave
  ASSERT_TRUE(adj.at("alice").count("bob"));
  ASSERT_TRUE(adj.at("alice").count("carol"));
  ASSERT_TRUE(adj.at("alice").count("dave"));
  ASSERT_FALSE(adj.at("alice").count("eve"));
}

TEST_F(HypergraphTest, TwoSection_EveHasNoNeighbors) {
  auto adj = hg.toTwoSection();
  ASSERT_TRUE(adj.at("eve").empty());
}

TEST(HypergraphTwoSectionTest, TwoSection_EmptyGraph) {
  CXXGraph::Hypergraph<int> hg;
  auto adj = hg.toTwoSection();
  ASSERT_TRUE(adj.empty());
}

// ============================================================================
// Hypergraph — BFS
// ============================================================================

TEST_F(HypergraphTest, BFS_FromAlice_VisitsConnectedComponent) {
  // alice, bob, carol, dave are all reachable via shared hyperedges
  auto res = hg.breadth_first_search(*alice);
  ASSERT_EQ(res.size(), 4u);
  ASSERT_TRUE(containsNode(res, "alice"));
  ASSERT_TRUE(containsNode(res, "bob"));
  ASSERT_TRUE(containsNode(res, "carol"));
  ASSERT_TRUE(containsNode(res, "dave"));
  ASSERT_FALSE(containsNode(res, "eve"));
}

TEST_F(HypergraphTest, BFS_FromAlice_StartsWithSource) {
  auto res = hg.breadth_first_search(*alice);
  ASSERT_FALSE(res.empty());
  ASSERT_EQ(res.front().getUserId(), "alice");
}

TEST_F(HypergraphTest, BFS_FromEve_ReturnsOnlyEve) {
  auto res = hg.breadth_first_search(*eve);
  ASSERT_EQ(res.size(), 1u);
  ASSERT_EQ(res.front().getUserId(), "eve");
}

TEST(HypergraphBFSTest, BFS_UnknownStartNode_ReturnsEmpty) {
  CXXGraph::Hypergraph<int> hg;
  CXXGraph::Node<int> ghost("ghost", 0);
  auto res = hg.breadth_first_search(ghost);
  ASSERT_TRUE(res.empty());
}

TEST(HypergraphBFSTest, BFS_SingleNode_ReturnsThatNode) {
  CXXGraph::Hypergraph<int> hg;
  auto n = make_shared<CXXGraph::Node<int>>("solo", 1);
  hg.addNode(n);

  auto res = hg.breadth_first_search(*n);
  ASSERT_EQ(res.size(), 1u);
  ASSERT_EQ(res.front().getUserId(), "solo");
}

TEST(HypergraphBFSTest, BFS_LinearChain_VisitsAll) {
  // he1={A,B}, he2={B,C}, he3={C,D}  →  chain A-B-C-D
  auto nA = make_shared<CXXGraph::Node<int>>("A", 1);
  auto nB = make_shared<CXXGraph::Node<int>>("B", 2);
  auto nC = make_shared<CXXGraph::Node<int>>("C", 3);
  auto nD = make_shared<CXXGraph::Node<int>>("D", 4);

  CXXGraph::Hypergraph<int> hg;
  hg.addHyperEdge(make_shared<CXXGraph::HyperEdge<int>>(
      "he1", std::vector<shared<const CXXGraph::Node<int>>>{nA, nB}));
  hg.addHyperEdge(make_shared<CXXGraph::HyperEdge<int>>(
      "he2", std::vector<shared<const CXXGraph::Node<int>>>{nB, nC}));
  hg.addHyperEdge(make_shared<CXXGraph::HyperEdge<int>>(
      "he3", std::vector<shared<const CXXGraph::Node<int>>>{nC, nD}));

  auto res = hg.breadth_first_search(*nA);
  ASSERT_EQ(res.size(), 4u);
  ASSERT_TRUE(containsNode(res, "A"));
  ASSERT_TRUE(containsNode(res, "B"));
  ASSERT_TRUE(containsNode(res, "C"));
  ASSERT_TRUE(containsNode(res, "D"));
}

TEST(HypergraphBFSTest, BFS_NodesVisitedExactlyOnce) {
  // Star topology: he1={center,a}, he2={center,b}, he3={center,c}
  auto center = make_shared<CXXGraph::Node<int>>("center", 0);
  auto nA = make_shared<CXXGraph::Node<int>>("a", 1);
  auto nB = make_shared<CXXGraph::Node<int>>("b", 2);
  auto nC = make_shared<CXXGraph::Node<int>>("c", 3);

  CXXGraph::Hypergraph<int> hg;
  hg.addHyperEdge(make_shared<CXXGraph::HyperEdge<int>>(
      "h1", std::vector<shared<const CXXGraph::Node<int>>>{center, nA}));
  hg.addHyperEdge(make_shared<CXXGraph::HyperEdge<int>>(
      "h2", std::vector<shared<const CXXGraph::Node<int>>>{center, nB}));
  hg.addHyperEdge(make_shared<CXXGraph::HyperEdge<int>>(
      "h3", std::vector<shared<const CXXGraph::Node<int>>>{center, nC}));

  auto res = hg.breadth_first_search(*center);
  ASSERT_EQ(res.size(), 4u);

  // Verify no duplicates
  std::set<std::string> seen;
  for (const auto& n : res) {
    ASSERT_TRUE(seen.insert(n.getUserId()).second)
        << "Node " << n.getUserId() << " visited more than once";
  }
}

// ============================================================================
// Hypergraph — DFS
// ============================================================================

TEST_F(HypergraphTest, DFS_FromAlice_VisitsConnectedComponent) {
  auto res = hg.depth_first_search(*alice);
  ASSERT_EQ(res.size(), 4u);
  ASSERT_TRUE(containsNode(res, "alice"));
  ASSERT_TRUE(containsNode(res, "bob"));
  ASSERT_TRUE(containsNode(res, "carol"));
  ASSERT_TRUE(containsNode(res, "dave"));
  ASSERT_FALSE(containsNode(res, "eve"));
}

TEST_F(HypergraphTest, DFS_FromEve_ReturnsOnlyEve) {
  auto res = hg.depth_first_search(*eve);
  ASSERT_EQ(res.size(), 1u);
  ASSERT_EQ(res.front().getUserId(), "eve");
}

TEST(HypergraphDFSTest, DFS_UnknownStartNode_ReturnsEmpty) {
  CXXGraph::Hypergraph<int> hg;
  CXXGraph::Node<int> ghost("ghost", 0);
  auto res = hg.depth_first_search(ghost);
  ASSERT_TRUE(res.empty());
}

TEST(HypergraphDFSTest, DFS_NodesVisitedExactlyOnce) {
  auto n1 = make_shared<CXXGraph::Node<int>>("1", 1);
  auto n2 = make_shared<CXXGraph::Node<int>>("2", 2);
  auto n3 = make_shared<CXXGraph::Node<int>>("3", 3);
  auto n4 = make_shared<CXXGraph::Node<int>>("4", 4);

  // A 3-node edge sharing n2 with a 2-node edge
  CXXGraph::Hypergraph<int> hg;
  hg.addHyperEdge(make_shared<CXXGraph::HyperEdge<int>>(
      "h1", std::vector<shared<const CXXGraph::Node<int>>>{n1, n2, n3}));
  hg.addHyperEdge(make_shared<CXXGraph::HyperEdge<int>>(
      "h2", std::vector<shared<const CXXGraph::Node<int>>>{n2, n4}));

  auto res = hg.depth_first_search(*n1);
  ASSERT_EQ(res.size(), 4u);

  std::set<std::string> seen;
  for (const auto& n : res) {
    ASSERT_TRUE(seen.insert(n.getUserId()).second)
        << "DFS visited " << n.getUserId() << " more than once";
  }
}

TEST(HypergraphDFSTest, DFS_BFS_SameReachabilitySet) {
  // BFS and DFS must reach exactly the same set of nodes (order may differ).
  auto n1 = make_shared<CXXGraph::Node<int>>("1", 1);
  auto n2 = make_shared<CXXGraph::Node<int>>("2", 2);
  auto n3 = make_shared<CXXGraph::Node<int>>("3", 3);
  auto n4 = make_shared<CXXGraph::Node<int>>("4", 4);

  CXXGraph::Hypergraph<int> hg;
  hg.addHyperEdge(make_shared<CXXGraph::HyperEdge<int>>(
      "h1", std::vector<shared<const CXXGraph::Node<int>>>{n1, n2, n3}));
  hg.addHyperEdge(make_shared<CXXGraph::HyperEdge<int>>(
      "h2", std::vector<shared<const CXXGraph::Node<int>>>{n3, n4}));

  auto bfsRes = hg.breadth_first_search(*n1);
  auto dfsRes = hg.depth_first_search(*n1);

  ASSERT_EQ(bfsRes.size(), dfsRes.size());

  std::set<std::string> bfsSet, dfsSet;
  for (const auto& n : bfsRes) bfsSet.insert(n.getUserId());
  for (const auto& n : dfsRes) dfsSet.insert(n.getUserId());
  ASSERT_EQ(bfsSet, dfsSet);
}

// ============================================================================
// Hypergraph — connected components
// ============================================================================

TEST_F(HypergraphTest, ConnectedComponents_TwoComponents) {
  // alice/bob/carol/dave form one component; eve is isolated → 2 components
  auto comps = hg.connectedComponents();
  ASSERT_EQ(comps.size(), 2u);
}

TEST(HypergraphComponentTest, ConnectedComponents_SingleComponent) {
  auto n1 = make_shared<CXXGraph::Node<int>>("1", 1);
  auto n2 = make_shared<CXXGraph::Node<int>>("2", 2);
  auto n3 = make_shared<CXXGraph::Node<int>>("3", 3);

  CXXGraph::Hypergraph<int> hg;
  hg.addHyperEdge(make_shared<CXXGraph::HyperEdge<int>>(
      "he", std::vector<shared<const CXXGraph::Node<int>>>{n1, n2, n3}));

  auto comps = hg.connectedComponents();
  ASSERT_EQ(comps.size(), 1u);
  ASSERT_EQ(comps[0].size(), 3u);
}

TEST(HypergraphComponentTest, ConnectedComponents_AllIsolated) {
  CXXGraph::Hypergraph<int> hg;
  auto n1 = make_shared<CXXGraph::Node<int>>("1", 1);
  auto n2 = make_shared<CXXGraph::Node<int>>("2", 2);
  auto n3 = make_shared<CXXGraph::Node<int>>("3", 3);
  hg.addNode(n1);
  hg.addNode(n2);
  hg.addNode(n3);

  auto comps = hg.connectedComponents();
  ASSERT_EQ(comps.size(), 3u);
  for (const auto& c : comps) ASSERT_EQ(c.size(), 1u);
}

TEST(HypergraphComponentTest, ConnectedComponents_TwoDisjointEdges) {
  auto n1 = make_shared<CXXGraph::Node<int>>("1", 1);
  auto n2 = make_shared<CXXGraph::Node<int>>("2", 2);
  auto n3 = make_shared<CXXGraph::Node<int>>("3", 3);
  auto n4 = make_shared<CXXGraph::Node<int>>("4", 4);

  CXXGraph::Hypergraph<int> hg;
  hg.addHyperEdge(make_shared<CXXGraph::HyperEdge<int>>(
      "he1", std::vector<shared<const CXXGraph::Node<int>>>{n1, n2}));
  hg.addHyperEdge(make_shared<CXXGraph::HyperEdge<int>>(
      "he2", std::vector<shared<const CXXGraph::Node<int>>>{n3, n4}));

  auto comps = hg.connectedComponents();
  ASSERT_EQ(comps.size(), 2u);
  for (const auto& c : comps) ASSERT_EQ(c.size(), 2u);
}

TEST(HypergraphComponentTest, ConnectedComponents_EmptyGraph) {
  CXXGraph::Hypergraph<int> hg;
  auto comps = hg.connectedComponents();
  ASSERT_TRUE(comps.empty());
}

TEST(HypergraphComponentTest, ConnectedComponents_ComponentSizesCoverAllNodes) {
  auto n1 = make_shared<CXXGraph::Node<int>>("1", 1);
  auto n2 = make_shared<CXXGraph::Node<int>>("2", 2);
  auto n3 = make_shared<CXXGraph::Node<int>>("3", 3);
  auto n4 = make_shared<CXXGraph::Node<int>>("4", 4);
  auto n5 = make_shared<CXXGraph::Node<int>>("5", 5);  // isolated

  CXXGraph::Hypergraph<int> hg;
  hg.addHyperEdge(make_shared<CXXGraph::HyperEdge<int>>(
      "he1", std::vector<shared<const CXXGraph::Node<int>>>{n1, n2, n3}));
  hg.addHyperEdge(make_shared<CXXGraph::HyperEdge<int>>(
      "he2", std::vector<shared<const CXXGraph::Node<int>>>{n3, n4}));
  hg.addNode(n5);

  auto comps = hg.connectedComponents();
  // n1,n2,n3,n4 connected via n3; n5 isolated → 2 components
  ASSERT_EQ(comps.size(), 2u);

  std::size_t totalNodes = 0;
  for (const auto& c : comps) totalNodes += c.size();
  ASSERT_EQ(totalNodes, 5u);
}

// ============================================================================
// Hypergraph — dual
// ============================================================================

TEST(HypergraphDualTest, Dual_NodeCountEqualsOriginalEdgeCount) {
  auto n1 = make_shared<CXXGraph::Node<int>>("1", 1);
  auto n2 = make_shared<CXXGraph::Node<int>>("2", 2);
  auto n3 = make_shared<CXXGraph::Node<int>>("3", 3);

  CXXGraph::Hypergraph<int> hg;
  hg.addHyperEdge(make_shared<CXXGraph::HyperEdge<int>>(
      "he1", std::vector<shared<const CXXGraph::Node<int>>>{n1, n2}));
  hg.addHyperEdge(make_shared<CXXGraph::HyperEdge<int>>(
      "he2", std::vector<shared<const CXXGraph::Node<int>>>{n2, n3}));

  auto dual = hg.dual();
  // Original: 2 edges → dual: 2 nodes
  ASSERT_EQ(dual.nodeCount(), 2u);
}

TEST(HypergraphDualTest, Dual_EdgeCountEqualsOriginalNodeCount) {
  auto n1 = make_shared<CXXGraph::Node<int>>("n1", 1);
  auto n2 = make_shared<CXXGraph::Node<int>>("n2", 2);
  auto n3 = make_shared<CXXGraph::Node<int>>("n3", 3);

  // he1 covers n1, n2;  he2 covers n2, n3;  he3 covers n1, n3
  CXXGraph::Hypergraph<int> hg;
  hg.addHyperEdge(make_shared<CXXGraph::HyperEdge<int>>(
      "he1", std::vector<shared<const CXXGraph::Node<int>>>{n1, n2}));
  hg.addHyperEdge(make_shared<CXXGraph::HyperEdge<int>>(
      "he2", std::vector<shared<const CXXGraph::Node<int>>>{n2, n3}));
  hg.addHyperEdge(make_shared<CXXGraph::HyperEdge<int>>(
      "he3", std::vector<shared<const CXXGraph::Node<int>>>{n1, n3}));

  auto dual = hg.dual();
  // Original: 3 nodes → dual: 3 edges
  ASSERT_EQ(dual.hyperEdgeCount(), 3u);
}

TEST(HypergraphDualTest, Dual_OfDual_IsIsomorphicToOriginal) {
  // (H*)* is isomorphic to H — same counts
  auto n1 = make_shared<CXXGraph::Node<int>>("1", 1);
  auto n2 = make_shared<CXXGraph::Node<int>>("2", 2);
  auto n3 = make_shared<CXXGraph::Node<int>>("3", 3);

  CXXGraph::Hypergraph<int> hg;
  hg.addHyperEdge(make_shared<CXXGraph::HyperEdge<int>>(
      "he1", std::vector<shared<const CXXGraph::Node<int>>>{n1, n2, n3}));
  hg.addHyperEdge(make_shared<CXXGraph::HyperEdge<int>>(
      "he2", std::vector<shared<const CXXGraph::Node<int>>>{n1, n2}));

  auto dual = hg.dual();
  auto dualDual = dual.dual();

  ASSERT_EQ(dualDual.nodeCount(), hg.nodeCount());
  ASSERT_EQ(dualDual.hyperEdgeCount(), hg.hyperEdgeCount());
}

// ============================================================================
// Template parameter — non-int node data
// ============================================================================

TEST(HypergraphTemplateTest, StringNodeData) {
  auto n1 = make_shared<CXXGraph::Node<std::string>>("u", "hello");
  auto n2 = make_shared<CXXGraph::Node<std::string>>("v", "world");

  auto he = make_shared<CXXGraph::HyperEdge<std::string>>(
      "he", std::vector<shared<const CXXGraph::Node<std::string>>>{n1, n2});

  CXXGraph::Hypergraph<std::string> hg;
  hg.addHyperEdge(he);

  ASSERT_EQ(hg.nodeCount(), 2u);
  ASSERT_EQ(hg.hyperEdgeCount(), 1u);

  auto res = hg.breadth_first_search(*n1);
  ASSERT_EQ(res.size(), 2u);
}

TEST(HypergraphTemplateTest, DoubleNodeData) {
  auto n1 = make_shared<CXXGraph::Node<double>>("a", 1.1);
  auto n2 = make_shared<CXXGraph::Node<double>>("b", 2.2);
  auto n3 = make_shared<CXXGraph::Node<double>>("c", 3.3);

  CXXGraph::Hypergraph<double> hg;
  hg.addHyperEdge(make_shared<CXXGraph::HyperEdge<double>>(
      "he", std::vector<shared<const CXXGraph::Node<double>>>{n1, n2, n3}));

  ASSERT_EQ(hg.rank(), 3u);
  ASSERT_TRUE(hg.isUniform());
}

// ============================================================================
// Stream operator smoke test
// ============================================================================

TEST(HyperEdgeStreamTest, OutputOperator_DoesNotCrash) {
  auto n1 = make_shared<CXXGraph::Node<int>>("p", 1);
  auto n2 = make_shared<CXXGraph::Node<int>>("q", 2);
  CXXGraph::HyperEdge<int> he("edge-out", {n1, n2});

  std::ostringstream oss;
  ASSERT_NO_THROW(oss << he);
  ASSERT_FALSE(oss.str().empty());
}

TEST(HypergraphStreamTest, OutputOperator_DoesNotCrash) {
  auto n1 = make_shared<CXXGraph::Node<int>>("1", 1);
  CXXGraph::Hypergraph<int> hg;
  hg.addNode(n1);

  std::ostringstream oss;
  ASSERT_NO_THROW(oss << hg);
}
