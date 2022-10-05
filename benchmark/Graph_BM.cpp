#include <benchmark/benchmark.h>
#include <unistd.h>
#include "CXXGraph.hpp"
#include "Utilities.hpp"

//static CXXGRAPH::Graph<int> *graph;

static void GraphCreation(benchmark::State &state)
{
    for (auto _ : state)
    {
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

static void ReadGraphCitHep(benchmark::State &state)
{
    for (auto _ : state)
    {
        auto g = readGraph("CitHepPh");
    }
}

BENCHMARK(ReadGraphCitHep);

static void getEdgeSetX(benchmark::State &state)
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
        auto edgeSet = g.getEdgeSet();
    }
}

BENCHMARK(getEdgeSetX)->RangeMultiplier(16)->Range((unsigned long)1, (unsigned long)1 << 16);

static void getNodeSetX(benchmark::State &state)
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
        auto nodeSet = g.getNodeSet();
    }
}

BENCHMARK(getNodeSetX)->RangeMultiplier(16)->Range((unsigned long)1, (unsigned long)1 << 16);

static void getEdgeSetCitHep(benchmark::State &state)
{
    auto g = readGraph("CitHepPh");
    for (auto _ : state)
    {
        auto edgeSet = g->getEdgeSet();
    }
}

BENCHMARK(getEdgeSetCitHep);

static void getNodeSetCitHep(benchmark::State &state)
{
    auto g = readGraph("CitHepPh");
    for (auto _ : state)
    {
        auto nodeSet = g->getNodeSet();
    }
}

BENCHMARK(getNodeSetCitHep);


static void getAdjMatrixX(benchmark::State &state)
{
    CXXGRAPH::Graph<int> g;
    auto range_start = undirectedEdges.begin();
    auto range_end = undirectedEdges.find(state.range(0));
    std::unordered_map<unsigned long, CXXGRAPH::UndirectedEdge<int> *> edgesX;
    edgesX.insert(range_start, range_end);
    for (auto e : edgesX)
    {
        g.addEdge(&(*e.second));
    }
    for (auto _ : state)
    {
        auto adjMatrix = g.getAdjMatrix();
    }
}

BENCHMARK(getAdjMatrixX)->RangeMultiplier(16)->Range((unsigned long)1, (unsigned long)1 << 16);

static void readCitHep(benchmark::State &state)
{
    
    for (auto _ : state)
    {
        auto g = readGraph("CitHepPh");
    }
}

BENCHMARK(readCitHep);

static void getAdjMatrixCitHep(benchmark::State &state)
{
    auto g = readGraph("CitHepPh");
    for (auto _ : state)
    {
        auto adjMatrix = g->getAdjMatrix();
    }
}

BENCHMARK(getAdjMatrixCitHep);



