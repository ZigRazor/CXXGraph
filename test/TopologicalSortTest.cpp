#include "CXXGraph.hpp"
#include "Utility/ConstString.hpp"
#include "Utility/Typedef.hpp"
#include "gtest/gtest.h"

// topological sort test in a cyclic graph
TEST(TopologicalSortTest, test_1) {
  CXXGRAPH::Node<int> node1("1", 1);
  CXXGRAPH::Node<int> node2("2", 2);
  CXXGRAPH::Node<int> node3("3", 3);
  std::pair<const CXXGRAPH::Node<int> *, const CXXGRAPH::Node<int> *> pairNode(
      &node1, &node2);
  CXXGRAPH::DirectedWeightedEdge<int> edge1(1, pairNode, 1);
  CXXGRAPH::DirectedWeightedEdge<int> edge2(2, node2, node3, 2);
  CXXGRAPH::DirectedWeightedEdge<int> edge3(3, node3, node1, 3);
  CXXGRAPH::T_EdgeSet<int> edgeSet;
  edgeSet.insert(&edge1);
  edgeSet.insert(&edge2);
  edgeSet.insert(&edge3);
  CXXGRAPH::Graph<int> graph(edgeSet);

  CXXGRAPH::TopoSortResult<int> &&res = graph.topologicalSort();
  ASSERT_EQ(res.success, false);
  ASSERT_EQ(res.errorMessage, CXXGRAPH::ERR_CYCLIC_GRAPH);
}

// topogical sort test in a undirected graph
TEST(TopologicalSortTest, test_2) {
  CXXGRAPH::Node<int> node1("1", 1);
  CXXGRAPH::Node<int> node2("2", 2);
  CXXGRAPH::Node<int> node3("3", 3);
  CXXGRAPH::Node<int> node4("4", 4);
  CXXGRAPH::Node<int> node5("5", 5);
  std::pair<const CXXGRAPH::Node<int> *, const CXXGRAPH::Node<int> *> pairNode(
      &node1, &node2);
  CXXGRAPH::UndirectedWeightedEdge<int> edge1(1, pairNode, 1);
  CXXGRAPH::UndirectedWeightedEdge<int> edge2(2, node2, node3, 1);
  CXXGRAPH::UndirectedWeightedEdge<int> edge3(3, node3, node4, 1);
  CXXGRAPH::UndirectedWeightedEdge<int> edge4(3, node3, node5, 1);
  CXXGRAPH::T_EdgeSet<int> edgeSet;
  edgeSet.insert(&edge1);
  edgeSet.insert(&edge2);
  edgeSet.insert(&edge3);
  edgeSet.insert(&edge4);
  CXXGRAPH::Graph<int> graph(edgeSet);

  CXXGRAPH::TopoSortResult<int> &&res = graph.topologicalSort();
  ASSERT_EQ(res.success, false);
  ASSERT_EQ(res.errorMessage, CXXGRAPH::ERR_UNDIR_GRAPH);
}

// topogical sort test in a tiny graph
TEST(TopologicalSortTest, test_3) {
  CXXGRAPH::Node<int> node1("1", 1);
  CXXGRAPH::Node<int> node2("2", 2);
  CXXGRAPH::Node<int> node3("3", 3);
  CXXGRAPH::Node<int> node4("4", 4);
  CXXGRAPH::Node<int> node5("5", 5);
  CXXGRAPH::Node<int> node6("6", 6);
  CXXGRAPH::Node<int> node7("7", 7);
  CXXGRAPH::Node<int> node8("8", 8);
  std::pair<const CXXGRAPH::Node<int> *, const CXXGRAPH::Node<int> *> pairNode(
      &node1, &node2);
  CXXGRAPH::DirectedWeightedEdge<int> edge1(1, pairNode, 1);
  CXXGRAPH::DirectedWeightedEdge<int> edge2(2, node2, node3, 1);
  CXXGRAPH::DirectedWeightedEdge<int> edge3(3, node2, node6, 6);
  CXXGRAPH::DirectedWeightedEdge<int> edge4(3, node3, node4, 6);
  CXXGRAPH::DirectedWeightedEdge<int> edge5(3, node3, node5, 6);
  CXXGRAPH::DirectedWeightedEdge<int> edge6(3, node6, node7, 6);
  CXXGRAPH::DirectedWeightedEdge<int> edge7(3, node8, node6, 6);
  CXXGRAPH::DirectedWeightedEdge<int> edge8(3, node8, node7, 6);
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

  CXXGRAPH::TopoSortResult<int> &&res = graph.topologicalSort();
  ASSERT_EQ(res.success, true);
  ASSERT_TRUE(res.errorMessage.empty());
  ASSERT_EQ(res.nodesInTopoOrder.size(), 8);

  // check topological order of nodes
  std::unordered_map<unsigned long, int> nodeToOrder;
  for (int i = 0; i < res.nodesInTopoOrder.size(); ++i) {
    nodeToOrder[res.nodesInTopoOrder[i].getId()] = i;
  }

  for (const auto &edge : edgeSet) {
    auto node_id1 = edge->getNodePair().first->getId();
    auto node_id2 = edge->getNodePair().second->getId();

    ASSERT_TRUE(nodeToOrder.count(node_id1) && nodeToOrder.count(node_id2));
    ASSERT_LT(nodeToOrder[node_id1], nodeToOrder[node_id2]);
  }
}

// more test cases to be needed