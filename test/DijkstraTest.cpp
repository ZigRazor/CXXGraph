#include "gtest/gtest.h"
#include "Graph.hpp"

TEST(DijkstraTest, test_1)
{
    CXXGRAPH::Node<int> node1(1, 1);
    CXXGRAPH::Node<int> node2(2, 2);
    CXXGRAPH::Node<int> node3(3, 3);
    std::pair<const CXXGRAPH::Node<int> *, const CXXGRAPH::Node<int> *> pairNode(&node1, &node2);
    CXXGRAPH::DirectedWeightedEdge<int> edge1(1, pairNode,1);
    CXXGRAPH::DirectedWeightedEdge<int> edge2(2, node2, node3,1);
    CXXGRAPH::UndirectedWeightedEdge<int> edge3(3, node1, node3,6);
    std::set<const CXXGRAPH::Edge<int> *> edgeSet;
    edgeSet.insert(&edge1);
    edgeSet.insert(&edge2);
    edgeSet.insert(&edge3);
    CXXGRAPH::Graph<int> graph(edgeSet);
    CXXGRAPH::DijkstraResult  res= graph.dijkstra(node1,node3);
    ASSERT_TRUE(res.success);
    ASSERT_EQ(res.errorMessage, "");
    ASSERT_EQ(res.result, 2);

}


TEST(DijkstraTest, test_2)
{
    CXXGRAPH::Node<int> node1(1, 1);
    CXXGRAPH::Node<int> node2(2, 2);
    CXXGRAPH::Node<int> node3(3, 3);
    std::pair<const CXXGRAPH::Node<int> *, const CXXGRAPH::Node<int> *> pairNode(&node1, &node2);
    CXXGRAPH::DirectedWeightedEdge<int> edge1(1, pairNode,5);
    CXXGRAPH::DirectedWeightedEdge<int> edge2(2, node2, node3,4);
    CXXGRAPH::UndirectedWeightedEdge<int> edge3(3, node1, node3,6);
    std::set<const CXXGRAPH::Edge<int> *> edgeSet;
    edgeSet.insert(&edge1);
    edgeSet.insert(&edge2);
    edgeSet.insert(&edge3);
    CXXGRAPH::Graph<int> graph(edgeSet);
    CXXGRAPH::DijkstraResult  res= graph.dijkstra(node1,node3);
    ASSERT_TRUE(res.success);
    ASSERT_EQ(res.errorMessage, "");
    ASSERT_EQ(res.result, 6);

}

TEST(DijkstraTest, test_3)
{
    CXXGRAPH::Node<int> node1(1, 1);
    CXXGRAPH::Node<int> node2(2, 2);
    CXXGRAPH::Node<int> node3(3, 3);
    std::pair<const CXXGRAPH::Node<int> *, const CXXGRAPH::Node<int> *> pairNode(&node1, &node2);
    CXXGRAPH::DirectedWeightedEdge<int> edge1(1, pairNode,5);
    CXXGRAPH::DirectedEdge<int> edge2(2, node2, node3);
    CXXGRAPH::UndirectedWeightedEdge<int> edge3(3, node1, node3,6);
    std::set<const CXXGRAPH::Edge<int> *> edgeSet;
    edgeSet.insert(&edge1);
    edgeSet.insert(&edge2);
    edgeSet.insert(&edge3);
    CXXGRAPH::Graph<int> graph(edgeSet);
    CXXGRAPH::DijkstraResult  res= graph.dijkstra(node1,node3);
    ASSERT_FALSE(res.success);
    ASSERT_EQ(res.errorMessage, CXXGRAPH::ERR_NO_WEIGHTED_EDGE);
    ASSERT_EQ(res.result, CXXGRAPH::INF_DOUBLE);

}

TEST(DijkstraTest, test_4)
{
    CXXGRAPH::Node<int> node1(1, 1);
    CXXGRAPH::Node<int> node2(2, 2);
    CXXGRAPH::Node<int> node3(3, 3);
    CXXGRAPH::DirectedEdge<int> edge2(2, node2, node3);
    CXXGRAPH::UndirectedWeightedEdge<int> edge3(3, node1, node3,6);
    std::set<const CXXGRAPH::Edge<int> *> edgeSet;
    edgeSet.insert(&edge2);
    edgeSet.insert(&edge3);
    CXXGRAPH::Graph<int> graph(edgeSet);
    CXXGRAPH::DijkstraResult  res= graph.dijkstra(node1,node2);
    ASSERT_FALSE(res.success);
    ASSERT_EQ(res.errorMessage, CXXGRAPH::ERR_DIJ_TARGET_NODE_NOT_REACHABLE);
    ASSERT_EQ(res.result, -1);

}