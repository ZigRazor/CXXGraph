#include "CXXGraph.hpp"
#include "gtest/gtest.h"

TEST(GraphTest, Constructor_1) {
  CXXGraph::Node<int> node1("1", 1);
  CXXGraph::Node<int> node2("2", 2);
  std::pair<const CXXGraph::Node<int> *, const CXXGraph::Node<int> *> pairNode(
      &node1, &node2);
  CXXGraph::Edge<int> edge(1, pairNode);
  CXXGraph::T_EdgeSet<int> edgeSet;
  edgeSet.insert(&edge);
  CXXGraph::Graph<int> graph(edgeSet);
  ASSERT_EQ(graph.getEdgeSet(), edgeSet);
}

TEST(GraphTest, GetEdge_1) {
  CXXGraph::Node<int> node1("1", 1);
  CXXGraph::Node<int> node2("2", 2);
  std::pair<const CXXGraph::Node<int> *, const CXXGraph::Node<int> *> pairNode(
      &node1, &node2);
  CXXGraph::Edge<int> edge(1, pairNode);
  CXXGraph::T_EdgeSet<int> edgeSet;
  edgeSet.insert(&edge);
  CXXGraph::Graph<int> graph(edgeSet);
  ASSERT_FALSE(graph.getEdge(2).has_value());
}

TEST(GraphTest, GetEdge_2) {
  CXXGraph::Node<int> node1("1", 1);
  CXXGraph::Node<int> node2("2", 2);
  std::pair<const CXXGraph::Node<int> *, const CXXGraph::Node<int> *> pairNode(
      &node1, &node2);
  CXXGraph::Edge<int> edge(1, pairNode);
  CXXGraph::T_EdgeSet<int> edgeSet;
  edgeSet.insert(&edge);
  CXXGraph::Graph<int> graph(edgeSet);
  ASSERT_TRUE(graph.getEdge(1).has_value());
}

TEST(GraphTest, GetEdge_3) {
  CXXGraph::Node<int> node1("1", 1);
  CXXGraph::Node<int> node2("2", 2);
  std::pair<const CXXGraph::Node<int> *, const CXXGraph::Node<int> *> pairNode(
      &node1, &node2);
  CXXGraph::Edge<int> edge(1, pairNode);
  CXXGraph::T_EdgeSet<int> edgeSet;
  edgeSet.insert(&edge);
  CXXGraph::Graph<int> graph(edgeSet);
  ASSERT_EQ(*(graph.getEdge(1).value()), edge);
}

TEST(GraphTest, GetNodeSet_1) {
  CXXGraph::Node<int> node1("1", 1);
  CXXGraph::Node<int> node2("2", 2);
  std::pair<const CXXGraph::Node<int> *, const CXXGraph::Node<int> *> pairNode(
      &node1, &node2);
  CXXGraph::Edge<int> edge(1, pairNode);
  CXXGraph::T_EdgeSet<int> edgeSet;
  edgeSet.insert(&edge);
  CXXGraph::Graph<int> graph(edgeSet);
  auto nodeSet = graph.getNodeSet();
  ASSERT_EQ(nodeSet.size(), 2);
  ASSERT_TRUE(std::find(nodeSet.begin(), nodeSet.end(), &node1) !=
              nodeSet.end());
  ASSERT_TRUE(std::find(nodeSet.begin(), nodeSet.end(), &node2) !=
              nodeSet.end());
}

TEST(GraphTest, GetNodeSet_2) {
  CXXGraph::Node<int> node1("1", 1);
  CXXGraph::Node<int> node2("2", 2);
  CXXGraph::Node<int> node3("3", 3);
  std::pair<const CXXGraph::Node<int> *, const CXXGraph::Node<int> *> pairNode(
      &node1, &node2);
  CXXGraph::Edge<int> edge(1, pairNode);
  CXXGraph::UndirectedEdge<int> edge2(2, node2, node3);
  CXXGraph::T_EdgeSet<int> edgeSet;
  edgeSet.insert(&edge);
  edgeSet.insert(&edge2);
  CXXGraph::Graph<int> graph(edgeSet);
  auto nodeSet = graph.getNodeSet();
  ASSERT_EQ(nodeSet.size(), 3);
  ASSERT_TRUE(std::find(nodeSet.begin(), nodeSet.end(), &node1) !=
              nodeSet.end());
  ASSERT_TRUE(std::find(nodeSet.begin(), nodeSet.end(), &node2) !=
              nodeSet.end());
  ASSERT_TRUE(std::find(nodeSet.begin(), nodeSet.end(), &node3) !=
              nodeSet.end());
}

TEST(GraphTest, adj_print_1) {
  CXXGraph::Node<int> node1("1", 1);
  CXXGraph::Node<int> node2("2", 2);
  std::pair<const CXXGraph::Node<int> *, const CXXGraph::Node<int> *> pairNode(
      &node1, &node2);
  CXXGraph::Edge<int> edge(1, pairNode);
  CXXGraph::T_EdgeSet<int> edgeSet;
  edgeSet.insert(&edge);
  CXXGraph::Graph<int> graph(edgeSet);
  std::cout << "Test Print Adjacency Matrix" << std::endl;
  std::cout << *graph.getAdjMatrix() << std::endl;
}

TEST(GraphTest, adj_print_2) {
  CXXGraph::Node<int> node1("1", 1);
  CXXGraph::Node<int> node2("2", 2);
  std::pair<const CXXGraph::Node<int> *, const CXXGraph::Node<int> *> pairNode(
      &node1, &node2);
  CXXGraph::DirectedEdge<int> edge(1, pairNode);
  CXXGraph::T_EdgeSet<int> edgeSet;
  edgeSet.insert(&edge);
  CXXGraph::Graph<int> graph(edgeSet);
  std::cout << "Test Print Adjacency Matrix" << std::endl;
  std::cout << *graph.getAdjMatrix() << std::endl;
}

TEST(GraphTest, adj_print_3) {
  CXXGraph::Node<int> node1("1", 1);
  CXXGraph::Node<int> node2("2", 2);
  std::pair<const CXXGraph::Node<int> *, const CXXGraph::Node<int> *> pairNode(
      &node1, &node2);
  CXXGraph::UndirectedEdge<int> edge(1, pairNode);
  CXXGraph::T_EdgeSet<int> edgeSet;
  edgeSet.insert(&edge);
  CXXGraph::Graph<int> graph(edgeSet);
  std::cout << "Test Print Adjacency Matrix" << std::endl;
  std::cout << *graph.getAdjMatrix() << std::endl;
}

TEST(GraphTest, adj_print_4) {
  CXXGraph::Node<int> node1("1", 1);
  CXXGraph::Node<int> node2("2", 2);
  CXXGraph::Node<int> node3("3", 3);
  std::pair<const CXXGraph::Node<int> *, const CXXGraph::Node<int> *> pairNode(
      &node1, &node2);
  CXXGraph::UndirectedEdge<int> edge1(1, pairNode);
  CXXGraph::UndirectedEdge<int> edge2(2, node2, node3);
  CXXGraph::UndirectedEdge<int> edge3(3, node1, node3);
  CXXGraph::T_EdgeSet<int> edgeSet;
  edgeSet.insert(&edge1);
  edgeSet.insert(&edge2);
  edgeSet.insert(&edge3);
  CXXGraph::Graph<int> graph(edgeSet);
  std::cout << "Test Print Adjacency Matrix" << std::endl;
  std::cout << *graph.getAdjMatrix() << std::endl;
}

TEST(GraphTest, adj_print_5) {
  CXXGraph::Node<int> node1("1", 1);
  CXXGraph::Node<int> node2("2", 2);
  CXXGraph::Node<int> node3("3", 3);
  std::pair<const CXXGraph::Node<int> *, const CXXGraph::Node<int> *> pairNode(
      &node1, &node2);
  CXXGraph::DirectedEdge<int> edge1(1, pairNode);
  CXXGraph::DirectedEdge<int> edge2(2, node2, node3);
  CXXGraph::DirectedEdge<int> edge3(3, node1, node3);
  CXXGraph::T_EdgeSet<int> edgeSet;
  edgeSet.insert(&edge1);
  edgeSet.insert(&edge2);
  edgeSet.insert(&edge3);
  CXXGraph::Graph<int> graph(edgeSet);
  std::cout << "Test Print Adjacency Matrix" << std::endl;
  std::cout << *graph.getAdjMatrix() << std::endl;
}

TEST(GraphTest, adj_print_6) {
  CXXGraph::Node<int> node1("1", 1);
  CXXGraph::Node<int> node2("2", 2);
  CXXGraph::Node<int> node3("3", 3);
  std::pair<const CXXGraph::Node<int> *, const CXXGraph::Node<int> *> pairNode(
      &node1, &node2);
  CXXGraph::DirectedEdge<int> edge1(1, pairNode);
  CXXGraph::DirectedEdge<int> edge2(2, node2, node3);
  CXXGraph::UndirectedEdge<int> edge3(3, node1, node3);
  CXXGraph::T_EdgeSet<int> edgeSet;
  edgeSet.insert(&edge1);
  edgeSet.insert(&edge2);
  edgeSet.insert(&edge3);
  CXXGraph::Graph<int> graph(edgeSet);
  std::cout << "Test Print Adjacency Matrix" << std::endl;
  std::cout << *graph.getAdjMatrix() << std::endl;
}