#include "CXXGraph.hpp"
#include "gtest/gtest.h"

TEST(DFSTest, test_1) {
  CXXGraph::Node<int> node1("1", 1);
  CXXGraph::Node<int> node2("2", 2);
  CXXGraph::Node<int> node3("3", 3);
  std::pair<const CXXGraph::Node<int> *, const CXXGraph::Node<int> *> pairNode(
      &node1, &node2);
  CXXGraph::DirectedWeightedEdge<int> edge1(1, pairNode, 1);
  CXXGraph::DirectedWeightedEdge<int> edge2(2, node2, node3, 1);
  CXXGraph::UndirectedWeightedEdge<int> edge3(3, node1, node3, 6);
  CXXGraph::T_EdgeSet<int> edgeSet;
  edgeSet.insert(&edge1);
  edgeSet.insert(&edge2);
  edgeSet.insert(&edge3);
  CXXGraph::Graph<int> graph(edgeSet);
  std::vector<CXXGraph::Node<int>> res = graph.depth_first_search(node1);
  ASSERT_EQ(res.size(), 3);
  ASSERT_TRUE(std::find(res.begin(), res.end(), node1) != res.end());
  ASSERT_TRUE(std::find(res.begin(), res.end(), node2) != res.end());
  ASSERT_TRUE(std::find(res.begin(), res.end(), node3) != res.end());
}

TEST(DFSTest, test_2) {
  CXXGraph::Node<int> node1("1", 1);
  CXXGraph::Node<int> node2("2", 2);
  CXXGraph::Node<int> node3("3", 3);
  std::pair<const CXXGraph::Node<int> *, const CXXGraph::Node<int> *> pairNode(
      &node1, &node2);
  CXXGraph::DirectedWeightedEdge<int> edge1(1, pairNode, 1);
  CXXGraph::DirectedWeightedEdge<int> edge2(2, node2, node3, 1);
  CXXGraph::DirectedWeightedEdge<int> edge3(3, node1, node3, 6);
  CXXGraph::T_EdgeSet<int> edgeSet;
  edgeSet.insert(&edge1);
  edgeSet.insert(&edge2);
  edgeSet.insert(&edge3);
  CXXGraph::Graph<int> graph(edgeSet);
  std::vector<CXXGraph::Node<int>> res = graph.depth_first_search(node2);
  ASSERT_EQ(res.size(), 2);
  ASSERT_FALSE(std::find(res.begin(), res.end(), node1) != res.end());
  ASSERT_TRUE(std::find(res.begin(), res.end(), node2) != res.end());
  ASSERT_TRUE(std::find(res.begin(), res.end(), node3) != res.end());
}

TEST(DFSTest, test_3) {
  CXXGraph::Node<int> node1("1", 1);
  CXXGraph::Node<int> node2("2", 2);
  CXXGraph::Node<int> node3("3", 3);
  std::pair<const CXXGraph::Node<int> *, const CXXGraph::Node<int> *> pairNode(
      &node1, &node2);
  CXXGraph::DirectedWeightedEdge<int> edge1(1, pairNode, 1);
  CXXGraph::DirectedWeightedEdge<int> edge2(2, node2, node3, 1);
  CXXGraph::UndirectedWeightedEdge<int> edge3(3, node1, node3, 6);
  CXXGraph::T_EdgeSet<int> edgeSet;
  edgeSet.insert(&edge1);
  edgeSet.insert(&edge2);
  edgeSet.insert(&edge3);
  CXXGraph::Graph<int> graph(edgeSet);
  std::vector<CXXGraph::Node<int>> res = graph.depth_first_search(node2);
  ASSERT_EQ(res.size(), 3);
  ASSERT_TRUE(std::find(res.begin(), res.end(), node1) != res.end());
  ASSERT_TRUE(std::find(res.begin(), res.end(), node2) != res.end());
  ASSERT_TRUE(std::find(res.begin(), res.end(), node3) != res.end());
}

TEST(DFSTest, test_4) {
  CXXGraph::Node<int> node1("1", 1);
  CXXGraph::Node<int> node2("2", 2);
  CXXGraph::Node<int> node3("3", 3);
  std::pair<const CXXGraph::Node<int> *, const CXXGraph::Node<int> *> pairNode(
      &node1, &node2);
  CXXGraph::DirectedWeightedEdge<int> edge1(1, pairNode, 1);
  CXXGraph::DirectedWeightedEdge<int> edge2(2, node2, node3, 1);
  CXXGraph::UndirectedWeightedEdge<int> edge3(3, node1, node3, 6);
  CXXGraph::T_EdgeSet<int> edgeSet;
  edgeSet.insert(&edge1);
  edgeSet.insert(&edge2);
  edgeSet.insert(&edge3);
  CXXGraph::Graph<int> graph(edgeSet);
  std::vector<CXXGraph::Node<int>> res = graph.depth_first_search(node3);
  ASSERT_EQ(res.size(), 3);
  ASSERT_TRUE(std::find(res.begin(), res.end(), node1) != res.end());
  ASSERT_TRUE(std::find(res.begin(), res.end(), node2) != res.end());
  ASSERT_TRUE(std::find(res.begin(), res.end(), node3) != res.end());
}

TEST(DFSTest, test_5) {
  CXXGraph::Node<int> node1("1", 1);
  CXXGraph::Node<int> node2("2", 2);
  CXXGraph::Node<int> node3("3", 3);
  std::pair<const CXXGraph::Node<int> *, const CXXGraph::Node<int> *> pairNode(
      &node1, &node2);
  CXXGraph::DirectedWeightedEdge<int> edge1(1, pairNode, 1);
  CXXGraph::DirectedWeightedEdge<int> edge2(2, node2, node3, 1);
  CXXGraph::DirectedWeightedEdge<int> edge3(3, node1, node3, 6);
  CXXGraph::T_EdgeSet<int> edgeSet;
  edgeSet.insert(&edge1);
  edgeSet.insert(&edge2);
  edgeSet.insert(&edge3);
  CXXGraph::Graph<int> graph(edgeSet);
  std::vector<CXXGraph::Node<int>> res = graph.depth_first_search(node3);
  ASSERT_EQ(res.size(), 1);
  ASSERT_FALSE(std::find(res.begin(), res.end(), node1) != res.end());
  ASSERT_FALSE(std::find(res.begin(), res.end(), node2) != res.end());
  ASSERT_TRUE(std::find(res.begin(), res.end(), node3) != res.end());
}

TEST(DFSTest, test_6) {
  CXXGraph::Node<int> node1("1", 1);
  CXXGraph::Node<int> node2("2", 2);
  CXXGraph::Node<int> node3("3", 3);
  CXXGraph::Node<int> node4("4", 4);
  std::pair<const CXXGraph::Node<int> *, const CXXGraph::Node<int> *> pairNode(
      &node1, &node2);
  CXXGraph::DirectedWeightedEdge<int> edge1(1, pairNode, 1);
  CXXGraph::DirectedWeightedEdge<int> edge2(2, node2, node3, 1);
  CXXGraph::DirectedWeightedEdge<int> edge3(3, node1, node3, 6);
  CXXGraph::T_EdgeSet<int> edgeSet;
  edgeSet.insert(&edge1);
  edgeSet.insert(&edge2);
  edgeSet.insert(&edge3);
  CXXGraph::Graph<int> graph(edgeSet);
  std::vector<CXXGraph::Node<int>> res = graph.depth_first_search(node4);
  ASSERT_EQ(res.size(), 0);
  ASSERT_FALSE(std::find(res.begin(), res.end(), node1) != res.end());
  ASSERT_FALSE(std::find(res.begin(), res.end(), node2) != res.end());
  ASSERT_FALSE(std::find(res.begin(), res.end(), node3) != res.end());
  ASSERT_FALSE(std::find(res.begin(), res.end(), node4) != res.end());
}