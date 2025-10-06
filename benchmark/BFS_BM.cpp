#include <benchmark/benchmark.h>

#include "CXXGraph/CXXGraph.hpp"
#include "Utilities.hpp"

static void BFS_X(benchmark::State &state) {
  CXXGraph::Graph<int> g;
  auto range_start = edges.begin();
  auto range_end = edges.find(state.range(0));
  std::unordered_map<unsigned long, CXXGraph::Edge<int> *> edgesX;
  edgesX.insert(range_start, range_end);
  for (auto e : edgesX) {
    g.addEdge(&(*e.second));
  }
  for (auto _ : state) {
    auto &result =
        g.breadth_first_search(*(range_start->second->getNodePair().first));
  }
  state.SetComplexityN(state.range(0));
}
BENCHMARK(BFS_X)
    ->RangeMultiplier(2)
    ->Range((unsigned long)1, (unsigned long)1 << 20)
    ->Complexity();

static void BFS_FromReadedCitHep(benchmark::State &state) {
  auto edgeSet = cit_graph_ptr->getEdgeSet();
  for (auto _ : state) {
    auto &result = cit_graph_ptr->breadth_first_search(
        *((*(edgeSet.begin()))->getNodePair().first));
  }
}
// BENCHMARK(BFS_FromReadedCitHep);

static void PSEUDO_CONCURRENCY_BFS_X(benchmark::State &state) {
  CXXGraph::Graph<int> g;
  auto range_start = edges.begin();
  auto range_end = edges.find(state.range(0));
  std::unordered_map<unsigned long, CXXGraph::Edge<int> *> edgesX;
  edgesX.insert(range_start, range_end);
  for (auto e : edgesX) {
    g.addEdge(&(*e.second));
  }
  for (auto _ : state) {
    auto &result = g.concurrency_breadth_first_search(
        *(range_start->second->getNodePair().first), 1);
  }
  state.SetComplexityN(state.range(0));
}
BENCHMARK(PSEUDO_CONCURRENCY_BFS_X)
    ->RangeMultiplier(2)
    ->Range((unsigned long)1, (unsigned long)1 << 20)
    ->Complexity();

static void PSEUDO_CONCURRENCY_BFS_FromReadedCitHep(benchmark::State &state) {
  auto edgeSet = cit_graph_ptr->getEdgeSet();
  for (auto _ : state) {
    auto &result = cit_graph_ptr->concurrency_breadth_first_search(
        *((*(edgeSet.begin()))->getNodePair().first), 1);
  }
}

// BENCHMARK(PSEUDO_CONCURRENCY_BFS_FromReadedCitHep);

static void CONCURRENCY_BFS_X(benchmark::State &state) {
  CXXGraph::Graph<int> g;
  auto range_start = edges.begin();
  auto range_end = edges.find(state.range(0));
  std::unordered_map<unsigned long, CXXGraph::Edge<int> *> edgesX;
  edgesX.insert(range_start, range_end);
  for (auto e : edgesX) {
    g.addEdge(&(*e.second));
  }
  for (auto _ : state) {
    auto &result = g.concurrency_breadth_first_search(
        *(range_start->second->getNodePair().first), 8);
  }
  state.SetComplexityN(state.range(0));
}
// BENCHMARK(CONCURRENCY_BFS_X)
//     ->RangeMultiplier(2)
//     ->Range((unsigned long)1, (unsigned long)1 << 18);

static void CONCURRENCY_BFS_FromReadedCitHep(benchmark::State &state) {
  auto edgeSet = cit_graph_ptr->getEdgeSet();
  for (auto _ : state) {
    auto &result = cit_graph_ptr->concurrency_breadth_first_search(
        *((*(edgeSet.begin()))->getNodePair().first), 8);
  }
}

// BENCHMARK(CONCURRENCY_BFS_FromReadedCitHep);
