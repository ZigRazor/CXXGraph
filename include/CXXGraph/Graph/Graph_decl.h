/***********************************************************/
/***      ______  ____  ______                 _         ***/
/***     / ___\ \/ /\ \/ / ___|_ __ __ _ _ __ | |__	     ***/
/***    | |    \  /  \  / |  _| '__/ _` | '_ \| '_ \	 ***/
/***    | |___ /  \  /  \ |_| | | | (_| | |_) | | | |    ***/
/***     \____/_/\_\/_/\_\____|_|  \__,_| .__/|_| |_|    ***/
/***                                    |_|			     ***/
/***********************************************************/
/***     Header-Only C++ Library for Graph			     ***/
/***	 Representation and Algorithms				     ***/
/***********************************************************/
/***     Author: ZigRazor ***/
/***	 E-Mail: zigrazor@gmail.com 				     ***/
/***********************************************************/
/***	 Collaboration: ----------- 				     ***/
/***********************************************************/
/***	 License: AGPL v3.0 ***/
/***********************************************************/

#ifndef __CXXGRAPH_GRAPH_DECL_H__
#define __CXXGRAPH_GRAPH_DECL_H__

#pragma once

#include <cmath>
#include <cstring>
#include <fstream>
#include <functional>
#include <iostream>
#include <map>
#include <memory>
#include <optional>
#include <sstream>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <utility>

#include "CXXGraph/Edge/DirectedEdge.h"
#include "CXXGraph/Edge/DirectedWeightedEdge.h"
#include "CXXGraph/Edge/Edge.h"
#include "CXXGraph/Edge/UndirectedEdge.h"
#include "CXXGraph/Edge/UndirectedWeightedEdge.h"
#include "CXXGraph/Edge/Weighted.h"
#include "CXXGraph/Node/Node.h"
#include "CXXGraph/Utility/TypeTraits.hpp"
#include "CXXGraph/Utility/Typedef.hpp"

#ifdef WITH_COMPRESSION
#include <zlib.h>
#endif

namespace CXXGraph {
// Smart pointers alias
template <typename T>
using unique = std::unique_ptr<T>;
template <typename T>
using shared = std::shared_ptr<T>;

template <typename T>
using T_EdgeSet = std::unordered_set<shared<const Edge<T>>, edgeHash<T>>;

template <typename T>
using T_NodeSet = std::unordered_set<shared<const Node<T>>, nodeHash<T>>;

template <typename T>
class Graph;

template <typename T>
std::ostream &operator<<(std::ostream &o, const Graph<T> &graph);
template <typename T>
std::ostream &operator<<(std::ostream &o, const AdjacencyMatrix<T> &adj);

/// Class that implement the Graph. ( This class is not Thread Safe )
template <typename T>
class Graph {
 private:
  T_EdgeSet<T> edgeSet = {};
  T_NodeSet<T> isolatedNodesSet = {};

  shared<AdjacencyMatrix<T>> cachedAdjMatrix;
  shared<DegreeMatrix<T>> cachedDegreeMatrix;
  shared<LaplacianMatrix<T>> cachedLaplacianMatrix;
  shared<TransitionMatrix<T>> cachedTransitionMatrix;
  // Private non-const getter for the set of nodes
  std::unordered_set<shared<Node<T>>, nodeHash<T>> nodeSet();

  std::optional<std::pair<std::string, char>> getExtenstionAndSeparator(
      InputOutputFormat format) const;
  void writeGraphToStream(std::ostream &oGraph, std::ostream &oNodeFeat,
                          std::ostream &oEdgeWeight, const char &sep,
                          bool writeNodeFeat, bool writeEdgeWeight) const;
  void readGraphFromStream(std::istream &iGraph, std::istream &iNodeFeat,
                           std::istream &iEdgeWeight, bool readNodeFeat,
                           bool readEdgeWeight);
  int writeToDot(const std::string &workingDir, const std::string &OFileName,
                 const std::string &graphName) const;
  int readFromDot(const std::string &workingDir, const std::string &fileName);
  void recreateGraph(
      std::unordered_map<CXXGraph::id_t, std::pair<std::string, std::string>>
          &edgeMap,
      std::unordered_map<CXXGraph::id_t, bool> &edgeDirectedMap,
      std::unordered_map<std::string, T> &nodeFeatMap,
      std::unordered_map<CXXGraph::id_t, double> &edgeWeightMap);

#ifdef WITH_COMPRESSION
  int compressFile(const std::string &inputFile,
                   const std::string &outputFile) const;
  int decompressFile(const std::string &inputFile,
                     const std::string &outputFile) const;
#endif

 public:
  Graph();
  Graph(const T_EdgeSet<T> &edgeSet);
  virtual ~Graph() = default;
  /**
   * \brief
   * Function that return the Edge set of the Graph
   * Note: No Thread Safe
   *
   * @returns a list of Edges of the graph
   *
   */
  virtual const T_EdgeSet<T> &getEdgeSet() const;
  /**
   * \brief
   * Function set the Edge Set of the Graph
   * Note: No Thread Safe
   *
   * @param edgeSet The Edge Set
   *
   */
  virtual void setEdgeSet(const T_EdgeSet<T> &edgeSet);
  /**
   * \brief
   * Function add an Edge to the Graph Edge Set
   * First check if a pointer to a node with the same userId has
   * already been added, and if not add it
   * Note: No Thread Safe
   *
   * @param edge The Edge to insert
   *
   */
  virtual void addEdge(const Edge<T> *edge);
  /**
   * \brief
   * Function add an Edge to the Graph Edge Set
   * First check if a pointer to a node with the same userId has
   * already been added, and if not add it
   * Note: No Thread Safe
   *
   * @param edge The Edge to insert
   *
   */
  virtual void addEdge(shared<const Edge<T>> edge);
  /**
   * \brief
   * Function that adds any number of Edges to the Graph Edge set
   * Note: This is the overload needed to terminate the
   * recursion
   *
   * @param None
   *
   */
  template <typename... Tn>
  void addEdges();
  /**
   * \brief
   * Function that adds any number of Edges to the Graph Edge set
   *
   * @param Raw pointers or shared pointers to the Edges
   *
   */
  template <typename T1, typename... Tn>
  std::enable_if_t<is_edge_ptr_v<T1> && (is_edge_ptr_v<Tn> && ...), void>
  addEdges(T1 edge, Tn... edges);
  /**
   * \brief
   * Function to add a Node to the Graph Node Set
   * Note: No Thread Safe
   *
   * @param pointer to the node
   *
   */
  virtual void addNode(const Node<T> *node);
  /**
   * \brief
   * Function to add a Node to the Graph Node Set
   * Note: No Thread Safe
   *
   * @param shared pointer to the node
   *
   */
  virtual void addNode(shared<const Node<T>> node);
  /**
   * \brief
   * Function that adds any number of Nodes to the Graph Node set
   * Note: This overload is needed to terminate the recursion
   *
   * @param None
   *
   */
  template <typename... Tn>
  void addNodes();
  /**
   * \brief
   * Function that adds any number of Nodes to the Graph Node set
   *
   * @param Raw pointers or shared pointers to the Edges
   *
   */
  template <typename T1, typename... Tn>
  std::enable_if_t<is_node_ptr_v<T1> && (is_node_ptr_v<Tn> && ...), void>
  addNodes(T1 node, Tn... nodes);
  /**
   * \brief
   * Function remove an Edge from the Graph Edge Set
   * Note: No Thread Safe
   *
   * @param edgeId The Edge Id to remove
   *
   */
  virtual void removeEdge(const CXXGraph::id_t edgeId);
  /**
   * \brief
   * Function to remove a Node from the Graph Node Set
   * Note: No Thread Safe
   *
   * @param edgeId The Edge Id to remove
   *
   */
  virtual void removeNode(const std::string &nodeUserId);
  /**
   * \brief
   * Finds the given edge defined by v1 and v2 within the graph.
   *
   * @param v1 The first vertex.
   * @param v2 The second vertex.
   * @param id The edge id if the edge is found. Otherwise set to 0.
   * @return True if the edge exists in the graph.
   */
  virtual bool findEdge(const Node<T> *v1, const Node<T> *v2,
                        CXXGraph::id_t &id) const;
  /**
   * \brief
   * Overload of findEdge which takes shared pointers as parameters
   *
   * @param v1 The first vertex.
   * @param v2 The second vertex.
   * @param id The edge id if the edge is found. Otherwise set to 0.
   * @return True if the edge exists in the graph.
   */
  virtual bool findEdge(shared<const Node<T>> v1, shared<const Node<T>> v2,
                        CXXGraph::id_t &id) const;
  /**
   * \brief
   * Function that return the Node Set of the Graph
   * Note: No Thread Safe
   *
   * @returns a list of Nodes of the graph
   *
   */
  virtual const T_NodeSet<T> getNodeSet() const;
  /**
   * \brief
   * Function that return the Set of isolated nodes
   * in the Graph
   * Note: No Thread Safe
   *
   * @returns a list of Nodes of the graph
   *
   */
  virtual const T_NodeSet<T> getIsolatedNodeSet() const;
  /**
   * \brief
   * Function that sets the data contained in a node
   *
   * @param nodeUserId The userId string of the node whose data is to be changes
   * @param data The new value for the node data
   *
   */
  virtual void setNodeData(const std::string &nodeUserId, T data);
  /**
   * \brief
   * Function that sets the data contained in every node of the graph
   *
   * @param dataMap Map of the userId of every node with its new data value
   *
   */
  virtual void setNodeData(std::map<std::string, T> &dataMap);
  /**
   * \brief
   * Function that return an Edge with specific ID if Exist in the Graph
   * Note: No Thread Safe
   *
   * @param edgeId The Edge Id to return
   * @returns the Edge if exist
   *
   */
  virtual const std::optional<shared<const Edge<T>>> getEdge(
      const CXXGraph::id_t edgeId) const;
  /**
   * \brief
   * Function that return a Node with specific ID if Exist in the Graph
   * Note: No Thread Safe
   *
   * @param nodeId The Node Id to return
   * @returns the Node if exist
   *
   */
  virtual const std::optional<shared<const Node<T>>> getNode(
      const std::string &nodeUserId) const;
  /**
   * @brief This function generate a list of adjacency matrix with every element
   * of the matrix contain the node where is directed the link and the Edge
   * corrispondent to the link
   * Note: No Thread Safe
   */
  virtual shared<AdjacencyMatrix<T>> getAdjMatrix() const;

  virtual void cacheAdjMatrix();
  /**
   * @brief This function generates a list of the degree matrix with every
   * element of the matrix containing the node where the link is directed and
   * the corresponding edge to the link. Note: No Thread Safe
   */
  virtual shared<DegreeMatrix<T>> getDegreeMatrix() const;

  virtual void cacheDegreeMatrix();
  /**
   * @brief This function generates a list of the Laplacian matrix with every
   * element of the matrix containing the node connected to the current node and
   * the corresponding edge to the link. Note: No Thread Safe
   */
  virtual shared<LaplacianMatrix<T>> getLaplacianMatrix() const;

  virtual void cacheLaplacianMatrix();
  /**
   * @brief This function generates a list of the transition matrix with every
   * element of the matrix containing the node that can be transitioned to from
   * the current node and the probability of the transition. Note: No Thread
   * Safe
   */
  virtual shared<TransitionMatrix<T>> getTransitionMatrix() const;

  virtual void cacheTransitionMatrix();
  /**
   * \brief This function generates a set of nodes linked to the provided node
   * in a directed graph
   *
   * @param Pointer to the node
   *
   */
  virtual const std::unordered_set<shared<const Node<T>>, nodeHash<T>>
  outNeighbors(const Node<T> *node) const;
  /**
   * \brief This function generates a set of nodes linked to the provided node
   * in a directed graph
   *
   * @param Pointer to the node
   *
   */
  virtual const std::unordered_set<shared<const Node<T>>, nodeHash<T>>
  outNeighbors(shared<const Node<T>> node) const;
  /**
   * \brief This function generates a set of nodes linked to the provided node
   * in any graph
   *
   * @param Pointer to the node
   *
   */
  virtual const std::unordered_set<shared<const Node<T>>, nodeHash<T>>
  inOutNeighbors(const Node<T> *node) const;
  /**
   * \brief
   * \brief This function generates a set of nodes linked to the provided node
   * in any graph
   *
   * @param Pointer to the node
   *
   */
  virtual const std::unordered_set<shared<const Node<T>>, nodeHash<T>>
  inOutNeighbors(shared<const Node<T>> node) const;
  /**
   * \brief
   * \brief This function generates a set of Edges going out of a node
   * in any graph
   *
   * @param Pointer to the node
   *
   */
  virtual const std::unordered_set<shared<const Edge<T>>, edgeHash<T>> outEdges(
      const Node<T> *node) const;
  /**
   * \brief
   * \brief This function generates a set of Edges going out of a node
   * in any graph
   *
   * @param Shared pointer to the node
   *
   */
  virtual const std::unordered_set<shared<const Edge<T>>, edgeHash<T>> outEdges(
      shared<const Node<T>> node) const;
  /**
   * \brief
   * \brief This function generates a set of Edges coming in or going out of
   * a node in any graph
   *
   * @param Pointer to the node
   *
   */
  virtual const std::unordered_set<shared<const Edge<T>>, edgeHash<T>>
  inOutEdges(const Node<T> *node) const;
  /**
   * \brief
   * \brief This function generates a set of Edges coming in or going out of
   * a node in any graph
   *
   * @param Shared pointer to the node
   *
   */
  virtual const std::unordered_set<shared<const Edge<T>>, edgeHash<T>>
  inOutEdges(shared<const Node<T>> node) const;
  /**
   * @brief This function finds the subset of given a nodeId
   * Subset is stored in a map where keys are the hash-id of the node & values
   * is the subset.
   * @param subset query subset, we want to find target in this subset
   * @param elem elem that we wish to find in the subset
   *
   * @return parent node of elem
   * Note: No Thread Safe
   */
  virtual CXXGraph::id_t setFind(std::unordered_map<CXXGraph::id_t, Subset> *,
                                 const CXXGraph::id_t elem) const;
  /**
   * @brief This function finds the subset of given a nodeId
   * Subset is stored in a map where keys are the hash-id of the node & values
   * is the subset.
   * @param shared pointer to subset query subset, we want to find target in
   * this subset
   * @param elem elem that we wish to find in the subset
   *
   * @return parent node of elem
   * Note: No Thread Safe
   */
  virtual CXXGraph::id_t setFind(
      shared<std::unordered_map<CXXGraph::id_t, Subset>>,
      const CXXGraph::id_t elem) const;
  /**
   * @brief This function modifies the original subset array
   * such that it the union of two sets a and b
   * @param subset original subset is modified to obtain union of a & b
   * @param a parent id of set1
   * @param b parent id of set2
   * NOTE: Original subset is no longer available after union.
   * Note: No Thread Safe
   */
  virtual void setUnion(std::unordered_map<CXXGraph::id_t, Subset> *,
                        const CXXGraph::id_t set1,
                        const CXXGraph::id_t elem2) const;
  /**
   * @brief This function modifies the original subset array
   * such that it the union of two sets a and b
   * @param subset original subset is modified to obtain union of a & b
   * @param a parent id of set1
   * @param b parent id of set2
   * NOTE: Original subset is no longer available after union.
   * Note: No Thread Safe
   */
  virtual void setUnion(shared<std::unordered_map<CXXGraph::id_t, Subset>>,
                        const CXXGraph::id_t set1,
                        const CXXGraph::id_t elem2) const;
  /**
   * @brief This function finds the eulerian path of a directed graph using
   * hierholzers algorithm
   *
   * @return a vector containing nodes in eulerian path
   * Note: No Thread Safe
   */
  virtual std::shared_ptr<std::vector<Node<T>>> eulerianPath() const;
  /**
   * @brief Function runs the dijkstra algorithm for some source node and
   * target node in the graph and returns the shortest distance of target
   * from the source.
   * Note: No Thread Safe
   *
   * @param source source vertex
   * @param target target vertex
   *
   * @return shortest distance if target is reachable from source else ERROR in
   * case if target is not reachable from source or there is error in the
   * computation.
   */
  virtual const DijkstraResult dijkstra(const Node<T> &source,
                                        const Node<T> &target) const;
  /**
   * @brief This function runs the tarjan algorithm and returns different types
   * of results depending on the input parameter typeMask.
   *
   * @param typeMask each bit of typeMask within valid range represents a kind
   * of results should be returned.
   *
   * Note: No Thread Safe
   *
   * @return The types of return include strongly connected components
   * (only for directed graphs) and cut vertices、 bridges、edge
   * biconnected components and vertice biconnected components
   * (only for undirected graphs).
   */
  virtual const TarjanResult<T> tarjan(const unsigned int typeMask) const;
  /**
   * @brief Function runs the bellman-ford algorithm for some source node and
   * target node in the graph and returns the shortest distance of target
   * from the source. It can also detect if a negative cycle exists in the
   * graph. Note: No Thread Safe
   *
   * @param source source vertex
   * @param target target vertex
   *
   * @return shortest distance if target is reachable from source else ERROR in
   * case if target is not reachable from source. If there is no error then also
   * returns if the graph contains a negative cycle.
   */
  virtual const BellmanFordResult bellmanford(const Node<T> &source,
                                              const Node<T> &target) const;
  /**
   * @brief This function computes the transitive reduction of the graph,
   * returning a graph with the property of transitive closure satisfied. It
   * removes the "short-circuit" paths from a graph, leaving only the longest
   * paths. Commonly used to remove duplicate edges among nodes that do not pass
   * through the entire graph.
   * @return A copy of the current graph with the transitive closure property
   * satisfied.
   *
   */
  virtual const Graph<T> transitiveReduction() const;
  /**
   * @brief Function runs the floyd-warshall algorithm and returns the shortest
   * distance of all pair of nodes. It can also detect if a negative cycle
   * exists in the graph. Note: No Thread Safe
   * @return a map whose keys are node ids and values are the shortest distance.
   * If there is no error then also returns if the graph contains a negative
   * cycle.
   */
  virtual const FWResult floydWarshall() const;
  /**
   * @brief Function runs the prim algorithm and returns the minimum spanning
   * tree if the graph is undirected. Note: No Thread Safe
   * @return a vector containing id of nodes in minimum spanning tree & cost of
   * MST
   */
  virtual const MstResult prim() const;
  /**
   * @brief Function runs the boruvka algorithm and returns the minimum spanning
   * tree & cost if the graph is undirected. Note: No Thread Safe
   * @return struct of type MstResult with following fields
   * success: true if algorithm completed successfully ELSE false
   * mst: vector containing id of nodes in minimum spanning tree & cost of MST
   * mstCost: Cost of MST
   * errorMessage: "" if no error ELSE report the encountered error
   */
  virtual const MstResult boruvka() const;
  /**
   * @brief Function runs the kruskal algorithm and returns the minimum spanning
   * tree if the graph is undirected. Note: No Thread Safe
   * @return struct of type MstResult with following fields
   * success: true if algorithm completed successfully ELSE false
   * mst: vector containing id of nodes in minimum spanning tree & cost of MST
   * mstCost: Cost of MST
   * errorMessage: "" if no error ELSE report the encountered error
   */
  virtual const MstResult kruskal() const;
  /**
   * \brief
   * Function runs the best first search algorithm over the graph
   * using an evaluation function to decide which adjacent node is
   * most promising to explore
   * Note: No Thread Safe
   *
   * @param source source node
   * @param target target node
   * @returns a struct with a vector of Nodes if target is reachable else ERROR
   * in case if target is not reachable or there is an error in the computation.
   *
   */
  virtual BestFirstSearchResult<T> best_first_search(
      const Node<T> &source, const Node<T> &target) const;
  /**
   * \brief
   * Function performs the breadth first search algorithm over the graph
   * Note: No Thread Safe
   *
   * @param start Node from where traversing starts
   * @returns a vector of Node indicating which Node were visited during the
   * search.
   *
   */
  virtual const std::vector<Node<T>> breadth_first_search(
      const Node<T> &start) const;
  /**
   * \brief
   * The multithreaded version of breadth_first_search
   * It turns out to be two indepentent functions because of implemntation
   * differences
   *
   * @param start Node from where traversing starts
   * @param num_threads number of threads
   * @returns a vector of Node indicating which Node were visited during the
   * search.
   *
   */
  virtual const std::vector<Node<T>> concurrency_breadth_first_search(
      const Node<T> &start, size_t num_threads) const;
  /**
   * \brief
   * Function performs the depth first search algorithm over the graph
   * Note: No Thread Safe
   *
   * @param start Node from where traversing starts
   * @returns a vector of Node indicating which Node were visited during the
   * search.
   *
   */
  virtual const std::vector<Node<T>> depth_first_search(
      const Node<T> &start) const;

  /**
   * \brief
   * This function uses DFS to check for cycle in the graph.
   * Pay Attention, this function work only with directed Graph
   * Note: No Thread Safe
   *
   * @return true if a cycle is detected, else false. ( false is returned also
   * if the graph in indirected)
   */
  virtual bool isCyclicDirectedGraphDFS() const;

  /**
   * \brief
   * This function uses BFS to check for cycle in the graph.
   * Pay Attention, this function work only with directed Graph
   * Note: No Thread Safe
   *
   * @return true if a cycle is detected, else false. ( false is returned also
   * if the graph in indirected)
   */
  virtual bool isCyclicDirectedGraphBFS() const;

  /**
   * @brief
   * This function checks if the given set of edges
   * forms a cycle or not using union-find method.
   *
   * @return true if a cycle is detected, else false
   */
  virtual bool containsCycle(const T_EdgeSet<T> *) const;
  /**
   * @brief
   * This function checks if the given set of edges
   * forms a cycle or not using union-find method.
   *
   * @return true if a cycle is detected, else false
   */
  virtual bool containsCycle(shared<const T_EdgeSet<T>>) const;
  /**
   * @brief
   * This function checks if the given Subset
   * forms a cycle or not using union-find method.
   *
   * @return true if a cycle is detected, else false
   */
  virtual bool containsCycle(
      shared<const T_EdgeSet<T>> edgeSet,
      shared<std::unordered_map<CXXGraph::id_t, Subset>>) const;

  /**
   * \brief
   * This function checks if a graph is directed
   * Note: No Thread Safe
   *
   * @return true if the graph is directed, else false.
   */
  virtual bool isDirectedGraph() const;

  /**
   * \brief
   * This function checks if a graph is undirected
   * Note: No Thread Safe
   *
   * @return true if the graph is undirected, else false.
   */
  virtual bool isUndirectedGraph() const;

  /**
   * @brief This function reverse the direction of the edges in a directed graph
   */
  virtual void reverseDirectedGraph();

  /**
   * @brief This function checks if the graph is connected or not
   * 	Applicable for Undirected Graph, for Directed Graph use the
   * isStronglyConnectedGraph() function
   *
   * @return true if the graph is connected
   * @return false otherwise
   */
  virtual bool isConnectedGraph() const;

  /**
   * @brief This function checks if the graph is strongly connected or not
   * 	Applicable for Directed Graph, for Undirected Graph use the
   * isConnectedGraph() function
   *
   * @return true if the graph is connected
   * @return false otherwise
   */
  virtual bool isStronglyConnectedGraph() const;

  /**
   * @brief This function sort nodes in topological order.
   * 	Applicable for Directed Acyclic Graph
   *
   * @return a struct with a vector of Nodes ordered topologically else ERROR in
   * case of undirected or cyclic graph
   */
  virtual TopoSortResult<T> topologicalSort() const;

  /**
   * @brief This function sort nodes in topological order using kahn's algorithm
   * 	Applicable for Directed Acyclic Graph
   *
   * @return a struct with a vector of Nodes ordered topologically else ERROR in
   * case of undirected or cyclic graph
   */
  virtual TopoSortResult<T> kahn() const;

  /**
  * \brief
  * This function performs performs the kosaraju algorthm on the graph to find
  the strongly connected components.
  *
  * Mathematical definition of the problem:
  * A strongly connected component (SCC) of a directed graph is a maximal
  strongly connected subgraph.

  * Note: No Thread Safe
  * @return a vector of vector of strongly connected components.
  */
  virtual SCCResult<T> kosaraju() const;

  /**
  * \brief
  * This function performs Graph Slicing based on connectivity
  *
  * Mathematical definition of the problem:
  *
  * Let G be the set of nodes in a graph and n be a given node in that set.
  * Let C be the non-strict subset of G containing both n and all nodes
  reachable
  * from n, and let C' be its complement. There's a third set M, which is the
  * non-strict subset of C containing all nodes that are reachable from any node
  in C'.
  * The problem consists of finding all nodes that belong to C but not to M.

  * Note: No Thread Safe
  * @param start Node from where traversing starts
  * @return a vector of nodes that belong to C but not to M.
  */
  virtual const std::vector<Node<T>> graph_slicing(const Node<T> &start) const;

  /**
   * @brief Function runs the Dial algorithm  (Optimized Dijkstra for small
   * range weights) for some source node and target node in the graph and
   * returns the shortest distance of target from the source. Note: No Thread
   * Safe
   *
   * @param source source vertex
   * @param maxWeight maximum weight of the edge
   *
   * @return shortest distance for all nodes reachable from source else ERROR in
   * case there is error in the computation.
   */
  virtual const DialResult dial(const Node<T> &source, int maxWeight) const;

  /**
   * @brief Function runs the Ford-Fulkerson algorithm for some source node and
   * target node in the graph and returns the maximum flow of the graph
   *
   * @param source source vertex
   * @param target  target vertex
   * @return double Max-Flow value or -1 in case of error
   */
  virtual double fordFulkersonMaxFlow(const Node<T> &source,
                                      const Node<T> &target) const;

  /**
   * \brief
   * This function writes the graph to an output file
   * Note: Not threadsafe
   *
   * @param format The output format of the file
   * @param workingDir The parent directory of the output file
   * @param OFileName The output filename
   * @param compress Enables compression (requires zlib)
   * @param writeNodeFeat Indicates if export also Node Features
   * @param writeEdgeWeight Indicates if export also Edge Weights
   * @return 0 if OK, else return a negative value
   */
  virtual int writeToFile(
      InputOutputFormat format = InputOutputFormat::STANDARD_CSV,
      const std::string &workingDir = ".",
      const std::string &OFileName = "graph", bool compress = false,
      bool writeNodeFeat = false, bool writeEdgeWeight = false) const;

  virtual int writeToDotFile(const std::string &workingDir,
                             const std::string &OFileName,
                             const std::string &graphName) const;

  virtual int writeToMTXFile(const std::string &workingDir,
                             const std::string &OFileName, char delimier) const;

  /**
   * \brief
   * This function reads the graph from an input file
   * Note: Not threadsafe
   *
   * @param format The input format of the file
   * @param workingDir The parent directory of the input
   * file
   * @param OFileName The input filename
   * @param compress Enables compression (requires zlib)
   * @param readNodeFeat Indicates if import also Node Features
   * @param readEdgeWeight Indicates if import also Edge Weights
   * @return 0 if OK, else return a negative value
   */
  virtual int readFromFile(
      InputOutputFormat format = InputOutputFormat::STANDARD_CSV,
      const std::string &workingDir = ".",
      const std::string &OFileName = "graph", bool compress = false,
      bool readNodeFeat = false, bool readEdgeWeight = false);

  virtual int readFromDotFile(const std::string &workingDir,
                              const std::string &fileName);

  virtual int readFromMTXFile(const std::string &workingDir,
                              const std::string &fileName);

  friend std::ostream &operator<< <>(std::ostream &os, const Graph<T> &graph);
  friend std::ostream &operator<< <>(std::ostream &os,
                                     const AdjacencyMatrix<T> &adj);
};

}  // namespace CXXGraph
#endif  // __CXXGRAPH_GRAPH_DECL_H__
