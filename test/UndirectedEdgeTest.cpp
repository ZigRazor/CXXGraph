#include "gtest/gtest.h"
#include "CXXGraph.hpp"

TEST(UndirectedEdgeTest, Constructor_1)
{
    CXXGRAPH::Node<int> node1("1", 1);
    CXXGRAPH::Node<int> node2("2", 2);
    CXXGRAPH::UndirectedEdge<int> edge(1, node1, node2);
    ASSERT_EQ(*(edge.getNodePair().first), node1);
    ASSERT_EQ(*(edge.getNodePair().second), node2);
}

TEST(UndirectedEdgeTest, Constructor_2)
{
    CXXGRAPH::Node<int> node1("1", 1);
    CXXGRAPH::Node<int> node2("2", 2);
    std::pair<const CXXGRAPH::Node<int> *, const CXXGRAPH::Node<int> *> pairNode(&node1, &node2);
    CXXGRAPH::UndirectedEdge<int> edge(1, pairNode);
    ASSERT_EQ(edge.getNodePair(), pairNode);
    ASSERT_EQ(*(edge.getNodePair().first), node1);
    ASSERT_EQ(*(edge.getNodePair().second), node2);
}

TEST(UndirectedEdgeTest, Constructor_3)
{
    CXXGRAPH::Node<int> node1("1", 1);
    CXXGRAPH::Node<int> node2("2", 2);
    std::pair<const CXXGRAPH::Node<int> *, const CXXGRAPH::Node<int> *> pairNode(&node1, &node2);
    CXXGRAPH::UndirectedEdge<int> edge(1, pairNode);
    ASSERT_FALSE(edge.isDirected().value());
}

TEST(UndirectedEdgeTest, Constructor_4)
{
    CXXGRAPH::Node<int> node1("1", 1);
    CXXGRAPH::Node<int> node2("2", 2);
    std::pair<const CXXGRAPH::Node<int> *, const CXXGRAPH::Node<int> *> pairNode(&node1, &node2);
    CXXGRAPH::UndirectedEdge<int> edge(1, pairNode);
    ASSERT_FALSE(edge.isWeighted().value());
}

TEST(UndirectedEdgeTest, Constructor_5)
{
    CXXGRAPH::Node<int> node1("1", 1);
    CXXGRAPH::Node<int> node2("2", 2);
    std::pair<const CXXGRAPH::Node<int> *, const CXXGRAPH::Node<int> *> pairNode(&node1, &node2);
    CXXGRAPH::Edge<int> base_edge(1, pairNode);
    CXXGRAPH::UndirectedEdge<int> edge(base_edge);
    ASSERT_EQ(edge.getNodePair(), pairNode);
    ASSERT_EQ(*(edge.getNodePair().first), node1);
    ASSERT_EQ(*(edge.getNodePair().second), node2);
    ASSERT_FALSE(edge.isDirected().value());
    ASSERT_FALSE(edge.isWeighted().value());
}

TEST(UndirectedEdgeTest, Cast_1)
{
    CXXGRAPH::Node<int> node1("1", 1);
    CXXGRAPH::Node<int> node2("2", 2);
    std::pair<const CXXGRAPH::Node<int> *, const CXXGRAPH::Node<int> *> pairNode(&node1, &node2);
    CXXGRAPH::Edge<int> base_edge(1, pairNode);
    CXXGRAPH::UndirectedEdge<int> edge = base_edge;
    ASSERT_EQ(edge.getNodePair(), pairNode);
    ASSERT_EQ(*(edge.getNodePair().first), node1);
    ASSERT_EQ(*(edge.getNodePair().second), node2);
    ASSERT_FALSE(edge.isDirected().value());
    ASSERT_FALSE(edge.isWeighted().value());
}

TEST(UndirectedEdgeTest, Cast_2)
{
    CXXGRAPH::Node<int> node1("1", 1);
    CXXGRAPH::Node<int> node2("2", 2);
    std::pair<const CXXGRAPH::Node<int> *, const CXXGRAPH::Node<int> *> pairNode(&node1, &node2);
    CXXGRAPH::DirectedEdge<int> base_edge(1, pairNode);
    CXXGRAPH::UndirectedEdge<int> edge = base_edge;
    ASSERT_TRUE(base_edge.isDirected().value());
    ASSERT_EQ(edge.getNodePair(), pairNode);
    ASSERT_EQ(*(edge.getNodePair().first), node1);
    ASSERT_EQ(*(edge.getNodePair().second), node2);
    ASSERT_FALSE(edge.isDirected().value());
    ASSERT_FALSE(edge.isWeighted().value());
}

TEST(UndirectedEdgeTest, print_1)
{
    CXXGRAPH::Node<int> node1("1", 1);
    CXXGRAPH::Node<int> node2("2", 2);
    CXXGRAPH::UndirectedEdge<int> edge(1, node1, node2);
    std::cout << "Test Print UndirectedEdge" << std::endl;
    std::cout << edge << std::endl;
}