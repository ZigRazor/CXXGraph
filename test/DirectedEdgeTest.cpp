#include "CXXGraph.hpp"
#include "gtest/gtest.h"

TEST(DirectedEdgeTest, Constructor_1) {
  CXXGRAPH::Node<int> node1("1", 1);
  CXXGRAPH::Node<int> node2("2", 2);
  CXXGRAPH::DirectedEdge<int> edge(1, node1, node2);
  ASSERT_EQ(*(edge.getNodePair().first), node1);
  ASSERT_EQ(*(edge.getNodePair().second), node2);
}

TEST(DirectedEdgeTest, Constructor_2) {
  CXXGRAPH::Node<int> node1("1", 1);
  CXXGRAPH::Node<int> node2("2", 2);
  std::pair<const CXXGRAPH::Node<int> *, const CXXGRAPH::Node<int> *> pairNode(
      &node1, &node2);
  CXXGRAPH::DirectedEdge<int> edge(1, pairNode);
  ASSERT_EQ(edge.getNodePair(), pairNode);
  ASSERT_EQ(*(edge.getNodePair().first), node1);
  ASSERT_EQ(*(edge.getNodePair().second), node2);
}

TEST(DirectedEdgeTest, Constructor_3) {
  CXXGRAPH::Node<int> node1("1", 1);
  CXXGRAPH::Node<int> node2("2", 2);
  std::pair<const CXXGRAPH::Node<int> *, const CXXGRAPH::Node<int> *> pairNode(
      &node1, &node2);
  CXXGRAPH::DirectedEdge<int> edge(1, pairNode);
  ASSERT_TRUE(edge.isDirected().value());
}

TEST(DirectedEdgeTest, Constructor_4) {
  CXXGRAPH::Node<int> node1("1", 1);
  CXXGRAPH::Node<int> node2("2", 2);
  std::pair<const CXXGRAPH::Node<int> *, const CXXGRAPH::Node<int> *> pairNode(
      &node1, &node2);
  CXXGRAPH::DirectedEdge<int> edge(1, pairNode);
  ASSERT_FALSE(edge.isWeighted().value());
}

TEST(DirectedEdgeTest, Constructor_5) {
  CXXGRAPH::Node<int> node1("1", 1);
  CXXGRAPH::Node<int> node2("2", 2);
  std::pair<const CXXGRAPH::Node<int> *, const CXXGRAPH::Node<int> *> pairNode(
      &node1, &node2);
  CXXGRAPH::Edge<int> base_edge(1, pairNode);
  CXXGRAPH::DirectedEdge<int> edge(base_edge);
  ASSERT_EQ(edge.getNodePair(), pairNode);
  ASSERT_EQ(*(edge.getNodePair().first), node1);
  ASSERT_EQ(*(edge.getNodePair().second), node2);
  ASSERT_TRUE(edge.isDirected().value());
  ASSERT_FALSE(edge.isWeighted().value());
}

TEST(DirectedEdgeTest, Cast_1) {
  CXXGRAPH::Node<int> node1("1", 1);
  CXXGRAPH::Node<int> node2("2", 2);
  std::pair<const CXXGRAPH::Node<int> *, const CXXGRAPH::Node<int> *> pairNode(
      &node1, &node2);
  CXXGRAPH::Edge<int> base_edge(1, pairNode);
  CXXGRAPH::DirectedEdge<int> edge = base_edge;
  ASSERT_EQ(edge.getNodePair(), pairNode);
  ASSERT_EQ(*(edge.getNodePair().first), node1);
  ASSERT_EQ(*(edge.getNodePair().second), node2);
  ASSERT_TRUE(edge.isDirected().value());
  ASSERT_FALSE(edge.isWeighted().value());
}

TEST(DirectedEdgeTest, Cast_2) {
  CXXGRAPH::Node<int> node1("1", 1);
  CXXGRAPH::Node<int> node2("2", 2);
  std::pair<const CXXGRAPH::Node<int> *, const CXXGRAPH::Node<int> *> pairNode(
      &node1, &node2);
  CXXGRAPH::UndirectedEdge<int> base_edge(1, pairNode);
  CXXGRAPH::DirectedEdge<int> edge = base_edge;
  ASSERT_FALSE(base_edge.isDirected().value());
  ASSERT_EQ(edge.getNodePair(), pairNode);
  ASSERT_EQ(*(edge.getNodePair().first), node1);
  ASSERT_EQ(*(edge.getNodePair().second), node2);
  ASSERT_TRUE(edge.isDirected().value());
  ASSERT_FALSE(edge.isWeighted().value());
}

TEST(DirectedEdgeTest, print_1) {
  CXXGRAPH::Node<int> node1("1", 1);
  CXXGRAPH::Node<int> node2("2", 2);
  CXXGRAPH::DirectedEdge<int> edge(1, node1, node2);
  std::cout << "Test Print DirectedEdge" << std::endl;
  std::cout << edge << std::endl;
}
