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

#ifndef __CXXGRAPH_PARTITIONING_RECORD_H__
#define __CXXGRAPH_PARTITIONING_RECORD_H__

#pragma once

#include <set>

namespace CXXGraph {
namespace Partitioning {
template <typename T>
class Record {
 public:
  virtual const std::set<int> &getPartitions() const = 0;
  virtual void addPartition(const int m) = 0;
  virtual bool hasReplicaInPartition(const int m) const = 0;
  virtual bool getLock() = 0;
  virtual bool releaseLock() = 0;
  virtual int getReplicas() const = 0;
  virtual int getDegree() const = 0;
  virtual void incrementDegree() = 0;
};
}  // namespace Partitioning
}  // namespace CXXGraph

#endif  // __CXXGRAPH_PARTITIONING_RECORD_H__