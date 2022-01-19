#include "gtest/gtest.h"
#include "CXXGraph.hpp"

TEST(DijkstraTest, correct_example_1)
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
    CXXGRAPH::DijkstraResult res = graph.dijkstra(node1, node3);
    ASSERT_TRUE(res.success);
    ASSERT_EQ(res.errorMessage, "");
    ASSERT_EQ(res.result, 2);

    CXXGRAPH::Graph_TS<int> graph_ts(edgeSet);
    CXXGRAPH::DijkstraResult res_ts = graph_ts.dijkstra(node1, node3);
    ASSERT_TRUE(res_ts.success);
    ASSERT_EQ(res_ts.errorMessage, "");
    ASSERT_EQ(res_ts.result, 2);
}

TEST(DijkstraTest, correct_example_2)
{
    CXXGRAPH::Node<int> node1("1", 1);
    CXXGRAPH::Node<int> node2("2", 2);
    CXXGRAPH::Node<int> node3("3", 3);

    std::pair<const CXXGRAPH::Node<int> *, const CXXGRAPH::Node<int> *> pairNode(&node1, &node2);
    CXXGRAPH::DirectedWeightedEdge<int> edge1(1, pairNode, 5);
    CXXGRAPH::DirectedWeightedEdge<int> edge2(2, node2, node3, 4);
    CXXGRAPH::UndirectedWeightedEdge<int> edge3(3, node1, node3, 6);

    std::list<const CXXGRAPH::Edge<int> *> edgeSet;
    edgeSet.push_back(&edge1);
    edgeSet.push_back(&edge2);
    edgeSet.push_back(&edge3);

    CXXGRAPH::Graph<int> graph(edgeSet);
    CXXGRAPH::DijkstraResult res = graph.dijkstra(node1, node3);
    ASSERT_TRUE(res.success);
    ASSERT_EQ(res.errorMessage, "");
    ASSERT_EQ(res.result, 6);

    CXXGRAPH::Graph_TS<int> graph_ts(edgeSet);
    CXXGRAPH::DijkstraResult res_ts = graph_ts.dijkstra(node1, node3);
    ASSERT_TRUE(res_ts.success);
    ASSERT_EQ(res_ts.errorMessage, "");
    ASSERT_EQ(res_ts.result, 6);
}

TEST(DijkstraTest, correct_example_3)
{
	// Example from https://www.analyticssteps.com/blogs/dijkstras-algorithm-shortest-path-algorithm
	CXXGRAPH::Node<int> nodeA("A", 1);
	CXXGRAPH::Node<int> nodeB("B", 1);
	CXXGRAPH::Node<int> nodeC("C", 1);
	CXXGRAPH::Node<int> nodeD("D", 1);
	CXXGRAPH::Node<int> nodeE("E", 1);

	CXXGRAPH::UndirectedWeightedEdge<int> edge1(1, nodeA, nodeB, 3);
	CXXGRAPH::UndirectedWeightedEdge<int> edge2(2, nodeA, nodeC, 1);
	CXXGRAPH::UndirectedWeightedEdge<int> edge3(3, nodeB, nodeC, 7);
	CXXGRAPH::UndirectedWeightedEdge<int> edge4(4, nodeC, nodeD, 2);
	CXXGRAPH::UndirectedWeightedEdge<int> edge5(5, nodeB, nodeE, 1);
	CXXGRAPH::UndirectedWeightedEdge<int> edge6(6, nodeB, nodeD, 5);
	CXXGRAPH::UndirectedWeightedEdge<int> edge7(7, nodeD, nodeE, 7);

	std::list<const CXXGRAPH::Edge<int> *> edgeSet;
	edgeSet.push_back(&edge1);
	edgeSet.push_back(&edge2);
	edgeSet.push_back(&edge3);
	edgeSet.push_back(&edge4);
	edgeSet.push_back(&edge5);
	edgeSet.push_back(&edge6);
	edgeSet.push_back(&edge7);

	CXXGRAPH::Graph<int> graph(edgeSet);
	CXXGRAPH::DijkstraResult res = graph.dijkstra(nodeC, nodeE);
	ASSERT_TRUE(res.success);
	ASSERT_EQ(res.errorMessage, "");
	ASSERT_EQ(res.result, 5);
	res = graph.dijkstra(nodeC, nodeA);
	ASSERT_TRUE(res.success);
	ASSERT_EQ(res.errorMessage, "");
	ASSERT_EQ(res.result, 1);
	res = graph.dijkstra(nodeC, nodeB);
	ASSERT_TRUE(res.success);
	ASSERT_EQ(res.errorMessage, "");
	ASSERT_EQ(res.result, 4);
	res = graph.dijkstra(nodeC, nodeD);
	ASSERT_TRUE(res.success);
	ASSERT_EQ(res.errorMessage, "");
	ASSERT_EQ(res.result, 2);

	CXXGRAPH::Graph_TS<int> graph_ts(edgeSet);
	CXXGRAPH::DijkstraResult res_ts = graph_ts.dijkstra(nodeC, nodeE);
	ASSERT_TRUE(res_ts.success);
	ASSERT_EQ(res_ts.errorMessage, "");
	ASSERT_EQ(res_ts.result, 5);
	res_ts = graph_ts.dijkstra(nodeC, nodeA);
	ASSERT_TRUE(res_ts.success);
	ASSERT_EQ(res_ts.errorMessage, "");
	ASSERT_EQ(res_ts.result, 1);
	res_ts = graph_ts.dijkstra(nodeC, nodeB);
	ASSERT_TRUE(res_ts.success);
	ASSERT_EQ(res_ts.errorMessage, "");
	ASSERT_EQ(res_ts.result, 4);
	res_ts = graph_ts.dijkstra(nodeC, nodeD);
	ASSERT_TRUE(res_ts.success);
	ASSERT_EQ(res_ts.errorMessage, "");
	ASSERT_EQ(res_ts.result, 2);
}

TEST(DijkstraTest, correct_example_4)
{
	// Example from https://www.freecodecamp.org/news/dijkstras-shortest-path-algorithm-visual-introduction/
	CXXGRAPH::Node<int> node0("0", 1);
	CXXGRAPH::Node<int> node1("1", 1);
	CXXGRAPH::Node<int> node2("2", 1);
	CXXGRAPH::Node<int> node3("3", 1);
	CXXGRAPH::Node<int> node4("4", 1);
	CXXGRAPH::Node<int> node5("5", 1);
	CXXGRAPH::Node<int> node6("6", 1);

	CXXGRAPH::UndirectedWeightedEdge<int> edge1(1, node0, node1, 2);
	CXXGRAPH::UndirectedWeightedEdge<int> edge2(2, node0, node2, 6);
	CXXGRAPH::UndirectedWeightedEdge<int> edge3(3, node1, node3, 5);
	CXXGRAPH::UndirectedWeightedEdge<int> edge4(4, node2, node3, 8);
	CXXGRAPH::UndirectedWeightedEdge<int> edge5(5, node3, node5, 15);
	CXXGRAPH::UndirectedWeightedEdge<int> edge6(6, node3, node4, 10);
	CXXGRAPH::UndirectedWeightedEdge<int> edge7(7, node4, node5, 6);
	CXXGRAPH::UndirectedWeightedEdge<int> edge8(8, node4, node6, 2);
	CXXGRAPH::UndirectedWeightedEdge<int> edge9(9, node5, node6, 6);

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

	CXXGRAPH::Graph<int> graph(edgeSet);
	CXXGRAPH::DijkstraResult res = graph.dijkstra(node0, node1);
	ASSERT_TRUE(res.success);
	ASSERT_EQ(res.errorMessage, "");
	ASSERT_EQ(res.result, 2);
	res = graph.dijkstra(node0, node2);
	ASSERT_TRUE(res.success);
	ASSERT_EQ(res.errorMessage, "");
	ASSERT_EQ(res.result, 6);
	res = graph.dijkstra(node0, node3);
	ASSERT_TRUE(res.success);
	ASSERT_EQ(res.errorMessage, "");
	ASSERT_EQ(res.result, 7);
	res = graph.dijkstra(node0, node4);
	ASSERT_TRUE(res.success);
	ASSERT_EQ(res.errorMessage, "");
	ASSERT_EQ(res.result, 17);
	res = graph.dijkstra(node0, node5);
	ASSERT_TRUE(res.success);
	ASSERT_EQ(res.errorMessage, "");
	ASSERT_EQ(res.result, 22);
	res = graph.dijkstra(node0, node6);
	ASSERT_TRUE(res.success);
	ASSERT_EQ(res.errorMessage, "");
	ASSERT_EQ(res.result, 19);

	CXXGRAPH::Graph_TS<int> graph_ts(edgeSet);
	CXXGRAPH::DijkstraResult res_ts = graph_ts.dijkstra(node0, node1);
	ASSERT_TRUE(res_ts.success);
	ASSERT_EQ(res_ts.errorMessage, "");
	ASSERT_EQ(res_ts.result, 2);
	res_ts = graph_ts.dijkstra(node0, node2);
	ASSERT_TRUE(res_ts.success);
	ASSERT_EQ(res_ts.errorMessage, "");
	ASSERT_EQ(res_ts.result, 6);
	res_ts = graph_ts.dijkstra(node0, node3);
	ASSERT_TRUE(res_ts.success);
	ASSERT_EQ(res_ts.errorMessage, "");
	ASSERT_EQ(res_ts.result, 7);
	res_ts = graph_ts.dijkstra(node0, node4);
	ASSERT_TRUE(res_ts.success);
	ASSERT_EQ(res_ts.errorMessage, "");
	ASSERT_EQ(res_ts.result, 17);
	res_ts = graph_ts.dijkstra(node0, node5);
	ASSERT_TRUE(res_ts.success);
	ASSERT_EQ(res_ts.errorMessage, "");
	ASSERT_EQ(res_ts.result, 22);
	res_ts = graph_ts.dijkstra(node0, node6);
	ASSERT_TRUE(res_ts.success);
	ASSERT_EQ(res_ts.errorMessage, "");
	ASSERT_EQ(res_ts.result, 19);
}

TEST(DijkstraTest, correct_example_5)
{
	// Example from https://es.wikipedia.org/wiki/Algoritmo_de_Dijkstra
	CXXGRAPH::Node<int> node1("1", 1);
	CXXGRAPH::Node<int> node2("2", 1);
	CXXGRAPH::Node<int> node3("3", 1);
	CXXGRAPH::Node<int> node4("4", 1);
	CXXGRAPH::Node<int> node5("5", 1);
	CXXGRAPH::Node<int> node6("6", 1);

	CXXGRAPH::UndirectedWeightedEdge<int> edge1(1, node1, node2, 7);
	CXXGRAPH::UndirectedWeightedEdge<int> edge2(2, node1, node3, 9);
	CXXGRAPH::UndirectedWeightedEdge<int> edge3(3, node1, node6, 14);
	CXXGRAPH::UndirectedWeightedEdge<int> edge4(4, node2, node4, 15);
	CXXGRAPH::UndirectedWeightedEdge<int> edge5(5, node2, node3, 10);
	CXXGRAPH::UndirectedWeightedEdge<int> edge6(6, node3, node4, 11);
	CXXGRAPH::UndirectedWeightedEdge<int> edge7(7, node3, node6, 2);
	CXXGRAPH::UndirectedWeightedEdge<int> edge8(8, node4, node5, 6);
	CXXGRAPH::UndirectedWeightedEdge<int> edge9(9, node6, node5, 9);

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

	CXXGRAPH::Graph<int> graph(edgeSet);
	CXXGRAPH::DijkstraResult res = graph.dijkstra(node1, node5);
	ASSERT_TRUE(res.success);
	ASSERT_EQ(res.errorMessage, "");
	ASSERT_EQ(res.result, 20);

	CXXGRAPH::Graph_TS<int> graph_ts(edgeSet);
	CXXGRAPH::DijkstraResult res_ts = graph_ts.dijkstra(node1, node5);
	ASSERT_TRUE(res_ts.success);
	ASSERT_EQ(res_ts.errorMessage, "");
	ASSERT_EQ(res_ts.result, 20);
}

TEST(DijkstraTest, non_weigthed_node_test)
{
    CXXGRAPH::Node<int> node1("1", 1);
    CXXGRAPH::Node<int> node2("2", 2);
    CXXGRAPH::Node<int> node3("3", 3);

    std::pair<const CXXGRAPH::Node<int> *, const CXXGRAPH::Node<int> *> pairNode(&node1, &node2);
    CXXGRAPH::DirectedWeightedEdge<int> edge1(1, pairNode, 5);
    CXXGRAPH::DirectedEdge<int> edge2(2, node2, node3);
    CXXGRAPH::UndirectedWeightedEdge<int> edge3(3, node1, node3, 6);

    std::list<const CXXGRAPH::Edge<int> *> edgeSet;
    edgeSet.push_back(&edge1);
    edgeSet.push_back(&edge2);
    edgeSet.push_back(&edge3);

    CXXGRAPH::Graph<int> graph(edgeSet);
    CXXGRAPH::DijkstraResult res = graph.dijkstra(node1, node3);
    ASSERT_FALSE(res.success);
    ASSERT_EQ(res.errorMessage, CXXGRAPH::ERR_NO_WEIGHTED_EDGE);
    ASSERT_EQ(res.result, CXXGRAPH::INF_DOUBLE);

    CXXGRAPH::Graph_TS<int> graph_ts(edgeSet);
    CXXGRAPH::DijkstraResult res_ts = graph_ts.dijkstra(node1, node3);
    ASSERT_FALSE(res_ts.success);
    ASSERT_EQ(res_ts.errorMessage, CXXGRAPH::ERR_NO_WEIGHTED_EDGE);
    ASSERT_EQ(res_ts.result, CXXGRAPH::INF_DOUBLE);
}

TEST(DijkstraTest, negative_weigthed_node_test)
{
	CXXGRAPH::Node<int> node1("1", 1);
	CXXGRAPH::Node<int> node2("2", 2);
	CXXGRAPH::Node<int> node3("3", 3);

	std::pair<const CXXGRAPH::Node<int> *, const CXXGRAPH::Node<int> *> pairNode(&node1, &node2);
	CXXGRAPH::DirectedWeightedEdge<int> edge1(1, pairNode, -5);
	CXXGRAPH::DirectedWeightedEdge<int> edge2(2, node2, node3, 5);
	CXXGRAPH::UndirectedWeightedEdge<int> edge3(3, node1, node3, 6);

	std::list<const CXXGRAPH::Edge<int> *> edgeSet;
	edgeSet.push_back(&edge1);
	edgeSet.push_back(&edge2);
	edgeSet.push_back(&edge3);

	CXXGRAPH::Graph<int> graph(edgeSet);
	CXXGRAPH::DijkstraResult res = graph.dijkstra(node1, node3);
	ASSERT_FALSE(res.success);
	ASSERT_EQ(res.errorMessage, CXXGRAPH::ERR_NEGATIVE_WEIGHTED_EDGE);
	ASSERT_EQ(res.result, CXXGRAPH::INF_DOUBLE);

	CXXGRAPH::Graph_TS<int> graph_ts(edgeSet);
	CXXGRAPH::DijkstraResult res_ts = graph_ts.dijkstra(node1, node3);
	ASSERT_FALSE(res_ts.success);
	ASSERT_EQ(res_ts.errorMessage, CXXGRAPH::ERR_NEGATIVE_WEIGHTED_EDGE);
	ASSERT_EQ(res_ts.result, CXXGRAPH::INF_DOUBLE);
}

TEST(DijkstraTest, unreachable_node_test)
{
    CXXGRAPH::Node<int> node1("1", 1);
    CXXGRAPH::Node<int> node2("2", 2);
    CXXGRAPH::Node<int> node3("3", 3);

    CXXGRAPH::DirectedEdge<int> edge2(2, node2, node3);
    CXXGRAPH::UndirectedWeightedEdge<int> edge3(3, node1, node3, 6);

    std::list<const CXXGRAPH::Edge<int> *> edgeSet;
    edgeSet.push_back(&edge2);
    edgeSet.push_back(&edge3);

    CXXGRAPH::Graph<int> graph(edgeSet);
    CXXGRAPH::DijkstraResult res = graph.dijkstra(node1, node2);
    ASSERT_FALSE(res.success);
    ASSERT_EQ(res.errorMessage, CXXGRAPH::ERR_TARGET_NODE_NOT_REACHABLE);
    ASSERT_EQ(res.result, CXXGRAPH::INF_DOUBLE);

    CXXGRAPH::Graph_TS<int> graph_ts(edgeSet);
    CXXGRAPH::DijkstraResult res_ts = graph_ts.dijkstra(node1, node2);
    ASSERT_FALSE(res_ts.success);
    ASSERT_EQ(res_ts.errorMessage, CXXGRAPH::ERR_TARGET_NODE_NOT_REACHABLE);
    ASSERT_EQ(res_ts.result, CXXGRAPH::INF_DOUBLE);
}

TEST(DijkstraTest, source_not_connected_test)
{
    CXXGRAPH::Node<int> node1("1", 1);
    CXXGRAPH::Node<int> node2("2", 2);
    CXXGRAPH::Node<int> node3("3", 3);
    CXXGRAPH::Node<int> node4("4", 4);

    CXXGRAPH::DirectedEdge<int> edge2(2, node2, node3);
    CXXGRAPH::UndirectedWeightedEdge<int> edge3(3, node1, node3, 6);

    std::list<const CXXGRAPH::Edge<int> *> edgeSet;
    edgeSet.push_back(&edge2);
    edgeSet.push_back(&edge3);

    CXXGRAPH::Graph<int> graph(edgeSet);
    CXXGRAPH::DijkstraResult res = graph.dijkstra(node4, node2);
    ASSERT_FALSE(res.success);
    ASSERT_EQ(res.errorMessage, CXXGRAPH::ERR_SOURCE_NODE_NOT_IN_GRAPH);
    ASSERT_EQ(res.result, CXXGRAPH::INF_DOUBLE);

    CXXGRAPH::Graph_TS<int> graph_ts(edgeSet);
    CXXGRAPH::DijkstraResult res_ts = graph_ts.dijkstra(node4, node2);
    ASSERT_FALSE(res_ts.success);
    ASSERT_EQ(res_ts.errorMessage, CXXGRAPH::ERR_SOURCE_NODE_NOT_IN_GRAPH);
    ASSERT_EQ(res_ts.result, CXXGRAPH::INF_DOUBLE);
}

TEST(DijkstraTest, target_not_connected_test)
{
    CXXGRAPH::Node<int> node1("1", 1);
    CXXGRAPH::Node<int> node2("2", 2);
    CXXGRAPH::Node<int> node3("3", 3);
    CXXGRAPH::Node<int> node4("4", 4);

    CXXGRAPH::DirectedEdge<int> edge2(2, node2, node3);
    CXXGRAPH::UndirectedWeightedEdge<int> edge3(3, node1, node3, 6);

    std::list<const CXXGRAPH::Edge<int> *> edgeSet;
    edgeSet.push_back(&edge2);
    edgeSet.push_back(&edge3);
    
    CXXGRAPH::Graph<int> graph(edgeSet);
    CXXGRAPH::DijkstraResult res = graph.dijkstra(node1, node4);
    ASSERT_FALSE(res.success);
    ASSERT_EQ(res.errorMessage, CXXGRAPH::ERR_TARGET_NODE_NOT_IN_GRAPH);
    ASSERT_EQ(res.result, CXXGRAPH::INF_DOUBLE);

    CXXGRAPH::Graph_TS<int> graph_ts(edgeSet);
    CXXGRAPH::DijkstraResult res_ts = graph_ts.dijkstra(node1, node4);
    ASSERT_FALSE(res_ts.success);
    ASSERT_EQ(res_ts.errorMessage, CXXGRAPH::ERR_TARGET_NODE_NOT_IN_GRAPH);
    ASSERT_EQ(res_ts.result, CXXGRAPH::INF_DOUBLE);
}