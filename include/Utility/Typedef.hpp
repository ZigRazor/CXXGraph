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

#ifndef __CXXGRAPH_TYPEDEF_H__
#define __CXXGRAPH_TYPEDEF_H__

#pragma once

#include <fstream>
#include <map>
#include <memory>
#include <string>

#include "ConstValue.hpp"
#include "PointerHash.hpp"

namespace CXXGraph {
// Smart pointers alias
template <typename T>
using unique = std::unique_ptr<T>;
template <typename T>
using shared= std::shared_ptr<T>;

using std::make_unique;
using std::make_shared;

template <typename T>
class Node;

template <typename T>
class Edge;

namespace Partitioning {
template <typename T>
class Partition;
}
// ENUMERATION //////////////////////////////////////

/// Specify the Input/Output format of the Graph for Import/Export functions
enum E_InputOutputFormat {
  STANDARD_CSV,  ///< A standard csv format
  STANDARD_TSV,  ///< A standard tsv format
  OUT_1,
  OUT_2
};

typedef E_InputOutputFormat InputOutputFormat;

/////////////////////////////////////////////////////
// Structures ///////////////////////////////////////

/// Struct useful for union-find operations
struct Subset_struct {
  unsigned long long parent = 0;  // parent of the current set
  unsigned long long rank =
      0;  // rank of the current set, used for balancing the trees
};
typedef Subset_struct Subset;

/// Struct that contains the information about Dijsktra's Algorithm results
struct DijkstraResult_struct {
  bool success =
      false;  // TRUE if the function does not return error, FALSE otherwise
  std::string errorMessage = "";  // message of error
  double result = INF_DOUBLE;     // result (valid only if success is TRUE)
};
typedef DijkstraResult_struct DijkstraResult;

/// Struct that contains the information about Dijsktra's Algorithm results
struct BellmanFordResult_struct {
  bool success =
      false;  // TRUE if the function does not return error, FALSE otherwise
  bool negativeCycle =
      false;  // TRUE if graph contains a negative cycle, FALSE otherwise
  std::string errorMessage = "";  // message of error
  double result =
      0.0;  // result (valid only if success is TRUE & negativeCycle is false )
};
typedef BellmanFordResult_struct BellmanFordResult;

// implmentation is similar to boost hash_combine
template <typename T>
inline T hash_combine(T &lhs, const T &rhs) {
  T result = lhs ^ (rhs + 0x9e3779b9 + (lhs << 6) + (lhs >> 2));
  return result;
}

/// The C++ Standard doesn't provide a hash for std::pair type, which is
/// required when using std::pair as a key in std::unordered_map. So, hash
/// function for pair needs to be provided. Hash for a pair is calculated by
/// calcuating hash for individual elements and then combining. For combining,
/// an implmentation similar to boost hash_combine is implemented.
struct pair_hash {
  template <class T1, class T2>
  std::size_t operator()(const std::pair<T1, T2> &p) const {
    std::size_t h1 = std::hash<T1>{}(p.first);
    std::size_t h2 = std::hash<T2>{}(p.second);
    return hash_combine(h1, h2);
  }
};

/// Struct that contains the information about Floyd-Warshall Algorithm results
struct FWResult_struct {
  bool success =
      false;  // TRUE if the function does not return error, FALSE otherwise
  bool negativeCycle =
      false;  // TRUE if graph contains a negative cycle, FALSE otherwise
  std::string errorMessage = "";  // message of error
  std::unordered_map<std::pair<std::string, std::string>, double, pair_hash>
      result = {};
};
typedef FWResult_struct FWResult;

/// Struct that contains the information about Prim, Boruvka & Kruskal Algorithm
/// results
struct MstResult_struct {
  bool success =
      false;  // TRUE if the function does not return error, FALSE otherwise
  std::string errorMessage = "";  // message of error
  std::vector<std::pair<std::string, std::string>> mst =
      {};  // Stores the nodes of MST (string node-names are set by user during
           // init)
  double mstCost = 0.0;  // MST
};
typedef MstResult_struct MstResult;

/// Struct that contains the information about Dijsktra's Algorithm results
struct DialResult_struct {
  bool success =
      false;  // TRUE if the function does not return error, FALSE otherwise
  std::string errorMessage = "";  // message of error
  std::unordered_map<unsigned long long, long> minDistanceMap =
      {};  // result a map that contains the node id and the minumum distance
           // from source (valid only if success is TRUE)
};
typedef DialResult_struct DialResult;

/// Struct that contains the information about TopologicalSort's Algorithm
/// results
template <typename T>
struct TopoSortResult_struct {
  bool success =
      false;  // TRUE if the function does not return error, FALSE otherwise
  std::string errorMessage = "";  // message of error
  std::vector<Node<T>> nodesInTopoOrder =
      {};  // result a vector that contains the nodes in topological order
           // (valid only if success is TRUE)

  /*
  TopoSortResult & operator=(TopoSortResult_struct && res)
      : success(res.success),
        errorMessage(move(res.errorMessage))
        nodesInTopoOrder(move(res.nodesInTopoOrder))
  {}
  */
};
template <typename T>
using TopoSortResult = TopoSortResult_struct<T>;

// typedef for a collection of sets of vertices (useful for connected components
// algorithms)
template <typename T>
using Components = std::vector<std::vector<Node<T>>>;

/// Struct that contains the information about strongly connected components
/// (SCC) algorithms results
template <typename T>
struct SCCResult_struct {
  bool success =
      false;  // TRUE if the function does not return error, FALSE otherwise
  std::string errorMessage = "";  // message of error
  Components<T> stronglyConnectedComps;
};
template <typename T>
using SCCResult = SCCResult_struct<T>;

/// Struct that contains the information about Best First Search Algorithm
/// results
template <typename T>
struct BestFirstSearchResult_struct {
  bool success = false;
  std::string errorMessage = "";
  std::vector<Node<T>> nodesInBestSearchOrder = {};
};
template <typename T>
using BestFirstSearchResult = BestFirstSearchResult_struct<T>;

/// Struct that contains the information about the partitioning statistics

///////////////////////////////////////////////////////////////////////////////////
// Using Definition
// ///////////////////////////////////////////////////////////////

template <typename T>
using AdjacencyMatrix = std::unordered_map<
    shared<const Node<T>>, std::vector<std::pair<shared<const Node<T>>, shared<const Edge<T>>>>, nodeHash<T>>;

template <typename T>
using PartitionMap =
    std::unordered_map<unsigned int,
                       std::shared_ptr<Partitioning::Partition<T>>>;

///////////////////////////////////////////////////////////////////////////////////
}  // namespace CXXGraph

#endif  // __CXXGRAPH_TYPEDEF_H__
