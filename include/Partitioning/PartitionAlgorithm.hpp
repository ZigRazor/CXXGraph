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
/***     Author: ZigRazor			     			     ***/
/***	 E-Mail: zigrazor@gmail.com 				     ***/
/***********************************************************/
/***	 Collaboration: ----------- 				     ***/
/***********************************************************/
/***	 License: AGPL v3.0							     ***/
/***********************************************************/

#ifndef __CXXGRAPH_PARTITIONING_PARTITIONALGORITHM_H__
#define __CXXGRAPH_PARTITIONING_PARTITIONALGORITHM_H__

#pragma once

namespace CXXGRAPH
{
    namespace PARTITIONING
    {
        /// Specify the Partition Algorithm
        enum E_PartitionAlgorithm
        {
            GREEDY_VC, ///< A Greedy Vertex-Cut Algorithm
            HDRF,      ///< High-Degree (are) Replicated First (HDRF) Algorithm (Stream-Based Vertex-Cut Partitioning)
            ALG_2
        };
        typedef E_PartitionAlgorithm PartitionAlgorithm;
    }
}

#endif // __CXXGRAPH_PARTITIONING_PARTITIONALGORITHM_H__