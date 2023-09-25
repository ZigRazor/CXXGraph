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

#ifndef __CXXGRAPH_PARTITIONING_WEIGHTBALANCEDLIBRA_H__
#define __CXXGRAPH_PARTITIONING_WEIGHTBALANCEDLIBRA_H__

#pragma once

#include <chrono>

#include "Edge/Edge.hpp"
#include "PartitionStrategy.hpp"
#include "Partitioning/Utility/Globals.hpp"

namespace CXXGraph {
namespace Partitioning {
/**
 * @brief A Vertex Cut Partioning Algorithm ( as described by this paper
 * https://arxiv.org/pdf/2010.04414.pdf )
 * @details This algorithm is a greedy algorithm that partitions the graph into
 * n sets of vertices ( as described by this paper
 * https://arxiv.org/pdf/2010.04414.pdf ).
 */
template <typename T>
class WeightBalancedLibra : public PartitionStrategy<T> {
 private:
  Globals GLOBALS;
  double weight_sum_bound;
  std::unordered_map<std::size_t, int> vertices_degrees;

 public:
  explicit WeightBalancedLibra(
      const Globals &G, double _weight_sum_bound,
      std::unordered_map<std::size_t, int> &&_vertices_degrees);
  ~WeightBalancedLibra();

  void performStep(shared<const Edge<T>> e, shared<PartitionState<T>> Sstate) override;
};
template <typename T>
WeightBalancedLibra<T>::WeightBalancedLibra(
    const Globals &G, double _weight_sum_bound,
    std::unordered_map<std::size_t, int> &&_vertices_degrees)
    : GLOBALS(G),
      weight_sum_bound(_weight_sum_bound),
      vertices_degrees(_vertices_degrees) {}
template <typename T>
WeightBalancedLibra<T>::~WeightBalancedLibra() {}
template <typename T>
void WeightBalancedLibra<T>::performStep(shared<const Edge<T>> e,
                                         shared<PartitionState<T>> state) {
  int P = GLOBALS.numberOfPartition;
  auto nodePair = e->getNodePair();
  size_t u = nodePair.first->getId();
  size_t v = nodePair.second->getId();
  std::shared_ptr<Record<T>> u_record = state->getRecord(u);
  std::shared_ptr<Record<T>> v_record = state->getRecord(v);

  //*** ASK FOR LOCK
  bool locks_taken = false;
  while (!locks_taken) {
    srand((unsigned)time(NULL));
    int usleep_time = 2;
    while (!u_record->getLock()) {
      std::this_thread::sleep_for(std::chrono::microseconds(usleep_time));
      usleep_time = (int)pow(usleep_time, 2);
    }
    usleep_time = 2;
    if (u != v) {
      while ((locks_taken = v_record->getLock()) == false) {
        std::this_thread::sleep_for(std::chrono::microseconds(usleep_time));
        usleep_time = (int)pow(usleep_time, 2);

        if (usleep_time > GLOBALS.SLEEP_LIMIT) {
          u_record->releaseLock();
          // performStep(e, state);
          break;
        }  // TO AVOID DEADLOCK
      }
    } else {
      locks_taken = true;
    }
  }
  //*** LOCK TAKEN
  int machine_id = -1;
  const std::set<int> &u_partition = u_record->getPartitions();
  const std::set<int> &v_partition = v_record->getPartitions();

  // Case 1: no edges of two nodes have been assigned
  if (u_partition.empty() && v_partition.empty()) {
    machine_id = state->getMachineWithMinWeight();
  }
  // Case 2: one or more edges of node v have been assigned but that of node u
  // haven't
  else if (u_partition.empty() && !v_partition.empty()) {
    machine_id = state->getMachineWithMinWeight(v_partition);
    if (state->getMachineWeight(machine_id) >= weight_sum_bound) {
      machine_id = state->getMachineWithMinWeight();
    }
  }
  // Case 3: one or more edges of node u have been assigned but that of node v
  // haven't
  else if (!u_partition.empty() && v_partition.empty()) {
    machine_id = state->getMachineWithMinWeight(u_partition);
    if (state->getMachineWeight(machine_id) >= weight_sum_bound) {
      machine_id = state->getMachineWithMinWeight();
    }
  }
  // Case 4: one or more edges of both nodes have been assigned
  else {
    std::shared_ptr<CoordinatedRecord<T>> u_coord_record =
        std::dynamic_pointer_cast<CoordinatedRecord<T>>(u_record);
    std::shared_ptr<CoordinatedRecord<T>> v_coord_record =
        std::dynamic_pointer_cast<CoordinatedRecord<T>>(v_record);
    const auto &uv_intersection =
        u_coord_record->partition_intersection(v_coord_record);

    // Case 4.1: no common partitions for both nodes
    if (uv_intersection.empty()) {
      size_t u_degree = vertices_degrees[u];
      size_t v_degree = vertices_degrees[v];

      // according to paper, s refers to node with lower degree, t = {u, v} -
      // {s}
      size_t s_node = (u_degree > v_degree) ? v : u;
      size_t t_node = (u_degree > v_degree) ? u : v;
      const std::set<int> &s_partition =
          (u_degree > v_degree) ? v_partition : u_partition;
      const std::set<int> &t_partition =
          (u_degree > v_degree) ? u_partition : v_partition;

      machine_id = state->getMachineWithMinWeight(s_partition);
      if (state->getMachineWeight(machine_id) >= weight_sum_bound) {
        machine_id = state->getMachineWithMinWeight(t_partition);
        if (state->getMachineWeight(machine_id) >= weight_sum_bound) {
          machine_id = state->getMachineWithMinWeight();
        }
      }
    }
    // Case 4.2: there are some common partitions for both nodes
    else {
      machine_id = state->getMachineWithMinWeight(uv_intersection);
      if (state->getMachineWeight(machine_id) >= weight_sum_bound) {
        const auto &uv_union = u_coord_record->partition_union(v_coord_record);
        machine_id = state->getMachineWithMinWeight(uv_union);
        if (machine_id >= weight_sum_bound) {
          machine_id = state->getMachineWithMinWeight();
        }
      }
    }
  }

  if (machine_id < 0 || machine_id >= P) {
    std::cout << "ERROR: wrong partition id" << std::endl;
    exit(-1);
  }

  // 1-UPDATE RECORDS
  if (!u_record->hasReplicaInPartition(machine_id)) {
    u_record->addPartition(machine_id);
  }
  if (!v_record->hasReplicaInPartition(machine_id)) {
    v_record->addPartition(machine_id);
  }

  // 2-UPDATE EDGES
  state->incrementMachineWeight(machine_id, e);

  //*** RELEASE LOCK
  u_record->releaseLock();
  v_record->releaseLock();
  return;
}
}  // namespace Partitioning
}  // namespace CXXGraph

#endif  // __CXXGRAPH_PARTITIONING_WEIGHTBALANCEDLIBRA_H__
