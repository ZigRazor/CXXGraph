#include <benchmark/benchmark.h>

#include <unordered_map>

#include "CXXGraph/CXXGraph.hpp"
#include "Utilities.hpp"

static void Connectivity_X(benchmark::State &state) {
  CXXGraph::Graph<int> g;
  auto range_start = edges.begin();
  auto range_end = edges.find(state.range(0));
  std::unordered_map<unsigned long, CXXGraph::Edge<int> *> edgesX;
  edgesX.insert(range_start, range_end);
  for (auto e : edgesX) {
    g.addEdge(&(*e.second));
  }
  for (auto _ : state) {
    auto result = g.isConnectedGraph();
  }
  state.SetComplexityN(state.range(0));
}
BENCHMARK(Connectivity_X)
    ->RangeMultiplier(2)
    ->Range((unsigned long)1, (unsigned long)1 << 18)
    ->Complexity();

static void Connectivity_FromReadedCitHep(benchmark::State &state) {
  auto edgeSet = cit_graph_ptr->getEdgeSet();
  for (auto _ : state) {
    auto result = cit_graph_ptr->isConnectedGraph();
  }
}

// BENCHMARK(Connectivity_FromReadedCitHep);

static void StrongConnectivity_X(benchmark::State &state) {
  CXXGraph::Graph<int> g;
  auto range_start = edges.begin();
  auto range_end = edges.find(state.range(0));
  std::unordered_map<unsigned long, CXXGraph::Edge<int> *> edgesX;
  edgesX.insert(range_start, range_end);
  for (auto e : edgesX) {
    g.addEdge(&(*e.second));
  }
  for (auto _ : state) {
    auto result = g.isConnectedGraph();
  }
  state.SetComplexityN(state.range(0));
}
BENCHMARK(StrongConnectivity_X)
    ->RangeMultiplier(2)
    ->Range((unsigned long)1, (unsigned long)1 << 18)
    ->Complexity();

static void StrongConnectivity_FromReadedCitHep(benchmark::State &state) {
  auto edgeSet = cit_graph_ptr->getEdgeSet();
  for (auto _ : state) {
    auto result = cit_graph_ptr->isConnectedGraph();
  }
}

// BENCHMARK(StrongConnectivity_FromReadedCitHep);
