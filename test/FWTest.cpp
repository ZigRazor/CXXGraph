#include "gtest/gtest.h"
#include "CXXGraph.hpp"
#include <map>

// https://en.wikipedia.org/wiki/Floyd%E2%80%93Warshall_algorithm#Example
TEST(FWTest, test_1)
{
    CXXGRAPH::Node<int> node1("1", 1);
    CXXGRAPH::Node<int> node2("2", 2);
    CXXGRAPH::Node<int> node3("3", 3);
    CXXGRAPH::Node<int> node4("4", 4);

    CXXGRAPH::DirectedWeightedEdge<int> edge1(1, node2, node1, 4);
    CXXGRAPH::DirectedWeightedEdge<int> edge2(2, node1, node3, -2);
    CXXGRAPH::DirectedWeightedEdge<int> edge3(3, node3, node4, 2);
    CXXGRAPH::DirectedWeightedEdge<int> edge4(4, node4, node2, -1);
    CXXGRAPH::DirectedWeightedEdge<int> edge5(3, node2, node3, 3);

    std::list<const CXXGRAPH::Edge<int> *> edgeSet;
    edgeSet.push_back(&edge1);
    edgeSet.push_back(&edge2);
    edgeSet.push_back(&edge3);
    edgeSet.push_back(&edge4);
    edgeSet.push_back(&edge5);

    CXXGRAPH::Graph<int> graph(edgeSet);
    CXXGRAPH::FWResult res = graph.floydWarshall();

    std::unordered_map<std::pair<std::string, std::string>, double, CXXGRAPH::pair_hash> pairwise_dist;
    auto key = std::make_pair(node1.getUserId(), node1.getUserId());
    auto nodeSet = graph.getNodeSet();
    double values[4][4] = {{0, -1, -2, 0}, {4, 0, 2, 4}, {5, 1, 0, 2}, {3, -1, 1, 0}};
    int row(0), col(0);
    for (const auto& elem1 : nodeSet)
    {
        col = 0;
        for (const auto& elem2 : nodeSet)
        {
            auto key = std::make_pair(elem1->getUserId(), elem2->getUserId());
            pairwise_dist[key] = values[row][col];
            col += 1;
        }
        row += 1;
    }
    auto isEqual = pairwise_dist.size() == res.result.size() && std::equal(pairwise_dist.begin(), pairwise_dist.end(), res.result.begin(),
                                                                           [](auto a, auto b)
                                                                           { return a.first == b.first; });

    ASSERT_TRUE(res.success);
    ASSERT_FALSE(res.negativeCycle);
    ASSERT_TRUE(isEqual);
    ASSERT_EQ(res.errorMessage, "");

    CXXGRAPH::Graph_TS<int> graph_ts(edgeSet);

    CXXGRAPH::FWResult res_ts = graph_ts.floydWarshall();
    isEqual = pairwise_dist.size() == res_ts.result.size() && std::equal(pairwise_dist.begin(), pairwise_dist.end(), res_ts.result.begin(),
                                                                           [](auto a, auto b)
                                                                           { return a.first == b.first; });

    ASSERT_TRUE(res_ts.success);
    ASSERT_FALSE(res_ts.negativeCycle);
    ASSERT_TRUE(isEqual);
    ASSERT_EQ(res_ts.errorMessage, "");

}

// a graph with negative cycle
TEST(FWTest, test_2)
{
    CXXGRAPH::Node<int> node0("0", 0);
    CXXGRAPH::Node<int> node1("1", 1);
    CXXGRAPH::Node<int> node2("2", 2);
    CXXGRAPH::DirectedWeightedEdge<int> edge1(1, node0, node1, 2);
    CXXGRAPH::DirectedWeightedEdge<int> edge2(2, node1, node2, 3);
    CXXGRAPH::DirectedWeightedEdge<int> edge3(3, node2, node0, -7);
    std::list<const CXXGRAPH::Edge<int> *> edgeSet;
    edgeSet.push_back(&edge1);
    edgeSet.push_back(&edge2);
    edgeSet.push_back(&edge3);
    CXXGRAPH::Graph<int> graph(edgeSet);
    CXXGRAPH::FWResult res = graph.floydWarshall();
    ASSERT_TRUE(res.success);
    ASSERT_TRUE(res.negativeCycle);
    ASSERT_EQ(res.errorMessage, "");

    CXXGRAPH::Graph_TS<int> graph_ts(edgeSet);

    CXXGRAPH::FWResult res_ts = graph_ts.floydWarshall();
    ASSERT_TRUE(res_ts.success);
    ASSERT_TRUE(res_ts.negativeCycle);
    ASSERT_EQ(res_ts.errorMessage, "");

}

// UndirectedWeightedEdge
TEST(FWTest, test_3)
{
    CXXGRAPH::Node<int> node1("1", 1);
    CXXGRAPH::Node<int> node2("2", 2);
    CXXGRAPH::Node<int> node3("3", 3);
    std::pair<const CXXGRAPH::Node<int> *, const CXXGRAPH::Node<int> *> pairNode(&node1, &node2);
    CXXGRAPH::DirectedWeightedEdge<int> edge1(1, pairNode, 1);
    CXXGRAPH::DirectedWeightedEdge<int> edge2(2, node2, node3, 1);
    CXXGRAPH::UndirectedWeightedEdge<int> edge3(3, node1, node3, 6);
    std::list<const CXXGRAPH::Edge<int> *> edgeSet;
    edgeSet.push_back(&edge1);
    edgeSet.push_back(&edge2);
    edgeSet.push_back(&edge3);
    CXXGRAPH::Graph<int> graph(edgeSet);
    CXXGRAPH::FWResult res = graph.floydWarshall();
    ASSERT_TRUE(res.success);
    ASSERT_FALSE(res.negativeCycle);
    ASSERT_EQ(res.errorMessage, "");

    CXXGRAPH::Graph_TS<int> graph_ts(edgeSet);

    CXXGRAPH::FWResult res_ts = graph_ts.floydWarshall();
    ASSERT_TRUE(res_ts.success);
    ASSERT_FALSE(res_ts.negativeCycle);
    ASSERT_EQ(res_ts.errorMessage, "");
}

// No weighted edge
TEST(FWTest, test_4)
{
    CXXGRAPH::Node<int> node1("1", 1);
    CXXGRAPH::Node<int> node2("2", 2);
    CXXGRAPH::Node<int> node3("3", 3);
    std::pair<const CXXGRAPH::Node<int> *, const CXXGRAPH::Node<int> *> pairNode(&node1, &node2);
    CXXGRAPH::DirectedWeightedEdge<int> edge1(1, pairNode, 1);
    CXXGRAPH::DirectedWeightedEdge<int> edge2(2, node2, node3, 1);
    CXXGRAPH::DirectedEdge<int> edge3(3, node1, node3);
    std::list<const CXXGRAPH::Edge<int> *> edgeSet;
    edgeSet.push_back(&edge1);
    edgeSet.push_back(&edge2);
    edgeSet.push_back(&edge3);
    CXXGRAPH::Graph<int> graph(edgeSet);
    CXXGRAPH::FWResult res = graph.floydWarshall();
    ASSERT_FALSE(res.success);
    ASSERT_EQ(res.errorMessage, CXXGRAPH::ERR_NO_WEIGHTED_EDGE);

    CXXGRAPH::Graph_TS<int> graph_ts(edgeSet);

    CXXGRAPH::FWResult res_ts = graph_ts.floydWarshall();
    ASSERT_FALSE(res_ts.success);
    ASSERT_EQ(res_ts.errorMessage, CXXGRAPH::ERR_NO_WEIGHTED_EDGE);
}