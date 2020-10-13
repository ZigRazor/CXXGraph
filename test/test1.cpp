#include "gtest/gtest.h"
#include "Graph.hpp"

TEST(NodeTest, Constructor_1)
{
    CXXGRAPH::Node<int> node(1,1);
    ASSERT_EQ(node.getId(), 1);
    ASSERT_EQ(node.getData(), 1);
}

TEST(EdgeTest, Constructor_1)
{
    CXXGRAPH::Node<int> node1(1,1);
    CXXGRAPH::Node<int> node2(2,2);
    CXXGRAPH::Edge<int> edge(1,node1,node2);
    ASSERT_EQ(edge.getNodePair().first, node1);
    ASSERT_EQ(edge.getNodePair().second, node2);
}

TEST(EdgeTest, Constructor_2)
{
    CXXGRAPH::Node<int> node1(1,1);
    CXXGRAPH::Node<int> node2(2,2);
    std::pair<CXXGRAPH::Node<int>,CXXGRAPH::Node<int>> pairNode(node1,node2);
    CXXGRAPH::Edge<int> edge(1,pairNode);
    ASSERT_EQ(edge.getNodePair(),pairNode);
    ASSERT_EQ(edge.getNodePair().first, node1);
    ASSERT_EQ(edge.getNodePair().second, node2);
}

TEST(DirectedEdgeTest, Constructor_1)
{
    CXXGRAPH::Node<int> node1(1,1);
    CXXGRAPH::Node<int> node2(2,2);
    CXXGRAPH::DirectedEdge<int> edge(1,node1,node2);
    ASSERT_EQ(edge.getNodePair().first, node1);
    ASSERT_EQ(edge.getNodePair().second, node2);
}

TEST(DirectedEdgeTest, Constructor_2)
{
    CXXGRAPH::Node<int> node1(1,1);
    CXXGRAPH::Node<int> node2(2,2);
    std::pair<CXXGRAPH::Node<int>,CXXGRAPH::Node<int>> pairNode(node1,node2);
    CXXGRAPH::DirectedEdge<int> edge(1,pairNode);
    ASSERT_EQ(edge.getNodePair(),pairNode);
    ASSERT_EQ(edge.getNodePair().first, node1);
    ASSERT_EQ(edge.getNodePair().second, node2);
}

TEST(DirectedEdgeTest, Constructor_3)
{
    CXXGRAPH::Node<int> node1(1,1);
    CXXGRAPH::Node<int> node2(2,2);
    std::pair<CXXGRAPH::Node<int>,CXXGRAPH::Node<int>> pairNode(node1,node2);
    CXXGRAPH::DirectedEdge<int> edge(1,pairNode);
    ASSERT_TRUE(edge.isDirected().value());
}

TEST(DirectedEdgeTest, Constructor_4)
{
    CXXGRAPH::Node<int> node1(1,1);
    CXXGRAPH::Node<int> node2(2,2);
    std::pair<CXXGRAPH::Node<int>,CXXGRAPH::Node<int>> pairNode(node1,node2);
    CXXGRAPH::DirectedEdge<int> edge(1,pairNode);
    ASSERT_FALSE(edge.isWeighted().value());
}

TEST(DirectedEdgeTest, Constructor_5)
{
    CXXGRAPH::Node<int> node1(1,1);
    CXXGRAPH::Node<int> node2(2,2);
    std::pair<CXXGRAPH::Node<int>,CXXGRAPH::Node<int>> pairNode(node1,node2);
    CXXGRAPH::Edge<int> base_edge(1,pairNode);
    CXXGRAPH::DirectedEdge<int> edge(base_edge);
    ASSERT_EQ(edge.getNodePair(),pairNode);
    ASSERT_EQ(edge.getNodePair().first, node1);
    ASSERT_EQ(edge.getNodePair().second, node2);
    ASSERT_TRUE(edge.isDirected().value());
    ASSERT_FALSE(edge.isWeighted().value());
}

TEST(DirectedEdgeTest, Cast_1)
{
    CXXGRAPH::Node<int> node1(1,1);
    CXXGRAPH::Node<int> node2(2,2);
    std::pair<CXXGRAPH::Node<int>,CXXGRAPH::Node<int>> pairNode(node1,node2);
    CXXGRAPH::Edge<int> base_edge(1,pairNode);
    CXXGRAPH::DirectedEdge<int> edge = base_edge;
    ASSERT_EQ(edge.getNodePair(),pairNode);
    ASSERT_EQ(edge.getNodePair().first, node1);
    ASSERT_EQ(edge.getNodePair().second, node2);
    ASSERT_TRUE(edge.isDirected().value());
    ASSERT_FALSE(edge.isWeighted().value());
}



TEST(UndirectedEdgeTest, Constructor_1)
{
    CXXGRAPH::Node<int> node1(1,1);
    CXXGRAPH::Node<int> node2(2,2);
    CXXGRAPH::UndirectedEdge<int> edge(1,node1,node2);
    ASSERT_EQ(edge.getNodePair().first, node1);
    ASSERT_EQ(edge.getNodePair().second, node2);
}

TEST(UndirectedEdgeTest, Constructor_2)
{
    CXXGRAPH::Node<int> node1(1,1);
    CXXGRAPH::Node<int> node2(2,2);
    std::pair<CXXGRAPH::Node<int>,CXXGRAPH::Node<int>> pairNode(node1,node2);
    CXXGRAPH::UndirectedEdge<int> edge(1,pairNode);
    ASSERT_EQ(edge.getNodePair(),pairNode);
    ASSERT_EQ(edge.getNodePair().first, node1);
    ASSERT_EQ(edge.getNodePair().second, node2);
}

TEST(UndirectedEdgeTest, Constructor_3)
{
    CXXGRAPH::Node<int> node1(1,1);
    CXXGRAPH::Node<int> node2(2,2);
    std::pair<CXXGRAPH::Node<int>,CXXGRAPH::Node<int>> pairNode(node1,node2);
    CXXGRAPH::UndirectedEdge<int> edge(1,pairNode);
    ASSERT_FALSE(edge.isDirected().value());
}

TEST(UndirectedEdgeTest, Constructor_4)
{
    CXXGRAPH::Node<int> node1(1,1);
    CXXGRAPH::Node<int> node2(2,2);
    std::pair<CXXGRAPH::Node<int>,CXXGRAPH::Node<int>> pairNode(node1,node2);
    CXXGRAPH::UndirectedEdge<int> edge(1,pairNode);
    ASSERT_FALSE(edge.isWeighted().value());
}

TEST(UndirectedEdgeTest, Constructor_5)
{
    CXXGRAPH::Node<int> node1(1,1);
    CXXGRAPH::Node<int> node2(2,2);
    std::pair<CXXGRAPH::Node<int>,CXXGRAPH::Node<int>> pairNode(node1,node2);
    CXXGRAPH::Edge<int> base_edge(1,pairNode);
    CXXGRAPH::UndirectedEdge<int> edge(base_edge);
    ASSERT_EQ(edge.getNodePair(),pairNode);
    ASSERT_EQ(edge.getNodePair().first, node1);
    ASSERT_EQ(edge.getNodePair().second, node2);
    ASSERT_FALSE(edge.isDirected().value());
    ASSERT_FALSE(edge.isWeighted().value());
}

TEST(UndirectedEdgeTest, Cast_1)
{
    CXXGRAPH::Node<int> node1(1,1);
    CXXGRAPH::Node<int> node2(2,2);
    std::pair<CXXGRAPH::Node<int>,CXXGRAPH::Node<int>> pairNode(node1,node2);
    CXXGRAPH::Edge<int> base_edge(1,pairNode);
    CXXGRAPH::UndirectedEdge<int> edge = base_edge;
    ASSERT_EQ(edge.getNodePair(),pairNode);
    ASSERT_EQ(edge.getNodePair().first, node1);
    ASSERT_EQ(edge.getNodePair().second, node2);
    ASSERT_FALSE(edge.isDirected().value());
    ASSERT_FALSE(edge.isWeighted().value());
}


TEST(GraphTest, Constructor_1)
{
    CXXGRAPH::Node<int> node1(1,1);
    CXXGRAPH::Node<int> node2(2,2);
    std::pair<CXXGRAPH::Node<int>,CXXGRAPH::Node<int>> pairNode(node1,node2);
    CXXGRAPH::Edge<int> edge(1,pairNode);
    std::set<CXXGRAPH::Edge<int>> edgeSet;
    edgeSet.insert(edge);
    CXXGRAPH::Graph<int> graph(edgeSet);
    ASSERT_EQ(graph.getEdgeSet(),edgeSet);
}

TEST(GraphTest, GetEdge_1)
{
    CXXGRAPH::Node<int> node1(1,1);
    CXXGRAPH::Node<int> node2(2,2);
    std::pair<CXXGRAPH::Node<int>,CXXGRAPH::Node<int>> pairNode(node1,node2);
    CXXGRAPH::Edge<int> edge(1,pairNode);
    std::set<CXXGRAPH::Edge<int>> edgeSet;
    edgeSet.insert(edge);
    CXXGRAPH::Graph<int> graph(edgeSet);
    ASSERT_FALSE(graph.getEdge(2).has_value());
}

TEST(GraphTest, GetEdge_2)
{
    CXXGRAPH::Node<int> node1(1,1);
    CXXGRAPH::Node<int> node2(2,2);
    std::pair<CXXGRAPH::Node<int>,CXXGRAPH::Node<int>> pairNode(node1,node2);
    CXXGRAPH::Edge<int> edge(1,pairNode);
    std::set<CXXGRAPH::Edge<int>> edgeSet;
    edgeSet.insert(edge);
    CXXGRAPH::Graph<int> graph(edgeSet);
    ASSERT_TRUE(graph.getEdge(1).has_value());
}

TEST(GraphTest, GetEdge_3)
{
    CXXGRAPH::Node<int> node1(1,1);
    CXXGRAPH::Node<int> node2(2,2);
    std::pair<CXXGRAPH::Node<int>,CXXGRAPH::Node<int>> pairNode(node1,node2);
    CXXGRAPH::Edge<int> edge(1,pairNode);
    std::set<CXXGRAPH::Edge<int>> edgeSet;
    edgeSet.insert(edge);
    CXXGRAPH::Graph<int> graph(edgeSet);
    ASSERT_EQ(graph.getEdge(1).value(), edge);
}