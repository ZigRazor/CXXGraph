#include "CXXGraph/CXXGraph.hpp"
#include "gtest/gtest.h"

TEST(UndirectedWeightedEdgeTest, Constructor_1) {
  CXXGraph::Node<int> node1("1", 1);
  CXXGraph::Node<int> node2("2", 2);
  CXXGraph::UndirectedWeightedEdge<int> edge("1", node1, node2, 10);
  ASSERT_EQ(*(edge.getNodePair().first), node1);
  ASSERT_EQ(*(edge.getNodePair().second), node2);
  ASSERT_EQ(edge.getWeight(), 10);
}

TEST(UndirectedWeightedEdgeTest, Constructor_2) {
  CXXGraph::Node<int> node1("1", 1);
  CXXGraph::Node<int> node2("2", 2);
  std::pair<const CXXGraph::Node<int> *, const CXXGraph::Node<int> *> pairNode(
      &node1, &node2);
  CXXGraph::UndirectedWeightedEdge<int> edge("1", pairNode, 10);
  /* ASSERT_EQ(edge.getNodePair(), pairNode); */
  ASSERT_EQ(*(edge.getNodePair().first), node1);
  ASSERT_EQ(*(edge.getNodePair().second), node2);
  ASSERT_EQ(edge.getWeight(), 10);
}

TEST(UndirectedWeightedEdgeTest, Constructor_3) {
  CXXGraph::Node<int> node1("1", 1);
  CXXGraph::Node<int> node2("2", 2);
  std::pair<const CXXGraph::Node<int> *, const CXXGraph::Node<int> *> pairNode(
      &node1, &node2);
  CXXGraph::UndirectedWeightedEdge<int> edge("1", pairNode, 10);
  ASSERT_FALSE(edge.isDirected().value());
}

TEST(UndirectedWeightedEdgeTest, Constructor_4) {
  CXXGraph::Node<int> node1("1", 1);
  CXXGraph::Node<int> node2("2", 2);
  std::pair<const CXXGraph::Node<int> *, const CXXGraph::Node<int> *> pairNode(
      &node1, &node2);
  CXXGraph::UndirectedWeightedEdge<int> edge("1", pairNode, 10);
  ASSERT_TRUE(edge.isWeighted().value());
}

TEST(UndirectedWeightedEdgeTest, Constructor_5) {
  CXXGraph::Node<int> node1("1", 1);
  CXXGraph::Node<int> node2("2", 2);
  std::pair<const CXXGraph::Node<int> *, const CXXGraph::Node<int> *> pairNode(
      &node1, &node2);
  CXXGraph::Edge<int> base_edge("1", pairNode);
  CXXGraph::UndirectedWeightedEdge<int> edge(base_edge, 10);
  /* ASSERT_EQ(edge.getNodePair(), pairNode); */
  ASSERT_EQ(*(edge.getNodePair().first), node1);
  ASSERT_EQ(*(edge.getNodePair().second), node2);
  ASSERT_FALSE(edge.isDirected().value());
  ASSERT_TRUE(edge.isWeighted().value());
  ASSERT_EQ(edge.getWeight(), 10);
}

TEST(UndirectedWeightedEdgeTest, Constructor_6) {
  CXXGraph::Node<int> node1("1", 1);
  CXXGraph::Node<int> node2("2", 2);
  std::pair<const CXXGraph::Node<int> *, const CXXGraph::Node<int> *> pairNode(
      &node1, &node2);
  CXXGraph::Edge<int> base_edge("1", pairNode);
  CXXGraph::UndirectedWeightedEdge<int> edge(base_edge);
  /* ASSERT_EQ(edge.getNodePair(), pairNode); */
  ASSERT_EQ(*(edge.getNodePair().first), node1);
  ASSERT_EQ(*(edge.getNodePair().second), node2);
  ASSERT_FALSE(edge.isDirected().value());
  ASSERT_TRUE(edge.isWeighted().value());
  ASSERT_EQ(edge.getWeight(), 0.0);
}

TEST(UndirectedWeightedEdgeTest, Constructor_7) {
  CXXGraph::Node<int> node1("1", 1);
  CXXGraph::Node<int> node2("2", 2);
  std::pair<const CXXGraph::Node<int> *, const CXXGraph::Node<int> *> pairNode(
      &node1, &node2);
  CXXGraph::UndirectedEdge<int> base_edge("1", pairNode);
  CXXGraph::UndirectedWeightedEdge<int> edge(base_edge);
  /* ASSERT_EQ(edge.getNodePair(), pairNode); */
  ASSERT_EQ(*(edge.getNodePair().first), node1);
  ASSERT_EQ(*(edge.getNodePair().second), node2);
  ASSERT_FALSE(edge.isDirected().value());
  ASSERT_TRUE(edge.isWeighted().value());
  ASSERT_EQ(edge.getWeight(), 0.0);
}

TEST(UndirectedWeightedEdgeTest, Bool_data) {
  // First constructor
  CXXGraph::Node<bool> node1("1", true);
  CXXGraph::Node<bool> node2("2", false);
  CXXGraph::UndirectedWeightedEdge<bool> edge1("1", node1, node2, 4);
  ASSERT_EQ(*(edge1.getNodePair().first), node1);
  ASSERT_EQ(*(edge1.getNodePair().second), node2);
  ASSERT_FALSE(edge1.isDirected().value());
  ASSERT_TRUE(edge1.isWeighted().value());

  // Second constructor
  CXXGraph::Node<bool> node3("3", true);
  CXXGraph::Node<bool> node4("4", false);
  std::pair<const CXXGraph::Node<bool> *, const CXXGraph::Node<bool> *>
      pairNode(&node3, &node4);
  CXXGraph::UndirectedWeightedEdge<bool> edge2("2", pairNode, 7);
  /* ASSERT_EQ(edge2.getNodePair(), pairNode); */
  ASSERT_EQ(*(edge2.getNodePair().first), node3);
  ASSERT_EQ(*(edge2.getNodePair().second), node4);
  ASSERT_FALSE(edge2.isDirected().value());
  ASSERT_TRUE(edge2.isWeighted().value());
}

TEST(UndirectedWeightedEdgeTest, String_data) {
  // First constructor
  CXXGraph::Node<bool> node1("1", "On");
  CXXGraph::Node<bool> node2("2", "Off");
  CXXGraph::UndirectedWeightedEdge<bool> edge1("1", node1, node2, 3);
  ASSERT_EQ(*(edge1.getNodePair().first), node1);
  ASSERT_EQ(*(edge1.getNodePair().second), node2);
  ASSERT_FALSE(edge1.isDirected().value());
  ASSERT_TRUE(edge1.isWeighted().value());

  // Second constructor
  CXXGraph::Node<bool> node3("3", "On");
  CXXGraph::Node<bool> node4("4", "Off");
  std::pair<const CXXGraph::Node<bool> *, const CXXGraph::Node<bool> *>
      pairNode(&node3, &node4);
  CXXGraph::UndirectedWeightedEdge<bool> edge2("2", pairNode, 5);
  /* ASSERT_EQ(edge2.getNodePair(), pairNode); */
  ASSERT_EQ(*(edge2.getNodePair().first), node3);
  ASSERT_EQ(*(edge2.getNodePair().second), node4);
  ASSERT_FALSE(edge2.isDirected().value());
  ASSERT_TRUE(edge2.isWeighted().value());
}

TEST(UndirectedWeightedEdgeTest, Cast_1) {
  CXXGraph::Node<int> node1("1", 1);
  CXXGraph::Node<int> node2("2", 2);
  std::pair<const CXXGraph::Node<int> *, const CXXGraph::Node<int> *> pairNode(
      &node1, &node2);
  CXXGraph::Edge<int> base_edge("1", pairNode);
  CXXGraph::UndirectedWeightedEdge<int> edge = base_edge;
  /* ASSERT_EQ(edge.getNodePair(), pairNode); */
  ASSERT_EQ(*(edge.getNodePair().first), node1);
  ASSERT_EQ(*(edge.getNodePair().second), node2);
  ASSERT_FALSE(edge.isDirected().value());
  ASSERT_TRUE(edge.isWeighted().value());
  ASSERT_EQ(edge.getWeight(), 0.0);
}

TEST(UndirectedWeightedEdgeTest, Cast_2) {
  CXXGraph::Node<int> node1("1", 1);
  CXXGraph::Node<int> node2("2", 2);
  std::pair<const CXXGraph::Node<int> *, const CXXGraph::Node<int> *> pairNode(
      &node1, &node2);
  CXXGraph::UndirectedEdge<int> base_edge("1", pairNode);
  CXXGraph::UndirectedWeightedEdge<int> edge = base_edge;
  ASSERT_FALSE(base_edge.isDirected().value());
  /* ASSERT_EQ(edge.getNodePair(), pairNode); */
  ASSERT_EQ(*(edge.getNodePair().first), node1);
  ASSERT_EQ(*(edge.getNodePair().second), node2);
  ASSERT_FALSE(edge.isDirected().value());
  ASSERT_TRUE(edge.isWeighted().value());
  ASSERT_EQ(edge.getWeight(), 0.0);
}

TEST(UndirectedWeightedEdgeTest, Cast_3) {
  CXXGraph::Node<int> node1("1", 1);
  CXXGraph::Node<int> node2("2", 2);
  std::pair<const CXXGraph::Node<int> *, const CXXGraph::Node<int> *> pairNode(
      &node1, &node2);
  CXXGraph::DirectedEdge<int> base_edge("1", pairNode);
  CXXGraph::UndirectedWeightedEdge<int> edge = base_edge;
  ASSERT_TRUE(base_edge.isDirected().value());
  /* ASSERT_EQ(edge.getNodePair(), pairNode); */
  ASSERT_EQ(*(edge.getNodePair().first), node1);
  ASSERT_EQ(*(edge.getNodePair().second), node2);
  ASSERT_FALSE(edge.isDirected().value());
  ASSERT_TRUE(edge.isWeighted().value());
  ASSERT_EQ(edge.getWeight(), 0.0);
}

TEST(UndirectedWeightedEdgeTest, Cast_4) {
  CXXGraph::Node<int> node1("1", 1);
  CXXGraph::Node<int> node2("2", 2);
  std::pair<const CXXGraph::Node<int> *, const CXXGraph::Node<int> *> pairNode(
      &node1, &node2);
  CXXGraph::DirectedWeightedEdge<int> base_edge("1", pairNode, 10);
  CXXGraph::UndirectedWeightedEdge<int> edge = base_edge;
  ASSERT_TRUE(base_edge.isDirected().value());
  ASSERT_TRUE(base_edge.isWeighted().value());
  /* ASSERT_EQ(edge.getNodePair(), pairNode); */
  ASSERT_EQ(*(edge.getNodePair().first), node1);
  ASSERT_EQ(*(edge.getNodePair().second), node2);
  ASSERT_FALSE(edge.isDirected().value());
  ASSERT_TRUE(edge.isWeighted().value());
  ASSERT_EQ(edge.getWeight(), 10);
}

TEST(UndirectedWeightedEdgeTest, print_1) {
  CXXGraph::Node<int> node1("1", 1);
  CXXGraph::Node<int> node2("2", 2);
  CXXGraph::UndirectedWeightedEdge<int> edge("1", node1, node2, 10);
  std::cout << "Test Print UndirectedWeightedEdge" << std::endl;
  std::cout << edge << std::endl;
}
