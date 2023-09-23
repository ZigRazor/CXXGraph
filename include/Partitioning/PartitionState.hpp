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

#include <memory>
#include "Record.hpp"

namespace CXXGraph {
// Smart pointers alias
template <typename T>
using unique = std::unique_ptr<T>;
template <typename T>
using shared = std::shared_ptr<T>;

using std::make_unique;
using std::make_shared;

namespace Partitioning {
template <typename T>
class PartitionState {
 public:
  virtual shared<Record<T>> getRecord(CXXGraph::id_t x) = 0;
  virtual int getMachineLoad(const int m) const = 0;
  virtual int getMachineWeight(const int m) const = 0;
  virtual int getMachineLoadVertices(const int m) const = 0;
  virtual void incrementMachineLoad(const int m, shared<const Edge<T>> e) = 0;
  virtual void incrementMachineWeight(const int m, shared<const Edge<T>> e) = 0;
  virtual int getMinLoad() const = 0;
  virtual int getMaxLoad() const = 0;
  virtual int getMachineWithMinWeight() const = 0;
  virtual int getMachineWithMinWeight(
      const std::set<int>& partitions) const = 0;
  virtual std::vector<int> getMachines_load() const = 0;
  virtual size_t getTotalReplicas() const = 0;
  virtual size_t getNumVertices() const = 0;
  virtual std::set<CXXGraph::id_t> getVertexIds() const = 0;
};
}  // namespace Partitioning
}  // namespace CXXGraph

#endif  // __CXXGRAPH_PARTITIONING_PARTITIONSTATE_H__
