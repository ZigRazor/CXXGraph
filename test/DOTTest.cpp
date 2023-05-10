#include <Edge/Edge.hpp>
#include <Node/Node.hpp>

#include "CXXGraph.hpp"
#include "gtest/gtest.h"

TEST(DOTTest, WriteToDotDirectedWeighted) {
  // Generate a simple test graph with few nodes and edges
  CXXGRAPH::Node<int> node1("1", 1);
  CXXGRAPH::Node<int> node2("2", 2);
  CXXGRAPH::Node<int> node3("3", 3);
  std::pair<const CXXGRAPH::Node<int> *, const CXXGRAPH::Node<int> *> pairNode(
      &node1, &node2);
  CXXGRAPH::DirectedWeightedEdge<int> edge1(1, pairNode, 5);
  CXXGRAPH::DirectedWeightedEdge<int> edge2(2, node2, node3, 3);
  CXXGRAPH::DirectedWeightedEdge<int> edge3(3, node3, node1, 7);
  CXXGRAPH::T_EdgeSet<int> edgeSet;
  edgeSet.insert(&edge1);
  edgeSet.insert(&edge2);
  edgeSet.insert(&edge3);
  CXXGRAPH::Graph<int> graph(edgeSet);

  // Write the graph to a DOT file
  graph.writeToDotFile("./", "example_graph_directed_weighted",
                       "example_graph");
}

TEST(DOTTest, WriteToDotUndirected) {
  // Generate a simple test graph with few nodes and edges
  CXXGRAPH::Node<int> node1("1", 1);
  CXXGRAPH::Node<int> node2("2", 2);
  CXXGRAPH::Node<int> node3("3", 3);
  std::pair<const CXXGRAPH::Node<int> *, const CXXGRAPH::Node<int> *> pairNode(
      &node1, &node2);
  CXXGRAPH::UndirectedEdge<int> edge1(1, pairNode);
  CXXGRAPH::UndirectedEdge<int> edge2(2, node2, node3);
  CXXGRAPH::UndirectedEdge<int> edge3(3, node3, node1);
  CXXGRAPH::T_EdgeSet<int> edgeSet;
  edgeSet.insert(&edge1);
  edgeSet.insert(&edge2);
  edgeSet.insert(&edge3);
  CXXGRAPH::Graph<int> graph(edgeSet);

  // Write the graph to a DOT file
  graph.writeToDotFile("./", "example_graph_undirected", "example_graph");
}

TEST(DOTTest, WriteToDotMixed) {
  CXXGRAPH::Node<int> node1("1", 1);
  CXXGRAPH::Node<int> node2("2", 2);
  CXXGRAPH::Node<int> node3("3", 3);

  CXXGRAPH::DirectedWeightedEdge<int> edge1(1, node1, node2, 1);
  CXXGRAPH::UndirectedWeightedEdge<int> edge2(2, node2, node3, 1);
  CXXGRAPH::DirectedEdge<int> edge3(3, node1, node3);

  CXXGRAPH::T_EdgeSet<int> edgeSet;
  edgeSet.insert(&edge1);
  edgeSet.insert(&edge2);
  edgeSet.insert(&edge3);

  CXXGRAPH::Graph<int> graph(edgeSet);
  graph.writeToDotFile("./", "mixed", "example_graph");
}

TEST(DOTTest, ReadFromDotUndirected) {
  CXXGRAPH::Graph<int> graph;
  graph.readFromDotFile("..", "test_dot_undirected");

  // Check that the graph is undirected
  ASSERT_EQ(graph.isDirectedGraph(), false);
  // Check that the number of edges and nodes are correct
  ASSERT_EQ(graph.getEdgeSet().size(), 212);
  ASSERT_EQ(graph.getNodeSet().size(), 30);
  // Check that the first edge is correct
  ASSERT_EQ(graph.getEdge(0).value()->getNodePair().first->getUserId(), "0");
  ASSERT_EQ(graph.getEdge(0).value()->getNodePair().second->getUserId(), "4");
  ASSERT_EQ(graph.getEdge(0).value()->isDirected(), false);
  ASSERT_EQ(graph.getEdge(0).value()->isWeighted(), false);
  // Check that the last edge is correct
  ASSERT_EQ(graph.getEdge(211).value()->getNodePair().first->getUserId(), "28");
  ASSERT_EQ(graph.getEdge(211).value()->getNodePair().second->getUserId(),
            "29");
  ASSERT_EQ(graph.getEdge(211).value()->isDirected(), false);
  ASSERT_EQ(graph.getEdge(211).value()->isWeighted(), false);
}

TEST(DOTTest, ReadFromDotUndirectedWeighted) {
  CXXGRAPH::Graph<int> graph;
  graph.readFromDotFile("..", "test_dot_weighted");

  // Check that the graph is undirected
  ASSERT_EQ(graph.isDirectedGraph(), false);
  // Check that the number of edges and nodes are correct
  ASSERT_EQ(graph.getEdgeSet().size(), 211);
  ASSERT_EQ(graph.getNodeSet().size(), 30);
  // Check that the first edge is correct
  ASSERT_EQ(graph.getEdge(0).value()->getNodePair().first->getUserId(), "0");
  ASSERT_EQ(graph.getEdge(0).value()->getNodePair().second->getUserId(), "1");
  ASSERT_EQ(dynamic_cast<const CXXGRAPH::UndirectedWeightedEdge<int> *>(
                graph.getEdge(0).value())
                ->getWeight(),
            6);
  ASSERT_EQ(graph.getEdge(0).value()->isDirected(), false);
  ASSERT_EQ(graph.getEdge(0).value()->isWeighted(), true);
  // Check that the last edge is correct
  ASSERT_EQ(graph.getEdge(210).value()->getNodePair().first->getUserId(), "27");
  ASSERT_EQ(graph.getEdge(210).value()->getNodePair().second->getUserId(),
            "28");
  ASSERT_EQ(dynamic_cast<const CXXGRAPH::UndirectedWeightedEdge<int> *>(
                graph.getEdge(210).value())
                ->getWeight(),
            2);
  ASSERT_EQ(graph.getEdge(210).value()->isDirected(), false);
  ASSERT_EQ(graph.getEdge(0).value()->isWeighted(), true);
}

TEST(DOTTest, ReadFromDotDirected) {
  CXXGRAPH::Graph<int> graph;
  graph.readFromDotFile("..", "test_dot_directed");

  // Check that the graph is undirected
  ASSERT_EQ(graph.isDirectedGraph(), true);
  // Check that the number of edges and nodes are correct
  ASSERT_EQ(graph.getEdgeSet().size(), 410);
  ASSERT_EQ(graph.getNodeSet().size(), 30);
  // Check that the first edge is correct
  ASSERT_EQ(graph.getEdge(0).value()->getNodePair().first->getUserId(), "0");
  ASSERT_EQ(graph.getEdge(0).value()->getNodePair().second->getUserId(), "1");
  ASSERT_EQ(dynamic_cast<const CXXGRAPH::DirectedEdge<int> *>(
                graph.getEdge(0).value())
                ->getFrom()
                .getUserId(),
            "0");
  ASSERT_EQ(dynamic_cast<const CXXGRAPH::DirectedEdge<int> *>(
                graph.getEdge(0).value())
                ->getTo()
                .getUserId(),
            "1");
  ASSERT_EQ(graph.getEdge(0).value()->isDirected(), true);
  ASSERT_EQ(graph.getEdge(0).value()->isWeighted(), false);
  // Check that the last edge is correct
  ASSERT_EQ(graph.getEdge(409).value()->getNodePair().first->getUserId(), "29");
  ASSERT_EQ(graph.getEdge(409).value()->getNodePair().second->getUserId(),
            "27");
  ASSERT_EQ(dynamic_cast<const CXXGRAPH::DirectedEdge<int> *>(
                graph.getEdge(409).value())
                ->getFrom()
                .getUserId(),
            "29");
  ASSERT_EQ(dynamic_cast<const CXXGRAPH::DirectedEdge<int> *>(
                graph.getEdge(409).value())
                ->getTo()
                .getUserId(),
            "27");
  ASSERT_EQ(graph.getEdge(409).value()->isDirected(), true);
  ASSERT_EQ(graph.getEdge(409).value()->isWeighted(), false);
}
