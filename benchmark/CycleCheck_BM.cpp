#include <benchmark/benchmark.h>

#include "CXXGraph/CXXGraph.hpp"
#include "Utilities.hpp"

static void CycleCheckBFS_X(benchmark::State &state) {
  CXXGraph::Graph<int> g;
  auto range_start = edges.begin();
  auto range_end = edges.find(state.range(0));
  std::unordered_map<unsigned long, CXXGraph::Edge<int> *> edgesX;
  edgesX.insert(range_start, range_end);
  for (auto e : edgesX) {
    g.addEdge(&(*e.second));
  }
  for (auto _ : state) {
    auto result = g.isCyclicDirectedGraphBFS();
  }
  state.SetComplexityN(state.range(0));
}
BENCHMARK(CycleCheckBFS_X)
    ->RangeMultiplier(2)
    ->Range((unsigned long)1, (unsigned long)1 << 18)
    ->Complexity();

static void CycleCheckBFS_FromReadedCitHep(benchmark::State &state) {
  auto edgeSet = cit_graph_ptr->getEdgeSet();
  for (auto _ : state) {
    auto result = cit_graph_ptr->isCyclicDirectedGraphBFS();
  }
}

// BENCHMARK(CycleCheckBFS_FromReadedCitHep);

static void CycleCheckDFS_X(benchmark::State &state) {
  CXXGraph::Graph<int> g;
  auto range_start = edges.begin();
  auto range_end = edges.find(state.range(0));
  std::unordered_map<unsigned long, CXXGraph::Edge<int> *> edgesX;
  edgesX.insert(range_start, range_end);
  for (auto e : edgesX) {
    g.addEdge(&(*e.second));
  }
  for (auto _ : state) {
    auto result = g.isCyclicDirectedGraphDFS();
  }
  state.SetComplexityN(state.range(0));
}
BENCHMARK(CycleCheckDFS_X)
    ->RangeMultiplier(2)
    ->Range((unsigned long)1, (unsigned long)1 << 18)
    ->Complexity();

static void CycleCheckDFS_FromReadedCitHep(benchmark::State &state) {
  auto edgeSet = cit_graph_ptr->getEdgeSet();
  for (auto _ : state) {
    auto result = cit_graph_ptr->isCyclicDirectedGraphDFS();
  }
}

// BENCHMARK(CycleCheckDFS_FromReadedCitHep);
