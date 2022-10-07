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
            const T_EdgeSet<T>* dataset = nullptr;
            PartitionStrategy<T>* algorithm = nullptr;
            Globals GLOBALS;

            CoordinatedPartitionState<T> startCoordinated();
            

        public:
            Partitioner(const T_EdgeSet<T> *dataset, Globals &G);
            Partitioner(const Partitioner& other);
            ~Partitioner();

            CoordinatedPartitionState<T> performCoordinatedPartition();
        };
        template <typename T>
        Partitioner<T>::Partitioner(const T_EdgeSet<T> *dataset, Globals &G) : GLOBALS(G)
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
            std::shared_ptr<Runnable> myRunnable[processors];
            std::vector<const Edge<T>*> list_vector[processors];
            int n = dataset->size();
            int subSize = n / processors + 1;
            for (int t = 0; t < processors; ++t)
            {
                int iStart = t * subSize;
                int iEnd = std::min((t + 1) * subSize, n);
                if (iEnd >= iStart)
                {
                    list_vector[t] = std::vector<const Edge<T>*>(std::next(dataset->begin(), iStart), std::next(dataset->begin(), iEnd));
                    myRunnable[t] = std::make_shared<PartitionerThread<T>>(list_vector[t], &state, algorithm);
                    myThreads[t] = std::thread(&Runnable::run, myRunnable[t].get());
                }
            }
            for (int t = 0; t < processors; ++t)
            {
                if (myThreads[t].joinable()){
                    myThreads[t].join();
                }
                //if(myRunnable[t] != nullptr){
                //    delete myRunnable[t];
                //}
            }
            /*
            for (int t = 0; t < processors; ++t){
                if (runnableList[t] != nullptr){
                    delete runnableList[t];
                } 
            }
            */
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