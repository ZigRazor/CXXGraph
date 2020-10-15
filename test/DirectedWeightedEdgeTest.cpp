#include "gtest/gtest.h"
#include "Graph.hpp"

TEST(DirectedWeightedEdgeTest, Constructor_1)
{
    CXXGRAPH::Node<int> node1(1, 1);
    CXXGRAPH::Node<int> node2(2, 2);
    CXXGRAPH::DirectedWeightedEdge<int> edge(1, node1, node2,10);
    ASSERT_EQ(*(edge.getNodePair().first), node1);
    ASSERT_EQ(*(edge.getNodePair().second), node2);
    ASSERT_EQ(edge.getWeight(), 10);
}

TEST(DirectedWeightedEdgeTest, Constructor_2)
{
    CXXGRAPH::Node<int> node1(1, 1);
    CXXGRAPH::Node<int> node2(2, 2);
    std::pair<const CXXGRAPH::Node<int> *, const CXXGRAPH::Node<int> *> pairNode(&node1, &node2);
    CXXGRAPH::DirectedWeightedEdge<int> edge(1, pairNode,10);
    ASSERT_EQ(edge.getNodePair(), pairNode);
    ASSERT_EQ(*(edge.getNodePair().first), node1);
    ASSERT_EQ(*(edge.getNodePair().second), node2);
    ASSERT_EQ(edge.getWeight(), 10);
}

TEST(DirectedWeightedEdgeTest, Constructor_3)
{
    CXXGRAPH::Node<int> node1(1, 1);
    CXXGRAPH::Node<int> node2(2, 2);
    std::pair<const CXXGRAPH::Node<int> *, const CXXGRAPH::Node<int> *> pairNode(&node1, &node2);
    CXXGRAPH::DirectedWeightedEdge<int> edge(1, pairNode,10);
    ASSERT_TRUE(edge.isDirected().value());
}

TEST(DirectedWeightedEdgeTest, Constructor_4)
{
    CXXGRAPH::Node<int> node1(1, 1);
    CXXGRAPH::Node<int> node2(2, 2);
    std::pair<const CXXGRAPH::Node<int> *, const CXXGRAPH::Node<int> *> pairNode(&node1, &node2);
    CXXGRAPH::DirectedWeightedEdge<int> edge(1, pairNode,10);
    ASSERT_TRUE(edge.isWeighted().value());
}

TEST(DirectedWeightedEdgeTest, Constructor_5)
{
    CXXGRAPH::Node<int> node1(1, 1);
    CXXGRAPH::Node<int> node2(2, 2);
    std::pair<const CXXGRAPH::Node<int> *, const CXXGRAPH::Node<int> *> pairNode(&node1, &node2);
    CXXGRAPH::Edge<int> base_edge(1, pairNode);
    CXXGRAPH::DirectedWeightedEdge<int> edge(base_edge,10);
    ASSERT_EQ(edge.getNodePair(), pairNode);
    ASSERT_EQ(*(edge.getNodePair().first), node1);
    ASSERT_EQ(*(edge.getNodePair().second), node2);
    ASSERT_TRUE(edge.isDirected().value());
    ASSERT_TRUE(edge.isWeighted().value());
    ASSERT_EQ(edge.getWeight(), 10);
}

TEST(DirectedWeightedEdgeTest, Constructor_6)
{
    CXXGRAPH::Node<int> node1(1, 1);
    CXXGRAPH::Node<int> node2(2, 2);
    std::pair<const CXXGRAPH::Node<int> *, const CXXGRAPH::Node<int> *> pairNode(&node1, &node2);
    CXXGRAPH::Edge<int> base_edge(1, pairNode);
    CXXGRAPH::DirectedWeightedEdge<int> edge(base_edge);
    ASSERT_EQ(edge.getNodePair(), pairNode);
    ASSERT_EQ(*(edge.getNodePair().first), node1);
    ASSERT_EQ(*(edge.getNodePair().second), node2);
    ASSERT_TRUE(edge.isDirected().value());
    ASSERT_TRUE(edge.isWeighted().value());
    ASSERT_EQ(edge.getWeight(), 0.0);
}

TEST(DirectedWeightedEdgeTest, Constructor_7)
{
    CXXGRAPH::Node<int> node1(1, 1);
    CXXGRAPH::Node<int> node2(2, 2);
    std::pair<const CXXGRAPH::Node<int> *, const CXXGRAPH::Node<int> *> pairNode(&node1, &node2);
    CXXGRAPH::DirectedEdge<int> base_edge(1, pairNode);
    CXXGRAPH::DirectedWeightedEdge<int> edge(base_edge);
    ASSERT_EQ(edge.getNodePair(), pairNode);
    ASSERT_EQ(*(edge.getNodePair().first), node1);
    ASSERT_EQ(*(edge.getNodePair().second), node2);
    ASSERT_TRUE(edge.isDirected().value());
    ASSERT_TRUE(edge.isWeighted().value());
    ASSERT_EQ(edge.getWeight(), 0.0);
}

TEST(DirectedWeightedEdgeTest, Cast_1)
{
    CXXGRAPH::Node<int> node1(1, 1);
    CXXGRAPH::Node<int> node2(2, 2);
    std::pair<const CXXGRAPH::Node<int> *, const CXXGRAPH::Node<int> *> pairNode(&node1, &node2);
    CXXGRAPH::Edge<int> base_edge(1, pairNode);
    CXXGRAPH::DirectedWeightedEdge<int> edge = base_edge;
    ASSERT_EQ(edge.getNodePair(), pairNode);
    ASSERT_EQ(*(edge.getNodePair().first), node1);
    ASSERT_EQ(*(edge.getNodePair().second), node2);
    ASSERT_TRUE(edge.isDirected().value());
    ASSERT_TRUE(edge.isWeighted().value());
    ASSERT_EQ(edge.getWeight(), 0.0);
}

TEST(DirectedWeightedEdgeTest, Cast_2)
{
    CXXGRAPH::Node<int> node1(1, 1);
    CXXGRAPH::Node<int> node2(2, 2);
    std::pair<const CXXGRAPH::Node<int> *, const CXXGRAPH::Node<int> *> pairNode(&node1, &node2);
    CXXGRAPH::UndirectedEdge<int> base_edge(1, pairNode);
    CXXGRAPH::DirectedWeightedEdge<int> edge = base_edge;
    ASSERT_FALSE(base_edge.isDirected().value());
    ASSERT_EQ(edge.getNodePair(), pairNode);
    ASSERT_EQ(*(edge.getNodePair().first), node1);
    ASSERT_EQ(*(edge.getNodePair().second), node2);
    ASSERT_TRUE(edge.isDirected().value());
    ASSERT_TRUE(edge.isWeighted().value());
    ASSERT_EQ(edge.getWeight(), 0.0);
}

TEST(DirectedWeightedEdgeTest, Cast_3)
{
    CXXGRAPH::Node<int> node1(1, 1);
    CXXGRAPH::Node<int> node2(2, 2);
    std::pair<const CXXGRAPH::Node<int> *, const CXXGRAPH::Node<int> *> pairNode(&node1, &node2);
    CXXGRAPH::DirectedEdge<int> base_edge(1, pairNode);
    CXXGRAPH::DirectedWeightedEdge<int> edge = base_edge;
    ASSERT_TRUE(base_edge.isDirected().value());
    ASSERT_EQ(edge.getNodePair(), pairNode);
    ASSERT_EQ(*(edge.getNodePair().first), node1);
    ASSERT_EQ(*(edge.getNodePair().second), node2);
    ASSERT_TRUE(edge.isDirected().value());
    ASSERT_TRUE(edge.isWeighted().value());
    ASSERT_EQ(edge.getWeight(), 0.0);
}

TEST(DirectedWeightedEdgeTest, Cast_4)
{
    CXXGRAPH::Node<int> node1(1, 1);
    CXXGRAPH::Node<int> node2(2, 2);
    std::pair<const CXXGRAPH::Node<int> *, const CXXGRAPH::Node<int> *> pairNode(&node1, &node2);
    CXXGRAPH::UndirectedWeightedEdge<int> base_edge(1, pairNode,10);
    CXXGRAPH::DirectedWeightedEdge<int> edge = base_edge;
    ASSERT_FALSE(base_edge.isDirected().value());
    ASSERT_TRUE(base_edge.isWeighted().value());
    ASSERT_EQ(edge.getNodePair(), pairNode);
    ASSERT_EQ(*(edge.getNodePair().first), node1);
    ASSERT_EQ(*(edge.getNodePair().second), node2);
    ASSERT_TRUE(edge.isDirected().value());
    ASSERT_TRUE(edge.isWeighted().value());
    ASSERT_EQ(edge.getWeight(), 10);
}

TEST(DirectedWeightedEdgeTest, print_1)
{
    CXXGRAPH::Node<int> node1(1, 1);
    CXXGRAPH::Node<int> node2(2, 2);
    CXXGRAPH::DirectedWeightedEdge<int> edge(1, node1, node2,10);
    std::cout << "Test Print DirectedWeightedEdge" << std::endl;
    std::cout << edge << std::endl;
}
