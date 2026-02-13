#include <memory>
#include <string>
#include <utility>
#include <vector>

#include "CXXGraph/CXXGraph.hpp"
#include "gtest/gtest.h"


// Smart pointers alias
template <typename T>
using unique = std::unique_ptr<T>;
template <typename T>
using shared = std::shared_ptr<T>;

using std::make_shared;
using std::make_unique;

// helper: does the bridges vector contain an edge between a and b?
static bool has_bridge(
    const std::vector<std::pair<CXXGraph::Node<int>, CXXGraph::Node<int>>> &bridges,
    const CXXGraph::Node<int> &a,
    const CXXGraph::Node<int> &b) {

    return std::any_of(
        bridges.begin(), bridges.end(),
        [&a, &b](const auto &e) {
            return  (e.first  == a && e.second == b) ||
                    (e.first  == b && e.second == a);
        });
}

/*
Test 1: 1 -- 2 -- 3

All edges are bridges
*/
TEST(BridgesTest, Chain_AllEdgesAreBridges) {
    using namespace CXXGraph;

    // Nodes
    Node<int> node1("1", 1);
    Node<int> node2("2", 2);
    Node<int> node3("3", 3);

    // Undirected edges
    UndirectedWeightedEdge<int> e1("e1", node1, node2, 1);
    UndirectedWeightedEdge<int> e2("e2", node2, node3, 1);

    T_EdgeSet<int> edgeSet;
    edgeSet.insert(make_shared<UndirectedWeightedEdge<int>>(e1));
    edgeSet.insert(make_shared<UndirectedWeightedEdge<int>>(e2));

    Graph<int> graph(edgeSet);

    auto bridge = graph.bridges(node1);

    // Expected bridges
    ASSERT_TRUE(has_bridge(bridge, node1, node2));
    ASSERT_TRUE(has_bridge(bridge, node2, node3));
}

/*
Test 2:
   1
  / \
 2---3---4

(3,4) is the only bridge
 */
TEST(BridgesTest, TrianglePlusTail_OnlyTailIsBridge) {
    using namespace CXXGraph;

    // Nodes
    Node<int> node1("1", 1);
    Node<int> node2("2", 2);
    Node<int> node3("3", 3);
    Node<int> node4("4", 4);

    // Undirected edges
    UndirectedWeightedEdge<int> e1("e1", node1, node2, 1);
    UndirectedWeightedEdge<int> e2("e2", node2, node3, 1);
    UndirectedWeightedEdge<int> e3("e3", node1, node3, 1);
    UndirectedWeightedEdge<int> e4("e4", node3, node4, 1);

    T_EdgeSet<int> edgeSet;
    edgeSet.insert(make_shared<UndirectedWeightedEdge<int>>(e1));
    edgeSet.insert(make_shared<UndirectedWeightedEdge<int>>(e2));
    edgeSet.insert(make_shared<UndirectedWeightedEdge<int>>(e3));
    edgeSet.insert(make_shared<UndirectedWeightedEdge<int>>(e4));

    Graph<int> graph(edgeSet);

    auto bridge = graph.bridges(node1);

    // Only (3,4) should be a bridge
    ASSERT_EQ(bridge.size(), 1u);
    ASSERT_TRUE(has_bridge(bridge, node3, node4));

    // All other edges should NOT be bridges
    ASSERT_FALSE(has_bridge(bridge, node1, node2));
    ASSERT_FALSE(has_bridge(bridge, node2, node3));
    ASSERT_FALSE(has_bridge(bridge, node1, node3));
}


