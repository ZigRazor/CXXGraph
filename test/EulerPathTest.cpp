#include "CXXGraph.hpp"
#include "gtest/gtest.h"

// example taken from
// https://www.geeksforgeeks.org/hierholzers-algorithm-directed-graph/
// different eulerian paths (i.e different node visit order)
// are possible for the same graph
// so we check if all the nodes in the graph are atleast traversed
// once in the eulerian path
TEST(EulerPathTest, test_1) {
  CXXGRAPH::Node<int> node0("0", 0);
  CXXGRAPH::Node<int> node1("1", 1);
  CXXGRAPH::Node<int> node2("2", 2);

  CXXGRAPH::DirectedWeightedEdge<int> edge1(1, node0, node1, 4);
  CXXGRAPH::DirectedWeightedEdge<int> edge2(2, node1, node2, 8);
  CXXGRAPH::DirectedWeightedEdge<int> edge3(3, node2, node0, 11);
  CXXGRAPH::T_EdgeSet<int> edgeSet;
  edgeSet.insert(&edge1);
  edgeSet.insert(&edge2);
  edgeSet.insert(&edge3);

  CXXGRAPH::Graph<int> graph(edgeSet);
  auto res = graph.eulerianPath();
  auto nodeSet = graph.getNodeSet();
  for (const auto& node : nodeSet) {
    auto check = std::find_if(res->begin(), res->end(), [node](auto it) {
                   return (node->getUserId() == it.getUserId());
                 }) == res->end();

    ASSERT_FALSE(check);
  }
}

TEST(EulerPathTest, test_2) {
  CXXGRAPH::Node<int> node0("0", 0);
  CXXGRAPH::Node<int> node1("1", 1);
  CXXGRAPH::Node<int> node2("2", 2);
  CXXGRAPH::Node<int> node3("3", 3);
  CXXGRAPH::Node<int> node4("4", 4);

  CXXGRAPH::DirectedWeightedEdge<int> edge1(1, node0, node1, 4);
  CXXGRAPH::DirectedWeightedEdge<int> edge2(2, node1, node2, 8);
  CXXGRAPH::DirectedWeightedEdge<int> edge3(3, node2, node0, 11);
  CXXGRAPH::DirectedWeightedEdge<int> edge4(4, node1, node3, 11);
  CXXGRAPH::DirectedWeightedEdge<int> edge5(5, node3, node4, 11);
  CXXGRAPH::DirectedWeightedEdge<int> edge6(6, node4, node1, 11);

  CXXGRAPH::T_EdgeSet<int> edgeSet;
  edgeSet.insert(&edge1);
  edgeSet.insert(&edge2);
  edgeSet.insert(&edge3);
  edgeSet.insert(&edge4);
  edgeSet.insert(&edge5);
  edgeSet.insert(&edge6);

  CXXGRAPH::Graph<int> graph(edgeSet);
  auto res = graph.eulerianPath();
  auto nodeSet = graph.getNodeSet();
  for (const auto& node : nodeSet) {
    auto check = std::find_if(res->begin(), res->end(), [node](auto it) {
                   return (node->getUserId() == it.getUserId());
                 }) == res->end();

    ASSERT_FALSE(check);
  }
}

TEST(EulerPathTest, test_3) {
  CXXGRAPH::Node<int> node0("0", 0);
  CXXGRAPH::Node<int> node1("1", 1);
  CXXGRAPH::Node<int> node2("2", 2);
  CXXGRAPH::Node<int> node3("3", 3);
  CXXGRAPH::Node<int> node4("4", 4);
  CXXGRAPH::Node<int> node5("5", 5);
  CXXGRAPH::Node<int> node6("6", 6);

  CXXGRAPH::DirectedEdge<int> edge1(1, node0, node1);
  CXXGRAPH::DirectedEdge<int> edge2(2, node0, node6);
  CXXGRAPH::DirectedEdge<int> edge3(3, node1, node2);
  CXXGRAPH::DirectedEdge<int> edge4(4, node2, node3);
  CXXGRAPH::DirectedEdge<int> edge5(5, node3, node4);
  CXXGRAPH::DirectedEdge<int> edge6(6, node4, node5);
  CXXGRAPH::DirectedEdge<int> edge7(6, node5, node0);
  CXXGRAPH::DirectedEdge<int> edge8(6, node6, node4);

  CXXGRAPH::T_EdgeSet<int> edgeSet;
  edgeSet.insert(&edge1);
  edgeSet.insert(&edge2);
  edgeSet.insert(&edge3);
  edgeSet.insert(&edge4);
  edgeSet.insert(&edge5);
  edgeSet.insert(&edge6);
  edgeSet.insert(&edge7);
  edgeSet.insert(&edge8);

  CXXGRAPH::Graph<int> graph(edgeSet);
  auto res = graph.eulerianPath();
  auto nodeSet = graph.getNodeSet();
  for (const auto& node : nodeSet) {
    auto check = std::find_if(res->begin(), res->end(), [node](auto it) {
                   return (node->getUserId() == it.getUserId());
                 }) == res->end();

    ASSERT_FALSE(check);
  }
}