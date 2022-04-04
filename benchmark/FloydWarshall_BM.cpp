#include <benchmark/benchmark.h>
#include "CXXGraph.hpp"
#include "Utilities.hpp"

// https://en.wikipedia.org/wiki/Floyd%E2%80%93Warshall_algorithm#Example
static void BM_FWDirected(benchmark::State &state)
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

    std::set<const CXXGRAPH::Edge<int> *> edgeSet;
    edgeSet.insert(&edge1);
    edgeSet.insert(&edge2);
    edgeSet.insert(&edge3);
    edgeSet.insert(&edge4);
    edgeSet.insert(&edge5);

    CXXGRAPH::Graph<int> graph(edgeSet);
    for (auto _ : state)
    {
        CXXGRAPH::FWResult res = graph.floydWarshall();
    }
}
BENCHMARK(BM_FWDirected);

// a graph with negative cycle
static void BM_FWNegCycle(benchmark::State &state)
{
    CXXGRAPH::Node<int> node0("0", 0);
    CXXGRAPH::Node<int> node1("1", 1);
    CXXGRAPH::Node<int> node2("2", 2);
    CXXGRAPH::DirectedWeightedEdge<int> edge1(1, node0, node1, 2);
    CXXGRAPH::DirectedWeightedEdge<int> edge2(2, node1, node2, 3);
    CXXGRAPH::DirectedWeightedEdge<int> edge3(3, node2, node0, -7);
    std::set<const CXXGRAPH::Edge<int> *> edgeSet;
    edgeSet.insert(&edge1);
    edgeSet.insert(&edge2);
    edgeSet.insert(&edge3);
    CXXGRAPH::Graph<int> graph(edgeSet);
    for (auto _ : state)
    {
        CXXGRAPH::FWResult res = graph.floydWarshall();
    }
}
BENCHMARK(BM_FWNegCycle);

static void BM_FWUndirectedWeighted(benchmark::State &state)
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
    for (auto _ : state)
    {
        CXXGRAPH::FWResult res = graph.floydWarshall();
    }
}
BENCHMARK(BM_FWUndirectedWeighted);

static void BM_FWNoWeighted(benchmark::State &state)
{
    CXXGRAPH::Node<int> node1("1", 1);
    CXXGRAPH::Node<int> node2("2", 2);
    CXXGRAPH::Node<int> node3("3", 3);
    std::pair<const CXXGRAPH::Node<int> *, const CXXGRAPH::Node<int> *> pairNode(&node1, &node2);
    CXXGRAPH::DirectedWeightedEdge<int> edge1(1, pairNode, 1);
    CXXGRAPH::DirectedWeightedEdge<int> edge2(2, node2, node3, 1);
    CXXGRAPH::DirectedEdge<int> edge3(3, node1, node3);
    std::set<const CXXGRAPH::Edge<int> *> edgeSet;
    edgeSet.insert(&edge1);
    edgeSet.insert(&edge2);
    edgeSet.insert(&edge3);
    CXXGRAPH::Graph<int> graph(edgeSet);
    for (auto _ : state)
    {
        CXXGRAPH::FWResult res = graph.floydWarshall();
    }
}

BENCHMARK(BM_FWNoWeighted);
