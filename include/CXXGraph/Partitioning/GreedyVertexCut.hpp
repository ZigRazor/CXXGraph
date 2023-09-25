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

#ifndef __CXXGRAPH_PARTITIONING_GREEDYVERTEXCUT_H__
#define __CXXGRAPH_PARTITIONING_GREEDYVERTEXCUT_H__

#include <memory>
#pragma once

#include <chrono>
#include <random>

#include "Edge/Edge.hpp"
#include "PartitionStrategy.hpp"
#include "Partitioning/Utility/Globals.hpp"

namespace CXXGraph {
// Smart pointers alias
template <typename T>
using unique = std::unique_ptr<T>;
template <typename T>
using shared= std::shared_ptr<T>;

using std::make_unique;
using std::make_shared;

namespace Partitioning {
/**
 * @brief A Greedy Vertex Cut Partioning Algorithm
 * @details This algorithm is a greedy algorithm that partitions the graph into
 * n sets of vertices.
 */
template <typename T>
class GreedyVertexCut : public PartitionStrategy<T> {
 private:
  Globals GLOBALS;

 public:
  explicit GreedyVertexCut(const Globals &G);
  ~GreedyVertexCut();

  void performStep(shared<const Edge<T>> e, shared<PartitionState<T>> Sstate) override;
};

template <typename T>
GreedyVertexCut<T>::GreedyVertexCut(const Globals &G) : GLOBALS(G) {}

template <typename T>
GreedyVertexCut<T>::~GreedyVertexCut() {}

template <typename T>
void GreedyVertexCut<T>::performStep(shared<const Edge<T>> e,
                                     shared<PartitionState<T>> state) {
  int P = GLOBALS.numberOfPartition;
  auto nodePair = e->getNodePair();
  CXXGraph::id_t u = nodePair.first->getId();
  CXXGraph::id_t v = nodePair.second->getId();

  std::shared_ptr<Record<T>> u_record = state->getRecord(u);
  std::shared_ptr<Record<T>> v_record = state->getRecord(v);

  //*** ASK FOR LOCK
  bool locks_taken = false;
  while (!locks_taken) {
    int usleep_time = 2;
    while (!u_record->getLock()) {
      std::this_thread::sleep_for(std::chrono::microseconds(usleep_time));
      usleep_time = (int)pow(usleep_time, 2);
    }
    usleep_time = 2;
    if (u != v) {
      while (!v_record->getLock()) {
        std::this_thread::sleep_for(std::chrono::microseconds(usleep_time));
        usleep_time = (int)pow(usleep_time, 2);

        if (usleep_time > GLOBALS.SLEEP_LIMIT) {
          u_record->releaseLock();
          performStep(e, state);
          return;
        }  // TO AVOID DEADLOCK
      }
    }
    locks_taken = true;
  }
  //*** LOCK TAKEN
  int machine_id = -1;

  //*** COMPUTE CANDIDATES PARITIONS
  std::vector<int> candidates;

  if (u_record->getPartitions().empty() && v_record->getPartitions().empty()) {
    // Find the partition with min load
    int min_load = INT_MAX;
    int machine_id = 0;
    for (int i = 0; i < P; i++) {
      if (state->getMachineLoad(i) < min_load) {
        min_load = state->getMachineLoad(i);
        machine_id = i;
      }
    }
    candidates.push_back(machine_id);
  } else if (!u_record->getPartitions().empty() &&
             v_record->getPartitions().empty()) {
    // Find the partition with min load in u
    int min_load = INT_MAX;
    int machine_id = 0;
    for (auto &partition : u_record->getPartitions()) {
      if (state->getMachineLoad(partition) < min_load) {
        min_load = state->getMachineLoad(partition);
        machine_id = partition;
      }
    }
    candidates.push_back(machine_id);
  } else if (u_record->getPartitions().empty() &&
             !v_record->getPartitions().empty()) {
    // Find the partition with min load in v
    int min_load = INT_MAX;
    int machine_id = 0;
    for (auto &partition : v_record->getPartitions()) {
      if (state->getMachineLoad(partition) < min_load) {
        min_load = state->getMachineLoad(partition);
        machine_id = partition;
      }
    }
    candidates.push_back(machine_id);
  } else if (!u_record->getPartitions().empty() &&
             !v_record->getPartitions().empty()) {
    // check if have intersection
    std::set<int> intersection;
    std::set_intersection(
        u_record->getPartitions().begin(), u_record->getPartitions().end(),
        v_record->getPartitions().begin(), v_record->getPartitions().end(),
        std::inserter(intersection, intersection.begin()));
    if (!intersection.empty()) {
      // Find the partition with min load in the intersection of u and v
      int min_load = INT_MAX;
      int machine_id = 0;
      for (auto &partition : intersection) {
        if (state->getMachineLoad(partition) < min_load) {
          min_load = state->getMachineLoad(partition);
          machine_id = partition;
        }
      }
      candidates.push_back(machine_id);
    } else {
      // Find the partition with min load in the union of u and v
      std::set<int> part_union;
      std::set_union(
          u_record->getPartitions().begin(), u_record->getPartitions().end(),
          v_record->getPartitions().begin(), v_record->getPartitions().end(),
          std::inserter(part_union, part_union.begin()));
      int min_load = INT_MAX;
      int machine_id = 0;
      for (auto &partition : part_union) {
        if (state->getMachineLoad(partition) < min_load) {
          min_load = state->getMachineLoad(partition);
          machine_id = partition;
        }
      }
      candidates.push_back(machine_id);
    }
  }

  //*** CHECK TO AVOID ERRORS
  if (candidates.empty()) {
    std::cout
        << "ERROR: GreedyObjectiveFunction.performStep -> candidates.isEmpty()"
        << std::endl;
    exit(-1);
  }

  //*** PICK A RANDOM ELEMENT FROM CANDIDATES
  // Use TLS statics to pay init cost once per-thread
  thread_local static std::default_random_engine rand;
  thread_local static std::uniform_int_distribution distribution(0, RAND_MAX);

  unsigned int seed = (unsigned int)time(NULL);
  rand.seed(seed);

  int choice = distribution(rand) % candidates.size();
  machine_id = candidates.at(choice);
  try {
    shared<CoordinatedPartitionState<T>> cord_state =
        std::static_pointer_cast<CoordinatedPartitionState<T>>(state);
    // NEW UPDATE RECORDS RULE TO UPFDATE THE SIZE OF THE PARTITIONS EXPRESSED
    // AS THE NUMBER OF VERTICES THEY CONTAINS
    if (!u_record->hasReplicaInPartition(machine_id)) {
      u_record->addPartition(machine_id);
      cord_state->incrementMachineLoadVertices(machine_id);
    }
    if (!v_record->hasReplicaInPartition(machine_id)) {
      v_record->addPartition(machine_id);
      cord_state->incrementMachineLoadVertices(machine_id);
    }
  } catch (const std::bad_cast &) {
    // use employee's member functions
    // 1-UPDATE RECORDS
    if (!u_record->hasReplicaInPartition(machine_id)) {
      u_record->addPartition(machine_id);
    }
    if (!v_record->hasReplicaInPartition(machine_id)) {
      v_record->addPartition(machine_id);
    }
  }

  // 2-UPDATE EDGES
  state->incrementMachineLoad(machine_id, e);

  // 3-UPDATE DEGREES
  u_record->incrementDegree();
  v_record->incrementDegree();

  //*** RELEASE LOCK
  u_record->releaseLock();
  v_record->releaseLock();
  return;
}
}  // namespace Partitioning
}  // namespace CXXGraph

#endif  // __CXXGRAPH_PARTITIONING_GREEDYVERTEXCUT_H__
