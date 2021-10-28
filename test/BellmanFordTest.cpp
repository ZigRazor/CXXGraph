#include "gtest/gtest.h"
#include "CXXGraph.hpp"

// check if algorithm works using a complicated test case
TEST(BellmanFordTest, test_1)
{
    CXXGRAPH::Node<int> node0("0", 0);
    CXXGRAPH::Node<int> node1("1", 1);
    CXXGRAPH::Node<int> node2("2", 2);
    CXXGRAPH::Node<int> node3("3", 3);
    CXXGRAPH::Node<int> node4("4", 4);

    CXXGRAPH::DirectedWeightedEdge<int> edge1(1, node0, node1, 6);
    CXXGRAPH::DirectedWeightedEdge<int> edge2(1, node0, node2, 7);

    CXXGRAPH::DirectedWeightedEdge<int> edge3(1, node1, node2, 8);
    CXXGRAPH::DirectedWeightedEdge<int> edge4(1, node1, node3, -4);
    CXXGRAPH::DirectedWeightedEdge<int> edge5(1, node1, node4, 5);


    CXXGRAPH::DirectedWeightedEdge<int> edge6(1, node2, node4, -3);
    CXXGRAPH::DirectedWeightedEdge<int> edge7(1, node2, node3, 9);

    CXXGRAPH::DirectedWeightedEdge<int> edge8(1, node3, node4, 7);
    CXXGRAPH::DirectedWeightedEdge<int> edge9(1, node3, node0, 2);

    CXXGRAPH::DirectedWeightedEdge<int> edge10(1, node4, node1, -2);
    std::list<const CXXGRAPH::Edge<int> *> edgeSet;
    edgeSet.push_back(&edge1);
    edgeSet.push_back(&edge2);
    edgeSet.push_back(&edge3);
    edgeSet.push_back(&edge4);
    edgeSet.push_back(&edge5);
    edgeSet.push_back(&edge6);
    edgeSet.push_back(&edge7);
    edgeSet.push_back(&edge8);
    edgeSet.push_back(&edge9);
    edgeSet.push_back(&edge10);

    CXXGRAPH::Graph<int> graph(edgeSet);
    CXXGRAPH::BellmanFordResult res = graph.bellmanford(node0, node3);
    ASSERT_TRUE(res.success);
    ASSERT_FALSE(res.negativeCycle);
    ASSERT_EQ(res.errorMessage, "");
    ASSERT_EQ(res.result, -2);

    CXXGRAPH::Graph_TS<int> graph_ts(edgeSet);
    CXXGRAPH::BellmanFordResult res_ts = graph_ts.bellmanford(node0, node3);
    ASSERT_TRUE(res_ts.success);
    ASSERT_FALSE(res_ts.negativeCycle);
    ASSERT_EQ(res_ts.errorMessage, "");
    ASSERT_EQ(res_ts.result, -2);
}

// a graph with negative cycle
TEST(BellmanFordTest, test_2)
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
    CXXGRAPH::BellmanFordResult res = graph.bellmanford(node0, node2);
    ASSERT_TRUE(res.success);
    ASSERT_TRUE(res.negativeCycle);
    ASSERT_EQ(res.errorMessage, "");
    ASSERT_EQ(res.result, CXXGRAPH::INF_DOUBLE);

    CXXGRAPH::Graph_TS<int> graph_ts(edgeSet);
    CXXGRAPH::BellmanFordResult res_ts = graph_ts.bellmanford(node0, node2);
    ASSERT_TRUE(res_ts.success);
    ASSERT_TRUE(res_ts.negativeCycle);
    ASSERT_EQ(res_ts.errorMessage, "");
    ASSERT_EQ(res_ts.result, CXXGRAPH::INF_DOUBLE);
}

// UndirectedWeightedEdge
TEST(BellmanFordTest, test_3)
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
    CXXGRAPH::BellmanFordResult res = graph.bellmanford(node1, node3);
    ASSERT_TRUE(res.success);
    ASSERT_FALSE(res.negativeCycle);
    ASSERT_EQ(res.errorMessage, "");
    ASSERT_EQ(res.result, 2);

    CXXGRAPH::Graph_TS<int> graph_ts(edgeSet);
    CXXGRAPH::BellmanFordResult res_ts = graph_ts.bellmanford(node1, node3);
    ASSERT_TRUE(res_ts.success);
    ASSERT_FALSE(res_ts.negativeCycle);
    ASSERT_EQ(res_ts.errorMessage, "");
    ASSERT_EQ(res_ts.result, 2);

}

// No weighted edge
TEST(BellmanFordTest, test_4)
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
    CXXGRAPH::BellmanFordResult res = graph.bellmanford(node1, node3);
    ASSERT_FALSE(res.success);
    ASSERT_FALSE(res.negativeCycle);
    ASSERT_EQ(res.errorMessage, CXXGRAPH::ERR_NO_WEIGHTED_EDGE);
    ASSERT_EQ(res.result, CXXGRAPH::INF_DOUBLE);

    CXXGRAPH::Graph_TS<int> graph_ts(edgeSet);
    CXXGRAPH::BellmanFordResult res_ts = graph_ts.bellmanford(node1, node3);
    ASSERT_FALSE(res_ts.success);
    ASSERT_FALSE(res_ts.negativeCycle);
    ASSERT_EQ(res_ts.errorMessage, CXXGRAPH::ERR_NO_WEIGHTED_EDGE);
    ASSERT_EQ(res_ts.result, CXXGRAPH::INF_DOUBLE);
}


// ERR_SOURCE_NODE_NOT_IN_GRAPH 
// ERR_TARGET_NODE_NOT_IN_GRAPH
// ERR_TARGET_NODE_NOT_REACHABLE
TEST(BellmanFordTest, test_5)
{
    CXXGRAPH::Node<int> node1("1", 1);
    CXXGRAPH::Node<int> node2("2", 2);
    CXXGRAPH::Node<int> node3("3", 3);
    CXXGRAPH::DirectedWeightedEdge<int> edge1(2, node1, node2, 1);
    std::list<const CXXGRAPH::Edge<int> *> edgeSet;
    edgeSet.push_back(&edge1);
    CXXGRAPH::Graph<int> graph(edgeSet);
    CXXGRAPH::BellmanFordResult res = graph.bellmanford(node3, node1);
    ASSERT_FALSE(res.success);
    ASSERT_FALSE(res.negativeCycle);
    ASSERT_EQ(res.errorMessage, CXXGRAPH::ERR_SOURCE_NODE_NOT_IN_GRAPH);
    ASSERT_EQ(res.result, CXXGRAPH::INF_DOUBLE);

    CXXGRAPH::Graph_TS<int> graph_ts(edgeSet);
    CXXGRAPH::BellmanFordResult res_ts = graph.bellmanford(node3, node1);
    ASSERT_FALSE(res_ts.success);
    ASSERT_FALSE(res_ts.negativeCycle);
    ASSERT_EQ(res_ts.errorMessage, CXXGRAPH::ERR_SOURCE_NODE_NOT_IN_GRAPH);
    ASSERT_EQ(res_ts.result, CXXGRAPH::INF_DOUBLE);

    res = graph.bellmanford(node1, node3);
    ASSERT_FALSE(res.success);
    ASSERT_FALSE(res.negativeCycle);
    ASSERT_EQ(res.errorMessage, CXXGRAPH::ERR_TARGET_NODE_NOT_IN_GRAPH);
    ASSERT_EQ(res.result, CXXGRAPH::INF_DOUBLE);

    res_ts = graph_ts.bellmanford(node1, node3);
    ASSERT_FALSE(res_ts.success);
    ASSERT_FALSE(res_ts.negativeCycle);
    ASSERT_EQ(res_ts.errorMessage, CXXGRAPH::ERR_TARGET_NODE_NOT_IN_GRAPH);
    ASSERT_EQ(res_ts.result, CXXGRAPH::INF_DOUBLE);

    CXXGRAPH::DirectedWeightedEdge<int> edge2(2, node3, node2, 1);
    edgeSet.push_back(&edge2);

    CXXGRAPH::Graph<int> graph1(edgeSet);
    res = graph1.bellmanford(node1, node3);
    ASSERT_FALSE(res.success);
    ASSERT_FALSE(res.negativeCycle);
    ASSERT_EQ(res.errorMessage, CXXGRAPH::ERR_TARGET_NODE_NOT_REACHABLE);
    ASSERT_EQ(res.result, -1);

    CXXGRAPH::Graph<int> graph1_ts(edgeSet);
    res_ts = graph1_ts.bellmanford(node1, node3);
    ASSERT_FALSE(res_ts.success);
    ASSERT_FALSE(res_ts.negativeCycle);
    ASSERT_EQ(res_ts.errorMessage, CXXGRAPH::ERR_TARGET_NODE_NOT_REACHABLE);
    ASSERT_EQ(res_ts.result, -1);

}

