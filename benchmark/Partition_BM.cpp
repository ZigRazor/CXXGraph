#include <benchmark/benchmark.h>

#include "CXXGraph/CXXGraph.hpp"
#include "Utilities.hpp"

static void PartitionHDRF_X(benchmark::State &state) {
  CXXGraph::Graph<int> g;
  auto range_start = edges.begin();
  auto range_end = edges.find(state.range(0));
  std::unordered_map<unsigned long, CXXGraph::Edge<int> *> edgesX;
  edgesX.insert(range_start, range_end);
  for (auto e : edgesX) {
    g.addEdge(&(*e.second));
  }
  for (auto _ : state) {
    auto result = g.partitionGraph(
        CXXGraph::Partitioning::PartitionAlgorithm::HDRF_ALG, 4, 1, 0.001);
  }
}
BENCHMARK(PartitionHDRF_X)
    ->RangeMultiplier(16)
    ->Range((unsigned long)1, (unsigned long)1 << 16);

static void PartitionHDRF_FromReadedCitHep(benchmark::State &state) {
  auto edgeSet = cit_graph_ptr->getEdgeSet();
  for (auto _ : state) {
    auto result = cit_graph_ptr->partitionGraph(
        CXXGraph::Partitioning::PartitionAlgorithm::HDRF_ALG, 4, 1, 0.001);
  }
}

BENCHMARK(PartitionHDRF_FromReadedCitHep);

static void PartitionEBVC_X(benchmark::State &state) {
  CXXGraph::Graph<int> g;
  auto range_start = edges.begin();
  auto range_end = edges.find(state.range(0));
  std::unordered_map<unsigned long, CXXGraph::Edge<int> *> edgesX;
  edgesX.insert(range_start, range_end);
  for (auto e : edgesX) {
    g.addEdge(&(*e.second));
  }
  for (auto _ : state) {
    auto result = g.partitionGraph(
        CXXGraph::Partitioning::PartitionAlgorithm::EDGEBALANCED_VC_ALG, 4);
  }
}
BENCHMARK(PartitionEBVC_X)
    ->RangeMultiplier(16)
    ->Range((unsigned long)1, (unsigned long)1 << 16);

static void PartitionEBVC_FromReadedCitHep(benchmark::State &state) {
  auto edgeSet = cit_graph_ptr->getEdgeSet();
  for (auto _ : state) {
    auto result = cit_graph_ptr->partitionGraph(
        CXXGraph::Partitioning::PartitionAlgorithm::EDGEBALANCED_VC_ALG, 4);
  }
}

BENCHMARK(PartitionEBVC_FromReadedCitHep);

static void PartitionGVC_X(benchmark::State &state) {
  CXXGraph::Graph<int> g;
  auto range_start = edges.begin();
  auto range_end = edges.find(state.range(0));
  std::unordered_map<unsigned long, CXXGraph::Edge<int> *> edgesX;
  edgesX.insert(range_start, range_end);
  for (auto e : edgesX) {
    g.addEdge(&(*e.second));
  }
  for (auto _ : state) {
    auto result = g.partitionGraph(
        CXXGraph::Partitioning::PartitionAlgorithm::GREEDY_VC_ALG, 4);
  }
}
BENCHMARK(PartitionGVC_X)
    ->RangeMultiplier(16)
    ->Range((unsigned long)1, (unsigned long)1 << 16);

static void PartitionGVC_FromReadedCitHep(benchmark::State &state) {
  auto edgeSet = cit_graph_ptr->getEdgeSet();
  for (auto _ : state) {
    auto result = cit_graph_ptr->partitionGraph(
        CXXGraph::Partitioning::PartitionAlgorithm::GREEDY_VC_ALG, 4);
  }
}

BENCHMARK(PartitionGVC_FromReadedCitHep);

static void PartitionEBV_X(benchmark::State &state) {
  CXXGraph::Graph<int> g;
  auto range_start = edges.begin();
  auto range_end = edges.find(state.range(0));
  std::unordered_map<unsigned long, CXXGraph::Edge<int> *> edgesX;
  edgesX.insert(range_start, range_end);
  for (auto e : edgesX) {
    g.addEdge(&(*e.second));
  }
  for (auto _ : state) {
    auto result = g.partitionGraph(
        CXXGraph::Partitioning::PartitionAlgorithm::EBV_ALG, 4, 1, 1);
  }
}
BENCHMARK(PartitionEBV_X)
    ->RangeMultiplier(16)
    ->Range((unsigned long)1, (unsigned long)1 << 16);

static void PartitionEBV_FromReadedCitHep(benchmark::State &state) {
  auto edgeSet = cit_graph_ptr->getEdgeSet();
  for (auto _ : state) {
    auto result = cit_graph_ptr->partitionGraph(
        CXXGraph::Partitioning::PartitionAlgorithm::EBV_ALG, 4, 1, 1);
  }
}

BENCHMARK(PartitionEBV_FromReadedCitHep);
