#include <benchmark/benchmark.h>
#include "CXXGraph.hpp"
#include "Utilities.hpp"

static auto nodes = generateRandomNodes(100000, 2);
static auto edges = generateRandomEdges(100000, nodes);

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
BENCHMARK(BFS_X)->RangeMultiplier(16)->Range((unsigned long)1, (unsigned long)1 << 12);