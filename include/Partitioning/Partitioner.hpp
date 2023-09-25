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

#ifndef __CXXGRAPH_PARTITIONING_PARTITIONER_H__
#define __CXXGRAPH_PARTITIONING_PARTITIONER_H__

#include <memory>
#pragma once
#include <vector>

#include "CoordinatedPartitionState.hpp"
#include "EBV.hpp"
#include "Edge/Edge.hpp"
#include "EdgeBalancedVertexCut.hpp"
#include "GreedyVertexCut.hpp"
#include "HDRF.hpp"
#include "PartitionAlgorithm.hpp"
#include "PartitionStrategy.hpp"
#include "PartitionerThread.hpp"
#include "Partitioning/Utility/Globals.hpp"
#include "Utility/Runnable.hpp"
#include "WeightBalancedLibra.hpp"

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
class Partitioner {
 private:
  shared<const T_EdgeSet<T>> dataset = nullptr;
  shared<PartitionStrategy<T>> algorithm = nullptr;
  Globals GLOBALS;

  CoordinatedPartitionState<T> startCoordinated();

 public:
  Partitioner(shared<const T_EdgeSet<T>> dataset, Globals &G);
  Partitioner(const Partitioner &other);

  CoordinatedPartitionState<T> performCoordinatedPartition();
};
template <typename T>
Partitioner<T>::Partitioner(shared<const T_EdgeSet<T>> dataset, Globals &G)
    : GLOBALS(G) {
  // this->GLOBALS = G;
  this->dataset = dataset;
  if (GLOBALS.partitionStategy == PartitionAlgorithm::HDRF_ALG) {
    algorithm = make_shared<HDRF<T>>(GLOBALS);
  } else if (GLOBALS.partitionStategy ==
             PartitionAlgorithm::EDGEBALANCED_VC_ALG) {
    algorithm = make_shared<EdgeBalancedVertexCut<T>>(GLOBALS);
  } else if (GLOBALS.partitionStategy == PartitionAlgorithm::GREEDY_VC_ALG) {
    algorithm = make_shared<GreedyVertexCut<T>>(GLOBALS);
  } else if (GLOBALS.partitionStategy == PartitionAlgorithm::EBV_ALG) {
    algorithm = make_shared<EBV<T>>(GLOBALS);
  } else if (GLOBALS.partitionStategy == PartitionAlgorithm::WB_LIBRA) {
    // precompute weight sum
    double weight_sum = 0.0;
    for (const auto &edge_it : *(this->dataset)) {
      weight_sum +=
          (edge_it->isWeighted().has_value() && edge_it->isWeighted().value())
              ? std::dynamic_pointer_cast<const Weighted>(edge_it)->getWeight()
              : CXXGraph::NEGLIGIBLE_WEIGHT;
    }
    double lambda = std::max(1.0, GLOBALS.param1);
    double P = static_cast<double>(GLOBALS.numberOfPartition);
    // avoid divide by zero when some parameters are invalid
    double weight_sum_bound =
        (GLOBALS.numberOfPartition == 0) ? 0.0 : lambda * weight_sum / P;

    // precompute degrees of vertices
    std::unordered_map<std::size_t, int> vertices_degrees;
    for (const auto &edge_it : *(this->dataset)) {
      auto nodePair = edge_it->getNodePair();
      std::size_t u = nodePair.first->getId();
      std::size_t v = nodePair.second->getId();
      vertices_degrees[u]++;
      vertices_degrees[v]++;
    }

    algorithm = make_shared<WeightBalancedLibra<T>>(GLOBALS, weight_sum_bound,
                                           std::move(vertices_degrees));
  }
}

template <typename T>
Partitioner<T>::Partitioner(const Partitioner &other) {
  this->dataset = other.dataset;
  this->GLOBALS = other.GLOBALS;
  if (GLOBALS.partitionStategy == PartitionAlgorithm::HDRF_ALG) {
    algorithm = make_shared<HDRF<T>>(GLOBALS);
  } else if (GLOBALS.partitionStategy ==
             PartitionAlgorithm::EDGEBALANCED_VC_ALG) {
    algorithm = make_shared<EdgeBalancedVertexCut<T>>(GLOBALS);
  } else if (GLOBALS.partitionStategy == PartitionAlgorithm::GREEDY_VC_ALG) {
    algorithm = make_shared<GreedyVertexCut<T>>(GLOBALS);
  } else if (GLOBALS.partitionStategy == PartitionAlgorithm::EBV_ALG) {
    algorithm = make_shared<EBV<T>>(GLOBALS);
  } else if (GLOBALS.partitionStategy == PartitionAlgorithm::WB_LIBRA) {
    // precompute weight sum
    double weight_sum = 0.0;
    for (const auto &edge_it : *(this->dataset)) {
      weight_sum +=
          (edge_it->isWeighted().has_value() && edge_it->isWeighted().value())
              ? std::dynamic_pointer_cast<const Weighted>(edge_it)->getWeight()
              : CXXGraph::NEGLIGIBLE_WEIGHT;
    }
    double lambda = GLOBALS.param1;
    double P = static_cast<double>(GLOBALS.numberOfPartition);
    // avoid divide by zero when some parameters are invalid
    double weight_sum_bound =
        (GLOBALS.numberOfPartition == 0) ? 0.0 : lambda * weight_sum / P;

    // precompute degrees of vertices
    std::unordered_map<std::size_t, int> vertices_degrees;
    for (const auto &edge_it : *(this->dataset)) {
      auto nodePair = edge_it->getNodePair();
      std::size_t u = nodePair.first->getId();
      std::size_t v = nodePair.second->getId();
      vertices_degrees[u]++;
      vertices_degrees[v]++;
    }

    algorithm = make_shared<WeightBalancedLibra<T>>(GLOBALS, weight_sum_bound,
                                           std::move(vertices_degrees));
  }
}

template <typename T>
CoordinatedPartitionState<T> Partitioner<T>::startCoordinated() {
  CoordinatedPartitionState<T> state(GLOBALS);
  int processors = GLOBALS.threads;

  std::vector<std::thread> myThreads(processors);
  std::vector<std::shared_ptr<Runnable>> myRunnable(processors);
  std::vector<std::vector<shared<const Edge<T>>>> list_vector(processors);
  size_t n = dataset->size();
  int subSize = (int)n / processors + 1;
  for (int t = 0; t < processors; ++t) {
    int iStart = t * subSize;
    int iEnd = std::min((t + 1) * subSize, (int)n);
    if (iEnd >= iStart) {
      list_vector[t] =
          std::vector<shared<const Edge<T>>>(std::next(dataset->begin(), iStart),
                                       std::next(dataset->begin(), iEnd));
      myRunnable[t].reset(
          new PartitionerThread<T>(list_vector[t],
								   make_shared<CoordinatedPartitionState<T>>(state),
								   algorithm));
      myThreads[t] = std::thread(&Runnable::run, myRunnable[t].get());
    }
  }
  for (int t = 0; t < processors; ++t) {
    if (myThreads[t].joinable()) {
      myThreads[t].join();
    }
    // if(myRunnable[t] != nullptr){
    //    delete myRunnable[t];
    //}
  }
  /*
  for (int t = 0; t < processors; ++t){
      if (runnableList[t] != nullptr){
          delete runnableList[t];
      }
  }
  */
  return state;
}

template <typename T>
CoordinatedPartitionState<T> Partitioner<T>::performCoordinatedPartition() {
  return startCoordinated();
}

}  // namespace Partitioning
}  // namespace CXXGraph

#endif  // __CXXGRAPH_PARTITIONING_PARTITIONER_H__
