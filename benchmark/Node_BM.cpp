#include <benchmark/benchmark.h>
#include "../include/Graph.hpp"
#include "Utilities.hpp"

static void BM_NodeCreation_1(benchmark::State &state)
{
    for (auto _ : state)
    {
        CXXGRAPH::Node<int> n1(1, 1);
    }
}
BENCHMARK(BM_NodeCreation_1);

static void BM_NodeCreationDestruction_2(benchmark::State &state)
{
    for (auto _ : state)
    {
        CXXGRAPH::Node<int> *n1 = new CXXGRAPH::Node<int>(1, 1);
        delete n1;
    }
}

BENCHMARK(BM_NodeCreationDestruction_2);

static void BM_NodeGetId(benchmark::State &state)
{
    CXXGRAPH::Node<int> n1(1, 1);
    for (auto _ : state)
    {
        n1.getId();
    }
}
BENCHMARK(BM_NodeGetId);

static void BM_NodeGetData(benchmark::State &state)
{
    CXXGRAPH::Node<int> n1(1, 1);
    for (auto _ : state)
    {
        n1.getData();
    }
}
BENCHMARK(BM_NodeGetData);