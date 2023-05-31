#include <Edge/Edge.hpp>
#include <Edge/Weighted.hpp>
#include <Node/Node.hpp>
#include <memory>

#include "CXXGraph.hpp"
#include "gtest/gtest.h"

// Smart pointers alias
template <typename T>
using unique = std::unique_ptr<T>;
template <typename T>
using shared= std::shared_ptr<T>;

using std::make_unique;
using std::make_shared;

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
  edgeSet.insert(make_shared<CXXGraph::DirectedWeightedEdge<int>>(edge1));
  edgeSet.insert(make_shared<CXXGraph::DirectedWeightedEdge<int>>(edge2));
  edgeSet.insert(make_shared<CXXGraph::DirectedWeightedEdge<int>>(edge3));
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
  edgeSet.insert(make_shared<CXXGraph::UndirectedEdge<int>>(edge1));
  edgeSet.insert(make_shared<CXXGraph::UndirectedEdge<int>>(edge2));
  edgeSet.insert(make_shared<CXXGraph::UndirectedEdge<int>>(edge3));
  CXXGraph::Graph<int> graph(edgeSet);

  // Write the graph to a DOT file
  graph.writeToMTXFile(".", "example_graph_undirected", ' ');
}

TEST(MTXTest, WriteToMtxMixed) {
  CXXGraph::Node<int> node1("1", 1);
  CXXGraph::Node<int> node2("2", 2);
  CXXGraph::Node<int> node3("3", 3);

  CXXGraph::DirectedWeightedEdge<int> edge1(1, node1, node2, 1);
  CXXGraph::UndirectedWeightedEdge<int> edge2(2, node2, node3, 1);
  CXXGraph::DirectedEdge<int> edge3(3, node1, node3);

  CXXGraph::T_EdgeSet<int> edgeSet;
  edgeSet.insert(make_shared<CXXGraph::DirectedWeightedEdge<int>>(edge1));
  edgeSet.insert(make_shared<CXXGraph::UndirectedWeightedEdge<int>>(edge2));
  edgeSet.insert(make_shared<CXXGraph::DirectedEdge<int>>(edge3));

  CXXGraph::Graph<int> graph(edgeSet);
  graph.writeToMTXFile(".", "example_graph_mixed", ' ');
}

TEST(MTXTest, ReadFromMtxDirectedWeighted) {
  CXXGraph::Graph<int> graph;
  graph.readFromMTXFile("../../test", "test_mtx");

  // Check the number of edges and nodes
  ASSERT_EQ(graph.getEdgeSet().size(), 8);
  ASSERT_EQ(graph.getNodeSet().size(), 5);

  // Check the first edge
  ASSERT_EQ(graph.getEdge(0).value()->getNodePair().first->getUserId(), "1");
  ASSERT_EQ(graph.getEdge(0).value()->getNodePair().second->getUserId(), "1");
  // Check that it is directed
  ASSERT_EQ(graph.getEdge(0).value()->isDirected(), false);
  // Check that it's weighted and the value of the weight
  ASSERT_EQ(graph.getEdge(0).value()->isWeighted(), true);
  ASSERT_EQ(dynamic_cast<const CXXGraph::Weighted *>(graph.getEdge(0).value().get())
                ->getWeight(),
            1.);

  // Check the last edge
  ASSERT_EQ(graph.getEdge(7).value()->getNodePair().first->getUserId(), "5");
  ASSERT_EQ(graph.getEdge(7).value()->getNodePair().second->getUserId(), "5");
  // Check that it is directed
  ASSERT_EQ(graph.getEdge(7).value()->isDirected(), false);
  // Check that it's weighted and the value of the weight
  ASSERT_EQ(graph.getEdge(7).value()->isWeighted(), true);
  ASSERT_EQ(dynamic_cast<const CXXGraph::Weighted *>(graph.getEdge(7).value().get())
                ->getWeight(),
            12.);

  // Check an edge in the middle
  ASSERT_EQ(graph.getEdge(3).value()->getNodePair().first->getUserId(), "1");
  ASSERT_EQ(graph.getEdge(3).value()->getNodePair().second->getUserId(), "4");
  // Check that it is directed
  ASSERT_EQ(graph.getEdge(3).value()->isDirected(), true);
  // Check that it's weighted and the value of the weight
  ASSERT_EQ(graph.getEdge(3).value()->isWeighted(), true);
  ASSERT_EQ(dynamic_cast<const CXXGraph::Weighted *>(graph.getEdge(3).value().get())
                ->getWeight(),
            6.);
}

TEST(MTXTest, ReadFromMtxUndirectedWeighted) {
  CXXGraph::Graph<int> graph;
  graph.readFromMTXFile("../../test", "test_mtx_symmetric");

  // Check the number of edges and nodes
  ASSERT_EQ(graph.getEdgeSet().size(), 8);
  ASSERT_EQ(graph.getNodeSet().size(), 5);

  // Check the first edge
  ASSERT_EQ(graph.getEdge(0).value()->getNodePair().first->getUserId(), "1");
  ASSERT_EQ(graph.getEdge(0).value()->getNodePair().second->getUserId(), "1");
  // Check that it is directed
  ASSERT_EQ(graph.getEdge(0).value()->isDirected(), false);
  // Check that it's weighted and the value of the weight
  ASSERT_EQ(graph.getEdge(0).value()->isWeighted(), true);
  ASSERT_EQ(dynamic_cast<const CXXGraph::Weighted *>(graph.getEdge(0).value().get())
                ->getWeight(),
            1.);

  // Check the last edge
  ASSERT_EQ(graph.getEdge(7).value()->getNodePair().first->getUserId(), "5");
  ASSERT_EQ(graph.getEdge(7).value()->getNodePair().second->getUserId(), "5");
  // Check that it is directed
  ASSERT_EQ(graph.getEdge(7).value()->isDirected(), false);
  // Check that it's weighted and the value of the weight
  ASSERT_EQ(graph.getEdge(7).value()->isWeighted(), true);
  ASSERT_EQ(dynamic_cast<const CXXGraph::Weighted *>(graph.getEdge(7).value().get())
                ->getWeight(),
            12.);

  // Check an edge in the middle
  ASSERT_EQ(graph.getEdge(3).value()->getNodePair().first->getUserId(), "1");
  ASSERT_EQ(graph.getEdge(3).value()->getNodePair().second->getUserId(), "4");
  // Check that it is directed
  ASSERT_EQ(graph.getEdge(3).value()->isDirected(), false);
  // Check that it's weighted and the value of the weight
  ASSERT_EQ(graph.getEdge(3).value()->isWeighted(), true);
  ASSERT_EQ(dynamic_cast<const CXXGraph::Weighted *>(graph.getEdge(3).value().get())
                ->getWeight(),
            6.);
}
