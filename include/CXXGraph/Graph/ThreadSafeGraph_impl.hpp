#pragma once

#include <mutex>
#include <shared_mutex>

#include "CXXGraph/Graph/Graph_decl.h"

namespace CXXGraph {

/**
 * @brief Thread-safe wrapper around Graph<T>.
 *
 * Inherits all algorithms and I/O from Graph<T> unchanged.
 * Every public method is overridden to acquire the correct lock:
 *   - const (read-only) methods → std::shared_lock  (N readers allowed)
 *   - mutating methods          → std::unique_lock  (1 writer, blocks all)
 *
 * All locks are RAII — they release on scope exit, including exceptions.
 */
template <typename T>
class ThreadSafeGraph : public Graph<T> {
 public:
  // Inherit all constructors transparently
  using Graph<T>::Graph;

  // ── Structural mutations (unique_lock) ─────────────────────────────────

  std::optional<CXXGraph::id_t> addEdge(const Edge<T>* edge) override {
    std::unique_lock lock(mutex_);
    return Graph<T>::addEdge(edge);
  }

  std::optional<CXXGraph::id_t> addEdge(shared<const Edge<T>> edge) override {
    std::unique_lock lock(mutex_);
    return Graph<T>::addEdge(edge);
  }

  void addNode(const Node<T>* node) override {
    std::unique_lock lock(mutex_);
    Graph<T>::addNode(node);
  }

  void addNode(shared<const Node<T>> node) override {
    std::unique_lock lock(mutex_);
    Graph<T>::addNode(node);
  }

  void removeEdge(const std::string& edgeUserId) override {
    std::unique_lock lock(mutex_);
    Graph<T>::removeEdge(edgeUserId);
  }

  void removeEdge(const CXXGraph::id_t edgeId) override {
    std::unique_lock lock(mutex_);
    Graph<T>::removeEdge(edgeId);
  }

  void removeNode(const std::string& nodeUserId) override {
    std::unique_lock lock(mutex_);
    Graph<T>::removeNode(nodeUserId);
  }

  void removeNode(const CXXGraph::id_t nodeId) override {
    std::unique_lock lock(mutex_);
    Graph<T>::removeNode(nodeId);
  }

  // ── Read-only queries (shared_lock) ───────────────────────────────────

  const T_EdgeSet<T> getEdgeSet() const override {
    std::shared_lock lock(mutex_);
    return Graph<T>::getEdgeSet();
  }

  const T_NodeSet<T> getNodeSet() const override {
    std::shared_lock lock(mutex_);
    return Graph<T>::getNodeSet();
  }

  std::optional<shared<const Edge<T>>> getEdge(
      const std::string& edgeUserId) const override {
    std::shared_lock lock(mutex_);
    return Graph<T>::getEdge(edgeUserId);
  }

  std::optional<shared<const Node<T>>> getNode(
      const std::string& nodeUserId) const override {
    std::shared_lock lock(mutex_);
    return Graph<T>::getNode(nodeUserId);
  }

  bool findEdge(const Node<T>* v1, const Node<T>* v2,
                CXXGraph::id_t& id) const override {
    std::shared_lock lock(mutex_);
    return Graph<T>::findEdge(v1, v2, id);
  }

  bool isDirectedGraph() const override {
    std::shared_lock lock(mutex_);
    return Graph<T>::isDirectedGraph();
  }

  bool isUndirectedGraph() const override {
    std::shared_lock lock(mutex_);
    return Graph<T>::isUndirectedGraph();
  }

  // ── Algorithms (shared_lock — pure reads on graph topology) ──────────

  const DijkstraResult dijkstra(const Node<T>& source,
                                const Node<T>& target) const override {
    std::shared_lock lock(mutex_);
    return Graph<T>::dijkstra(source, target);
  }

  const BellmanFordResult bellmanford(const Node<T>& source,
                                      const Node<T>& target) const override {
    std::shared_lock lock(mutex_);
    return Graph<T>::bellmanford(source, target);
  }

  const FWResult floydWarshall() const override {
    std::shared_lock lock(mutex_);
    return Graph<T>::floydWarshall();
  }

  const MstResult prim() const override {
    std::shared_lock lock(mutex_);
    return Graph<T>::prim();
  }

  const MstResult kruskal() const override {
    std::shared_lock lock(mutex_);
    return Graph<T>::kruskal();
  }

  SCCResult<T> kosaraju() const override {
    std::shared_lock lock(mutex_);
    return Graph<T>::kosaraju();
  }

  std::vector<Node<T>> breadth_first_search(
      const Node<T>& start) const override {
    std::shared_lock lock(mutex_);
    return Graph<T>::breadth_first_search(start);
  }

  std::vector<Node<T>> depth_first_search(const Node<T>& start) const override {
    std::shared_lock lock(mutex_);
    return Graph<T>::depth_first_search(start);
  }

  double fordFulkersonMaxFlow(const Node<T>& source,
                              const Node<T>& target) const override {
    std::shared_lock lock(mutex_);
    return Graph<T>::fordFulkersonMaxFlow(source, target);
  }

  // ── Matrix accessors (shared_lock) ────────────────────────────────────

  shared<AdjacencyList<T>> getAdjListOut() const override {
    std::shared_lock lock(mutex_);
    return Graph<T>::getAdjListOut();
  }

  shared<AdjacencyList<T>> getAdjListIn() const override {
    std::shared_lock lock(mutex_);
    return Graph<T>::getAdjListIn();
  }

  shared<DegreeMatrix<T>> getDegreeMatrix() const override {
    std::shared_lock lock(mutex_);
    return Graph<T>::getDegreeMatrix();
  }

  shared<LaplacianMatrix<T>> getLaplacianMatrix() const override {
    std::shared_lock lock(mutex_);
    return Graph<T>::getLaplacianMatrix();
  }

 private:
  mutable std::shared_mutex mutex_;
};

}  // namespace CXXGraph