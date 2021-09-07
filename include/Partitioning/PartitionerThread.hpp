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

#ifndef __CXXGRAPH_PARTITIONING_PARTITIONERTHREAD_H__
#define __CXXGRAPH_PARTITIONING_PARTITIONERTHREAD_H__

#pragma once

#include <vector>
#include <list>
#include "Edge/Edge.hpp"
#include "PartitionState.hpp"
#include "PartitionStrategy.hpp"

namespace CXXGRAPH
{
    namespace PARTITIONING
    {
        template <typename T>
		class PartitionerThread
		{
		private:
			std::vector<Edge<T>> list;
			PartitionState<T> *state;
			PartitionStrategy<T> algorithm;

		public:
			PartitionerThread(std::vector<Edge<T>> &list, PartitionState<T> *state, PartitionStrategy<T> &algorithm, std::list<int> *ids);
			~PartitionerThread();

			void run();

			std::list<int> *id_partitions;
		};
		template <typename T>
		PartitionerThread<T>::PartitionerThread(std::vector<Edge<T>> &list, PartitionState<T> *state, PartitionStrategy<T> &algorithm, std::list<int> *ids)
		{
			this->list = list;
			this->state = state;
			this->algorithm = algorithm;
			this->id_partitions = ids;
		}
		template <typename T>
		PartitionerThread<T>::~PartitionerThread()
		{
		}
		template <typename T>
		void PartitionerThread<T>::run()
		{
			auto edge_it = list.begin();
			for (edge_it; edge_it != list.end(); ++edge_it)
			{
				algorithm.performStep(*edge_it, *state);
			}
		}
    }
}

#endif // __CXXGRAPH_PARTITIONING_PARTITIONERTHREAD_H__