#include "CXXGraph.hpp"
#include "gtest/gtest.h"

TEST(UndirectedWeightedEdgeTest, Constructor_1) {
  CXXGRAPH::Node<int> node1("1", 1);
  CXXGRAPH::Node<int> node2("2", 2);
  CXXGRAPH::UndirectedWeightedEdge<int> edge(1, node1, node2, 10);
  ASSERT_EQ(*(edge.getNodePair().first), node1);
  ASSERT_EQ(*(edge.getNodePair().second), node2);
  ASSERT_EQ(edge.getWeight(), 10);
}

TEST(UndirectedWeightedEdgeTest, Constructor_2) {
  CXXGRAPH::Node<int> node1("1", 1);
  CXXGRAPH::Node<int> node2("2", 2);
  std::pair<const CXXGRAPH::Node<int> *, const CXXGRAPH::Node<int> *> pairNode(
      &node1, &node2);
  CXXGRAPH::UndirectedWeightedEdge<int> edge(1, pairNode, 10);
  ASSERT_EQ(edge.getNodePair(), pairNode);
  ASSERT_EQ(*(edge.getNodePair().first), node1);
  ASSERT_EQ(*(edge.getNodePair().second), node2);
  ASSERT_EQ(edge.getWeight(), 10);
}

TEST(UndirectedWeightedEdgeTest, Constructor_3) {
  CXXGRAPH::Node<int> node1("1", 1);
  CXXGRAPH::Node<int> node2("2", 2);
  std::pair<const CXXGRAPH::Node<int> *, const CXXGRAPH::Node<int> *> pairNode(
      &node1, &node2);
  CXXGRAPH::UndirectedWeightedEdge<int> edge(1, pairNode, 10);
  ASSERT_FALSE(edge.isDirected().value());
}

TEST(UndirectedWeightedEdgeTest, Constructor_4) {
  CXXGRAPH::Node<int> node1("1", 1);
  CXXGRAPH::Node<int> node2("2", 2);
  std::pair<const CXXGRAPH::Node<int> *, const CXXGRAPH::Node<int> *> pairNode(
      &node1, &node2);
  CXXGRAPH::UndirectedWeightedEdge<int> edge(1, pairNode, 10);
  ASSERT_TRUE(edge.isWeighted().value());
}

TEST(UndirectedWeightedEdgeTest, Constructor_5) {
  CXXGRAPH::Node<int> node1("1", 1);
  CXXGRAPH::Node<int> node2("2", 2);
  std::pair<const CXXGRAPH::Node<int> *, const CXXGRAPH::Node<int> *> pairNode(
      &node1, &node2);
  CXXGRAPH::Edge<int> base_edge(1, pairNode);
  CXXGRAPH::UndirectedWeightedEdge<int> edge(base_edge, 10);
  ASSERT_EQ(edge.getNodePair(), pairNode);
  ASSERT_EQ(*(edge.getNodePair().first), node1);
  ASSERT_EQ(*(edge.getNodePair().second), node2);
  ASSERT_FALSE(edge.isDirected().value());
  ASSERT_TRUE(edge.isWeighted().value());
  ASSERT_EQ(edge.getWeight(), 10);
}

TEST(UndirectedWeightedEdgeTest, Constructor_6) {
  CXXGRAPH::Node<int> node1("1", 1);
  CXXGRAPH::Node<int> node2("2", 2);
  std::pair<const CXXGRAPH::Node<int> *, const CXXGRAPH::Node<int> *> pairNode(
      &node1, &node2);
  CXXGRAPH::Edge<int> base_edge(1, pairNode);
  CXXGRAPH::UndirectedWeightedEdge<int> edge(base_edge);
  ASSERT_EQ(edge.getNodePair(), pairNode);
  ASSERT_EQ(*(edge.getNodePair().first), node1);
  ASSERT_EQ(*(edge.getNodePair().second), node2);
  ASSERT_FALSE(edge.isDirected().value());
  ASSERT_TRUE(edge.isWeighted().value());
  ASSERT_EQ(edge.getWeight(), 0.0);
}

TEST(UndirectedWeightedEdgeTest, Constructor_7) {
  CXXGRAPH::Node<int> node1("1", 1);
  CXXGRAPH::Node<int> node2("2", 2);
  std::pair<const CXXGRAPH::Node<int> *, const CXXGRAPH::Node<int> *> pairNode(
      &node1, &node2);
  CXXGRAPH::UndirectedEdge<int> base_edge(1, pairNode);
  CXXGRAPH::UndirectedWeightedEdge<int> edge(base_edge);
  ASSERT_EQ(edge.getNodePair(), pairNode);
  ASSERT_EQ(*(edge.getNodePair().first), node1);
  ASSERT_EQ(*(edge.getNodePair().second), node2);
  ASSERT_FALSE(edge.isDirected().value());
  ASSERT_TRUE(edge.isWeighted().value());
  ASSERT_EQ(edge.getWeight(), 0.0);
}

TEST(UndirectedWeightedEdgeTest, Cast_1) {
  CXXGRAPH::Node<int> node1("1", 1);
  CXXGRAPH::Node<int> node2("2", 2);
  std::pair<const CXXGRAPH::Node<int> *, const CXXGRAPH::Node<int> *> pairNode(
      &node1, &node2);
  CXXGRAPH::Edge<int> base_edge(1, pairNode);
  CXXGRAPH::UndirectedWeightedEdge<int> edge = base_edge;
  ASSERT_EQ(edge.getNodePair(), pairNode);
  ASSERT_EQ(*(edge.getNodePair().first), node1);
  ASSERT_EQ(*(edge.getNodePair().second), node2);
  ASSERT_FALSE(edge.isDirected().value());
  ASSERT_TRUE(edge.isWeighted().value());
  ASSERT_EQ(edge.getWeight(), 0.0);
}

TEST(UndirectedWeightedEdgeTest, Cast_2) {
  CXXGRAPH::Node<int> node1("1", 1);
  CXXGRAPH::Node<int> node2("2", 2);
  std::pair<const CXXGRAPH::Node<int> *, const CXXGRAPH::Node<int> *> pairNode(
      &node1, &node2);
  CXXGRAPH::UndirectedEdge<int> base_edge(1, pairNode);
  CXXGRAPH::UndirectedWeightedEdge<int> edge = base_edge;
  ASSERT_FALSE(base_edge.isDirected().value());
  ASSERT_EQ(edge.getNodePair(), pairNode);
  ASSERT_EQ(*(edge.getNodePair().first), node1);
  ASSERT_EQ(*(edge.getNodePair().second), node2);
  ASSERT_FALSE(edge.isDirected().value());
  ASSERT_TRUE(edge.isWeighted().value());
  ASSERT_EQ(edge.getWeight(), 0.0);
}

TEST(UndirectedWeightedEdgeTest, Cast_3) {
  CXXGRAPH::Node<int> node1("1", 1);
  CXXGRAPH::Node<int> node2("2", 2);
  std::pair<const CXXGRAPH::Node<int> *, const CXXGRAPH::Node<int> *> pairNode(
      &node1, &node2);
  CXXGRAPH::DirectedEdge<int> base_edge(1, pairNode);
  CXXGRAPH::UndirectedWeightedEdge<int> edge = base_edge;
  ASSERT_TRUE(base_edge.isDirected().value());
  ASSERT_EQ(edge.getNodePair(), pairNode);
  ASSERT_EQ(*(edge.getNodePair().first), node1);
  ASSERT_EQ(*(edge.getNodePair().second), node2);
  ASSERT_FALSE(edge.isDirected().value());
  ASSERT_TRUE(edge.isWeighted().value());
  ASSERT_EQ(edge.getWeight(), 0.0);
}

TEST(UndirectedWeightedEdgeTest, Cast_4) {
  CXXGRAPH::Node<int> node1("1", 1);
  CXXGRAPH::Node<int> node2("2", 2);
  std::pair<const CXXGRAPH::Node<int> *, const CXXGRAPH::Node<int> *> pairNode(
      &node1, &node2);
  CXXGRAPH::DirectedWeightedEdge<int> base_edge(1, pairNode, 10);
  CXXGRAPH::UndirectedWeightedEdge<int> edge = base_edge;
  ASSERT_TRUE(base_edge.isDirected().value());
  ASSERT_TRUE(base_edge.isWeighted().value());
  ASSERT_EQ(edge.getNodePair(), pairNode);
  ASSERT_EQ(*(edge.getNodePair().first), node1);
  ASSERT_EQ(*(edge.getNodePair().second), node2);
  ASSERT_FALSE(edge.isDirected().value());
  ASSERT_TRUE(edge.isWeighted().value());
  ASSERT_EQ(edge.getWeight(), 10);
}

TEST(UndirectedWeightedEdgeTest, print_1) {
  CXXGRAPH::Node<int> node1("1", 1);
  CXXGRAPH::Node<int> node2("2", 2);
  CXXGRAPH::UndirectedWeightedEdge<int> edge(1, node1, node2, 10);
  std::cout << "Test Print UndirectedWeightedEdge" << std::endl;
  std::cout << edge << std::endl;
}
