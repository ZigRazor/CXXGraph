#include "gtest/gtest.h"
#include "CXXGraph.hpp"

TEST(GraphTest, Constructor_1)
{
    CXXGRAPH::Node<int> node1("1", 1);
    CXXGRAPH::Node<int> node2("2", 2);
    std::pair<const CXXGRAPH::Node<int> *, const CXXGRAPH::Node<int> *> pairNode(&node1, &node2);
    CXXGRAPH::Edge<int> edge(1, pairNode);
    std::list<const CXXGRAPH::Edge<int> *> edgeSet;
    edgeSet.push_back(&edge);
    CXXGRAPH::Graph<int> graph(edgeSet);
    ASSERT_EQ(graph.getEdgeSet(), edgeSet);
}

TEST(GraphTest, GetEdge_1)
{
    CXXGRAPH::Node<int> node1("1", 1);
    CXXGRAPH::Node<int> node2("2", 2);
    std::pair<const CXXGRAPH::Node<int> *, const CXXGRAPH::Node<int> *> pairNode(&node1, &node2);
    CXXGRAPH::Edge<int> edge(1, pairNode);
    std::list<const CXXGRAPH::Edge<int> *> edgeSet;
    edgeSet.push_back(&edge);
    CXXGRAPH::Graph<int> graph(edgeSet);
    ASSERT_FALSE(graph.getEdge(2).has_value());
}

TEST(GraphTest, GetEdge_2)
{
    CXXGRAPH::Node<int> node1("1", 1);
    CXXGRAPH::Node<int> node2("2", 2);
    std::pair<const CXXGRAPH::Node<int> *, const CXXGRAPH::Node<int> *> pairNode(&node1, &node2);
    CXXGRAPH::Edge<int> edge(1, pairNode);
    std::list<const CXXGRAPH::Edge<int> *> edgeSet;
    edgeSet.push_back(&edge);
    CXXGRAPH::Graph<int> graph(edgeSet);
    ASSERT_TRUE(graph.getEdge(1).has_value());
}

TEST(GraphTest, GetEdge_3)
{
    CXXGRAPH::Node<int> node1("1", 1);
    CXXGRAPH::Node<int> node2("2", 2);
    std::pair<const CXXGRAPH::Node<int> *, const CXXGRAPH::Node<int> *> pairNode(&node1, &node2);
    CXXGRAPH::Edge<int> edge(1, pairNode);
    std::list<const CXXGRAPH::Edge<int> *> edgeSet;
    edgeSet.push_back(&edge);
    CXXGRAPH::Graph<int> graph(edgeSet);
    ASSERT_EQ(*(graph.getEdge(1).value()), edge);
}

TEST(GraphTest, GetNodeSet_1)
{
    CXXGRAPH::Node<int> node1("1", 1);
    CXXGRAPH::Node<int> node2("2", 2);
    std::pair<const CXXGRAPH::Node<int> *, const CXXGRAPH::Node<int> *> pairNode(&node1, &node2);
    CXXGRAPH::Edge<int> edge(1, pairNode);
    std::list<const CXXGRAPH::Edge<int> *> edgeSet;
    edgeSet.push_back(&edge);
    CXXGRAPH::Graph<int> graph(edgeSet);
    auto nodeSet = graph.getNodeSet();
    ASSERT_EQ(nodeSet.size(), 2);
    ASSERT_TRUE(std::find(nodeSet.begin(), nodeSet.end(),&node1) != nodeSet.end());
    ASSERT_TRUE(std::find(nodeSet.begin(), nodeSet.end(),&node2) != nodeSet.end());
}

TEST(GraphTest, GetNodeSet_2)
{
    CXXGRAPH::Node<int> node1("1", 1);
    CXXGRAPH::Node<int> node2("2", 2);
    CXXGRAPH::Node<int> node3("3", 3);
    std::pair<const CXXGRAPH::Node<int> *, const CXXGRAPH::Node<int> *> pairNode(&node1, &node2);
    CXXGRAPH::Edge<int> edge(1, pairNode);
    CXXGRAPH::UndirectedEdge<int> edge2(2, node2, node3);
    std::list<const CXXGRAPH::Edge<int> *> edgeSet;
    edgeSet.push_back(&edge);
    edgeSet.push_back(&edge2);
    CXXGRAPH::Graph<int> graph(edgeSet);
    auto nodeSet = graph.getNodeSet();
    ASSERT_EQ(nodeSet.size(), 3);
    ASSERT_TRUE(std::find(nodeSet.begin(), nodeSet.end(),&node1) != nodeSet.end());
    ASSERT_TRUE(std::find(nodeSet.begin(), nodeSet.end(),&node2) != nodeSet.end());
    ASSERT_TRUE(std::find(nodeSet.begin(), nodeSet.end(),&node3) != nodeSet.end());
}

TEST(GraphTest, adj_print_1)
{
    CXXGRAPH::Node<int> node1("1", 1);
    CXXGRAPH::Node<int> node2("2", 2);
    std::pair<const CXXGRAPH::Node<int> *, const CXXGRAPH::Node<int> *> pairNode(&node1, &node2);
    CXXGRAPH::Edge<int> edge(1, pairNode);
    std::list<const CXXGRAPH::Edge<int> *> edgeSet;
    edgeSet.push_back(&edge);
    CXXGRAPH::Graph<int> graph(edgeSet);
    std::cout << "Test Print Adjacency Matrix" << std::endl;
    std::cout << graph.getAdjMatrix() << std::endl;
}

TEST(GraphTest, adj_print_2)
{
    CXXGRAPH::Node<int> node1("1", 1);
    CXXGRAPH::Node<int> node2("2", 2);
    std::pair<const CXXGRAPH::Node<int> *, const CXXGRAPH::Node<int> *> pairNode(&node1, &node2);
    CXXGRAPH::DirectedEdge<int> edge(1, pairNode);
    std::list<const CXXGRAPH::Edge<int> *> edgeSet;
    edgeSet.push_back(&edge);
    CXXGRAPH::Graph<int> graph(edgeSet);
    std::cout << "Test Print Adjacency Matrix" << std::endl;
    std::cout << graph.getAdjMatrix() << std::endl;
}

TEST(GraphTest, adj_print_3)
{
    CXXGRAPH::Node<int> node1("1", 1);
    CXXGRAPH::Node<int> node2("2", 2);
    std::pair<const CXXGRAPH::Node<int> *, const CXXGRAPH::Node<int> *> pairNode(&node1, &node2);
    CXXGRAPH::UndirectedEdge<int> edge(1, pairNode);
    std::list<const CXXGRAPH::Edge<int> *> edgeSet;
    edgeSet.push_back(&edge);
    CXXGRAPH::Graph<int> graph(edgeSet);
    std::cout << "Test Print Adjacency Matrix" << std::endl;
    std::cout << graph.getAdjMatrix() << std::endl;
}

TEST(GraphTest, adj_print_4)
{
    CXXGRAPH::Node<int> node1("1", 1);
    CXXGRAPH::Node<int> node2("2", 2);
    CXXGRAPH::Node<int> node3("3", 3);
    std::pair<const CXXGRAPH::Node<int> *, const CXXGRAPH::Node<int> *> pairNode(&node1, &node2);
    CXXGRAPH::UndirectedEdge<int> edge1(1, pairNode);
    CXXGRAPH::UndirectedEdge<int> edge2(2, node2, node3);
    CXXGRAPH::UndirectedEdge<int> edge3(3, node1, node3);
    std::list<const CXXGRAPH::Edge<int> *> edgeSet;
    edgeSet.push_back(&edge1);
    edgeSet.push_back(&edge2);
    edgeSet.push_back(&edge3);
    CXXGRAPH::Graph<int> graph(edgeSet);
    std::cout << "Test Print Adjacency Matrix" << std::endl;
    std::cout << graph.getAdjMatrix() << std::endl;
}

TEST(GraphTest, adj_print_5)
{
    CXXGRAPH::Node<int> node1("1", 1);
    CXXGRAPH::Node<int> node2("2", 2);
    CXXGRAPH::Node<int> node3("3", 3);
    std::pair<const CXXGRAPH::Node<int> *, const CXXGRAPH::Node<int> *> pairNode(&node1, &node2);
    CXXGRAPH::DirectedEdge<int> edge1(1, pairNode);
    CXXGRAPH::DirectedEdge<int> edge2(2, node2, node3);
    CXXGRAPH::DirectedEdge<int> edge3(3, node1, node3);
    std::list<const CXXGRAPH::Edge<int> *> edgeSet;
    edgeSet.push_back(&edge1);
    edgeSet.push_back(&edge2);
    edgeSet.push_back(&edge3);
    CXXGRAPH::Graph<int> graph(edgeSet);
    std::cout << "Test Print Adjacency Matrix" << std::endl;
    std::cout << graph.getAdjMatrix() << std::endl;
}

TEST(GraphTest, adj_print_6)
{
    CXXGRAPH::Node<int> node1("1", 1);
    CXXGRAPH::Node<int> node2("2", 2);
    CXXGRAPH::Node<int> node3("3", 3);
    std::pair<const CXXGRAPH::Node<int> *, const CXXGRAPH::Node<int> *> pairNode(&node1, &node2);
    CXXGRAPH::DirectedEdge<int> edge1(1, pairNode);
    CXXGRAPH::DirectedEdge<int> edge2(2, node2, node3);
    CXXGRAPH::UndirectedEdge<int> edge3(3, node1, node3);
    std::list<const CXXGRAPH::Edge<int> *> edgeSet;
    edgeSet.push_back(&edge1);
    edgeSet.push_back(&edge2);
    edgeSet.push_back(&edge3);
    CXXGRAPH::Graph<int> graph(edgeSet);
    std::cout << "Test Print Adjacency Matrix" << std::endl;
    std::cout << graph.getAdjMatrix() << std::endl;
}

TEST(Graph_TSTest, Constructor_1)
{
    CXXGRAPH::Node<int> node1("1", 1);
    CXXGRAPH::Node<int> node2("2", 2);
    std::pair<const CXXGRAPH::Node<int> *, const CXXGRAPH::Node<int> *> pairNode(&node1, &node2);
    CXXGRAPH::Edge<int> edge(1, pairNode);
    std::list<const CXXGRAPH::Edge<int> *> edgeSet;
    edgeSet.push_back(&edge);
    CXXGRAPH::Graph_TS<int> graph(edgeSet);
    ASSERT_EQ(graph.getEdgeSet(), edgeSet);
}

TEST(Graph_TSTest, GetEdge_1)
{
    CXXGRAPH::Node<int> node1("1", 1);
    CXXGRAPH::Node<int> node2("2", 2);
    std::pair<const CXXGRAPH::Node<int> *, const CXXGRAPH::Node<int> *> pairNode(&node1, &node2);
    CXXGRAPH::Edge<int> edge(1, pairNode);
    std::list<const CXXGRAPH::Edge<int> *> edgeSet;
    edgeSet.push_back(&edge);
    CXXGRAPH::Graph_TS<int> graph(edgeSet);
    ASSERT_FALSE(graph.getEdge(2).has_value());
}

TEST(Graph_TSTest, GetEdge_2)
{
    CXXGRAPH::Node<int> node1("1", 1);
    CXXGRAPH::Node<int> node2("2", 2);
    std::pair<const CXXGRAPH::Node<int> *, const CXXGRAPH::Node<int> *> pairNode(&node1, &node2);
    CXXGRAPH::Edge<int> edge(1, pairNode);
    std::list<const CXXGRAPH::Edge<int> *> edgeSet;
    edgeSet.push_back(&edge);
    CXXGRAPH::Graph_TS<int> graph(edgeSet);
    ASSERT_TRUE(graph.getEdge(1).has_value());
}

TEST(Graph_TSTest, GetEdge_3)
{
    CXXGRAPH::Node<int> node1("1", 1);
    CXXGRAPH::Node<int> node2("2", 2);
    std::pair<const CXXGRAPH::Node<int> *, const CXXGRAPH::Node<int> *> pairNode(&node1, &node2);
    CXXGRAPH::Edge<int> edge(1, pairNode);
    std::list<const CXXGRAPH::Edge<int> *> edgeSet;
    edgeSet.push_back(&edge);
    CXXGRAPH::Graph_TS<int> graph(edgeSet);
    ASSERT_EQ(*(graph.getEdge(1).value()), edge);
}

TEST(Graph_TSTest, GetNodeSet_1)
{
    CXXGRAPH::Node<int> node1("1", 1);
    CXXGRAPH::Node<int> node2("2", 2);
    std::pair<const CXXGRAPH::Node<int> *, const CXXGRAPH::Node<int> *> pairNode(&node1, &node2);
    CXXGRAPH::Edge<int> edge(1, pairNode);
    std::list<const CXXGRAPH::Edge<int> *> edgeSet;
    edgeSet.push_back(&edge);
    CXXGRAPH::Graph_TS<int> graph(edgeSet);
    auto nodeSet = graph.getNodeSet();
    ASSERT_EQ(nodeSet.size(), 2);
    ASSERT_TRUE(std::find(nodeSet.begin(), nodeSet.end(), &node1) != nodeSet.end());
    ASSERT_TRUE(std::find(nodeSet.begin(), nodeSet.end(), &node2) != nodeSet.end());
}

TEST(Graph_TSTest, GetNodeSet_2)
{
    CXXGRAPH::Node<int> node1("1", 1);
    CXXGRAPH::Node<int> node2("2", 2);
    CXXGRAPH::Node<int> node3("3", 3);
    std::pair<const CXXGRAPH::Node<int> *, const CXXGRAPH::Node<int> *> pairNode(&node1, &node2);
    CXXGRAPH::Edge<int> edge(1, pairNode);
    CXXGRAPH::UndirectedEdge<int> edge2(2, node2, node3);
    std::list<const CXXGRAPH::Edge<int> *> edgeSet;
    edgeSet.push_back(&edge);
    edgeSet.push_back(&edge2);
    CXXGRAPH::Graph_TS<int> graph(edgeSet);
    auto nodeSet = graph.getNodeSet();
    ASSERT_EQ(nodeSet.size(), 3);
    ASSERT_TRUE(std::find(nodeSet.begin(), nodeSet.end(), &node1) != nodeSet.end());
    ASSERT_TRUE(std::find(nodeSet.begin(), nodeSet.end(), &node2) != nodeSet.end());
    ASSERT_TRUE(std::find(nodeSet.begin(), nodeSet.end(), &node3) != nodeSet.end());
}

TEST(Graph_TSTest, adj_print_1)
{
    CXXGRAPH::Node<int> node1("1", 1);
    CXXGRAPH::Node<int> node2("2", 2);
    std::pair<const CXXGRAPH::Node<int> *, const CXXGRAPH::Node<int> *> pairNode(&node1, &node2);
    CXXGRAPH::Edge<int> edge(1, pairNode);
    std::list<const CXXGRAPH::Edge<int> *> edgeSet;
    edgeSet.push_back(&edge);
    CXXGRAPH::Graph_TS<int> graph(edgeSet);
    std::cout << "Test Print Adjacency Matrix" << std::endl;
    std::cout << graph.getAdjMatrix() << std::endl;
}

TEST(Graph_TSTest, adj_print_2)
{
    CXXGRAPH::Node<int> node1("1", 1);
    CXXGRAPH::Node<int> node2("2", 2);
    std::pair<const CXXGRAPH::Node<int> *, const CXXGRAPH::Node<int> *> pairNode(&node1, &node2);
    CXXGRAPH::DirectedEdge<int> edge(1, pairNode);
    std::list<const CXXGRAPH::Edge<int> *> edgeSet;
    edgeSet.push_back(&edge);
    CXXGRAPH::Graph_TS<int> graph(edgeSet);
    std::cout << "Test Print Adjacency Matrix" << std::endl;
    std::cout << graph.getAdjMatrix() << std::endl;
}

TEST(Graph_TSTest, adj_print_3)
{
    CXXGRAPH::Node<int> node1("1", 1);
    CXXGRAPH::Node<int> node2("2", 2);
    std::pair<const CXXGRAPH::Node<int> *, const CXXGRAPH::Node<int> *> pairNode(&node1, &node2);
    CXXGRAPH::UndirectedEdge<int> edge(1, pairNode);
    std::list<const CXXGRAPH::Edge<int> *> edgeSet;
    edgeSet.push_back(&edge);
    CXXGRAPH::Graph_TS<int> graph(edgeSet);
    std::cout << "Test Print Adjacency Matrix" << std::endl;
    std::cout << graph.getAdjMatrix() << std::endl;
}

TEST(Graph_TSTest, adj_print_4)
{
    CXXGRAPH::Node<int> node1("1", 1);
    CXXGRAPH::Node<int> node2("2", 2);
    CXXGRAPH::Node<int> node3("3", 3);
    std::pair<const CXXGRAPH::Node<int> *, const CXXGRAPH::Node<int> *> pairNode(&node1, &node2);
    CXXGRAPH::UndirectedEdge<int> edge1(1, pairNode);
    CXXGRAPH::UndirectedEdge<int> edge2(2, node2, node3);
    CXXGRAPH::UndirectedEdge<int> edge3(3, node1, node3);
    std::list<const CXXGRAPH::Edge<int> *> edgeSet;
    edgeSet.push_back(&edge1);
    edgeSet.push_back(&edge2);
    edgeSet.push_back(&edge3);
    CXXGRAPH::Graph_TS<int> graph(edgeSet);
    std::cout << "Test Print Adjacency Matrix" << std::endl;
    std::cout << graph.getAdjMatrix() << std::endl;
}

TEST(Graph_TSTest, adj_print_5)
{
    CXXGRAPH::Node<int> node1("1", 1);
    CXXGRAPH::Node<int> node2("2", 2);
    CXXGRAPH::Node<int> node3("3", 3);
    std::pair<const CXXGRAPH::Node<int> *, const CXXGRAPH::Node<int> *> pairNode(&node1, &node2);
    CXXGRAPH::DirectedEdge<int> edge1(1, pairNode);
    CXXGRAPH::DirectedEdge<int> edge2(2, node2, node3);
    CXXGRAPH::DirectedEdge<int> edge3(3, node1, node3);
    std::list<const CXXGRAPH::Edge<int> *> edgeSet;
    edgeSet.push_back(&edge1);
    edgeSet.push_back(&edge2);
    edgeSet.push_back(&edge3);
    CXXGRAPH::Graph_TS<int> graph(edgeSet);
    std::cout << "Test Print Adjacency Matrix" << std::endl;
    std::cout << graph.getAdjMatrix() << std::endl;
}

TEST(Graph_TSTest, adj_print_6)
{
    CXXGRAPH::Node<int> node1("1", 1);
    CXXGRAPH::Node<int> node2("2", 2);
    CXXGRAPH::Node<int> node3("3", 3);
    std::pair<const CXXGRAPH::Node<int> *, const CXXGRAPH::Node<int> *> pairNode(&node1, &node2);
    CXXGRAPH::DirectedEdge<int> edge1(1, pairNode);
    CXXGRAPH::DirectedEdge<int> edge2(2, node2, node3);
    CXXGRAPH::UndirectedEdge<int> edge3(3, node1, node3);
    std::list<const CXXGRAPH::Edge<int> *> edgeSet;
    edgeSet.push_back(&edge1);
    edgeSet.push_back(&edge2);
    edgeSet.push_back(&edge3);
    CXXGRAPH::Graph_TS<int> graph(edgeSet);
    std::cout << "Test Print Adjacency Matrix" << std::endl;
    std::cout << graph.getAdjMatrix() << std::endl;
}