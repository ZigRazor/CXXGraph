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
  /* ASSERT_EQ(edge.getNodePair(), pairNode); */
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
  CXXGraph::DirectedEdge<bool> edge1(1, node1, node2);
  ASSERT_EQ(*(edge1.getNodePair().first), node1);
  ASSERT_EQ(*(edge1.getNodePair().second), node2);
  ASSERT_TRUE(edge1.isDirected().value());
  ASSERT_FALSE(edge1.isWeighted().value());

  // Second constructor
  CXXGraph::Node<bool> node3("3", true);
  CXXGraph::Node<bool> node4("4", false);
  std::pair<const CXXGraph::Node<bool> *, const CXXGraph::Node<bool> *>
      pairNode(&node3, &node4);
  CXXGraph::DirectedEdge<bool> edge2(2, pairNode);
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
  CXXGraph::DirectedEdge<bool> edge1(1, node1, node2);
  ASSERT_EQ(*(edge1.getNodePair().first), node1);
  ASSERT_EQ(*(edge1.getNodePair().second), node2);
  ASSERT_TRUE(edge1.isDirected().value());
  ASSERT_FALSE(edge1.isWeighted().value());

  // Second constructor
  CXXGraph::Node<bool> node3("3", "On");
  CXXGraph::Node<bool> node4("4", "Off");
  std::pair<const CXXGraph::Node<bool> *, const CXXGraph::Node<bool> *>
      pairNode(&node3, &node4);
  CXXGraph::DirectedEdge<bool> edge2(2, pairNode);
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
  CXXGraph::Edge<int> base_edge(1, pairNode);
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
  CXXGraph::UndirectedEdge<int> base_edge(1, pairNode);
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
  CXXGraph::DirectedEdge<int> edge(1, node1, node2);
  std::cout << "Test Print DirectedEdge" << std::endl;
  std::cout << edge << std::endl;
}

TEST(DirectedEdgeTest, inOutNeigbors_1) {
  CXXGraph::Graph<int> g;

  CXXGraph::Node<int> n1("1", 1);
  CXXGraph::Node<int> n2("2", 2);
  CXXGraph::Node<int> n3("3", 3);

  for (auto &&n : {n1, n2, n3}) {
    g.addNode(&n);
  }

  CXXGraph::DirectedEdge<int> e1(1, {&n1, &n2});
  CXXGraph::DirectedEdge<int> e2(2, {&n2, &n3});

  for (auto &&e : {e1, e2}) {
    g.addEdge(&e);
  }

  ASSERT_EQ(g.outNotInNeighbors(&n1).size(), 1);
  ASSERT_EQ(g.outNotInNeighbors(&n2).size(), 1);
  ASSERT_EQ(g.outNotInNeighbors(&n3).size(), 0);

  ASSERT_EQ(g.inOrOutNeighbors(&n1).size(), 1);
  ASSERT_EQ(g.inOrOutNeighbors(&n2).size(), 2);
  ASSERT_EQ(g.inOrOutNeighbors(&n3).size(), 1);  

  ASSERT_EQ(g.outNotInEdges(&n1).size(), 1);
  ASSERT_EQ(g.outNotInEdges(&n2).size(), 1);
  ASSERT_EQ(g.outNotInEdges(&n3).size(), 0);

  ASSERT_EQ(g.inOrOutEdges(&n1).size(), 1);
  ASSERT_EQ(g.inOrOutEdges(&n2).size(), 2);
  ASSERT_EQ(g.inOrOutEdges(&n3).size(), 1);
}