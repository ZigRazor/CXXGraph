#include <vector>

#include "CXXGraph.hpp"
#include "gtest/gtest.h"

TEST(BestFirstSearchTest, source_node_missing) {
  CXXGraph::Node<int> node1("1", 1);
  CXXGraph::Node<int> node2("2", 2);
  CXXGraph::Node<int> node3("3", 3);
  CXXGraph::Node<int> node4("4", 4);
  std::pair<const CXXGraph::Node<int> *, const CXXGraph::Node<int> *> pairNode(
      &node1, &node2);
  CXXGraph::DirectedWeightedEdge<int> edge1(1, pairNode, 1);
  CXXGraph::DirectedWeightedEdge<int> edge2(2, node2, node3, 3);
  CXXGraph::DirectedWeightedEdge<int> edge3(3, node1, node3, 6);
  CXXGraph::T_EdgeSet<int> edgeSet;
  edgeSet.insert(&edge1);
  edgeSet.insert(&edge2);
  edgeSet.insert(&edge3);
  CXXGraph::Graph<int> graph(edgeSet);
  CXXGraph::BestFirstSearchResult<int> res =
      graph.best_first_search(node4, node1);
  ASSERT_EQ(res.success, false);
  ASSERT_EQ(res.nodesInBestSearchOrder.size(), 0);
  ASSERT_EQ(res.errorMessage, CXXGraph::ERR_SOURCE_NODE_NOT_IN_GRAPH);
}

TEST(BestFirstSearchTest, target_node_missing) {
  CXXGraph::Node<int> node1("1", 1);
  CXXGraph::Node<int> node2("2", 2);
  CXXGraph::Node<int> node3("3", 3);
  CXXGraph::Node<int> node4("4", 4);
  std::pair<const CXXGraph::Node<int> *, const CXXGraph::Node<int> *> pairNode(
      &node1, &node2);
  CXXGraph::DirectedWeightedEdge<int> edge1(1, pairNode, 1);
  CXXGraph::DirectedWeightedEdge<int> edge2(2, node2, node3, 3);
  CXXGraph::DirectedWeightedEdge<int> edge3(3, node1, node3, 6);
  CXXGraph::T_EdgeSet<int> edgeSet;
  edgeSet.insert(&edge1);
  edgeSet.insert(&edge2);
  edgeSet.insert(&edge3);
  CXXGraph::Graph<int> graph(edgeSet);
  CXXGraph::BestFirstSearchResult<int> res =
      graph.best_first_search(node1, node4);
  ASSERT_EQ(res.success, false);
  ASSERT_EQ(res.nodesInBestSearchOrder.size(), 0);
  ASSERT_EQ(res.errorMessage, CXXGraph::ERR_TARGET_NODE_NOT_IN_GRAPH);
}

TEST(BestFirstSearchTest, correct_example_small) {
  CXXGraph::Node<int> node1("1", 1);
  CXXGraph::Node<int> node2("2", 2);
  CXXGraph::Node<int> node3("3", 3);
  std::pair<const CXXGraph::Node<int> *, const CXXGraph::Node<int> *> pairNode(
      &node1, &node2);
  CXXGraph::DirectedWeightedEdge<int> edge1(1, pairNode, 1);
  CXXGraph::DirectedWeightedEdge<int> edge2(2, node2, node3, 3);
  CXXGraph::DirectedWeightedEdge<int> edge3(3, node1, node3, 6);
  CXXGraph::T_EdgeSet<int> edgeSet;
  edgeSet.insert(&edge1);
  edgeSet.insert(&edge2);
  edgeSet.insert(&edge3);
  CXXGraph::Graph<int> graph(edgeSet);
  CXXGraph::BestFirstSearchResult<int> res =
      graph.best_first_search(node1, node2);
  ASSERT_EQ(res.success, true);
  ASSERT_EQ(res.nodesInBestSearchOrder.size(), 2);
  ASSERT_EQ(res.errorMessage, "");
}

TEST(BestFirstSearchTest, source_target_same) {
  CXXGraph::Node<int> node1("1", 1);
  CXXGraph::Node<int> node2("2", 2);
  CXXGraph::Node<int> node3("3", 3);
  std::pair<const CXXGraph::Node<int> *, const CXXGraph::Node<int> *> pairNode(
      &node1, &node2);
  CXXGraph::DirectedWeightedEdge<int> edge1(1, pairNode, 1);
  CXXGraph::DirectedWeightedEdge<int> edge2(2, node2, node3, 3);
  CXXGraph::DirectedWeightedEdge<int> edge3(3, node1, node3, 6);
  CXXGraph::T_EdgeSet<int> edgeSet;
  edgeSet.insert(&edge1);
  edgeSet.insert(&edge2);
  edgeSet.insert(&edge3);
  CXXGraph::Graph<int> graph(edgeSet);
  CXXGraph::BestFirstSearchResult<int> res =
      graph.best_first_search(node1, node1);
  ASSERT_EQ(res.success, true);
  ASSERT_EQ(res.nodesInBestSearchOrder.size(), 1);
  ASSERT_EQ(res.errorMessage, "");
}

TEST(BestFirstSearchTest, correct_example_big) {
  CXXGraph::Node<int> node1("1", 1);
  CXXGraph::Node<int> node2("2", 2);
  CXXGraph::Node<int> node3("3", 3);
  CXXGraph::Node<int> node4("4", 4);
  CXXGraph::Node<int> node5("5", 5);
  CXXGraph::Node<int> node6("6", 6);
  CXXGraph::Node<int> node7("7", 7);
  CXXGraph::Node<int> node8("8", 8);
  CXXGraph::Node<int> node9("9", 9);
  CXXGraph::Node<int> node10("10", 10);
  CXXGraph::Node<int> node11("11", 11);
  CXXGraph::Node<int> node12("12", 12);
  CXXGraph::Node<int> node13("13", 13);
  CXXGraph::Node<int> node14("14", 14);
  std::pair<const CXXGraph::Node<int> *, const CXXGraph::Node<int> *> pairNode(
      &node1, &node2);
  CXXGraph::DirectedWeightedEdge<int> edge1(1, node1, node2, 3);
  CXXGraph::DirectedWeightedEdge<int> edge2(2, node1, node3, 6);
  CXXGraph::DirectedWeightedEdge<int> edge3(3, node1, node4, 5);
  CXXGraph::DirectedWeightedEdge<int> edge4(4, node2, node5, 9);
  CXXGraph::DirectedWeightedEdge<int> edge5(5, node2, node6, 8);
  CXXGraph::DirectedWeightedEdge<int> edge6(6, node3, node7, 12);
  CXXGraph::DirectedWeightedEdge<int> edge7(7, node3, node8, 14);
  CXXGraph::DirectedWeightedEdge<int> edge8(8, node4, node9, 7);
  CXXGraph::DirectedWeightedEdge<int> edge9(9, node9, node10, 5);
  CXXGraph::DirectedWeightedEdge<int> edge10(10, node9, node11, 6);
  CXXGraph::DirectedWeightedEdge<int> edge11(10, node10, node12, 1);
  CXXGraph::DirectedWeightedEdge<int> edge12(10, node10, node13, 10);
  CXXGraph::DirectedWeightedEdge<int> edge13(10, node10, node14, 2);
  CXXGraph::T_EdgeSet<int> edgeSet;
  edgeSet.insert(&edge1);
  edgeSet.insert(&edge2);
  edgeSet.insert(&edge3);
  edgeSet.insert(&edge4);
  edgeSet.insert(&edge5);
  edgeSet.insert(&edge6);
  edgeSet.insert(&edge7);
  edgeSet.insert(&edge8);
  edgeSet.insert(&edge9);
  edgeSet.insert(&edge10);
  edgeSet.insert(&edge11);
  edgeSet.insert(&edge12);
  edgeSet.insert(&edge13);
  CXXGraph::Graph<int> graph(edgeSet);
  CXXGraph::BestFirstSearchResult<int> res =
      graph.best_first_search(node1, node10);
  ASSERT_EQ(res.success, true);
  ASSERT_EQ(res.nodesInBestSearchOrder.size(), 6);
  ASSERT_EQ(res.errorMessage, "");
}