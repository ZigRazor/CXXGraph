#include "CXXGraph/CXXGraph.hpp"
#include "gtest/gtest.h"

// Smart pointers alias
template <typename T>
using unique = std::unique_ptr<T>;
template <typename T>
using shared = std::shared_ptr<T>;

using std::make_shared;
using std::make_unique;

TEST(EdgeTest, Constructor_1) {
  CXXGraph::Node<int> node1("1", 1);
  CXXGraph::Node<int> node2("2", 2);
  CXXGraph::Edge<int> edge("1", node1, node2);
  ASSERT_EQ(*(edge.getNodePair().first), node1);
  ASSERT_EQ(*(edge.getNodePair().second), node2);
}

TEST(EdgeTest, Constructor_2) {
  CXXGraph::Node<int> node1("1", 1);
  CXXGraph::Node<int> node2("2", 2);
  std::pair<const CXXGraph::Node<int> *, const CXXGraph::Node<int> *> pairNode(
      &node1, &node2);
  CXXGraph::Edge<int> edge("1", pairNode);
  /* ASSERT_EQ(edge.getNodePair(), pairNode); */
  ASSERT_EQ(*(edge.getNodePair().first), node1);
  ASSERT_EQ(*(edge.getNodePair().second), node2);
}

TEST(EdgeTest, print_1) {
  CXXGraph::Node<int> node1("1", 1);
  CXXGraph::Node<int> node2("2", 2);
  CXXGraph::Edge<int> edge("1", node1, node2);
  std::cout << "Test Print Edge" << std::endl;
  std::cout << edge << std::endl;
}

TEST(EdgeTest, Bool_data) {
  // First constructor
  CXXGraph::Node<bool> node1("1", true);
  CXXGraph::Node<bool> node2("2", false);
  CXXGraph::Edge<bool> edge1("1", node1, node2);
  ASSERT_EQ(*(edge1.getNodePair().first), node1);
  ASSERT_EQ(*(edge1.getNodePair().second), node2);

  // Second constructor
  CXXGraph::Node<bool> node3("3", true);
  CXXGraph::Node<bool> node4("4", false);
  std::pair<const CXXGraph::Node<bool> *, const CXXGraph::Node<bool> *>
      pairNode(&node3, &node4);
  CXXGraph::Edge<bool> edge2("2", pairNode);
  /* ASSERT_EQ(edge2.getNodePair(), pairNode); */
  ASSERT_EQ(*(edge2.getNodePair().first), node3);
  ASSERT_EQ(*(edge2.getNodePair().second), node4);
}

TEST(EdgeTest, String_data) {
  // First constructor
  CXXGraph::Node<bool> node1("1", "On");
  CXXGraph::Node<bool> node2("2", "Off");
  CXXGraph::Edge<bool> edge1("1", node1, node2);
  ASSERT_EQ(*(edge1.getNodePair().first), node1);
  ASSERT_EQ(*(edge1.getNodePair().second), node2);

  // Second constructor
  CXXGraph::Node<bool> node3("3", "On");
  CXXGraph::Node<bool> node4("4", "Off");
  std::pair<const CXXGraph::Node<bool> *, const CXXGraph::Node<bool> *>
      pairNode(&node3, &node4);
  CXXGraph::Edge<bool> edge2("2", pairNode);
  /* ASSERT_EQ(edge2.getNodePair(), pairNode); */
  ASSERT_EQ(*(edge2.getNodePair().first), node3);
  ASSERT_EQ(*(edge2.getNodePair().second), node4);
}

TEST(EdgeTest, test) {
  CXXGraph::Node<int> node1("1", 1);
  CXXGraph::Node<int> node2("2", 2);
  CXXGraph::Node<int> node3("3", 3);

  CXXGraph::DirectedWeightedEdge<int> edge1("1", node1, node2, 1);
  CXXGraph::UndirectedWeightedEdge<int> edge2("2", node2, node3, 1);
  CXXGraph::DirectedEdge<int> edge3("3", node1, node3);

  CXXGraph::T_EdgeSet<int> edgeSet;
  edgeSet.insert(make_shared<CXXGraph::DirectedWeightedEdge<int>>(edge1));
  edgeSet.insert(make_shared<CXXGraph::UndirectedWeightedEdge<int>>(edge2));
  edgeSet.insert(make_shared<CXXGraph::DirectedEdge<int>>(edge3));

  CXXGraph::Graph<int> graph;
  graph.setEdgeSet(edgeSet);
  auto adj = graph.getAdjListOut();
  ASSERT_EQ(adj->size(), 3);
  graph.removeEdge("3");
  adj = graph.getAdjListOut();
  ASSERT_EQ(adj->size(), 3);

  graph.removeEdge("2");
  adj = graph.getAdjListOut();
  ASSERT_EQ(adj->size(), 1);
  std::cout << *adj << std::endl;
}
