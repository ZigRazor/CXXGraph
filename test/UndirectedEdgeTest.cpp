#include "CXXGraph.hpp"
#include "gtest/gtest.h"

TEST(UndirectedEdgeTest, Constructor_1) {
  CXXGraph::Node<int> node1("1", 1);
  CXXGraph::Node<int> node2("2", 2);
  CXXGraph::UndirectedEdge<int> edge(1, node1, node2);
  ASSERT_EQ(*(edge.getNodePair().first), node1);
  ASSERT_EQ(*(edge.getNodePair().second), node2);
}

TEST(UndirectedEdgeTest, Constructor_2) {
  CXXGraph::Node<int> node1("1", 1);
  CXXGraph::Node<int> node2("2", 2);
  std::pair<const CXXGraph::Node<int> *, const CXXGraph::Node<int> *> pairNode(
      &node1, &node2);
  CXXGraph::UndirectedEdge<int> edge(1, pairNode);
  ASSERT_EQ(edge.getNodePair(), pairNode);
  ASSERT_EQ(*(edge.getNodePair().first), node1);
  ASSERT_EQ(*(edge.getNodePair().second), node2);
}

TEST(UndirectedEdgeTest, Constructor_3) {
  CXXGraph::Node<int> node1("1", 1);
  CXXGraph::Node<int> node2("2", 2);
  std::pair<const CXXGraph::Node<int> *, const CXXGraph::Node<int> *> pairNode(
      &node1, &node2);
  CXXGraph::UndirectedEdge<int> edge(1, pairNode);
  ASSERT_FALSE(edge.isDirected().value());
}

TEST(UndirectedEdgeTest, Constructor_4) {
  CXXGraph::Node<int> node1("1", 1);
  CXXGraph::Node<int> node2("2", 2);
  std::pair<const CXXGraph::Node<int> *, const CXXGraph::Node<int> *> pairNode(
      &node1, &node2);
  CXXGraph::UndirectedEdge<int> edge(1, pairNode);
  ASSERT_FALSE(edge.isWeighted().value());
}

TEST(UndirectedEdgeTest, Constructor_5) {
  CXXGraph::Node<int> node1("1", 1);
  CXXGraph::Node<int> node2("2", 2);
  std::pair<const CXXGraph::Node<int> *, const CXXGraph::Node<int> *> pairNode(
      &node1, &node2);
  CXXGraph::Edge<int> base_edge(1, pairNode);
  CXXGraph::UndirectedEdge<int> edge(base_edge);
  ASSERT_EQ(edge.getNodePair(), pairNode);
  ASSERT_EQ(*(edge.getNodePair().first), node1);
  ASSERT_EQ(*(edge.getNodePair().second), node2);
  ASSERT_FALSE(edge.isDirected().value());
  ASSERT_FALSE(edge.isWeighted().value());
}

TEST(UndirectedEdgeTest, Cast_1) {
  CXXGraph::Node<int> node1("1", 1);
  CXXGraph::Node<int> node2("2", 2);
  std::pair<const CXXGraph::Node<int> *, const CXXGraph::Node<int> *> pairNode(
      &node1, &node2);
  CXXGraph::Edge<int> base_edge(1, pairNode);
  CXXGraph::UndirectedEdge<int> edge = base_edge;
  ASSERT_EQ(edge.getNodePair(), pairNode);
  ASSERT_EQ(*(edge.getNodePair().first), node1);
  ASSERT_EQ(*(edge.getNodePair().second), node2);
  ASSERT_FALSE(edge.isDirected().value());
  ASSERT_FALSE(edge.isWeighted().value());
}

TEST(UndirectedEdgeTest, Cast_2) {
  CXXGraph::Node<int> node1("1", 1);
  CXXGraph::Node<int> node2("2", 2);
  std::pair<const CXXGraph::Node<int> *, const CXXGraph::Node<int> *> pairNode(
      &node1, &node2);
  CXXGraph::DirectedEdge<int> base_edge(1, pairNode);
  CXXGraph::UndirectedEdge<int> edge = base_edge;
  ASSERT_TRUE(base_edge.isDirected().value());
  ASSERT_EQ(edge.getNodePair(), pairNode);
  ASSERT_EQ(*(edge.getNodePair().first), node1);
  ASSERT_EQ(*(edge.getNodePair().second), node2);
  ASSERT_FALSE(edge.isDirected().value());
  ASSERT_FALSE(edge.isWeighted().value());
}

TEST(UndirectedEdgeTest, print_1) {
  CXXGraph::Node<int> node1("1", 1);
  CXXGraph::Node<int> node2("2", 2);
  CXXGraph::UndirectedEdge<int> edge(1, node1, node2);
  std::cout << "Test Print UndirectedEdge" << std::endl;
  std::cout << edge << std::endl;
}