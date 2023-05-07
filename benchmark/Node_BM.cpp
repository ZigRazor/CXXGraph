#include <benchmark/benchmark.h>

#include "CXXGraph.hpp"
#include "Utilities.hpp"

static void NodeCreation(benchmark::State &state) {
  for (auto _ : state) {
    CXXGRAPH::Node<int> n1("1", 1);
  }
}
BENCHMARK(NodeCreation);

static void NodeCreationDestruction_new_delete(benchmark::State &state) {
  for (auto _ : state) {
    CXXGRAPH::Node<int> *n1 = new CXXGRAPH::Node<int>("1", 1);
    delete n1;
  }
}

BENCHMARK(NodeCreationDestruction_new_delete);

static void NodeGetId(benchmark::State &state) {
  CXXGRAPH::Node<int> n1("1", 1);
  for (auto _ : state) {
    n1.getId();
  }
}
BENCHMARK(NodeGetId);

static void NodeGetData(benchmark::State &state) {
  CXXGRAPH::Node<int> n1("1", 1);
  for (auto _ : state) {
    n1.getData();
  }
}
BENCHMARK(NodeGetData);