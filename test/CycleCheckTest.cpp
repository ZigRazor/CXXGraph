#include <memory>
#include <vector>
#include <string>
#include <random>

#include "CXXGraph/CXXGraph.hpp"
#include "gtest/gtest.h"

// Smart pointers alias
template <typename T>
using unique = std::unique_ptr<T>;
template <typename T>
using shared = std::shared_ptr<T>;

using std::shared_ptr;
using std::make_shared;
using std::make_unique;

TEST(CycleCheckTest, test_1) {
  CXXGraph::Node<int> node1("1", 1);
  CXXGraph::Node<int> node2("2", 2);
  CXXGraph::Node<int> node3("3", 3);
  std::pair<const CXXGraph::Node<int> *, const CXXGraph::Node<int> *> pairNode(
      &node1, &node2);
  CXXGraph::DirectedWeightedEdge<int> edge1("1", pairNode, 1);
  CXXGraph::DirectedWeightedEdge<int> edge2("2", node2, node3, 1);
  CXXGraph::DirectedWeightedEdge<int> edge3("3", node1, node3, 6);
  CXXGraph::T_EdgeSet<int> edgeSet;
  edgeSet.insert(make_shared<CXXGraph::DirectedWeightedEdge<int>>(edge1));
  edgeSet.insert(make_shared<CXXGraph::DirectedWeightedEdge<int>>(edge2));
  edgeSet.insert(make_shared<CXXGraph::DirectedWeightedEdge<int>>(edge3));
  CXXGraph::Graph<int> graph(edgeSet);
  bool res = graph.isCyclicDirectedGraphDFS();
  ASSERT_EQ(res, false);
}

TEST(CycleCheckTest, test_2) {
  CXXGraph::Node<int> node1("1", 1);
  CXXGraph::Node<int> node2("2", 2);
  CXXGraph::Node<int> node3("3", 3);
  std::pair<const CXXGraph::Node<int> *, const CXXGraph::Node<int> *> pairNode(
      &node1, &node2);
  CXXGraph::DirectedWeightedEdge<int> edge1("1", pairNode, 1);
  CXXGraph::DirectedWeightedEdge<int> edge2("2", node2, node3, 1);
  CXXGraph::T_EdgeSet<int> edgeSet;
  edgeSet.insert(make_shared<CXXGraph::DirectedWeightedEdge<int>>(edge1));
  edgeSet.insert(make_shared<CXXGraph::DirectedWeightedEdge<int>>(edge2));
  CXXGraph::Graph<int> graph(edgeSet);
  bool res = graph.isCyclicDirectedGraphDFS();
  ASSERT_EQ(res, false);
}

TEST(CycleCheckTest, test_3) {
  CXXGraph::Node<int> node1("1", 1);
  CXXGraph::Node<int> node2("2", 2);
  CXXGraph::Node<int> node3("3", 3);
  std::pair<const CXXGraph::Node<int> *, const CXXGraph::Node<int> *> pairNode(
      &node1, &node2);
  CXXGraph::DirectedWeightedEdge<int> edge1("1", pairNode, 1);
  CXXGraph::DirectedWeightedEdge<int> edge2("2", node2, node3, 1);
  CXXGraph::UndirectedWeightedEdge<int> edge3("3", node1, node3, 6);
  CXXGraph::T_EdgeSet<int> edgeSet;
  edgeSet.insert(make_shared<CXXGraph::DirectedWeightedEdge<int>>(edge1));
  edgeSet.insert(make_shared<CXXGraph::DirectedWeightedEdge<int>>(edge2));
  edgeSet.insert(make_shared<CXXGraph::UndirectedWeightedEdge<int>>(edge3));
  CXXGraph::Graph<int> graph(edgeSet);
  bool res = graph.isCyclicDirectedGraphDFS();
  ASSERT_EQ(res, false);
}

TEST(CycleCheckTest, test_4) {
  CXXGraph::Node<int> node1("1", 1);
  CXXGraph::Node<int> node2("2", 2);
  CXXGraph::Node<int> node3("3", 3);
  std::pair<const CXXGraph::Node<int> *, const CXXGraph::Node<int> *> pairNode(
      &node1, &node2);
  CXXGraph::DirectedWeightedEdge<int> edge1("1", pairNode, 1);
  CXXGraph::DirectedWeightedEdge<int> edge2("2", node2, node3, 1);
  CXXGraph::DirectedWeightedEdge<int> edge3("3", node3, node1, 6);
  CXXGraph::T_EdgeSet<int> edgeSet;
  edgeSet.insert(make_shared<CXXGraph::DirectedWeightedEdge<int>>(edge1));
  edgeSet.insert(make_shared<CXXGraph::DirectedWeightedEdge<int>>(edge2));
  edgeSet.insert(make_shared<CXXGraph::DirectedWeightedEdge<int>>(edge3));
  CXXGraph::Graph<int> graph(edgeSet);
  bool res = graph.isCyclicDirectedGraphDFS();
  ASSERT_EQ(res, true);
}

TEST(CycleCheckTest, test_5) {
  CXXGraph::Node<int> node1("1", 1);
  CXXGraph::Node<int> node2("2", 2);
  CXXGraph::Node<int> node3("3", 3);
  std::pair<const CXXGraph::Node<int> *, const CXXGraph::Node<int> *> pairNode(
      &node1, &node2);
  CXXGraph::DirectedWeightedEdge<int> edge1("1", pairNode, 1);
  CXXGraph::DirectedWeightedEdge<int> edge2("2", node2, node3, 1);
  CXXGraph::DirectedWeightedEdge<int> edge3("3", node1, node3, 6);
  CXXGraph::T_EdgeSet<int> edgeSet;
  edgeSet.insert(make_shared<CXXGraph::DirectedWeightedEdge<int>>(edge1));
  edgeSet.insert(make_shared<CXXGraph::DirectedWeightedEdge<int>>(edge2));
  edgeSet.insert(make_shared<CXXGraph::DirectedWeightedEdge<int>>(edge3));
  CXXGraph::Graph<int> graph(edgeSet);
  bool res = graph.isCyclicDirectedGraphBFS();
  ASSERT_EQ(res, false);
}

TEST(CycleCheckTest, test_6) {
  CXXGraph::Node<int> node1("1", 1);
  CXXGraph::Node<int> node2("2", 2);
  CXXGraph::Node<int> node3("3", 3);
  std::pair<const CXXGraph::Node<int> *, const CXXGraph::Node<int> *> pairNode(
      &node1, &node2);
  CXXGraph::DirectedWeightedEdge<int> edge1("1", pairNode, 1);
  CXXGraph::DirectedWeightedEdge<int> edge2("2", node2, node3, 1);
  CXXGraph::T_EdgeSet<int> edgeSet;
  edgeSet.insert(make_shared<CXXGraph::DirectedWeightedEdge<int>>(edge1));
  edgeSet.insert(make_shared<CXXGraph::DirectedWeightedEdge<int>>(edge2));
  CXXGraph::Graph<int> graph(edgeSet);
  bool res = graph.isCyclicDirectedGraphBFS();
  ASSERT_EQ(res, false);
}

TEST(CycleCheckTest, test_7) {
  CXXGraph::Node<int> node1("1", 1);
  CXXGraph::Node<int> node2("2", 2);
  CXXGraph::Node<int> node3("3", 3);
  std::pair<const CXXGraph::Node<int> *, const CXXGraph::Node<int> *> pairNode(
      &node1, &node2);
  CXXGraph::DirectedWeightedEdge<int> edge1("1", pairNode, 1);
  CXXGraph::DirectedWeightedEdge<int> edge2("2", node2, node3, 1);
  CXXGraph::UndirectedWeightedEdge<int> edge3("3", node1, node3, 6);
  CXXGraph::T_EdgeSet<int> edgeSet;
  edgeSet.insert(make_shared<CXXGraph::DirectedWeightedEdge<int>>(edge1));
  edgeSet.insert(make_shared<CXXGraph::DirectedWeightedEdge<int>>(edge2));
  edgeSet.insert(make_shared<CXXGraph::UndirectedWeightedEdge<int>>(edge3));
  CXXGraph::Graph<int> graph(edgeSet);
  bool res = graph.isCyclicDirectedGraphBFS();
  ASSERT_EQ(res, false);
}

TEST(CycleCheckTest, test_8) {
  CXXGraph::Node<int> node1("1", 1);
  CXXGraph::Node<int> node2("2", 2);
  CXXGraph::Node<int> node3("3", 3);
  std::pair<const CXXGraph::Node<int> *, const CXXGraph::Node<int> *> pairNode(
      &node1, &node2);
  CXXGraph::DirectedWeightedEdge<int> edge1("1", pairNode, 1);
  CXXGraph::DirectedWeightedEdge<int> edge2("2", node2, node3, 1);
  CXXGraph::DirectedWeightedEdge<int> edge3("3", node3, node1, 6);
  CXXGraph::T_EdgeSet<int> edgeSet;
  edgeSet.insert(make_shared<CXXGraph::DirectedWeightedEdge<int>>(edge1));
  edgeSet.insert(make_shared<CXXGraph::DirectedWeightedEdge<int>>(edge2));
  edgeSet.insert(make_shared<CXXGraph::DirectedWeightedEdge<int>>(edge3));
  CXXGraph::Graph<int> graph(edgeSet);
  bool res = graph.isCyclicDirectedGraphBFS();
  ASSERT_EQ(res, true);
}

TEST(CycleCheckTest, test_2001000) {
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<int> distrib(1, 100);

  std::vector<CXXGraph::Node<int>> nodes;
  std::vector<CXXGraph::DirectedWeightedEdge<int>> edges;
  nodes.reserve(2001000);
  edges.reserve(2001000);
  CXXGraph::T_EdgeSet<int> edgeSet;
  int node_i = 1;
  int edge_i = 1;

  /*
   * Creates a Tree Graph with a root node in which each level
   * has one more node than the previous one, having in the end
   * 2000*2001/2 = 2001000 nodes the form looks as follows:
   * node1-node2
   *     |-node3-node4
   *           |-node5
   *           |-node6...
   */
  CXXGraph::Node<int> node(std::to_string(node_i), node_i);
  nodes.push_back(node);
  node_i++;
  for (int i = 2; i < 2001; i++) {
    for (int j = 0; j < i; j++) {
      auto last_i_node = nodes.back();
      CXXGraph::Node<int> node(std::to_string(node_i), node_i);
      nodes.push_back(node);
      node_i++;
      CXXGraph::DirectedWeightedEdge<int> edge(std::to_string(edge_i++), last_i_node, nodes.back(), distrib(gen));
      edgeSet.insert(make_shared<CXXGraph::DirectedWeightedEdge<int>>(edge));
    }
  }
  CXXGraph::Graph<int> graph_tree(edgeSet);
  ASSERT_EQ(graph_tree.isCyclicDirectedGraphBFS(), false);
  CXXGraph::DirectedWeightedEdge<int> edge(std::to_string(edge_i++), nodes.back(), nodes.front(), distrib(gen));
  edgeSet.insert(make_shared<CXXGraph::DirectedWeightedEdge<int>>(edge));
  CXXGraph::Graph<int> graph_cycle(edgeSet);
  ASSERT_EQ(graph_cycle.isCyclicDirectedGraphBFS(), true);
}
