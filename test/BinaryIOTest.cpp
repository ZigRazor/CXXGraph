#include <memory>
#include <string>

#include "CXXGraph/CXXGraph.hpp"
#include "gtest/gtest.h"

// Smart pointers alias
template <typename T>
using unique = std::unique_ptr<T>;
template <typename T>
using shared = std::shared_ptr<T>;

using std::make_shared;
using std::make_unique;

TEST(BinaryIOTest, WriteToBinaryDirectedWeighted) {
  // Generate a simple test graph with few nodes and edges
  CXXGraph::Node<int> node1("1", 1);
  CXXGraph::Node<int> node2("2", 2);
  CXXGraph::Node<int> node3("3", 3);
  std::pair<const CXXGraph::Node<int> *, const CXXGraph::Node<int> *> pairNode(
      &node1, &node2);
  CXXGraph::DirectedWeightedEdge<int> edge1("1", pairNode, 5);
  CXXGraph::DirectedWeightedEdge<int> edge2("2", node2, node3, 3);
  CXXGraph::DirectedWeightedEdge<int> edge3("3", node3, node1, 7);
  CXXGraph::T_EdgeSet<int> edgeSet;
  edgeSet.insert(make_shared<CXXGraph::DirectedWeightedEdge<int>>(edge1));
  edgeSet.insert(make_shared<CXXGraph::DirectedWeightedEdge<int>>(edge2));
  edgeSet.insert(make_shared<CXXGraph::DirectedWeightedEdge<int>>(edge3));
  CXXGraph::Graph<int> graph(edgeSet);

  // Write the graph to a binary file
  int result = graph.writeToBinaryFile("./", "example_graph_directed_weighted",
                                       false, true);
  ASSERT_EQ(result, 0);
}

TEST(BinaryIOTest, WriteToBinaryUndirected) {
  // Generate a simple test graph with few nodes and edges
  CXXGraph::Node<int> node1("1", 1);
  CXXGraph::Node<int> node2("2", 2);
  CXXGraph::Node<int> node3("3", 3);
  std::pair<const CXXGraph::Node<int> *, const CXXGraph::Node<int> *> pairNode(
      &node1, &node2);
  CXXGraph::UndirectedEdge<int> edge1("1", pairNode);
  CXXGraph::UndirectedEdge<int> edge2("2", node2, node3);
  CXXGraph::UndirectedEdge<int> edge3("3", node3, node1);
  CXXGraph::T_EdgeSet<int> edgeSet;
  edgeSet.insert(make_shared<CXXGraph::UndirectedEdge<int>>(edge1));
  edgeSet.insert(make_shared<CXXGraph::UndirectedEdge<int>>(edge2));
  edgeSet.insert(make_shared<CXXGraph::UndirectedEdge<int>>(edge3));
  CXXGraph::Graph<int> graph(edgeSet);

  // Write the graph to a binary file
  int result =
      graph.writeToBinaryFile("./", "example_graph_undirected", false, false);
  ASSERT_EQ(result, 0);
}

TEST(BinaryIOTest, WriteToBinaryWithNodeFeatures) {
  // Generate a simple test graph with node features
  CXXGraph::Node<int> node1("1", 10);
  CXXGraph::Node<int> node2("2", 20);
  CXXGraph::Node<int> node3("3", 30);

  CXXGraph::DirectedWeightedEdge<int> edge1("1", node1, node2, 5);
  CXXGraph::DirectedWeightedEdge<int> edge2("2", node2, node3, 3);

  CXXGraph::T_EdgeSet<int> edgeSet;
  edgeSet.insert(make_shared<CXXGraph::DirectedWeightedEdge<int>>(edge1));
  edgeSet.insert(make_shared<CXXGraph::DirectedWeightedEdge<int>>(edge2));
  CXXGraph::Graph<int> graph(edgeSet);

  // Write the graph with node features to a binary file
  int result =
      graph.writeToBinaryFile("./", "example_graph_with_features", true, true);
  ASSERT_EQ(result, 0);
}

TEST(BinaryIOTest, WriteToBinaryMixed) {
  CXXGraph::Node<int> node1("1", 1);
  CXXGraph::Node<int> node2("2", 2);
  CXXGraph::Node<int> node3("3", 3);

  CXXGraph::DirectedWeightedEdge<int> edge1("1", node1, node2, 5.5);
  CXXGraph::UndirectedWeightedEdge<int> edge2("2", node2, node3, 3.2);
  CXXGraph::DirectedEdge<int> edge3("3", node1, node3);

  CXXGraph::T_EdgeSet<int> edgeSet;
  edgeSet.insert(make_shared<CXXGraph::DirectedWeightedEdge<int>>(edge1));
  edgeSet.insert(make_shared<CXXGraph::UndirectedWeightedEdge<int>>(edge2));
  edgeSet.insert(make_shared<CXXGraph::DirectedEdge<int>>(edge3));

  CXXGraph::Graph<int> graph(edgeSet);
  int result = graph.writeToBinaryFile("./", "mixed", false, true);
  ASSERT_EQ(result, 0);
}

TEST(BinaryIOTest, ReadFromBinaryDirectedWeighted) {
  // First, write a graph to a binary file
  CXXGraph::Node<int> node1("1", 1);
  CXXGraph::Node<int> node2("2", 2);
  CXXGraph::Node<int> node3("3", 3);
  CXXGraph::DirectedWeightedEdge<int> edge1("1", node1, node2, 5);
  CXXGraph::DirectedWeightedEdge<int> edge2("2", node2, node3, 3);
  CXXGraph::DirectedWeightedEdge<int> edge3("3", node3, node1, 7);
  CXXGraph::T_EdgeSet<int> edgeSet;
  edgeSet.insert(make_shared<CXXGraph::DirectedWeightedEdge<int>>(edge1));
  edgeSet.insert(make_shared<CXXGraph::DirectedWeightedEdge<int>>(edge2));
  edgeSet.insert(make_shared<CXXGraph::DirectedWeightedEdge<int>>(edge3));
  CXXGraph::Graph<int> writeGraph(edgeSet);
  writeGraph.writeToBinaryFile("./", "test_binary_directed_weighted", false,
                               true);

  // Now read it back
  CXXGraph::Graph<int> readGraph;
  int result = readGraph.readFromBinaryFile(
      "./", "test_binary_directed_weighted", false, true);
  ASSERT_EQ(result, 0);

  // Verify the graph structure
  ASSERT_EQ(readGraph.getEdgeSet().size(), 3);
  ASSERT_EQ(readGraph.getNodeSet().size(), 3);
  ASSERT_EQ(readGraph.isDirectedGraph(), true);

  // Check edge 1
  auto edge1Read = readGraph.getEdge("1");
  ASSERT_TRUE(edge1Read.has_value());
  ASSERT_EQ(edge1Read.value()->getNodePair().first->getUserId(), "1");
  ASSERT_EQ(edge1Read.value()->getNodePair().second->getUserId(), "2");
  ASSERT_EQ(edge1Read.value()->isDirected(), true);
  ASSERT_EQ(edge1Read.value()->isWeighted(), true);
  ASSERT_EQ(dynamic_cast<const CXXGraph::DirectedWeightedEdge<int> *>(
                edge1Read.value().get())
                ->getWeight(),
            5);

  // Check edge 2
  auto edge2Read = readGraph.getEdge("2");
  ASSERT_TRUE(edge2Read.has_value());
  ASSERT_EQ(edge2Read.value()->getNodePair().first->getUserId(), "2");
  ASSERT_EQ(edge2Read.value()->getNodePair().second->getUserId(), "3");
  ASSERT_EQ(dynamic_cast<const CXXGraph::DirectedWeightedEdge<int> *>(
                edge2Read.value().get())
                ->getWeight(),
            3);
}

TEST(BinaryIOTest, ReadFromBinaryUndirected) {
  // First, write a graph to a binary file
  CXXGraph::Node<int> node1("1", 1);
  CXXGraph::Node<int> node2("2", 2);
  CXXGraph::Node<int> node3("3", 3);
  CXXGraph::UndirectedEdge<int> edge1("1", node1, node2);
  CXXGraph::UndirectedEdge<int> edge2("2", node2, node3);
  CXXGraph::UndirectedEdge<int> edge3("3", node3, node1);
  CXXGraph::T_EdgeSet<int> edgeSet;
  edgeSet.insert(make_shared<CXXGraph::UndirectedEdge<int>>(edge1));
  edgeSet.insert(make_shared<CXXGraph::UndirectedEdge<int>>(edge2));
  edgeSet.insert(make_shared<CXXGraph::UndirectedEdge<int>>(edge3));
  CXXGraph::Graph<int> writeGraph(edgeSet);
  writeGraph.writeToBinaryFile("./", "test_binary_undirected", false, false);

  // Now read it back
  CXXGraph::Graph<int> readGraph;
  int result = readGraph.readFromBinaryFile("./", "test_binary_undirected",
                                            false, false);
  ASSERT_EQ(result, 0);

  // Verify the graph structure
  ASSERT_EQ(readGraph.getEdgeSet().size(), 3);
  ASSERT_EQ(readGraph.getNodeSet().size(), 3);
  ASSERT_EQ(readGraph.isDirectedGraph(), false);

  // Check edges
  auto edge1Read = readGraph.getEdge("1");
  ASSERT_TRUE(edge1Read.has_value());
  ASSERT_EQ(edge1Read.value()->getNodePair().first->getUserId(), "1");
  ASSERT_EQ(edge1Read.value()->getNodePair().second->getUserId(), "2");
  ASSERT_EQ(edge1Read.value()->isDirected(), false);
  ASSERT_EQ(edge1Read.value()->isWeighted(), false);
}

TEST(BinaryIOTest, ReadFromBinaryWithNodeFeatures) {
  // First, write a graph with node features
  CXXGraph::Node<int> node1("1", 10);
  CXXGraph::Node<int> node2("2", 20);
  CXXGraph::Node<int> node3("3", 30);
  CXXGraph::DirectedWeightedEdge<int> edge1("1", node1, node2, 5);
  CXXGraph::DirectedWeightedEdge<int> edge2("2", node2, node3, 3);
  CXXGraph::T_EdgeSet<int> edgeSet;
  edgeSet.insert(make_shared<CXXGraph::DirectedWeightedEdge<int>>(edge1));
  edgeSet.insert(make_shared<CXXGraph::DirectedWeightedEdge<int>>(edge2));
  CXXGraph::Graph<int> writeGraph(edgeSet);
  writeGraph.writeToBinaryFile("./", "test_binary_with_features", true, true);

  // Now read it back
  CXXGraph::Graph<int> readGraph;
  int result = readGraph.readFromBinaryFile("./", "test_binary_with_features",
                                            true, true);
  ASSERT_EQ(result, 0);

  // Verify the graph structure
  ASSERT_EQ(readGraph.getEdgeSet().size(), 2);
  ASSERT_EQ(readGraph.getNodeSet().size(), 3);

  // Verify node features (for trivially copyable type int)
  auto nodeSet = readGraph.getNodeSet();
  bool foundNode1 = false, foundNode2 = false, foundNode3 = false;
  for (const auto &node : nodeSet) {
    if (node->getUserId() == "1") {
      ASSERT_EQ(node->getData(), 10);
      foundNode1 = true;
    } else if (node->getUserId() == "2") {
      ASSERT_EQ(node->getData(), 20);
      foundNode2 = true;
    } else if (node->getUserId() == "3") {
      ASSERT_EQ(node->getData(), 30);
      foundNode3 = true;
    }
  }
  ASSERT_TRUE(foundNode1);
  ASSERT_TRUE(foundNode2);
  ASSERT_TRUE(foundNode3);
}

TEST(BinaryIOTest, ReadFromBinaryMixed) {
  // First, write a mixed graph
  CXXGraph::Node<int> node1("1", 1);
  CXXGraph::Node<int> node2("2", 2);
  CXXGraph::Node<int> node3("3", 3);
  CXXGraph::DirectedWeightedEdge<int> edge1("1", node1, node2, 5.5);
  CXXGraph::UndirectedWeightedEdge<int> edge2("2", node2, node3, 3.2);
  CXXGraph::DirectedEdge<int> edge3("3", node1, node3);
  CXXGraph::T_EdgeSet<int> edgeSet;
  edgeSet.insert(make_shared<CXXGraph::DirectedWeightedEdge<int>>(edge1));
  edgeSet.insert(make_shared<CXXGraph::UndirectedWeightedEdge<int>>(edge2));
  edgeSet.insert(make_shared<CXXGraph::DirectedEdge<int>>(edge3));
  CXXGraph::Graph<int> writeGraph(edgeSet);
  writeGraph.writeToBinaryFile("./", "test_binary_mixed", false, true);

  // Now read it back
  CXXGraph::Graph<int> readGraph;
  int result =
      readGraph.readFromBinaryFile("./", "test_binary_mixed", false, true);
  ASSERT_EQ(result, 0);

  // Verify the graph structure
  ASSERT_EQ(readGraph.getEdgeSet().size(), 3);
  ASSERT_EQ(readGraph.getNodeSet().size(), 3);

  // Check directed weighted edge
  auto edge1Read = readGraph.getEdge("1");
  ASSERT_TRUE(edge1Read.has_value());
  ASSERT_EQ(edge1Read.value()->isDirected(), true);
  ASSERT_EQ(edge1Read.value()->isWeighted(), true);
  ASSERT_DOUBLE_EQ(dynamic_cast<const CXXGraph::DirectedWeightedEdge<int> *>(
                       edge1Read.value().get())
                       ->getWeight(),
                   5.5);

  // Check undirected weighted edge
  auto edge2Read = readGraph.getEdge("2");
  ASSERT_TRUE(edge2Read.has_value());
  ASSERT_EQ(edge2Read.value()->isDirected(), false);
  ASSERT_EQ(edge2Read.value()->isWeighted(), true);
  ASSERT_DOUBLE_EQ(dynamic_cast<const CXXGraph::UndirectedWeightedEdge<int> *>(
                       edge2Read.value().get())
                       ->getWeight(),
                   3.2);

  // Check directed unweighted edge
  auto edge3Read = readGraph.getEdge("3");
  ASSERT_TRUE(edge3Read.has_value());
  ASSERT_EQ(edge3Read.value()->isDirected(), true);
  ASSERT_EQ(edge3Read.value()->isWeighted(), false);
}

TEST(BinaryIOTest, ReadWriteRoundTrip) {
  // Create a complex graph
  CXXGraph::Node<int> node1("A", 100);
  CXXGraph::Node<int> node2("B", 200);
  CXXGraph::Node<int> node3("C", 300);
  CXXGraph::Node<int> node4("D", 400);

  CXXGraph::DirectedWeightedEdge<int> edge1("e1", node1, node2, 1.5);
  CXXGraph::DirectedWeightedEdge<int> edge2("e2", node2, node3, 2.5);
  CXXGraph::UndirectedWeightedEdge<int> edge3("e3", node3, node4, 3.5);
  CXXGraph::DirectedEdge<int> edge4("e4", node4, node1);
  CXXGraph::UndirectedEdge<int> edge5("e5", node1, node3);

  CXXGraph::T_EdgeSet<int> edgeSet;
  edgeSet.insert(make_shared<CXXGraph::DirectedWeightedEdge<int>>(edge1));
  edgeSet.insert(make_shared<CXXGraph::DirectedWeightedEdge<int>>(edge2));
  edgeSet.insert(make_shared<CXXGraph::UndirectedWeightedEdge<int>>(edge3));
  edgeSet.insert(make_shared<CXXGraph::DirectedEdge<int>>(edge4));
  edgeSet.insert(make_shared<CXXGraph::UndirectedEdge<int>>(edge5));

  CXXGraph::Graph<int> originalGraph(edgeSet);

  // Write with node features and edge weights
  originalGraph.writeToBinaryFile("./", "test_roundtrip", true, true);

  // Read it back
  CXXGraph::Graph<int> restoredGraph;
  restoredGraph.readFromBinaryFile("./", "test_roundtrip", true, true);

  // Verify everything matches
  ASSERT_EQ(restoredGraph.getEdgeSet().size(),
            originalGraph.getEdgeSet().size());
  ASSERT_EQ(restoredGraph.getNodeSet().size(),
            originalGraph.getNodeSet().size());

  // Verify all edges are preserved
  ASSERT_TRUE(restoredGraph.getEdge("e1").has_value());
  ASSERT_TRUE(restoredGraph.getEdge("e2").has_value());
  ASSERT_TRUE(restoredGraph.getEdge("e3").has_value());
  ASSERT_TRUE(restoredGraph.getEdge("e4").has_value());
  ASSERT_TRUE(restoredGraph.getEdge("e5").has_value());
}

TEST(BinaryIOTest, InvalidFilePath) {
  CXXGraph::Graph<int> graph;
  int result = graph.readFromBinaryFile("/invalid/path", "nonexistent");
  ASSERT_EQ(result, -1);  // File not found error
}

TEST(BinaryIOTest, EmptyGraph) {
  CXXGraph::T_EdgeSet<int> emptyEdgeSet;
  CXXGraph::Graph<int> emptyGraph(emptyEdgeSet);

  int writeResult =
      emptyGraph.writeToBinaryFile("./", "empty_graph", false, false);
  ASSERT_EQ(writeResult, 0);

  CXXGraph::Graph<int> readGraph;
  int readResult =
      readGraph.readFromBinaryFile("./", "empty_graph", false, false);
  ASSERT_EQ(readResult, 0);
  ASSERT_EQ(readGraph.getEdgeSet().size(), 0);
  ASSERT_EQ(readGraph.getNodeSet().size(), 0);
}

TEST(BinaryIOTest, LargeGraph) {
  // Create a larger graph to test performance
  CXXGraph::T_EdgeSet<int> edgeSet;

  for (int i = 0; i < 100; ++i) {
    for (int j = i + 1; j < 100; ++j) {
      if ((i * j) % 7 == 0) {  // Create some edges based on a pattern
        CXXGraph::Node<int> nodeI(std::to_string(i), i);
        CXXGraph::Node<int> nodeJ(std::to_string(j), j);
        std::string edgeId = std::to_string(i) + "_" + std::to_string(j);

        if (i % 2 == 0) {
          edgeSet.insert(make_shared<CXXGraph::DirectedWeightedEdge<int>>(
              edgeId, nodeI, nodeJ, static_cast<double>(i + j)));
        } else {
          edgeSet.insert(make_shared<CXXGraph::UndirectedWeightedEdge<int>>(
              edgeId, nodeI, nodeJ, static_cast<double>(i * j)));
        }
      }
    }
  }

  CXXGraph::Graph<int> largeGraph(edgeSet);

  int writeResult =
      largeGraph.writeToBinaryFile("./", "large_graph", true, true);
  ASSERT_EQ(writeResult, 0);

  CXXGraph::Graph<int> readGraph;
  int readResult =
      readGraph.readFromBinaryFile("./", "large_graph", true, true);
  ASSERT_EQ(readResult, 0);
  ASSERT_EQ(readGraph.getEdgeSet().size(), largeGraph.getEdgeSet().size());
  ASSERT_EQ(readGraph.getNodeSet().size(), largeGraph.getNodeSet().size());
}