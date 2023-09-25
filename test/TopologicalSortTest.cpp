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

// topological sort test in a cyclic graph
TEST(TopologicalSortTest, test_1) {
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

  CXXGraph::TopoSortResult<int> &&res = graph.topologicalSort();
  ASSERT_EQ(res.success, false);
  ASSERT_EQ(res.errorMessage, CXXGraph::ERR_CYCLIC_GRAPH);
}

// topogical sort test in a undirected graph
TEST(TopologicalSortTest, test_2) {
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
  edgeSet.insert(make_shared<CXXGraph::UndirectedWeightedEdge<int>>(edge1));
  edgeSet.insert(make_shared<CXXGraph::UndirectedWeightedEdge<int>>(edge1));
  edgeSet.insert(make_shared<CXXGraph::UndirectedWeightedEdge<int>>(edge1));
  CXXGraph::Graph<int> graph(edgeSet);

  CXXGraph::TopoSortResult<int> &&res = graph.topologicalSort();
  ASSERT_EQ(res.success, false);
  ASSERT_EQ(res.errorMessage, CXXGraph::ERR_UNDIR_GRAPH);
}

// topogical sort test in a tiny graph
TEST(TopologicalSortTest, test_3) {
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
  CXXGraph::DirectedWeightedEdge<int> edge4(3, node3, node4, 6);
  CXXGraph::DirectedWeightedEdge<int> edge5(3, node3, node5, 6);
  CXXGraph::DirectedWeightedEdge<int> edge6(3, node6, node7, 6);
  CXXGraph::DirectedWeightedEdge<int> edge7(3, node8, node6, 6);
  CXXGraph::DirectedWeightedEdge<int> edge8(3, node8, node7, 6);
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

  CXXGraph::TopoSortResult<int> &&res = graph.topologicalSort();
  ASSERT_EQ(res.success, true);
  ASSERT_TRUE(res.errorMessage.empty());
  ASSERT_EQ(res.nodesInTopoOrder.size(), 8);

  // check topological order of nodes
  std::unordered_map<CXXGraph::id_t, int> nodeToOrder;
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
