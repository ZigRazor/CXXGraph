#include <map>
#include <memory>

#include "CXXGraph/CXXGraph.hpp"
#include "gtest/gtest.h"

// Smart pointers alias
template <typename T>
using unique = std::unique_ptr<T>;
template <typename T>
using shared = std::shared_ptr<T>;

using std::make_shared;
using std::make_unique;

// https://en.wikipedia.org/wiki/Floyd%E2%80%93Warshall_algorithm#Example
TEST(FWTest, test_1) {
  CXXGraph::Node<int> node1("1", 1);
  CXXGraph::Node<int> node2("2", 2);
  CXXGraph::Node<int> node3("3", 3);
  CXXGraph::Node<int> node4("4", 4);

  CXXGraph::DirectedWeightedEdge<int> edge1(1, node2, node1, 4);
  CXXGraph::DirectedWeightedEdge<int> edge2(2, node1, node3, -2);
  CXXGraph::DirectedWeightedEdge<int> edge3(3, node3, node4, 2);
  CXXGraph::DirectedWeightedEdge<int> edge4(4, node4, node2, -1);
  CXXGraph::DirectedWeightedEdge<int> edge5(3, node2, node3, 3);

  CXXGraph::T_EdgeSet<int> edgeSet;
  edgeSet.insert(make_shared<CXXGraph::DirectedWeightedEdge<int>>(edge1));
  edgeSet.insert(make_shared<CXXGraph::DirectedWeightedEdge<int>>(edge2));
  edgeSet.insert(make_shared<CXXGraph::DirectedWeightedEdge<int>>(edge3));
  edgeSet.insert(make_shared<CXXGraph::DirectedWeightedEdge<int>>(edge4));
  edgeSet.insert(make_shared<CXXGraph::DirectedWeightedEdge<int>>(edge5));

  CXXGraph::Graph<int> graph(edgeSet);
  CXXGraph::FWResult res = graph.floydWarshall();

  CXXGraph::Map<std::pair<std::string, std::string>, double,
                     CXXGraph::pair_hash>
      pairwise_dist;
  auto key = std::make_pair(node1.getUserId(), node1.getUserId());
  auto nodeSet = graph.getNodeSet();
  double values[4][4] = {
      {0, -1, -2, 0}, {4, 0, 2, 4}, {5, 1, 0, 2}, {3, -1, 1, 0}};
  int row(0), col(0);
  for (const auto &elem1 : nodeSet) {
    col = 0;
    for (const auto &elem2 : nodeSet) {
      auto key = std::make_pair(elem1->getUserId(), elem2->getUserId());
      pairwise_dist[key] = values[row][col];
      col += 1;
    }
    row += 1;
  }
  auto isEqual =
      pairwise_dist.size() == res.result.size() &&
      std::equal(pairwise_dist.begin(), pairwise_dist.end(), res.result.begin(),
                 [](auto a, auto b) { return a.first == b.first; });

  ASSERT_TRUE(res.success);
  ASSERT_FALSE(res.negativeCycle);
  ASSERT_TRUE(isEqual);
  ASSERT_EQ(res.errorMessage, "");
}

// a graph with negative cycle
TEST(FWTest, test_2) {
  CXXGraph::Node<int> node0("0", 0);
  CXXGraph::Node<int> node1("1", 1);
  CXXGraph::Node<int> node2("2", 2);
  CXXGraph::DirectedWeightedEdge<int> edge1(1, node0, node1, 2);
  CXXGraph::DirectedWeightedEdge<int> edge2(2, node1, node2, 3);
  CXXGraph::DirectedWeightedEdge<int> edge3(3, node2, node0, -7);
  CXXGraph::T_EdgeSet<int> edgeSet;
  edgeSet.insert(make_shared<CXXGraph::DirectedWeightedEdge<int>>(edge1));
  edgeSet.insert(make_shared<CXXGraph::DirectedWeightedEdge<int>>(edge2));
  edgeSet.insert(make_shared<CXXGraph::DirectedWeightedEdge<int>>(edge3));
  CXXGraph::Graph<int> graph(edgeSet);
  CXXGraph::FWResult res = graph.floydWarshall();
  ASSERT_TRUE(res.success);
  ASSERT_TRUE(res.negativeCycle);
  ASSERT_EQ(res.errorMessage, "");
}

// UndirectedWeightedEdge
TEST(FWTest, test_3) {
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
  CXXGraph::FWResult res = graph.floydWarshall();
  ASSERT_TRUE(res.success);
  ASSERT_FALSE(res.negativeCycle);
  ASSERT_EQ(res.errorMessage, "");
}

// No weighted edge
TEST(FWTest, test_4) {
  CXXGraph::Node<int> node1("1", 1);
  CXXGraph::Node<int> node2("2", 2);
  CXXGraph::Node<int> node3("3", 3);
  std::pair<const CXXGraph::Node<int> *, const CXXGraph::Node<int> *> pairNode(
      &node1, &node2);
  CXXGraph::DirectedWeightedEdge<int> edge1(1, pairNode, 1);
  CXXGraph::DirectedWeightedEdge<int> edge2(2, node2, node3, 1);
  CXXGraph::DirectedEdge<int> edge3(3, node1, node3);
  CXXGraph::T_EdgeSet<int> edgeSet;
  edgeSet.insert(make_shared<CXXGraph::DirectedWeightedEdge<int>>(edge1));
  edgeSet.insert(make_shared<CXXGraph::DirectedWeightedEdge<int>>(edge2));
  edgeSet.insert(make_shared<CXXGraph::DirectedEdge<int>>(edge3));
  CXXGraph::Graph<int> graph(edgeSet);
  CXXGraph::FWResult res = graph.floydWarshall();
  ASSERT_FALSE(res.success);
  ASSERT_EQ(res.errorMessage, CXXGraph::ERR_NO_WEIGHTED_EDGE);
}
