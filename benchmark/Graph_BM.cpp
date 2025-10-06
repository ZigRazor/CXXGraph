#include <benchmark/benchmark.h>

#include "CXXGraph/CXXGraph.hpp"
#include "Utilities.hpp"

// static CXXGraph::Graph<int> *graph;

static void GraphCreation(benchmark::State &state) {
  for (auto _ : state) {
    CXXGraph::Graph<int> g;
  }
  state.SetComplexityN(state.range(0));
}

BENCHMARK(GraphCreation)->Complexity();

static void AddEdge(benchmark::State &state) {
  CXXGraph::Graph<int> g;
  auto n1 = *nodes.at(0);
  auto n2 = *nodes.at(1);
  CXXGraph::Edge<int> e("1", n1, n2);
  for (auto _ : state) {
    g.addEdge(&e);
  }
  state.SetComplexityN(state.range(0));
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
  state.SetComplexityN(state.range(0));
}
BENCHMARK(AddEdgeX)
    ->RangeMultiplier(2)
    ->Range((unsigned long)1, (unsigned long)1 << 20)
    ->Complexity();

static void ReadGraphCitHep(benchmark::State &state) {
  for (auto _ : state) {
    auto g = readGraph("CitHepPh");
    delete g;
  }
  state.SetComplexityN(state.range(0));
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
  state.SetComplexityN(state.range(0));
}

BENCHMARK(getEdgeSetX)
    ->RangeMultiplier(2)
    ->Range((unsigned long)1, (unsigned long)1 << 20)
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
  state.SetComplexityN(state.range(0));
}

BENCHMARK(getNodeSetX)
    ->RangeMultiplier(2)
    ->Range((unsigned long)1, (unsigned long)1 << 20)
    ->Complexity();

static void getEdgeSetCitHep(benchmark::State &state) {
  for (auto _ : state) {
    auto edgeSet = cit_graph_ptr->getEdgeSet();
  }
  state.SetComplexityN(state.range(0));
}

BENCHMARK(getEdgeSetCitHep)->Complexity();

static void getNodeSetCitHep(benchmark::State &state) {
  for (auto _ : state) {
    auto nodeSet = cit_graph_ptr->getNodeSet();
  }
  state.SetComplexityN(state.range(0));
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
    auto adjMatrix = g.getAdjListOut();
  }
  state.SetComplexityN(state.range(0));
}

BENCHMARK(getAdjMatrixX)
    ->RangeMultiplier(2)
    ->Range((unsigned long)1, (unsigned long)1 << 20)
    ->Complexity();

static void getAdjMatrixCitHep(benchmark::State &state) {
  for (auto _ : state) {
    auto adjMatrix = cit_graph_ptr->getAdjListOut();
  }
}

BENCHMARK(getAdjMatrixCitHep);