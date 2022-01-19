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

#ifndef __CXXGRAPH_PARTITIONING_COORDINATEDRECORD_H__
#define __CXXGRAPH_PARTITIONING_COORDINATEDRECORD_H__

#pragma once

#include <set>
#include "Utility/Typedef.hpp"

namespace CXXGRAPH
{
    namespace PARTITIONING
    {

        template <typename T>
        class CoordinatedRecord : public Record<T>
        {
        private:
            std::set<int> partitions = {};
            std::mutex *lock = nullptr;
            int degree = 0;

        public:
            CoordinatedRecord();
            ~CoordinatedRecord();

            std::set<int> &getPartitions();
            void addPartition(int m);
            bool hasReplicaInPartition(int m);
            bool getLock();
            bool releaseLock();
            int getReplicas() const;
            int getDegree();
            void incrementDegree();

            void addAll(std::set<int> &set);
            std::set<int> intersection(CoordinatedRecord &x, CoordinatedRecord &y);
        };
        template <typename T>
        CoordinatedRecord<T>::CoordinatedRecord() : partitions()
        {
            lock = new std::mutex();
            degree = 0;
        }
        template <typename T>
        CoordinatedRecord<T>::~CoordinatedRecord()
        {
            //std::cout << "CoordinatedRecord<T>::~CoordinatedRecord()" << std::endl;
            //TODOOOOOOOO
            //if(lock){
            //    delete lock;
            //}
        }
        template <typename T>
        std::set<int> &CoordinatedRecord<T>::getPartitions()
        {
            return partitions;
        }
        template <typename T>
        void CoordinatedRecord<T>::addPartition(int m)
        {
            if (m == -1)
            {
                std::cout << "ERROR! record.addPartition(-1)" << std::endl;
                exit(-1);
            }
            partitions.insert(m);
        }
        template <typename T>
        bool CoordinatedRecord<T>::hasReplicaInPartition(int m)
        {
            return partitions.find(m) != partitions.end();
        }
        template <typename T>
        bool CoordinatedRecord<T>::getLock()
        {   
            return lock->try_lock();
        }
        template <typename T>
        bool CoordinatedRecord<T>::releaseLock()
        {
            lock->unlock();
            return true;
        }
        template <typename T>
        int CoordinatedRecord<T>::getReplicas() const
        {
            return partitions.size();
        }
        template <typename T>
        int CoordinatedRecord<T>::getDegree()
        {
            return degree;
        }
        template <typename T>
        void CoordinatedRecord<T>::incrementDegree()
        {
            degree++;
        }
        template <typename T>
        void CoordinatedRecord<T>::addAll(std::set<int> &set)
        {
            partitions.insert(set.begin(), set.end());
        }
        template <typename T>
        std::set<int> CoordinatedRecord<T>::intersection(CoordinatedRecord &x, CoordinatedRecord &y)
        {
            std::set<int> result;
            set_intersection(x.partitions.begin(), x.partitions.end(), y.partitions.begin(), y.partitions.end(),
                             std::inserter(result, result.begin()));
            return result;
        }
    }
}

#endif // __CXXGRAPH_PARTITIONING_COORDINATEDRECORD_H__