#include <benchmark/benchmark.h>

#include "CXXGraph/CXXGraph.hpp"
#include "Utilities.hpp"

static void EulerPath_X(benchmark::State &state) {
  CXXGraph::Graph<int> g;
  auto range_start = undirectedEdges.begin();
  auto range_end = undirectedEdges.find(state.range(0));
  std::unordered_map<unsigned long, CXXGraph::Edge<int> *> edgesX;
  edgesX.insert(range_start, range_end);
  for (auto e : edgesX) {
    g.addEdge(&(*e.second));
  }
  for (auto _ : state) {
    auto result = g.eulerianPath();
  }
  state.SetComplexityN(state.range(0));
}
BENCHMARK(EulerPath_X)
    ->RangeMultiplier(2)
    ->Range((unsigned long)1, (unsigned long)1 << 18)
    ->Complexity();
