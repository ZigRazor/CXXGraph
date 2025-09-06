
#include <memory>

#include "CXXGraph/CXXGraph.hpp"
#include "gtest/gtest.h"

// include it to check that the static asserts don't fail
#include "TypeTraitsTest.hpp"

// Smart pointers alias
template <typename T>
using unique = std::unique_ptr<T>;
template <typename T>
using shared = std::shared_ptr<T>;

using std::make_shared;
using std::make_unique;

TEST(GraphTest, Constructor_1) {
  CXXGraph::Node<int> node1("1", 1);
  CXXGraph::Node<int> node2("2", 2);
  std::pair<const CXXGraph::Node<int> *, const CXXGraph::Node<int> *> pairNode(
      &node1, &node2);
  CXXGraph::Edge<int> edge(1, pairNode);
  CXXGraph::T_EdgeSet<int> edgeSet;
  edgeSet.insert(make_shared<CXXGraph::Edge<int>>(edge));
  CXXGraph::Graph<int> graph(edgeSet);
  ASSERT_EQ(graph.getEdgeSet(), edgeSet);
}

TEST(GraphTest, GetEdge_1) {
  CXXGraph::Node<int> node1("1", 1);
  CXXGraph::Node<int> node2("2", 2);
  std::pair<const CXXGraph::Node<int> *, const CXXGraph::Node<int> *> pairNode(
      &node1, &node2);
  CXXGraph::Edge<int> edge(1, pairNode);
  CXXGraph::T_EdgeSet<int> edgeSet;
  edgeSet.insert(make_shared<CXXGraph::Edge<int>>(edge));
  CXXGraph::Graph<int> graph(edgeSet);
  ASSERT_FALSE(graph.getEdge(2).has_value());
}

TEST(GraphTest, GetEdge_2) {
  CXXGraph::Node<int> node1("1", 1);
  CXXGraph::Node<int> node2("2", 2);
  std::pair<const CXXGraph::Node<int> *, const CXXGraph::Node<int> *> pairNode(
      &node1, &node2);
  CXXGraph::Edge<int> edge(1, pairNode);
  CXXGraph::T_EdgeSet<int> edgeSet;
  edgeSet.insert(make_shared<CXXGraph::Edge<int>>(edge));
  CXXGraph::Graph<int> graph(edgeSet);
  ASSERT_TRUE(graph.getEdge(1).has_value());
}

TEST(GraphTest, GetEdge_3) {
  CXXGraph::Node<int> node1("1", 1);
  CXXGraph::Node<int> node2("2", 2);
  std::pair<const CXXGraph::Node<int> *, const CXXGraph::Node<int> *> pairNode(
      &node1, &node2);
  CXXGraph::Edge<int> edge(1, pairNode);
  CXXGraph::T_EdgeSet<int> edgeSet;
  edgeSet.insert(make_shared<CXXGraph::Edge<int>>(edge));
  CXXGraph::Graph<int> graph(edgeSet);
  ASSERT_EQ(*(graph.getEdge(1).value()), edge);
}

TEST(GraphTest, GetNodeSet_1) {
  CXXGraph::Node<int> node1("1", 1);
  CXXGraph::Node<int> node2("2", 2);
  std::pair<const CXXGraph::Node<int> *, const CXXGraph::Node<int> *> pairNode(
      &node1, &node2);
  CXXGraph::Edge<int> edge(1, pairNode);
  CXXGraph::T_EdgeSet<int> edgeSet;
  edgeSet.insert(make_shared<CXXGraph::Edge<int>>(edge));
  CXXGraph::Graph<int> graph(edgeSet);
  auto nodeSet = graph.getNodeSet();
  ASSERT_EQ(nodeSet.size(), 2);
  ASSERT_TRUE(std::find_if(nodeSet.begin(), nodeSet.end(), [&node1](auto node) {
                return node->getUserId() == node1.getUserId();
              }) != nodeSet.end());
  ASSERT_TRUE(std::find_if(nodeSet.begin(), nodeSet.end(), [&node2](auto node) {
                return node->getUserId() == node2.getUserId();
              }) != nodeSet.end());
}

TEST(GraphTest, GetNodeSet_2) {
  CXXGraph::Node<int> node1("1", 1);
  CXXGraph::Node<int> node2("2", 2);
  CXXGraph::Node<int> node3("3", 3);
  std::pair<const CXXGraph::Node<int> *, const CXXGraph::Node<int> *> pairNode(
      &node1, &node2);
  CXXGraph::Edge<int> edge(1, pairNode);
  CXXGraph::UndirectedEdge<int> edge2(2, node2, node3);
  CXXGraph::T_EdgeSet<int> edgeSet;
  edgeSet.insert(make_shared<CXXGraph::Edge<int>>(edge));
  edgeSet.insert(make_shared<CXXGraph::UndirectedEdge<int>>(edge2));
  CXXGraph::Graph<int> graph(edgeSet);
  auto nodeSet = graph.getNodeSet();
  ASSERT_EQ(nodeSet.size(), 3);
  ASSERT_TRUE(std::find_if(nodeSet.begin(), nodeSet.end(), [&node1](auto node) {
                return node->getUserId() == node1.getUserId();
              }) != nodeSet.end());
  ASSERT_TRUE(std::find_if(nodeSet.begin(), nodeSet.end(), [&node2](auto node) {
                return node->getUserId() == node2.getUserId();
              }) != nodeSet.end());
  ASSERT_TRUE(std::find_if(nodeSet.begin(), nodeSet.end(), [&node3](auto node) {
                return node->getUserId() == node3.getUserId();
              }) != nodeSet.end());
}

TEST(GraphTest, FindEdge_Test) {
  CXXGraph::Node<int> node1("1", 1);
  CXXGraph::Node<int> node2("2", 2);
  CXXGraph::Node<int> node3("3", 3);
  CXXGraph::Node<int> node4("4", 2);
  CXXGraph::Node<int> node5("5", 3);
  CXXGraph::UndirectedEdge<int> edge(1, node1, node2);
  CXXGraph::UndirectedEdge<int> edge2(2, node2, node3);
  CXXGraph::T_EdgeSet<int> edgeSet;

  /* adding edges to the edgeset */

  edgeSet.insert(make_shared<CXXGraph::UndirectedEdge<int>>(edge));
  edgeSet.insert(make_shared<CXXGraph::UndirectedEdge<int>>(edge2));
  CXXGraph::Graph<int> graph(edgeSet);
  size_t edgeId = 0;
  ASSERT_TRUE(graph.findEdge(&node1, &node2, edgeId));
  CXXGraph::UndirectedEdge<int> edge3(3, node1, node3);

  /* adding edge using addEdge() */

  graph.addEdge(make_shared<CXXGraph::UndirectedEdge<int>>(edge3));
  ASSERT_TRUE(graph.findEdge(&node1, &node3, edgeId));
  ASSERT_TRUE(graph.findEdge(&node3, &node1, edgeId));
  CXXGraph::DirectedEdge<int> edge4(4, node1, node5);
  graph.addEdge(make_shared<CXXGraph::DirectedEdge<int>>(edge4));
  ASSERT_TRUE(graph.findEdge(&node1, &node5, edgeId));
  ASSERT_FALSE(graph.findEdge(&node5, &node1, edgeId));

  /* removing edge using removeEdge() */

  graph.removeEdge(2);
  CXXGraph::UndirectedWeightedEdge<int> edge5(7, node4, node5, 5);
  CXXGraph::DirectedWeightedEdge<int> edge6(8, node2, node5, 10);

  /* adding edge using addEdge() */

  graph.addEdge(&edge5);
  graph.addEdge(&edge6);
  ASSERT_FALSE(graph.findEdge(&node2, &node3, edgeId));
  ASSERT_FALSE(graph.findEdge(&node3, &node2, edgeId));

  /* Test for empty graph */

  CXXGraph::Graph<int> graph2;
  ASSERT_FALSE(graph2.findEdge(&node2, &node3, edgeId));
}

TEST(GraphTest, RawAddEdge_1) {
  CXXGraph::Node<int> n1("a", 1);
  CXXGraph::Node<int> n2("b", 1);
  CXXGraph::Node<int> n3("c", 1);

  CXXGraph::DirectedEdge<int> e1(0, n1, n2);
  CXXGraph::DirectedEdge<int> e2(1, n2, n3);
  CXXGraph::DirectedEdge<int> e3(2, n3, n1);

  CXXGraph::Graph<int> graph;
  graph.addEdge(&e1);
  graph.addEdge(&e2);
  graph.addEdge(&e3);

  ASSERT_TRUE(graph.isDirectedGraph());
  ASSERT_FALSE(graph.isUndirectedGraph());
}

TEST(GraphTest, RawAddEdge_2) {
  CXXGraph::Node<int> n1("a", 1);
  CXXGraph::Node<int> n2("b", 1);
  CXXGraph::Node<int> n3("c", 1);

  CXXGraph::UndirectedEdge<int> e1(0, n1, n2);
  CXXGraph::UndirectedEdge<int> e2(1, n2, n3);
  CXXGraph::UndirectedEdge<int> e3(2, n3, n1);

  CXXGraph::Graph<int> graph;
  graph.addEdge(&e1);
  graph.addEdge(&e2);
  graph.addEdge(&e3);

  ASSERT_FALSE(graph.isDirectedGraph());
  ASSERT_TRUE(graph.isUndirectedGraph());
}

TEST(GraphTest, RawAddEdge_3) {
  CXXGraph::Node<int> n1("a", 1);
  CXXGraph::Node<int> n2("b", 1);
  CXXGraph::Node<int> n3("c", 1);

  CXXGraph::UndirectedEdge<int> e1(0, n1, n2);
  CXXGraph::DirectedEdge<int> e2(1, n2, n3);
  CXXGraph::UndirectedEdge<int> e3(2, n3, n1);

  CXXGraph::Graph<int> graph;
  graph.addEdge(&e1);
  graph.addEdge(&e2);
  graph.addEdge(&e3);

  ASSERT_FALSE(graph.isDirectedGraph());
  ASSERT_FALSE(graph.isUndirectedGraph());
}

TEST(GraphTest, AddEdgeWeight_raw) {
  CXXGraph::Node<int> node1("1", 1);
  CXXGraph::Node<int> node2("2", 1);
  CXXGraph::Node<int> node3("3", 1);
  CXXGraph::DirectedWeightedEdge<int> edge1(1, node1, node2, 3);
  CXXGraph::UndirectedWeightedEdge<int> edge2(2, node1, node3, 5);
  CXXGraph::Graph<int> graph;

  graph.addEdge(&edge1);
  graph.addEdge(&edge2);

  // Check that the edges are weighted
  ASSERT_TRUE((*graph.getEdge(1))->isWeighted());
  ASSERT_TRUE((*graph.getEdge(2))->isWeighted());
  // Check the value of the weights
  ASSERT_EQ(
      std::dynamic_pointer_cast<const CXXGraph::Weighted>(*graph.getEdge(1))
          ->getWeight(),
      3);
  ASSERT_EQ(
      std::dynamic_pointer_cast<const CXXGraph::Weighted>(*graph.getEdge(2))
          ->getWeight(),
      5);
}

TEST(GraphTest, AddEdgeWeight_shared) {
  CXXGraph::Node<int> node1("1", 1);
  CXXGraph::Node<int> node2("2", 1);
  CXXGraph::Node<int> node3("3", 1);
  CXXGraph::DirectedWeightedEdge<int> edge1(1, node1, node2, 3);
  CXXGraph::UndirectedWeightedEdge<int> edge2(2, node1, node3, 5);
  CXXGraph::Graph<int> graph;

  graph.addEdge(make_shared<const CXXGraph::DirectedWeightedEdge<int>>(edge1));
  graph.addEdge(
      make_shared<const CXXGraph::UndirectedWeightedEdge<int>>(edge2));

  // Check that the edges are weighted
  ASSERT_TRUE((*graph.getEdge(1))->isWeighted());
  ASSERT_TRUE((*graph.getEdge(2))->isWeighted());
  // Check the value of the weights
  ASSERT_EQ(
      std::dynamic_pointer_cast<const CXXGraph::Weighted>(*graph.getEdge(1))
          ->getWeight(),
      3);
  ASSERT_EQ(
      std::dynamic_pointer_cast<const CXXGraph::Weighted>(*graph.getEdge(2))
          ->getWeight(),
      5);
}

TEST(GraphTest, AddEdges_1) {
  CXXGraph::Node<int> node1("1", 1);
  CXXGraph::Node<int> node2("2", 1);
  CXXGraph::Node<int> node3("3", 1);
  CXXGraph::DirectedEdge<int> edge1(1, node1, node2);
  CXXGraph::DirectedEdge<int> edge2(2, node1, node3);
  CXXGraph::DirectedEdge<int> edge3(3, node2, node3);
  CXXGraph::Graph<int> graph;

  graph.addEdges(&edge1, &edge2, &edge3);

  // Check the number of edges
  ASSERT_EQ(graph.getEdgeSet().size(), 3);
  // Check the number of nodes
  ASSERT_EQ(graph.getNodeSet().size(), 3);
}

TEST(GraphTest, AddEdges_1_shared) {
  CXXGraph::Node<int> node1("1", 1);
  CXXGraph::Node<int> node2("2", 1);
  CXXGraph::Node<int> node3("3", 1);
  CXXGraph::DirectedEdge<int> edge1(1, node1, node2);
  CXXGraph::DirectedEdge<int> edge2(2, node1, node3);
  CXXGraph::DirectedEdge<int> edge3(3, node2, node3);
  CXXGraph::Graph<int> graph;

  auto edge1_shared = make_shared<const CXXGraph::DirectedEdge<int>>(edge1);
  auto edge2_shared = make_shared<const CXXGraph::DirectedEdge<int>>(edge2);
  auto edge3_shared = make_shared<const CXXGraph::DirectedEdge<int>>(edge3);
  graph.addEdges(edge1_shared, edge2_shared, edge3_shared);

  // Check the number of edges
  ASSERT_EQ(graph.getEdgeSet().size(), 3);
  // Check the number of nodes
  ASSERT_EQ(graph.getNodeSet().size(), 3);
}

TEST(GraphTest, AddEdges_2) {
  CXXGraph::Node<int> node1("1", 1);
  CXXGraph::Node<int> node2("2", 1);
  CXXGraph::Node<int> node3("3", 1);
  CXXGraph::UndirectedEdge<int> edge1(1, node1, node2);
  CXXGraph::UndirectedEdge<int> edge2(2, node1, node3);
  CXXGraph::UndirectedEdge<int> edge3(3, node2, node3);
  CXXGraph::Graph<int> graph;

  graph.addEdges(&edge1, &edge2, &edge3);

  // Check the number of edges
  ASSERT_EQ(graph.getEdgeSet().size(), 3);
  // Check the number of nodes
  ASSERT_EQ(graph.getNodeSet().size(), 3);
}

TEST(GraphTest, AddEdges_2_shared) {
  CXXGraph::Node<int> node1("1", 1);
  CXXGraph::Node<int> node2("2", 1);
  CXXGraph::Node<int> node3("3", 1);
  CXXGraph::UndirectedEdge<int> edge1(1, node1, node2);
  CXXGraph::UndirectedEdge<int> edge2(2, node1, node3);
  CXXGraph::UndirectedEdge<int> edge3(3, node2, node3);
  CXXGraph::Graph<int> graph;

  auto edge1_shared = make_shared<const CXXGraph::UndirectedEdge<int>>(edge1);
  auto edge2_shared = make_shared<const CXXGraph::UndirectedEdge<int>>(edge2);
  auto edge3_shared = make_shared<const CXXGraph::UndirectedEdge<int>>(edge3);
  graph.addEdges(edge1_shared, edge2_shared, edge3_shared);

  // Check the number of edges
  ASSERT_EQ(graph.getEdgeSet().size(), 3);
  // Check the number of nodes
  ASSERT_EQ(graph.getNodeSet().size(), 3);
}

TEST(GraphTest, AddEdges_3) {
  CXXGraph::Node<int> node1("1", 1);
  CXXGraph::Node<int> node2("2", 1);
  CXXGraph::Node<int> node3("3", 1);
  CXXGraph::DirectedWeightedEdge<int> edge1(1, node1, node2, 4);
  CXXGraph::DirectedWeightedEdge<int> edge2(2, node1, node3, 5);
  CXXGraph::DirectedWeightedEdge<int> edge3(3, node2, node3, 6);
  CXXGraph::Graph<int> graph;

  graph.addEdges(&edge1, &edge2, &edge3);

  // Check the number of edges
  ASSERT_EQ(graph.getEdgeSet().size(), 3);
  // Check the number of nodes
  ASSERT_EQ(graph.getNodeSet().size(), 3);

  // Check that the edges are weighted
  ASSERT_TRUE((*graph.getEdge(1))->isWeighted());
  ASSERT_TRUE((*graph.getEdge(2))->isWeighted());
  ASSERT_TRUE((*graph.getEdge(3))->isWeighted());
  // Check the value of the weights
  ASSERT_EQ(
      std::dynamic_pointer_cast<const CXXGraph::Weighted>(*graph.getEdge(1))
          ->getWeight(),
      4);
  ASSERT_EQ(
      std::dynamic_pointer_cast<const CXXGraph::Weighted>(*graph.getEdge(2))
          ->getWeight(),
      5);
  ASSERT_EQ(
      std::dynamic_pointer_cast<const CXXGraph::Weighted>(*graph.getEdge(3))
          ->getWeight(),
      6);
}

TEST(GraphTest, AddEdges_3_shared) {
  CXXGraph::Node<int> node1("1", 1);
  CXXGraph::Node<int> node2("2", 1);
  CXXGraph::Node<int> node3("3", 1);
  CXXGraph::DirectedWeightedEdge<int> edge1(1, node1, node2, 4);
  CXXGraph::DirectedWeightedEdge<int> edge2(2, node1, node3, 5);
  CXXGraph::DirectedWeightedEdge<int> edge3(3, node2, node3, 6);
  CXXGraph::Graph<int> graph;

  auto edge1_shared =
      make_shared<const CXXGraph::DirectedWeightedEdge<int>>(edge1);
  auto edge2_shared =
      make_shared<const CXXGraph::DirectedWeightedEdge<int>>(edge2);
  auto edge3_shared =
      make_shared<const CXXGraph::DirectedWeightedEdge<int>>(edge3);
  graph.addEdges(edge1_shared, edge2_shared, edge3_shared);

  // Check the number of edges
  ASSERT_EQ(graph.getEdgeSet().size(), 3);
  // Check the number of nodes
  ASSERT_EQ(graph.getNodeSet().size(), 3);

  // Check that the edges are weighted
  ASSERT_TRUE((*graph.getEdge(1))->isWeighted());
  ASSERT_TRUE((*graph.getEdge(2))->isWeighted());
  ASSERT_TRUE((*graph.getEdge(3))->isWeighted());
  // Check the value of the weights
  ASSERT_EQ(
      std::dynamic_pointer_cast<const CXXGraph::Weighted>(*graph.getEdge(1))
          ->getWeight(),
      4);
  ASSERT_EQ(
      std::dynamic_pointer_cast<const CXXGraph::Weighted>(*graph.getEdge(2))
          ->getWeight(),
      5);
  ASSERT_EQ(
      std::dynamic_pointer_cast<const CXXGraph::Weighted>(*graph.getEdge(3))
          ->getWeight(),
      6);
}

TEST(GraphTest, AddEdges_4) {
  CXXGraph::Node<int> node1("1", 1);
  CXXGraph::Node<int> node2("2", 1);
  CXXGraph::Node<int> node3("3", 1);
  CXXGraph::UndirectedWeightedEdge<int> edge1(1, node1, node2, 4);
  CXXGraph::UndirectedWeightedEdge<int> edge2(2, node1, node3, 5);
  CXXGraph::UndirectedWeightedEdge<int> edge3(3, node2, node3, 6);
  CXXGraph::Graph<int> graph;

  graph.addEdges(&edge1, &edge2, &edge3);

  // Check the number of edges
  ASSERT_EQ(graph.getEdgeSet().size(), 3);
  // Check the number of nodes
  ASSERT_EQ(graph.getNodeSet().size(), 3);

  // Check that the edges are weighted
  ASSERT_TRUE((*graph.getEdge(1))->isWeighted());
  ASSERT_TRUE((*graph.getEdge(2))->isWeighted());
  ASSERT_TRUE((*graph.getEdge(3))->isWeighted());
  // Check the value of the weights
  ASSERT_EQ(
      std::dynamic_pointer_cast<const CXXGraph::Weighted>(*graph.getEdge(1))
          ->getWeight(),
      4);
  ASSERT_EQ(
      std::dynamic_pointer_cast<const CXXGraph::Weighted>(*graph.getEdge(2))
          ->getWeight(),
      5);
  ASSERT_EQ(
      std::dynamic_pointer_cast<const CXXGraph::Weighted>(*graph.getEdge(3))
          ->getWeight(),
      6);
}

TEST(GraphTest, AddEdges_4_shared) {
  CXXGraph::Node<int> node1("1", 1);
  CXXGraph::Node<int> node2("2", 1);
  CXXGraph::Node<int> node3("3", 1);
  CXXGraph::UndirectedWeightedEdge<int> edge1(1, node1, node2, 4);
  CXXGraph::UndirectedWeightedEdge<int> edge2(2, node1, node3, 5);
  CXXGraph::UndirectedWeightedEdge<int> edge3(3, node2, node3, 6);
  CXXGraph::Graph<int> graph;

  auto edge1_shared =
      make_shared<const CXXGraph::UndirectedWeightedEdge<int>>(edge1);
  auto edge2_shared =
      make_shared<const CXXGraph::UndirectedWeightedEdge<int>>(edge2);
  auto edge3_shared =
      make_shared<const CXXGraph::UndirectedWeightedEdge<int>>(edge3);
  graph.addEdges(edge1_shared, edge2_shared, edge3_shared);

  // Check the number of edges
  ASSERT_EQ(graph.getEdgeSet().size(), 3);
  // Check the number of nodes
  ASSERT_EQ(graph.getNodeSet().size(), 3);

  // Check that the edges are weighted
  ASSERT_TRUE((*graph.getEdge(1))->isWeighted());
  ASSERT_TRUE((*graph.getEdge(2))->isWeighted());
  ASSERT_TRUE((*graph.getEdge(3))->isWeighted());
  // Check the value of the weights
  ASSERT_EQ(
      std::dynamic_pointer_cast<const CXXGraph::Weighted>(*graph.getEdge(1))
          ->getWeight(),
      4);
  ASSERT_EQ(
      std::dynamic_pointer_cast<const CXXGraph::Weighted>(*graph.getEdge(2))
          ->getWeight(),
      5);
  ASSERT_EQ(
      std::dynamic_pointer_cast<const CXXGraph::Weighted>(*graph.getEdge(3))
          ->getWeight(),
      6);
}

TEST(GraphTest, DirectedEdgeCycle_1) {
  CXXGraph::Node<int> node1("a", 1);
  CXXGraph::Node<int> node2("b", 1);
  CXXGraph::Node<int> node3("c", 1);

  CXXGraph::DirectedEdge<int> edge1(0, node1, node2);
  CXXGraph::DirectedEdge<int> edge2(1, node2, node1);
  CXXGraph::DirectedEdge<int> edge3(2, node3, node1);

  CXXGraph::Graph<int> graph;

  graph.addEdge(&edge1);
  graph.addEdge(&edge2);
  graph.addEdge(&edge3);

  // Check that all of the edges have been added to the graph
  ASSERT_EQ(graph.getEdgeSet().size(), 3);
}

TEST(GraphTest, DirectedEdgeCycle_2) {
  CXXGraph::Node<int> node1("a", 1);
  CXXGraph::Node<int> node2("b", 1);
  CXXGraph::Node<int> node3("c", 1);

  CXXGraph::DirectedEdge<int> edge1(0, node1, node2);
  CXXGraph::DirectedEdge<int> edge2(1, node2, node1);
  CXXGraph::DirectedEdge<int> edge3(2, node3, node1);

  CXXGraph::T_EdgeSet<int> edgeSet;
  edgeSet.insert(make_shared<CXXGraph::DirectedEdge<int>>(edge1));
  edgeSet.insert(make_shared<CXXGraph::DirectedEdge<int>>(edge2));
  edgeSet.insert(make_shared<CXXGraph::DirectedEdge<int>>(edge3));

  CXXGraph::Graph<int> graph(edgeSet);

  // Check that all of the edges have been added to the graph
  ASSERT_EQ(graph.getEdgeSet().size(), 3);
}

TEST(GraphTest, DirectedEdge_hashequality) {
  CXXGraph::Node<int> node1("node1 (0)", 0);
  CXXGraph::Node<int> node2("node2 (1)", 1);
  CXXGraph::Node<int> node3("node3 (2)", 2);
  CXXGraph::Node<int> node4("node4 (3)", 3);
  CXXGraph::Node<int> node5("node5 (4)", 4);
  CXXGraph::Node<int> node6("node6 (5)", 5);
  CXXGraph::Node<int> node7("node7 (6)", 6);

  CXXGraph::DirectedEdge<int> edge1(0, node1, node2);
  CXXGraph::DirectedEdge<int> edge2(1, node2, node3);
  CXXGraph::DirectedEdge<int> edge3(3, node5, node4);
  CXXGraph::DirectedEdge<int> edge4(4, node5, node3);
  CXXGraph::DirectedEdge<int> edge5(5, node5, node2);
  CXXGraph::DirectedEdge<int> edge6(6, node5, node6);
  CXXGraph::DirectedEdge<int> edge7(7, node5, node1);
  CXXGraph::DirectedEdge<int> edge8(8, node5, node7);
  CXXGraph::DirectedEdge<int> edge9(9, node3, node4);
  CXXGraph::DirectedEdge<int> edge10(10, node6, node2);
  CXXGraph::DirectedEdge<int> edge11(11, node7, node2);

  CXXGraph::T_EdgeSet<int> edges;
  auto addEdge = [&](CXXGraph::DirectedEdge<int> &edge) {
    size_t currSize = edges.size();
    auto sharedEdge = CXXGraph::make_shared<CXXGraph::DirectedEdge<int>>(
        edge.getId(), edge.getFrom(), edge.getTo());
    edges.insert(sharedEdge);
    if ((currSize + 1) != edges.size()) {
      std::cout << "Skipped " << edge.getNodePair().first->getUserId()
                << " --> " << edge.getNodePair().second->getUserId()
                << " (hash: " << CXXGraph::edgeHash<int>{}(sharedEdge) << ")"
                << std::endl;
    } else {
      std::cout << "Added " << edge.getNodePair().first->getUserId() << " --> "
                << edge.getNodePair().second->getUserId()
                << " (hash: " << CXXGraph::edgeHash<int>{}(sharedEdge) << ")"
                << std::endl;
    }
  };

  addEdge(edge1);
  addEdge(edge2);
  addEdge(edge3);
  addEdge(edge4);
  addEdge(edge5);
  addEdge(edge6);
  addEdge(edge7);
  addEdge(edge8);
  addEdge(edge9);
  addEdge(edge10);
  addEdge(edge11);

  CXXGraph::Graph<int> graph;
  graph.setEdgeSet(edges);

  // Check that all of the edges have been added to the graph
  ASSERT_EQ(graph.getEdgeSet().size(), 11);
}

TEST(GraphTest, adj_print_1) {
  CXXGraph::Node<int> node1("1", 1);
  CXXGraph::Node<int> node2("2", 2);
  std::pair<const CXXGraph::Node<int> *, const CXXGraph::Node<int> *> pairNode(
      &node1, &node2);
  CXXGraph::Edge<int> edge(1, pairNode);
  CXXGraph::T_EdgeSet<int> edgeSet;
  edgeSet.insert(make_shared<CXXGraph::Edge<int>>(edge));
  CXXGraph::Graph<int> graph(edgeSet);
  std::cout << "Test Print Adjacency Matrix" << std::endl;
  std::cout << *graph.getAdjListOut() << std::endl;
}

TEST(GraphTest, adj_print_2) {
  CXXGraph::Node<int> node1("1", 1);
  CXXGraph::Node<int> node2("2", 2);
  std::pair<const CXXGraph::Node<int> *, const CXXGraph::Node<int> *> pairNode(
      &node1, &node2);
  CXXGraph::DirectedEdge<int> edge(1, pairNode);
  CXXGraph::T_EdgeSet<int> edgeSet;
  edgeSet.insert(make_shared<CXXGraph::DirectedEdge<int>>(edge));
  CXXGraph::Graph<int> graph(edgeSet);
  std::cout << "Test Print Adjacency Matrix" << std::endl;
  std::cout << *graph.getAdjListOut() << std::endl;
}

TEST(GraphTest, adj_print_3) {
  CXXGraph::Node<int> node1("1", 1);
  CXXGraph::Node<int> node2("2", 2);
  std::pair<const CXXGraph::Node<int> *, const CXXGraph::Node<int> *> pairNode(
      &node1, &node2);
  CXXGraph::UndirectedEdge<int> edge(1, pairNode);
  CXXGraph::T_EdgeSet<int> edgeSet;
  edgeSet.insert(make_shared<CXXGraph::UndirectedEdge<int>>(edge));
  CXXGraph::Graph<int> graph(edgeSet);
  std::cout << "Test Print Adjacency Matrix" << std::endl;
  std::cout << *graph.getAdjListOut() << std::endl;
}

TEST(GraphTest, adj_print_4) {
  CXXGraph::Node<int> node1("1", 1);
  CXXGraph::Node<int> node2("2", 2);
  CXXGraph::Node<int> node3("3", 3);
  std::pair<const CXXGraph::Node<int> *, const CXXGraph::Node<int> *> pairNode(
      &node1, &node2);
  CXXGraph::UndirectedEdge<int> edge1(1, pairNode);
  CXXGraph::UndirectedEdge<int> edge2(2, node2, node3);
  CXXGraph::UndirectedEdge<int> edge3(3, node1, node3);
  CXXGraph::T_EdgeSet<int> edgeSet;
  edgeSet.insert(make_shared<CXXGraph::UndirectedEdge<int>>(edge1));
  edgeSet.insert(make_shared<CXXGraph::UndirectedEdge<int>>(edge2));
  edgeSet.insert(make_shared<CXXGraph::UndirectedEdge<int>>(edge3));
  CXXGraph::Graph<int> graph(edgeSet);
  std::cout << "Test Print Adjacency Matrix" << std::endl;
  std::cout << *graph.getAdjListOut() << std::endl;
}

TEST(GraphTest, adj_print_5) {
  CXXGraph::Node<int> node1("1", 1);
  CXXGraph::Node<int> node2("2", 2);
  CXXGraph::Node<int> node3("3", 3);
  std::pair<const CXXGraph::Node<int> *, const CXXGraph::Node<int> *> pairNode(
      &node1, &node2);
  CXXGraph::DirectedEdge<int> edge1(1, pairNode);
  CXXGraph::DirectedEdge<int> edge2(2, node2, node3);
  CXXGraph::DirectedEdge<int> edge3(3, node1, node3);
  CXXGraph::T_EdgeSet<int> edgeSet;
  edgeSet.insert(make_shared<CXXGraph::DirectedEdge<int>>(edge1));
  edgeSet.insert(make_shared<CXXGraph::DirectedEdge<int>>(edge2));
  edgeSet.insert(make_shared<CXXGraph::DirectedEdge<int>>(edge3));
  CXXGraph::Graph<int> graph(edgeSet);
  std::cout << "Test Print Adjacency Matrix" << std::endl;
  std::cout << *graph.getAdjListOut() << std::endl;
}

TEST(GraphTest, adj_print_6) {
  CXXGraph::Node<int> node1("1", 1);
  CXXGraph::Node<int> node2("2", 2);
  CXXGraph::Node<int> node3("3", 3);
  std::pair<const CXXGraph::Node<int> *, const CXXGraph::Node<int> *> pairNode(
      &node1, &node2);
  CXXGraph::DirectedEdge<int> edge1(1, pairNode);
  CXXGraph::DirectedEdge<int> edge2(2, node2, node3);
  CXXGraph::UndirectedEdge<int> edge3(3, node1, node3);
  CXXGraph::T_EdgeSet<int> edgeSet;
  edgeSet.insert(make_shared<CXXGraph::DirectedEdge<int>>(edge1));
  edgeSet.insert(make_shared<CXXGraph::DirectedEdge<int>>(edge2));
  edgeSet.insert(make_shared<CXXGraph::UndirectedEdge<int>>(edge3));
  CXXGraph::Graph<int> graph(edgeSet);
  std::cout << "Test Print Adjacency Matrix" << std::endl;
  std::cout << *graph.getAdjListOut() << std::endl;
}

TEST(GraphTest, set_data) {
  // Create the graph
  CXXGraph::Node<int> node1("1", 1);
  CXXGraph::Node<int> node2("2", 2);
  CXXGraph::Node<int> node3("3", 3);
  std::pair<const CXXGraph::Node<int> *, const CXXGraph::Node<int> *> pairNode(
      &node1, &node2);
  CXXGraph::DirectedEdge<int> edge1(1, pairNode);
  CXXGraph::DirectedEdge<int> edge2(2, node2, node3);
  CXXGraph::UndirectedEdge<int> edge3(3, node1, node3);
  CXXGraph::T_EdgeSet<int> edgeSet;
  edgeSet.insert(make_shared<CXXGraph::DirectedEdge<int>>(edge1));
  edgeSet.insert(make_shared<CXXGraph::DirectedEdge<int>>(edge2));
  edgeSet.insert(make_shared<CXXGraph::UndirectedEdge<int>>(edge3));
  CXXGraph::Graph<int> graph(edgeSet);

  std::map<std::string, int> initial_values;
  // Construct map with the initial values of the nodes data
  for (const auto &nodeIt : graph.getNodeSet()) {
    initial_values[nodeIt->getUserId()] = nodeIt->getData();
  }
  // Change the data contained in the nodes singularly
  std::map<std::string, int> new_values;
  for (const auto &nodeIt : graph.getNodeSet()) {
    int r = std::rand();
    graph.setNodeData(nodeIt->getUserId(), r);
    new_values[nodeIt->getUserId()] = r;
  }
  // Check the final values of the node data
  for (const auto &nodeIt : graph.getNodeSet()) {
    ASSERT_EQ(nodeIt->getData(), new_values[nodeIt->getUserId()]);
  }

  // Now set the data of all the nodes at once
  std::map<std::string, int> data_values;
  for (const auto &nodeIt : graph.getNodeSet()) {
    int r = std::rand();
    data_values[nodeIt->getUserId()] = r;
  }
  graph.setNodeData(data_values);
  for (const auto &nodeIt : graph.getNodeSet()) {
    ASSERT_EQ(nodeIt->getData(), data_values[nodeIt->getUserId()]);
  }
}

TEST(GraphTest, test_outNodes) {
  CXXGraph::Node<int> node1("1", 1);
  CXXGraph::Node<int> node2("2", 2);
  CXXGraph::Node<int> node3("3", 3);
  CXXGraph::Node<int> node4("4", 4);
  CXXGraph::Node<int> node5("5", 5);
  CXXGraph::Node<int> node6("6", 6);
  CXXGraph::Node<int> node7("7", 7);
  CXXGraph::Node<int> node8("8", 8);
  CXXGraph::DirectedEdge<int> edge1(1, node1, node2);
  CXXGraph::DirectedEdge<int> edge2(2, node1, node3);
  CXXGraph::DirectedEdge<int> edge3(3, node2, node4);
  CXXGraph::DirectedEdge<int> edge4(4, node2, node5);
  CXXGraph::DirectedEdge<int> edge5(5, node3, node4);
  CXXGraph::DirectedEdge<int> edge6(6, node3, node5);
  CXXGraph::DirectedEdge<int> edge7(7, node4, node6);
  CXXGraph::DirectedEdge<int> edge8(8, node4, node7);
  CXXGraph::DirectedEdge<int> edge9(7, node5, node6);
  CXXGraph::DirectedEdge<int> edge10(8, node5, node7);
  CXXGraph::DirectedEdge<int> edge11(8, node6, node8);
  CXXGraph::DirectedEdge<int> edge12(8, node7, node8);
  CXXGraph::T_EdgeSet<int> edgeSet;
  edgeSet.insert(make_shared<CXXGraph::DirectedEdge<int>>(edge1));
  edgeSet.insert(make_shared<CXXGraph::DirectedEdge<int>>(edge2));
  edgeSet.insert(make_shared<CXXGraph::DirectedEdge<int>>(edge3));
  edgeSet.insert(make_shared<CXXGraph::DirectedEdge<int>>(edge4));
  edgeSet.insert(make_shared<CXXGraph::DirectedEdge<int>>(edge5));
  edgeSet.insert(make_shared<CXXGraph::DirectedEdge<int>>(edge6));
  edgeSet.insert(make_shared<CXXGraph::DirectedEdge<int>>(edge7));
  edgeSet.insert(make_shared<CXXGraph::DirectedEdge<int>>(edge8));
  edgeSet.insert(make_shared<CXXGraph::DirectedEdge<int>>(edge9));
  edgeSet.insert(make_shared<CXXGraph::DirectedEdge<int>>(edge10));
  edgeSet.insert(make_shared<CXXGraph::DirectedEdge<int>>(edge11));
  edgeSet.insert(make_shared<CXXGraph::DirectedEdge<int>>(edge12));
  CXXGraph::Graph<int> graph(edgeSet);

  // Check node 1
  for (auto x : graph.outNotInNeighbors(&node1)) {
    ASSERT_TRUE(x == make_shared<const CXXGraph::Node<int>>(node2) ||
                x == make_shared<const CXXGraph::Node<int>>(node3));
  }
  // Check node 2
  for (auto x : graph.outNotInNeighbors(&node2)) {
    ASSERT_TRUE(x == make_shared<const CXXGraph::Node<int>>(node4) ||
                x == make_shared<const CXXGraph::Node<int>>(node5));
    ASSERT_FALSE(x == make_shared<const CXXGraph::Node<int>>(node1));
  }
  // Check node 5
  for (auto x : graph.outNotInNeighbors(&node5)) {
    ASSERT_TRUE(x == make_shared<const CXXGraph::Node<int>>(node6) ||
                x == make_shared<const CXXGraph::Node<int>>(node7));
    ASSERT_FALSE(x == make_shared<const CXXGraph::Node<int>>(node2));
    ASSERT_FALSE(x == make_shared<const CXXGraph::Node<int>>(node3));
  }
  // Check that node 8 does not have any neighbors
  ASSERT_EQ(graph.outNotInNeighbors(&node8).size(), 0);
}

// Test the overload that takes shared_ptr as input
TEST(GraphTest, test_outNodes_shared) {
  CXXGraph::Node<int> node1("1", 1);
  CXXGraph::Node<int> node2("2", 2);
  CXXGraph::Node<int> node3("3", 3);
  CXXGraph::Node<int> node4("4", 4);
  CXXGraph::Node<int> node5("5", 5);
  CXXGraph::Node<int> node6("6", 6);
  CXXGraph::Node<int> node7("7", 7);
  CXXGraph::Node<int> node8("8", 8);
  CXXGraph::DirectedEdge<int> edge1(1, node1, node2);
  CXXGraph::DirectedEdge<int> edge2(2, node1, node3);
  CXXGraph::DirectedEdge<int> edge3(3, node2, node4);
  CXXGraph::DirectedEdge<int> edge4(4, node2, node5);
  CXXGraph::DirectedEdge<int> edge5(5, node3, node4);
  CXXGraph::DirectedEdge<int> edge6(6, node3, node5);
  CXXGraph::DirectedEdge<int> edge7(7, node4, node6);
  CXXGraph::DirectedEdge<int> edge8(8, node4, node7);
  CXXGraph::DirectedEdge<int> edge9(7, node5, node6);
  CXXGraph::DirectedEdge<int> edge10(8, node5, node7);
  CXXGraph::DirectedEdge<int> edge11(8, node6, node8);
  CXXGraph::DirectedEdge<int> edge12(8, node7, node8);
  CXXGraph::T_EdgeSet<int> edgeSet;
  edgeSet.insert(make_shared<CXXGraph::DirectedEdge<int>>(edge1));
  edgeSet.insert(make_shared<CXXGraph::DirectedEdge<int>>(edge2));
  edgeSet.insert(make_shared<CXXGraph::DirectedEdge<int>>(edge3));
  edgeSet.insert(make_shared<CXXGraph::DirectedEdge<int>>(edge4));
  edgeSet.insert(make_shared<CXXGraph::DirectedEdge<int>>(edge5));
  edgeSet.insert(make_shared<CXXGraph::DirectedEdge<int>>(edge6));
  edgeSet.insert(make_shared<CXXGraph::DirectedEdge<int>>(edge7));
  edgeSet.insert(make_shared<CXXGraph::DirectedEdge<int>>(edge8));
  edgeSet.insert(make_shared<CXXGraph::DirectedEdge<int>>(edge9));
  edgeSet.insert(make_shared<CXXGraph::DirectedEdge<int>>(edge10));
  edgeSet.insert(make_shared<CXXGraph::DirectedEdge<int>>(edge11));
  edgeSet.insert(make_shared<CXXGraph::DirectedEdge<int>>(edge12));
  CXXGraph::Graph<int> graph(edgeSet);

  for (auto x :
       graph.outNotInNeighbors(make_shared<const CXXGraph::Node<int>>(node1))) {
    ASSERT_TRUE(x == make_shared<const CXXGraph::Node<int>>(node2) ||
                x == make_shared<const CXXGraph::Node<int>>(node3));
  }

  auto node2_shared = make_shared<const CXXGraph::Node<int>>(node2);
  for (auto x : graph.outNotInNeighbors(node2_shared)) {
    ASSERT_TRUE(x == make_shared<const CXXGraph::Node<int>>(node4) ||
                x == make_shared<const CXXGraph::Node<int>>(node5));
    ASSERT_FALSE(x == make_shared<const CXXGraph::Node<int>>(node1));
  }
}

TEST(GraphTest, test_inOutNodes) {
  CXXGraph::Node<int> node1("1", 1);
  CXXGraph::Node<int> node2("2", 2);
  CXXGraph::Node<int> node3("3", 3);
  CXXGraph::Node<int> node4("4", 4);
  CXXGraph::Node<int> node5("5", 5);
  CXXGraph::Node<int> node6("6", 6);
  CXXGraph::Node<int> node7("7", 7);
  CXXGraph::Node<int> node8("8", 8);
  CXXGraph::UndirectedEdge<int> edge1(1, node1, node2);
  CXXGraph::UndirectedEdge<int> edge2(2, node1, node3);
  CXXGraph::UndirectedEdge<int> edge3(3, node2, node3);
  CXXGraph::UndirectedEdge<int> edge4(4, node2, node4);
  CXXGraph::UndirectedEdge<int> edge5(5, node4, node5);
  CXXGraph::UndirectedEdge<int> edge6(6, node4, node6);
  CXXGraph::UndirectedEdge<int> edge7(7, node6, node7);
  CXXGraph::UndirectedEdge<int> edge8(8, node6, node8);
  CXXGraph::T_EdgeSet<int> edgeSet;
  edgeSet.insert(make_shared<CXXGraph::UndirectedEdge<int>>(edge1));
  edgeSet.insert(make_shared<CXXGraph::UndirectedEdge<int>>(edge2));
  edgeSet.insert(make_shared<CXXGraph::UndirectedEdge<int>>(edge3));
  edgeSet.insert(make_shared<CXXGraph::UndirectedEdge<int>>(edge4));
  edgeSet.insert(make_shared<CXXGraph::UndirectedEdge<int>>(edge5));
  edgeSet.insert(make_shared<CXXGraph::UndirectedEdge<int>>(edge6));
  edgeSet.insert(make_shared<CXXGraph::UndirectedEdge<int>>(edge7));
  edgeSet.insert(make_shared<CXXGraph::UndirectedEdge<int>>(edge8));
  CXXGraph::Graph<int> graph(edgeSet);

  // Check node 1
  for (auto x : graph.inOrOutNeighbors(&node1)) {
    ASSERT_TRUE(x == make_shared<const CXXGraph::Node<int>>(node2) ||
                x == make_shared<const CXXGraph::Node<int>>(node3));
  }
  // Check node 4
  for (auto x : graph.inOrOutNeighbors(&node4)) {
    ASSERT_TRUE(x == make_shared<const CXXGraph::Node<int>>(node2) ||
                x == make_shared<const CXXGraph::Node<int>>(node3) ||
                x == make_shared<const CXXGraph::Node<int>>(node5) ||
                x == make_shared<const CXXGraph::Node<int>>(node6));
  }
  // Check node 7
  for (auto x : graph.inOrOutNeighbors(&node7)) {
    ASSERT_TRUE(x == make_shared<const CXXGraph::Node<int>>(node6));
  }
}

// Test the overload that takes shared_ptr as input
TEST(GraphTest, test_inOutNodes_shared) {
  CXXGraph::Node<int> node1("1", 1);
  CXXGraph::Node<int> node2("2", 2);
  CXXGraph::Node<int> node3("3", 3);
  CXXGraph::Node<int> node4("4", 4);
  CXXGraph::Node<int> node5("5", 5);
  CXXGraph::Node<int> node6("6", 6);
  CXXGraph::Node<int> node7("7", 7);
  CXXGraph::Node<int> node8("8", 8);
  CXXGraph::UndirectedEdge<int> edge1(1, node1, node2);
  CXXGraph::UndirectedEdge<int> edge2(2, node1, node3);
  CXXGraph::UndirectedEdge<int> edge3(3, node2, node3);
  CXXGraph::UndirectedEdge<int> edge4(4, node2, node4);
  CXXGraph::UndirectedEdge<int> edge5(5, node4, node5);
  CXXGraph::UndirectedEdge<int> edge6(6, node4, node6);
  CXXGraph::UndirectedEdge<int> edge7(7, node6, node7);
  CXXGraph::UndirectedEdge<int> edge8(8, node6, node8);
  CXXGraph::T_EdgeSet<int> edgeSet;
  edgeSet.insert(make_shared<CXXGraph::UndirectedEdge<int>>(edge1));
  edgeSet.insert(make_shared<CXXGraph::UndirectedEdge<int>>(edge2));
  edgeSet.insert(make_shared<CXXGraph::UndirectedEdge<int>>(edge3));
  edgeSet.insert(make_shared<CXXGraph::UndirectedEdge<int>>(edge4));
  edgeSet.insert(make_shared<CXXGraph::UndirectedEdge<int>>(edge5));
  edgeSet.insert(make_shared<CXXGraph::UndirectedEdge<int>>(edge6));
  edgeSet.insert(make_shared<CXXGraph::UndirectedEdge<int>>(edge7));
  edgeSet.insert(make_shared<CXXGraph::UndirectedEdge<int>>(edge8));
  CXXGraph::Graph<int> graph(edgeSet);

  for (auto x :
       graph.inOrOutNeighbors(make_shared<const CXXGraph::Node<int>>(node1))) {
    ASSERT_TRUE(x == make_shared<const CXXGraph::Node<int>>(node2) ||
                x == make_shared<const CXXGraph::Node<int>>(node3));
  }

  auto node7_shared = make_shared<const CXXGraph::Node<int>>(node7);
  for (auto x : graph.inOrOutNeighbors(node7_shared)) {
    ASSERT_TRUE(x == make_shared<const CXXGraph::Node<int>>(node6));
  }
}

TEST(InOutNodesTest, test_outEdges) {
  CXXGraph::Node<int> node1("1", 1);
  CXXGraph::Node<int> node2("2", 2);
  CXXGraph::Node<int> node3("3", 3);
  CXXGraph::Node<int> node4("4", 4);
  CXXGraph::Node<int> node5("5", 5);
  CXXGraph::Node<int> node6("6", 6);
  CXXGraph::Node<int> node7("7", 7);
  CXXGraph::Node<int> node8("8", 8);
  CXXGraph::DirectedEdge<int> edge1(1, node1, node2);
  CXXGraph::DirectedEdge<int> edge2(2, node1, node3);
  CXXGraph::DirectedEdge<int> edge3(3, node2, node4);
  CXXGraph::DirectedEdge<int> edge4(4, node2, node5);
  CXXGraph::DirectedEdge<int> edge5(5, node3, node4);
  CXXGraph::DirectedEdge<int> edge6(6, node3, node5);
  CXXGraph::DirectedEdge<int> edge7(7, node4, node6);
  CXXGraph::DirectedEdge<int> edge8(8, node4, node7);
  CXXGraph::DirectedEdge<int> edge9(7, node5, node6);
  CXXGraph::DirectedEdge<int> edge10(8, node5, node7);
  CXXGraph::DirectedEdge<int> edge11(8, node6, node8);
  CXXGraph::DirectedEdge<int> edge12(8, node7, node8);
  CXXGraph::T_EdgeSet<int> edgeSet;
  edgeSet.insert(make_shared<CXXGraph::DirectedEdge<int>>(edge1));
  edgeSet.insert(make_shared<CXXGraph::DirectedEdge<int>>(edge2));
  edgeSet.insert(make_shared<CXXGraph::DirectedEdge<int>>(edge3));
  edgeSet.insert(make_shared<CXXGraph::DirectedEdge<int>>(edge4));
  edgeSet.insert(make_shared<CXXGraph::DirectedEdge<int>>(edge5));
  edgeSet.insert(make_shared<CXXGraph::DirectedEdge<int>>(edge6));
  edgeSet.insert(make_shared<CXXGraph::DirectedEdge<int>>(edge7));
  edgeSet.insert(make_shared<CXXGraph::DirectedEdge<int>>(edge8));
  edgeSet.insert(make_shared<CXXGraph::DirectedEdge<int>>(edge9));
  edgeSet.insert(make_shared<CXXGraph::DirectedEdge<int>>(edge10));
  edgeSet.insert(make_shared<CXXGraph::DirectedEdge<int>>(edge11));
  edgeSet.insert(make_shared<CXXGraph::DirectedEdge<int>>(edge12));
  CXXGraph::Graph<int> graph(edgeSet);

  for (auto x : graph.outNotInEdges(&node1)) {
    ASSERT_TRUE(x == make_shared<const CXXGraph::Edge<int>>(edge1) ||
                x == make_shared<const CXXGraph::Edge<int>>(edge2));
  }

  auto node2_shared = make_shared<const CXXGraph::Node<int>>(node2);
  for (auto x : graph.outNotInEdges(&node2)) {
    ASSERT_TRUE(x == make_shared<const CXXGraph::Edge<int>>(edge3) ||
                x == make_shared<const CXXGraph::Edge<int>>(edge4));
    ASSERT_FALSE(x == make_shared<const CXXGraph::Edge<int>>(edge1));
  }
}

TEST(InOutNodesTest, test_outEdges_shared) {
  CXXGraph::Node<int> node1("1", 1);
  CXXGraph::Node<int> node2("2", 2);
  CXXGraph::Node<int> node3("3", 3);
  CXXGraph::Node<int> node4("4", 4);
  CXXGraph::Node<int> node5("5", 5);
  CXXGraph::Node<int> node6("6", 6);
  CXXGraph::Node<int> node7("7", 7);
  CXXGraph::Node<int> node8("8", 8);
  CXXGraph::DirectedEdge<int> edge1(1, node1, node2);
  CXXGraph::DirectedEdge<int> edge2(2, node1, node3);
  CXXGraph::DirectedEdge<int> edge3(3, node2, node4);
  CXXGraph::DirectedEdge<int> edge4(4, node2, node5);
  CXXGraph::DirectedEdge<int> edge5(5, node3, node4);
  CXXGraph::DirectedEdge<int> edge6(6, node3, node5);
  CXXGraph::DirectedEdge<int> edge7(7, node4, node6);
  CXXGraph::DirectedEdge<int> edge8(8, node4, node7);
  CXXGraph::DirectedEdge<int> edge9(7, node5, node6);
  CXXGraph::DirectedEdge<int> edge10(8, node5, node7);
  CXXGraph::DirectedEdge<int> edge11(8, node6, node8);
  CXXGraph::DirectedEdge<int> edge12(8, node7, node8);
  CXXGraph::T_EdgeSet<int> edgeSet;
  edgeSet.insert(make_shared<CXXGraph::DirectedEdge<int>>(edge1));
  edgeSet.insert(make_shared<CXXGraph::DirectedEdge<int>>(edge2));
  edgeSet.insert(make_shared<CXXGraph::DirectedEdge<int>>(edge3));
  edgeSet.insert(make_shared<CXXGraph::DirectedEdge<int>>(edge4));
  edgeSet.insert(make_shared<CXXGraph::DirectedEdge<int>>(edge5));
  edgeSet.insert(make_shared<CXXGraph::DirectedEdge<int>>(edge6));
  edgeSet.insert(make_shared<CXXGraph::DirectedEdge<int>>(edge7));
  edgeSet.insert(make_shared<CXXGraph::DirectedEdge<int>>(edge8));
  edgeSet.insert(make_shared<CXXGraph::DirectedEdge<int>>(edge9));
  edgeSet.insert(make_shared<CXXGraph::DirectedEdge<int>>(edge10));
  edgeSet.insert(make_shared<CXXGraph::DirectedEdge<int>>(edge11));
  edgeSet.insert(make_shared<CXXGraph::DirectedEdge<int>>(edge12));
  CXXGraph::Graph<int> graph(edgeSet);

  auto node1_shared = make_shared<const CXXGraph::Node<int>>(node1);
  for (auto x : graph.outNotInEdges(node1_shared)) {
    ASSERT_TRUE(x == make_shared<const CXXGraph::Edge<int>>(edge1) ||
                x == make_shared<const CXXGraph::Edge<int>>(edge2));
  }

  auto node2_shared = make_shared<const CXXGraph::Node<int>>(node2);
  for (auto x : graph.outNotInEdges(node2_shared)) {
    ASSERT_TRUE(x == make_shared<const CXXGraph::Edge<int>>(edge3) ||
                x == make_shared<const CXXGraph::Edge<int>>(edge4));
    ASSERT_FALSE(x == make_shared<const CXXGraph::Edge<int>>(edge1));
  }

  // Check the result for a node that does not exist in the graph
  CXXGraph::Node<int> node9("9", 9);
  auto node9_shared = make_shared<const CXXGraph::Node<int>>(node9);
  auto edges = graph.outNotInEdges(node9_shared);
  ASSERT_EQ(edges.size(), 0);
}

TEST(InOutNodesTest, test_inOutEdges) {
  CXXGraph::Node<int> node1("1", 1);
  CXXGraph::Node<int> node2("2", 2);
  CXXGraph::Node<int> node3("3", 3);
  CXXGraph::Node<int> node4("4", 4);
  CXXGraph::Node<int> node5("5", 5);
  CXXGraph::Node<int> node6("6", 6);
  CXXGraph::Node<int> node7("7", 7);
  CXXGraph::Node<int> node8("8", 8);
  CXXGraph::UndirectedEdge<int> edge1(1, node1, node2);
  CXXGraph::UndirectedEdge<int> edge2(2, node1, node3);
  CXXGraph::UndirectedEdge<int> edge3(3, node2, node3);
  CXXGraph::UndirectedEdge<int> edge4(4, node2, node4);
  CXXGraph::UndirectedEdge<int> edge5(5, node4, node5);
  CXXGraph::UndirectedEdge<int> edge6(6, node4, node6);
  CXXGraph::UndirectedEdge<int> edge7(7, node6, node7);
  CXXGraph::UndirectedEdge<int> edge8(8, node6, node8);
  CXXGraph::T_EdgeSet<int> edgeSet;
  edgeSet.insert(make_shared<CXXGraph::UndirectedEdge<int>>(edge1));
  edgeSet.insert(make_shared<CXXGraph::UndirectedEdge<int>>(edge2));
  edgeSet.insert(make_shared<CXXGraph::UndirectedEdge<int>>(edge3));
  edgeSet.insert(make_shared<CXXGraph::UndirectedEdge<int>>(edge4));
  edgeSet.insert(make_shared<CXXGraph::UndirectedEdge<int>>(edge5));
  edgeSet.insert(make_shared<CXXGraph::UndirectedEdge<int>>(edge6));
  edgeSet.insert(make_shared<CXXGraph::UndirectedEdge<int>>(edge7));
  edgeSet.insert(make_shared<CXXGraph::UndirectedEdge<int>>(edge8));
  CXXGraph::Graph<int> graph(edgeSet);

  for (auto x : graph.inOrOutEdges(&node1)) {
    ASSERT_TRUE(x == make_shared<const CXXGraph::Edge<int>>(edge1) ||
                x == make_shared<const CXXGraph::Edge<int>>(edge2));
  }

  for (auto x : graph.inOrOutEdges(&node6)) {
    ASSERT_TRUE(x == make_shared<const CXXGraph::Edge<int>>(edge6) ||
                x == make_shared<const CXXGraph::Edge<int>>(edge7) ||
                x == make_shared<const CXXGraph::Edge<int>>(edge8));
  }

  for (auto x : graph.inOrOutEdges(&node7)) {
    ASSERT_TRUE(x == make_shared<const CXXGraph::Edge<int>>(edge7));
  }
}

TEST(InOutNodesTest, test_inOutEdges_shared) {
  CXXGraph::Node<int> node1("1", 1);
  CXXGraph::Node<int> node2("2", 2);
  CXXGraph::Node<int> node3("3", 3);
  CXXGraph::Node<int> node4("4", 4);
  CXXGraph::Node<int> node5("5", 5);
  CXXGraph::Node<int> node6("6", 6);
  CXXGraph::Node<int> node7("7", 7);
  CXXGraph::Node<int> node8("8", 8);
  CXXGraph::UndirectedEdge<int> edge1(1, node1, node2);
  CXXGraph::UndirectedEdge<int> edge2(2, node1, node3);
  CXXGraph::UndirectedEdge<int> edge3(3, node2, node3);
  CXXGraph::UndirectedEdge<int> edge4(4, node2, node4);
  CXXGraph::UndirectedEdge<int> edge5(5, node4, node5);
  CXXGraph::UndirectedEdge<int> edge6(6, node4, node6);
  CXXGraph::UndirectedEdge<int> edge7(7, node6, node7);
  CXXGraph::UndirectedEdge<int> edge8(8, node6, node8);
  CXXGraph::T_EdgeSet<int> edgeSet;
  edgeSet.insert(make_shared<CXXGraph::UndirectedEdge<int>>(edge1));
  edgeSet.insert(make_shared<CXXGraph::UndirectedEdge<int>>(edge2));
  edgeSet.insert(make_shared<CXXGraph::UndirectedEdge<int>>(edge3));
  edgeSet.insert(make_shared<CXXGraph::UndirectedEdge<int>>(edge4));
  edgeSet.insert(make_shared<CXXGraph::UndirectedEdge<int>>(edge5));
  edgeSet.insert(make_shared<CXXGraph::UndirectedEdge<int>>(edge6));
  edgeSet.insert(make_shared<CXXGraph::UndirectedEdge<int>>(edge7));
  edgeSet.insert(make_shared<CXXGraph::UndirectedEdge<int>>(edge8));
  CXXGraph::Graph<int> graph(edgeSet);

  auto node1_shared = make_shared<const CXXGraph::Node<int>>(node1);
  for (auto x : graph.inOrOutEdges(node1_shared)) {
    ASSERT_TRUE(x == make_shared<const CXXGraph::Edge<int>>(edge1) ||
                x == make_shared<const CXXGraph::Edge<int>>(edge2));
  }

  auto node6_shared = make_shared<const CXXGraph::Node<int>>(node6);
  for (auto x : graph.inOrOutEdges(node6_shared)) {
    ASSERT_TRUE(x == make_shared<const CXXGraph::Edge<int>>(edge6) ||
                x == make_shared<const CXXGraph::Edge<int>>(edge7) ||
                x == make_shared<const CXXGraph::Edge<int>>(edge8));
  }

  auto node7_shared = make_shared<const CXXGraph::Node<int>>(node7);
  for (auto x : graph.inOrOutEdges(node7_shared)) {
    ASSERT_TRUE(x == make_shared<const CXXGraph::Edge<int>>(edge7));
  }

  // Check the result for a node that does not exist in the graph
  CXXGraph::Node<int> node9("9", 9);
  auto node9_shared = make_shared<const CXXGraph::Node<int>>(node9);
  auto edges = graph.inOrOutEdges(node9_shared);
  ASSERT_EQ(edges.size(), 0);
}

TEST(ReverseDirectedGraphTest, test_function) {
  CXXGraph::Node<int> node1("1", 1);
  CXXGraph::Node<int> node2("2", 2);
  CXXGraph::Node<int> node3("3", 3);
  CXXGraph::DirectedEdge<int> edge1(1, node1, node2);
  CXXGraph::DirectedEdge<int> edge2(2, node1, node3);
  CXXGraph::DirectedEdge<int> edge3(3, node2, node3);
  CXXGraph::T_EdgeSet<int> edgeSet;
  edgeSet.insert(make_shared<CXXGraph::DirectedEdge<int>>(edge1));
  edgeSet.insert(make_shared<CXXGraph::DirectedEdge<int>>(edge2));
  edgeSet.insert(make_shared<CXXGraph::DirectedEdge<int>>(edge3));
  CXXGraph::Graph<int> graph(edgeSet);
  CXXGraph::Graph<int> reverseGraph(edgeSet);
  reverseGraph.reverseDirectedGraph();
  // Check that the reverse graph has the same nodes as the original one
  ASSERT_EQ(graph.getNodeSet(), reverseGraph.getNodeSet());
  // Check edges
  auto originalSet = graph.getEdgeSet();
  auto reverseSet = reverseGraph.getEdgeSet();
  for (auto originalEdge : originalSet) {
    for (auto reverseEdge : reverseSet) {
      if (originalEdge->getId() == reverseEdge->getId()) {
        ASSERT_TRUE(originalEdge->getNodePair().first->getUserId() ==
                        reverseEdge->getNodePair().second->getUserId() &&
                    originalEdge->getNodePair().second->getUserId() ==
                        reverseEdge->getNodePair().first->getUserId());
      }
    }
  }
}

TEST(ReverseDirectedGraphTest, test_exception) {
  CXXGraph::Node<int> node1("1", 1);
  CXXGraph::Node<int> node2("2", 2);
  CXXGraph::Node<int> node3("3", 3);
  CXXGraph::Edge<int> edge1(1, node1, node2);
  CXXGraph::T_EdgeSet<int> edgeSet;
  edgeSet.insert(make_shared<CXXGraph::Edge<int>>(edge1));
  CXXGraph::Graph<int> graph(edgeSet);
  ASSERT_THROW(graph.reverseDirectedGraph(), std::runtime_error);
  CXXGraph::UndirectedEdge<int> edge2(2, node2, node3);
  CXXGraph::T_EdgeSet<int> undirEdgeSet;
  undirEdgeSet.insert(make_shared<CXXGraph::UndirectedEdge<int>>(edge2));
  CXXGraph::Graph<int> undirGraph(undirEdgeSet);
  ASSERT_THROW(undirGraph.reverseDirectedGraph(), std::runtime_error);
  CXXGraph::DirectedEdge<int> edge3(3, node3, node1);
  CXXGraph::T_EdgeSet<int> mixedEdgeSet;
  mixedEdgeSet.insert(make_shared<CXXGraph::DirectedEdge<int>>(edge3));
  mixedEdgeSet.insert(make_shared<CXXGraph::UndirectedEdge<int>>(edge2));
  CXXGraph::Graph<int> mixedGraph(mixedEdgeSet);
  ASSERT_THROW(mixedGraph.reverseDirectedGraph(), std::runtime_error);
}

TEST(IsolatedNodeGraphTest, Test_AddNode1) {
  CXXGraph::Node<int> node1("1", 1);
  CXXGraph::Node<int> node2("2", 2);
  CXXGraph::Node<int> node3("3", 3);
  CXXGraph::DirectedEdge<int> edge1(1, node1, node2);
  CXXGraph::DirectedEdge<int> edge2(2, node2, node1);
  CXXGraph::DirectedEdge<int> edge3(3, node1, node3);
  CXXGraph::T_EdgeSet<int> edgeSet;
  edgeSet.insert(make_shared<CXXGraph::Edge<int>>(edge1));
  edgeSet.insert(make_shared<CXXGraph::Edge<int>>(edge2));
  edgeSet.insert(make_shared<CXXGraph::Edge<int>>(edge3));
  CXXGraph::Graph<int> graph(edgeSet);

  // Create an isolated node and add it to the graph
  CXXGraph::Node<int> node4("4", 4);
  graph.addNode(make_shared<CXXGraph::Node<int>>(node4));

  // Check that the number of nodes in the graph is 4
  ASSERT_EQ(graph.getNodeSet().size(), 4);
  ASSERT_EQ(graph.getIsolatedNodeSet().size(), 1);
  ASSERT_EQ(graph.getEdgeSet().size(), 3);
}

TEST(IsolatedNodeGraphTest, Test_AddNode2) {
  CXXGraph::Node<int> node1("1", 1);
  CXXGraph::Node<int> node2("2", 2);
  CXXGraph::Node<int> node3("3", 3);
  CXXGraph::DirectedEdge<int> edge1(1, node1, node2);
  CXXGraph::DirectedEdge<int> edge2(2, node2, node1);
  CXXGraph::DirectedEdge<int> edge3(3, node1, node3);
  CXXGraph::T_EdgeSet<int> edgeSet;
  edgeSet.insert(make_shared<CXXGraph::Edge<int>>(edge1));
  edgeSet.insert(make_shared<CXXGraph::Edge<int>>(edge2));
  edgeSet.insert(make_shared<CXXGraph::Edge<int>>(edge3));
  CXXGraph::Graph<int> graph(edgeSet);

  // Create an isolated node and add it to the graph
  CXXGraph::Node<int> node4("4", 4);
  graph.addNode(&node4);

  // Check that the number of nodes in the graph is 4
  ASSERT_EQ(graph.getNodeSet().size(), 4);
  ASSERT_EQ(graph.getIsolatedNodeSet().size(), 1);
  ASSERT_EQ(graph.getEdgeSet().size(), 3);
}

TEST(IsolatedNodeGraphTest, Test_AddNodes1) {
  CXXGraph::Node<int> node1("1", 1);
  CXXGraph::Node<int> node2("2", 2);
  CXXGraph::Node<int> node3("3", 3);
  CXXGraph::DirectedEdge<int> edge1(1, node1, node2);
  CXXGraph::DirectedEdge<int> edge2(2, node2, node1);
  CXXGraph::DirectedEdge<int> edge3(3, node1, node3);
  CXXGraph::T_EdgeSet<int> edgeSet;
  edgeSet.insert(make_shared<CXXGraph::Edge<int>>(edge1));
  edgeSet.insert(make_shared<CXXGraph::Edge<int>>(edge2));
  edgeSet.insert(make_shared<CXXGraph::Edge<int>>(edge3));
  CXXGraph::Graph<int> graph(edgeSet);

  // Create an isolated node and add it to the graph
  CXXGraph::Node<int> node4("4", 4);
  CXXGraph::Node<int> node5("5", 5);
  auto node4_shared = make_shared<CXXGraph::Node<int>>(node4);
  auto node5_shared = make_shared<CXXGraph::Node<int>>(node5);
  graph.addNodes(node4_shared, node5_shared);

  // Check that the number of nodes in the graph is 4
  ASSERT_EQ(graph.getNodeSet().size(), 5);
  ASSERT_EQ(graph.getIsolatedNodeSet().size(), 2);
  ASSERT_EQ(graph.getEdgeSet().size(), 3);
}

TEST(IsolatedNodeGraphTest, Test_AddNodes2) {
  CXXGraph::Node<int> node1("1", 1);
  CXXGraph::Node<int> node2("2", 2);
  CXXGraph::Node<int> node3("3", 3);
  CXXGraph::DirectedEdge<int> edge1(1, node1, node2);
  CXXGraph::DirectedEdge<int> edge2(2, node2, node1);
  CXXGraph::DirectedEdge<int> edge3(3, node1, node3);
  CXXGraph::T_EdgeSet<int> edgeSet;
  edgeSet.insert(make_shared<CXXGraph::Edge<int>>(edge1));
  edgeSet.insert(make_shared<CXXGraph::Edge<int>>(edge2));
  edgeSet.insert(make_shared<CXXGraph::Edge<int>>(edge3));
  CXXGraph::Graph<int> graph(edgeSet);

  // Create an isolated node and add it to the graph
  CXXGraph::Node<int> node4("4", 4);
  CXXGraph::Node<int> node5("5", 5);
  graph.addNodes(&node4, &node5);

  // Check that the number of nodes in the graph is 4
  ASSERT_EQ(graph.getNodeSet().size(), 5);
  ASSERT_EQ(graph.getIsolatedNodeSet().size(), 2);
  ASSERT_EQ(graph.getEdgeSet().size(), 3);
}

TEST(TestRemoveNode, Test_isolatedNode) {
  CXXGraph::Node<int> node1("1", 1);
  CXXGraph::Node<int> node2("2", 2);
  CXXGraph::Node<int> node3("3", 3);
  CXXGraph::DirectedEdge<int> edge1(1, node1, node2);
  CXXGraph::DirectedEdge<int> edge2(2, node2, node1);
  CXXGraph::DirectedEdge<int> edge3(3, node1, node3);
  CXXGraph::T_EdgeSet<int> edgeSet;
  edgeSet.insert(make_shared<CXXGraph::Edge<int>>(edge1));
  edgeSet.insert(make_shared<CXXGraph::Edge<int>>(edge2));
  edgeSet.insert(make_shared<CXXGraph::Edge<int>>(edge3));
  CXXGraph::Graph<int> graph(edgeSet);

  // Create isolated nodes and add them to the graph
  CXXGraph::Node<int> node4("4", 4);
  CXXGraph::Node<int> node5("5", 5);
  CXXGraph::Node<int> node6("6", 6);
  graph.addNode(make_shared<CXXGraph::Node<int>>(node4));
  graph.addNode(make_shared<CXXGraph::Node<int>>(node5));
  graph.addNode(make_shared<CXXGraph::Node<int>>(node6));

  // Check the initial number of edges and nodes
  ASSERT_EQ(graph.getNodeSet().size(), 6);
  ASSERT_EQ(graph.getIsolatedNodeSet().size(), 3);
  ASSERT_EQ(graph.getEdgeSet().size(), 3);

  // We now remove node 5
  graph.removeNode("5");

  // Check the final number of edges and nodes
  ASSERT_EQ(graph.getNodeSet().size(), 5);
  ASSERT_EQ(graph.getIsolatedNodeSet().size(), 2);
  ASSERT_EQ(graph.getEdgeSet().size(), 3);
}

TEST(TestRemoveNode, Test_connectedNode) {
  CXXGraph::Node<int> node1("1", 1);
  CXXGraph::Node<int> node2("2", 2);
  CXXGraph::Node<int> node3("3", 3);
  CXXGraph::DirectedEdge<int> edge1(1, node1, node2);
  CXXGraph::DirectedEdge<int> edge2(2, node2, node1);
  CXXGraph::DirectedEdge<int> edge3(3, node1, node3);
  CXXGraph::T_EdgeSet<int> edgeSet;
  edgeSet.insert(make_shared<CXXGraph::Edge<int>>(edge1));
  edgeSet.insert(make_shared<CXXGraph::Edge<int>>(edge2));
  edgeSet.insert(make_shared<CXXGraph::Edge<int>>(edge3));
  CXXGraph::Graph<int> graph(edgeSet);

  // Create isolated nodes and add them to the graph
  CXXGraph::Node<int> node4("4", 4);
  CXXGraph::Node<int> node5("5", 5);
  CXXGraph::Node<int> node6("6", 6);
  graph.addNode(make_shared<CXXGraph::Node<int>>(node4));
  graph.addNode(make_shared<CXXGraph::Node<int>>(node5));
  graph.addNode(make_shared<CXXGraph::Node<int>>(node6));

  // Check the initial number of edges and nodes
  ASSERT_EQ(graph.getNodeSet().size(), 6);
  ASSERT_EQ(graph.getIsolatedNodeSet().size(), 3);
  ASSERT_EQ(graph.getEdgeSet().size(), 3);

  // We now remove node 2
  graph.removeNode("2");

  // Check the final number of edges and nodes
  ASSERT_EQ(graph.getNodeSet().size(), 5);
  ASSERT_EQ(graph.getIsolatedNodeSet().size(), 3);
  ASSERT_EQ(graph.getEdgeSet().size(), 1);
}

TEST(TestRemoveNode, Test_removeInvalidNode) {
  /** Test to call the remove_node function on a node that was never added. In
   * this case getNode will return an optional that is nullptr*/
  // Create a graph with 3 nodes and 3 edges.
  CXXGraph::Node<int> node1("1", 1);
  CXXGraph::Node<int> node2("2", 2);
  CXXGraph::Node<int> node3("3", 3);
  CXXGraph::DirectedEdge<int> edge1(1, node1, node2);
  CXXGraph::DirectedEdge<int> edge2(2, node2, node1);
  CXXGraph::DirectedEdge<int> edge3(3, node1, node3);
  CXXGraph::T_EdgeSet<int> edgeSet;
  // Add the 3 edges into the graph.
  edgeSet.insert(make_shared<CXXGraph::Edge<int>>(edge1));
  edgeSet.insert(make_shared<CXXGraph::Edge<int>>(edge2));
  edgeSet.insert(make_shared<CXXGraph::Edge<int>>(edge3));
  // Initialise the graph
  CXXGraph::Graph<int> graph(edgeSet);

  // Check the initial number of edges and nodes. Everything should be okay so
  // far
  ASSERT_EQ(graph.getNodeSet().size(), 3);
  ASSERT_EQ(graph.getEdgeSet().size(), 3);

  // Remove a node that was never in the graph
  graph.removeNode("4");

  // Number of nodes and edges in the graph should remain the same
  ASSERT_EQ(graph.getNodeSet().size(), 3);
  ASSERT_EQ(graph.getEdgeSet().size(), 3);

  // Remove an existing node, the edge associated with that node should also be
  // removed. Node "3" had just outgoing edge, so there should now be 2 nodes
  // and 2 edges.
  graph.removeNode("3");
  ASSERT_EQ(graph.getNodeSet().size(), 2);
  ASSERT_EQ(graph.getEdgeSet().size(), 2);

  // Remove the node that had already been removed. Should not change anything
  // about the graph now, similar to when "4" was removed above
  graph.removeNode("3");
  ASSERT_EQ(graph.getNodeSet().size(), 2);
  ASSERT_EQ(graph.getEdgeSet().size(), 2);
}

TEST(TestGetNode, Test_1) {
  CXXGraph::Node<int> node1("1", 1);
  CXXGraph::Node<int> node2("2", 2);
  CXXGraph::Node<int> node3("3", 3);
  CXXGraph::DirectedEdge<int> edge1(1, node1, node2);
  CXXGraph::DirectedEdge<int> edge2(2, node2, node1);
  CXXGraph::DirectedEdge<int> edge3(3, node1, node3);
  CXXGraph::T_EdgeSet<int> edgeSet;
  edgeSet.insert(make_shared<CXXGraph::Edge<int>>(edge1));
  edgeSet.insert(make_shared<CXXGraph::Edge<int>>(edge2));
  edgeSet.insert(make_shared<CXXGraph::Edge<int>>(edge3));
  CXXGraph::Graph<int> graph(edgeSet);

  auto node_found = graph.getNode("2");
  ASSERT_TRUE(node_found.has_value());
  ASSERT_EQ(node_found.value()->getUserId(), "2");

  auto node_notfound = graph.getNode("5");
  ASSERT_FALSE(node_notfound.has_value());
}

TEST(GraphTest, set_data_isolated) {
  // Create the graph
  CXXGraph::Node<int> node1("1", 1);
  CXXGraph::Node<int> node2("2", 2);
  CXXGraph::Node<int> node3("3", 3);
  std::pair<const CXXGraph::Node<int> *, const CXXGraph::Node<int> *> pairNode(
      &node1, &node2);
  CXXGraph::DirectedEdge<int> edge1(1, pairNode);
  CXXGraph::DirectedEdge<int> edge2(2, node2, node3);
  CXXGraph::UndirectedEdge<int> edge3(3, node1, node3);
  CXXGraph::T_EdgeSet<int> edgeSet;
  edgeSet.insert(make_shared<CXXGraph::DirectedEdge<int>>(edge1));
  edgeSet.insert(make_shared<CXXGraph::DirectedEdge<int>>(edge2));
  edgeSet.insert(make_shared<CXXGraph::UndirectedEdge<int>>(edge3));
  CXXGraph::Graph<int> graph(edgeSet);

  // Create isolated nodes and add them to the graph
  CXXGraph::Node<int> node4("4", 4);
  CXXGraph::Node<int> node5("5", 5);
  CXXGraph::Node<int> node6("6", 6);
  graph.addNode(make_shared<CXXGraph::Node<int>>(node4));
  graph.addNode(make_shared<CXXGraph::Node<int>>(node5));
  graph.addNode(make_shared<CXXGraph::Node<int>>(node6));

  std::map<std::string, int> initial_values;
  // Construct map with the initial values of the nodes data
  for (const auto &nodeIt : graph.getNodeSet()) {
    initial_values[nodeIt->getUserId()] = nodeIt->getData();
  }
  // Change the data contained in the nodes singularly
  std::map<std::string, int> new_values;
  for (const auto &nodeIt : graph.getNodeSet()) {
    int r = std::rand();
    graph.setNodeData(nodeIt->getUserId(), r);
    new_values[nodeIt->getUserId()] = r;
  }
  // Check the final values of the node data
  for (const auto &nodeIt : graph.getNodeSet()) {
    ASSERT_EQ(nodeIt->getData(), new_values[nodeIt->getUserId()]);
  }

  // Now set the data of all the nodes at once
  std::map<std::string, int> data_values;
  for (const auto &nodeIt : graph.getNodeSet()) {
    int r = std::rand();
    data_values[nodeIt->getUserId()] = r;
  }
  graph.setNodeData(data_values);
  for (const auto &nodeIt : graph.getNodeSet()) {
    ASSERT_EQ(nodeIt->getData(), data_values[nodeIt->getUserId()]);
  }
}

TEST(GraphTest, type_trait_not_extractable) {
  CXXGraph::Node<int*> node1("1", nullptr);
  CXXGraph::Node<int*> node2("2", nullptr);
  CXXGraph::Edge<int*> edge(1, node1, node2);

  CXXGraph::T_EdgeSet<int*> edgeSet;
  edgeSet.insert(make_shared<CXXGraph::Edge<int*>>(edge));

  CXXGraph::Graph<int*> graph(edgeSet);
  ASSERT_EQ(graph.getEdgeSet(), edgeSet);
}