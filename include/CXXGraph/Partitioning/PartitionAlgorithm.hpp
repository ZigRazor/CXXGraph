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

#ifndef __CXXGRAPH_PARTITIONING_PARTITIONALGORITHM_H__
#define __CXXGRAPH_PARTITIONING_PARTITIONALGORITHM_H__

#pragma once

namespace CXXGraph {
namespace Partitioning {
/// Specify the Partition Algorithm
enum E_PartitionAlgorithm {
  EDGEBALANCED_VC_ALG,  ///< A Edge Balanced Vertex-Cut Algorithm
  GREEDY_VC_ALG,        ///< A Greedy Algorithm
  HDRF_ALG,             ///< High-Degree (are) Replicated First (HDRF) Algorithm
                        ///< (Stream-Based Vertex-Cut Partitioning)
  EBV_ALG,              ///< Edge-Balanced Vertex-Cut Offline Algorithm (EBV)
  ALG_2,
  WB_LIBRA,  ///< Weighted Balanced Libra
};
typedef E_PartitionAlgorithm PartitionAlgorithm;
}  // namespace Partitioning
}  // namespace CXXGraph

#endif  // __CXXGRAPH_PARTITIONING_PARTITIONALGORITHM_H__