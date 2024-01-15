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

// DirectedEdge
TEST(GraphSlicingTest, test_1) {
  CXXGraph::Node<int> node1("1", 1);
  CXXGraph::Node<int> node2("2", 2);
  CXXGraph::Node<int> node3("3", 3);
  CXXGraph::Node<int> node4("4", 4);
  CXXGraph::Node<int> node5("5", 5);
  CXXGraph::Node<int> node6("6", 6);

  CXXGraph::DirectedEdge<int> edge1(1, node1, node2);
  CXXGraph::DirectedEdge<int> edge2(2, node2, node3);
  CXXGraph::DirectedEdge<int> edge3(3, node1, node5);
  CXXGraph::DirectedEdge<int> edge4(4, node5, node3);
  CXXGraph::DirectedEdge<int> edge5(5, node3, node6);
  CXXGraph::DirectedEdge<int> edge6(6, node4, node3);

  CXXGraph::T_EdgeSet<int> edgeSet;
  edgeSet.insert(make_shared<CXXGraph::DirectedEdge<int>>(edge1));
  edgeSet.insert(make_shared<CXXGraph::DirectedEdge<int>>(edge2));
  edgeSet.insert(make_shared<CXXGraph::DirectedEdge<int>>(edge3));
  edgeSet.insert(make_shared<CXXGraph::DirectedEdge<int>>(edge4));
  edgeSet.insert(make_shared<CXXGraph::DirectedEdge<int>>(edge5));
  edgeSet.insert(make_shared<CXXGraph::DirectedEdge<int>>(edge6));

  CXXGraph::Graph<int> graph(edgeSet);
  std::vector<CXXGraph::Node<int>> res = graph.graph_slicing(node1);
  ASSERT_EQ(res.size(), 3);
  ASSERT_TRUE(std::find(res.begin(), res.end(), node1) != res.end());
  ASSERT_TRUE(std::find(res.begin(), res.end(), node2) != res.end());
  ASSERT_TRUE(std::find(res.begin(), res.end(), node5) != res.end());
}

// DirectedWeightedEdge
// weights shouldn't matter
TEST(GraphSlicingTest, test_2) {
  CXXGraph::Node<int> node1("1", 1);
  CXXGraph::Node<int> node2("2", 2);
  CXXGraph::Node<int> node3("3", 3);
  CXXGraph::Node<int> node4("4", 4);
  CXXGraph::Node<int> node5("5", 5);
  CXXGraph::Node<int> node6("6", 6);

  CXXGraph::DirectedWeightedEdge<int> edge1(1, node1, node2, 10);
  CXXGraph::DirectedWeightedEdge<int> edge2(2, node2, node3, -1);
  CXXGraph::DirectedWeightedEdge<int> edge3(3, node1, node5, 3);
  CXXGraph::DirectedWeightedEdge<int> edge4(4, node5, node3, 5);
  CXXGraph::DirectedWeightedEdge<int> edge5(5, node3, node6, 8);
  CXXGraph::DirectedWeightedEdge<int> edge6(6, node4, node3, 0);

  CXXGraph::T_EdgeSet<int> edgeSet;
  edgeSet.insert(make_shared<CXXGraph::DirectedWeightedEdge<int>>(edge1));
  edgeSet.insert(make_shared<CXXGraph::DirectedWeightedEdge<int>>(edge2));
  edgeSet.insert(make_shared<CXXGraph::DirectedWeightedEdge<int>>(edge3));
  edgeSet.insert(make_shared<CXXGraph::DirectedWeightedEdge<int>>(edge4));
  edgeSet.insert(make_shared<CXXGraph::DirectedWeightedEdge<int>>(edge5));
  edgeSet.insert(make_shared<CXXGraph::DirectedWeightedEdge<int>>(edge6));

  CXXGraph::Graph<int> graph(edgeSet);
  std::vector<CXXGraph::Node<int>> res = graph.graph_slicing(node1);
  ASSERT_EQ(res.size(), 3);
  ASSERT_TRUE(std::find(res.begin(), res.end(), node1) != res.end());
  ASSERT_TRUE(std::find(res.begin(), res.end(), node2) != res.end());
  ASSERT_TRUE(std::find(res.begin(), res.end(), node5) != res.end());
}

// UndirectedWeightedEdge
TEST(GraphSlicingTest, test_3) {
  CXXGraph::Node<int> node1("1", 1);
  CXXGraph::Node<int> node2("2", 2);
  CXXGraph::Node<int> node3("3", 3);
  CXXGraph::Node<int> node4("4", 4);
  CXXGraph::Node<int> node5("5", 5);
  CXXGraph::Node<int> node6("6", 6);

  CXXGraph::UndirectedEdge<int> edge1(1, node1, node2);
  CXXGraph::UndirectedEdge<int> edge2(2, node2, node3);
  CXXGraph::UndirectedEdge<int> edge3(3, node1, node5);
  CXXGraph::UndirectedEdge<int> edge4(4, node5, node3);
  CXXGraph::UndirectedEdge<int> edge5(5, node3, node6);
  CXXGraph::UndirectedEdge<int> edge6(6, node4, node3);

  CXXGraph::T_EdgeSet<int> edgeSet;
  edgeSet.insert(make_shared<CXXGraph::UndirectedEdge<int>>(edge1));
  edgeSet.insert(make_shared<CXXGraph::UndirectedEdge<int>>(edge2));
  edgeSet.insert(make_shared<CXXGraph::UndirectedEdge<int>>(edge3));
  edgeSet.insert(make_shared<CXXGraph::UndirectedEdge<int>>(edge4));
  edgeSet.insert(make_shared<CXXGraph::UndirectedEdge<int>>(edge5));
  edgeSet.insert(make_shared<CXXGraph::UndirectedEdge<int>>(edge6));

  CXXGraph::Graph<int> graph(edgeSet);
  std::vector<CXXGraph::Node<int>> res = graph.graph_slicing(node1);
  ASSERT_EQ(res.size(), 6);
}

// UndirectedWeightedEdge
// weights shouldn't matter
TEST(GraphSlicingTest, test_4) {
  CXXGraph::Node<int> node1("1", 1);
  CXXGraph::Node<int> node2("2", 2);
  CXXGraph::Node<int> node3("3", 3);
  CXXGraph::Node<int> node4("4", 4);
  CXXGraph::Node<int> node5("5", 5);
  CXXGraph::Node<int> node6("6", 6);

  CXXGraph::UndirectedWeightedEdge<int> edge1(1, node1, node2, 10);
  CXXGraph::UndirectedWeightedEdge<int> edge2(2, node2, node3, -1);
  CXXGraph::UndirectedWeightedEdge<int> edge3(3, node1, node5, 3);
  CXXGraph::UndirectedWeightedEdge<int> edge4(4, node5, node3, 5);
  CXXGraph::UndirectedWeightedEdge<int> edge5(5, node3, node6, 8);
  CXXGraph::UndirectedWeightedEdge<int> edge6(6, node4, node3, 0);

  CXXGraph::T_EdgeSet<int> edgeSet;
  edgeSet.insert(make_shared<CXXGraph::UndirectedWeightedEdge<int>>(edge1));
  edgeSet.insert(make_shared<CXXGraph::UndirectedWeightedEdge<int>>(edge2));
  edgeSet.insert(make_shared<CXXGraph::UndirectedWeightedEdge<int>>(edge3));
  edgeSet.insert(make_shared<CXXGraph::UndirectedWeightedEdge<int>>(edge4));
  edgeSet.insert(make_shared<CXXGraph::UndirectedWeightedEdge<int>>(edge5));
  edgeSet.insert(make_shared<CXXGraph::UndirectedWeightedEdge<int>>(edge6));

  CXXGraph::Graph<int> graph(edgeSet);
  std::vector<CXXGraph::Node<int>> res = graph.graph_slicing(node1);
  ASSERT_EQ(res.size(), 6);
}

// start node is disconnected from rest of the graph
TEST(GraphSlicingTest, test_5) {
  CXXGraph::Node<int> node1("1", 1);
  CXXGraph::Node<int> node2("2", 2);
  CXXGraph::Node<int> node3("3", 3);
  CXXGraph::Node<int> node4("4", 4);
  CXXGraph::DirectedWeightedEdge<int> edge1(1, node1, node2, 1);
  CXXGraph::DirectedWeightedEdge<int> edge2(2, node2, node3, 1);
  CXXGraph::DirectedWeightedEdge<int> edge3(3, node1, node3, 6);
  CXXGraph::T_EdgeSet<int> edgeSet;
  edgeSet.insert(make_shared<CXXGraph::DirectedWeightedEdge<int>>(edge1));
  edgeSet.insert(make_shared<CXXGraph::DirectedWeightedEdge<int>>(edge2));
  edgeSet.insert(make_shared<CXXGraph::DirectedWeightedEdge<int>>(edge3));
  CXXGraph::Graph<int> graph(edgeSet);
  std::vector<CXXGraph::Node<int>> res = graph.graph_slicing(node4);
  ASSERT_EQ(res.size(), 0);
}
