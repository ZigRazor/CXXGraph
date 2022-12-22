#include "gtest/gtest.h"
#include "CXXGraph.hpp"
#include <vector>

TEST(BestFirstSearchTest, source_node_missing)
{
    CXXGRAPH::Node<int> node1("1", 1);
    CXXGRAPH::Node<int> node2("2", 2);
    CXXGRAPH::Node<int> node3("3", 3);
    CXXGRAPH::Node<int> node4("4", 4);
    std::pair<const CXXGRAPH::Node<int> *, const CXXGRAPH::Node<int> *> pairNode(&node1, &node2);
    CXXGRAPH::DirectedWeightedEdge<int> edge1(1, pairNode, 1);
    CXXGRAPH::DirectedWeightedEdge<int> edge2(2, node2, node3, 3);
    CXXGRAPH::DirectedWeightedEdge<int> edge3(3, node1, node3, 6);
    CXXGRAPH::T_EdgeSet<int> edgeSet;
    edgeSet.insert(&edge1);
    edgeSet.insert(&edge2);
    edgeSet.insert(&edge3);
    CXXGRAPH::Graph<int> graph(edgeSet);
    CXXGRAPH::BestFirstSearchResult<int> res = graph.best_first_search(node4, node1);
    ASSERT_EQ(res.success, false);
    ASSERT_EQ(res.nodesInBestSearchOrder.size(), 0);
    ASSERT_EQ(res.errorMessage, CXXGRAPH::ERR_SOURCE_NODE_NOT_IN_GRAPH);
}

TEST(BestFirstSearchTest, target_node_missing)
{
    CXXGRAPH::Node<int> node1("1", 1);
    CXXGRAPH::Node<int> node2("2", 2);
    CXXGRAPH::Node<int> node3("3", 3);
    CXXGRAPH::Node<int> node4("4", 4);
    std::pair<const CXXGRAPH::Node<int> *, const CXXGRAPH::Node<int> *> pairNode(&node1, &node2);
    CXXGRAPH::DirectedWeightedEdge<int> edge1(1, pairNode, 1);
    CXXGRAPH::DirectedWeightedEdge<int> edge2(2, node2, node3, 3);
    CXXGRAPH::DirectedWeightedEdge<int> edge3(3, node1, node3, 6);
    CXXGRAPH::T_EdgeSet<int> edgeSet;
    edgeSet.insert(&edge1);
    edgeSet.insert(&edge2);
    edgeSet.insert(&edge3);
    CXXGRAPH::Graph<int> graph(edgeSet);
    CXXGRAPH::BestFirstSearchResult<int> res = graph.best_first_search(node1, node4);
    ASSERT_EQ(res.success, false);
    ASSERT_EQ(res.nodesInBestSearchOrder.size(), 0);
    ASSERT_EQ(res.errorMessage, CXXGRAPH::ERR_TARGET_NODE_NOT_IN_GRAPH);
}

TEST(BestFirstSearchTest, correct_example_small)
{
    CXXGRAPH::Node<int> node1("1", 1);
    CXXGRAPH::Node<int> node2("2", 2);
    CXXGRAPH::Node<int> node3("3", 3);
    std::pair<const CXXGRAPH::Node<int> *, const CXXGRAPH::Node<int> *> pairNode(&node1, &node2);
    CXXGRAPH::DirectedWeightedEdge<int> edge1(1, pairNode, 1);
    CXXGRAPH::DirectedWeightedEdge<int> edge2(2, node2, node3, 3);
    CXXGRAPH::DirectedWeightedEdge<int> edge3(3, node1, node3, 6);
    CXXGRAPH::T_EdgeSet<int> edgeSet;
    edgeSet.insert(&edge1);
    edgeSet.insert(&edge2);
    edgeSet.insert(&edge3);
    CXXGRAPH::Graph<int> graph(edgeSet);
    CXXGRAPH::BestFirstSearchResult<int> res = graph.best_first_search(node1, node2);
    ASSERT_EQ(res.success, true);
    ASSERT_EQ(res.nodesInBestSearchOrder.size(), 2);
    ASSERT_EQ(res.errorMessage, "");
}

TEST(BestFirstSearchTest, source_target_same)
{
    CXXGRAPH::Node<int> node1("1", 1);
    CXXGRAPH::Node<int> node2("2", 2);
    CXXGRAPH::Node<int> node3("3", 3);
    std::pair<const CXXGRAPH::Node<int> *, const CXXGRAPH::Node<int> *> pairNode(&node1, &node2);
    CXXGRAPH::DirectedWeightedEdge<int> edge1(1, pairNode, 1);
    CXXGRAPH::DirectedWeightedEdge<int> edge2(2, node2, node3, 3);
    CXXGRAPH::DirectedWeightedEdge<int> edge3(3, node1, node3, 6);
    CXXGRAPH::T_EdgeSet<int> edgeSet;
    edgeSet.insert(&edge1);
    edgeSet.insert(&edge2);
    edgeSet.insert(&edge3);
    CXXGRAPH::Graph<int> graph(edgeSet);
    CXXGRAPH::BestFirstSearchResult<int> res = graph.best_first_search(node1, node1);
    ASSERT_EQ(res.success, true);
    ASSERT_EQ(res.nodesInBestSearchOrder.size(), 1);
    ASSERT_EQ(res.errorMessage, "");
}

TEST(BestFirstSearchTest, correct_example_big)
{
    CXXGRAPH::Node<int> node1("1", 1);
    CXXGRAPH::Node<int> node2("2", 2);
    CXXGRAPH::Node<int> node3("3", 3);
    CXXGRAPH::Node<int> node4("4", 4);
    CXXGRAPH::Node<int> node5("5", 5);
    CXXGRAPH::Node<int> node6("6", 6);
    CXXGRAPH::Node<int> node7("7", 7);
    CXXGRAPH::Node<int> node8("8", 8);
    CXXGRAPH::Node<int> node9("9", 9);
    CXXGRAPH::Node<int> node10("10", 10);
    CXXGRAPH::Node<int> node11("11", 11);
    CXXGRAPH::Node<int> node12("12", 12);
    CXXGRAPH::Node<int> node13("13", 13);
    CXXGRAPH::Node<int> node14("14", 14);
    std::pair<const CXXGRAPH::Node<int> *, const CXXGRAPH::Node<int> *> pairNode(&node1, &node2);
    CXXGRAPH::DirectedWeightedEdge<int> edge1(1, node1, node2, 3);
    CXXGRAPH::DirectedWeightedEdge<int> edge2(2, node1, node3, 6);
    CXXGRAPH::DirectedWeightedEdge<int> edge3(3, node1, node4, 5);
    CXXGRAPH::DirectedWeightedEdge<int> edge4(4, node2, node5, 9);
    CXXGRAPH::DirectedWeightedEdge<int> edge5(5, node2, node6, 8);
    CXXGRAPH::DirectedWeightedEdge<int> edge6(6, node3, node7, 12);
    CXXGRAPH::DirectedWeightedEdge<int> edge7(7, node3, node8, 14);
    CXXGRAPH::DirectedWeightedEdge<int> edge8(8, node4, node9, 7);
    CXXGRAPH::DirectedWeightedEdge<int> edge9(9, node9, node10, 5);
    CXXGRAPH::DirectedWeightedEdge<int> edge10(10, node9, node11, 6);
    CXXGRAPH::DirectedWeightedEdge<int> edge11(10, node10, node12, 1);
    CXXGRAPH::DirectedWeightedEdge<int> edge12(10, node10, node13, 10);
    CXXGRAPH::DirectedWeightedEdge<int> edge13(10, node10, node14, 2);
    CXXGRAPH::T_EdgeSet<int> edgeSet;
    edgeSet.insert(&edge1);
    edgeSet.insert(&edge2);
    edgeSet.insert(&edge3);
    edgeSet.insert(&edge4);
    edgeSet.insert(&edge5);
    edgeSet.insert(&edge6);
    edgeSet.insert(&edge7);
    edgeSet.insert(&edge8);
    edgeSet.insert(&edge9);
    edgeSet.insert(&edge10);
    edgeSet.insert(&edge11);
    edgeSet.insert(&edge12);
    edgeSet.insert(&edge13);
    CXXGRAPH::Graph<int> graph(edgeSet);
    CXXGRAPH::BestFirstSearchResult<int> res = graph.best_first_search(node1, node10);
    ASSERT_EQ(res.success, true);
    ASSERT_EQ(res.nodesInBestSearchOrder.size(), 6);
    ASSERT_EQ(res.errorMessage, "");
}