#include "CXXGraph/CXXGraph.hpp"
#include "gtest/gtest.h"

// Smart pointers alias
template <typename T>
using unique = std::unique_ptr<T>;
template <typename T>
using shared = std::shared_ptr<T>;

using std::make_shared;
using std::make_unique;

TEST(DirectedEdgeTest, Constructor_1) {
  CXXGraph::Node<int> node1("1", 1);
  CXXGraph::Node<int> node2("2", 2);
  CXXGraph::DirectedEdge<int> edge("1", node1, node2);
  ASSERT_EQ(*(edge.getNodePair().first), node1);
  ASSERT_EQ(*(edge.getNodePair().second), node2);
}

TEST(DirectedEdgeTest, Constructor_2) {
  CXXGraph::Node<int> node1("1", 1);
  CXXGraph::Node<int> node2("2", 2);
  std::pair<const CXXGraph::Node<int> *, const CXXGraph::Node<int> *> pairNode(
      &node1, &node2);
  CXXGraph::DirectedEdge<int> edge("1", pairNode);
  /* ASSERT_EQ(edge.getNodePair(), pairNode); */
  ASSERT_EQ(*(edge.getNodePair().first), node1);
  ASSERT_EQ(*(edge.getNodePair().second), node2);
}

TEST(DirectedEdgeTest, Constructor_3) {
  CXXGraph::Node<int> node1("1", 1);
  CXXGraph::Node<int> node2("2", 2);
  std::pair<const CXXGraph::Node<int> *, const CXXGraph::Node<int> *> pairNode(
      &node1, &node2);
  CXXGraph::DirectedEdge<int> edge("1", pairNode);
  ASSERT_TRUE(edge.isDirected().value());
}

TEST(DirectedEdgeTest, Constructor_4) {
  CXXGraph::Node<int> node1("1", 1);
  CXXGraph::Node<int> node2("2", 2);
  std::pair<const CXXGraph::Node<int> *, const CXXGraph::Node<int> *> pairNode(
      &node1, &node2);
  CXXGraph::DirectedEdge<int> edge("1", pairNode);
  ASSERT_FALSE(edge.isWeighted().value());
}

TEST(DirectedEdgeTest, Constructor_5) {
  CXXGraph::Node<int> node1("1", 1);
  CXXGraph::Node<int> node2("2", 2);
  std::pair<const CXXGraph::Node<int> *, const CXXGraph::Node<int> *> pairNode(
      &node1, &node2);
  CXXGraph::Edge<int> base_edge("1", pairNode);
  CXXGraph::DirectedEdge<int> edge(base_edge);
  /* ASSERT_EQ(edge.getNodePair(), pairNode); */
  ASSERT_EQ(*(edge.getNodePair().first), node1);
  ASSERT_EQ(*(edge.getNodePair().second), node2);
  ASSERT_TRUE(edge.isDirected().value());
  ASSERT_FALSE(edge.isWeighted().value());
}

TEST(DirectedEdgeTest, Bool_data) {
  // First constructor
  CXXGraph::Node<bool> node1("1", true);
  CXXGraph::Node<bool> node2("2", false);
  CXXGraph::DirectedEdge<bool> edge1("1", node1, node2);
  ASSERT_EQ(*(edge1.getNodePair().first), node1);
  ASSERT_EQ(*(edge1.getNodePair().second), node2);
  ASSERT_TRUE(edge1.isDirected().value());
  ASSERT_FALSE(edge1.isWeighted().value());

  // Second constructor
  CXXGraph::Node<bool> node3("3", true);
  CXXGraph::Node<bool> node4("4", false);
  std::pair<const CXXGraph::Node<bool> *, const CXXGraph::Node<bool> *>
      pairNode(&node3, &node4);
  CXXGraph::DirectedEdge<bool> edge2("2", pairNode);
  /* ASSERT_EQ(edge2.getNodePair(), pairNode); */
  ASSERT_EQ(*(edge2.getNodePair().first), node3);
  ASSERT_EQ(*(edge2.getNodePair().second), node4);
  ASSERT_TRUE(edge2.isDirected().value());
  ASSERT_FALSE(edge2.isWeighted().value());
}

TEST(DirectedEdgeTest, String_data) {
  // First constructor
  CXXGraph::Node<bool> node1("1", "On");
  CXXGraph::Node<bool> node2("2", "Off");
  CXXGraph::DirectedEdge<bool> edge1("1", node1, node2);
  ASSERT_EQ(*(edge1.getNodePair().first), node1);
  ASSERT_EQ(*(edge1.getNodePair().second), node2);
  ASSERT_TRUE(edge1.isDirected().value());
  ASSERT_FALSE(edge1.isWeighted().value());

  // Second constructor
  CXXGraph::Node<bool> node3("3", "On");
  CXXGraph::Node<bool> node4("4", "Off");
  std::pair<const CXXGraph::Node<bool> *, const CXXGraph::Node<bool> *>
      pairNode(&node3, &node4);
  CXXGraph::DirectedEdge<bool> edge2("2", pairNode);
  /* ASSERT_EQ(edge2.getNodePair(), pairNode); */
  ASSERT_EQ(*(edge2.getNodePair().first), node3);
  ASSERT_EQ(*(edge2.getNodePair().second), node4);
  ASSERT_TRUE(edge2.isDirected().value());
  ASSERT_FALSE(edge2.isWeighted().value());
}

TEST(DirectedEdgeTest, Cast_1) {
  CXXGraph::Node<int> node1("1", 1);
  CXXGraph::Node<int> node2("2", 2);
  std::pair<const CXXGraph::Node<int> *, const CXXGraph::Node<int> *> pairNode(
      &node1, &node2);
  CXXGraph::Edge<int> base_edge("1", pairNode);
  CXXGraph::DirectedEdge<int> edge = base_edge;
  /* ASSERT_EQ(edge.getNodePair(), pairNode); */
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
  CXXGraph::UndirectedEdge<int> base_edge("1", pairNode);
  CXXGraph::DirectedEdge<int> edge = base_edge;
  ASSERT_FALSE(base_edge.isDirected().value());
  /* ASSERT_EQ(edge.getNodePair(), pairNode); */
  ASSERT_EQ(*(edge.getNodePair().first), node1);
  ASSERT_EQ(*(edge.getNodePair().second), node2);
  ASSERT_TRUE(edge.isDirected().value());
  ASSERT_FALSE(edge.isWeighted().value());
}

TEST(DirectedEdgeTest, print_1) {
  CXXGraph::Node<int> node1("1", 1);
  CXXGraph::Node<int> node2("2", 2);
  CXXGraph::DirectedEdge<int> edge("1", node1, node2);
  std::cout << "Test Print DirectedEdge" << std::endl;
  std::cout << edge << std::endl;
}

TEST(DirectedEdgeTest, inOutNeigbors_1) {
  CXXGraph::Graph<int> graph;

  CXXGraph::Node<int> node1("1", 1);
  CXXGraph::Node<int> node2("2", 2);
  CXXGraph::Node<int> node3("3", 3);

  for (auto &&n : {node1, node2, node3}) {
    graph.addNode(&n);
  }

  CXXGraph::DirectedEdge<int> edge1("1", node1, node2);
  CXXGraph::DirectedEdge<int> edge2("2", node2, node3);

  for (auto &&edge : {edge1, edge2}) {
    graph.addEdge(&edge);
  }

  ASSERT_EQ(graph.outNotInNeighbors(&node1).size(), 1);
  ASSERT_EQ(graph.outNotInNeighbors(&node2).size(), 1);
  ASSERT_EQ(graph.outNotInNeighbors(&node3).size(), 0);

  ASSERT_EQ(graph.inNotOutNeighbors(&node1).size(), 0);
  ASSERT_EQ(graph.inNotOutNeighbors(&node2).size(), 1);
  ASSERT_EQ(graph.inNotOutNeighbors(&node3).size(), 1);

  ASSERT_EQ(graph.inOrOutNeighbors(&node1).size(), 1);
  ASSERT_EQ(graph.inOrOutNeighbors(&node2).size(), 2);
  ASSERT_EQ(graph.inOrOutNeighbors(&node3).size(), 1);

  ASSERT_EQ(graph.outNotInEdges(&node1).size(), 1);
  ASSERT_EQ(graph.outNotInEdges(&node2).size(), 1);
  ASSERT_EQ(graph.outNotInEdges(&node3).size(), 0);

  ASSERT_EQ(graph.inNotOutEdges(&node1).size(), 0);
  ASSERT_EQ(graph.inNotOutEdges(&node2).size(), 1);
  ASSERT_EQ(graph.inNotOutEdges(&node3).size(), 1);

  ASSERT_EQ(graph.inOrOutEdges(&node1).size(), 1);
  ASSERT_EQ(graph.inOrOutEdges(&node2).size(), 2);
  ASSERT_EQ(graph.inOrOutEdges(&node3).size(), 1);
}