#include <memory>
#include "CXXGraph/CXXGraph.hpp"
#include "gtest/gtest.h"

// Smart pointers alias
template <typename T>
using unique = std::unique_ptr<T>;
template <typename T>
using shared= std::shared_ptr<T>;

using std::make_unique;
using std::make_shared;

TEST(FordFulkersonTest, test_1) {
  CXXGraph::Node<int> node0("0", 0);
  CXXGraph::Node<int> node1("1", 1);
  CXXGraph::Node<int> node2("2", 2);
  CXXGraph::Node<int> node3("3", 3);
  CXXGraph::Node<int> node4("4", 4);
  CXXGraph::Node<int> node5("5", 5);

  CXXGraph::DirectedWeightedEdge<int> edge1(1, node0, node1, 11);
  CXXGraph::DirectedWeightedEdge<int> edge2(2, node0, node2, 12);
  CXXGraph::DirectedWeightedEdge<int> edge3(3, node2, node1, 1);
  CXXGraph::DirectedWeightedEdge<int> edge4(4, node1, node3, 12);
  CXXGraph::DirectedWeightedEdge<int> edge5(5, node2, node4, 11);
  CXXGraph::DirectedWeightedEdge<int> edge6(6, node4, node3, 7);
  CXXGraph::DirectedWeightedEdge<int> edge7(7, node4, node5, 4);
  CXXGraph::DirectedWeightedEdge<int> edge8(8, node3, node5, 19);
  CXXGraph::T_EdgeSet<int> edgeSet;
  edgeSet.insert(make_shared<CXXGraph::DirectedWeightedEdge<int>>(edge1));
  edgeSet.insert(make_shared<CXXGraph::DirectedWeightedEdge<int>>(edge2));
  edgeSet.insert(make_shared<CXXGraph::DirectedWeightedEdge<int>>(edge3));
  edgeSet.insert(make_shared<CXXGraph::DirectedWeightedEdge<int>>(edge4));
  edgeSet.insert(make_shared<CXXGraph::DirectedWeightedEdge<int>>(edge5));
  edgeSet.insert(make_shared<CXXGraph::DirectedWeightedEdge<int>>(edge6));
  edgeSet.insert(make_shared<CXXGraph::DirectedWeightedEdge<int>>(edge7));
  edgeSet.insert(make_shared<CXXGraph::DirectedWeightedEdge<int>>(edge8));

  CXXGraph::Graph<int> graph(edgeSet);

  ASSERT_EQ(graph.fordFulkersonMaxFlow(node0, node5), 23);
}

TEST(FordFulkersonTest, test_2) {
  CXXGraph::Node<int> node0("0", 0);
  CXXGraph::Node<int> node1("1", 1);
  CXXGraph::Node<int> node2("2", 2);
  CXXGraph::Node<int> node3("3", 3);
  CXXGraph::Node<int> node4("4", 4);
  CXXGraph::Node<int> node5("5", 5);

  CXXGraph::UndirectedWeightedEdge<int> edge1(1, node0, node1, 11);
  CXXGraph::DirectedWeightedEdge<int> edge2(2, node0, node2, 12);
  CXXGraph::DirectedWeightedEdge<int> edge3(3, node2, node1, 1);
  CXXGraph::DirectedWeightedEdge<int> edge4(4, node1, node3, 12);
  CXXGraph::DirectedWeightedEdge<int> edge5(5, node2, node4, 11);
  CXXGraph::DirectedWeightedEdge<int> edge6(6, node4, node3, 7);
  CXXGraph::DirectedWeightedEdge<int> edge7(7, node4, node5, 4);
  CXXGraph::DirectedWeightedEdge<int> edge8(8, node3, node5, 19);
  CXXGraph::T_EdgeSet<int> edgeSet;
  edgeSet.insert(make_shared<CXXGraph::UndirectedWeightedEdge<int>>(edge1));
  edgeSet.insert(make_shared<CXXGraph::DirectedWeightedEdge<int>>(edge2));
  edgeSet.insert(make_shared<CXXGraph::DirectedWeightedEdge<int>>(edge3));
  edgeSet.insert(make_shared<CXXGraph::DirectedWeightedEdge<int>>(edge4));
  edgeSet.insert(make_shared<CXXGraph::DirectedWeightedEdge<int>>(edge5));
  edgeSet.insert(make_shared<CXXGraph::DirectedWeightedEdge<int>>(edge6));
  edgeSet.insert(make_shared<CXXGraph::DirectedWeightedEdge<int>>(edge7));
  edgeSet.insert(make_shared<CXXGraph::DirectedWeightedEdge<int>>(edge8));

  CXXGraph::Graph<int> graph(edgeSet);

  ASSERT_EQ(graph.fordFulkersonMaxFlow(node0, node5), -1);
}

TEST(FordFulkersonTest, test_3) {
  CXXGraph::Node<int> node0("0", 0);
  CXXGraph::Node<int> node1("1", 1);
  CXXGraph::Node<int> node2("2", 2);
  CXXGraph::Node<int> node3("3", 3);
  CXXGraph::Node<int> node4("4", 4);
  CXXGraph::Node<int> node5("5", 5);

  CXXGraph::DirectedWeightedEdge<int> edge1(1, node0, node1, 11);
  CXXGraph::DirectedWeightedEdge<int> edge2(2, node0, node2, 12);
  CXXGraph::DirectedWeightedEdge<int> edge3(3, node2, node1, 1);
  CXXGraph::DirectedWeightedEdge<int> edge4(4, node1, node3, 12);
  CXXGraph::DirectedWeightedEdge<int> edge5(5, node2, node4, 11);
  CXXGraph::DirectedWeightedEdge<int> edge6(6, node4, node3, 7);
  CXXGraph::DirectedWeightedEdge<int> edge7(7, node4, node5, 4);
  CXXGraph::DirectedWeightedEdge<int> edge8(8, node3, node5, 4);
  CXXGraph::T_EdgeSet<int> edgeSet;
  edgeSet.insert(make_shared<CXXGraph::DirectedWeightedEdge<int>>(edge1));
  edgeSet.insert(make_shared<CXXGraph::DirectedWeightedEdge<int>>(edge2));
  edgeSet.insert(make_shared<CXXGraph::DirectedWeightedEdge<int>>(edge3));
  edgeSet.insert(make_shared<CXXGraph::DirectedWeightedEdge<int>>(edge4));
  edgeSet.insert(make_shared<CXXGraph::DirectedWeightedEdge<int>>(edge5));
  edgeSet.insert(make_shared<CXXGraph::DirectedWeightedEdge<int>>(edge6));
  edgeSet.insert(make_shared<CXXGraph::DirectedWeightedEdge<int>>(edge7));
  edgeSet.insert(make_shared<CXXGraph::DirectedWeightedEdge<int>>(edge8));

  CXXGraph::Graph<int> graph(edgeSet);

  ASSERT_EQ(graph.fordFulkersonMaxFlow(node0, node5), 8);
}

TEST(FordFulkersonTest, test_4) {
  CXXGraph::Node<int> node0("0", 0);
  CXXGraph::Node<int> node1("1", 1);
  CXXGraph::Node<int> node2("2", 2);
  CXXGraph::Node<int> node3("3", 3);
  CXXGraph::Node<int> node4("4", 4);
  CXXGraph::Node<int> node5("5", 5);

  CXXGraph::DirectedWeightedEdge<int> edge1(1, node0, node1, 11);
  CXXGraph::DirectedWeightedEdge<int> edge2(2, node0, node2, 12);
  CXXGraph::DirectedWeightedEdge<int> edge3(3, node2, node1, 1);
  CXXGraph::DirectedWeightedEdge<int> edge4(4, node1, node3, 12);
  CXXGraph::DirectedWeightedEdge<int> edge5(5, node2, node4, 11);
  CXXGraph::DirectedWeightedEdge<int> edge6(6, node4, node3, 7);
  CXXGraph::DirectedEdge<int> edge7(7, node4, node5);
  CXXGraph::DirectedWeightedEdge<int> edge8(8, node3, node5, 4);
  CXXGraph::T_EdgeSet<int> edgeSet;
  edgeSet.insert(make_shared<CXXGraph::DirectedWeightedEdge<int>>(edge1));
  edgeSet.insert(make_shared<CXXGraph::DirectedWeightedEdge<int>>(edge2));
  edgeSet.insert(make_shared<CXXGraph::DirectedWeightedEdge<int>>(edge3));
  edgeSet.insert(make_shared<CXXGraph::DirectedWeightedEdge<int>>(edge4));
  edgeSet.insert(make_shared<CXXGraph::DirectedWeightedEdge<int>>(edge5));
  edgeSet.insert(make_shared<CXXGraph::DirectedWeightedEdge<int>>(edge6));
  edgeSet.insert(make_shared<CXXGraph::DirectedEdge<int>>(edge7));
  edgeSet.insert(make_shared<CXXGraph::DirectedWeightedEdge<int>>(edge8));

  CXXGraph::Graph<int> graph(edgeSet);

  ASSERT_EQ(graph.fordFulkersonMaxFlow(node0, node5), 4);
}
