#include "gtest/gtest.h"
#include "Graph.hpp"

TEST(EdgeTest, Constructor_1)
{
    CXXGRAPH::Node<int> node1(1, 1);
    CXXGRAPH::Node<int> node2(2, 2);
    CXXGRAPH::Edge<int> edge(1, node1, node2);
    ASSERT_EQ(*(edge.getNodePair().first), node1);
    ASSERT_EQ(*(edge.getNodePair().second), node2);
}

TEST(EdgeTest, Constructor_2)
{
    CXXGRAPH::Node<int> node1(1, 1);
    CXXGRAPH::Node<int> node2(2, 2);
    std::pair<const CXXGRAPH::Node<int> *, const CXXGRAPH::Node<int> *> pairNode(&node1, &node2);
    CXXGRAPH::Edge<int> edge(1, pairNode);
    ASSERT_EQ(edge.getNodePair(), pairNode);
    ASSERT_EQ(*(edge.getNodePair().first), node1);
    ASSERT_EQ(*(edge.getNodePair().second), node2);
}

TEST(EdgeTest, print_1)
{
    CXXGRAPH::Node<int> node1(1, 1);
    CXXGRAPH::Node<int> node2(2, 2);
    CXXGRAPH::Edge<int> edge(1, node1, node2);
    std::cout << "Test Print Edge" << std::endl;
    std::cout << edge << std::endl;
}