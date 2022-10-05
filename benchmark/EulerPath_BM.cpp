#include <benchmark/benchmark.h>
#include "CXXGraph.hpp"
#include "Utilities.hpp"


static void EulerPath_X(benchmark::State &state)
{
    CXXGRAPH::Graph<int> g;
    auto range_start = undirectedEdges.begin();
    auto range_end = undirectedEdges.find(state.range(0));
    std::unordered_map<unsigned long, CXXGRAPH::Edge<int> *> edgesX;
    edgesX.insert(range_start, range_end);
    for (auto e : edgesX)
        {
            g.addEdge(&(*e.second));
        }
    for (auto _ : state)
    {
        auto result = g.eulerianPath();
    }
}
BENCHMARK(EulerPath_X)->RangeMultiplier(16)->Range((unsigned long)1, (unsigned long)1 << 16);
