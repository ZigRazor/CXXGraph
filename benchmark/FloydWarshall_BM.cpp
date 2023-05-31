#include <benchmark/benchmark.h>
#include <Edge/DirectedWeightedEdge.hpp>

#include "CXXGraph.hpp"
#include "Utilities.hpp"

// https://en.wikipedia.org/wiki/Floyd%E2%80%93Warshall_algorithm#Example
static void BM_FWDirected(benchmark::State &state) {
  CXXGraph::Node<int> node1("1", 1);
  CXXGraph::Node<int> node2("2", 2);
  CXXGraph::Node<int> node3("3", 3);
  CXXGraph::Node<int> node4("4", 4);

  CXXGraph::DirectedWeightedEdge<int> edge1(1, node2, node1, 4);
  CXXGraph::DirectedWeightedEdge<int> edge2(2, node1, node3, -2);
  CXXGraph::DirectedWeightedEdge<int> edge3(3, node3, node4, 2);
  CXXGraph::DirectedWeightedEdge<int> edge4(4, node4, node2, -1);
  CXXGraph::DirectedWeightedEdge<int> edge5(3, node2, node3, 3);

  CXXGraph::T_EdgeSet<int> edgeSet;
  edgeSet.insert(make_shared<CXXGraph::DirectedWeightedEdge<T>>(edge1));
  edgeSet.insert(make_shared<CXXGraph::DirectedWeightedEdge<T>>(edge2));
  edgeSet.insert(make_shared<CXXGraph::DirectedWeightedEdge<T>>(edge3));
  edgeSet.insert(make_shared<CXXGraph::DirectedWeightedEdge<T>>(edge4));
  edgeSet.insert(make_shared<CXXGraph::DirectedWeightedEdge<T>>(edge5));

  CXXGraph::Graph<int> graph(edgeSet);
  for (auto _ : state) {
    CXXGraph::FWResult res = graph.floydWarshall();
  }
}
BENCHMARK(BM_FWDirected);

// a graph with negative cycle
static void BM_FWNegCycle(benchmark::State &state) {
  CXXGraph::Node<int> node0("0", 0);
  CXXGraph::Node<int> node1("1", 1);
  CXXGraph::Node<int> node2("2", 2);
  CXXGraph::DirectedWeightedEdge<int> edge1(1, node0, node1, 2);
  CXXGraph::DirectedWeightedEdge<int> edge2(2, node1, node2, 3);
  CXXGraph::DirectedWeightedEdge<int> edge3(3, node2, node0, -7);
  CXXGraph::T_EdgeSet<int> edgeSet;
  edgeSet.insert(make_shared<CXXGraph::DirectedWeightedEdge<T>>(edge1));
  edgeSet.insert(make_shared<CXXGraph::DirectedWeightedEdge<T>>(edge2));
  edgeSet.insert(make_shared<CXXGraph::DirectedWeightedEdge<T>>(edge3));
  CXXGraph::Graph<int> graph(edgeSet);
  for (auto _ : state) {
    CXXGraph::FWResult res = graph.floydWarshall();
  }
}
BENCHMARK(BM_FWNegCycle);

static void BM_FWUndirectedWeighted(benchmark::State &state) {
  CXXGraph::Node<int> node1("1", 1);
  CXXGraph::Node<int> node2("2", 2);
  CXXGraph::Node<int> node3("3", 3);
  std::pair<const CXXGraph::Node<int> *, const CXXGraph::Node<int> *> pairNode(
      &node1, &node2);
  CXXGraph::DirectedWeightedEdge<int> edge1(1, pairNode, 1);
  CXXGraph::DirectedWeightedEdge<int> edge2(2, node2, node3, 1);
  CXXGraph::UndirectedWeightedEdge<int> edge3(3, node1, node3, 6);
  CXXGraph::T_EdgeSet<int> edgeSet;
  edgeSet.insert(make_shared<CXXGraph::DirectedWeightedEdge<T>>(edge1));
  edgeSet.insert(make_shared<CXXGraph::DirectedWeightedEdge<T>>(edge2));
  edgeSet.insert(make_shared<CXXGraph::UndirectedWeightedEdge<T>>(edge3));
  CXXGraph::Graph<int> graph(edgeSet);
  for (auto _ : state) {
    CXXGraph::FWResult res = graph.floydWarshall();
  }
}
BENCHMARK(BM_FWUndirectedWeighted);

static void BM_FWNoWeighted(benchmark::State &state) {
  CXXGraph::Node<int> node1("1", 1);
  CXXGraph::Node<int> node2("2", 2);
  CXXGraph::Node<int> node3("3", 3);
  std::pair<const CXXGraph::Node<int> *, const CXXGraph::Node<int> *> pairNode(
      &node1, &node2);
  CXXGraph::DirectedWeightedEdge<int> edge1(1, pairNode, 1);
  CXXGraph::DirectedWeightedEdge<int> edge2(2, node2, node3, 1);
  CXXGraph::DirectedEdge<int> edge3(3, node1, node3);
  CXXGraph::T_EdgeSet<int> edgeSet;
  edgeSet.insert(make_shared<CXXGraph::DirectedWeightedEdge<T>>(edge1));
  edgeSet.insert(make_shared<CXXGraph::DirectedWeightedEdge<T>>(edge2));
  edgeSet.insert(make_shared<CXXGraph::DirectedEdge<T>>(edge3));
  CXXGraph::Graph<int> graph(edgeSet);
  for (auto _ : state) {
    CXXGraph::FWResult res = graph.floydWarshall();
  }
}

BENCHMARK(BM_FWNoWeighted);
