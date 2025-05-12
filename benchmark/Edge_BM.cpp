#include <benchmark/benchmark.h>

#include "CXXGraph/CXXGraph.hpp"
#include "Utilities.hpp"

static void BM_EdgeCreation(benchmark::State &state) {
  auto nodes = generateRandomNodes(2, 2);
  auto n1 = *nodes.at(0);
  auto n2 = *nodes.at(1);
  for (auto _ : state) {
    CXXGraph::Edge<int> e(1, n1, n2);
  }
  state.SetComplexityN(2);
}

BENCHMARK(BM_EdgeCreation)->Complexity();

static void EdgeCreationDestruction_new_delete(benchmark::State &state) {
  auto nodes = generateRandomNodes(2, 2);
  auto n1 = *nodes.at(0);
  auto n2 = *nodes.at(1);
  CXXGraph::Edge<int> *e;
  for (auto _ : state) {
    e = new CXXGraph::Edge<int>(1, n1, n2);
    delete e;
  }
  state.SetComplexityN(2);
}

BENCHMARK(EdgeCreationDestruction_new_delete)->Complexity();

static void EdgeGetId(benchmark::State &state) {
  auto nodes = generateRandomNodes(2, 2);
  auto n1 = *nodes.at(0);
  auto n2 = *nodes.at(1);
  CXXGraph::Edge<int> e(1, n1, n2);
  for (auto _ : state) {
    e.getId();
  }
  state.SetComplexityN(2);
}
BENCHMARK(EdgeGetId)->Complexity();

static void NodeGetNodePair(benchmark::State &state) {
  auto nodes = generateRandomNodes(2, 2);
  auto n1 = *nodes.at(0);
  auto n2 = *nodes.at(1);
  CXXGraph::Edge<int> e(1, n1, n2);
  for (auto _ : state) {
    e.getNodePair();
  }
  state.SetComplexityN(2);
}
BENCHMARK(NodeGetNodePair)->Complexity();
