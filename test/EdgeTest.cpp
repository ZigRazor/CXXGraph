#include "gtest/gtest.h"
#include "CXXGraph.hpp"

TEST(EdgeTest, Constructor_1)
{
    CXXGRAPH::Node<int> node1("1", 1);
    CXXGRAPH::Node<int> node2("2", 2);
    CXXGRAPH::Edge<int> edge(1, node1, node2);
    ASSERT_EQ(*(edge.getNodePair().first), node1);
    ASSERT_EQ(*(edge.getNodePair().second), node2);
}

TEST(EdgeTest, Constructor_2)
{
    CXXGRAPH::Node<int> node1("1", 1);
    CXXGRAPH::Node<int> node2("2", 2);
    std::pair<const CXXGRAPH::Node<int> *, const CXXGRAPH::Node<int> *> pairNode(&node1, &node2);
    CXXGRAPH::Edge<int> edge(1, pairNode);
    ASSERT_EQ(edge.getNodePair(), pairNode);
    ASSERT_EQ(*(edge.getNodePair().first), node1);
    ASSERT_EQ(*(edge.getNodePair().second), node2);
}

TEST(EdgeTest, print_1)
{
    CXXGRAPH::Node<int> node1("1", 1);
    CXXGRAPH::Node<int> node2("2", 2);
    CXXGRAPH::Edge<int> edge(1, node1, node2);
    std::cout << "Test Print Edge" << std::endl;
    std::cout << edge << std::endl;
}

TEST(EdgeTest, test)
{
    CXXGRAPH::Node<int> node1("1", 1);
    CXXGRAPH::Node<int> node2("2", 2);
    CXXGRAPH::Node<int> node3("3", 3);

    CXXGRAPH::DirectedWeightedEdge<int> edge1(1, node1, node2, 1);
    CXXGRAPH::UndirectedWeightedEdge<int> edge2(2, node2, node3, 1);
    CXXGRAPH::DirectedEdge<int> edge3(3, node1, node3);

    std::set<const CXXGRAPH::Edge<int> *> edgeSet;
    edgeSet.insert(&edge1);
    edgeSet.insert(&edge2);
    edgeSet.insert(&edge3);

    CXXGRAPH::Graph<int> graph;
    graph.setEdgeSet(edgeSet);
    auto adj = graph.getAdjMatrix();
    ASSERT_EQ(adj.size(), 3);
    graph.removeEdge(3);
    adj = graph.getAdjMatrix();
    ASSERT_EQ(adj.size(), 3);

    graph.removeEdge(2);
    adj = graph.getAdjMatrix();
    ASSERT_EQ(adj.size(),1);
    std::cout << adj << std::endl;
}