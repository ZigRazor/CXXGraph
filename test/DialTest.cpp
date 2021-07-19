#include "gtest/gtest.h"
#include "Graph.hpp"

TEST(DialTest, test_1)
{
    CXXGRAPH::Node<int> node1(1, 1);
    CXXGRAPH::Node<int> node2(2, 2);
    CXXGRAPH::Node<int> node3(3, 3);
    std::pair<const CXXGRAPH::Node<int> *, const CXXGRAPH::Node<int> *> pairNode(&node1, &node2);
    CXXGRAPH::DirectedWeightedEdge<int> edge1(1, pairNode, 1);
    CXXGRAPH::DirectedWeightedEdge<int> edge2(2, node2, node3, 1);
    CXXGRAPH::UndirectedWeightedEdge<int> edge3(3, node1, node3, 6);
    std::list<const CXXGRAPH::Edge<int> *> edgeSet;
    edgeSet.push_back(&edge1);
    edgeSet.push_back(&edge2);
    edgeSet.push_back(&edge3);
    CXXGRAPH::Graph<int> graph(edgeSet);
    auto res = graph.dial(node1, 6);
    ASSERT_TRUE(res.success);
    ASSERT_EQ(res.errorMessage, "");
    ASSERT_EQ(res.minDistanceMap.at(1), 0);
    ASSERT_EQ(res.minDistanceMap.at(2), 1);
    ASSERT_EQ(res.minDistanceMap.at(3), 2);
}

TEST(DialTest, test_2)
{
    CXXGRAPH::Node<int> node1(1, 1);
    CXXGRAPH::Node<int> node2(2, 2);
    CXXGRAPH::Node<int> node3(3, 3);
    std::pair<const CXXGRAPH::Node<int> *, const CXXGRAPH::Node<int> *> pairNode(&node1, &node2);
    CXXGRAPH::DirectedWeightedEdge<int> edge1(1, pairNode, 5);
    CXXGRAPH::DirectedWeightedEdge<int> edge2(2, node2, node3, 4);
    CXXGRAPH::UndirectedWeightedEdge<int> edge3(3, node1, node3, 6);
    std::list<const CXXGRAPH::Edge<int> *> edgeSet;
    edgeSet.push_back(&edge1);
    edgeSet.push_back(&edge2);
    edgeSet.push_back(&edge3);
    CXXGRAPH::Graph<int> graph(edgeSet);
    auto res = graph.dial(node1, 6);
    ;
    ASSERT_TRUE(res.success);
    ASSERT_EQ(res.errorMessage, "");
    ASSERT_EQ(res.minDistanceMap.at(1), 0);
    ASSERT_EQ(res.minDistanceMap.at(2), 5);
    ASSERT_EQ(res.minDistanceMap.at(3), 6);
}

TEST(DialTest, test_3)
{
    CXXGRAPH::Node<int> node1(1, 1);
    CXXGRAPH::Node<int> node2(2, 2);
    CXXGRAPH::Node<int> node3(3, 3);
    std::pair<const CXXGRAPH::Node<int> *, const CXXGRAPH::Node<int> *> pairNode(&node1, &node2);
    CXXGRAPH::DirectedWeightedEdge<int> edge1(1, pairNode, 5);
    CXXGRAPH::DirectedEdge<int> edge2(2, node2, node3);
    CXXGRAPH::UndirectedWeightedEdge<int> edge3(3, node1, node3, 6);
    std::list<const CXXGRAPH::Edge<int> *> edgeSet;
    edgeSet.push_back(&edge1);
    edgeSet.push_back(&edge2);
    edgeSet.push_back(&edge3);
    CXXGRAPH::Graph<int> graph(edgeSet);
    auto res = graph.dial(node1, 6);
    ASSERT_FALSE(res.success);
    ASSERT_EQ(res.errorMessage, CXXGRAPH::ERR_NO_WEIGHTED_EDGE);
    ASSERT_TRUE(res.minDistanceMap.empty());
}

TEST(DialTest, test_4)
{
    CXXGRAPH::Node<int> node1(1, 1);
    CXXGRAPH::Node<int> node2(2, 2);
    CXXGRAPH::Node<int> node3(3, 3);
    CXXGRAPH::DirectedEdge<int> edge2(2, node2, node3);
    CXXGRAPH::UndirectedWeightedEdge<int> edge3(3, node1, node3, 6);
    std::list<const CXXGRAPH::Edge<int> *> edgeSet;
    edgeSet.push_back(&edge2);
    edgeSet.push_back(&edge3);
    CXXGRAPH::Graph<int> graph(edgeSet);
    auto res = graph.dial(node1, 6);
    ASSERT_TRUE(res.success);
    ASSERT_EQ(res.errorMessage, "");
    ASSERT_EQ(res.minDistanceMap.at(1), 0);
    ASSERT_EQ(res.minDistanceMap.at(2), std::numeric_limits<long>::max());
    ASSERT_EQ(res.minDistanceMap.at(3), 6);
}

TEST(DialTest, test_5)
{
    CXXGRAPH::Node<int> node1(1, 1);
    CXXGRAPH::Node<int> node2(2, 2);
    CXXGRAPH::Node<int> node3(3, 3);
    CXXGRAPH::Node<int> node4(4, 4);
    CXXGRAPH::DirectedEdge<int> edge2(2, node2, node3);
    CXXGRAPH::UndirectedWeightedEdge<int> edge3(3, node1, node3, 6);
    std::list<const CXXGRAPH::Edge<int> *> edgeSet;
    edgeSet.push_back(&edge2);
    edgeSet.push_back(&edge3);
    CXXGRAPH::Graph<int> graph(edgeSet);
    auto res = graph.dial(node4, 6);
    ASSERT_FALSE(res.success);
    ASSERT_EQ(res.errorMessage, CXXGRAPH::ERR_SOURCE_NODE_NOT_IN_GRAPH);
    ASSERT_TRUE(res.minDistanceMap.empty());
}