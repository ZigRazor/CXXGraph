
#include <memory>

#include "CXXGraph.hpp"
#include "gtest/gtest.h"

// Smart pointers alias
template <typename T>
using unique = std::unique_ptr<T>;
template <typename T>
using shared = std::shared_ptr<T>;

using std::make_shared;
using std::make_unique;

TEST(GraphTest, Constructor_1) {
  CXXGraph::Node<int> node1("1", 1);
  CXXGraph::Node<int> node2("2", 2);
  std::pair<const CXXGraph::Node<int> *, const CXXGraph::Node<int> *> pairNode(
      &node1, &node2);
  CXXGraph::Edge<int> edge(1, pairNode);
  CXXGraph::T_EdgeSet<int> edgeSet;
  edgeSet.insert(make_shared<CXXGraph::Edge<int>>(edge));
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
  edgeSet.insert(make_shared<CXXGraph::Edge<int>>(edge));
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
  edgeSet.insert(make_shared<CXXGraph::Edge<int>>(edge));
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
  edgeSet.insert(make_shared<CXXGraph::Edge<int>>(edge));
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
  edgeSet.insert(make_shared<CXXGraph::Edge<int>>(edge));
  CXXGraph::Graph<int> graph(edgeSet);
  auto nodeSet = graph.getNodeSet();
  ASSERT_EQ(nodeSet.size(), 2);
  ASSERT_TRUE(std::find_if(nodeSet.begin(), nodeSet.end(), [&node1](auto node) {
                return node->getUserId() == node1.getUserId();
              }) != nodeSet.end());
  ASSERT_TRUE(std::find_if(nodeSet.begin(), nodeSet.end(), [&node2](auto node) {
                return node->getUserId() == node2.getUserId();
              }) != nodeSet.end());
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
  edgeSet.insert(make_shared<CXXGraph::Edge<int>>(edge));
  edgeSet.insert(make_shared<CXXGraph::UndirectedEdge<int>>(edge2));
  CXXGraph::Graph<int> graph(edgeSet);
  auto nodeSet = graph.getNodeSet();
  ASSERT_EQ(nodeSet.size(), 3);
  ASSERT_TRUE(std::find_if(nodeSet.begin(), nodeSet.end(), [&node1](auto node) {
                return node->getUserId() == node1.getUserId();
              }) != nodeSet.end());
  ASSERT_TRUE(std::find_if(nodeSet.begin(), nodeSet.end(), [&node2](auto node) {
                return node->getUserId() == node2.getUserId();
              }) != nodeSet.end());
  ASSERT_TRUE(std::find_if(nodeSet.begin(), nodeSet.end(), [&node3](auto node) {
                return node->getUserId() == node3.getUserId();
              }) != nodeSet.end());
}

TEST(GraphTest, adj_print_1) {
  CXXGraph::Node<int> node1("1", 1);
  CXXGraph::Node<int> node2("2", 2);
  std::pair<const CXXGraph::Node<int> *, const CXXGraph::Node<int> *> pairNode(
      &node1, &node2);
  CXXGraph::Edge<int> edge(1, pairNode);
  CXXGraph::T_EdgeSet<int> edgeSet;
  edgeSet.insert(make_shared<CXXGraph::Edge<int>>(edge));
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
  edgeSet.insert(make_shared<CXXGraph::DirectedEdge<int>>(edge));
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
  edgeSet.insert(make_shared<CXXGraph::UndirectedEdge<int>>(edge));
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
  edgeSet.insert(make_shared<CXXGraph::UndirectedEdge<int>>(edge1));
  edgeSet.insert(make_shared<CXXGraph::UndirectedEdge<int>>(edge2));
  edgeSet.insert(make_shared<CXXGraph::UndirectedEdge<int>>(edge3));
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
  edgeSet.insert(make_shared<CXXGraph::DirectedEdge<int>>(edge1));
  edgeSet.insert(make_shared<CXXGraph::DirectedEdge<int>>(edge2));
  edgeSet.insert(make_shared<CXXGraph::DirectedEdge<int>>(edge3));
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
  edgeSet.insert(make_shared<CXXGraph::DirectedEdge<int>>(edge1));
  edgeSet.insert(make_shared<CXXGraph::DirectedEdge<int>>(edge2));
  edgeSet.insert(make_shared<CXXGraph::UndirectedEdge<int>>(edge3));
  CXXGraph::Graph<int> graph(edgeSet);
  std::cout << "Test Print Adjacency Matrix" << std::endl;
  std::cout << *graph.getAdjMatrix() << std::endl;
}

TEST(GraphTest, set_data) {
  // Create the graph
  CXXGraph::Node<int> node1("1", 1);
  CXXGraph::Node<int> node2("2", 2);
  CXXGraph::Node<int> node3("3", 3);
  std::pair<const CXXGraph::Node<int> *, const CXXGraph::Node<int> *> pairNode(
      &node1, &node2);
  CXXGraph::DirectedEdge<int> edge1(1, pairNode);
  CXXGraph::DirectedEdge<int> edge2(2, node2, node3);
  CXXGraph::UndirectedEdge<int> edge3(3, node1, node3);
  CXXGraph::T_EdgeSet<int> edgeSet;
  edgeSet.insert(make_shared<CXXGraph::DirectedEdge<int>>(edge1));
  edgeSet.insert(make_shared<CXXGraph::DirectedEdge<int>>(edge2));
  edgeSet.insert(make_shared<CXXGraph::UndirectedEdge<int>>(edge3));
  CXXGraph::Graph<int> graph(edgeSet);

  std::map<std::string, int> initial_values;
  // Construct map with the initial values of the nodes data
  for (const auto &nodeIt : graph.getNodeSet()) {
    initial_values[nodeIt->getUserId()] = nodeIt->getData();
  }
  // Change the data contained in the nodes singularly
  std::map<std::string, int> new_values;
  for (const auto &nodeIt : graph.getNodeSet()) {
    int r = std::rand();
    graph.setNodeData(nodeIt->getUserId(), r);
    new_values[nodeIt->getUserId()] = r;
  }
  // Check the final values of the node data
  for (const auto &nodeIt : graph.getNodeSet()) {
    ASSERT_EQ(nodeIt->getData(), new_values[nodeIt->getUserId()]);
  }

  // Now set the data of all the nodes at once
  std::map<std::string, int> data_values;
  for (const auto &nodeIt : graph.getNodeSet()) {
    int r = std::rand();
    data_values[nodeIt->getUserId()] = r;
  }
  graph.setNodeData(data_values);
  for (const auto &nodeIt : graph.getNodeSet()) {
    ASSERT_EQ(nodeIt->getData(), data_values[nodeIt->getUserId()]);
  }
}

TEST(GraphTest, test_outEdges) {
  CXXGraph::Node<int> node1("1", 1);
  CXXGraph::Node<int> node2("2", 2);
  CXXGraph::Node<int> node3("3", 3);
  CXXGraph::Node<int> node4("4", 4);
  CXXGraph::Node<int> node5("5", 5);
  CXXGraph::Node<int> node6("6", 6);
  CXXGraph::Node<int> node7("7", 7);
  CXXGraph::Node<int> node8("8", 8);
  CXXGraph::DirectedEdge<int> edge1(1, node1, node2);
  CXXGraph::DirectedEdge<int> edge2(2, node1, node3);
  CXXGraph::DirectedEdge<int> edge3(3, node2, node4);
  CXXGraph::DirectedEdge<int> edge4(4, node2, node5);
  CXXGraph::DirectedEdge<int> edge5(5, node3, node4);
  CXXGraph::DirectedEdge<int> edge6(6, node3, node5);
  CXXGraph::DirectedEdge<int> edge7(7, node4, node6);
  CXXGraph::DirectedEdge<int> edge8(8, node4, node7);
  CXXGraph::DirectedEdge<int> edge9(7, node5, node6);
  CXXGraph::DirectedEdge<int> edge10(8, node5, node7);
  CXXGraph::DirectedEdge<int> edge11(8, node6, node8);
  CXXGraph::DirectedEdge<int> edge12(8, node7, node8);
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
  CXXGraph::Graph<int> graph(edgeSet);

  // Check node 1
  for (auto x : graph.outNeighbors(&node1)) {
    ASSERT_TRUE(x == make_shared<const CXXGraph::Node<int>>(node2) ||
                x == make_shared<const CXXGraph::Node<int>>(node3));
  }
  // Check node 2
  for (auto x : graph.outNeighbors(&node2)) {
    ASSERT_TRUE(x == make_shared<const CXXGraph::Node<int>>(node4) ||
                x == make_shared<const CXXGraph::Node<int>>(node5));
    ASSERT_FALSE(x == make_shared<const CXXGraph::Node<int>>(node1));
  }
  // Check node 5
  for (auto x : graph.outNeighbors(&node5)) {
    ASSERT_TRUE(x == make_shared<const CXXGraph::Node<int>>(node6) ||
                x == make_shared<const CXXGraph::Node<int>>(node7));
    ASSERT_FALSE(x == make_shared<const CXXGraph::Node<int>>(node2));
    ASSERT_FALSE(x == make_shared<const CXXGraph::Node<int>>(node3));
  }
  // Check that node 8 does not have any neighbors
  ASSERT_EQ(graph.outNeighbors(&node8).size(), 0);
}

// Test the overload that takes shared_ptr as input
TEST(GraphTest, test_outEdges_shared) {
  CXXGraph::Node<int> node1("1", 1);
  CXXGraph::Node<int> node2("2", 2);
  CXXGraph::Node<int> node3("3", 3);
  CXXGraph::Node<int> node4("4", 4);
  CXXGraph::Node<int> node5("5", 5);
  CXXGraph::Node<int> node6("6", 6);
  CXXGraph::Node<int> node7("7", 7);
  CXXGraph::Node<int> node8("8", 8);
  CXXGraph::DirectedEdge<int> edge1(1, node1, node2);
  CXXGraph::DirectedEdge<int> edge2(2, node1, node3);
  CXXGraph::DirectedEdge<int> edge3(3, node2, node4);
  CXXGraph::DirectedEdge<int> edge4(4, node2, node5);
  CXXGraph::DirectedEdge<int> edge5(5, node3, node4);
  CXXGraph::DirectedEdge<int> edge6(6, node3, node5);
  CXXGraph::DirectedEdge<int> edge7(7, node4, node6);
  CXXGraph::DirectedEdge<int> edge8(8, node4, node7);
  CXXGraph::DirectedEdge<int> edge9(7, node5, node6);
  CXXGraph::DirectedEdge<int> edge10(8, node5, node7);
  CXXGraph::DirectedEdge<int> edge11(8, node6, node8);
  CXXGraph::DirectedEdge<int> edge12(8, node7, node8);
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
  CXXGraph::Graph<int> graph(edgeSet);

  for (auto x : graph.outNeighbors(make_shared<const CXXGraph::Node<int>>(node1))) {
    ASSERT_TRUE(x == make_shared<const CXXGraph::Node<int>>(node2) ||
                x == make_shared<const CXXGraph::Node<int>>(node3));
  }

  auto node2_shared = make_shared<const CXXGraph::Node<int>>(node2);
  for (auto x : graph.outNeighbors(node2_shared)) {
    ASSERT_TRUE(x == make_shared<const CXXGraph::Node<int>>(node4) ||
                x == make_shared<const CXXGraph::Node<int>>(node5));
    ASSERT_FALSE(x == make_shared<const CXXGraph::Node<int>>(node1));
  }
}

TEST(GraphTest, test_inOutEdges) {
  CXXGraph::Node<int> node1("1", 1);
  CXXGraph::Node<int> node2("2", 2);
  CXXGraph::Node<int> node3("3", 3);
  CXXGraph::Node<int> node4("4", 4);
  CXXGraph::Node<int> node5("5", 5);
  CXXGraph::Node<int> node6("6", 6);
  CXXGraph::Node<int> node7("7", 7);
  CXXGraph::Node<int> node8("8", 8);
  CXXGraph::UndirectedEdge<int> edge1(1, node1, node2);
  CXXGraph::UndirectedEdge<int> edge2(2, node1, node3);
  CXXGraph::UndirectedEdge<int> edge3(3, node2, node3);
  CXXGraph::UndirectedEdge<int> edge4(4, node2, node4);
  CXXGraph::UndirectedEdge<int> edge5(5, node4, node5);
  CXXGraph::UndirectedEdge<int> edge6(6, node4, node6);
  CXXGraph::UndirectedEdge<int> edge7(7, node6, node7);
  CXXGraph::UndirectedEdge<int> edge8(8, node6, node8);
  CXXGraph::T_EdgeSet<int> edgeSet;
  edgeSet.insert(make_shared<CXXGraph::UndirectedEdge<int>>(edge1));
  edgeSet.insert(make_shared<CXXGraph::UndirectedEdge<int>>(edge2));
  edgeSet.insert(make_shared<CXXGraph::UndirectedEdge<int>>(edge3));
  edgeSet.insert(make_shared<CXXGraph::UndirectedEdge<int>>(edge4));
  edgeSet.insert(make_shared<CXXGraph::UndirectedEdge<int>>(edge5));
  edgeSet.insert(make_shared<CXXGraph::UndirectedEdge<int>>(edge6));
  edgeSet.insert(make_shared<CXXGraph::UndirectedEdge<int>>(edge7));
  edgeSet.insert(make_shared<CXXGraph::UndirectedEdge<int>>(edge8));
  CXXGraph::Graph<int> graph(edgeSet);

  // Check node 1
  for (auto x : graph.inOutNeighbors(&node1)) {
    ASSERT_TRUE(x == make_shared<const CXXGraph::Node<int>>(node2) ||
                x == make_shared<const CXXGraph::Node<int>>(node3));
  }
  // Check node 4
  for (auto x : graph.inOutNeighbors(&node4)) {
    ASSERT_TRUE(x == make_shared<const CXXGraph::Node<int>>(node2) ||
                x == make_shared<const CXXGraph::Node<int>>(node3) ||
                x == make_shared<const CXXGraph::Node<int>>(node5) ||
                x == make_shared<const CXXGraph::Node<int>>(node6));
  }
  // Check node 7
  for (auto x : graph.inOutNeighbors(&node7)) {
    ASSERT_TRUE(x == make_shared<const CXXGraph::Node<int>>(node6));
  }
}

// Test the overload that takes shared_ptr as input
TEST(GraphTest, test_inOutEdges_shared) {
  CXXGraph::Node<int> node1("1", 1);
  CXXGraph::Node<int> node2("2", 2);
  CXXGraph::Node<int> node3("3", 3);
  CXXGraph::Node<int> node4("4", 4);
  CXXGraph::Node<int> node5("5", 5);
  CXXGraph::Node<int> node6("6", 6);
  CXXGraph::Node<int> node7("7", 7);
  CXXGraph::Node<int> node8("8", 8);
  CXXGraph::UndirectedEdge<int> edge1(1, node1, node2);
  CXXGraph::UndirectedEdge<int> edge2(2, node1, node3);
  CXXGraph::UndirectedEdge<int> edge3(3, node2, node3);
  CXXGraph::UndirectedEdge<int> edge4(4, node2, node4);
  CXXGraph::UndirectedEdge<int> edge5(5, node4, node5);
  CXXGraph::UndirectedEdge<int> edge6(6, node4, node6);
  CXXGraph::UndirectedEdge<int> edge7(7, node6, node7);
  CXXGraph::UndirectedEdge<int> edge8(8, node6, node8);
  CXXGraph::T_EdgeSet<int> edgeSet;
  edgeSet.insert(make_shared<CXXGraph::UndirectedEdge<int>>(edge1));
  edgeSet.insert(make_shared<CXXGraph::UndirectedEdge<int>>(edge2));
  edgeSet.insert(make_shared<CXXGraph::UndirectedEdge<int>>(edge3));
  edgeSet.insert(make_shared<CXXGraph::UndirectedEdge<int>>(edge4));
  edgeSet.insert(make_shared<CXXGraph::UndirectedEdge<int>>(edge5));
  edgeSet.insert(make_shared<CXXGraph::UndirectedEdge<int>>(edge6));
  edgeSet.insert(make_shared<CXXGraph::UndirectedEdge<int>>(edge7));
  edgeSet.insert(make_shared<CXXGraph::UndirectedEdge<int>>(edge8));
  CXXGraph::Graph<int> graph(edgeSet);

  for (auto x : graph.inOutNeighbors(make_shared<const CXXGraph::Node<int>>(node1))) {
    ASSERT_TRUE(x == make_shared<const CXXGraph::Node<int>>(node2) ||
                x == make_shared<const CXXGraph::Node<int>>(node3));
  }

  auto node7_shared = make_shared<const CXXGraph::Node<int>>(node7);
  for (auto x : graph.inOutNeighbors(node7_shared)) {
    ASSERT_TRUE(x == make_shared<const CXXGraph::Node<int>>(node6));
  }
}

TEST(ReverseDirectedGraphTest, test_function) {
  CXXGraph::Node<int> node1("1", 1);
  CXXGraph::Node<int> node2("2", 2);
  CXXGraph::Node<int> node3("3", 3);
  CXXGraph::DirectedEdge<int> edge1(1, node1, node2);
  CXXGraph::DirectedEdge<int> edge2(2, node1, node3);
  CXXGraph::DirectedEdge<int> edge3(3, node2, node3);
  CXXGraph::T_EdgeSet<int> edgeSet;
  edgeSet.insert(make_shared<CXXGraph::DirectedEdge<int>>(edge1));
  edgeSet.insert(make_shared<CXXGraph::DirectedEdge<int>>(edge2));
  edgeSet.insert(make_shared<CXXGraph::DirectedEdge<int>>(edge3));
  CXXGraph::Graph<int> graph(edgeSet);
  CXXGraph::Graph<int> reverseGraph(edgeSet);
  reverseGraph.reverseDirectedGraph();
  // Check that the reverse graph has the same nodes as the original one
  ASSERT_EQ(graph.getNodeSet(), reverseGraph.getNodeSet());
  // Check that the reverse graph has the same edges as the original one
  auto originalSet = graph.getEdgeSet();
  auto reverseSet = reverseGraph.getEdgeSet();
  for (auto originalEdge: originalSet) {
    for (auto reverseEdge : reverseSet) {
      if (originalEdge->getId() == reverseEdge->getId()) {
        ASSERT_TRUE(originalEdge->getNodePair().first->getUserId() == reverseEdge->getNodePair().second->getUserId() &&
                    originalEdge->getNodePair().second->getUserId() == reverseEdge->getNodePair().first->getUserId());
      }
    }
  }
}

TEST(ReverseDirectedGraphTest, test_exception) {
  CXXGraph::Node<int> node1("1", 1);
  CXXGraph::DirectedEdge<int> edge1(1, node1, node1);
  CXXGraph::T_EdgeSet<int> edgeSet;
  edgeSet.insert(make_shared<CXXGraph::DirectedEdge<int>>(edge1));
  CXXGraph::Graph<int> graph(edgeSet);
  ASSERT_THROW(graph.reverseDirectedGraph(), std::runtime_error);
}