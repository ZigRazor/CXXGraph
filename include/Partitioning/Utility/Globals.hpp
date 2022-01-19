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

#ifndef __CXXGRAPH_PARTITIONING_GLOBALS_H__
#define __CXXGRAPH_PARTITIONING_GLOBALS_H__

#pragma once

#include <thread>
#include "Partitioning/PartitionAlgorithm.hpp"


namespace CXXGRAPH {
    namespace PARTITIONING {
        class Globals
		{
		private:
		public:
			Globals(int numberOfPartiton, PartitionAlgorithm algorithm = PartitionAlgorithm::HDRF_ALG, unsigned int threads = std::thread::hardware_concurrency(), double lambda = 1);
			~Globals();

			void print();

			//CONSTANT
			const int SLEEP_LIMIT = 16;
			const int PLACES = 4;

			int numberOfPartition = 0; //number of partitions
			//OPTIONAL
			PartitionAlgorithm partitionStategy;
			double lambda = 0.0;
			unsigned int threads = 0;
		};

		inline Globals::Globals(int numberOfPartiton, PartitionAlgorithm algorithm, unsigned int threads,double lambda)
		{
			this->numberOfPartition = numberOfPartiton;
			this->partitionStategy = algorithm;
			this->lambda = lambda;
			this->threads = threads;
		}

		inline Globals::~Globals()
		{
		}
    }
}

#endif // __CXXGRAPH_PARTITIONING_GLOBALS_H__