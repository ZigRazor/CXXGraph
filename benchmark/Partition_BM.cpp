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
    auto result = CXXGraph::Partitioning::Partitioner<int>::partitionGraph(
        g, CXXGraph::Partitioning::PartitionAlgorithm::HDRF_ALG, 4, 1, 0.001);
  }
}
BENCHMARK(PartitionHDRF_X)
    ->RangeMultiplier(16)
    ->Range((unsigned long)1, (unsigned long)1 << 16)
    ->Complexity();

static void PartitionHDRF_FromReadedCitHep(benchmark::State &state) {
  auto edgeSet = cit_graph_ptr->getEdgeSet();
  for (auto _ : state) {
    auto result = CXXGraph::Partitioning::Partitioner<int>::partitionGraph(
        *cit_graph_ptr, CXXGraph::Partitioning::PartitionAlgorithm::HDRF_ALG, 4,
        1, 0.001);
  }
}

BENCHMARK(PartitionHDRF_FromReadedCitHep)->Complexity();

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
    auto result = CXXGraph::Partitioning::Partitioner<int>::partitionGraph(
        g, CXXGraph::Partitioning::PartitionAlgorithm::EDGEBALANCED_VC_ALG, 4);
  }
}
BENCHMARK(PartitionEBVC_X)
    ->RangeMultiplier(16)
    ->Range((unsigned long)1, (unsigned long)1 << 16)
    ->Complexity();

static void PartitionEBVC_FromReadedCitHep(benchmark::State &state) {
  auto edgeSet = cit_graph_ptr->getEdgeSet();
  for (auto _ : state) {
    auto result = CXXGraph::Partitioning::Partitioner<int>::partitionGraph(
        *cit_graph_ptr,
        CXXGraph::Partitioning::PartitionAlgorithm::EDGEBALANCED_VC_ALG, 4);
  }
}

BENCHMARK(PartitionEBVC_FromReadedCitHep)->Complexity();

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
    auto result = CXXGraph::Partitioning::Partitioner<int>::partitionGraph(
        g, CXXGraph::Partitioning::PartitionAlgorithm::GREEDY_VC_ALG, 4);
  }
}
BENCHMARK(PartitionGVC_X)
    ->RangeMultiplier(16)
    ->Range((unsigned long)1, (unsigned long)1 << 16)
    ->Complexity();

static void PartitionGVC_FromReadedCitHep(benchmark::State &state) {
  auto edgeSet = cit_graph_ptr->getEdgeSet();
  for (auto _ : state) {
    auto result = CXXGraph::Partitioning::Partitioner<int>::partitionGraph(
        *cit_graph_ptr,
        CXXGraph::Partitioning::PartitionAlgorithm::GREEDY_VC_ALG, 4);
  }
}

BENCHMARK(PartitionGVC_FromReadedCitHep)->Complexity();

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
    auto result = CXXGraph::Partitioning::Partitioner<int>::partitionGraph(
        g, CXXGraph::Partitioning::PartitionAlgorithm::EBV_ALG, 4, 1, 1);
  }
}
BENCHMARK(PartitionEBV_X)
    ->RangeMultiplier(16)
    ->Range((unsigned long)1, (unsigned long)1 << 16)
    ->Complexity();

static void PartitionEBV_FromReadedCitHep(benchmark::State &state) {
  auto edgeSet = cit_graph_ptr->getEdgeSet();
  for (auto _ : state) {
    auto result = CXXGraph::Partitioning::Partitioner<int>::partitionGraph(
        *cit_graph_ptr, CXXGraph::Partitioning::PartitionAlgorithm::EBV_ALG, 4,
        1, 1);
  }
}

BENCHMARK(PartitionEBV_FromReadedCitHep)->Complexity();
