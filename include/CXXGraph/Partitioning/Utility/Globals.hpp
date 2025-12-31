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
/***	 License: MPL v2.0 ***/
/***********************************************************/

#ifndef __CXXGRAPH_PARTITIONING_GLOBALS_H__
#define __CXXGRAPH_PARTITIONING_GLOBALS_H__

#pragma once

#include <iostream>
#include <string>
#include <thread>

#include "CXXGraph/Partitioning/PartitionAlgorithm.hpp"

namespace CXXGraph {
namespace Partitioning {
class Globals {
 private:
 public:
  explicit Globals(
      const int numberOfPartiton,
      const PartitionAlgorithm algorithm = PartitionAlgorithm::HDRF_ALG,
      const double param1 = 1, const double param2 = 1, const double param3 = 1,
      const unsigned int threads = std::thread::hardware_concurrency());
  ~Globals();

  const std::string print() const;

  // CONSTANT
  int SLEEP_LIMIT = 16;  // In microseconds
  int PLACES = 4;

  int numberOfPartition = 0;  // number of partitions
  // OPTIONAL
  PartitionAlgorithm partitionStategy;
  unsigned int threads = 0;
  double param1 = 0.0;
  double param2 = 0.0;
  double param3 = 0.0;
  unsigned long long edgeCardinality = 0;
  unsigned long long vertexCardinality = 0;
  unsigned long long edgeAnalyzed = 0;
};

inline Globals::Globals(const int numberOfPartiton,
                        const PartitionAlgorithm algorithm, const double param1,
                        const double param2, const double param3,
                        const unsigned int threads) {
  this->numberOfPartition = numberOfPartiton;
  this->partitionStategy = algorithm;
  this->threads = threads;
  this->param1 = param1;
  this->param2 = param2;
  this->param3 = param3;
  if (this->numberOfPartition <= 0) {
    std::cout << "ERROR: numberOfPartition " << numberOfPartition << std::endl;
    exit(-1);
  }
}

inline Globals::~Globals() = default;

inline const std::string Globals::print() const {
  std::string prt_str;
  return prt_str;
}

}  // namespace Partitioning
}  // namespace CXXGraph

#endif  // __CXXGRAPH_PARTITIONING_GLOBALS_H__
