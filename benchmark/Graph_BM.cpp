#include <benchmark/benchmark.h>
#include <unistd.h>
#include "../include/Graph.hpp"
#include "Utilities.hpp"

static auto nodes = generateRandomNodes(100000, 2);
static auto edges = generateRandomEdges(100000, nodes);

static CXXGRAPH::Graph<int> *graph;

static void GraphCreation(benchmark::State &state)
{
    for (auto _ : state){
        CXXGRAPH::Graph<int> g;
    }
}

BENCHMARK(GraphCreation);

static void AddEdge(benchmark::State &state)
{
    CXXGRAPH::Graph<int> g;
    auto n1 = *nodes.at(0);
    auto n2 = *nodes.at(1);
    CXXGRAPH::Edge<int> e(1, n1, n2);
    for (auto _ : state)
    {
        g.addEdge(&e);
    }
}
BENCHMARK(AddEdge);

static void AddEdgeX(benchmark::State &state)
{
    CXXGRAPH::Graph<int> g;
    auto range_start = edges.begin();
    auto range_end = edges.find(state.range(0));
    std::map<unsigned long, CXXGRAPH::Edge<int> *> edgesX;
    edgesX.insert(range_start, range_end);
    //std::cout << edges1k.size() << std::endl;
    for (auto _ : state)
    {
        for (auto e : edgesX)
        {
            g.addEdge(&(*e.second));
        }
    }
}
BENCHMARK(AddEdgeX)->RangeMultiplier(16)->Range((unsigned long)1, (unsigned long)1 << 18);

static void GraphCreation_TS(benchmark::State &state)
{
    for (auto _ : state)
    {
        CXXGRAPH::Graph_TS<int> g;
    }
}

BENCHMARK(GraphCreation_TS);

static void AddEdge_TS(benchmark::State &state)
{
    CXXGRAPH::Graph_TS<int> g;
    auto n1 = *nodes.at(0);
    auto n2 = *nodes.at(1);
    CXXGRAPH::Edge<int> e(1, n1, n2);
    for (auto _ : state)
    {
        g.addEdge(&e);
    }
}
BENCHMARK(AddEdge_TS);

static void AddEdgeX_TS(benchmark::State &state)
{
    CXXGRAPH::Graph_TS<int> g;
    auto range_start = edges.begin();
    auto range_end = edges.find(state.range(0));
    std::map<unsigned long, CXXGRAPH::Edge<int> *> edgesX;
    edgesX.insert(range_start, range_end);
    //std::cout << edges1k.size() << std::endl;
    for (auto _ : state)
    {
        for (auto e : edgesX)
        {
            g.addEdge(&(*e.second));
        }
    }
}
BENCHMARK(AddEdgeX_TS)->RangeMultiplier(16)->Range((unsigned long)1, (unsigned long)1 << 18);

static void BM_AddEdgeX_MT_TS(benchmark::State &state)
{
    //std::cout << "Thread Number" << state.thread_index << std::endl;
    if (state.thread_index == 0)
    {
        graph = new CXXGRAPH::Graph_TS<int>();
    }
    auto subrange = state.range(0) / state.threads;
    //CXXGRAPH::Graph<int>* g = graph;
    auto range_start = edges.find(subrange * state.thread_index);
    auto range_end = edges.find(subrange * (state.thread_index + 1));
    std::map<unsigned long, CXXGRAPH::Edge<int> *> edgesX;
    edgesX.insert(range_start, range_end);
    //std::cout << "Thread Number " << state.thread_index << "\tedge Set Size " << edgesX.size() << std::endl;
    for (auto _ : state)
    {
        for (auto e : edgesX)
        {
            graph->addEdge(&(*e.second));
        }
    }
    //std::cout << "Thread Number " << state.thread_index << "\tedge Set Size " << edgesX.size() << "\tGraph_ptr " << graph << "\tGraph Size " << graph->getEdgeSet().size() << std::endl;
    if (state.thread_index == 0)
    {
        delete graph;
    }
}
BENCHMARK(BM_AddEdgeX_MT_TS)->RangeMultiplier(16)->Range((unsigned long)1 << 4, (unsigned long)1 << 18)->ThreadRange(1, 4);
