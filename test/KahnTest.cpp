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

TEST(KahnTest, error_cyclic_graph) {
  CXXGraph::Node<int> node1("1", 1);
  CXXGraph::Node<int> node2("2", 2);
  CXXGraph::Node<int> node3("3", 3);
  std::pair<const CXXGraph::Node<int> *, const CXXGraph::Node<int> *> pairNode(
      &node1, &node2);
  CXXGraph::DirectedWeightedEdge<int> edge1(1, pairNode, 1);
  CXXGraph::DirectedWeightedEdge<int> edge2(2, node2, node3, 2);
  CXXGraph::DirectedWeightedEdge<int> edge3(3, node3, node1, 3);
  CXXGraph::T_EdgeSet<int> edgeSet;
  edgeSet.insert(make_shared<CXXGraph::DirectedWeightedEdge<int>>(edge1));
  edgeSet.insert(make_shared<CXXGraph::DirectedWeightedEdge<int>>(edge2));
  edgeSet.insert(make_shared<CXXGraph::DirectedWeightedEdge<int>>(edge3));
  CXXGraph::Graph<int> graph(edgeSet);

  CXXGraph::TopoSortResult<int> res = graph.kahn();
  ASSERT_EQ(res.success, false);
  ASSERT_EQ(res.errorMessage, CXXGraph::ERR_CYCLIC_GRAPH);
}

TEST(KahnTest, error_undirected_graph) {
  CXXGraph::Node<int> node1("1", 1);
  CXXGraph::Node<int> node2("2", 2);
  CXXGraph::Node<int> node3("3", 3);
  CXXGraph::Node<int> node4("4", 4);
  CXXGraph::Node<int> node5("5", 5);
  std::pair<const CXXGraph::Node<int> *, const CXXGraph::Node<int> *> pairNode(
      &node1, &node2);
  CXXGraph::UndirectedWeightedEdge<int> edge1(1, pairNode, 1);
  CXXGraph::UndirectedWeightedEdge<int> edge2(2, node2, node3, 1);
  CXXGraph::UndirectedWeightedEdge<int> edge3(3, node3, node4, 1);
  CXXGraph::UndirectedWeightedEdge<int> edge4(3, node3, node5, 1);
  CXXGraph::T_EdgeSet<int> edgeSet;
  edgeSet.insert(make_shared<CXXGraph::UndirectedWeightedEdge<int>>(edge1));
  edgeSet.insert(make_shared<CXXGraph::UndirectedWeightedEdge<int>>(edge2));
  edgeSet.insert(make_shared<CXXGraph::UndirectedWeightedEdge<int>>(edge3));
  edgeSet.insert(make_shared<CXXGraph::UndirectedWeightedEdge<int>>(edge4));
  CXXGraph::Graph<int> graph(edgeSet);

  CXXGraph::TopoSortResult<int> &&res = graph.kahn();
  ASSERT_EQ(res.success, false);
  ASSERT_EQ(res.errorMessage, CXXGraph::ERR_UNDIR_GRAPH);
}

TEST(KahnTest, correct_example_small) {
  CXXGraph::Node<int> node1("1", 1);
  CXXGraph::Node<int> node2("2", 2);
  CXXGraph::Node<int> node3("3", 3);
  CXXGraph::Node<int> node4("4", 4);
  CXXGraph::Node<int> node5("5", 5);
  CXXGraph::Node<int> node6("6", 6);
  CXXGraph::Node<int> node7("7", 7);
  CXXGraph::Node<int> node8("8", 8);
  std::pair<const CXXGraph::Node<int> *, const CXXGraph::Node<int> *> pairNode(
      &node1, &node2);
  CXXGraph::DirectedWeightedEdge<int> edge1(1, pairNode, 1);
  CXXGraph::DirectedWeightedEdge<int> edge2(2, node2, node3, 1);
  CXXGraph::DirectedWeightedEdge<int> edge3(3, node2, node6, 6);
  CXXGraph::DirectedWeightedEdge<int> edge4(4, node3, node4, 6);
  CXXGraph::DirectedWeightedEdge<int> edge5(5, node3, node5, 6);
  CXXGraph::DirectedWeightedEdge<int> edge6(6, node6, node7, 6);
  CXXGraph::DirectedWeightedEdge<int> edge7(7, node8, node6, 6);
  CXXGraph::DirectedWeightedEdge<int> edge8(8, node8, node7, 6);
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

  CXXGraph::TopoSortResult<int> res = graph.kahn();
  ASSERT_EQ(res.success, true);
  ASSERT_TRUE(res.errorMessage.empty());
  ASSERT_EQ(res.nodesInTopoOrder.size(), graph.getNodeSet().size());

  std::unordered_map<CXXGraph::id_t, int> topOrderNodeIds;
  for (int i = 0; i < res.nodesInTopoOrder.size(); ++i) {
    topOrderNodeIds[res.nodesInTopoOrder[i].getId()] = i;
  }

  for (const auto &node : graph.getNodeSet()) {
    ASSERT_TRUE(topOrderNodeIds.count(node->getId()));
  }
}

TEST(KahnTest, correct_example_big) {
  CXXGraph::Node<int> node0("0", 0);
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
  CXXGraph::DirectedEdge<int> edge1(1, node0, node2);
  CXXGraph::DirectedEdge<int> edge2(2, node0, node3);
  CXXGraph::DirectedEdge<int> edge3(3, node0, node6);
  CXXGraph::DirectedEdge<int> edge4(4, node1, node4);
  CXXGraph::DirectedEdge<int> edge5(5, node2, node6);
  CXXGraph::DirectedEdge<int> edge6(6, node3, node1);
  CXXGraph::DirectedEdge<int> edge7(7, node3, node4);
  CXXGraph::DirectedEdge<int> edge8(8, node4, node5);
  CXXGraph::DirectedEdge<int> edge9(9, node4, node8);
  CXXGraph::DirectedEdge<int> edge10(10, node6, node7);
  CXXGraph::DirectedEdge<int> edge11(11, node6, node11);
  CXXGraph::DirectedEdge<int> edge12(12, node7, node4);
  CXXGraph::DirectedEdge<int> edge13(13, node7, node12);
  CXXGraph::DirectedEdge<int> edge14(14, node9, node2);
  CXXGraph::DirectedEdge<int> edge15(15, node9, node10);
  CXXGraph::DirectedEdge<int> edge16(16, node10, node6);
  CXXGraph::DirectedEdge<int> edge17(17, node11, node12);
  CXXGraph::DirectedEdge<int> edge18(18, node12, node8);
  CXXGraph::T_EdgeSet<int> edgeSet;
  edgeSet.insert(make_shared<CXXGraph::DirectedEdge<int>>(edge1));
  edgeSet.insert(make_shared<CXXGraph::DirectedEdge<int>>(edge2));
  edgeSet.insert(make_shared<CXXGraph::DirectedEdge<int>>(edge3));
  edgeSet.insert(make_shared<CXXGraph::DirectedEdge<int>>(edge4));
  edgeSet.insert(make_shared<CXXGraph::DirectedEdge<int>>(edge5));
  edgeSet.insert(make_shared<CXXGraph::DirectedEdge<int>>(edge6));
  edgeSet.insert(make_shared<CXXGraph::DirectedEdge<int>>(edge7));
  edgeSet.insert(make_shared<CXXGraph::DirectedEdge<int>>(edge8));
  edgeSet.insert(make_shared<CXXGraph::DirectedEdge<int>>(edge9));
  edgeSet.insert(make_shared<CXXGraph::DirectedEdge<int>>(edge10));
  edgeSet.insert(make_shared<CXXGraph::DirectedEdge<int>>(edge11));
  edgeSet.insert(make_shared<CXXGraph::DirectedEdge<int>>(edge12));
  edgeSet.insert(make_shared<CXXGraph::DirectedEdge<int>>(edge13));
  edgeSet.insert(make_shared<CXXGraph::DirectedEdge<int>>(edge14));
  edgeSet.insert(make_shared<CXXGraph::DirectedEdge<int>>(edge15));
  edgeSet.insert(make_shared<CXXGraph::DirectedEdge<int>>(edge16));
  edgeSet.insert(make_shared<CXXGraph::DirectedEdge<int>>(edge17));
  edgeSet.insert(make_shared<CXXGraph::DirectedEdge<int>>(edge18));
  CXXGraph::Graph<int> graph(edgeSet);

  CXXGraph::TopoSortResult<int> res = graph.kahn();
  ASSERT_EQ(res.success, true);
  ASSERT_TRUE(res.errorMessage.empty());
  ASSERT_EQ(res.nodesInTopoOrder.size(), graph.getNodeSet().size());

  std::unordered_map<CXXGraph::id_t, int> topOrderNodeIds;
  for (int i = 0; i < res.nodesInTopoOrder.size(); ++i) {
    topOrderNodeIds[res.nodesInTopoOrder[i].getId()] = i;
  }

  for (const auto &node : graph.getNodeSet()) {
    ASSERT_TRUE(topOrderNodeIds.count(node->getId()));
  }
}
