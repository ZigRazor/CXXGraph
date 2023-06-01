#include <memory>
#include "CXXGraph.hpp"
#include "gtest/gtest.h"

// Smart pointers alias
template <typename T>
using unique = std::unique_ptr<T>;
template <typename T>
using shared= std::shared_ptr<T>;

using std::make_unique;
using std::make_shared;

TEST(DialTest, test_1) {
  CXXGraph::Node<int> node1("1", 1);
  CXXGraph::Node<int> node2("2", 2);
  CXXGraph::Node<int> node3("3", 3);
  std::pair<const CXXGraph::Node<int> *, const CXXGraph::Node<int> *> pairNode(
      &node1, &node2);
  CXXGraph::DirectedWeightedEdge<int> edge1(1, pairNode, 1);
  CXXGraph::DirectedWeightedEdge<int> edge2(2, node2, node3, 1);
  CXXGraph::UndirectedWeightedEdge<int> edge3(3, node1, node3, 6);
  CXXGraph::T_EdgeSet<int> edgeSet;
  edgeSet.insert(make_shared<CXXGraph::DirectedWeightedEdge<int>>(edge1));
  edgeSet.insert(make_shared<CXXGraph::DirectedWeightedEdge<int>>(edge2));
  edgeSet.insert(make_shared<CXXGraph::UndirectedWeightedEdge<int>>(edge3));
  CXXGraph::Graph<int> graph(edgeSet);
  auto res = graph.dial(node1, 6);
  ASSERT_TRUE(res.success);
  ASSERT_EQ(res.errorMessage, "");
  ASSERT_EQ(res.minDistanceMap.at(node1.getId()), 0);
  ASSERT_EQ(res.minDistanceMap.at(node2.getId()), 1);
  ASSERT_EQ(res.minDistanceMap.at(node3.getId()), 2);
}

TEST(DialTest, test_2) {
  CXXGraph::Node<int> node1("1", 1);
  CXXGraph::Node<int> node2("2", 2);
  CXXGraph::Node<int> node3("3", 3);
  std::pair<const CXXGraph::Node<int> *, const CXXGraph::Node<int> *> pairNode(
      &node1, &node2);
  CXXGraph::DirectedWeightedEdge<int> edge1(1, pairNode, 5);
  CXXGraph::DirectedWeightedEdge<int> edge2(2, node2, node3, 4);
  CXXGraph::UndirectedWeightedEdge<int> edge3(3, node1, node3, 6);
  CXXGraph::T_EdgeSet<int> edgeSet;
  edgeSet.insert(make_shared<CXXGraph::DirectedWeightedEdge<int>>(edge1));
  edgeSet.insert(make_shared<CXXGraph::DirectedWeightedEdge<int>>(edge2));
  edgeSet.insert(make_shared<CXXGraph::UndirectedWeightedEdge<int>>(edge3));
  CXXGraph::Graph<int> graph(edgeSet);
  auto res = graph.dial(node1, 6);
  ;
  ASSERT_TRUE(res.success);
  ASSERT_EQ(res.errorMessage, "");
  ASSERT_EQ(res.minDistanceMap.at(node1.getId()), 0);
  ASSERT_EQ(res.minDistanceMap.at(node2.getId()), 5);
  ASSERT_EQ(res.minDistanceMap.at(node3.getId()), 6);
}

TEST(DialTest, test_3) {
  CXXGraph::Node<int> node1("1", 1);
  CXXGraph::Node<int> node2("2", 2);
  CXXGraph::Node<int> node3("3", 3);
  std::pair<const CXXGraph::Node<int> *, const CXXGraph::Node<int> *> pairNode(
      &node1, &node2);
  CXXGraph::DirectedWeightedEdge<int> edge1(1, pairNode, 5);
  CXXGraph::DirectedEdge<int> edge2(2, node2, node3);
  CXXGraph::UndirectedWeightedEdge<int> edge3(3, node1, node3, 6);
  CXXGraph::T_EdgeSet<int> edgeSet;
  edgeSet.insert(make_shared<CXXGraph::DirectedWeightedEdge<int>>(edge1));
  edgeSet.insert(make_shared<CXXGraph::DirectedEdge<int>>(edge2));
  edgeSet.insert(make_shared<CXXGraph::UndirectedWeightedEdge<int>>(edge3));
  CXXGraph::Graph<int> graph(edgeSet);
  auto res = graph.dial(node1, 6);
  ASSERT_FALSE(res.success);
  ASSERT_EQ(res.errorMessage, CXXGraph::ERR_NO_WEIGHTED_EDGE);
  ASSERT_TRUE(res.minDistanceMap.empty());
}

TEST(DialTest, test_4) {
  CXXGraph::Node<int> node1("1", 1);
  CXXGraph::Node<int> node2("2", 2);
  CXXGraph::Node<int> node3("3", 3);
  CXXGraph::DirectedEdge<int> edge2(2, node2, node3);
  CXXGraph::UndirectedWeightedEdge<int> edge3(3, node1, node3, 6);
  CXXGraph::T_EdgeSet<int> edgeSet;
  edgeSet.insert(make_shared<CXXGraph::DirectedWeightedEdge<int>>(edge2));
  edgeSet.insert(make_shared<CXXGraph::UndirectedWeightedEdge<int>>(edge3));
  CXXGraph::Graph<int> graph(edgeSet);
  auto res = graph.dial(node1, 6);
  ASSERT_TRUE(res.success);
  ASSERT_EQ(res.errorMessage, "");
  ASSERT_EQ(res.minDistanceMap.at(node1.getId()), 0);
  ASSERT_EQ(res.minDistanceMap.at(node2.getId()),
            std::numeric_limits<long>::max());
  ASSERT_EQ(res.minDistanceMap.at(node3.getId()), 6);
}

TEST(DialTest, test_5) {
  CXXGraph::Node<int> node1("1", 1);
  CXXGraph::Node<int> node2("2", 2);
  CXXGraph::Node<int> node3("3", 3);
  CXXGraph::Node<int> node4("4", 4);
  CXXGraph::DirectedEdge<int> edge2(2, node2, node3);
  CXXGraph::UndirectedWeightedEdge<int> edge3(3, node1, node3, 6);
  CXXGraph::T_EdgeSet<int> edgeSet;
  edgeSet.insert(make_shared<CXXGraph::DirectedWeightedEdge<int>>(edge2));
  edgeSet.insert(make_shared<CXXGraph::UndirectedWeightedEdge<int>>(edge3));
  CXXGraph::Graph<int> graph(edgeSet);
  auto res = graph.dial(node4, 6);
  ASSERT_FALSE(res.success);
  ASSERT_EQ(res.errorMessage, CXXGraph::ERR_SOURCE_NODE_NOT_IN_GRAPH);
  ASSERT_TRUE(res.minDistanceMap.empty());
}
