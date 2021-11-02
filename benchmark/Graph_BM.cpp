#include <benchmark/benchmark.h>
#include <unistd.h>
#include "CXXGraph.hpp"
#include "Utilities.hpp"

static auto nodes = generateRandomNodes(100000, 2);
static auto edges = generateRandomEdges(100000, nodes);

static CXXGRAPH::Graph<int> *graph;
static CXXGRAPH::Graph_TS<int> *graph_ts;

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
    std::unordered_map<unsigned long, CXXGRAPH::Edge<int> *> edgesX;
    edgesX.insert(range_start, range_end);
    for (auto _ : state)
    {
        for (auto e : edgesX)
        {
            g.addEdge(&(*e.second));
        }
    }
}
BENCHMARK(AddEdgeX)->RangeMultiplier(16)->Range((unsigned long)1, (unsigned long)1 << 16);

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
    std::unordered_map<unsigned long, CXXGRAPH::Edge<int> *> edgesX;
    edgesX.insert(range_start, range_end);
    for (auto _ : state)
    {
        for (auto e : edgesX)
        {
            g.addEdge(&(*e.second));
        }
    }
}
BENCHMARK(AddEdgeX_TS)->RangeMultiplier(16)->Range((unsigned long)1, (unsigned long)1 << 16);

static void BM_AddEdgeX_MT_TS(benchmark::State &state)
{
    if (state.thread_index() == 0)
    {
        graph_ts = new CXXGRAPH::Graph_TS<int>();
    }
    auto subrange = state.range(0) / state.threads();
    auto range_start = edges.find(subrange * state.thread_index());
    auto range_end = edges.find(subrange * (state.thread_index() + 1));
    std::unordered_map<unsigned long, CXXGRAPH::Edge<int> *> edgesX;
    edgesX.insert(range_start, range_end);
    for (auto _ : state)
    {
        for (auto e : edgesX)
        {
            graph_ts->addEdge(&(*e.second));
        }
    }
    if (state.thread_index() == 0)
    {
        delete graph_ts;
    }
}
BENCHMARK(BM_AddEdgeX_MT_TS)->RangeMultiplier(16)->Range((unsigned long)1 << 4, (unsigned long)1 << 16)->ThreadRange(1, 4);

static void RemoveEdge(benchmark::State &state)
{
    CXXGRAPH::Graph<int> g;
    auto n1 = *nodes.at(0);
    auto n2 = *nodes.at(1);
    CXXGRAPH::Edge<int> e(1, n1, n2);
    g.addEdge(&e);
    for (auto _ : state)
    {
        g.removeEdge(1);
    }
}
BENCHMARK(RemoveEdge);

static void RemoveEdgeX(benchmark::State &state)
{
    CXXGRAPH::Graph<int> g;
    auto range_start = edges.begin();
    auto range_end = edges.find(state.range(0));
    std::unordered_map<unsigned long, CXXGRAPH::Edge<int> *> edgesX;
    edgesX.insert(range_start, range_end);
    for (auto e : edgesX)
    {
        g.addEdge(&(*e.second));
    }
    for (auto _ : state)
    {
        for (auto e : edgesX)
        {
            g.removeEdge(e.second->getId());
        }
    }
}
BENCHMARK(RemoveEdgeX)->RangeMultiplier(16)->Range((unsigned long)1, (unsigned long)1 << 16);

static void RemoveEdge_TS(benchmark::State &state)
{
    CXXGRAPH::Graph_TS<int> g;
    auto n1 = *nodes.at(0);
    auto n2 = *nodes.at(1);
    CXXGRAPH::Edge<int> e(1, n1, n2);
    g.addEdge(&e);
    for (auto _ : state)
    {
        g.removeEdge(1);
    }
}
BENCHMARK(RemoveEdge_TS);

static void RemoveEdgeX_TS(benchmark::State &state)
{
    CXXGRAPH::Graph_TS<int> g;
    auto range_start = edges.begin();
    auto range_end = edges.find(state.range(0));
    std::unordered_map<unsigned long, CXXGRAPH::Edge<int> *> edgesX;
    edgesX.insert(range_start, range_end);
    for (auto e : edgesX)
    {
        g.addEdge(&(*e.second));
    }
    for (auto _ : state)
    {
        for (auto e : edgesX)
        {
            g.removeEdge(e.second->getId());
        }
    }
}
BENCHMARK(RemoveEdgeX_TS)->RangeMultiplier(16)->Range((unsigned long)1, (unsigned long)1 << 16);

static void RemoveEdgeX_MT_TS(benchmark::State &state)
{
    if (state.thread_index() == 0)
    {
        graph_ts = new CXXGRAPH::Graph_TS<int>();
    }
    sleep(1); //let the possibility to create the Graph and avoid segmentation fault
    auto subrange = state.range(0) / state.threads();
    auto range_start = edges.find(subrange * state.thread_index());
    auto range_end = edges.find(subrange * (state.thread_index() + 1));
    std::unordered_map<unsigned long, CXXGRAPH::Edge<int> *> edgesX;
    edgesX.insert(range_start, range_end);
    for (auto e : edgesX)
    {
        graph_ts->addEdge(&(*e.second));
    }
    for (auto _ : state)
    {

        for (auto e : edgesX)
        {
            graph_ts->removeEdge(e.second->getId());
        }
    }

    if (state.thread_index() == 0)
    {
        delete graph_ts;
    }
}
BENCHMARK(RemoveEdgeX_MT_TS)->RangeMultiplier(16)->Range((unsigned long)1 << 4, (unsigned long)1 << 16)->ThreadRange(1, 4);
