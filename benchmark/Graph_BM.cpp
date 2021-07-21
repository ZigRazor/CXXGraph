#include <benchmark/benchmark.h>
#include "../include/Graph.hpp"

static void BM_GraphCreation(benchmark::State &state)
{
    for (auto _ : state){
        CXXGRAPH::Graph<int> g;
    }
}

BENCHMARK(BM_GraphCreation);


static void BM_AddEdge(benchmark::State &state)
{
    CXXGRAPH::Graph<int> g;
    CXXGRAPH::Node<int> n1(1, 1), n2(2, 2);
    CXXGRAPH::Edge<int> e(1, n1, n2);
    for (auto _ : state){
        g.addEdge(&e);
    }
}
BENCHMARK(BM_AddEdge);
