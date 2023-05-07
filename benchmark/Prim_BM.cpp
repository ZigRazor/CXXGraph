#include <benchmark/benchmark.h>

#include "CXXGraph.hpp"
#include "Utilities.hpp"

static void Prim_X(benchmark::State &state) {
  CXXGraph::Graph<int> g;
  auto range_start = edges.begin();
  auto range_end = edges.find(state.range(0));
  std::unordered_map<unsigned long, CXXGraph::Edge<int> *> edgesX;
  edgesX.insert(range_start, range_end);
  for (auto e : edgesX) {
    g.addEdge(&(*e.second));
  }
  for (auto _ : state) {
    auto &result = g.prim();
  }
}
BENCHMARK(Prim_X)->RangeMultiplier(16)->Range((unsigned long)1,
                                              (unsigned long)1 << 16);

static void Prim_FromReadedCitHep(benchmark::State &state) {
  auto edgeSet = cit_graph_ptr->getEdgeSet();
  for (auto _ : state) {
    auto &result = cit_graph_ptr->prim();
  }
}

BENCHMARK(Prim_FromReadedCitHep);