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

#ifndef __CXXGRAPH_PARTITIONING_PARTITIONERTHREAD_H__
#define __CXXGRAPH_PARTITIONING_PARTITIONERTHREAD_H__

#pragma once

#include <list>
#include <vector>

#include "Edge/Edge.hpp"
#include "PartitionState.hpp"
#include "PartitionStrategy.hpp"
#include "Utility/Runnable.hpp"

namespace CXXGraph {
namespace Partitioning {
template <typename T>
class PartitionerThread : public Runnable {
 private:
  std::vector<shared<const Edge<T>>> list = {};
  shared<PartitionState<T>> state = nullptr;
  shared<PartitionStrategy<T>> algorithm = nullptr;

 public:
  PartitionerThread(std::vector<shared<const Edge<T>>> &list,
                    shared<PartitionState<T>> state,
					shared<PartitionStrategy<T>> algorithm);
  ~PartitionerThread();

  void run() override;

  std::list<int> id_partitions;
};
template <typename T>
PartitionerThread<T>::PartitionerThread(std::vector<shared<const Edge<T>>> &list,
                                        shared<PartitionState<T>> state,
                                        shared<PartitionStrategy<T>> algorithm) {
  this->list = list;
  this->state = state;
  this->algorithm = algorithm;
}
template <typename T>
PartitionerThread<T>::~PartitionerThread() {}
template <typename T>
void PartitionerThread<T>::run() {
  for (const auto &edge_it : list) {
    algorithm->performStep(edge_it, state);
  }
}
}  // namespace Partitioning
}  // namespace CXXGraph

#endif  // __CXXGRAPH_PARTITIONING_PARTITIONERTHREAD_H__
