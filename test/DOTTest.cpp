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

TEST(DOTTest, WriteToDotDirectedWeighted) {
  // Generate a simple test graph with few nodes and edges
  CXXGraph::Node<int> node1("1", 1);
  CXXGraph::Node<int> node2("2", 2);
  CXXGraph::Node<int> node3("3", 3);
  std::pair<const CXXGraph::Node<int> *, const CXXGraph::Node<int> *> pairNode(
      &node1, &node2);
  CXXGraph::DirectedWeightedEdge<int> edge1(1, pairNode, 5);
  CXXGraph::DirectedWeightedEdge<int> edge2(2, node2, node3, 3);
  CXXGraph::DirectedWeightedEdge<int> edge3(3, node3, node1, 7);
  CXXGraph::T_EdgeSet<int> edgeSet;
  edgeSet.insert(make_shared<CXXGraph::DirectedWeightedEdge<int>>(edge1));
  edgeSet.insert(make_shared<CXXGraph::DirectedWeightedEdge<int>>(edge2));
  edgeSet.insert(make_shared<CXXGraph::DirectedWeightedEdge<int>>(edge3));
  CXXGraph::Graph<int> graph(edgeSet);

  // Write the graph to a DOT file
  graph.writeToDotFile("./", "example_graph_directed_weighted",
                       "example_graph");
}

TEST(DOTTest, WriteToDotUndirected) {
  // Generate a simple test graph with few nodes and edges
  CXXGraph::Node<int> node1("1", 1);
  CXXGraph::Node<int> node2("2", 2);
  CXXGraph::Node<int> node3("3", 3);
  std::pair<const CXXGraph::Node<int> *, const CXXGraph::Node<int> *> pairNode(
      &node1, &node2);
  CXXGraph::UndirectedEdge<int> edge1(1, pairNode);
  CXXGraph::UndirectedEdge<int> edge2(2, node2, node3);
  CXXGraph::UndirectedEdge<int> edge3(3, node3, node1);
  CXXGraph::T_EdgeSet<int> edgeSet;
  edgeSet.insert(make_shared<CXXGraph::UndirectedEdge<int>>(edge1));
  edgeSet.insert(make_shared<CXXGraph::UndirectedEdge<int>>(edge2));
  edgeSet.insert(make_shared<CXXGraph::UndirectedEdge<int>>(edge3));
  CXXGraph::Graph<int> graph(edgeSet);

  // Write the graph to a DOT file
  graph.writeToDotFile("./", "example_graph_undirected", "example_graph");
}

TEST(DOTTest, WriteToDotMixed) {
  CXXGraph::Node<int> node1("1", 1);
  CXXGraph::Node<int> node2("2", 2);
  CXXGraph::Node<int> node3("3", 3);

  CXXGraph::DirectedWeightedEdge<int> edge1(1, node1, node2, 1);
  CXXGraph::UndirectedWeightedEdge<int> edge2(2, node2, node3, 1);
  CXXGraph::DirectedEdge<int> edge3(3, node1, node3);

  CXXGraph::T_EdgeSet<int> edgeSet;
  edgeSet.insert(make_shared<CXXGraph::DirectedWeightedEdge<int>>(edge1));
  edgeSet.insert(make_shared<CXXGraph::UndirectedWeightedEdge<int>>(edge1));
  edgeSet.insert(make_shared<CXXGraph::DirectedEdge<int>>(edge1));

  CXXGraph::Graph<int> graph(edgeSet);
  graph.writeToDotFile("./", "mixed", "example_graph");
}

TEST(DOTTest, ReadFromDotUndirected) {
  CXXGraph::Graph<int> graph;
  graph.readFromDotFile("../../test", "test_dot_undirected");

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
  CXXGraph::Graph<int> graph;
  graph.readFromDotFile("../../test", "test_dot_weighted");

  // Check that the graph is undirected
  ASSERT_EQ(graph.isDirectedGraph(), false);
  // Check that the number of edges and nodes are correct
  ASSERT_EQ(graph.getEdgeSet().size(), 211);
  ASSERT_EQ(graph.getNodeSet().size(), 30);
  // Check that the first edge is correct
  ASSERT_EQ(graph.getEdge(0).value()->getNodePair().first->getUserId(), "0");
  ASSERT_EQ(graph.getEdge(0).value()->getNodePair().second->getUserId(), "1");
  ASSERT_EQ(dynamic_cast<const CXXGraph::UndirectedWeightedEdge<int> *>(
                graph.getEdge(0).value().get())
                ->getWeight(),
            6);
  ASSERT_EQ(graph.getEdge(0).value()->isDirected(), false);
  ASSERT_EQ(graph.getEdge(0).value()->isWeighted(), true);
  // Check that the last edge is correct
  ASSERT_EQ(graph.getEdge(210).value()->getNodePair().first->getUserId(), "27");
  ASSERT_EQ(graph.getEdge(210).value()->getNodePair().second->getUserId(),
            "28");
  ASSERT_EQ(dynamic_cast<const CXXGraph::UndirectedWeightedEdge<int> *>(
                graph.getEdge(210).value().get())
                ->getWeight(),
            2);
  ASSERT_EQ(graph.getEdge(210).value()->isDirected(), false);
  ASSERT_EQ(graph.getEdge(0).value()->isWeighted(), true);
}

TEST(DOTTest, ReadFromDotDirected) {
  CXXGraph::Graph<int> graph;
  graph.readFromDotFile("../../test", "test_dot_directed");

  // Check that the graph is undirected
  ASSERT_EQ(graph.isDirectedGraph(), true);
  // Check that the number of edges and nodes are correct
  ASSERT_EQ(graph.getEdgeSet().size(), 410);
  ASSERT_EQ(graph.getNodeSet().size(), 30);
  // Check that the first edge is correct
  ASSERT_EQ(graph.getEdge(0).value()->getNodePair().first->getUserId(), "0");
  ASSERT_EQ(graph.getEdge(0).value()->getNodePair().second->getUserId(), "1");
  ASSERT_EQ(dynamic_cast<const CXXGraph::DirectedEdge<int> *>(
                graph.getEdge(0).value().get())
                ->getFrom()
                .getUserId(),
            "0");
  ASSERT_EQ(dynamic_cast<const CXXGraph::DirectedEdge<int> *>(
                graph.getEdge(0).value().get())
                ->getTo()
                .getUserId(),
            "1");
  ASSERT_EQ(graph.getEdge(0).value()->isDirected(), true);
  ASSERT_EQ(graph.getEdge(0).value()->isWeighted(), false);
  // Check that the last edge is correct
  ASSERT_EQ(graph.getEdge(409).value()->getNodePair().first->getUserId(), "29");
  ASSERT_EQ(graph.getEdge(409).value()->getNodePair().second->getUserId(),
            "27");
  ASSERT_EQ(dynamic_cast<const CXXGraph::DirectedEdge<int> *>(
                graph.getEdge(409).value().get())
                ->getFrom()
                .getUserId(),
            "29");
  ASSERT_EQ(dynamic_cast<const CXXGraph::DirectedEdge<int> *>(
                graph.getEdge(409).value().get())
                ->getTo()
                .getUserId(),
            "27");
  ASSERT_EQ(graph.getEdge(409).value()->isDirected(), true);
  ASSERT_EQ(graph.getEdge(409).value()->isWeighted(), false);
}
