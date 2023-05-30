#include "CXXGraph.hpp"
#include "gtest/gtest.h"

TEST(TransitiveReductionTest, reduceEmpty) {
  CXXGraph::T_EdgeSet<int> edgeSet;
  CXXGraph::Graph<int> graph(edgeSet);
  CXXGraph::Graph<int> result = graph.transitiveReduction();

  ASSERT_EQ(result.getEdgeSet().size(), 0);
}

TEST(TransitiveReductionTest, reduceReducedDAG) {
  CXXGraph::Node<int> node1("1", 1);
  CXXGraph::Node<int> node2("2", 2);
  CXXGraph::Node<int> node3("3", 3);
  CXXGraph::Node<int> node4("4", 4);
  CXXGraph::Node<int> node5("5", 5);
  CXXGraph::Node<int> node6("6", 6);
  CXXGraph::Node<int> node7("7", 7);

  CXXGraph::DirectedEdge<int> edge1(1, node1, node2);
  CXXGraph::DirectedEdge<int> edge2(2, node1, node3);
  CXXGraph::DirectedEdge<int> edge3(3, node2, node4);
  CXXGraph::DirectedEdge<int> edge4(4, node3, node4);
  CXXGraph::DirectedEdge<int> edge5(5, node4, node5);
  CXXGraph::DirectedEdge<int> edge6(6, node4, node6);
  CXXGraph::DirectedEdge<int> edge7(7, node4, node7);

  CXXGraph::T_EdgeSet<int> edgeSet;
  edgeSet.insert(&edge1);
  edgeSet.insert(&edge2);
  edgeSet.insert(&edge3);
  edgeSet.insert(&edge4);
  edgeSet.insert(&edge5);
  edgeSet.insert(&edge6);
  edgeSet.insert(&edge7);

  CXXGraph::Graph<int> graph(edgeSet);
  CXXGraph::Graph<int> result = graph.transitiveReduction();

  ASSERT_EQ(result.getEdgeSet(), graph.getEdgeSet());
}

TEST(TransitiveReductionTest, reduceDAG) {
  CXXGraph::Node<int> node1("1", 1);
  CXXGraph::Node<int> node2("2", 2);
  CXXGraph::Node<int> node3("3", 3);
  CXXGraph::Node<int> node4("4", 4);
  CXXGraph::Node<int> node5("5", 5);
  CXXGraph::Node<int> node6("6", 6);
  CXXGraph::Node<int> node7("7", 7);

  CXXGraph::DirectedEdge<int> edge1(1, node1, node2);
  CXXGraph::DirectedEdge<int> edge2(2, node1, node3);
  CXXGraph::DirectedEdge<int> edge3(3, node2, node4);
  CXXGraph::DirectedEdge<int> edge4(4, node3, node4);
  CXXGraph::DirectedEdge<int> edge5(5, node4, node5);
  CXXGraph::DirectedEdge<int> edge6(6, node4, node6);
  CXXGraph::DirectedEdge<int> edge7(7, node4, node7);

  CXXGraph::T_EdgeSet<int> reducedEdgeSet;
  reducedEdgeSet.insert(&edge1);
  reducedEdgeSet.insert(&edge2);
  reducedEdgeSet.insert(&edge3);
  reducedEdgeSet.insert(&edge4);
  reducedEdgeSet.insert(&edge5);
  reducedEdgeSet.insert(&edge6);
  reducedEdgeSet.insert(&edge7);
  CXXGraph::Graph<int> reducedGraph(reducedEdgeSet);

  // Add some more edges that can be reduced
  CXXGraph::T_EdgeSet<int> edgeSet(reducedEdgeSet);
  CXXGraph::DirectedEdge<int> edge8(8, node2, node5);
  CXXGraph::DirectedEdge<int> edge9(9, node1, node4);
  CXXGraph::DirectedEdge<int> edge10(10, node1, node7);
  CXXGraph::DirectedEdge<int> edge11(11, node3, node6);
  edgeSet.insert(&edge8);
  edgeSet.insert(&edge9);
  edgeSet.insert(&edge10);
  edgeSet.insert(&edge11);
  CXXGraph::Graph<int> graph(edgeSet);

  // Perform reduction
  CXXGraph::Graph<int> result = graph.transitiveReduction();

  ASSERT_EQ(reducedGraph.getEdgeSet(), result.getEdgeSet());
}