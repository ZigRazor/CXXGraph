#include <memory>

#include "CXXGraph/CXXGraph.hpp"
#include "gtest/gtest.h"

// Smart pointers alias
template <typename T>
using unique = std::unique_ptr<T>;
template <typename T>
using shared = std::shared_ptr<T>;

using std::make_shared;
using std::make_unique;

TEST(HopcroftKarpTest, test_simple_bipartite) {
  // complete bipartite graph K_2,2 should give maximum matching of size 2
  CXXGraph::Node<int> u1("u1", 1);
  CXXGraph::Node<int> u2("u2", 2);
  CXXGraph::Node<int> v1("v1", 3);
  CXXGraph::Node<int> v2("v2", 4);

  CXXGraph::UndirectedEdge<int> edge1("1", u1, v1);
  CXXGraph::UndirectedEdge<int> edge2("2", u1, v2);
  CXXGraph::UndirectedEdge<int> edge3("3", u2, v1);
  CXXGraph::UndirectedEdge<int> edge4("4", u2, v2);

  CXXGraph::T_EdgeSet<int> edgeSet;
  edgeSet.insert(make_shared<CXXGraph::UndirectedEdge<int>>(edge1));
  edgeSet.insert(make_shared<CXXGraph::UndirectedEdge<int>>(edge2));
  edgeSet.insert(make_shared<CXXGraph::UndirectedEdge<int>>(edge3));
  edgeSet.insert(make_shared<CXXGraph::UndirectedEdge<int>>(edge4));

  CXXGraph::Graph<int> graph(edgeSet);
  CXXGraph::HopcroftKarpResult result = graph.hopcroftKarp();

  ASSERT_TRUE(result.success);
  ASSERT_EQ(result.maxMatching, 2);
  ASSERT_EQ(result.matching.size(), 2);
  ASSERT_TRUE(result.errorMessage.empty());
}

TEST(HopcroftKarpTest, test_path_graph) {
  // path graph u1-v1-u2-v2 should give maximum matching of size 2
  CXXGraph::Node<int> u1("u1", 1);
  CXXGraph::Node<int> v1("v1", 2);
  CXXGraph::Node<int> u2("u2", 3);
  CXXGraph::Node<int> v2("v2", 4);

  CXXGraph::UndirectedEdge<int> edge1("1", u1, v1);
  CXXGraph::UndirectedEdge<int> edge2("2", v1, u2);
  CXXGraph::UndirectedEdge<int> edge3("3", u2, v2);

  CXXGraph::T_EdgeSet<int> edgeSet;
  edgeSet.insert(make_shared<CXXGraph::UndirectedEdge<int>>(edge1));
  edgeSet.insert(make_shared<CXXGraph::UndirectedEdge<int>>(edge2));
  edgeSet.insert(make_shared<CXXGraph::UndirectedEdge<int>>(edge3));

  CXXGraph::Graph<int> graph(edgeSet);
  CXXGraph::HopcroftKarpResult result = graph.hopcroftKarp();

  ASSERT_TRUE(result.success);
  ASSERT_EQ(result.maxMatching, 2);
  ASSERT_EQ(result.matching.size(), 2);
  ASSERT_TRUE(result.errorMessage.empty());
}

TEST(HopcroftKarpTest, test_single_edge) {
  // single edge should give maximum matching of size 1
  CXXGraph::Node<int> node1("1", 1);
  CXXGraph::Node<int> node2("2", 2);

  CXXGraph::UndirectedEdge<int> edge1("1", node1, node2);

  CXXGraph::T_EdgeSet<int> edgeSet;
  edgeSet.insert(make_shared<CXXGraph::UndirectedEdge<int>>(edge1));

  CXXGraph::Graph<int> graph(edgeSet);
  CXXGraph::HopcroftKarpResult result = graph.hopcroftKarp();

  ASSERT_TRUE(result.success);
  ASSERT_EQ(result.maxMatching, 1);
  ASSERT_EQ(result.matching.size(), 1);
  ASSERT_TRUE(result.errorMessage.empty());
}

TEST(HopcroftKarpTest, test_empty_graph) {
  // empty graph should be considered bipartite with 0 matching
  CXXGraph::T_EdgeSet<int> edgeSet;

  CXXGraph::Graph<int> graph(edgeSet);
  CXXGraph::HopcroftKarpResult result = graph.hopcroftKarp();

  ASSERT_TRUE(result.success);
  ASSERT_EQ(result.maxMatching, 0);
  ASSERT_TRUE(result.errorMessage.empty());
}

TEST(HopcroftKarpTest, test_single_node_graph) {
  // single node graph is also bipartite with 0 matching
  CXXGraph::Graph<int> graph;
  graph.addNode(std::make_shared<CXXGraph::Node<int>>("1", 1));

  CXXGraph::HopcroftKarpResult result = graph.hopcroftKarp();

  ASSERT_TRUE(result.success);
  ASSERT_EQ(result.maxMatching, 0);
  ASSERT_TRUE(result.errorMessage.empty());
}

TEST(HopcroftKarpTest, test_non_bipartite_graph) {
  // triangle (odd cycle) should fail as it's not bipartite
  CXXGraph::Node<int> node1("1", 1);
  CXXGraph::Node<int> node2("2", 2);
  CXXGraph::Node<int> node3("3", 3);

  CXXGraph::UndirectedEdge<int> edge1("1", node1, node2);
  CXXGraph::UndirectedEdge<int> edge2("2", node2, node3);
  CXXGraph::UndirectedEdge<int> edge3("3", node3, node1);

  CXXGraph::T_EdgeSet<int> edgeSet;
  edgeSet.insert(make_shared<CXXGraph::UndirectedEdge<int>>(edge1));
  edgeSet.insert(make_shared<CXXGraph::UndirectedEdge<int>>(edge2));
  edgeSet.insert(make_shared<CXXGraph::UndirectedEdge<int>>(edge3));

  CXXGraph::Graph<int> graph(edgeSet);
  CXXGraph::HopcroftKarpResult result = graph.hopcroftKarp();

  ASSERT_FALSE(result.success);
  ASSERT_EQ(result.maxMatching, 0);
  ASSERT_FALSE(result.errorMessage.empty());
  ASSERT_EQ(result.errorMessage, "Graph is not bipartite.");
}

TEST(HopcroftKarpTest, test_directed_graph_error) {
  // directed graph should fail as algorithm requires undirected graphs
  CXXGraph::Node<int> node1("1", 1);
  CXXGraph::Node<int> node2("2", 2);

  CXXGraph::DirectedEdge<int> edge1("1", node1, node2);

  CXXGraph::T_EdgeSet<int> edgeSet;
  edgeSet.insert(make_shared<CXXGraph::DirectedEdge<int>>(edge1));

  CXXGraph::Graph<int> graph(edgeSet);
  CXXGraph::HopcroftKarpResult result = graph.hopcroftKarp();

  ASSERT_FALSE(result.success);
  ASSERT_EQ(result.maxMatching, 0);
  ASSERT_FALSE(result.errorMessage.empty());
  ASSERT_EQ(result.errorMessage, "Graph is directed");
}

TEST(HopcroftKarpTest, test_augmenting_path_behavior) {
  // L1-R1, L2-R1, L2-R2 structure tests augmenting path discovery
  CXXGraph::Node<int> l1("L1", 1);
  CXXGraph::Node<int> l2("L2", 2);
  CXXGraph::Node<int> r1("R1", 3);
  CXXGraph::Node<int> r2("R2", 4);

  CXXGraph::UndirectedEdge<int> edge1("1", l1, r1);  // L1 -> R1
  CXXGraph::UndirectedEdge<int> edge2("2", l2, r1);  // L2 -> R1
  CXXGraph::UndirectedEdge<int> edge3("3", l2, r2);  // L2 -> R2

  CXXGraph::T_EdgeSet<int> edgeSet;
  edgeSet.insert(make_shared<CXXGraph::UndirectedEdge<int>>(edge1));
  edgeSet.insert(make_shared<CXXGraph::UndirectedEdge<int>>(edge2));
  edgeSet.insert(make_shared<CXXGraph::UndirectedEdge<int>>(edge3));

  CXXGraph::Graph<int> graph(edgeSet);
  CXXGraph::HopcroftKarpResult result = graph.hopcroftKarp();

  // l1-r1, l2-r1, l2-r2 structure tests augmenting path discovery with optimal
  // matching of 2
  ASSERT_TRUE(result.success);
  ASSERT_EQ(result.maxMatching, 2);
  ASSERT_EQ(result.matching.size(), 2);
  ASSERT_TRUE(result.errorMessage.empty());

  // verify no duplicates in matching - each node appears exactly once
  std::set<std::string> leftMatched, rightMatched;
  for (const auto& match : result.matching) {
    ASSERT_TRUE(leftMatched.find(match.first) == leftMatched.end())
        << "Left node " << match.first << " is matched multiple times";
    ASSERT_TRUE(rightMatched.find(match.second) == rightMatched.end())
        << "Right node " << match.second << " is matched multiple times";
    leftMatched.insert(match.first);
    rightMatched.insert(match.second);
  }

  ASSERT_EQ(leftMatched.size(), 2);
  ASSERT_EQ(rightMatched.size(), 2);
}

TEST(HopcroftKarpTest, test_incremental_matching) {
  // star-like graph (one left node to multiple right nodes) should give
  // matching of size 1
  CXXGraph::Node<int> u1("u1", 1);
  CXXGraph::Node<int> v1("v1", 2);
  CXXGraph::Node<int> v2("v2", 3);
  CXXGraph::Node<int> v3("v3", 4);

  // u1 can connect to any of v1, v2, v3 but only one match is possible
  CXXGraph::UndirectedEdge<int> edge1("1", u1, v1);
  CXXGraph::UndirectedEdge<int> edge2("2", u1, v2);
  CXXGraph::UndirectedEdge<int> edge3("3", u1, v3);

  CXXGraph::T_EdgeSet<int> edgeSet;
  edgeSet.insert(make_shared<CXXGraph::UndirectedEdge<int>>(edge1));
  edgeSet.insert(make_shared<CXXGraph::UndirectedEdge<int>>(edge2));
  edgeSet.insert(make_shared<CXXGraph::UndirectedEdge<int>>(edge3));

  CXXGraph::Graph<int> graph(edgeSet);
  CXXGraph::HopcroftKarpResult result = graph.hopcroftKarp();

  // should achieve matching of size 1 (u1 matched to one of v1,v2,v3)
  ASSERT_TRUE(result.success);
  ASSERT_EQ(result.maxMatching, 1);
  ASSERT_EQ(result.matching.size(), 1);
  ASSERT_TRUE(result.errorMessage.empty());

  // verify exactly one match exists and u1 is matched
  ASSERT_EQ(result.matching[0].first, "u1");
  std::set<std::string> possibleMatches = {"v1", "v2", "v3"};
  ASSERT_TRUE(possibleMatches.count(result.matching[0].second) > 0);
}

TEST(HopcroftKarpTest, test_disconnected_graph) {
  // tests matching on a graph with multiple disconnected components
  // component 1: a single edge (matching size 1)
  CXXGraph::Node<int> u1("u1", 1), v1("v1", 2);
  CXXGraph::UndirectedEdge<int> edge1("1", u1, v1);

  // component 2: a 4-cycle (matching size 2)
  CXXGraph::Node<int> u2("u2", 3), v2("v2", 4);
  CXXGraph::Node<int> u3("u3", 5), v3("v3", 6);
  CXXGraph::UndirectedEdge<int> edge2("2", u2, v2);
  CXXGraph::UndirectedEdge<int> edge3("3", v2, u3);
  CXXGraph::UndirectedEdge<int> edge4("4", u3, v3);
  CXXGraph::UndirectedEdge<int> edge5("5", v3, u2);

  CXXGraph::T_EdgeSet<int> edgeSet;
  edgeSet.insert(make_shared<CXXGraph::UndirectedEdge<int>>(edge1));
  edgeSet.insert(make_shared<CXXGraph::UndirectedEdge<int>>(edge2));
  edgeSet.insert(make_shared<CXXGraph::UndirectedEdge<int>>(edge3));
  edgeSet.insert(make_shared<CXXGraph::UndirectedEdge<int>>(edge4));
  edgeSet.insert(make_shared<CXXGraph::UndirectedEdge<int>>(edge5));

  CXXGraph::Graph<int> graph(edgeSet);
  CXXGraph::HopcroftKarpResult result = graph.hopcroftKarp();

  // expected matching is sum of matchings from each component (1 + 2 = 3)
  ASSERT_TRUE(result.success);
  ASSERT_EQ(result.maxMatching, 3);
  ASSERT_EQ(result.matching.size(), 3);
  ASSERT_TRUE(result.errorMessage.empty());
}

TEST(HopcroftKarpTest, test_graph_with_isolated_vertices) {
  // tests matching on a graph with isolated vertices
  CXXGraph::Node<int> u1("u1", 1), v1("v1", 2);
  CXXGraph::UndirectedEdge<int> edge1("1", u1, v1);

  // isolated nodes
  CXXGraph::Node<int> iso1("iso1", 3), iso2("iso2", 4);

  CXXGraph::T_EdgeSet<int> edgeSet;
  edgeSet.insert(make_shared<CXXGraph::UndirectedEdge<int>>(edge1));

  CXXGraph::Graph<int> graph(edgeSet);
  graph.addNode(make_shared<CXXGraph::Node<int>>(iso1));
  graph.addNode(make_shared<CXXGraph::Node<int>>(iso2));

  CXXGraph::HopcroftKarpResult result = graph.hopcroftKarp();

  // isolated vertices should not affect the matching
  ASSERT_TRUE(result.success);
  ASSERT_EQ(result.maxMatching, 1);
  ASSERT_EQ(result.matching.size(), 1);
  ASSERT_TRUE(result.errorMessage.empty());
  ASSERT_EQ(result.matching[0].first, "u1");
  ASSERT_EQ(result.matching[0].second, "v1");
}

TEST(HopcroftKarpTest, test_no_matching_possible) {
  // tests a bipartite graph with no edges between partitions
  CXXGraph::Node<int> u1("u1", 1), u2("u2", 2);
  CXXGraph::Node<int> v1("v1", 3), v2("v2", 4);

  // no edges connect U and V partitions
  CXXGraph::T_EdgeSet<int> edgeSet;

  CXXGraph::Graph<int> graph(edgeSet);
  graph.addNode(make_shared<CXXGraph::Node<int>>(u1));
  graph.addNode(make_shared<CXXGraph::Node<int>>(u2));
  graph.addNode(make_shared<CXXGraph::Node<int>>(v1));
  graph.addNode(make_shared<CXXGraph::Node<int>>(v2));

  CXXGraph::HopcroftKarpResult result = graph.hopcroftKarp();

  // graph is bipartite, but matching should be 0
  ASSERT_TRUE(result.success);
  ASSERT_EQ(result.maxMatching, 0);
  ASSERT_EQ(result.matching.size(), 0);
  ASSERT_TRUE(result.errorMessage.empty());
}

TEST(HopcroftKarpTest, test_unbalanced_bipartite_graph) {
  // tests an unbalanced bipartite graph (U=3, V=2)
  CXXGraph::Node<int> u1("u1", 1), u2("u2", 2), u3("u3", 3);
  CXXGraph::Node<int> v1("v1", 4), v2("v2", 5);

  CXXGraph::UndirectedEdge<int> edge1("1", u1, v1);
  CXXGraph::UndirectedEdge<int> edge2("2", u2, v1);
  CXXGraph::UndirectedEdge<int> edge3("3", u3, v2);

  CXXGraph::T_EdgeSet<int> edgeSet;
  edgeSet.insert(make_shared<CXXGraph::UndirectedEdge<int>>(edge1));
  edgeSet.insert(make_shared<CXXGraph::UndirectedEdge<int>>(edge2));
  edgeSet.insert(make_shared<CXXGraph::UndirectedEdge<int>>(edge3));

  CXXGraph::Graph<int> graph(edgeSet);
  CXXGraph::HopcroftKarpResult result = graph.hopcroftKarp();

  // max matching cannot exceed the size of the smaller partition (V)
  ASSERT_TRUE(result.success);
  ASSERT_EQ(result.maxMatching, 2);
  ASSERT_EQ(result.matching.size(), 2);
  ASSERT_TRUE(result.errorMessage.empty());
}
