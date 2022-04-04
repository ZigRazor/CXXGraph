#include "gtest/gtest.h"
#include "CXXGraph.hpp"

TEST(BFSTest, test_1)
{
    CXXGRAPH::Node<int> node1("1", 1);
    CXXGRAPH::Node<int> node2("2", 2);
    CXXGRAPH::Node<int> node3("3", 3);
    std::pair<const CXXGRAPH::Node<int> *, const CXXGRAPH::Node<int> *> pairNode(&node1, &node2);
    CXXGRAPH::DirectedWeightedEdge<int> edge1(1, pairNode, 1);
    CXXGRAPH::DirectedWeightedEdge<int> edge2(2, node2, node3, 1);
    CXXGRAPH::UndirectedWeightedEdge<int> edge3(3, node1, node3, 6);
    std::set<const CXXGRAPH::Edge<int> *> edgeSet;
    edgeSet.insert(&edge1);
    edgeSet.insert(&edge2);
    edgeSet.insert(&edge3);
    CXXGRAPH::Graph<int> graph(edgeSet);
    std::vector<CXXGRAPH::Node<int>> res = graph.breadth_first_search(node1);
    ASSERT_EQ(res.size(), 3);
    ASSERT_TRUE(std::find(res.begin(), res.end(), node1) != res.end());
    ASSERT_TRUE(std::find(res.begin(), res.end(), node2) != res.end());
    ASSERT_TRUE(std::find(res.begin(), res.end(), node3) != res.end());

}

TEST(BFSTest, test_2)
{
    CXXGRAPH::Node<int> node1("1", 1);
    CXXGRAPH::Node<int> node2("2", 2);
    CXXGRAPH::Node<int> node3("3", 3);
    std::pair<const CXXGRAPH::Node<int> *, const CXXGRAPH::Node<int> *> pairNode(&node1, &node2);
    CXXGRAPH::DirectedWeightedEdge<int> edge1(1, pairNode, 1);
    CXXGRAPH::DirectedWeightedEdge<int> edge2(2, node2, node3, 1);
    CXXGRAPH::DirectedWeightedEdge<int> edge3(3, node1, node3, 6);
    std::set<const CXXGRAPH::Edge<int> *> edgeSet;
    edgeSet.insert(&edge1);
    edgeSet.insert(&edge2);
    edgeSet.insert(&edge3);
    CXXGRAPH::Graph<int> graph(edgeSet);
    std::vector<CXXGRAPH::Node<int>> res = graph.breadth_first_search(node2);
    ASSERT_EQ(res.size(), 2);
    ASSERT_FALSE(std::find(res.begin(), res.end(), node1) != res.end());
    ASSERT_TRUE(std::find(res.begin(), res.end(), node2) != res.end());
    ASSERT_TRUE(std::find(res.begin(), res.end(), node3) != res.end());

}

TEST(BFSTest, test_3)
{
    CXXGRAPH::Node<int> node1("1", 1);
    CXXGRAPH::Node<int> node2("2", 2);
    CXXGRAPH::Node<int> node3("3", 3);
    std::pair<const CXXGRAPH::Node<int> *, const CXXGRAPH::Node<int> *> pairNode(&node1, &node2);
    CXXGRAPH::DirectedWeightedEdge<int> edge1(1, pairNode, 1);
    CXXGRAPH::DirectedWeightedEdge<int> edge2(2, node2, node3, 1);
    CXXGRAPH::UndirectedWeightedEdge<int> edge3(3, node1, node3, 6);
    std::set<const CXXGRAPH::Edge<int> *> edgeSet;
    edgeSet.insert(&edge1);
    edgeSet.insert(&edge2);
    edgeSet.insert(&edge3);
    CXXGRAPH::Graph<int> graph(edgeSet);
    std::vector<CXXGRAPH::Node<int>> res = graph.breadth_first_search(node2);
    ASSERT_EQ(res.size(), 3);
    ASSERT_TRUE(std::find(res.begin(), res.end(), node1) != res.end());
    ASSERT_TRUE(std::find(res.begin(), res.end(), node2) != res.end());
    ASSERT_TRUE(std::find(res.begin(), res.end(), node3) != res.end());
}

TEST(BFSTest, test_4)
{
    CXXGRAPH::Node<int> node1("1", 1);
    CXXGRAPH::Node<int> node2("2", 2);
    CXXGRAPH::Node<int> node3("3", 3);
    std::pair<const CXXGRAPH::Node<int> *, const CXXGRAPH::Node<int> *> pairNode(&node1, &node2);
    CXXGRAPH::DirectedWeightedEdge<int> edge1(1, pairNode, 1);
    CXXGRAPH::DirectedWeightedEdge<int> edge2(2, node2, node3, 1);
    CXXGRAPH::UndirectedWeightedEdge<int> edge3(3, node1, node3, 6);
    std::set<const CXXGRAPH::Edge<int> *> edgeSet;
    edgeSet.insert(&edge1);
    edgeSet.insert(&edge2);
    edgeSet.insert(&edge3);
    CXXGRAPH::Graph<int> graph(edgeSet);
    std::vector<CXXGRAPH::Node<int>> res = graph.breadth_first_search(node3);
    ASSERT_EQ(res.size(), 3);
    ASSERT_TRUE(std::find(res.begin(), res.end(), node1) != res.end());
    ASSERT_TRUE(std::find(res.begin(), res.end(), node2) != res.end());
    ASSERT_TRUE(std::find(res.begin(), res.end(), node3) != res.end());

}

TEST(BFSTest, test_5)
{
    CXXGRAPH::Node<int> node1("1", 1);
    CXXGRAPH::Node<int> node2("2", 2);
    CXXGRAPH::Node<int> node3("3", 3);
    std::pair<const CXXGRAPH::Node<int> *, const CXXGRAPH::Node<int> *> pairNode(&node1, &node2);
    CXXGRAPH::DirectedWeightedEdge<int> edge1(1, pairNode, 1);
    CXXGRAPH::DirectedWeightedEdge<int> edge2(2, node2, node3, 1);
    CXXGRAPH::DirectedWeightedEdge<int> edge3(3, node1, node3, 6);
    std::set<const CXXGRAPH::Edge<int> *> edgeSet;
    edgeSet.insert(&edge1);
    edgeSet.insert(&edge2);
    edgeSet.insert(&edge3);
    CXXGRAPH::Graph<int> graph(edgeSet);
    std::vector<CXXGRAPH::Node<int>> res = graph.breadth_first_search(node3);
    ASSERT_EQ(res.size(), 1);
    ASSERT_FALSE(std::find(res.begin(), res.end(), node1) != res.end());
    ASSERT_FALSE(std::find(res.begin(), res.end(), node2) != res.end());
    ASSERT_TRUE(std::find(res.begin(), res.end(), node3) != res.end());

}

TEST(BFSTest, test_6)
{
    CXXGRAPH::Node<int> node1("1", 1);
    CXXGRAPH::Node<int> node2("2", 2);
    CXXGRAPH::Node<int> node3("3", 3);
    CXXGRAPH::Node<int> node4("4", 4);
    std::pair<const CXXGRAPH::Node<int> *, const CXXGRAPH::Node<int> *> pairNode(&node1, &node2);
    CXXGRAPH::DirectedWeightedEdge<int> edge1(1, pairNode, 1);
    CXXGRAPH::DirectedWeightedEdge<int> edge2(2, node2, node3, 1);
    CXXGRAPH::DirectedWeightedEdge<int> edge3(3, node1, node3, 6);
    std::set<const CXXGRAPH::Edge<int> *> edgeSet;
    edgeSet.insert(&edge1);
    edgeSet.insert(&edge2);
    edgeSet.insert(&edge3);
    CXXGRAPH::Graph<int> graph(edgeSet);
    std::vector<CXXGRAPH::Node<int>> res = graph.breadth_first_search(node4);
    ASSERT_EQ(res.size(), 0);
    ASSERT_FALSE(std::find(res.begin(), res.end(), node1) != res.end());
    ASSERT_FALSE(std::find(res.begin(), res.end(), node2) != res.end());
    ASSERT_FALSE(std::find(res.begin(), res.end(), node3) != res.end());
    ASSERT_FALSE(std::find(res.begin(), res.end(), node4) != res.end());

}