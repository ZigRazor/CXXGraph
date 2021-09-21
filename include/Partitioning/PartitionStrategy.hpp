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

#ifndef __CXXGRAPH_PARTITIONING_PARTITIONSTRATEGY_H__
#define __CXXGRAPH_PARTITIONING_PARTITIONSTRATEGY_H__

#pragma once

#include "Edge/Edge.hpp"
#include "PartitionState.hpp"

namespace CXXGRAPH
{
    namespace PARTITIONING
    {
        template <typename T>
		class PartitionStrategy
		{
		public:
			virtual void performStep(const Edge<T> &t, PartitionState<T> &Sstate) = 0;
		};
    }
}

#endif // __CXXGRAPH_PARTITIONING_PARTITIONSTRATEGY_H__