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

#ifndef __CXXGRAPH_PARTITIONING_PARTITIONSTATE_H__
#define __CXXGRAPH_PARTITIONING_PARTITIONSTATE_H__

#pragma once

#include "Record.hpp"

namespace CXXGRAPH {
namespace PARTITIONING {
template <typename T>
class PartitionState {
 public:
  virtual std::shared_ptr<Record<T>> getRecord(const int x) = 0;
  virtual int getMachineLoad(const int m) const = 0;
  virtual int getMachineWeight(const int m) const = 0;
  virtual int getMachineLoadVertices(const int m) const = 0;
  virtual void incrementMachineLoad(const int m, const Edge<T>* e) = 0;
  virtual void incrementMachineWeight(const int m, const Edge<T>* e) = 0;
  virtual int getMinLoad() const = 0;
  virtual int getMaxLoad() const = 0;
  virtual int getMachineWithMinWeight() const = 0;
  virtual int getMachineWithMinWeight(
      const std::set<int>& partitions) const = 0;
  virtual std::vector<int> getMachines_load() const = 0;
  virtual int getTotalReplicas() const = 0;
  virtual int getNumVertices() const = 0;
  virtual std::set<int> getVertexIds() const = 0;
};
}  // namespace PARTITIONING
}  // namespace CXXGRAPH

#endif  // __CXXGRAPH_PARTITIONING_PARTITIONSTATE_H__