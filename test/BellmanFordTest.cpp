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

// check if algorithm works using a complicated test case
TEST(BellmanFordTest, test_1) {
  CXXGraph::Node<int> node0("0", 0);
  CXXGraph::Node<int> node1("1", 1);
  CXXGraph::Node<int> node2("2", 2);
  CXXGraph::Node<int> node3("3", 3);
  CXXGraph::Node<int> node4("4", 4);

  CXXGraph::DirectedWeightedEdge<int> edge1("1", node0, node1, 6);
  CXXGraph::DirectedWeightedEdge<int> edge2("1", node0, node2, 7);

  CXXGraph::DirectedWeightedEdge<int> edge3("1", node1, node2, 8);
  CXXGraph::DirectedWeightedEdge<int> edge4("1", node1, node3, -4);
  CXXGraph::DirectedWeightedEdge<int> edge5("1", node1, node4, 5);

  CXXGraph::DirectedWeightedEdge<int> edge6("1", node2, node4, -3);
  CXXGraph::DirectedWeightedEdge<int> edge7("1", node2, node3, 9);

  CXXGraph::DirectedWeightedEdge<int> edge8("1", node3, node4, 7);
  CXXGraph::DirectedWeightedEdge<int> edge9("1", node3, node0, 2);

  CXXGraph::DirectedWeightedEdge<int> edge10("1", node4, node1, -2);
  CXXGraph::T_EdgeSet<int> edgeSet;
  edgeSet.insert(make_shared<CXXGraph::DirectedWeightedEdge<int>>(edge1));
  edgeSet.insert(make_shared<CXXGraph::DirectedWeightedEdge<int>>(edge2));
  edgeSet.insert(make_shared<CXXGraph::DirectedWeightedEdge<int>>(edge3));
  edgeSet.insert(make_shared<CXXGraph::DirectedWeightedEdge<int>>(edge4));
  edgeSet.insert(make_shared<CXXGraph::DirectedWeightedEdge<int>>(edge5));
  edgeSet.insert(make_shared<CXXGraph::DirectedWeightedEdge<int>>(edge6));
  edgeSet.insert(make_shared<CXXGraph::DirectedWeightedEdge<int>>(edge7));
  edgeSet.insert(make_shared<CXXGraph::DirectedWeightedEdge<int>>(edge8));
  edgeSet.insert(make_shared<CXXGraph::DirectedWeightedEdge<int>>(edge9));
  edgeSet.insert(make_shared<CXXGraph::DirectedWeightedEdge<int>>(edge10));

  CXXGraph::Graph<int> graph(edgeSet);
  CXXGraph::BellmanFordResult res = graph.bellmanford(node0, node3);
  ASSERT_TRUE(res.success);
  ASSERT_FALSE(res.negativeCycle);
  ASSERT_EQ(res.errorMessage, "");
  ASSERT_EQ(res.result, -2);
}

// a graph with negative cycle
TEST(BellmanFordTest, test_2) {
  CXXGraph::Node<int> node0("0", 0);
  CXXGraph::Node<int> node1("1", 1);
  CXXGraph::Node<int> node2("2", 2);
  CXXGraph::DirectedWeightedEdge<int> edge1("1", node0, node1, 2);
  CXXGraph::DirectedWeightedEdge<int> edge2("2", node1, node2, 3);
  CXXGraph::DirectedWeightedEdge<int> edge3("2", node2, node0, -7);
  CXXGraph::T_EdgeSet<int> edgeSet;
  edgeSet.insert(make_shared<CXXGraph::DirectedWeightedEdge<int>>(edge1));
  edgeSet.insert(make_shared<CXXGraph::DirectedWeightedEdge<int>>(edge2));
  edgeSet.insert(make_shared<CXXGraph::DirectedWeightedEdge<int>>(edge3));
  CXXGraph::Graph<int> graph(edgeSet);
  CXXGraph::BellmanFordResult res = graph.bellmanford(node0, node2);
  ASSERT_TRUE(res.success);
  ASSERT_TRUE(res.negativeCycle);
  ASSERT_EQ(res.errorMessage, "");
  ASSERT_EQ(res.result, CXXGraph::INF_DOUBLE);
}

// UndirectedWeightedEdge
TEST(BellmanFordTest, test_3) {
  CXXGraph::Node<int> node1("1", 1);
  CXXGraph::Node<int> node2("2", 2);
  CXXGraph::Node<int> node3("3", 3);
  std::pair<const CXXGraph::Node<int> *, const CXXGraph::Node<int> *> pairNode(
      &node1, &node2);
  CXXGraph::DirectedWeightedEdge<int> edge1("1", pairNode, 1);
  CXXGraph::DirectedWeightedEdge<int> edge2("2", node2, node3, 1);
  CXXGraph::UndirectedWeightedEdge<int> edge3("2", node1, node3, 6);
  CXXGraph::T_EdgeSet<int> edgeSet;
  edgeSet.insert(make_shared<CXXGraph::DirectedWeightedEdge<int>>(edge1));
  edgeSet.insert(make_shared<CXXGraph::DirectedWeightedEdge<int>>(edge2));
  edgeSet.insert(make_shared<CXXGraph::UndirectedWeightedEdge<int>>(edge3));
  CXXGraph::Graph<int> graph(edgeSet);
  CXXGraph::BellmanFordResult res = graph.bellmanford(node1, node3);
  ASSERT_TRUE(res.success);
  ASSERT_FALSE(res.negativeCycle);
  ASSERT_EQ(res.errorMessage, "");
  ASSERT_EQ(res.result, 2);
}

// No weighted edge
TEST(BellmanFordTest, test_4) {
  CXXGraph::Node<int> node1("1", 1);
  CXXGraph::Node<int> node2("2", 2);
  CXXGraph::Node<int> node3("3", 3);
  std::pair<const CXXGraph::Node<int> *, const CXXGraph::Node<int> *> pairNode(
      &node1, &node2);
  CXXGraph::DirectedWeightedEdge<int> edge1("1", pairNode, 1);
  CXXGraph::DirectedWeightedEdge<int> edge2("2", node2, node3, 1);
  CXXGraph::DirectedEdge<int> edge3("2", node1, node3);
  CXXGraph::T_EdgeSet<int> edgeSet;
  edgeSet.insert(make_shared<CXXGraph::DirectedWeightedEdge<int>>(edge1));
  edgeSet.insert(make_shared<CXXGraph::DirectedWeightedEdge<int>>(edge2));
  edgeSet.insert(make_shared<CXXGraph::DirectedEdge<int>>(edge3));
  CXXGraph::Graph<int> graph(edgeSet);
  CXXGraph::BellmanFordResult res = graph.bellmanford(node1, node3);
  ASSERT_FALSE(res.success);
  ASSERT_FALSE(res.negativeCycle);
  ASSERT_EQ(res.errorMessage, CXXGraph::ERR_NO_WEIGHTED_EDGE);
  ASSERT_EQ(res.result, CXXGraph::INF_DOUBLE);
}

// ERR_SOURCE_NODE_NOT_IN_GRAPH
// ERR_TARGET_NODE_NOT_IN_GRAPH
// ERR_TARGET_NODE_NOT_REACHABLE
TEST(BellmanFordTest, test_5) {
  CXXGraph::Node<int> node1("1", 1);
  CXXGraph::Node<int> node2("2", 2);
  CXXGraph::Node<int> node3("3", 3);
  CXXGraph::DirectedWeightedEdge<int> edge1("2", node1, node2, 1);
  CXXGraph::T_EdgeSet<int> edgeSet;
  edgeSet.insert(make_shared<CXXGraph::DirectedWeightedEdge<int>>(edge1));
  CXXGraph::Graph<int> graph(edgeSet);
  CXXGraph::BellmanFordResult res = graph.bellmanford(node3, node1);
  ASSERT_FALSE(res.success);
  ASSERT_FALSE(res.negativeCycle);
  ASSERT_EQ(res.errorMessage, CXXGraph::ERR_SOURCE_NODE_NOT_IN_GRAPH);
  ASSERT_EQ(res.result, CXXGraph::INF_DOUBLE);

  res = graph.bellmanford(node1, node3);
  ASSERT_FALSE(res.success);
  ASSERT_FALSE(res.negativeCycle);
  ASSERT_EQ(res.errorMessage, CXXGraph::ERR_TARGET_NODE_NOT_IN_GRAPH);
  ASSERT_EQ(res.result, CXXGraph::INF_DOUBLE);

  CXXGraph::DirectedWeightedEdge<int> edge2("2", node3, node2, 1);
  edgeSet.insert(make_shared<CXXGraph::DirectedWeightedEdge<int>>(edge2));

  CXXGraph::Graph<int> graph1(edgeSet);
  res = graph1.bellmanford(node1, node3);
  ASSERT_FALSE(res.success);
  ASSERT_FALSE(res.negativeCycle);
  ASSERT_EQ(res.errorMessage, CXXGraph::ERR_TARGET_NODE_NOT_REACHABLE);
  ASSERT_EQ(res.result, -1);
}
