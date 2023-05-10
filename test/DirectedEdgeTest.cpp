#include "CXXGraph.hpp"
#include "gtest/gtest.h"

TEST(DirectedEdgeTest, Constructor_1) {
  CXXGraph::Node<int> node1("1", 1);
  CXXGraph::Node<int> node2("2", 2);
  CXXGraph::DirectedEdge<int> edge(1, node1, node2);
  ASSERT_EQ(*(edge.getNodePair().first), node1);
  ASSERT_EQ(*(edge.getNodePair().second), node2);
}

TEST(DirectedEdgeTest, Constructor_2) {
  CXXGraph::Node<int> node1("1", 1);
  CXXGraph::Node<int> node2("2", 2);
  std::pair<const CXXGraph::Node<int> *, const CXXGraph::Node<int> *> pairNode(
      &node1, &node2);
  CXXGraph::DirectedEdge<int> edge(1, pairNode);
  ASSERT_EQ(edge.getNodePair(), pairNode);
  ASSERT_EQ(*(edge.getNodePair().first), node1);
  ASSERT_EQ(*(edge.getNodePair().second), node2);
}

TEST(DirectedEdgeTest, Constructor_3) {
  CXXGraph::Node<int> node1("1", 1);
  CXXGraph::Node<int> node2("2", 2);
  std::pair<const CXXGraph::Node<int> *, const CXXGraph::Node<int> *> pairNode(
      &node1, &node2);
  CXXGraph::DirectedEdge<int> edge(1, pairNode);
  ASSERT_TRUE(edge.isDirected().value());
}

TEST(DirectedEdgeTest, Constructor_4) {
  CXXGraph::Node<int> node1("1", 1);
  CXXGraph::Node<int> node2("2", 2);
  std::pair<const CXXGraph::Node<int> *, const CXXGraph::Node<int> *> pairNode(
      &node1, &node2);
  CXXGraph::DirectedEdge<int> edge(1, pairNode);
  ASSERT_FALSE(edge.isWeighted().value());
}

TEST(DirectedEdgeTest, Constructor_5) {
  CXXGraph::Node<int> node1("1", 1);
  CXXGraph::Node<int> node2("2", 2);
  std::pair<const CXXGraph::Node<int> *, const CXXGraph::Node<int> *> pairNode(
      &node1, &node2);
  CXXGraph::Edge<int> base_edge(1, pairNode);
  CXXGraph::DirectedEdge<int> edge(base_edge);
  ASSERT_EQ(edge.getNodePair(), pairNode);
  ASSERT_EQ(*(edge.getNodePair().first), node1);
  ASSERT_EQ(*(edge.getNodePair().second), node2);
  ASSERT_TRUE(edge.isDirected().value());
  ASSERT_FALSE(edge.isWeighted().value());
}

TEST(DirectedEdgeTest, Cast_1) {
  CXXGraph::Node<int> node1("1", 1);
  CXXGraph::Node<int> node2("2", 2);
  std::pair<const CXXGraph::Node<int> *, const CXXGraph::Node<int> *> pairNode(
      &node1, &node2);
  CXXGraph::Edge<int> base_edge(1, pairNode);
  CXXGraph::DirectedEdge<int> edge = base_edge;
  ASSERT_EQ(edge.getNodePair(), pairNode);
  ASSERT_EQ(*(edge.getNodePair().first), node1);
  ASSERT_EQ(*(edge.getNodePair().second), node2);
  ASSERT_TRUE(edge.isDirected().value());
  ASSERT_FALSE(edge.isWeighted().value());
}

TEST(DirectedEdgeTest, Cast_2) {
  CXXGraph::Node<int> node1("1", 1);
  CXXGraph::Node<int> node2("2", 2);
  std::pair<const CXXGraph::Node<int> *, const CXXGraph::Node<int> *> pairNode(
      &node1, &node2);
  CXXGraph::UndirectedEdge<int> base_edge(1, pairNode);
  CXXGraph::DirectedEdge<int> edge = base_edge;
  ASSERT_FALSE(base_edge.isDirected().value());
  ASSERT_EQ(edge.getNodePair(), pairNode);
  ASSERT_EQ(*(edge.getNodePair().first), node1);
  ASSERT_EQ(*(edge.getNodePair().second), node2);
  ASSERT_TRUE(edge.isDirected().value());
  ASSERT_FALSE(edge.isWeighted().value());
}

TEST(DirectedEdgeTest, print_1) {
  CXXGraph::Node<int> node1("1", 1);
  CXXGraph::Node<int> node2("2", 2);
  CXXGraph::DirectedEdge<int> edge(1, node1, node2);
  std::cout << "Test Print DirectedEdge" << std::endl;
  std::cout << edge << std::endl;
}
