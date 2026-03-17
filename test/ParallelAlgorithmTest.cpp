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

// Parallel algorithm tests
// Covers: floydWarshall_parallel, bellmanford_parallel,
//         kruskal_parallel, welshPowellColoring_parallel
//
// Test strategy for every algorithm:
//   1. Error paths (same inputs that make the serial version fail)
//   2. Known-answer correctness (hand-computed expected values)
//   3. Serial/parallel equivalence on identical graphs
//   4. Scale / stress (larger random graph, equivalence only)

#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <limits>
#include <map>
#include <memory>
#include <random>
#include <set>
#include <string>
#include <utility>
#include <vector>

#include "CXXGraph/CXXGraph.hpp"
#include "gtest/gtest.h"

template <typename T>
using shared = std::shared_ptr<T>;
using std::make_shared;

// ============================================================================
//  Helpers
// ============================================================================

/** Retrieve distance from an FWResult map; returns +inf if key is absent. */
static double fwDist(const CXXGraph::FWResult& res, const std::string& u,
                     const std::string& v) {
  auto it = res.result.find({u, v});
  if (it == res.result.end()) return std::numeric_limits<double>::infinity();
  return it->second;
}

/** True if two FWResult distance maps are element-wise equal within eps. */
static bool fwResultsEqual(const CXXGraph::FWResult& a,
                           const CXXGraph::FWResult& b, double eps = 1e-9) {
  if (a.result.size() != b.result.size()) return false;
  for (const auto& [key, val] : a.result) {
    auto it = b.result.find(key);
    if (it == b.result.end()) return false;
    if (std::isinf(val) && std::isinf(it->second)) continue;
    if (std::abs(val - it->second) > eps) return false;
  }
  return true;
}

/** True if every adjacent node pair in the coloring map has different colors.
 */
template <typename T>
static bool coloringIsValid(const CXXGraph::Graph<T>& g,
                            const std::map<CXXGraph::Node<T>, int>& coloring) {
  for (const auto& edge : g.getEdgeSet()) {
    auto n1 = edge->getNodePair().first;
    auto n2 = edge->getNodePair().second;
    auto it1 =
        std::find_if(coloring.begin(), coloring.end(), [&n1](const auto& p) {
          return p.first.getUserId() == n1->getUserId();
        });
    auto it2 =
        std::find_if(coloring.begin(), coloring.end(), [&n2](const auto& p) {
          return p.first.getUserId() == n2->getUserId();
        });
    if (it1 == coloring.end() || it2 == coloring.end()) return false;
    if (it1->second == it2->second) return false;
  }
  return true;
}

/** Maximum color value in a coloring map. */
template <typename T>
static int maxColor(const std::map<CXXGraph::Node<T>, int>& coloring) {
  if (coloring.empty()) return 0;
  return std::max_element(
             coloring.begin(), coloring.end(),
             [](const auto& a, const auto& b) { return a.second < b.second; })
      ->second;
}

// ============================================================================
//  floydWarshall_parallel
// ============================================================================

// ── Error paths ──────────────────────────────────────────────────────────────

TEST(FWParallelTest, fails_on_unweighted_edge) {
  CXXGraph::Node<int> n1("1", 1), n2("2", 2);
  CXXGraph::DirectedEdge<int> e("1", n1, n2);
  CXXGraph::T_EdgeSet<int> es;
  es.insert(make_shared<CXXGraph::DirectedEdge<int>>(e));
  CXXGraph::Graph<int> g(es);

  auto res = g.floydWarshall_parallel();
  ASSERT_FALSE(res.success);
  ASSERT_EQ(res.errorMessage, CXXGraph::ERR_NO_WEIGHTED_EDGE);
}

TEST(FWParallelTest, fails_on_mixed_weighted_unweighted) {
  CXXGraph::Node<int> n1("1", 1), n2("2", 2), n3("3", 3);
  CXXGraph::DirectedWeightedEdge<int> e1("1", n1, n2, 5.0);
  CXXGraph::DirectedEdge<int> e2("2", n2, n3);
  CXXGraph::T_EdgeSet<int> es;
  es.insert(make_shared<CXXGraph::DirectedWeightedEdge<int>>(e1));
  es.insert(make_shared<CXXGraph::DirectedEdge<int>>(e2));
  CXXGraph::Graph<int> g(es);

  auto res = g.floydWarshall_parallel();
  ASSERT_FALSE(res.success);
  ASSERT_EQ(res.errorMessage, CXXGraph::ERR_NO_WEIGHTED_EDGE);
}

// ── Known-answer tests
// ────────────────────────────────────────────────────────

// Triangle: 1→2 (w=1), 2→3 (w=1), 1→3 (w=6)
// Expected: dist(1,3) = 2 (via 2), not 6 direct
TEST(FWParallelTest, triangle_shortest_via_relay) {
  CXXGraph::Node<int> n1("1", 1), n2("2", 2), n3("3", 3);
  CXXGraph::DirectedWeightedEdge<int> e1("1", n1, n2, 1.0);
  CXXGraph::DirectedWeightedEdge<int> e2("2", n2, n3, 1.0);
  CXXGraph::DirectedWeightedEdge<int> e3("3", n1, n3, 6.0);
  CXXGraph::T_EdgeSet<int> es;
  es.insert(make_shared<CXXGraph::DirectedWeightedEdge<int>>(e1));
  es.insert(make_shared<CXXGraph::DirectedWeightedEdge<int>>(e2));
  es.insert(make_shared<CXXGraph::DirectedWeightedEdge<int>>(e3));
  CXXGraph::Graph<int> g(es);

  auto res = g.floydWarshall_parallel();
  ASSERT_TRUE(res.success);
  ASSERT_FALSE(res.negativeCycle);
  ASSERT_EQ(res.errorMessage, "");
  ASSERT_DOUBLE_EQ(fwDist(res, "1", "2"), 1.0);
  ASSERT_DOUBLE_EQ(fwDist(res, "1", "3"), 2.0);
  ASSERT_DOUBLE_EQ(fwDist(res, "2", "3"), 1.0);
  ASSERT_DOUBLE_EQ(fwDist(res, "1", "1"), 0.0);
}

// Two isolated nodes connected by a single edge
TEST(FWParallelTest, single_undirected_edge_symmetric) {
  CXXGraph::Node<int> n0("0", 0), n1("1", 1);
  CXXGraph::UndirectedWeightedEdge<int> e("1", n0, n1, 7.0);
  CXXGraph::T_EdgeSet<int> es;
  es.insert(make_shared<CXXGraph::UndirectedWeightedEdge<int>>(e));
  CXXGraph::Graph<int> g(es);

  auto res = g.floydWarshall_parallel();
  ASSERT_TRUE(res.success);
  ASSERT_FALSE(res.negativeCycle);
  ASSERT_DOUBLE_EQ(fwDist(res, "0", "1"), 7.0);
  ASSERT_DOUBLE_EQ(fwDist(res, "1", "0"), 7.0);  // symmetric
  ASSERT_DOUBLE_EQ(fwDist(res, "0", "0"), 0.0);
  ASSERT_DOUBLE_EQ(fwDist(res, "1", "1"), 0.0);
}

// Negative cycle: 0→1 (+2), 1→2 (+3), 2→0 (-7)  → sum = -2
TEST(FWParallelTest, detects_negative_cycle) {
  CXXGraph::Node<int> n0("0", 0), n1("1", 1), n2("2", 2);
  CXXGraph::DirectedWeightedEdge<int> e1("1", n0, n1, 2.0);
  CXXGraph::DirectedWeightedEdge<int> e2("2", n1, n2, 3.0);
  CXXGraph::DirectedWeightedEdge<int> e3("3", n2, n0, -7.0);
  CXXGraph::T_EdgeSet<int> es;
  es.insert(make_shared<CXXGraph::DirectedWeightedEdge<int>>(e1));
  es.insert(make_shared<CXXGraph::DirectedWeightedEdge<int>>(e2));
  es.insert(make_shared<CXXGraph::DirectedWeightedEdge<int>>(e3));
  CXXGraph::Graph<int> g(es);

  auto res = g.floydWarshall_parallel();
  ASSERT_TRUE(res.success);
  ASSERT_TRUE(res.negativeCycle);
}

// Self-loop with negative weight is a negative cycle
TEST(FWParallelTest, self_loop_negative_weight_is_negative_cycle) {
  CXXGraph::Node<int> n1("1", 1), n2("2", 2);
  CXXGraph::DirectedWeightedEdge<int> e1("1", n1, n2, 1.0);
  CXXGraph::DirectedWeightedEdge<int> e2("2", n1, n1,
                                         -1.0);  // negative self-loop
  CXXGraph::T_EdgeSet<int> es;
  es.insert(make_shared<CXXGraph::DirectedWeightedEdge<int>>(e1));
  es.insert(make_shared<CXXGraph::DirectedWeightedEdge<int>>(e2));
  CXXGraph::Graph<int> g(es);

  auto res = g.floydWarshall_parallel();
  ASSERT_TRUE(res.success);
  ASSERT_TRUE(res.negativeCycle);
}

// Disconnected graph: dist from component A to component B should be inf
TEST(FWParallelTest, disconnected_graph_infinity_between_components) {
  CXXGraph::Node<int> n1("1", 1), n2("2", 2);
  CXXGraph::Node<int> n3("3", 3), n4("4", 4);
  CXXGraph::DirectedWeightedEdge<int> e1("1", n1, n2, 3.0);
  CXXGraph::DirectedWeightedEdge<int> e2("2", n3, n4, 2.0);
  CXXGraph::T_EdgeSet<int> es;
  es.insert(make_shared<CXXGraph::DirectedWeightedEdge<int>>(e1));
  es.insert(make_shared<CXXGraph::DirectedWeightedEdge<int>>(e2));
  CXXGraph::Graph<int> g(es);

  auto res = g.floydWarshall_parallel();
  ASSERT_TRUE(res.success);
  ASSERT_FALSE(res.negativeCycle);
  ASSERT_TRUE(std::isinf(fwDist(res, "1", "3")));
  ASSERT_TRUE(std::isinf(fwDist(res, "2", "4")));
  ASSERT_DOUBLE_EQ(fwDist(res, "1", "2"), 3.0);
  ASSERT_DOUBLE_EQ(fwDist(res, "3", "4"), 2.0);
}

// 4-node directed graph with known pairwise distances
// 1→2 (w=3), 1→3 (w=8), 1→4 (w=-4),
// 2→4 (w=1), 2→5... simplified to 4 nodes
// Using a well-known textbook example:
// Nodes: A,B,C,D   A→B=3, A→C=8, B→D=1, D→B=4, C→D=2
// dist(A,D) = min(direct A→D=inf, A→B→D=4, A→C→D=10) = 4
TEST(FWParallelTest, four_node_textbook_example) {
  CXXGraph::Node<int> nA("A", 1), nB("B", 2), nC("C", 3), nD("D", 4);
  CXXGraph::DirectedWeightedEdge<int> eAB("AB", nA, nB, 3.0);
  CXXGraph::DirectedWeightedEdge<int> eAC("AC", nA, nC, 8.0);
  CXXGraph::DirectedWeightedEdge<int> eBD("BD", nB, nD, 1.0);
  CXXGraph::DirectedWeightedEdge<int> eDB("DB", nD, nB, 4.0);
  CXXGraph::DirectedWeightedEdge<int> eCD("CD", nC, nD, 2.0);
  CXXGraph::T_EdgeSet<int> es;
  es.insert(make_shared<CXXGraph::DirectedWeightedEdge<int>>(eAB));
  es.insert(make_shared<CXXGraph::DirectedWeightedEdge<int>>(eAC));
  es.insert(make_shared<CXXGraph::DirectedWeightedEdge<int>>(eBD));
  es.insert(make_shared<CXXGraph::DirectedWeightedEdge<int>>(eDB));
  es.insert(make_shared<CXXGraph::DirectedWeightedEdge<int>>(eCD));
  CXXGraph::Graph<int> g(es);

  auto res = g.floydWarshall_parallel();
  ASSERT_TRUE(res.success);
  ASSERT_FALSE(res.negativeCycle);
  ASSERT_DOUBLE_EQ(fwDist(res, "A", "B"), 3.0);
  ASSERT_DOUBLE_EQ(fwDist(res, "A", "D"), 4.0);  // A→B→D
  ASSERT_DOUBLE_EQ(fwDist(res, "D", "B"), 4.0);  // direct D→B
}

// ── Serial/parallel equivalence
// ───────────────────────────────────────────────

TEST(FWParallelTest, matches_serial_on_triangle) {
  CXXGraph::Node<int> n1("1", 1), n2("2", 2), n3("3", 3);
  CXXGraph::DirectedWeightedEdge<int> e1("1", n1, n2, 2.0);
  CXXGraph::DirectedWeightedEdge<int> e2("2", n2, n3, 3.0);
  CXXGraph::DirectedWeightedEdge<int> e3("3", n1, n3, 9.0);
  CXXGraph::T_EdgeSet<int> es;
  es.insert(make_shared<CXXGraph::DirectedWeightedEdge<int>>(e1));
  es.insert(make_shared<CXXGraph::DirectedWeightedEdge<int>>(e2));
  es.insert(make_shared<CXXGraph::DirectedWeightedEdge<int>>(e3));
  CXXGraph::Graph<int> g(es);

  auto serial = g.floydWarshall();
  auto parallel = g.floydWarshall_parallel();

  ASSERT_EQ(serial.success, parallel.success);
  ASSERT_EQ(serial.negativeCycle, parallel.negativeCycle);
  ASSERT_TRUE(fwResultsEqual(serial, parallel));
}

TEST(FWParallelTest, matches_serial_on_negative_cycle_graph) {
  CXXGraph::Node<int> n0("0", 0), n1("1", 1), n2("2", 2);
  CXXGraph::DirectedWeightedEdge<int> e1("1", n0, n1, 2.0);
  CXXGraph::DirectedWeightedEdge<int> e2("2", n1, n2, 3.0);
  CXXGraph::DirectedWeightedEdge<int> e3("3", n2, n0, -7.0);
  CXXGraph::T_EdgeSet<int> es;
  es.insert(make_shared<CXXGraph::DirectedWeightedEdge<int>>(e1));
  es.insert(make_shared<CXXGraph::DirectedWeightedEdge<int>>(e2));
  es.insert(make_shared<CXXGraph::DirectedWeightedEdge<int>>(e3));
  CXXGraph::Graph<int> g(es);

  auto serial = g.floydWarshall();
  auto parallel = g.floydWarshall_parallel();
  ASSERT_EQ(serial.negativeCycle, parallel.negativeCycle);
  ASSERT_EQ(serial.success, parallel.success);
}

// Larger random graph: 20 nodes, 60 directed weighted edges
TEST(FWParallelTest, matches_serial_on_random_20_node_graph) {
  std::mt19937 rng(42);
  std::uniform_int_distribution<int> nodeDist(0, 19);
  std::uniform_real_distribution<double> wDist(0.5, 20.0);

  const int N = 20;
  std::vector<CXXGraph::Node<int>> nodes;
  nodes.reserve(N);
  for (int i = 0; i < N; ++i) nodes.emplace_back(std::to_string(i), i);

  CXXGraph::T_EdgeSet<int> es;
  int edgeCounter = 0;
  while (static_cast<int>(es.size()) < 60) {
    int u = nodeDist(rng), v = nodeDist(rng);
    if (u == v) continue;
    double w = wDist(rng);
    es.insert(make_shared<CXXGraph::DirectedWeightedEdge<int>>(
        std::to_string(edgeCounter++), nodes[u], nodes[v], w));
  }

  CXXGraph::Graph<int> g(es);
  auto serial = g.floydWarshall();
  auto parallel = g.floydWarshall_parallel();

  ASSERT_EQ(serial.success, parallel.success);
  ASSERT_EQ(serial.negativeCycle, parallel.negativeCycle);
  if (serial.success && !serial.negativeCycle) {
    ASSERT_TRUE(fwResultsEqual(serial, parallel));
  }
}

// ============================================================================
//  bellmanford_parallel
// ============================================================================

// ── Error paths ──────────────────────────────────────────────────────────────

TEST(BFParallelTest, fails_on_unweighted_edge) {
  CXXGraph::Node<int> n1("1", 1), n2("2", 2), n3("3", 3);
  CXXGraph::DirectedWeightedEdge<int> e1("1", n1, n2, 1.0);
  CXXGraph::DirectedEdge<int> e2("2", n2, n3);
  CXXGraph::T_EdgeSet<int> es;
  es.insert(make_shared<CXXGraph::DirectedWeightedEdge<int>>(e1));
  es.insert(make_shared<CXXGraph::DirectedEdge<int>>(e2));
  CXXGraph::Graph<int> g(es);

  auto res = g.bellmanford_parallel(n1, n3);
  ASSERT_FALSE(res.success);
  ASSERT_EQ(res.errorMessage, CXXGraph::ERR_NO_WEIGHTED_EDGE);
}

TEST(BFParallelTest, fails_when_source_not_in_graph) {
  CXXGraph::Node<int> n1("1", 1), n2("2", 2), n3("3", 3);
  CXXGraph::DirectedWeightedEdge<int> e("1", n1, n2, 1.0);
  CXXGraph::T_EdgeSet<int> es;
  es.insert(make_shared<CXXGraph::DirectedWeightedEdge<int>>(e));
  CXXGraph::Graph<int> g(es);

  auto res = g.bellmanford_parallel(n3, n1);  // n3 not in graph
  ASSERT_FALSE(res.success);
  ASSERT_EQ(res.errorMessage, CXXGraph::ERR_SOURCE_NODE_NOT_IN_GRAPH);
}

TEST(BFParallelTest, fails_when_target_not_in_graph) {
  CXXGraph::Node<int> n1("1", 1), n2("2", 2), n3("3", 3);
  CXXGraph::DirectedWeightedEdge<int> e("1", n1, n2, 1.0);
  CXXGraph::T_EdgeSet<int> es;
  es.insert(make_shared<CXXGraph::DirectedWeightedEdge<int>>(e));
  CXXGraph::Graph<int> g(es);

  auto res = g.bellmanford_parallel(n1, n3);  // n3 not in graph
  ASSERT_FALSE(res.success);
  ASSERT_EQ(res.errorMessage, CXXGraph::ERR_TARGET_NODE_NOT_IN_GRAPH);
}

TEST(BFParallelTest, fails_when_target_not_reachable) {
  CXXGraph::Node<int> n1("1", 1), n2("2", 2), n3("3", 3);
  CXXGraph::DirectedWeightedEdge<int> e1("1", n1, n2, 1.0);
  CXXGraph::DirectedWeightedEdge<int> e2("2", n3, n2, 1.0);
  CXXGraph::T_EdgeSet<int> es;
  es.insert(make_shared<CXXGraph::DirectedWeightedEdge<int>>(e1));
  es.insert(make_shared<CXXGraph::DirectedWeightedEdge<int>>(e2));
  CXXGraph::Graph<int> g(es);

  auto res = g.bellmanford_parallel(n1, n3);  // n3 not reachable from n1
  ASSERT_FALSE(res.success);
  ASSERT_EQ(res.errorMessage, CXXGraph::ERR_TARGET_NODE_NOT_REACHABLE);
  ASSERT_EQ(res.result, -1);
}

// ── Known-answer tests
// ────────────────────────────────────────────────────────

// Linear chain: 1→2 (w=4), 2→3 (w=3)   dist(1,3) = 7
TEST(BFParallelTest, linear_chain_correct_distance) {
  CXXGraph::Node<int> n1("1", 1), n2("2", 2), n3("3", 3);
  CXXGraph::DirectedWeightedEdge<int> e1("1", n1, n2, 4.0);
  CXXGraph::DirectedWeightedEdge<int> e2("2", n2, n3, 3.0);
  CXXGraph::T_EdgeSet<int> es;
  es.insert(make_shared<CXXGraph::DirectedWeightedEdge<int>>(e1));
  es.insert(make_shared<CXXGraph::DirectedWeightedEdge<int>>(e2));
  CXXGraph::Graph<int> g(es);

  auto res = g.bellmanford_parallel(n1, n3);
  ASSERT_TRUE(res.success);
  ASSERT_FALSE(res.negativeCycle);
  ASSERT_EQ(res.errorMessage, "");
  ASSERT_DOUBLE_EQ(res.result, 7.0);
}

// Source == target distance is 0
TEST(BFParallelTest, source_equals_target_is_zero) {
  CXXGraph::Node<int> n1("1", 1), n2("2", 2);
  CXXGraph::DirectedWeightedEdge<int> e("1", n1, n2, 5.0);
  CXXGraph::T_EdgeSet<int> es;
  es.insert(make_shared<CXXGraph::DirectedWeightedEdge<int>>(e));
  CXXGraph::Graph<int> g(es);

  auto res = g.bellmanford_parallel(n1, n1);
  ASSERT_TRUE(res.success);
  ASSERT_DOUBLE_EQ(res.result, 0.0);
}

// Graph with a shortcut: 1→2 (w=10), 1→3 (w=1), 3→2 (w=1) → dist = 2
TEST(BFParallelTest, picks_shorter_path_via_relay) {
  CXXGraph::Node<int> n1("1", 1), n2("2", 2), n3("3", 3);
  CXXGraph::DirectedWeightedEdge<int> e1("1", n1, n2, 10.0);
  CXXGraph::DirectedWeightedEdge<int> e2("2", n1, n3, 1.0);
  CXXGraph::DirectedWeightedEdge<int> e3("3", n3, n2, 1.0);
  CXXGraph::T_EdgeSet<int> es;
  es.insert(make_shared<CXXGraph::DirectedWeightedEdge<int>>(e1));
  es.insert(make_shared<CXXGraph::DirectedWeightedEdge<int>>(e2));
  es.insert(make_shared<CXXGraph::DirectedWeightedEdge<int>>(e3));
  CXXGraph::Graph<int> g(es);

  auto res = g.bellmanford_parallel(n1, n2);
  ASSERT_TRUE(res.success);
  ASSERT_FALSE(res.negativeCycle);
  ASSERT_DOUBLE_EQ(res.result, 2.0);
}

// Negative-weight edge (non-cycle): 1→2 (w=4), 2→3 (w=-2) → dist(1,3) = 2
TEST(BFParallelTest, handles_negative_weight_no_cycle) {
  CXXGraph::Node<int> n1("1", 1), n2("2", 2), n3("3", 3);
  CXXGraph::DirectedWeightedEdge<int> e1("1", n1, n2, 4.0);
  CXXGraph::DirectedWeightedEdge<int> e2("2", n2, n3, -2.0);
  CXXGraph::T_EdgeSet<int> es;
  es.insert(make_shared<CXXGraph::DirectedWeightedEdge<int>>(e1));
  es.insert(make_shared<CXXGraph::DirectedWeightedEdge<int>>(e2));
  CXXGraph::Graph<int> g(es);

  auto res = g.bellmanford_parallel(n1, n3);
  ASSERT_TRUE(res.success);
  ASSERT_FALSE(res.negativeCycle);
  ASSERT_DOUBLE_EQ(res.result, 2.0);
}

// Negative cycle: 0→1 (+2), 1→2 (+3), 2→0 (-7)
TEST(BFParallelTest, detects_negative_cycle) {
  CXXGraph::Node<int> n0("0", 0), n1("1", 1), n2("2", 2);
  CXXGraph::DirectedWeightedEdge<int> e1("1", n0, n1, 2.0);
  CXXGraph::DirectedWeightedEdge<int> e2("2", n1, n2, 3.0);
  CXXGraph::DirectedWeightedEdge<int> e3("3", n2, n0, -7.0);
  CXXGraph::T_EdgeSet<int> es;
  es.insert(make_shared<CXXGraph::DirectedWeightedEdge<int>>(e1));
  es.insert(make_shared<CXXGraph::DirectedWeightedEdge<int>>(e2));
  es.insert(make_shared<CXXGraph::DirectedWeightedEdge<int>>(e3));
  CXXGraph::Graph<int> g(es);

  auto res = g.bellmanford_parallel(n0, n2);
  ASSERT_TRUE(res.success);
  ASSERT_TRUE(res.negativeCycle);
}

// 5-node graph with multiple paths; known best distance
// 1→2(w=6), 1→3(w=5), 1→4(w=5), 2→5(w=-1), 3→2(w=-2), 4→3(w=-1), 5→4(w=3)
// Canonical textbook Bellman-Ford example (CLRS 4th, Fig. 22.4)
TEST(BFParallelTest, five_node_clrs_example) {
  CXXGraph::Node<int> s("s", 0), t("t", 1), x("x", 2), y("y", 3), z("z", 4);
  CXXGraph::DirectedWeightedEdge<int> e1("st", s, t, 6.0);
  CXXGraph::DirectedWeightedEdge<int> e2("sy", s, y, 7.0);
  CXXGraph::DirectedWeightedEdge<int> e3("tx", t, x, 5.0);
  CXXGraph::DirectedWeightedEdge<int> e4("ty", t, y, 8.0);
  CXXGraph::DirectedWeightedEdge<int> e5("tz", t, z, -4.0);
  CXXGraph::DirectedWeightedEdge<int> e6("xt", x, t, -2.0);
  CXXGraph::DirectedWeightedEdge<int> e7("yx", y, x, -3.0);
  CXXGraph::DirectedWeightedEdge<int> e8("yz", y, z, 9.0);
  CXXGraph::DirectedWeightedEdge<int> e9("zx", z, x, 7.0);
  CXXGraph::T_EdgeSet<int> es;
  es.insert(make_shared<CXXGraph::DirectedWeightedEdge<int>>(e1));
  es.insert(make_shared<CXXGraph::DirectedWeightedEdge<int>>(e2));
  es.insert(make_shared<CXXGraph::DirectedWeightedEdge<int>>(e3));
  es.insert(make_shared<CXXGraph::DirectedWeightedEdge<int>>(e4));
  es.insert(make_shared<CXXGraph::DirectedWeightedEdge<int>>(e5));
  es.insert(make_shared<CXXGraph::DirectedWeightedEdge<int>>(e6));
  es.insert(make_shared<CXXGraph::DirectedWeightedEdge<int>>(e7));
  es.insert(make_shared<CXXGraph::DirectedWeightedEdge<int>>(e8));
  es.insert(make_shared<CXXGraph::DirectedWeightedEdge<int>>(e9));
  CXXGraph::Graph<int> g(es);

  // dist(s, t) = 2  (s→y→x→t)
  auto res = g.bellmanford_parallel(s, t);
  ASSERT_TRUE(res.success);
  ASSERT_FALSE(res.negativeCycle);
  ASSERT_DOUBLE_EQ(res.result, 2.0);

  // dist(s, z) = -2  (s→y→x→t→z)
  auto res2 = g.bellmanford_parallel(s, z);
  ASSERT_TRUE(res2.success);
  ASSERT_FALSE(res2.negativeCycle);
  ASSERT_DOUBLE_EQ(res2.result, -2.0);
}

// ── Serial/parallel equivalence
// ───────────────────────────────────────────────

TEST(BFParallelTest, matches_serial_on_linear_chain) {
  CXXGraph::Node<int> n1("1", 1), n2("2", 2), n3("3", 3);
  CXXGraph::DirectedWeightedEdge<int> e1("1", n1, n2, 4.0);
  CXXGraph::DirectedWeightedEdge<int> e2("2", n2, n3, 3.0);
  CXXGraph::T_EdgeSet<int> es;
  es.insert(make_shared<CXXGraph::DirectedWeightedEdge<int>>(e1));
  es.insert(make_shared<CXXGraph::DirectedWeightedEdge<int>>(e2));
  CXXGraph::Graph<int> g(es);

  auto serial = g.bellmanford(n1, n3);
  auto parallel = g.bellmanford_parallel(n1, n3);

  ASSERT_EQ(serial.success, parallel.success);
  ASSERT_EQ(serial.negativeCycle, parallel.negativeCycle);
  ASSERT_DOUBLE_EQ(serial.result, parallel.result);
}

TEST(BFParallelTest, matches_serial_on_negative_cycle) {
  CXXGraph::Node<int> n0("0", 0), n1("1", 1), n2("2", 2);
  CXXGraph::DirectedWeightedEdge<int> e1("1", n0, n1, 2.0);
  CXXGraph::DirectedWeightedEdge<int> e2("2", n1, n2, 3.0);
  CXXGraph::DirectedWeightedEdge<int> e3("3", n2, n0, -7.0);
  CXXGraph::T_EdgeSet<int> es;
  es.insert(make_shared<CXXGraph::DirectedWeightedEdge<int>>(e1));
  es.insert(make_shared<CXXGraph::DirectedWeightedEdge<int>>(e2));
  es.insert(make_shared<CXXGraph::DirectedWeightedEdge<int>>(e3));
  CXXGraph::Graph<int> g(es);

  auto serial = g.bellmanford(n0, n2);
  auto parallel = g.bellmanford_parallel(n0, n2);

  ASSERT_EQ(serial.success, parallel.success);
  ASSERT_EQ(serial.negativeCycle, parallel.negativeCycle);
}

// Random 15-node graph, 40 edges, positive weights only (no cycle risk)
TEST(BFParallelTest, matches_serial_on_random_15_node_graph) {
  std::mt19937 rng(7);
  std::uniform_int_distribution<int> nodeDist(0, 14);
  std::uniform_real_distribution<double> wDist(0.1, 15.0);

  const int N = 15;
  std::vector<CXXGraph::Node<int>> nodes;
  nodes.reserve(N);
  for (int i = 0; i < N; ++i) nodes.emplace_back(std::to_string(i), i);

  CXXGraph::T_EdgeSet<int> es;
  // chain ensures reachability
  for (int i = 0; i < N - 1; ++i)
    es.insert(make_shared<CXXGraph::DirectedWeightedEdge<int>>(
        "chain" + std::to_string(i), nodes[i], nodes[i + 1], wDist(rng)));

  int counter = N;
  while (static_cast<int>(es.size()) < 40) {
    int u = nodeDist(rng), v = nodeDist(rng);
    if (u == v) continue;
    es.insert(make_shared<CXXGraph::DirectedWeightedEdge<int>>(
        std::to_string(counter++), nodes[u], nodes[v], wDist(rng)));
  }

  CXXGraph::Graph<int> g(es);
  auto serial = g.bellmanford(nodes[0], nodes[N - 1]);
  auto parallel = g.bellmanford_parallel(nodes[0], nodes[N - 1]);

  ASSERT_EQ(serial.success, parallel.success);
  ASSERT_EQ(serial.negativeCycle, parallel.negativeCycle);
  if (serial.success && !serial.negativeCycle) {
    ASSERT_NEAR(serial.result, parallel.result, 1e-9);
  }
}

// ============================================================================
//  kruskal_parallel
// ============================================================================

// ── Error paths ──────────────────────────────────────────────────────────────

TEST(KruskalParallelTest, fails_on_directed_graph) {
  CXXGraph::Node<int> n1("1", 1), n2("2", 2), n3("3", 3);
  CXXGraph::DirectedWeightedEdge<int> e1("1", n1, n2, 1.0);
  CXXGraph::DirectedWeightedEdge<int> e2("2", n2, n3, 1.0);
  CXXGraph::T_EdgeSet<int> es;
  es.insert(make_shared<CXXGraph::DirectedWeightedEdge<int>>(e1));
  es.insert(make_shared<CXXGraph::DirectedWeightedEdge<int>>(e2));
  CXXGraph::Graph<int> g(es);

  auto res = g.kruskal_parallel();
  ASSERT_FALSE(res.success);
  ASSERT_EQ(res.errorMessage, CXXGraph::ERR_DIR_GRAPH);
}

TEST(KruskalParallelTest, fails_on_unweighted_edge) {
  CXXGraph::Node<int> n1("1", 1), n2("2", 2);
  CXXGraph::UndirectedEdge<int> e("1", n1, n2);
  CXXGraph::T_EdgeSet<int> es;
  es.insert(make_shared<CXXGraph::UndirectedEdge<int>>(e));
  CXXGraph::Graph<int> g(es);

  auto res = g.kruskal_parallel();
  ASSERT_FALSE(res.success);
  ASSERT_EQ(res.errorMessage, CXXGraph::ERR_NO_WEIGHTED_EDGE);
}

// ── Known-answer tests
// ────────────────────────────────────────────────────────

// Two nodes, one edge: MST IS the edge
TEST(KruskalParallelTest, two_node_single_edge) {
  CXXGraph::Node<int> n1("1", 1), n2("2", 2);
  CXXGraph::UndirectedWeightedEdge<int> e("1", n1, n2, 5.0);
  CXXGraph::T_EdgeSet<int> es;
  es.insert(make_shared<CXXGraph::UndirectedWeightedEdge<int>>(e));
  CXXGraph::Graph<int> g(es);

  auto res = g.kruskal_parallel();
  ASSERT_TRUE(res.success);
  ASSERT_EQ(res.errorMessage, "");
  ASSERT_EQ(res.mst.size(), 1u);
  ASSERT_DOUBLE_EQ(res.mstCost, 5.0);
}

// Four-node complete undirected graph; MST must have exactly 3 edges and
// cost = sum of 3 cheapest non-redundant edges
// Edges: 1-2(1), 1-3(3), 1-4(4), 2-3(2), 2-4(5), 3-4(6)
// MST: 1-2(1), 2-3(2), 1-3(3)? No — Kruskal picks 1-2(1), 2-3(2), 1-3(3)
//      but 1-3 would form cycle 1-2-3-1 — so it picks 1-4(4) instead.
// MST: {1-2, 2-3, 1-4}  cost = 1+2+4 = 7
TEST(KruskalParallelTest, four_node_complete_graph_mst_cost) {
  CXXGraph::Node<int> n1("1", 1), n2("2", 2), n3("3", 3), n4("4", 4);
  CXXGraph::UndirectedWeightedEdge<int> e12("12", n1, n2, 1.0);
  CXXGraph::UndirectedWeightedEdge<int> e13("13", n1, n3, 3.0);
  CXXGraph::UndirectedWeightedEdge<int> e14("14", n1, n4, 4.0);
  CXXGraph::UndirectedWeightedEdge<int> e23("23", n2, n3, 2.0);
  CXXGraph::UndirectedWeightedEdge<int> e24("24", n2, n4, 5.0);
  CXXGraph::UndirectedWeightedEdge<int> e34("34", n3, n4, 6.0);
  CXXGraph::T_EdgeSet<int> es;
  es.insert(make_shared<CXXGraph::UndirectedWeightedEdge<int>>(e12));
  es.insert(make_shared<CXXGraph::UndirectedWeightedEdge<int>>(e13));
  es.insert(make_shared<CXXGraph::UndirectedWeightedEdge<int>>(e14));
  es.insert(make_shared<CXXGraph::UndirectedWeightedEdge<int>>(e23));
  es.insert(make_shared<CXXGraph::UndirectedWeightedEdge<int>>(e24));
  es.insert(make_shared<CXXGraph::UndirectedWeightedEdge<int>>(e34));
  CXXGraph::Graph<int> g(es);

  auto res = g.kruskal_parallel();
  ASSERT_TRUE(res.success);
  ASSERT_EQ(res.errorMessage, "");
  ASSERT_EQ(res.mst.size(), g.getNodeSet().size() - 1);  // 3 edges for 4 nodes
  ASSERT_DOUBLE_EQ(res.mstCost, 7.0);
}

// Standard 7-node textbook example (GATE CSE)
// Identical to KruskalTest::test_2 from the existing suite (mstCost=99)
TEST(KruskalParallelTest, seven_node_textbook_gate_example) {
  CXXGraph::Node<int> n1("1", 1), n2("2", 2), n3("3", 3), n4("4", 4),
      n5("5", 5), n6("6", 6), n7("7", 7);
  CXXGraph::UndirectedWeightedEdge<int> e1("1", n1, n2, 28);
  CXXGraph::UndirectedWeightedEdge<int> e2("2", n1, n6, 10);
  CXXGraph::UndirectedWeightedEdge<int> e3("3", n2, n7, 14);
  CXXGraph::UndirectedWeightedEdge<int> e4("4", n2, n3, 16);
  CXXGraph::UndirectedWeightedEdge<int> e5("5", n6, n5, 25);
  CXXGraph::UndirectedWeightedEdge<int> e6("6", n7, n5, 24);
  CXXGraph::UndirectedWeightedEdge<int> e7("7", n7, n4, 18);
  CXXGraph::UndirectedWeightedEdge<int> e8("8", n5, n4, 22);
  CXXGraph::UndirectedWeightedEdge<int> e9("9", n4, n3, 12);
  CXXGraph::T_EdgeSet<int> es;
  es.insert(make_shared<CXXGraph::UndirectedWeightedEdge<int>>(e1));
  es.insert(make_shared<CXXGraph::UndirectedWeightedEdge<int>>(e2));
  es.insert(make_shared<CXXGraph::UndirectedWeightedEdge<int>>(e3));
  es.insert(make_shared<CXXGraph::UndirectedWeightedEdge<int>>(e4));
  es.insert(make_shared<CXXGraph::UndirectedWeightedEdge<int>>(e5));
  es.insert(make_shared<CXXGraph::UndirectedWeightedEdge<int>>(e6));
  es.insert(make_shared<CXXGraph::UndirectedWeightedEdge<int>>(e7));
  es.insert(make_shared<CXXGraph::UndirectedWeightedEdge<int>>(e8));
  es.insert(make_shared<CXXGraph::UndirectedWeightedEdge<int>>(e9));
  CXXGraph::Graph<int> g(es);

  auto res = g.kruskal_parallel();
  ASSERT_TRUE(res.success);
  ASSERT_EQ(res.mst.size(), g.getNodeSet().size() - 1);
  ASSERT_DOUBLE_EQ(res.mstCost, 99.0);
  ASSERT_EQ(res.errorMessage, "");
}

// MST edges must form a spanning tree: no node should be missing
TEST(KruskalParallelTest, mst_covers_all_nodes) {
  CXXGraph::Node<int> n1("1", 1), n2("2", 2), n3("3", 3), n4("4", 4),
      n5("5", 5);
  CXXGraph::UndirectedWeightedEdge<int> e1("1", n1, n2, 2.0);
  CXXGraph::UndirectedWeightedEdge<int> e2("2", n2, n3, 3.0);
  CXXGraph::UndirectedWeightedEdge<int> e3("3", n3, n4, 1.0);
  CXXGraph::UndirectedWeightedEdge<int> e4("4", n4, n5, 4.0);
  CXXGraph::UndirectedWeightedEdge<int> e5("5", n1, n5, 10.0);
  CXXGraph::UndirectedWeightedEdge<int> e6("6", n2, n4, 5.0);
  CXXGraph::T_EdgeSet<int> es;
  es.insert(make_shared<CXXGraph::UndirectedWeightedEdge<int>>(e1));
  es.insert(make_shared<CXXGraph::UndirectedWeightedEdge<int>>(e2));
  es.insert(make_shared<CXXGraph::UndirectedWeightedEdge<int>>(e3));
  es.insert(make_shared<CXXGraph::UndirectedWeightedEdge<int>>(e4));
  es.insert(make_shared<CXXGraph::UndirectedWeightedEdge<int>>(e5));
  es.insert(make_shared<CXXGraph::UndirectedWeightedEdge<int>>(e6));
  CXXGraph::Graph<int> g(es);

  auto res = g.kruskal_parallel();
  ASSERT_TRUE(res.success);
  ASSERT_EQ(res.mst.size(), 4u);  // V-1 = 5-1 = 4

  // Every node must appear in at least one MST edge
  std::set<std::string> nodesCovered;
  for (const auto& [u, v] : res.mst) {
    nodesCovered.insert(u);
    nodesCovered.insert(v);
  }
  ASSERT_EQ(nodesCovered.size(), 5u);
}

// ── Serial/parallel equivalence
// ───────────────────────────────────────────────

TEST(KruskalParallelTest, matches_serial_cost_on_four_node_graph) {
  CXXGraph::Node<int> n1("1", 1), n2("2", 2), n3("3", 3), n4("4", 4);
  CXXGraph::UndirectedWeightedEdge<int> e12("12", n1, n2, 1.0);
  CXXGraph::UndirectedWeightedEdge<int> e13("13", n1, n3, 3.0);
  CXXGraph::UndirectedWeightedEdge<int> e14("14", n1, n4, 4.0);
  CXXGraph::UndirectedWeightedEdge<int> e23("23", n2, n3, 2.0);
  CXXGraph::UndirectedWeightedEdge<int> e24("24", n2, n4, 5.0);
  CXXGraph::UndirectedWeightedEdge<int> e34("34", n3, n4, 6.0);
  CXXGraph::T_EdgeSet<int> es;
  es.insert(make_shared<CXXGraph::UndirectedWeightedEdge<int>>(e12));
  es.insert(make_shared<CXXGraph::UndirectedWeightedEdge<int>>(e13));
  es.insert(make_shared<CXXGraph::UndirectedWeightedEdge<int>>(e14));
  es.insert(make_shared<CXXGraph::UndirectedWeightedEdge<int>>(e23));
  es.insert(make_shared<CXXGraph::UndirectedWeightedEdge<int>>(e24));
  es.insert(make_shared<CXXGraph::UndirectedWeightedEdge<int>>(e34));
  CXXGraph::Graph<int> g(es);

  auto serial = g.kruskal();
  auto parallel = g.kruskal_parallel();

  ASSERT_EQ(serial.success, parallel.success);
  ASSERT_DOUBLE_EQ(serial.mstCost, parallel.mstCost);
  ASSERT_EQ(serial.mst.size(), parallel.mst.size());
}

// Random 25-node undirected graph: MST cost must match serial exactly
TEST(KruskalParallelTest, matches_serial_cost_on_random_25_node_graph) {
  std::mt19937 rng(99);
  std::uniform_int_distribution<int> nodeDist(0, 24);
  std::uniform_real_distribution<double> wDist(1.0, 100.0);

  const int N = 25;
  std::vector<CXXGraph::Node<int>> nodes;
  nodes.reserve(N);
  for (int i = 0; i < N; ++i) nodes.emplace_back(std::to_string(i), i);

  CXXGraph::T_EdgeSet<int> es;
  // Chain to guarantee connectivity
  for (int i = 0; i < N - 1; ++i)
    es.insert(make_shared<CXXGraph::UndirectedWeightedEdge<int>>(
        "c" + std::to_string(i), nodes[i], nodes[i + 1], wDist(rng)));

  int counter = N;
  while (static_cast<int>(es.size()) < 80) {
    int u = nodeDist(rng), v = nodeDist(rng);
    if (u == v) continue;
    es.insert(make_shared<CXXGraph::UndirectedWeightedEdge<int>>(
        std::to_string(counter++), nodes[u], nodes[v], wDist(rng)));
  }

  CXXGraph::Graph<int> g(es);
  auto serial = g.kruskal();
  auto parallel = g.kruskal_parallel();

  ASSERT_EQ(serial.success, parallel.success);
  ASSERT_EQ(serial.mst.size(), parallel.mst.size());
  ASSERT_NEAR(serial.mstCost, parallel.mstCost, 1e-9);
}

// ============================================================================
//  welshPowellColoring_parallel
// ============================================================================

// ── Error / trivial paths ────────────────────────────────────────────────────

TEST(WPParallelTest, empty_graph_returns_empty_coloring) {
  CXXGraph::T_EdgeSet<int> es;
  CXXGraph::Graph<int> g(es);

  auto res = g.welshPowellColoring_parallel();
  ASSERT_TRUE(res.empty());
}

TEST(WPParallelTest, single_node_gets_color_1) {
  // Isolated node added directly to a graph with no edges
  CXXGraph::T_EdgeSet<int> es;
  CXXGraph::Graph<int> g(es);
  g.addNode(make_shared<CXXGraph::Node<int>>("solo", 1));

  auto res = g.welshPowellColoring_parallel();
  ASSERT_EQ(res.size(), 1u);
  ASSERT_EQ(maxColor(res), 1);
}

// ── Known-answer tests
// ────────────────────────────────────────────────────────

// One edge, two nodes: chromatic number = 2
TEST(WPParallelTest, one_edge_chromatic_number_is_2) {
  CXXGraph::Node<int> n1("1", 1), n2("2", 2);
  CXXGraph::UndirectedWeightedEdge<int> e("1", n1, n2, 1.0);
  CXXGraph::T_EdgeSet<int> es;
  es.insert(make_shared<CXXGraph::UndirectedWeightedEdge<int>>(e));
  CXXGraph::Graph<int> g(es);

  auto res = g.welshPowellColoring_parallel();
  ASSERT_EQ(maxColor(res), 2);
  ASSERT_TRUE(coloringIsValid(g, res));
}

// K3 (triangle): chromatic number = 3
TEST(WPParallelTest, triangle_chromatic_number_is_3) {
  CXXGraph::Node<int> n1("1", 1), n2("2", 2), n3("3", 3);
  CXXGraph::UndirectedEdge<int> e1("1", n1, n2);
  CXXGraph::UndirectedEdge<int> e2("2", n2, n3);
  CXXGraph::UndirectedEdge<int> e3("3", n3, n1);
  CXXGraph::T_EdgeSet<int> es;
  es.insert(make_shared<CXXGraph::UndirectedEdge<int>>(e1));
  es.insert(make_shared<CXXGraph::UndirectedEdge<int>>(e2));
  es.insert(make_shared<CXXGraph::UndirectedEdge<int>>(e3));
  CXXGraph::Graph<int> g(es);

  auto res = g.welshPowellColoring_parallel();
  ASSERT_EQ(maxColor(res), 3);
  ASSERT_TRUE(coloringIsValid(g, res));
}

// K4 (complete 4-node graph): chromatic number = 4
TEST(WPParallelTest, k4_chromatic_number_is_4) {
  CXXGraph::Node<int> n1("1", 1), n2("2", 2), n3("3", 3), n4("4", 4);
  CXXGraph::UndirectedEdge<int> e12("12", n1, n2);
  CXXGraph::UndirectedEdge<int> e13("13", n1, n3);
  CXXGraph::UndirectedEdge<int> e14("14", n1, n4);
  CXXGraph::UndirectedEdge<int> e23("23", n2, n3);
  CXXGraph::UndirectedEdge<int> e24("24", n2, n4);
  CXXGraph::UndirectedEdge<int> e34("34", n3, n4);
  CXXGraph::T_EdgeSet<int> es;
  es.insert(make_shared<CXXGraph::UndirectedEdge<int>>(e12));
  es.insert(make_shared<CXXGraph::UndirectedEdge<int>>(e13));
  es.insert(make_shared<CXXGraph::UndirectedEdge<int>>(e14));
  es.insert(make_shared<CXXGraph::UndirectedEdge<int>>(e23));
  es.insert(make_shared<CXXGraph::UndirectedEdge<int>>(e24));
  es.insert(make_shared<CXXGraph::UndirectedEdge<int>>(e34));
  CXXGraph::Graph<int> g(es);

  auto res = g.welshPowellColoring_parallel();
  ASSERT_EQ(maxColor(res), 4);
  ASSERT_TRUE(coloringIsValid(g, res));
}

// Even cycle C4: bipartite → chromatic number = 2
TEST(WPParallelTest, even_cycle_bipartite_chromatic_number_is_2) {
  CXXGraph::Node<int> n1("1", 1), n2("2", 2), n3("3", 3), n4("4", 4);
  CXXGraph::UndirectedEdge<int> e1("1", n1, n2);
  CXXGraph::UndirectedEdge<int> e2("2", n2, n3);
  CXXGraph::UndirectedEdge<int> e3("3", n3, n4);
  CXXGraph::UndirectedEdge<int> e4("4", n4, n1);
  CXXGraph::T_EdgeSet<int> es;
  es.insert(make_shared<CXXGraph::UndirectedEdge<int>>(e1));
  es.insert(make_shared<CXXGraph::UndirectedEdge<int>>(e2));
  es.insert(make_shared<CXXGraph::UndirectedEdge<int>>(e3));
  es.insert(make_shared<CXXGraph::UndirectedEdge<int>>(e4));
  CXXGraph::Graph<int> g(es);

  auto res = g.welshPowellColoring_parallel();
  ASSERT_EQ(maxColor(res), 2);
  ASSERT_TRUE(coloringIsValid(g, res));
}

// Star graph K1,4: center connected to 4 leaves → chromatic number = 2
TEST(WPParallelTest, star_graph_chromatic_number_is_2) {
  CXXGraph::Node<int> center("c", 0), l1("l1", 1), l2("l2", 2), l3("l3", 3),
      l4("l4", 4);
  CXXGraph::UndirectedEdge<int> e1("1", center, l1);
  CXXGraph::UndirectedEdge<int> e2("2", center, l2);
  CXXGraph::UndirectedEdge<int> e3("3", center, l3);
  CXXGraph::UndirectedEdge<int> e4("4", center, l4);
  CXXGraph::T_EdgeSet<int> es;
  es.insert(make_shared<CXXGraph::UndirectedEdge<int>>(e1));
  es.insert(make_shared<CXXGraph::UndirectedEdge<int>>(e2));
  es.insert(make_shared<CXXGraph::UndirectedEdge<int>>(e3));
  es.insert(make_shared<CXXGraph::UndirectedEdge<int>>(e4));
  CXXGraph::Graph<int> g(es);

  auto res = g.welshPowellColoring_parallel();
  ASSERT_EQ(maxColor(res), 2);
  ASSERT_TRUE(coloringIsValid(g, res));
}

// Petersen graph: 10 nodes, 3-regular, chromatic number = 3
TEST(WPParallelTest, petersen_graph_chromatic_number_is_3) {
  std::vector<CXXGraph::Node<int>> n;
  for (int i = 0; i < 10; ++i) n.emplace_back(std::to_string(i), i);

  // Outer pentagon
  CXXGraph::T_EdgeSet<int> es;
  auto addE = [&](int u, int v) {
    static int cnt = 0;
    es.insert(make_shared<CXXGraph::UndirectedEdge<int>>(std::to_string(cnt++),
                                                         n[u], n[v]));
  };
  addE(0, 1);
  addE(1, 2);
  addE(2, 3);
  addE(3, 4);
  addE(4, 0);
  // Inner pentagram (0-5, 1-6, 2-7, 3-8, 4-9)
  addE(0, 5);
  addE(1, 6);
  addE(2, 7);
  addE(3, 8);
  addE(4, 9);
  // Inner connections (5-7, 7-9, 9-6, 6-8, 8-5)
  addE(5, 7);
  addE(7, 9);
  addE(9, 6);
  addE(6, 8);
  addE(8, 5);

  CXXGraph::Graph<int> g(es);
  auto res = g.welshPowellColoring_parallel();

  ASSERT_EQ(maxColor(res), 3);
  ASSERT_TRUE(coloringIsValid(g, res));
}

// ── Validity invariant (no coloring constraints require the chromatic number
//    to be exact; Welsh-Powell is greedy and may over-color) ──────────────────

TEST(WPParallelTest, coloring_is_always_valid_on_arbitrary_graph) {
  // Path graph P6: 1-2-3-4-5-6, chromatic = 2
  CXXGraph::Node<int> n1("1", 1), n2("2", 2), n3("3", 3), n4("4", 4),
      n5("5", 5), n6("6", 6);
  CXXGraph::UndirectedEdge<int> e1("1", n1, n2), e2("2", n2, n3),
      e3("3", n3, n4), e4("4", n4, n5), e5("5", n5, n6);
  CXXGraph::T_EdgeSet<int> es;
  es.insert(make_shared<CXXGraph::UndirectedEdge<int>>(e1));
  es.insert(make_shared<CXXGraph::UndirectedEdge<int>>(e2));
  es.insert(make_shared<CXXGraph::UndirectedEdge<int>>(e3));
  es.insert(make_shared<CXXGraph::UndirectedEdge<int>>(e4));
  es.insert(make_shared<CXXGraph::UndirectedEdge<int>>(e5));
  CXXGraph::Graph<int> g(es);

  auto res = g.welshPowellColoring_parallel();
  ASSERT_TRUE(coloringIsValid(g, res));
  ASSERT_GE(maxColor(res), 2);  // at least chromatic number
}

// ── Serial/parallel equivalence
// ───────────────────────────────────────────────

// Chromatic number must match; exact color assignment may differ
// (both are correct greedy colorings, order may vary)
TEST(WPParallelTest, chromatic_number_matches_serial_on_triangle) {
  CXXGraph::Node<int> n1("1", 1), n2("2", 2), n3("3", 3);
  CXXGraph::UndirectedEdge<int> e1("1", n1, n2), e2("2", n2, n3),
      e3("3", n3, n1);
  CXXGraph::T_EdgeSet<int> es;
  es.insert(make_shared<CXXGraph::UndirectedEdge<int>>(e1));
  es.insert(make_shared<CXXGraph::UndirectedEdge<int>>(e2));
  es.insert(make_shared<CXXGraph::UndirectedEdge<int>>(e3));
  CXXGraph::Graph<int> g(es);

  auto serial = g.welshPowellColoring();
  auto parallel = g.welshPowellColoring_parallel();

  ASSERT_EQ(serial.size(), parallel.size());
  ASSERT_EQ(maxColor(serial), maxColor(parallel));
  ASSERT_TRUE(coloringIsValid(g, serial));
  ASSERT_TRUE(coloringIsValid(g, parallel));
}

TEST(WPParallelTest, chromatic_number_matches_serial_on_petersen) {
  std::vector<CXXGraph::Node<int>> n;
  for (int i = 0; i < 10; ++i) n.emplace_back(std::to_string(i), i);

  CXXGraph::T_EdgeSet<int> es;
  auto addE = [&](int u, int v) {
    static int cnt = 0;
    es.insert(make_shared<CXXGraph::UndirectedEdge<int>>(std::to_string(cnt++),
                                                         n[u], n[v]));
  };
  addE(0, 1);
  addE(1, 2);
  addE(2, 3);
  addE(3, 4);
  addE(4, 0);
  addE(0, 5);
  addE(1, 6);
  addE(2, 7);
  addE(3, 8);
  addE(4, 9);
  addE(5, 7);
  addE(7, 9);
  addE(9, 6);
  addE(6, 8);
  addE(8, 5);

  CXXGraph::Graph<int> g(es);
  auto serial = g.welshPowellColoring();
  auto parallel = g.welshPowellColoring_parallel();

  ASSERT_EQ(maxColor(serial), maxColor(parallel));
  ASSERT_TRUE(coloringIsValid(g, serial));
  ASSERT_TRUE(coloringIsValid(g, parallel));
}

// Random 30-node graph: both serial and parallel coloring must be valid
// and produce the same chromatic number
TEST(WPParallelTest, coloring_valid_and_equal_chromatic_on_random_graph) {
  std::mt19937 rng(13);
  std::uniform_int_distribution<int> nodeDist(0, 29);

  const int N = 30;
  std::vector<CXXGraph::Node<int>> nodes;
  nodes.reserve(N);
  for (int i = 0; i < N; ++i) nodes.emplace_back(std::to_string(i), i);

  CXXGraph::T_EdgeSet<int> es;
  int counter = 0;
  while (static_cast<int>(es.size()) < 50) {
    int u = nodeDist(rng), v = nodeDist(rng);
    if (u == v) continue;
    // Use min/max to avoid duplicate {u,v} / {v,u} under different ids
    std::string id =
        std::to_string(std::min(u, v)) + "_" + std::to_string(std::max(u, v));
    es.insert(make_shared<CXXGraph::UndirectedEdge<int>>(
        std::to_string(counter++), nodes[u], nodes[v]));
  }

  CXXGraph::Graph<int> g(es);
  auto serial = g.welshPowellColoring();
  auto parallel = g.welshPowellColoring_parallel();

  ASSERT_TRUE(coloringIsValid(g, serial));
  ASSERT_TRUE(coloringIsValid(g, parallel));
  ASSERT_EQ(maxColor(serial), maxColor(parallel));
}
