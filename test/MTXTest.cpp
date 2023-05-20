#include <Edge/Edge.hpp>
#include <Edge/Weighted.hpp>
#include <Node/Node.hpp>

#include "CXXGraph.hpp"
#include "gtest/gtest.h"

TEST(MTXTest, WriteToMtxDirectedWeighted) {
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
  edgeSet.insert(&edge1);
  edgeSet.insert(&edge2);
  edgeSet.insert(&edge3);
  CXXGraph::Graph<int> graph(edgeSet);

  // Write the graph to a DOT file
  graph.writeToMTXFile(".", "example_graph_directed_weighted", ' ');
}

TEST(MTXTest, WriteToMtxUndirected) {
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
  edgeSet.insert(&edge1);
  edgeSet.insert(&edge2);
  edgeSet.insert(&edge3);
  CXXGraph::Graph<int> graph(edgeSet);

  // Write the graph to a DOT file
  graph.writeToMTXFile(".", "example_graph_undirected", ' ');
}

TEST(MRXTest, WriteToMtxMixed) {
  CXXGraph::Node<int> node1("1", 1);
  CXXGraph::Node<int> node2("2", 2);
  CXXGraph::Node<int> node3("3", 3);

  CXXGraph::DirectedWeightedEdge<int> edge1(1, node1, node2, 1);
  CXXGraph::UndirectedWeightedEdge<int> edge2(2, node2, node3, 1);
  CXXGraph::DirectedEdge<int> edge3(3, node1, node3);

  CXXGraph::T_EdgeSet<int> edgeSet;
  edgeSet.insert(&edge1);
  edgeSet.insert(&edge2);
  edgeSet.insert(&edge3);

  CXXGraph::Graph<int> graph(edgeSet);
  graph.writeToMTXFile(".", "example_graph_mixed", ' ');
}

TEST(MTXTest, ReadFromMtxUndirectedWeighted) {
  CXXGraph::Graph<int> graph;
  graph.readFromMTXFile("..", "test_mtx");

  // Check the number of edges and nodes
  ASSERT_EQ(graph.getEdgeSet().size(), 8);
  ASSERT_EQ(graph.getNodeSet().size(), 5);
  
  // Check the first edge
  /* ASSERT_EQ(graph.getEdge(0).value()->getNodePair().first->getUserId(), "1"); */
  /* ASSERT_EQ(graph.getEdge(0).value()->getNodePair().first->getUserId(), "1"); */
  /* // Check that it is directed */
  /* ASSERT_EQ(graph.getEdge(0).value()->isDirected(), true); */
  /* // Check that it's weighted and the value of the weight */
  /* ASSERT_EQ(graph.getEdge(0).value()->isWeighted(), true); */
  /* ASSERT_EQ(dynamic_cast<const CXXGraph::Weighted *>(graph.getEdge(0).value())->getWeight(), 1.); */

  // Check the last edge 
  /* ASSERT_EQ(graph.getEdge(7).value()->getNodePair().first->getUserId(), "5"); */
  /* ASSERT_EQ(graph.getEdge(7).value()->getNodePair().first->getUserId(), "5"); */
  /* // Check that it is directed */
  /* ASSERT_EQ(graph.getEdge(0).value()->isDirected(), true); */
  /* // Check that it's weighted and the value of the weight */
  /* ASSERT_EQ(graph.getEdge(0).value()->isWeighted(), true); */
  /* ASSERT_EQ(dynamic_cast<const CXXGraph::Weighted *>(graph.getEdge(0).value())->getWeight(), 12.); */
}

/* TEST(DOTTest, ReadFromDotDirected) { */
/*   CXXGraph::Graph<int> graph; */
/*   graph.readFromDotFile("../../test", "test_dot_directed"); */

/*   // Check that the graph is undirected */
/*   ASSERT_EQ(graph.isDirectedGraph(), true); */
/*   // Check that the number of edges and nodes are correct */
/*   ASSERT_EQ(graph.getEdgeSet().size(), 410); */
/*   ASSERT_EQ(graph.getNodeSet().size(), 30); */
/*   // Check that the first edge is correct */
/*   ASSERT_EQ(graph.getEdge(0).value()->getNodePair().first->getUserId(), "0"); */
/*   ASSERT_EQ(graph.getEdge(0).value()->getNodePair().second->getUserId(), "1"); */
/*   ASSERT_EQ(dynamic_cast<const CXXGraph::DirectedEdge<int> *>( */
/*                 graph.getEdge(0).value()) */
/*                 ->getFrom() */
/*                 .getUserId(), */
/*             "0"); */
/*   ASSERT_EQ(dynamic_cast<const CXXGraph::DirectedEdge<int> *>( */
/*                 graph.getEdge(0).value()) */
/*                 ->getTo() */
/*                 .getUserId(), */
/*             "1"); */
/*   ASSERT_EQ(graph.getEdge(0).value()->isDirected(), true); */
/*   ASSERT_EQ(graph.getEdge(0).value()->isWeighted(), false); */
/*   // Check that the last edge is correct */
/*   ASSERT_EQ(graph.getEdge(409).value()->getNodePair().first->getUserId(), "29"); */
/*   ASSERT_EQ(graph.getEdge(409).value()->getNodePair().second->getUserId(), */
/*             "27"); */
/*   ASSERT_EQ(dynamic_cast<const CXXGraph::DirectedEdge<int> *>( */
/*                 graph.getEdge(409).value()) */
/*                 ->getFrom() */
/*                 .getUserId(), */
/*             "29"); */
/*   ASSERT_EQ(dynamic_cast<const CXXGraph::DirectedEdge<int> *>( */
/*                 graph.getEdge(409).value()) */
/*                 ->getTo() */
/*                 .getUserId(), */
/*             "27"); */
/*   ASSERT_EQ(graph.getEdge(409).value()->isDirected(), true); */
/*   ASSERT_EQ(graph.getEdge(409).value()->isWeighted(), false); */
/* } */
