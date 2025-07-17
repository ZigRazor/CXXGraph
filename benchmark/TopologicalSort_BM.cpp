#include <benchmark/benchmark.h>

#include "CXXGraph/CXXGraph.hpp"
#include "Utilities.hpp"

static void TopologicalSort_X(benchmark::State &state) {
  CXXGraph::Graph<int> g;
  auto range_start = edges.begin();
  auto range_end = edges.find(state.range(0));
  CXXGraph::Map<unsigned long, CXXGraph::Edge<int> *> edgesX;
  edgesX.insert(range_start, range_end);
  for (auto e : edgesX) {
    g.addEdge(&(*e.second));
  }
  for (auto _ : state) {
    const auto &result = g.topologicalSort();
  }
  state.SetComplexityN(2);
}
BENCHMARK(TopologicalSort_X)
    ->RangeMultiplier(16)
    ->Range((unsigned long)1, (unsigned long)1 << 16)
    ->Complexity();

static void TopologicalSort_FromReadedCitHep(benchmark::State &state) {
  auto edgeSet = cit_graph_ptr->getEdgeSet();
  for (auto _ : state) {
    const auto &result = cit_graph_ptr->topologicalSort();
  }
  state.SetComplexityN(2);
}

BENCHMARK(TopologicalSort_FromReadedCitHep)->Complexity();
