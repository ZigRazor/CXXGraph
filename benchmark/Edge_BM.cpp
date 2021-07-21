#include <benchmark/benchmark.h>
#include "../include/Graph.hpp"
#include "Utilities.hpp"

static void BM_EdgeCreation_1(benchmark::State &state)
{
    auto nodes = generateRandomNodes(2, 2);
    auto n1 = *nodes.at(0);
    auto n2 = *nodes.at(1);
    for (auto _ : state)
    {
        CXXGRAPH::Edge<int> e(1, n1, n2);
    }
}

BENCHMARK(BM_EdgeCreation_1);

static void BM_EdgeCreationDestruction_2(benchmark::State &state)
{
    auto nodes = generateRandomNodes(2, 2);
    auto n1 = *nodes.at(0);
    auto n2 = *nodes.at(1);
    CXXGRAPH::Edge<int> *e;
    for (auto _ : state)
    {
        e = new CXXGRAPH::Edge<int>(1, n1, n2);
        delete e;
    }
}

BENCHMARK(BM_EdgeCreationDestruction_2);

static void BM_EdgeGetId(benchmark::State &state)
{
    auto nodes = generateRandomNodes(2, 2);
    auto n1 = *nodes.at(0);
    auto n2 = *nodes.at(1);
    CXXGRAPH::Edge<int> e(1, n1, n2);
    for (auto _ : state)
    {
        e.getId();
    }
}
BENCHMARK(BM_EdgeGetId);

static void BM_NodeGetNodePair(benchmark::State &state)
{
    auto nodes = generateRandomNodes(2, 2);
    auto n1 = *nodes.at(0);
    auto n2 = *nodes.at(1);
    CXXGRAPH::Edge<int> e(1, n1, n2);
    for (auto _ : state)
    {
        e.getNodePair();
    }
}
BENCHMARK(BM_NodeGetNodePair);