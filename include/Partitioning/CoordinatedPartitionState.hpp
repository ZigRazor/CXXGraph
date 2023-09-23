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

#ifndef __CXXGRAPH_PARTITIONING_COORDINATEDPARTITIONSTATE_H__
#define __CXXGRAPH_PARTITIONING_COORDINATEDPARTITIONSTATE_H__

#pragma once

#include <memory>
#include <mutex>
#include <set>
#include <vector>

#include "CoordinatedRecord.hpp"
#include "Edge/Edge.hpp"
#include "PartitionState.hpp"
#include "Partitioning/Utility/Globals.hpp"
#include "Record.hpp"

namespace CXXGraph {
// Smart pointers alias
template <typename T>
using unique = std::unique_ptr<T>;
template <typename T>
using shared= std::shared_ptr<T>;

using std::make_unique;
using std::make_shared;

namespace Partitioning {
template <typename T>
class CoordinatedPartitionState : public PartitionState<T> {
 private:
  std::map<CXXGraph::id_t, std::shared_ptr<CoordinatedRecord<T>>> record_map;
  std::vector<int> machines_load_edges;
  std::vector<double> machines_weight_edges;
  std::vector<int> machines_load_vertices;
  PartitionMap<T> partition_map;
  Globals GLOBALS;
  int MAX_LOAD;
  std::shared_ptr<std::mutex> machines_load_edges_mutex = nullptr;
  std::shared_ptr<std::mutex> machines_load_vertices_mutex = nullptr;
  std::shared_ptr<std::mutex> machines_weight_edges_mutex = nullptr;
  std::shared_ptr<std::mutex> record_map_mutex = nullptr;
  // DatWriter out; //to print the final partition of each edge
 public:
  CoordinatedPartitionState(const Globals &G);
  ~CoordinatedPartitionState();

  std::shared_ptr<Record<T>> getRecord(CXXGraph::id_t x) override;
  int getMachineLoad(const int m) const override;
  int getMachineWeight(const int m) const override;
  int getMachineLoadVertices(const int m) const override;
  void incrementMachineLoad(const int m, shared<const Edge<T>> e) override;
  void incrementMachineWeight(const int m, shared<const Edge<T>> e) override;
  int getMinLoad() const override;
  int getMaxLoad() const override;
  int getMachineWithMinWeight() const override;
  int getMachineWithMinWeight(const std::set<int> &partitions) const override;
  std::vector<int> getMachines_load() const override;
  size_t getTotalReplicas() const override;
  size_t getNumVertices() const override;
  std::set<CXXGraph::id_t> getVertexIds() const override;

  void incrementMachineLoadVertices(const int m);
  std::vector<int> getMachines_loadVertices() const;
  const PartitionMap<T> &getPartitionMap() const;
};

template <typename T>
CoordinatedPartitionState<T>::CoordinatedPartitionState(const Globals &G)
    : record_map(),
      GLOBALS(G),
      machines_load_edges_mutex(std::make_shared<std::mutex>()),
      machines_load_vertices_mutex(std::make_shared<std::mutex>()),
      machines_weight_edges_mutex(std::make_shared<std::mutex>()),
      record_map_mutex(std::make_shared<std::mutex>()) {
  machines_load_edges.reserve(GLOBALS.numberOfPartition);
  machines_load_vertices.reserve(GLOBALS.numberOfPartition);
  machines_weight_edges.reserve(GLOBALS.numberOfPartition);
  for (int i = 0; i < GLOBALS.numberOfPartition; ++i) {
    machines_load_edges.push_back(0);
    machines_load_vertices.push_back(0);
    machines_weight_edges.push_back(0);
    partition_map[i] = std::make_shared<Partitioning::Partition<T>>(i);
  }
  MAX_LOAD = 0;
}

template <typename T>
CoordinatedPartitionState<T>::~CoordinatedPartitionState() {}

template <typename T>
std::shared_ptr<Record<T>> CoordinatedPartitionState<T>::getRecord(
    CXXGraph::id_t x) {
  std::lock_guard<std::mutex> lock(*record_map_mutex);
  if (record_map.find(x) == record_map.end()) {
    record_map[x] = std::make_shared<CoordinatedRecord<T>>();
  }
  return record_map.at(x);
}

template <typename T>
int CoordinatedPartitionState<T>::getMachineLoad(const int m) const {
  std::lock_guard<std::mutex> lock(*machines_load_edges_mutex);
  return (int)machines_load_edges.at(m);
}

template <typename T>
int CoordinatedPartitionState<T>::getMachineWeight(const int m) const {
  std::lock_guard<std::mutex> lock(*machines_weight_edges_mutex);
  return (int)machines_weight_edges.at(m);
}

template <typename T>
int CoordinatedPartitionState<T>::getMachineLoadVertices(const int m) const {
  std::lock_guard<std::mutex> lock(*machines_load_vertices_mutex);
  return (int)machines_load_vertices.at(m);
}
template <typename T>
void CoordinatedPartitionState<T>::incrementMachineLoad(const int m,
                                                        shared<const Edge<T>> e) {
  std::lock_guard<std::mutex> lock(*machines_load_edges_mutex);
  machines_load_edges[m] = machines_load_edges[m] + 1;
  int new_value = machines_load_edges.at(m);
  if (new_value > MAX_LOAD) {
    MAX_LOAD = new_value;
  }
  partition_map[m]->addEdge(e);
}
template <typename T>
void CoordinatedPartitionState<T>::incrementMachineWeight(const int m,
                                                          shared<const Edge<T>> e) {
  std::lock_guard<std::mutex> lock(*machines_weight_edges_mutex);
  double edge_weight = CXXGraph::NEGLIGIBLE_WEIGHT;
  if (e->isWeighted().has_value() && e->isWeighted().value()) {
    edge_weight = (std::dynamic_pointer_cast<const Weighted>(e))->getWeight();
  }
  machines_weight_edges[m] = machines_weight_edges[m] + edge_weight;
  // double new_value = machines_weight_edges[m];
  // if (new_value > MAX_LOAD)
  //{
  //    MAX_LOAD = new_value;
  //}
  partition_map[m]->addEdge(e);
}
template <typename T>
int CoordinatedPartitionState<T>::getMinLoad() const {
  std::lock_guard<std::mutex> lock(*machines_load_edges_mutex);
  int MIN_LOAD = std::numeric_limits<int>::max();
  for (const auto &machines_load_edges_it : machines_load_edges) {
    int loadi = machines_load_edges_it;
    if (loadi < MIN_LOAD) {
      MIN_LOAD = loadi;
    }
  }
  return MIN_LOAD;
}
template <typename T>
int CoordinatedPartitionState<T>::getMaxLoad() const {
  return MAX_LOAD;
}
template <typename T>
int CoordinatedPartitionState<T>::getMachineWithMinWeight() const {
  std::lock_guard<std::mutex> lock(*machines_weight_edges_mutex);

  double MIN_LOAD = std::numeric_limits<double>::max();
  int machine_id = 0;
  for (int i = 0; i < machines_weight_edges.size(); ++i) {
    double loadi = machines_weight_edges[i];
    if (loadi < MIN_LOAD) {
      MIN_LOAD = loadi;
      machine_id = i;
    }
  }

  return machine_id;
}
template <typename T>
int CoordinatedPartitionState<T>::getMachineWithMinWeight(
    const std::set<int> &partitions) const {
  std::lock_guard<std::mutex> lock(*machines_weight_edges_mutex);

  double MIN_LOAD = std::numeric_limits<double>::max();
  int machine_id = 0;
  for (const auto &partition_id : partitions) {
    double loadi = machines_weight_edges.at(partition_id);
    if (loadi < MIN_LOAD) {
      MIN_LOAD = loadi;
      machine_id = partition_id;
    }
  }

  return machine_id;
}
template <typename T>
std::vector<int> CoordinatedPartitionState<T>::getMachines_load() const {
  std::lock_guard<std::mutex> lock(*machines_load_edges_mutex);
  std::vector<int> result;
  for (const auto &machines_load_edges_it : machines_load_edges) {
    result.push_back(machines_load_edges_it);
  }
  return result;
}
template <typename T>
size_t CoordinatedPartitionState<T>::getTotalReplicas() const {
  // TODO
  std::lock_guard<std::mutex> lock(*record_map_mutex);
  size_t result = 0;
  for (const auto &record_map_it : record_map) {
    size_t r = record_map_it.second->getReplicas();
    if (r > 0) {
      result += r;
    } else {
      result++;
    }
  }
  return result;
}
template <typename T>
size_t CoordinatedPartitionState<T>::getNumVertices() const {
  std::lock_guard<std::mutex> lock(*record_map_mutex);
  return (size_t)record_map.size();
}
template <typename T>
std::set<CXXGraph::id_t> CoordinatedPartitionState<T>::getVertexIds() const {
  std::lock_guard<std::mutex> lock(*record_map_mutex);
  // if (GLOBALS.OUTPUT_FILE_NAME!=null){ out.close(); }
  std::set<CXXGraph::id_t> result;
  for (const auto &record_map_it : record_map) {
    result.insert((CXXGraph::id_t)record_map_it.first);
  }
  return result;
}
template <typename T>
void CoordinatedPartitionState<T>::incrementMachineLoadVertices(const int m) {
  std::lock_guard<std::mutex> lock(*machines_load_vertices_mutex);
  machines_load_vertices[m] = machines_load_vertices[m] + 1;
}
template <typename T>
std::vector<int> CoordinatedPartitionState<T>::getMachines_loadVertices()
    const {
  std::lock_guard<std::mutex> lock(*machines_load_vertices_mutex);
  std::vector<int> result;
  for (const auto &machines_load_vertices_it : machines_load_vertices) {
    result.push_back(machines_load_vertices_it);
  }
  return result;
}

template <typename T>
const PartitionMap<T> &CoordinatedPartitionState<T>::getPartitionMap() const {
  return partition_map;
}
}  // namespace Partitioning
}  // namespace CXXGraph

#endif  // __CXXGRAPH_PARTITIONING_COORDINATEDPARTITIONSTATE_H__
