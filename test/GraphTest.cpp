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
  ASSERT_TRUE(std::find_if(nodeSet.begin(), nodeSet.end(), [&node1](auto node){
		  return node->getUserId() == node1.getUserId();
		}) !=
              nodeSet.end());
  ASSERT_TRUE(std::find_if(nodeSet.begin(), nodeSet.end(), [&node2](auto node){
		  return node->getUserId() == node2.getUserId();
		}) !=
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
  edgeSet.insert(make_shared<CXXGraph::Edge<int>>(edge));
  edgeSet.insert(make_shared<CXXGraph::UndirectedEdge<int>>(edge2));
  CXXGraph::Graph<int> graph(edgeSet);
  auto nodeSet = graph.getNodeSet();
  ASSERT_EQ(nodeSet.size(), 3);
  ASSERT_TRUE(std::find_if(nodeSet.begin(), nodeSet.end(), [&node1](auto node){
		  return node->getUserId() == node1.getUserId();
		}) !=
              nodeSet.end());
  ASSERT_TRUE(std::find_if(nodeSet.begin(), nodeSet.end(), [&node2](auto node){
		  return node->getUserId() == node2.getUserId();
		}) !=
              nodeSet.end());
  ASSERT_TRUE(std::find_if(nodeSet.begin(), nodeSet.end(), [&node3](auto node){
		  return node->getUserId() == node3.getUserId();
		}) !=
              nodeSet.end());
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
  for (const auto& nodeIt : graph.getNodeSet()) {
	initial_values[nodeIt->getUserId()] = nodeIt->getData();
  }
  // Change the data contained in the nodes singularly
  std::map<std::string, int> new_values;
  for (const auto& nodeIt : graph.getNodeSet()) {
	int r = std::rand();
	graph.setNodeData(nodeIt->getUserId(), r);
	new_values[nodeIt->getUserId()] = r;	
  }
  // Check the final values of the node data
  for (const auto& nodeIt : graph.getNodeSet()) {
	ASSERT_EQ(nodeIt->getData(), new_values[nodeIt->getUserId()]);
  }

  // Now set the data of all the nodes at once
  std::map<std::string, int> data_values;
  for (const auto& nodeIt : graph.getNodeSet()) {
	int r = std::rand();
	data_values[nodeIt->getUserId()] = r;	
  }
  graph.setNodeData(data_values);
  for (const auto& nodeIt : graph.getNodeSet()) {
	ASSERT_EQ(nodeIt->getData(), data_values[nodeIt->getUserId()]);
  }
}
