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

#ifndef __CXXGRAPH_PARTITIONING_PARTITIONSTATE_H__
#define __CXXGRAPH_PARTITIONING_PARTITIONSTATE_H__

#pragma once

#include "Record.hpp"

namespace CXXGRAPH
{
    namespace PARTITIONING
    {
        template <typename T>
        class PartitionState
        {
        public:
            virtual Record<T> *getRecord(int x) = 0;
            virtual int getMachineLoad(int m) = 0;
            virtual int getMachineLoadVertices(int m) = 0;
            virtual void incrementMachineLoad(int m,const Edge<T>* e) = 0;
            virtual int getMinLoad() = 0;
            virtual int getMaxLoad() = 0;
            virtual std::vector<int> getMachines_load() = 0;
            virtual int getTotalReplicas() = 0;
            virtual int getNumVertices() = 0;
            virtual std::set<int> getVertexIds() = 0;
        };
    }
}

#endif // __CXXGRAPH_PARTITIONING_PARTITIONSTATE_H__