#include "gtest/gtest.h"
#include "CXXGraph.hpp"

// DirectedEdge
TEST(GraphSlicingTest, test_1)
{
    CXXGRAPH::Node<int> node1(1, 1);
    CXXGRAPH::Node<int> node2(2, 2);
    CXXGRAPH::Node<int> node3(3, 3);
    CXXGRAPH::Node<int> node4(4, 4);
    CXXGRAPH::Node<int> node5(5, 5);
    CXXGRAPH::Node<int> node6(6, 6);

    CXXGRAPH::DirectedEdge<int> edge1(1, node1, node2);
    CXXGRAPH::DirectedEdge<int> edge2(2, node2, node3);
    CXXGRAPH::DirectedEdge<int> edge3(3, node1, node5);
    CXXGRAPH::DirectedEdge<int> edge4(4, node5, node3);
    CXXGRAPH::DirectedEdge<int> edge5(5, node3, node6);
    CXXGRAPH::DirectedEdge<int> edge6(6, node4, node3);

    std::list<const CXXGRAPH::Edge<int> *> edgeSet;
    edgeSet.push_back(&edge1);
    edgeSet.push_back(&edge2);
    edgeSet.push_back(&edge3);
    edgeSet.push_back(&edge4);
    edgeSet.push_back(&edge5);
    edgeSet.push_back(&edge6);

    CXXGRAPH::Graph<int> graph(edgeSet);
    std::vector<CXXGRAPH::Node<int>> res = graph.graph_slicing(node1);
    ASSERT_EQ(res.size(), 3);
    ASSERT_TRUE(std::find(res.begin(), res.end(), node1) != res.end());
    ASSERT_TRUE(std::find(res.begin(), res.end(), node2) != res.end());
    ASSERT_TRUE(std::find(res.begin(), res.end(), node5) != res.end());
}

// DirectedWeightedEdge
// weights shouldn't matter
TEST(GraphSlicingTest, test_2)
{
    CXXGRAPH::Node<int> node1(1, 1);
    CXXGRAPH::Node<int> node2(2, 2);
    CXXGRAPH::Node<int> node3(3, 3);
    CXXGRAPH::Node<int> node4(4, 4);
    CXXGRAPH::Node<int> node5(5, 5);
    CXXGRAPH::Node<int> node6(6, 6);

    CXXGRAPH::DirectedWeightedEdge<int> edge1(1, node1, node2, 10);
    CXXGRAPH::DirectedWeightedEdge<int> edge2(2, node2, node3, -1);
    CXXGRAPH::DirectedWeightedEdge<int> edge3(3, node1, node5, 3);
    CXXGRAPH::DirectedWeightedEdge<int> edge4(4, node5, node3, 5);
    CXXGRAPH::DirectedWeightedEdge<int> edge5(5, node3, node6, 8);
    CXXGRAPH::DirectedWeightedEdge<int> edge6(6, node4, node3, 0);

    std::list<const CXXGRAPH::Edge<int> *> edgeSet;
    edgeSet.push_back(&edge1);
    edgeSet.push_back(&edge2);
    edgeSet.push_back(&edge3);
    edgeSet.push_back(&edge4);
    edgeSet.push_back(&edge5);
    edgeSet.push_back(&edge6);

    CXXGRAPH::Graph<int> graph(edgeSet);
    std::vector<CXXGRAPH::Node<int>> res = graph.graph_slicing(node1);
    ASSERT_EQ(res.size(), 3);
    ASSERT_TRUE(std::find(res.begin(), res.end(), node1) != res.end());
    ASSERT_TRUE(std::find(res.begin(), res.end(), node2) != res.end());
    ASSERT_TRUE(std::find(res.begin(), res.end(), node5) != res.end());
}

// UndirectedWeightedEdge
TEST(GraphSlicingTest, test_3)
{
    CXXGRAPH::Node<int> node1(1, 1);
    CXXGRAPH::Node<int> node2(2, 2);
    CXXGRAPH::Node<int> node3(3, 3);
    CXXGRAPH::Node<int> node4(4, 4);
    CXXGRAPH::Node<int> node5(5, 5);
    CXXGRAPH::Node<int> node6(6, 6);

    CXXGRAPH::UndirectedEdge<int> edge1(1, node1, node2);
    CXXGRAPH::UndirectedEdge<int> edge2(2, node2, node3);
    CXXGRAPH::UndirectedEdge<int> edge3(3, node1, node5);
    CXXGRAPH::UndirectedEdge<int> edge4(4, node5, node3);
    CXXGRAPH::UndirectedEdge<int> edge5(5, node3, node6);
    CXXGRAPH::UndirectedEdge<int> edge6(6, node4, node3);

    std::list<const CXXGRAPH::Edge<int> *> edgeSet;
    edgeSet.push_back(&edge1);
    edgeSet.push_back(&edge2);
    edgeSet.push_back(&edge3);
    edgeSet.push_back(&edge4);
    edgeSet.push_back(&edge5);
    edgeSet.push_back(&edge6);

    CXXGRAPH::Graph<int> graph(edgeSet);
    std::vector<CXXGRAPH::Node<int>> res = graph.graph_slicing(node1);
    ASSERT_EQ(res.size(), 6);
}

// UndirectedWeightedEdge
// weights shouldn't matter
TEST(GraphSlicingTest, test_4)
{
    CXXGRAPH::Node<int> node1(1, 1);
    CXXGRAPH::Node<int> node2(2, 2);
    CXXGRAPH::Node<int> node3(3, 3);
    CXXGRAPH::Node<int> node4(4, 4);
    CXXGRAPH::Node<int> node5(5, 5);
    CXXGRAPH::Node<int> node6(6, 6);

    CXXGRAPH::UndirectedWeightedEdge<int> edge1(1, node1, node2, 10);
    CXXGRAPH::UndirectedWeightedEdge<int> edge2(2, node2, node3, -1);
    CXXGRAPH::UndirectedWeightedEdge<int> edge3(3, node1, node5, 3);
    CXXGRAPH::UndirectedWeightedEdge<int> edge4(4, node5, node3, 5);
    CXXGRAPH::UndirectedWeightedEdge<int> edge5(5, node3, node6, 8);
    CXXGRAPH::UndirectedWeightedEdge<int> edge6(6, node4, node3, 0);

    std::list<const CXXGRAPH::Edge<int> *> edgeSet;
    edgeSet.push_back(&edge1);
    edgeSet.push_back(&edge2);
    edgeSet.push_back(&edge3);
    edgeSet.push_back(&edge4);
    edgeSet.push_back(&edge5);
    edgeSet.push_back(&edge6);

    CXXGRAPH::Graph<int> graph(edgeSet);
    std::vector<CXXGRAPH::Node<int>> res = graph.graph_slicing(node1);
    ASSERT_EQ(res.size(), 6);
}

// start node is disconnected from rest of the graph
TEST(GraphSlicingTest, test_5)
{
    CXXGRAPH::Node<int> node1(1, 1);
    CXXGRAPH::Node<int> node2(2, 2);
    CXXGRAPH::Node<int> node3(3, 3);
    CXXGRAPH::Node<int> node4(4, 4);
    CXXGRAPH::DirectedWeightedEdge<int> edge1(1, node1, node2, 1);
    CXXGRAPH::DirectedWeightedEdge<int> edge2(2, node2, node3, 1);
    CXXGRAPH::DirectedWeightedEdge<int> edge3(3, node1, node3, 6);
    std::list<const CXXGRAPH::Edge<int> *> edgeSet;
    edgeSet.push_back(&edge1);
    edgeSet.push_back(&edge2);
    edgeSet.push_back(&edge3);
    CXXGRAPH::Graph<int> graph(edgeSet);
    std::vector<CXXGRAPH::Node<int>> res = graph.graph_slicing(node4);
    ASSERT_EQ(res.size(), 0);
}