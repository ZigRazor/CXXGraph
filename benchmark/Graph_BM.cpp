#include <benchmark/benchmark.h>

#include "CXXGraph/CXXGraph.hpp"
#include "Utilities.hpp"

// static CXXGraph::Graph<int> *graph;

static void GraphCreation(benchmark::State &state) {
  for (auto _ : state) {
    CXXGraph::Graph<int> g;
  }
  state.SetComplexityN(2);
}

BENCHMARK(GraphCreation)->Complexity();

static void AddEdge(benchmark::State &state) {
  CXXGraph::Graph<int> g;
  auto n1 = *nodes.at(0);
  auto n2 = *nodes.at(1);
  CXXGraph::Edge<int> e(1, n1, n2);
  for (auto _ : state) {
    g.addEdge(&e);
  }
  state.SetComplexityN(2);
}
BENCHMARK(AddEdge)->Complexity();

static void AddEdgeX(benchmark::State &state) {
  CXXGraph::Graph<int> g;
  auto range_start = edges.begin();
  auto range_end = edges.find(state.range(0));
  std::unordered_map<unsigned long, CXXGraph::Edge<int> *> edgesX;
  edgesX.insert(range_start, range_end);
  for (auto _ : state) {
    for (auto e : edgesX) {
      g.addEdge(&(*e.second));
    }
  }
  state.SetComplexityN(2);
}
BENCHMARK(AddEdgeX)
    ->RangeMultiplier(16)
    ->Range((unsigned long)1, (unsigned long)1 << 16)
    ->Complexity();

static void ReadGraphCitHep(benchmark::State &state) {
  for (auto _ : state) {
    auto g = readGraph("CitHepPh");
    delete g;
  }
  state.SetComplexityN(2);
}

BENCHMARK(ReadGraphCitHep)->Complexity();

static void getEdgeSetX(benchmark::State &state) {
  CXXGraph::Graph<int> g;
  auto range_start = edges.begin();
  auto range_end = edges.find(state.range(0));
  std::unordered_map<unsigned long, CXXGraph::Edge<int> *> edgesX;
  edgesX.insert(range_start, range_end);
  for (auto e : edgesX) {
    g.addEdge(&(*e.second));
  }
  for (auto _ : state) {
    auto edgeSet = g.getEdgeSet();
  }
  state.SetComplexityN(2);
}

BENCHMARK(getEdgeSetX)
    ->RangeMultiplier(16)
    ->Range((unsigned long)1, (unsigned long)1 << 16)
    ->Complexity();

static void getNodeSetX(benchmark::State &state) {
  CXXGraph::Graph<int> g;
  auto range_start = edges.begin();
  auto range_end = edges.find(state.range(0));
  std::unordered_map<unsigned long, CXXGraph::Edge<int> *> edgesX;
  edgesX.insert(range_start, range_end);
  for (auto e : edgesX) {
    g.addEdge(&(*e.second));
  }
  for (auto _ : state) {
    auto nodeSet = g.getNodeSet();
  }
  state.SetComplexityN(2);
}

BENCHMARK(getNodeSetX)
    ->RangeMultiplier(16)
    ->Range((unsigned long)1, (unsigned long)1 << 16)
    ->Complexity();

static void getEdgeSetCitHep(benchmark::State &state) {
  for (auto _ : state) {
    auto edgeSet = cit_graph_ptr->getEdgeSet();
  }
  state.SetComplexityN(2);
}

BENCHMARK(getEdgeSetCitHep)->Complexity();

static void getNodeSetCitHep(benchmark::State &state) {
  for (auto _ : state) {
    auto nodeSet = cit_graph_ptr->getNodeSet();
  }
  state.SetComplexityN(2);
}

BENCHMARK(getNodeSetCitHep)->Complexity();

static void getAdjMatrixX(benchmark::State &state) {
  CXXGraph::Graph<int> g;
  auto range_start = undirectedEdges.begin();
  auto range_end = undirectedEdges.find(state.range(0));
  std::unordered_map<unsigned long, CXXGraph::UndirectedEdge<int> *> edgesX;
  edgesX.insert(range_start, range_end);
  for (auto e : edgesX) {
    g.addEdge(&(*e.second));
  }
  for (auto _ : state) {
    auto adjMatrix = g.getAdjMatrixOut();
  }
  state.SetComplexityN(2);
}

BENCHMARK(getAdjMatrixX)
    ->RangeMultiplier(16)
    ->Range((unsigned long)1, (unsigned long)1 << 16)
    ->Complexity();

static void getAdjMatrixCitHep(benchmark::State &state) {
  for (auto _ : state) {
    auto adjMatrix = cit_graph_ptr->getAdjMatrixOut();
  }
  state.SetComplexityN(2);
}

BENCHMARK(getAdjMatrixCitHep)->Complexity();
