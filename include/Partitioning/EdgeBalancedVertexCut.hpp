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

#ifndef __CXXGRAPH_PARTITIONING_EDGEBALANCEDVERTEXCUT_H__
#define __CXXGRAPH_PARTITIONING_EDGEBALANCEDVERTEXCUT_H__

#include <memory>
#pragma once

#include <chrono>

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
 * @brief A Vertex Cut Partioning Algorithm that assign an edge in the partition
 * with less load
 * @details This algorithm is a greedy algorithm that assign an edge in the
 * partition with less load
 */
template <typename T>
class EdgeBalancedVertexCut : public PartitionStrategy<T> {
 private:
  Globals GLOBALS;

 public:
  explicit EdgeBalancedVertexCut(const Globals &G);
  ~EdgeBalancedVertexCut();

  void performStep(shared<const Edge<T>> e, shared<PartitionState<T>> Sstate) override;
};
template <typename T>
EdgeBalancedVertexCut<T>::EdgeBalancedVertexCut(const Globals &G) : GLOBALS(G) {
  // this->GLOBALS = G;
}
template <typename T>
EdgeBalancedVertexCut<T>::~EdgeBalancedVertexCut() {}
template <typename T>
void EdgeBalancedVertexCut<T>::performStep(shared<const Edge<T>> e,
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
    srand((unsigned)time(NULL));
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

  //*** Check which partition has the less load
  int MIN_LOAD = state->getMachineLoad(0);
  int machine_id = 0;
  double MAX_SCORE = 0.0;

  for (int m = 0; m < P; m++) {
    int load = state->getMachineLoad(m);
    if (load <= MIN_LOAD) {
      MIN_LOAD = load;
      machine_id = m;
    }
  }
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

#endif  // __CXXGRAPH_PARTITIONING_EDGEBALANCEDVERTEXCUT_H__
