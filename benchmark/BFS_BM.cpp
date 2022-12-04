#include <benchmark/benchmark.h>
#include "CXXGraph.hpp"
#include "Utilities.hpp"


static void BFS_X(benchmark::State &state)
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
        auto &result = g.breadth_first_search(*(range_start->second->getNodePair().first));
    }
}
BENCHMARK(BFS_X)->RangeMultiplier(18)->Range((unsigned long)1, (unsigned long)1 << 18);

static void BFS_FromReadedCitHep(benchmark::State &state)
{
    auto edgeSet = cit_graph_ptr->getEdgeSet();
    for (auto _ : state)
    {
        
        auto &result = cit_graph_ptr->breadth_first_search(*((*(edgeSet.begin()))->getNodePair().first));
    }
}

BENCHMARK(BFS_FromReadedCitHep);

static void PSEUDO_CONCURRENCY_BFS_X(benchmark::State &state)
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
        auto &result = g.concurrency_breadth_first_search(*(range_start->second->getNodePair().first), 1);
    }
}
BENCHMARK(PSEUDO_CONCURRENCY_BFS_X)->RangeMultiplier(18)->Range((unsigned long)1, (unsigned long)1 << 18);

static void PSEUDO_CONCURRENCY_BFS_FromReadedCitHep(benchmark::State &state)
{
    auto edgeSet = cit_graph_ptr->getEdgeSet();
    for (auto _ : state)
    {
        
        auto &result = cit_graph_ptr->concurrency_breadth_first_search(*((*(edgeSet.begin()))->getNodePair().first), 1);
    }
}

BENCHMARK(PSEUDO_CONCURRENCY_BFS_FromReadedCitHep);

static void CONCURRENCY_BFS_X(benchmark::State &state)
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
        auto &result = g.concurrency_breadth_first_search(*(range_start->second->getNodePair().first), 8);
    }
}
BENCHMARK(CONCURRENCY_BFS_X)->RangeMultiplier(18)->Range((unsigned long)1, (unsigned long)1 << 18);

static void CONCURRENCY_BFS_FromReadedCitHep(benchmark::State &state)
{
    auto edgeSet = cit_graph_ptr->getEdgeSet();
    for (auto _ : state)
    {
        
        auto &result = cit_graph_ptr->concurrency_breadth_first_search(*((*(edgeSet.begin()))->getNodePair().first), 8);
    }
}

BENCHMARK(CONCURRENCY_BFS_FromReadedCitHep);

