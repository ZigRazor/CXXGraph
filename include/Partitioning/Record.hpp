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

#ifndef __CXXGRAPH_PARTITIONING_RECORD_H__
#define __CXXGRAPH_PARTITIONING_RECORD_H__

#pragma once

#include <set>

namespace CXXGRAPH {
    namespace PARTITIONING {
        template <typename T>
		class Record
		{
		public:
			virtual std::set<int> &getPartitions() = 0;
			virtual void addPartition(int m) = 0;
			virtual bool hasReplicaInPartition(int m) = 0;
			virtual bool getLock() = 0;
			virtual bool releaseLock() = 0;
			virtual int getReplicas() const = 0;
			virtual int getDegree() = 0;
			virtual void incrementDegree() = 0;
		};
    }
}

#endif // __CXXGRAPH_PARTITIONING_RECORD_H__