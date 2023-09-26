
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

TEST(GraphTest, FindEdge_Test) {
  CXXGraph::Node<int> node1("1", 1);
  CXXGraph::Node<int> node2("2", 2);
  CXXGraph::Node<int> node3("3", 3);
  CXXGraph::Node<int> node4("4", 2);
  CXXGraph::Node<int> node5("5", 3);
  CXXGraph::UndirectedEdge<int> edge(1, node1, node2);
  CXXGraph::UndirectedEdge<int> edge2(2, node2, node3);
  CXXGraph::T_EdgeSet<int> edgeSet;

  /* adding edges to the edgeset */

  edgeSet.insert(make_shared<CXXGraph::UndirectedEdge<int>>(edge));
  edgeSet.insert(make_shared<CXXGraph::UndirectedEdge<int>>(edge2));
  CXXGraph::Graph<int> graph(edgeSet);
  unsigned long edgeId = 0;
  ASSERT_TRUE(graph.findEdge(&node1,&node2,edgeId));
  CXXGraph::UndirectedEdge<int> edge3(3, node1, node3);

  /* adding edge using addEdge() */

  graph.addEdge(make_shared<CXXGraph::UndirectedEdge<int>>(edge3));
  ASSERT_TRUE(graph.findEdge(&node1,&node3,edgeId));
  ASSERT_TRUE(graph.findEdge(&node3,&node1,edgeId));
  CXXGraph::DirectedEdge<int> edge4(4, node1, node5);
  graph.addEdge(make_shared<CXXGraph::DirectedEdge<int>>(edge4));
  ASSERT_TRUE(graph.findEdge(&node1,&node5,edgeId));
  ASSERT_FALSE(graph.findEdge(&node5,&node1,edgeId));

  /* removing edge using removeEdge() */

  graph.removeEdge(2);
  CXXGraph::UndirectedWeightedEdge<int> edge5(7, node4, node5, 5);
  CXXGraph::DirectedWeightedEdge<int> edge6(8, node2, node5, 10);

  /* adding edge using addEdge() */
  
  graph.addEdge(&edge5);
  graph.addEdge(&edge6);
  ASSERT_FALSE(graph.findEdge(&node2,&node3,edgeId));
  ASSERT_FALSE(graph.findEdge(&node3,&node2,edgeId));

  /* Test for empty graph */

  CXXGraph::Graph<int> graph2;
  ASSERT_FALSE(graph2.findEdge(&node2,&node3,edgeId));
}

TEST(GraphTest, RawAddEdge_1) {
  CXXGraph::Node<int> n1("a", 1);
  CXXGraph::Node<int> n2("b", 1);
  CXXGraph::Node<int> n3("c", 1);

  CXXGraph::DirectedEdge<int> e1(0, n1, n2);
  CXXGraph::DirectedEdge<int> e2(1, n2, n3);
  CXXGraph::DirectedEdge<int> e3(2, n3, n1);

  CXXGraph::Graph<int> graph;
  graph.addEdge(&e1);
  graph.addEdge(&e2);
  graph.addEdge(&e3);

  ASSERT_TRUE(graph.isDirectedGraph());
  ASSERT_FALSE(graph.isUndirectedGraph());
}

TEST(GraphTest, RawAddEdge_2) {
  CXXGraph::Node<int> n1("a", 1);
  CXXGraph::Node<int> n2("b", 1);
  CXXGraph::Node<int> n3("c", 1);

  CXXGraph::UndirectedEdge<int> e1(0, n1, n2);
  CXXGraph::UndirectedEdge<int> e2(1, n2, n3);
  CXXGraph::UndirectedEdge<int> e3(2, n3, n1);

  CXXGraph::Graph<int> graph;
  graph.addEdge(&e1);
  graph.addEdge(&e2);
  graph.addEdge(&e3);

  ASSERT_FALSE(graph.isDirectedGraph());
  ASSERT_TRUE(graph.isUndirectedGraph());
}

TEST(GraphTest, RawAddEdge_3) {
  CXXGraph::Node<int> n1("a", 1);
  CXXGraph::Node<int> n2("b", 1);
  CXXGraph::Node<int> n3("c", 1);

  CXXGraph::UndirectedEdge<int> e1(0, n1, n2);
  CXXGraph::DirectedEdge<int> e2(1, n2, n3);
  CXXGraph::UndirectedEdge<int> e3(2, n3, n1);

  CXXGraph::Graph<int> graph;
  graph.addEdge(&e1);
  graph.addEdge(&e2);
  graph.addEdge(&e3);

  ASSERT_FALSE(graph.isDirectedGraph());
  ASSERT_FALSE(graph.isUndirectedGraph());
}

TEST(GraphTest, DirectedEdgeCycle_1) {
  CXXGraph::Node<int> node1("a", 1);
  CXXGraph::Node<int> node2("b", 1);
  CXXGraph::Node<int> node3("c", 1);

  CXXGraph::DirectedEdge<int> edge1(0, node1, node2);
  CXXGraph::DirectedEdge<int> edge2(1, node2, node1);
  CXXGraph::DirectedEdge<int> edge3(2, node3, node1);

  CXXGraph::Graph<int> graph;

  graph.addEdge(&edge1);
  graph.addEdge(&edge2);
  graph.addEdge(&edge3);

  // Check that all of the edges have been added to the graph
  ASSERT_EQ(graph.getEdgeSet().size(), 3);
}

TEST(GraphTest, DirectedEdgeCycle_2) {
  CXXGraph::Node<int> node1("a", 1);
  CXXGraph::Node<int> node2("b", 1);
  CXXGraph::Node<int> node3("c", 1);

  CXXGraph::DirectedEdge<int> edge1(0, node1, node2);
  CXXGraph::DirectedEdge<int> edge2(1, node2, node1);
  CXXGraph::DirectedEdge<int> edge3(2, node3, node1);

  CXXGraph::T_EdgeSet<int> edgeSet;
  edgeSet.insert(make_shared<CXXGraph::DirectedEdge<int>>(edge1));
  edgeSet.insert(make_shared<CXXGraph::DirectedEdge<int>>(edge2));
  edgeSet.insert(make_shared<CXXGraph::DirectedEdge<int>>(edge3));

  CXXGraph::Graph<int> graph(edgeSet);

  // Check that all of the edges have been added to the graph
  ASSERT_EQ(graph.getEdgeSet().size(), 3);
}

TEST(GraphTest, DirectedEdge_hashequality) {
  CXXGraph::Node<int> node1("node1 (0)", 0);
  CXXGraph::Node<int> node2("node2 (1)", 1);
  CXXGraph::Node<int> node3("node3 (2)", 2);
  CXXGraph::Node<int> node4("node4 (3)", 3);
  CXXGraph::Node<int> node5("node5 (4)", 4);
  CXXGraph::Node<int> node6("node6 (5)", 5);
  CXXGraph::Node<int> node7("node7 (6)", 6);

  CXXGraph::DirectedEdge<int> edge1(0, node1, node2);
  CXXGraph::DirectedEdge<int> edge2(1, node2, node3);
  CXXGraph::DirectedEdge<int> edge3(3, node5, node4);
  CXXGraph::DirectedEdge<int> edge4(4, node5, node3);
  CXXGraph::DirectedEdge<int> edge5(5, node5, node2);
  CXXGraph::DirectedEdge<int> edge6(6, node5, node6);
  CXXGraph::DirectedEdge<int> edge7(7, node5, node1);
  CXXGraph::DirectedEdge<int> edge8(8, node5, node7);
  CXXGraph::DirectedEdge<int> edge9(9, node3, node4);
  CXXGraph::DirectedEdge<int> edge10(10, node6, node2);
  CXXGraph::DirectedEdge<int> edge11(11, node7, node2);

  CXXGraph::T_EdgeSet<int> edges;
  auto addEdge = [&](CXXGraph::DirectedEdge<int>& edge)
  {
    size_t currSize = edges.size();
    auto sharedEdge = CXXGraph::make_shared<CXXGraph::DirectedEdge<int>>(edge.getId(), edge.getFrom(), edge.getTo());
    edges.insert(sharedEdge);
    if ((currSize + 1) != edges.size())
    {
      std::cout << "Skipped " << edge.getNodePair().first->getUserId() << " --> " << edge.getNodePair().second->getUserId() << " (hash: " << CXXGraph::edgeHash<int>{}(sharedEdge) << ")" << std::endl;
    } else {
      std::cout << "Added " << edge.getNodePair().first->getUserId() << " --> " << edge.getNodePair().second->getUserId() << " (hash: " << CXXGraph::edgeHash<int>{}(sharedEdge) << ")" << std::endl;
    }
  };

  addEdge(edge1);
  addEdge(edge2);
  addEdge(edge3);
  addEdge(edge4);
  addEdge(edge5);
  addEdge(edge6);
  addEdge(edge7);
  addEdge(edge8);
  addEdge(edge9);
  addEdge(edge10);
  addEdge(edge11);

  CXXGraph::Graph<int> graph;
  graph.setEdgeSet(edges);

  // Check that all of the edges have been added to the graph
  ASSERT_EQ(graph.getEdgeSet().size(), 11);
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

  for (auto x :
       graph.outNeighbors(make_shared<const CXXGraph::Node<int>>(node1))) {
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

  for (auto x :
       graph.inOutNeighbors(make_shared<const CXXGraph::Node<int>>(node1))) {
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
  // Check edges
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
  CXXGraph::Node<int> node2("2", 2);
  CXXGraph::Node<int> node3("3", 3);
  CXXGraph::Edge<int> edge1(1, node1, node2);
  CXXGraph::T_EdgeSet<int> edgeSet;
  edgeSet.insert(make_shared<CXXGraph::Edge<int>>(edge1));
  CXXGraph::Graph<int> graph(edgeSet);
  ASSERT_THROW(graph.reverseDirectedGraph(), std::runtime_error);
  CXXGraph::UndirectedEdge<int> edge2(2, node2, node3);
  CXXGraph::T_EdgeSet<int> undirEdgeSet;
  undirEdgeSet.insert(make_shared<CXXGraph::UndirectedEdge<int>>(edge2));
  CXXGraph::Graph<int> undirGraph(undirEdgeSet);
  ASSERT_THROW(undirGraph.reverseDirectedGraph(), std::runtime_error);
  CXXGraph::DirectedEdge<int> edge3(3, node3, node1);
  CXXGraph::T_EdgeSet<int> mixedEdgeSet;
  mixedEdgeSet.insert(make_shared<CXXGraph::DirectedEdge<int>>(edge3));
  mixedEdgeSet.insert(make_shared<CXXGraph::UndirectedEdge<int>>(edge2));
  CXXGraph::Graph<int> mixedGraph(mixedEdgeSet);
  ASSERT_THROW(mixedGraph.reverseDirectedGraph(), std::runtime_error);
}

TEST(IsolatedNodeGraphTest, Test_AddNode1) {
  CXXGraph::Node<int> node1("1", 1);
  CXXGraph::Node<int> node2("2", 2);
  CXXGraph::Node<int> node3("3", 3);
  CXXGraph::DirectedEdge<int> edge1(1, node1, node2);
  CXXGraph::DirectedEdge<int> edge2(2, node2, node1);
  CXXGraph::DirectedEdge<int> edge3(3, node1, node3);
  CXXGraph::T_EdgeSet<int> edgeSet;
  edgeSet.insert(make_shared<CXXGraph::Edge<int>>(edge1));
  edgeSet.insert(make_shared<CXXGraph::Edge<int>>(edge2));
  edgeSet.insert(make_shared<CXXGraph::Edge<int>>(edge3));
  CXXGraph::Graph<int> graph(edgeSet);

  // Create an isolated node and add it to the graph
  CXXGraph::Node<int> node4("4", 4);
  graph.addNode(make_shared<CXXGraph::Node<int>>(node4));

  // Check that the number of nodes in the graph is 4
  ASSERT_EQ(graph.getNodeSet().size(), 4);
  ASSERT_EQ(graph.getIsolatedNodeSet().size(), 1);
  ASSERT_EQ(graph.getEdgeSet().size(), 3);
}

TEST(IsolatedNodeGraphTest, Test_AddNode2) {
  CXXGraph::Node<int> node1("1", 1);
  CXXGraph::Node<int> node2("2", 2);
  CXXGraph::Node<int> node3("3", 3);
  CXXGraph::DirectedEdge<int> edge1(1, node1, node2);
  CXXGraph::DirectedEdge<int> edge2(2, node2, node1);
  CXXGraph::DirectedEdge<int> edge3(3, node1, node3);
  CXXGraph::T_EdgeSet<int> edgeSet;
  edgeSet.insert(make_shared<CXXGraph::Edge<int>>(edge1));
  edgeSet.insert(make_shared<CXXGraph::Edge<int>>(edge2));
  edgeSet.insert(make_shared<CXXGraph::Edge<int>>(edge3));
  CXXGraph::Graph<int> graph(edgeSet);

  // Create an isolated node and add it to the graph
  CXXGraph::Node<int> node4("4", 4);
  graph.addNode(&node4);

  // Check that the number of nodes in the graph is 4
  ASSERT_EQ(graph.getNodeSet().size(), 4);
  ASSERT_EQ(graph.getIsolatedNodeSet().size(), 1);
  ASSERT_EQ(graph.getEdgeSet().size(), 3);
}

TEST(TestRemoveNode, Test_isolatedNode) {
  CXXGraph::Node<int> node1("1", 1);
  CXXGraph::Node<int> node2("2", 2);
  CXXGraph::Node<int> node3("3", 3);
  CXXGraph::DirectedEdge<int> edge1(1, node1, node2);
  CXXGraph::DirectedEdge<int> edge2(2, node2, node1);
  CXXGraph::DirectedEdge<int> edge3(3, node1, node3);
  CXXGraph::T_EdgeSet<int> edgeSet;
  edgeSet.insert(make_shared<CXXGraph::Edge<int>>(edge1));
  edgeSet.insert(make_shared<CXXGraph::Edge<int>>(edge2));
  edgeSet.insert(make_shared<CXXGraph::Edge<int>>(edge3));
  CXXGraph::Graph<int> graph(edgeSet);

  // Create isolated nodes and add them to the graph
  CXXGraph::Node<int> node4("4", 4);
  CXXGraph::Node<int> node5("5", 5);
  CXXGraph::Node<int> node6("6", 6);
  graph.addNode(make_shared<CXXGraph::Node<int>>(node4));
  graph.addNode(make_shared<CXXGraph::Node<int>>(node5));
  graph.addNode(make_shared<CXXGraph::Node<int>>(node6));

  // Check the initial number of edges and nodes
  ASSERT_EQ(graph.getNodeSet().size(), 6);
  ASSERT_EQ(graph.getIsolatedNodeSet().size(), 3);
  ASSERT_EQ(graph.getEdgeSet().size(), 3);

  // We now remove node 5
  graph.removeNode("5");

  // Check the final number of edges and nodes
  ASSERT_EQ(graph.getNodeSet().size(), 5);
  ASSERT_EQ(graph.getIsolatedNodeSet().size(), 2);
  ASSERT_EQ(graph.getEdgeSet().size(), 3);
}

TEST(TestRemoveNode, Test_connectedNode) {
  CXXGraph::Node<int> node1("1", 1);
  CXXGraph::Node<int> node2("2", 2);
  CXXGraph::Node<int> node3("3", 3);
  CXXGraph::DirectedEdge<int> edge1(1, node1, node2);
  CXXGraph::DirectedEdge<int> edge2(2, node2, node1);
  CXXGraph::DirectedEdge<int> edge3(3, node1, node3);
  CXXGraph::T_EdgeSet<int> edgeSet;
  edgeSet.insert(make_shared<CXXGraph::Edge<int>>(edge1));
  edgeSet.insert(make_shared<CXXGraph::Edge<int>>(edge2));
  edgeSet.insert(make_shared<CXXGraph::Edge<int>>(edge3));
  CXXGraph::Graph<int> graph(edgeSet);

  // Create isolated nodes and add them to the graph
  CXXGraph::Node<int> node4("4", 4);
  CXXGraph::Node<int> node5("5", 5);
  CXXGraph::Node<int> node6("6", 6);
  graph.addNode(make_shared<CXXGraph::Node<int>>(node4));
  graph.addNode(make_shared<CXXGraph::Node<int>>(node5));
  graph.addNode(make_shared<CXXGraph::Node<int>>(node6));

  // Check the initial number of edges and nodes
  ASSERT_EQ(graph.getNodeSet().size(), 6);
  ASSERT_EQ(graph.getIsolatedNodeSet().size(), 3);
  ASSERT_EQ(graph.getEdgeSet().size(), 3);

  // We now remove node 2
  graph.removeNode("2");

  // Check the final number of edges and nodes
  ASSERT_EQ(graph.getNodeSet().size(), 5);
  ASSERT_EQ(graph.getIsolatedNodeSet().size(), 3);
  ASSERT_EQ(graph.getEdgeSet().size(), 1);
}

TEST(TestGetNode, Test_1) {
  CXXGraph::Node<int> node1("1", 1);
  CXXGraph::Node<int> node2("2", 2);
  CXXGraph::Node<int> node3("3", 3);
  CXXGraph::DirectedEdge<int> edge1(1, node1, node2);
  CXXGraph::DirectedEdge<int> edge2(2, node2, node1);
  CXXGraph::DirectedEdge<int> edge3(3, node1, node3);
  CXXGraph::T_EdgeSet<int> edgeSet;
  edgeSet.insert(make_shared<CXXGraph::Edge<int>>(edge1));
  edgeSet.insert(make_shared<CXXGraph::Edge<int>>(edge2));
  edgeSet.insert(make_shared<CXXGraph::Edge<int>>(edge3));
  CXXGraph::Graph<int> graph(edgeSet);

  auto node_found = graph.getNode("2");
  ASSERT_TRUE(node_found.has_value());
  ASSERT_EQ(node_found.value()->getUserId(), "2");

  auto node_notfound = graph.getNode("5");
  ASSERT_FALSE(node_notfound.has_value());
}

TEST(GraphTest, set_data_isolated) {
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

  // Create isolated nodes and add them to the graph
  CXXGraph::Node<int> node4("4", 4);
  CXXGraph::Node<int> node5("5", 5);
  CXXGraph::Node<int> node6("6", 6);
  graph.addNode(make_shared<CXXGraph::Node<int>>(node4));
  graph.addNode(make_shared<CXXGraph::Node<int>>(node5));
  graph.addNode(make_shared<CXXGraph::Node<int>>(node6));

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
