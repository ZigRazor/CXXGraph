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

#ifndef __CXXGRAPH_PARTITION_H__
#define __CXXGRAPH_PARTITION_H__

#pragma once

#include <list>
#include <memory>
#include <unordered_set>

#include "PartitioningStats.hpp"
#include "Utility/Typedef.hpp"

namespace CXXGraph {
// Smart pointers alias
template <typename T>
using unique = std::unique_ptr<T>;
template <typename T>
using shared= std::shared_ptr<T>;

using std::make_unique;
using std::make_shared;

template <typename T>
class Graph;

template <typename T>
using T_EdgeSet = std::unordered_set<shared<const Edge<T>>, edgeHash<T>>;
namespace Partitioning {
template <typename T>
std::ostream &operator<<(std::ostream &o, const Partition<T> &partition);

template <typename T>
class Partition : public Graph<T> {
 public:
  Partition();
  explicit Partition(const CXXGraph::id_t partitionId);
  explicit Partition(const T_EdgeSet<T> &edgeSet);
  Partition(const CXXGraph::id_t partitionId, const T_EdgeSet<T> &edgeSet);
  ~Partition() = default;
  /**
   * @brief Get the Partition ID
   *
   * @return The ID of the partition
   */
  CXXGraph::id_t getPartitionId() const;
  /**
   * @brief Set the Partition ID
   *
   * @param partitionId the ID to set
   */
  void setPartitionId(const CXXGraph::id_t partitionId);

 private:
  CXXGraph::id_t partitionId = 0;
};

/**
 * @brief Calculate and return the statistic of the Partitioned Graph
 *
 * @param partitionMap the Partition Map
 *
 * @return The Statistic of the Partioned Graph
 */
template <typename T>
static PartitioningStats getPartitionStats(const PartitionMap<T> &partitionMap);

/**
 * @brief Calculate the Maximum Load in a single partition (in terms of edges)
 * for the Partioned Graph
 *
 * @param partitionMap the Partition Map
 *
 * @return The value of the Maximum Load
 */
template <typename T>
static unsigned int getMaxEdgesLoad(const PartitionMap<T> &partitionMap);

/**
 * @brief Calculate the Minimum Load in a single partition (in terms of edges)
 * for the Partioned Graph
 *
 * @param partitionMap the Partition Map
 *
 * @return The value of the Minimum Load
 */
template <typename T>
static unsigned int getMinEdgesLoad(const PartitionMap<T> &partitionMap);

/**
 * @brief Calculate the Maximum Load in a single partition (in terms of nodes)
 * for the Partioned Graph
 *
 * @param partitionMap the Partition Map
 *
 * @return The value of the Maximum Load
 */
template <typename T>
static unsigned int getMaxNodesLoad(const PartitionMap<T> &partitionMap);

/**
 * @brief Calculate the Minimum Load in a single partition (in terms of nodes)
 * for the Partioned Graph
 *
 * @param partitionMap the Partition Map
 *
 * @return The value of the Minimum Load
 */
template <typename T>
static unsigned int getMinNodesLoad(const PartitionMap<T> &partitionMap);

/**
 * @brief Calculate the Number of Unique Edges in the Partitioned Graph ( this
 * value is equal to the number of edges in the Original Graph)
 *
 * @param partitionMap the Partition Map
 *
 * @return The number of Edges
 */
template <typename T>
static unsigned int getNumberOfEdges(const PartitionMap<T> &partitionMap);

/**
 * @brief Calculate the Number of Unique Nodes in the Partitioned Graph ( this
 * value is equal to the number of nodes in the Original Graph)
 *
 * @param partitionMap the Partition Map
 *
 * @return The number of Nodes
 */
template <typename T>
static unsigned int getNumberOfNodes(const PartitionMap<T> &partitionMap);

/**
 * @brief Calculate the Total Number of Edges in the Partitioned Graph
 *
 * @param partitionMap the Partition Map
 *
 * @return The number of Edges
 */
template <typename T>
static unsigned int getNumberOfReplicatedEdges(
    const PartitionMap<T> &partitionMap);

/**
 * @brief Calculate the Total Number of Nodes in the Partitioned Graph
 *
 * @param partitionMap the Partition Map
 *
 * @return The number of Nodes
 */
template <typename T>
static unsigned int getNumberOfReplicatedNodes(
    const PartitionMap<T> &partitionMap);

template <typename T>
Partition<T>::Partition() : Graph<T>() {
  partitionId = 0;
}

template <typename T>
Partition<T>::Partition(const CXXGraph::id_t partitionId) : Graph<T>() {
  this->partitionId = partitionId;
}

template <typename T>
Partition<T>::Partition(const T_EdgeSet<T> &edgeSet) : Graph<T>(edgeSet) {
  partitionId = 0;
}

template <typename T>
Partition<T>::Partition(const CXXGraph::id_t partitionId,
                        const T_EdgeSet<T> &edgeSet)
    : Graph<T>(edgeSet) {
  this->partitionId = partitionId;
}

template <typename T>
CXXGraph::id_t Partition<T>::getPartitionId() const {
  return partitionId;
}

template <typename T>
void Partition<T>::setPartitionId(const CXXGraph::id_t partitionId) {
  this->partitionId = partitionId;
}

template <typename T>
PartitioningStats getPartitionStats(const PartitionMap<T> &partitionMap) {
  PartitioningStats result;
  result.numberOfPartitions = partitionMap.size();
  result.numberOfNodes = getNumberOfNodes(partitionMap);
  result.numberOfEdges = getNumberOfEdges(partitionMap);
  result.replicatedNodesCount = getNumberOfReplicatedNodes(partitionMap);
  result.replicatedEdgesCount = getNumberOfReplicatedEdges(partitionMap);
  result.maxEdgesLoad = getMaxEdgesLoad(partitionMap);
  result.minEdgesLoad = getMinEdgesLoad(partitionMap);
  result.maxNodesLoad = getMaxNodesLoad(partitionMap);
  result.minNodesLoad = getMinNodesLoad(partitionMap);
  result.edgesReplicationFactor =
      static_cast<double>(result.replicatedEdgesCount) / result.numberOfEdges;
  result.nodesReplicationFactor =
      static_cast<double>(result.replicatedNodesCount) / result.numberOfNodes;
  result.balanceEdgesFactor =
      static_cast<double>((result.maxEdgesLoad - result.minEdgesLoad)) /
      (result.maxEdgesLoad);
  result.balanceNodesFactor =
      static_cast<double>((result.maxNodesLoad - result.minNodesLoad)) /
      (result.maxNodesLoad);
  return result;
}

template <typename T>
unsigned int getMaxEdgesLoad(const PartitionMap<T> &partitionMap) {
  unsigned int maxLoad = 0;
  for (const auto &it : partitionMap) {
    if (it.second->getEdgeSet().size() > maxLoad) {
      maxLoad = it.second->getEdgeSet().size();
    }
  }
  return maxLoad;
}

template <typename T>
unsigned int getMinEdgesLoad(const PartitionMap<T> &partitionMap) {
  unsigned int minLoad = std::numeric_limits<unsigned int>::max();
  for (const auto &it : partitionMap) {
    if (it.second->getEdgeSet().size() < minLoad) {
      minLoad = it.second->getEdgeSet().size();
    }
  }
  return minLoad;
}

template <typename T>
unsigned int getMaxNodesLoad(const PartitionMap<T> &partitionMap) {
  unsigned int maxLoad = 0;
  for (const auto &it : partitionMap) {
    if (it.second->getNodeSet().size() > maxLoad) {
      maxLoad = it.second->getNodeSet().size();
    }
  }
  return maxLoad;
}

template <typename T>
unsigned int getMinNodesLoad(const PartitionMap<T> &partitionMap) {
  unsigned int minLoad = std::numeric_limits<unsigned int>::max();
  for (const auto &it : partitionMap) {
    if (it.second->getNodeSet().size() < minLoad) {
      minLoad = it.second->getNodeSet().size();
    }
  }
  return minLoad;
}

template <typename T>
unsigned int getNumberOfEdges(const PartitionMap<T> &partitionMap) {
  unsigned int numberOfEdges = 0;
  T_EdgeSet<T> edgeSet;

  for (const auto &it : partitionMap) {
    const T_EdgeSet<T> partitionEdgeSet = it.second->getEdgeSet();
    for (const auto &it2 : partitionEdgeSet) {
      edgeSet.insert(it2);
    }
  }

  return edgeSet.size();
}

template <typename T>
unsigned int getNumberOfNodes(const PartitionMap<T> &partitionMap) {
  unsigned int numberOfNodes = 0;
  std::unordered_set<shared<const Node<T>>, nodeHash<T>> nodeSet;

  for (const auto &it : partitionMap) {
    const std::unordered_set<shared<const Node<T>>, nodeHash<T>> partitionNodeSet = it.second->getNodeSet();
    for (const auto &it2 : partitionNodeSet) {
      // if (std::find_if(nodeSet.begin(), nodeSet.end(), [it2](const Node<T>
      // *node)
      //                  { return (*it2 == *node); }) == nodeSet.end())
      // {
      nodeSet.insert(it2);
      // }
    }
  }

  return nodeSet.size();
}

template <typename T>
unsigned int getNumberOfReplicatedEdges(const PartitionMap<T> &partitionMap) {
  unsigned int numberOfEdges = 0;
  for (const auto &it : partitionMap) {
    numberOfEdges += it.second->getEdgeSet().size();
  }
  return numberOfEdges;
}

template <typename T>
unsigned int getNumberOfReplicatedNodes(const PartitionMap<T> &partitionMap) {
  unsigned int numberOfNodes = 0;
  for (const auto &it : partitionMap) {
    numberOfNodes += it.second->getNodeSet().size();
  }
  return numberOfNodes;
}

template <typename T>
std::ostream &operator<<(std::ostream &os, const Partition<T> &partition) {
  os << "Partition " << partition.getPartitionId() << ":\n";
  auto edgeList = partition.getEdgeSet();
  for (const auto &it : edgeList) {
    if (!(*it)->isDirected().has_value() && !(*it)->isWeighted().has_value()) {
      // Edge Case
      os << **it << "\n";
    } else if (((*it)->isDirected().has_value() &&
                (*it)->isDirected().value()) &&
               ((*it)->isWeighted().has_value() &&
                (*it)->isWeighted().value())) {
      os << std::static_pointer_cast<const DirectedWeightedEdge<T>>(*it) << "\n";
    } else if ((it->isDirected().has_value() && it->isDirected().value()) &&
               !(it->isWeighted().has_value() && it->isWeighted().value())) {
      os << std::static_pointer_cast<const DirectedEdge<T>>(*it) << "\n";
    } else if (!(it->isDirected().has_value() && it->isDirected().value()) &&
               (it->isWeighted().has_value() && it->isWeighted().value())) {
      os << std::static_pointer_cast<const UndirectedWeightedEdge<T>>(*it) << "\n";
    } else if (!(it->isDirected().has_value() && it->isDirected().value()) &&
               !(it->isWeighted().has_value() && it->isWeighted().value())) {
      os << std::static_pointer_cast<const UndirectedEdge<T>>(*it) << "\n";
    } else {
      // Should never happens
      os << "Wrong Edge Class"
         << "\n";
    }
  }
  return os;
}
}  // namespace Partitioning

}  // namespace CXXGraph

#endif  // __CXXGRAPH_PARTITION_H__
