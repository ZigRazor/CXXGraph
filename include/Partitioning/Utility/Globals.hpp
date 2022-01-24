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
			Globals(int numberOfPartiton, PartitionAlgorithm algorithm = PartitionAlgorithm::HDRF_ALG, double param1 = 1, double param2 = 1, double param3 = 1, unsigned int threads = std::thread::hardware_concurrency());
			~Globals();

			void print();

			//CONSTANT
			const int SLEEP_LIMIT = 16; // In microseconds
			const int PLACES = 4;

			int numberOfPartition = 0; //number of partitions
			//OPTIONAL
			PartitionAlgorithm partitionStategy;			
			unsigned int threads = 0;
			double param1 = 0.0;
			double param2 = 0.0;
			double param3 = 0.0;
			unsigned long long edgeCardinality = 0;
			unsigned long long vertexCardinality = 0;
			unsigned long long edgeAnalyzed = 0;
		};

		inline Globals::Globals(int numberOfPartiton, PartitionAlgorithm algorithm,double param1, double param2, double param3, unsigned int threads)
		{
			this->numberOfPartition = numberOfPartiton;
			this->partitionStategy = algorithm;			
			this->threads = threads;
			this->param1 = param1;
			this->param2 = param2;
			this->param3 = param3;
		}

		inline Globals::~Globals()
		{
		}

    }
}

#endif // __CXXGRAPH_PARTITIONING_GLOBALS_H__