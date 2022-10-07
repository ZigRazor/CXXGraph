#include <benchmark/benchmark.h>
#include "CXXGraph.hpp"
#include "Utilities.hpp"


static void GraphSlicing_X(benchmark::State &state)
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
        auto &result = g.graph_slicing(*(range_start->second->getNodePair().first));
    }
}
BENCHMARK(GraphSlicing_X)->RangeMultiplier(16)->Range((unsigned long)1, (unsigned long)1 << 8);
