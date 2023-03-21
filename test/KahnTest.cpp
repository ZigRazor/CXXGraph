#include "CXXGraph.hpp"
#include "Utility/ConstString.hpp"
#include "Utility/Typedef.hpp"
#include "gtest/gtest.h"

TEST(KahnTest, error_cyclic_graph) {
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

  CXXGRAPH::TopoSortResult<int> res = graph.kahn();
  ASSERT_EQ(res.success, false);
  ASSERT_EQ(res.errorMessage, CXXGRAPH::ERR_CYCLIC_GRAPH);
}

TEST(KahnTest, error_undirected_graph) {
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

  CXXGRAPH::TopoSortResult<int> &&res = graph.kahn();
  ASSERT_EQ(res.success, false);
  ASSERT_EQ(res.errorMessage, CXXGRAPH::ERR_UNDIR_GRAPH);
}

TEST(KahnTest, correct_example_small) {
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
  CXXGRAPH::DirectedWeightedEdge<int> edge4(4, node3, node4, 6);
  CXXGRAPH::DirectedWeightedEdge<int> edge5(5, node3, node5, 6);
  CXXGRAPH::DirectedWeightedEdge<int> edge6(6, node6, node7, 6);
  CXXGRAPH::DirectedWeightedEdge<int> edge7(7, node8, node6, 6);
  CXXGRAPH::DirectedWeightedEdge<int> edge8(8, node8, node7, 6);
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

  CXXGRAPH::TopoSortResult<int> res = graph.kahn();
  ASSERT_EQ(res.success, true);
  ASSERT_TRUE(res.errorMessage.empty());
  ASSERT_EQ(res.nodesInTopoOrder.size(), graph.getNodeSet().size());

  std::unordered_map<unsigned long, int> topOrderNodeIds;
  for (int i = 0; i < res.nodesInTopoOrder.size(); ++i) {
    topOrderNodeIds[res.nodesInTopoOrder[i].getId()] = i;
  }

  for (const auto &node : graph.getNodeSet()) {
    ASSERT_TRUE(topOrderNodeIds.count(node->getId()));
  }
}

TEST(KahnTest, correct_example_big) {
  CXXGRAPH::Node<int> node0("0", 0);
  CXXGRAPH::Node<int> node1("1", 1);
  CXXGRAPH::Node<int> node2("2", 2);
  CXXGRAPH::Node<int> node3("3", 3);
  CXXGRAPH::Node<int> node4("4", 4);
  CXXGRAPH::Node<int> node5("5", 5);
  CXXGRAPH::Node<int> node6("6", 6);
  CXXGRAPH::Node<int> node7("7", 7);
  CXXGRAPH::Node<int> node8("8", 8);
  CXXGRAPH::Node<int> node9("9", 9);
  CXXGRAPH::Node<int> node10("10", 10);
  CXXGRAPH::Node<int> node11("11", 11);
  CXXGRAPH::Node<int> node12("12", 12);
  CXXGRAPH::Node<int> node13("13", 13);
  CXXGRAPH::DirectedEdge<int> edge1(1, node0, node2);
  CXXGRAPH::DirectedEdge<int> edge2(2, node0, node3);
  CXXGRAPH::DirectedEdge<int> edge3(3, node0, node6);
  CXXGRAPH::DirectedEdge<int> edge4(4, node1, node4);
  CXXGRAPH::DirectedEdge<int> edge5(5, node2, node6);
  CXXGRAPH::DirectedEdge<int> edge6(6, node3, node1);
  CXXGRAPH::DirectedEdge<int> edge7(7, node3, node4);
  CXXGRAPH::DirectedEdge<int> edge8(8, node4, node5);
  CXXGRAPH::DirectedEdge<int> edge9(9, node4, node8);
  CXXGRAPH::DirectedEdge<int> edge10(10, node6, node7);
  CXXGRAPH::DirectedEdge<int> edge11(11, node6, node11);
  CXXGRAPH::DirectedEdge<int> edge12(12, node7, node4);
  CXXGRAPH::DirectedEdge<int> edge13(13, node7, node12);
  CXXGRAPH::DirectedEdge<int> edge14(14, node9, node2);
  CXXGRAPH::DirectedEdge<int> edge15(15, node9, node10);
  CXXGRAPH::DirectedEdge<int> edge16(16, node10, node6);
  CXXGRAPH::DirectedEdge<int> edge17(17, node11, node12);
  CXXGRAPH::DirectedEdge<int> edge18(18, node12, node8);
  CXXGRAPH::T_EdgeSet<int> edgeSet;
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
  edgeSet.insert(&edge14);
  edgeSet.insert(&edge15);
  edgeSet.insert(&edge16);
  edgeSet.insert(&edge17);
  edgeSet.insert(&edge18);
  CXXGRAPH::Graph<int> graph(edgeSet);

  CXXGRAPH::TopoSortResult<int> res = graph.kahn();
  ASSERT_EQ(res.success, true);
  ASSERT_TRUE(res.errorMessage.empty());
  ASSERT_EQ(res.nodesInTopoOrder.size(), graph.getNodeSet().size());

  std::unordered_map<unsigned long, int> topOrderNodeIds;
  for (int i = 0; i < res.nodesInTopoOrder.size(); ++i) {
    topOrderNodeIds[res.nodesInTopoOrder[i].getId()] = i;
  }

  for (const auto &node : graph.getNodeSet()) {
    ASSERT_TRUE(topOrderNodeIds.count(node->getId()));
  }
}
