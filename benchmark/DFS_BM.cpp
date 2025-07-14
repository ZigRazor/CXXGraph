#include <benchmark/benchmark.h>

#include "CXXGraph/CXXGraph.hpp"
#include "Utilities.hpp"

static void DFS_X(benchmark::State &state) {
  CXXGraph::Graph<int> g;
  auto range_start = edges.begin();
  auto range_end = edges.find(state.range(0));
  CXXGraph::Map<unsigned long, CXXGraph::Edge<int> *> edgesX;
  edgesX.insert(range_start, range_end);
  for (auto e : edgesX) {
    g.addEdge(&(*e.second));
  }
  for (auto _ : state) {
    auto &result =
        g.depth_first_search(*(range_start->second->getNodePair().first));
  }
  state.SetComplexityN(2);
}

BENCHMARK(DFS_X)
    ->RangeMultiplier(16)
    ->Range((unsigned long)1, (unsigned long)1 << 16)
    ->Complexity();

static void DFS_FromReadedCitHep(benchmark::State &state) {
  auto edgeSet = cit_graph_ptr->getEdgeSet();
  for (auto _ : state) {
    auto &result = cit_graph_ptr->depth_first_search(
        *((*(edgeSet.begin()))->getNodePair().first));
  }
  state.SetComplexityN(2);
}

// BENCHMARK(DFS_FromReadedCitHep)->Complexity();
