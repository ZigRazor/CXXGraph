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
/***	 License: MPL v2.0 ***/
/***********************************************************/

#ifndef CXXGRAPH_GRAPH_DECL_H_
#define CXXGRAPH_GRAPH_DECL_H_

#pragma once

#include <cmath>
#include <cstring>
#include <deque>
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
#include <vector>

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
using T_EdgeVector = std::vector<shared<const Edge<T>>>;

template <typename T>
using T_NodeSet = std::unordered_set<shared<const Node<T>>, nodeHash<T>>;

template <typename T>
using T_NodeVector = std::vector<shared<const Node<T>>>;

template <typename T>
class Graph;

template <typename T>
std::ostream &operator<<(std::ostream &o, const Graph<T> &graph);
template <typename T>
std::ostream &operator<<(std::ostream &o, const AdjacencyList<T> &adj);

/// Class that implement the Graph. ( This class is not Thread Safe )
template <typename T>
class Graph {
 public:
  /**
   * @brief Write the graph to a binary file
   * @param workingDir The parent directory of the output file
   * @param fileName The output filename (without extension)
   * @param writeNodeFeatures Whether to include node features
   * @param writeEdgeWeights Whether to include edge weights
   * @return 0 if successful, negative value on error:
   *         -1: Cannot open file
   *         -2: Write error
   */
  int writeToBinaryFile(const std::string &workingDir,
                        const std::string &fileName,
                        bool writeNodeFeatures = false,
                        bool writeEdgeWeights = true) const;

  /**
   * @brief Read the graph from a binary file
   * @param workingDir The parent directory of the input file
   * @param fileName The input filename (without extension)
   * @param readNodeFeatures Whether to read node features
   * @param readEdgeWeights Whether to read edge weights
   * @return 0 if successful, negative value on error:
   *         -1: Cannot open file
   *         -2: Invalid file format
   *         -3: Unsupported version
   *         -4: Read error
   */
  int readFromBinaryFile(const std::string &workingDir,
                         const std::string &fileName,
                         bool readNodeFeatures = false,
                         bool readEdgeWeights = true);

 private:
  T_EdgeSet<T> edgeSet = {};
  T_NodeSet<T> isolatedNodesSet = {};

  shared<AdjacencyList<T>> cachedAdjListOut;
  shared<AdjacencyList<T>> cachedAdjListIn;
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

  // Binary file format constants
  static constexpr uint32_t BINARY_MAGIC_NUMBER = 0x47525048;  // "GRPH"
  static constexpr uint32_t BINARY_VERSION = 1;
  static constexpr uint64_t BINARY_FLAG_HAS_NODE_FEATURES = 0x01;
  static constexpr uint64_t BINARY_FLAG_HAS_EDGE_WEIGHTS = 0x02;

  // Type trait to check if T is serializable to binary
  template <typename U, typename = void>
  struct is_binary_serializable : std::false_type {};

  template <typename U>
  struct is_binary_serializable<
      U, std::void_t<decltype(std::declval<std::ofstream &>().write(
             reinterpret_cast<const char *>(&std::declval<const U &>()),
             sizeof(U)))>> : std::is_trivially_copyable<U> {};

  // Helper functions for binary I/O
  void writeBinaryString(std::ofstream &out, const std::string &str) const;
  std::string readBinaryString(std::ifstream &in) const;

  /**
   * @brief Write the graph to a binary file
   * @param filepath The full path to the output file
   * @param writeNodeFeatures Whether to include node features
   * @param writeEdgeWeights Whether to include edge weights
   * @return 0 if successful, negative value on error
   */
  int writeToBinary(const std::string &filepath, bool writeNodeFeatures,
                    bool writeEdgeWeights) const;

  /**
   * @brief Read the graph from a binary file
   * @param filepath The full path to the input file
   * @param readNodeFeatures Whether to read node features
   * @param readEdgeWeights Whether to read edge weights
   * @return 0 if successful, negative value on error
   */
  int readFromBinary(const std::string &filepath, bool readNodeFeatures,
                     bool readEdgeWeights);

  void recreateGraph(
      std::unordered_map<std::string, std::pair<std::string, std::string>>
          &edgeMap,
      std::unordered_map<std::string, bool> &edgeDirectedMap,
      std::unordered_map<std::string, T> &nodeFeatMap,
      std::unordered_map<std::string, double> &edgeWeightMap);

  // Type trait used to compile allow compilation when T is not extractable
  template <typename U, typename = void>
  struct is_istream_extractable : std::false_type {};

  template <typename U>
  struct is_istream_extractable<
      U, std::void_t<decltype(std::declval<std::istream &>() >>
                              std::declval<U &>())>> : std::true_type {};

#ifdef WITH_COMPRESSION
  int compressFile(const std::string &inputFile,
                   const std::string &outputFile) const;
  int decompressFile(const std::string &inputFile,
                     const std::string &outputFile) const;
#endif

 public:
  Graph();
  explicit Graph(const T_EdgeSet<T> &edgeSet);
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
   * Function that return the Edge set of the Graph
   * Note: No Thread Safe
   *
   * @returns a list of Edges of the graph
   *
   */
  virtual T_EdgeVector<T> getEdgeVector() const;

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
   * @return The id of the added edge or nullopt if the edge was already present
   * or if failed
   *
   */
  virtual std::optional<CXXGraph::id_t> addEdge(const Edge<T> *edge);

  /**
   * \brief
   * Function add an Edge to the Graph Edge Set
   * First check if a pointer to a node with the same userId has
   * already been added, and if not add it
   * Note: No Thread Safe
   *
   * @param edge The Edge to insert
   * @return The id of the added edge or nullopt if the edge was already present
   * or if failed
   *
   */
  virtual std::optional<CXXGraph::id_t> addEdge(shared<const Edge<T>> edge);

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
  std::enable_if_t<all_are_edge_ptrs_v<T1, Tn...>, void> addEdges(T1 edge,
                                                                  Tn... edges);

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
  std::enable_if_t<all_are_node_ptrs_v<T1, Tn...>, void> addNodes(T1 node,
                                                                  Tn... nodes);

  /**
   * \brief
   * Function remove an Edge from the Graph Edge Set
   * Note: No Thread Safe
   *
   * @param edgeUserId The Edge User Id to remove
   *
   */
  virtual void removeEdge(const std::string &edgeUserId);

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
   * @param edgeId The Node UserId to remove
   *
   */
  virtual void removeNode(const std::string &nodeUserId);

  /**
   * \brief
   * Function to remove a Node from the Graph Node Set
   * Note: No Thread Safe
   *
   * @param edgeId The Node Id to remove
   *
   */
  virtual void removeNode(const CXXGraph::id_t nodeId);

  /**
   * \brief
   * Invalidates and rebuilds the graph's core caches.
   * This includes the adjacency lists, degree matrix, and Laplacian matrix.
   * Optionally, the transition matrix can also be rebuilt.
   *
   * \param includeTransitionMatrix
   * If true, the transition matrix will be rebuilt as part of the cache update.
   *
   * \note Not thread-safe.
   * \note Call after any structural modification of the graph.
   */
  void invalidateCache(bool includeTransitionMatrix);

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
   * Function that return the Node Set of the Graph
   * Note: No Thread Safe
   *
   * @returns a list of Nodes of the graph
   *
   */
  virtual const T_NodeVector<T> getNodeVector() const;

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
   * @param edgeId The Edge UserId to return
   * @returns the Edge if exist
   *
   */
  virtual const std::optional<shared<const Edge<T>>> getEdge(
      const std::string &edgeUserId) const;

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
   * @param nodeId The Node UserId to return
   * @returns the Node if exist
   *
   */
  virtual const std::optional<shared<const Node<T>>> getNode(
      const std::string &nodeUserId) const;

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
      const CXXGraph::id_t nodeId) const;

  /**
   * @brief This function generates an adjacency list with every
   * element of the list containing the node where is directed the link and the
   * Edge corrispondent to the link Note: No Thread Safe
   * Note: No Thread Safe
   */
  virtual shared<AdjacencyList<T>> getAdjListOut() const;

  /**
   * @brief This function generate an adjacency list with every element
   * of the list containing the node where is the origin of the Edge and the
   * Edge corrispondent to the link Note: No Thread Safe
   */
  virtual shared<AdjacencyList<T>> getAdjListIn() const;

  /**
   * @brief This function calculates the adjacency matricies of the graph and
   * stores it in the cachedAdjListOut and cachedAdjListIn variable.
   */
  virtual void cacheAdjLists();

  /**
   * @brief This function generates a list of the degree matrix with every
   * element of the matrix containing the node where the link is directed and
   * the corresponding edge to the link. Note: No Thread Safe
   */
  virtual shared<DegreeMatrix<T>> getDegreeMatrix() const;

  /**
   * @brief This function calculates the degree matrix of the graph and stores
   * it in the cachedDegreeMatrix variable.
   */
  virtual void cacheDegreeMatrix();

  /**
   * @brief This function generates a list of the Laplacian matrix with every
   * element of the matrix containing the node connected to the current node and
   * the corresponding edge to the link. Note: No Thread Safe
   */
  virtual shared<LaplacianMatrix<T>> getLaplacianMatrix() const;

  /**
   * @brief This function calculates the laplacian matrix of the graph and
   * stores it in the cachedLaplacianMatrix variable.
   */
  virtual void cacheLaplacianMatrix();

  /**
   * @brief This function generates a list of the transition matrix with every
   * element of the matrix containing the node that can be transitioned to from
   * the current node and the probability of the transition. Note: No Thread
   * Safe
   */
  virtual shared<TransitionMatrix<T>> getTransitionMatrix() const;

  /**
   * @brief This function calculates the transition matrix of the graph and
   * stores it in the cachedTransitionMatrix variable.
   */
  virtual void cacheTransitionMatrix();

  /**
   * \brief This function generates a set of nodes linked only out (not in) from
   * the provided node in a directed graph
   *
   * @param Pointer to the node
   *
   */
  virtual const std::unordered_set<shared<const Node<T>>, nodeHash<T>>
  outNotInNeighbors(const Node<T> *node) const;

  /**
   * \brief This function generates a set of nodes linked only out (not in) from
   * the provided node in a directed graph
   *
   * @param Pointer to the node
   *
   */
  virtual const std::unordered_set<shared<const Node<T>>, nodeHash<T>>
  outNotInNeighbors(shared<const Node<T>> node) const;

  /**
   * \brief This function generates a set of nodes linked only in (not out) of
   * the provided node in a directed graph
   *
   * @param Pointer to the node
   *
   */
  virtual const std::unordered_set<shared<const Node<T>>, nodeHash<T>>
  inNotOutNeighbors(const Node<T> *node) const;

  /**
   * \brief This function generates a set of nodes linked only in (not out) of
   * the provided node in a directed graph
   *
   * @param Pointer to the node
   *
   */
  virtual const std::unordered_set<shared<const Node<T>>, nodeHash<T>>
  inNotOutNeighbors(shared<const Node<T>> node) const;

  /**
   * \brief This function generates a set of nodes linked to the provided node
   * in any graph
   *
   * @param Pointer to the node
   *
   */
  virtual const std::unordered_set<shared<const Node<T>>, nodeHash<T>>
  inOrOutNeighbors(const Node<T> *node) const;

  /**
   * \brief
   * \brief This function generates a set of nodes linked to the provided node
   * in any graph
   *
   * @param Pointer to the node
   *
   */
  virtual const std::unordered_set<shared<const Node<T>>, nodeHash<T>>
  inOrOutNeighbors(shared<const Node<T>> node) const;

  /**
   * \brief
   * \brief This function generates a set of directed Edges going only out of
   * (not in) to a node in any graph
   *
   * @param Pointer to the node
   *
   */
  virtual const std::unordered_set<shared<const Edge<T>>, edgeHash<T>>
  outNotInEdges(const Node<T> *node) const;

  /**
   * \brief This function generates a set of directed Edges going only out of
   * (not in) to a node in any graph
   *
   * @param Shared pointer to the node
   *
   */
  virtual const std::unordered_set<shared<const Edge<T>>, edgeHash<T>>
  outNotInEdges(shared<const Node<T>> node) const;

  /**
   * \brief
   * \brief This function generates a set of directed Edges going only out of
   * (not in) to a node in any graph
   *
   * @param Pointer to the node
   *
   */
  virtual const std::unordered_set<shared<const Edge<T>>, edgeHash<T>>
  inNotOutEdges(const Node<T> *node) const;

  /**
   * \brief This function generates a set of directed Edges going only out of
   * (not in) to a node in any graph
   *
   * @param Shared pointer to the node
   *
   */
  virtual const std::unordered_set<shared<const Edge<T>>, edgeHash<T>>
  inNotOutEdges(shared<const Node<T>> node) const;

  /**
   * \brief
   * \brief This function generates a set of Edges coming in or going out of
   * a node in any graph
   *
   * @param Pointer to the node
   *
   */
  virtual const std::unordered_set<shared<const Edge<T>>, edgeHash<T>>
  inOrOutEdges(const Node<T> *node) const;

  /**
   * \brief
   * \brief This function generates a set of Edges coming in or going out of
   * a node in any graph
   *
   * @param Shared pointer to the node
   *
   */
  virtual const std::unordered_set<shared<const Edge<T>>, edgeHash<T>>
  inOrOutEdges(shared<const Node<T>> node) const;

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
   * @brief Function runs the dijkstra algorithm with inverted metric for some
   * source node and target node in the graph and returns the longest distance
   * of target from the source (called critical path). Note: No Thread Safe
   *
   * @param source source vertex
   * @param target target vertex
   *
   * @return longest distance if target is reachable from source else ERROR in
   * case if target is not reachable from source or there is error in the
   * computation.
   */
  virtual const DijkstraResult criticalpath_deterministic(
      const Node<T> &source, const Node<T> &target) const;

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
   * @brief Deterministic implementation of the dijkstra algorithm
   * Note: No Thread Safe
   *
   * @param source source vertex
   * @param target target vertex
   *
   * @return shortest distance if target is reachable from source else ERROR in
   * case if target is not reachable from source or there is error in the
   * computation.
   */
  virtual const DijkstraResult dijkstra_deterministic(
      const Node<T> &source, const Node<T> &target) const;

  /**
   * @brief Alternative version of the deterministic dijkstra algorithm which
   * assures complete determinism even in particular cases of paths with equal
   * length and sum of vertex ids. More spatially and temporally expensive
   * than the other two implementations of the algorithm.
   * Note: No Thread Safe
   *
   * @param source source vertex
   * @param target target vertex
   *
   * @return shortest distance if target is reachable from source else ERROR in
   * case if target is not reachable from source or there is error in the
   * computation.
   */
  virtual const DijkstraResult dijkstra_deterministic2(
      const Node<T> &source, const Node<T> &target) const;

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
   * @brief Deterministic implementation of the boruvka algorithm
   * Note: No Thread Safe
   *
   * @return struct of type MstResult with following fields
   * success: true if algorithm completed successfully ELSE false
   * mst: vector containing id of nodes in minimum spanning tree & cost of MST
   * mstCost: Cost of MST
   * errorMessage: "" if no error ELSE report the encountered error
   */
  virtual const MstResult boruvka_deterministic() const;

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

  virtual const BronKerboschResult<T> bron_kerbosch() const;

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
   * @brief This function performs the Hopcroft-Karp algorithm to find the
   * maximum matching in a bipartite graph.
   *
   * @return HopcroftKarpResult containing success status, error message (if
   * any), the size of maximum matching, and the actual matching pairs
   *
   * Note: The function requires an undirected graph. If the graph is not
   * bipartite, the algorithm will return a matching of size 0 with success =
   * true.
   *
   * Complexity: O(E√V) where E is the number of edges and V is the number of
   * vertices
   */
  virtual const HopcroftKarpResult_struct hopcroftKarp() const;

  /**
   * @brief Welsh-Powell Coloring algorithm
   * @return a std::map of keys being the nodes and the values being the color
   * order (by integer) starting from 1.
   * Source :
   *          https://www.youtube.com/watch?v=SLkyDuG1Puw&ab_channel=TheLogicalLearning
   *          https://www.geeksforgeeks.org/welsh-powell-graph-colouring-algorithm/
   *          https://www.tutorialspoint.com/de-powell-graph-colouring-algorithm
   */
  virtual std::map<Node<T>, int> welshPowellColoring() const;

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

  /**
   * @brief This function writes the graph to a dot file
   *
   * @param workingDir The parent directory of the output file
   * @param OFileName The output filename
   * @param graphName The name of the graph
   * @return 0 if OK, else return a negative value
   */
  virtual int writeToDotFile(const std::string &workingDir,
                             const std::string &OFileName,
                             const std::string &graphName) const;
  /**
   * @brief This function writes the graph to a MTX file
   * @param workingDir The parent directory of the output file
   * @param OFileName The output filename
   * @param delimier The delimiter to use in the file
   * @return 0 if OK, else return a negative value
   */
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
  /**
   * @brief This function reads the graph from a dot file
   *
   * @param workingDir The parent directory of the input file
   * @param fileName The input filename
   * @return 0 if OK, else return a negative value
   */
  virtual int readFromDotFile(const std::string &workingDir,
                              const std::string &fileName);
  /**
   * @brief This function reads the graph from a MTX file
   *
   * @param workingDir The parent directory of the input file
   * @param fileName The input filename
   * @return 0 if OK, else return a negative value
   */
  virtual int readFromMTXFile(const std::string &workingDir,
                              const std::string &fileName);

  friend std::ostream &operator<< <>(std::ostream &os, const Graph<T> &graph);
  friend std::ostream &operator<< <>(std::ostream &os,
                                     const AdjacencyList<T> &adj);
};

}  // namespace CXXGraph
#endif  // CXXGRAPH_GRAPH_DECL_H_
