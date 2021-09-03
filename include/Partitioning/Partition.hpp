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

#ifndef __PARTITION_H__
#define __PARTITION_H__

#pragma once

#include "Graph/Graph.hpp"
#include "PartitioningStats.hpp"

namespace CXXGRAPH
{
    namespace PARTITIONING
    {
        template <typename T>
        class Partition : public Graph<T>
        {
        public:
            Partition();
            Partition(unsigned int partitionId);
            Partition(const std::list<const Edge<T> *> &edgeSet);
            Partition(unsigned int partitionId, const std::list<const Edge<T> *> &edgeSet);
            ~Partition() = default;
            /**
		    * @brief Get the Partition ID
		    *
		    * @return The ID of the partition
		    */
            unsigned int getPartitionId() const;
            /**
 		    * @brief Set the Partition ID
 		    *
		    * @param partitionId the ID to set
 		    */
            void setPartitionId(unsigned int partitionId);

        private:
            unsigned int partitionId;
        };

        /**
 	    * @brief Calculate and return the statistic of the Partitioned Graph
 	    *
	    * @param partitionMap the Partition Map
	    *
	    * @return The Statistic of the Partioned Graph
 	    */
        template <typename T>
        static PartitioningStats getPartitionStats(const PartitionMap<T> &partitionMap);

        /**
 	    * @brief Calculate the Maximum Load in a single partition (in terms of edges) for the Partioned Graph
 	    *
	    * @param partitionMap the Partition Map
	    *
	    * @return The value of the Maximum Load
 	    */
        template <typename T>
        static unsigned int getMaxEdgesLoad(const PartitionMap<T> &partitionMap);

        /**
 	    * @brief Calculate the Minimum Load in a single partition (in terms of edges) for the Partioned Graph
 	    *
	    * @param partitionMap the Partition Map
	    *
	    * @return The value of the Minimum Load
 	    */
        template <typename T>
        static unsigned int getMinEdgesLoad(const PartitionMap<T> &partitionMap);

        /**
 	    * @brief Calculate the Maximum Load in a single partition (in terms of nodes) for the Partioned Graph
 	    *
	    * @param partitionMap the Partition Map
	    *
	    * @return The value of the Maximum Load
 	    */
        template <typename T>
        static unsigned int getMaxNodesLoad(const PartitionMap<T> &partitionMap);

        /**
 	    * @brief Calculate the Minimum Load in a single partition (in terms of nodes) for the Partioned Graph
 	    *
	    * @param partitionMap the Partition Map
	    *
	    * @return The value of the Minimum Load
 	    */
        template <typename T>
        static unsigned int getMinNodesLoad(const PartitionMap<T> &partitionMap);

        /**
 	    * @brief Calculate the Number of Unique Edges in the Partitioned Graph ( this value is equal to the number of edges in the Original Graph)
 	    *
	    * @param partitionMap the Partition Map
	    *
	    * @return The number of Edges
 	    */
        template <typename T>
        static unsigned int getNumberOfEdges(const PartitionMap<T> &partitionMap);

        /**
 	    * @brief Calculate the Number of Unique Nodes in the Partitioned Graph ( this value is equal to the number of nodes in the Original Graph)
 	    *
	    * @param partitionMap the Partition Map
	    *
	    * @return The number of Nodes
 	    */
        template <typename T>
        static unsigned int getNumberOfNodes(const PartitionMap<T> &partitionMap);

        /**
 	    * @brief Calculate the Total Number of Edges in the Partitioned Graph
 	    *
	    * @param partitionMap the Partition Map
	    *
	    * @return The number of Edges
 	    */
        template <typename T>
        static unsigned int getNumberOfReplicatedEdges(const PartitionMap<T> &partitionMap);

        /**
 	    * @brief Calculate the Total Number of Nodes in the Partitioned Graph
 	    *
	    * @param partitionMap the Partition Map
	    *
	    * @return The number of Nodes
 	    */
        template <typename T>
        static unsigned int getNumberOfReplicatedNodes(const PartitionMap<T> &partitionMap);

        template <typename T>
        Partition<T>::Partition() : Graph<T>()
        {
            partitionId = 0;
        }

        template <typename T>
        Partition<T>::Partition(unsigned int partitionId) : Graph<T>()
        {
            this->partitionId = partitionId;
        }

        template <typename T>
        Partition<T>::Partition(const std::list<const Edge<T> *> &edgeSet) : Graph<T>(edgeSet)
        {
            partitionId = 0;
        }

        template <typename T>
        Partition<T>::Partition(unsigned int partitionId, const std::list<const Edge<T> *> &edgeSet) : Graph<T>(edgeSet)
        {
            this->partitionId = partitionId;
        }

        template <typename T>
        unsigned int Partition<T>::getPartitionId() const
        {
            return partitionId;
        }

        template <typename T>
        void Partition<T>::setPartitionId(unsigned int partitionId)
        {
            this->partitionId = partitionId;
        }
    }
}

#endif // __PARTITION_H__