#include "gtest/gtest.h"
#include "CXXGraph.hpp"

TEST(FordFulkersonTest, test_1)
{
    CXXGRAPH::Node<int> node0("0", 0);
    CXXGRAPH::Node<int> node1("1", 1);
    CXXGRAPH::Node<int> node2("2", 2);
    CXXGRAPH::Node<int> node3("3", 3);
    CXXGRAPH::Node<int> node4("4", 4);
    CXXGRAPH::Node<int> node5("5", 5);

    CXXGRAPH::DirectedWeightedEdge<int> edge1(1, node0, node1, 11);
    CXXGRAPH::DirectedWeightedEdge<int> edge2(2, node0, node2, 12);
    CXXGRAPH::DirectedWeightedEdge<int> edge3(3, node2, node1, 1);
    CXXGRAPH::DirectedWeightedEdge<int> edge4(4, node1, node3, 12);
    CXXGRAPH::DirectedWeightedEdge<int> edge5(5, node2, node4, 11);
    CXXGRAPH::DirectedWeightedEdge<int> edge6(6, node4, node3, 7);
    CXXGRAPH::DirectedWeightedEdge<int> edge7(7, node4, node5, 4);
    CXXGRAPH::DirectedWeightedEdge<int> edge8(8, node3, node5, 19);
    std::list<const CXXGRAPH::Edge<int> *> edgeSet;
    edgeSet.push_back(&edge1);
    edgeSet.push_back(&edge2);
    edgeSet.push_back(&edge3);
    edgeSet.push_back(&edge4);
    edgeSet.push_back(&edge5);
    edgeSet.push_back(&edge6);
    edgeSet.push_back(&edge7);
    edgeSet.push_back(&edge8);

    CXXGRAPH::Graph<int> graph(edgeSet);

    ASSERT_EQ(graph.fordFulkersonMaxFlow(node0, node5), 23);
}

TEST(FordFulkersonTest, test_2)
{
    CXXGRAPH::Node<int> node0("0", 0);
    CXXGRAPH::Node<int> node1("1", 1);
    CXXGRAPH::Node<int> node2("2", 2);
    CXXGRAPH::Node<int> node3("3", 3);
    CXXGRAPH::Node<int> node4("4", 4);
    CXXGRAPH::Node<int> node5("5", 5);

    CXXGRAPH::UndirectedWeightedEdge<int> edge1(1, node0, node1, 11);
    CXXGRAPH::DirectedWeightedEdge<int> edge2(2, node0, node2, 12);
    CXXGRAPH::DirectedWeightedEdge<int> edge3(3, node2, node1, 1);
    CXXGRAPH::DirectedWeightedEdge<int> edge4(4, node1, node3, 12);
    CXXGRAPH::DirectedWeightedEdge<int> edge5(5, node2, node4, 11);
    CXXGRAPH::DirectedWeightedEdge<int> edge6(6, node4, node3, 7);
    CXXGRAPH::DirectedWeightedEdge<int> edge7(7, node4, node5, 4);
    CXXGRAPH::DirectedWeightedEdge<int> edge8(8, node3, node5, 19);
    std::list<const CXXGRAPH::Edge<int> *> edgeSet;
    edgeSet.push_back(&edge1);
    edgeSet.push_back(&edge2);
    edgeSet.push_back(&edge3);
    edgeSet.push_back(&edge4);
    edgeSet.push_back(&edge5);
    edgeSet.push_back(&edge6);
    edgeSet.push_back(&edge7);
    edgeSet.push_back(&edge8);

    CXXGRAPH::Graph<int> graph(edgeSet);

    ASSERT_EQ(graph.fordFulkersonMaxFlow(node0, node5), -1);
}

TEST(FordFulkersonTest, test_3)
{
    CXXGRAPH::Node<int> node0("0", 0);
    CXXGRAPH::Node<int> node1("1", 1);
    CXXGRAPH::Node<int> node2("2", 2);
    CXXGRAPH::Node<int> node3("3", 3);
    CXXGRAPH::Node<int> node4("4", 4);
    CXXGRAPH::Node<int> node5("5", 5);

    CXXGRAPH::DirectedWeightedEdge<int> edge1(1, node0, node1, 11);
    CXXGRAPH::DirectedWeightedEdge<int> edge2(2, node0, node2, 12);
    CXXGRAPH::DirectedWeightedEdge<int> edge3(3, node2, node1, 1);
    CXXGRAPH::DirectedWeightedEdge<int> edge4(4, node1, node3, 12);
    CXXGRAPH::DirectedWeightedEdge<int> edge5(5, node2, node4, 11);
    CXXGRAPH::DirectedWeightedEdge<int> edge6(6, node4, node3, 7);
    CXXGRAPH::DirectedWeightedEdge<int> edge7(7, node4, node5, 4);
    CXXGRAPH::DirectedWeightedEdge<int> edge8(8, node3, node5, 4);
    std::list<const CXXGRAPH::Edge<int> *> edgeSet;
    edgeSet.push_back(&edge1);
    edgeSet.push_back(&edge2);
    edgeSet.push_back(&edge3);
    edgeSet.push_back(&edge4);
    edgeSet.push_back(&edge5);
    edgeSet.push_back(&edge6);
    edgeSet.push_back(&edge7);
    edgeSet.push_back(&edge8);

    CXXGRAPH::Graph<int> graph(edgeSet);

    ASSERT_EQ(graph.fordFulkersonMaxFlow(node0, node5), 8);
}

TEST(FordFulkersonTest, test_4)
{
    CXXGRAPH::Node<int> node0("0", 0);
    CXXGRAPH::Node<int> node1("1", 1);
    CXXGRAPH::Node<int> node2("2", 2);
    CXXGRAPH::Node<int> node3("3", 3);
    CXXGRAPH::Node<int> node4("4", 4);
    CXXGRAPH::Node<int> node5("5", 5);

    CXXGRAPH::DirectedWeightedEdge<int> edge1(1, node0, node1, 11);
    CXXGRAPH::DirectedWeightedEdge<int> edge2(2, node0, node2, 12);
    CXXGRAPH::DirectedWeightedEdge<int> edge3(3, node2, node1, 1);
    CXXGRAPH::DirectedWeightedEdge<int> edge4(4, node1, node3, 12);
    CXXGRAPH::DirectedWeightedEdge<int> edge5(5, node2, node4, 11);
    CXXGRAPH::DirectedWeightedEdge<int> edge6(6, node4, node3, 7);
    CXXGRAPH::DirectedEdge<int> edge7(7, node4, node5);
    CXXGRAPH::DirectedWeightedEdge<int> edge8(8, node3, node5, 4);
    std::list<const CXXGRAPH::Edge<int> *> edgeSet;
    edgeSet.push_back(&edge1);
    edgeSet.push_back(&edge2);
    edgeSet.push_back(&edge3);
    edgeSet.push_back(&edge4);
    edgeSet.push_back(&edge5);
    edgeSet.push_back(&edge6);
    edgeSet.push_back(&edge7);
    edgeSet.push_back(&edge8);

    CXXGRAPH::Graph<int> graph(edgeSet);

    ASSERT_EQ(graph.fordFulkersonMaxFlow(node0, node5), 4);
}
