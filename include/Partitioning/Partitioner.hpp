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

#ifndef __CXXGRAPH_PARTITIONING_PARTITIONER_H__
#define __CXXGRAPH_PARTITIONING_PARTITIONER_H__

#pragma once
#include <vector>
#include "PartitionStrategy.hpp"
#include "Partitioning/Utility/Globals.hpp"
#include "Edge/Edge.hpp"
#include "CoordinatedPartitionState.hpp"
#include "Utility/Runnable.hpp"
#include "PartitionerThread.hpp"
#include "PartitionAlgorithm.hpp"
#include "HDRF.hpp"
#include "EdgeBalancedVertexCut.hpp"
#include "GreedyVertexCut.hpp"
#include "EBV.hpp"

namespace CXXGRAPH
{
    namespace PARTITIONING
    {
        template <typename T>
        class Partitioner
        {
        private:
            std::list<const Edge<T> *> dataset = {};
            PartitionStrategy<T>* algorithm = nullptr;
            Globals GLOBALS;

            CoordinatedPartitionState<T> startCoordinated();
            

        public:
            Partitioner(const std::list<const Edge<T> *> &dataset, Globals &G);
            Partitioner(const Partitioner& other);
            ~Partitioner();

            CoordinatedPartitionState<T> performCoordinatedPartition();
        };
        template <typename T>
        Partitioner<T>::Partitioner(const std::list<const Edge<T> *> &dataset, Globals &G) : GLOBALS(G)
        {
            //this->GLOBALS = G;
            this->dataset = dataset;
            if (GLOBALS.partitionStategy == PartitionAlgorithm::HDRF_ALG)
            {
                algorithm = new HDRF<T>(GLOBALS);
            } else if (GLOBALS.partitionStategy == PartitionAlgorithm::EDGEBALANCED_VC_ALG)
            {
                algorithm = new EdgeBalancedVertexCut<T>(GLOBALS);
            } else if (GLOBALS.partitionStategy == PartitionAlgorithm::GREEDY_VC_ALG)
            {
                algorithm = new GreedyVertexCut<T>(GLOBALS);
            } else if (GLOBALS.partitionStategy == PartitionAlgorithm::EBV_ALG)
            {
                algorithm = new EBV<T>(GLOBALS);
            }

        }

        template <typename T>
        Partitioner<T>::Partitioner(const Partitioner& other){
            this->dataset = other.dataset;
            this->GLOBALS = other.GLOBALS;
            if (GLOBALS.partitionStategy == PartitionAlgorithm::HDRF_ALG)
            {
                algorithm = new HDRF<T>(GLOBALS);
            } else if (GLOBALS.partitionStategy == PartitionAlgorithm::EDGEBALANCED_VC_ALG)
            {
                algorithm = new EdgeBalancedVertexCut<T>(GLOBALS);
            } else if (GLOBALS.partitionStategy == PartitionAlgorithm::GREEDY_VC_ALG)
            {
                algorithm = new GreedyVertexCut<T>(GLOBALS);
            } else if (GLOBALS.partitionStategy == PartitionAlgorithm::EBV_ALG)
            {
                algorithm = new EBV<T>(GLOBALS);
            }
        }

        template <typename T>
        CoordinatedPartitionState<T> Partitioner<T>::startCoordinated()
        {
            CoordinatedPartitionState<T> state(GLOBALS);
            int processors = GLOBALS.threads;

            std::thread myThreads[processors];

            int n = dataset.size();
            int subSize = n / processors + 1;
            for (int t = 0; t < processors; ++t)
            {
                int iStart = t * subSize;
                int iEnd = std::min((t + 1) * subSize, n);
                if (iEnd >= iStart)
                {
                    std::vector<const Edge<T>*> list(std::next(dataset.begin(), iStart), std::next(dataset.begin(), iEnd));
                    Runnable *x = new PartitionerThread<T>(list, &state, algorithm, new std::list<int>());
                    myThreads[t] = std::thread(&Runnable::run, x);
                }
            }
            for (int t = 0; t < processors; ++t)
            {
                myThreads[t].join();
            }
            return state;
        }
        template <typename T>
        Partitioner<T>::~Partitioner()
        {
            if(algorithm != nullptr)
            {
                delete algorithm;
            }
        }
        template <typename T>
        CoordinatedPartitionState<T> Partitioner<T>::performCoordinatedPartition()
        {
            return startCoordinated();
        }

    }
}

#endif // __CXXGRAPH_PARTITIONING_PARTITIONER_H__