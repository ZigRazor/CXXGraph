#include <benchmark/benchmark.h>

#include "CXXGraph/CXXGraph.hpp"
#include "Utilities.hpp"

static void NodeCreation(benchmark::State &state) {
  for (auto _ : state) {
    CXXGraph::Node<int> n1("1", 1);
  }
  state.SetComplexityN(2);
}
BENCHMARK(NodeCreation)->Complexity();

static void NodeCreationDestruction_new_delete(benchmark::State &state) {
  for (auto _ : state) {
    CXXGraph::Node<int> *n1 = new CXXGraph::Node<int>("1", 1);
    delete n1;
  }
  state.SetComplexityN(2);
}

BENCHMARK(NodeCreationDestruction_new_delete)->Complexity();

static void NodeGetId(benchmark::State &state) {
  CXXGraph::Node<int> n1("1", 1);
  for (auto _ : state) {
    n1.getId();
  }
  state.SetComplexityN(2);
}
BENCHMARK(NodeGetId)->Complexity();

static void NodeGetData(benchmark::State &state) {
  CXXGraph::Node<int> n1("1", 1);
  for (auto _ : state) {
    n1.getData();
  }
  state.SetComplexityN(2);
}
BENCHMARK(NodeGetData)->Complexity();
