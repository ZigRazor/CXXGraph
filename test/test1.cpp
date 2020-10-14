#include "gtest/gtest.h"
#include "Graph.hpp"

TEST(NodeTest, Constructor_1)
{
    CXXGRAPH::Node<int> node(1,1);
    ASSERT_EQ(node.getId(), 1);
    ASSERT_EQ(node.getData(), 1);
}

TEST(NodeTest, print_1)
{
    CXXGRAPH::Node<int> node(1,1);
    std::cout << "Test Print Node" << std::endl;
    std::cout << node << std::endl;
}

TEST(EdgeTest, Constructor_1)
{
    CXXGRAPH::Node<int> node1(1,1);
    CXXGRAPH::Node<int> node2(2,2);
    CXXGRAPH::Edge<int> edge(1,node1,node2);
    ASSERT_EQ(*(edge.getNodePair().first), node1);
    ASSERT_EQ(*(edge.getNodePair().second), node2);
}

TEST(EdgeTest, Constructor_2)
{
    CXXGRAPH::Node<int> node1(1,1);
    CXXGRAPH::Node<int> node2(2,2);
    std::pair<const CXXGRAPH::Node<int>*,const CXXGRAPH::Node<int>*> pairNode(&node1,&node2);
    CXXGRAPH::Edge<int> edge(1,pairNode);
    ASSERT_EQ(edge.getNodePair(),pairNode);
    ASSERT_EQ(*(edge.getNodePair().first), node1);
    ASSERT_EQ(*(edge.getNodePair().second), node2);
}

TEST(EdgeTest, print_1)
{
    CXXGRAPH::Node<int> node1(1,1);
    CXXGRAPH::Node<int> node2(2,2);
    CXXGRAPH::Edge<int> edge(1,node1,node2);
    std::cout << "Test Print Edge" << std::endl;
    std::cout << edge << std::endl;
}

TEST(DirectedEdgeTest, Constructor_1)
{
    CXXGRAPH::Node<int> node1(1,1);
    CXXGRAPH::Node<int> node2(2,2);
    CXXGRAPH::DirectedEdge<int> edge(1,node1,node2);
    ASSERT_EQ(*(edge.getNodePair().first), node1);
    ASSERT_EQ(*(edge.getNodePair().second), node2);
}

TEST(DirectedEdgeTest, Constructor_2)
{
    CXXGRAPH::Node<int> node1(1,1);
    CXXGRAPH::Node<int> node2(2,2);
    std::pair<const CXXGRAPH::Node<int>*,const CXXGRAPH::Node<int>*> pairNode(&node1,&node2);
    CXXGRAPH::DirectedEdge<int> edge(1,pairNode);
    ASSERT_EQ(edge.getNodePair(),pairNode);
    ASSERT_EQ(*(edge.getNodePair().first), node1);
    ASSERT_EQ(*(edge.getNodePair().second), node2);
}

TEST(DirectedEdgeTest, Constructor_3)
{
    CXXGRAPH::Node<int> node1(1,1);
    CXXGRAPH::Node<int> node2(2,2);
    std::pair<const CXXGRAPH::Node<int>*,const CXXGRAPH::Node<int>*> pairNode(&node1,&node2);
    CXXGRAPH::DirectedEdge<int> edge(1,pairNode);
    ASSERT_TRUE(edge.isDirected().value());
}

TEST(DirectedEdgeTest, Constructor_4)
{
    CXXGRAPH::Node<int> node1(1,1);
    CXXGRAPH::Node<int> node2(2,2);
    std::pair<const CXXGRAPH::Node<int>*,const CXXGRAPH::Node<int>*> pairNode(&node1,&node2);
    CXXGRAPH::DirectedEdge<int> edge(1,pairNode);
    ASSERT_FALSE(edge.isWeighted().value());
}

TEST(DirectedEdgeTest, Constructor_5)
{
    CXXGRAPH::Node<int> node1(1,1);
    CXXGRAPH::Node<int> node2(2,2);
    std::pair<const CXXGRAPH::Node<int>*,const CXXGRAPH::Node<int>*> pairNode(&node1,&node2);
    CXXGRAPH::Edge<int> base_edge(1,pairNode);
    CXXGRAPH::DirectedEdge<int> edge(base_edge);
    ASSERT_EQ(edge.getNodePair(),pairNode);
    ASSERT_EQ(*(edge.getNodePair().first), node1);
    ASSERT_EQ(*(edge.getNodePair().second), node2);
    ASSERT_TRUE(edge.isDirected().value());
    ASSERT_FALSE(edge.isWeighted().value());
}

TEST(DirectedEdgeTest, Cast_1)
{
    CXXGRAPH::Node<int> node1(1,1);
    CXXGRAPH::Node<int> node2(2,2);
    std::pair<const CXXGRAPH::Node<int>*,const CXXGRAPH::Node<int>*> pairNode(&node1,&node2);
    CXXGRAPH::Edge<int> base_edge(1,pairNode);
    CXXGRAPH::DirectedEdge<int> edge = base_edge;
    ASSERT_EQ(edge.getNodePair(),pairNode);
    ASSERT_EQ(*(edge.getNodePair().first), node1);
    ASSERT_EQ(*(edge.getNodePair().second), node2);
    ASSERT_TRUE(edge.isDirected().value());
    ASSERT_FALSE(edge.isWeighted().value());
}

TEST(DirectedEdgeTest, print_1)
{
    CXXGRAPH::Node<int> node1(1,1);
    CXXGRAPH::Node<int> node2(2,2);
    CXXGRAPH::DirectedEdge<int> edge(1,node1,node2);
    std::cout << "Test Print DirectedEdge" << std::endl;
    std::cout << edge << std::endl;
}



TEST(UndirectedEdgeTest, Constructor_1)
{
    CXXGRAPH::Node<int> node1(1,1);
    CXXGRAPH::Node<int> node2(2,2);
    CXXGRAPH::UndirectedEdge<int> edge(1,node1,node2);
    ASSERT_EQ(*(edge.getNodePair().first), node1);
    ASSERT_EQ(*(edge.getNodePair().second), node2);
}

TEST(UndirectedEdgeTest, Constructor_2)
{
    CXXGRAPH::Node<int> node1(1,1);
    CXXGRAPH::Node<int> node2(2,2);
    std::pair<const CXXGRAPH::Node<int>*,const CXXGRAPH::Node<int>*> pairNode(&node1,&node2);
    CXXGRAPH::UndirectedEdge<int> edge(1,pairNode);
    ASSERT_EQ(edge.getNodePair(),pairNode);
    ASSERT_EQ(*(edge.getNodePair().first), node1);
    ASSERT_EQ(*(edge.getNodePair().second), node2);
}

TEST(UndirectedEdgeTest, Constructor_3)
{
    CXXGRAPH::Node<int> node1(1,1);
    CXXGRAPH::Node<int> node2(2,2);
    std::pair<const CXXGRAPH::Node<int>*,const CXXGRAPH::Node<int>*> pairNode(&node1,&node2);
    CXXGRAPH::UndirectedEdge<int> edge(1,pairNode);
    ASSERT_FALSE(edge.isDirected().value());
}

TEST(UndirectedEdgeTest, Constructor_4)
{
    CXXGRAPH::Node<int> node1(1,1);
    CXXGRAPH::Node<int> node2(2,2);
    std::pair<const CXXGRAPH::Node<int>*,const CXXGRAPH::Node<int>*> pairNode(&node1,&node2);
    CXXGRAPH::UndirectedEdge<int> edge(1,pairNode);
    ASSERT_FALSE(edge.isWeighted().value());
}

TEST(UndirectedEdgeTest, Constructor_5)
{
    CXXGRAPH::Node<int> node1(1,1);
    CXXGRAPH::Node<int> node2(2,2);
    std::pair<const CXXGRAPH::Node<int>*,const CXXGRAPH::Node<int>*> pairNode(&node1,&node2);
    CXXGRAPH::Edge<int> base_edge(1,pairNode);
    CXXGRAPH::UndirectedEdge<int> edge(base_edge);
    ASSERT_EQ(edge.getNodePair(),pairNode);
    ASSERT_EQ(*(edge.getNodePair().first), node1);
    ASSERT_EQ(*(edge.getNodePair().second), node2);
    ASSERT_FALSE(edge.isDirected().value());
    ASSERT_FALSE(edge.isWeighted().value());
}

TEST(UndirectedEdgeTest, Cast_1)
{
    CXXGRAPH::Node<int> node1(1,1);
    CXXGRAPH::Node<int> node2(2,2);
    std::pair<const CXXGRAPH::Node<int>*,const CXXGRAPH::Node<int>*> pairNode(&node1,&node2);
    CXXGRAPH::Edge<int> base_edge(1,pairNode);
    CXXGRAPH::UndirectedEdge<int> edge = base_edge;
    ASSERT_EQ(edge.getNodePair(),pairNode);
    ASSERT_EQ(*(edge.getNodePair().first), node1);
    ASSERT_EQ(*(edge.getNodePair().second), node2);
    ASSERT_FALSE(edge.isDirected().value());
    ASSERT_FALSE(edge.isWeighted().value());
}

TEST(UndirectedEdgeTest, print_1)
{
    CXXGRAPH::Node<int> node1(1,1);
    CXXGRAPH::Node<int> node2(2,2);
    CXXGRAPH::UndirectedEdge<int> edge(1,node1,node2);
    std::cout << "Test Print UndirectedEdge" << std::endl;
    std::cout << edge << std::endl;
}


TEST(GraphTest, Constructor_1)
{
    CXXGRAPH::Node<int> node1(1,1);
    CXXGRAPH::Node<int> node2(2,2);
    std::pair<const CXXGRAPH::Node<int>*,const CXXGRAPH::Node<int>*> pairNode(&node1,&node2);
    CXXGRAPH::Edge<int> edge(1,pairNode);
    std::set<const CXXGRAPH::Edge<int>*> edgeSet;
    edgeSet.insert(&edge);
    CXXGRAPH::Graph<int> graph(edgeSet);
    ASSERT_EQ(graph.getEdgeSet(),edgeSet);
}

TEST(GraphTest, GetEdge_1)
{
    CXXGRAPH::Node<int> node1(1,1);
    CXXGRAPH::Node<int> node2(2,2);
    std::pair<const CXXGRAPH::Node<int>*,const CXXGRAPH::Node<int>*> pairNode(&node1,&node2);
    CXXGRAPH::Edge<int> edge(1,pairNode);
    std::set<const CXXGRAPH::Edge<int>*> edgeSet;
    edgeSet.insert(&edge);
    CXXGRAPH::Graph<int> graph(edgeSet);
    ASSERT_FALSE(graph.getEdge(2).has_value());
}

TEST(GraphTest, GetEdge_2)
{
    CXXGRAPH::Node<int> node1(1,1);
    CXXGRAPH::Node<int> node2(2,2);
    std::pair<const CXXGRAPH::Node<int>*,const CXXGRAPH::Node<int>*> pairNode(&node1,&node2);
    CXXGRAPH::Edge<int> edge(1,pairNode);
    std::set<const CXXGRAPH::Edge<int>*> edgeSet;
    edgeSet.insert(&edge);
    CXXGRAPH::Graph<int> graph(edgeSet);
    ASSERT_TRUE(graph.getEdge(1).has_value());
}

TEST(GraphTest, GetEdge_3)
{
    CXXGRAPH::Node<int> node1(1,1);
    CXXGRAPH::Node<int> node2(2,2);
    std::pair<const CXXGRAPH::Node<int>*,const CXXGRAPH::Node<int>*> pairNode(&node1,&node2);
    CXXGRAPH::Edge<int> edge(1,pairNode);
    std::set<const CXXGRAPH::Edge<int>*> edgeSet;
    edgeSet.insert(&edge);
    CXXGRAPH::Graph<int> graph(edgeSet);
    ASSERT_EQ(*(graph.getEdge(1).value()), edge);
}

TEST(GraphTest, print_1)
{
    CXXGRAPH::Node<int> node1(1,1);
    CXXGRAPH::Node<int> node2(2,2);
    std::pair<const CXXGRAPH::Node<int>*,const CXXGRAPH::Node<int>*> pairNode(&node1,&node2);
    CXXGRAPH::Edge<int> edge(1,pairNode);
    std::set<const CXXGRAPH::Edge<int>*> edgeSet;
    edgeSet.insert(&edge);
    CXXGRAPH::Graph<int> graph(edgeSet);
    std::cout << "Test Print Adjacency Matrix" << std::endl;
    std::cout << graph.getAdjMatrix() << std::endl;
}

TEST(GraphTest, print_2)
{
    CXXGRAPH::Node<int> node1(1,1);
    CXXGRAPH::Node<int> node2(2,2);
    std::pair<const CXXGRAPH::Node<int>*,const CXXGRAPH::Node<int>*> pairNode(&node1,&node2);
    CXXGRAPH::DirectedEdge<int> edge(1,pairNode);
    std::set<const CXXGRAPH::Edge<int>*> edgeSet;
    edgeSet.insert(&edge);
    CXXGRAPH::Graph<int> graph(edgeSet);
    std::cout << "Test Print Adjacency Matrix" << std::endl;
    std::cout << graph.getAdjMatrix() << std::endl;
}

TEST(GraphTest, print_3)
{
    CXXGRAPH::Node<int> node1(1,1);
    CXXGRAPH::Node<int> node2(2,2);
    std::pair<const CXXGRAPH::Node<int>*,const CXXGRAPH::Node<int>*> pairNode(&node1,&node2);
    CXXGRAPH::UndirectedEdge<int> edge(1,pairNode);
    std::set<const CXXGRAPH::Edge<int>*> edgeSet;
    edgeSet.insert(&edge);
    CXXGRAPH::Graph<int> graph(edgeSet);
    std::cout << "Test Print Adjacency Matrix" << std::endl;
    std::cout << graph.getAdjMatrix() << std::endl;
}