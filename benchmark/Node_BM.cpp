#include <benchmark/benchmark.h>
#include "../include/Graph.hpp"

static void BM_NodeCreation(benchmark::State &state)
{
    for (auto _ : state)
    {
        CXXGRAPH::Node<int> n1(1, 1);
    }
}

BENCHMARK(BM_NodeCreation);

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
BENCHMARK(BM_NodeGetId);