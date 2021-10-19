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

#ifndef __CXXGRAPH_PARTITION_H__
#define __CXXGRAPH_PARTITION_H__

#pragma once

#include <list>

#include "Utility/Typedef.hpp"
#include "PartitioningStats.hpp"

namespace CXXGRAPH
{
    template <typename T>
    class Graph;
    namespace PARTITIONING
    {
        template <typename T>
        std::ostream &operator<<(std::ostream &o, const Partition<T> &partition);

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

        template <typename T>
        PartitioningStats getPartitionStats(const PartitionMap<T> &partitionMap)
        {
            PartitioningStats result;
            result.numberOfPartitions = partitionMap.size();
            result.numberOfNodes = getNumberOfNodes(partitionMap);
            result.numberOfEdges = getNumberOfEdges(partitionMap);
            result.replicatedNodesCount = getNumberOfReplicatedNodes(partitionMap);
            result.replicatedEdgesCount = getNumberOfReplicatedEdges(partitionMap);
            result.maxEdgesLoad = getMaxEdgesLoad(partitionMap);
            result.minEdgesLoad = getMinEdgesLoad(partitionMap);
            result.maxNodesLoad = getMaxNodesLoad(partitionMap);
            result.minNodesLoad = getMinNodesLoad(partitionMap);
            result.edgesReplicationFactor = (double)result.replicatedEdgesCount / result.numberOfEdges;
            result.nodesReplicationFactor = (double)result.replicatedNodesCount / result.numberOfNodes;
            result.balanceEdgesFactor = (double)(result.maxEdgesLoad - result.minEdgesLoad) / (result.maxEdgesLoad);
            result.balanceNodesFactor = (double)(result.maxNodesLoad - result.minNodesLoad) / (result.maxNodesLoad);
            return result;
        }

        template <typename T>
        unsigned int getMaxEdgesLoad(const PartitionMap<T> &partitionMap)
        {
            unsigned int maxLoad = 0;
            for (auto it = partitionMap.begin(); it != partitionMap.end(); ++it)
            {
                if (it->second->getEdgeSet().size() > maxLoad)
                {
                    maxLoad = it->second->getEdgeSet().size();
                }
            }
            return maxLoad;
        }

        template <typename T>
        unsigned int getMinEdgesLoad(const PartitionMap<T> &partitionMap)
        {
            unsigned int minLoad = std::numeric_limits<unsigned int>::max();
            for (auto it = partitionMap.begin(); it != partitionMap.end(); ++it)
            {
                if (it->second->getEdgeSet().size() < minLoad)
                {
                    minLoad = it->second->getEdgeSet().size();
                }
            }
            return minLoad;
        }

        template <typename T>
        unsigned int getMaxNodesLoad(const PartitionMap<T> &partitionMap)
        {
            unsigned int maxLoad = 0;
            for (auto it = partitionMap.begin(); it != partitionMap.end(); ++it)
            {
                if (it->second->getNodeSet().size() > maxLoad)
                {
                    maxLoad = it->second->getNodeSet().size();
                }
            }
            return maxLoad;
        }

        template <typename T>
        unsigned int getMinNodesLoad(const PartitionMap<T> &partitionMap)
        {
            unsigned int minLoad = std::numeric_limits<unsigned int>::max();
            for (auto it = partitionMap.begin(); it != partitionMap.end(); ++it)
            {
                if (it->second->getNodeSet().size() < minLoad)
                {
                    minLoad = it->second->getNodeSet().size();
                }
            }
            return minLoad;
        }

        template <typename T>
        unsigned int getNumberOfEdges(const PartitionMap<T> &partitionMap)
        {
            unsigned int numberOfEdges = 0;
            std::list<const Edge<T> *> edgeSet;

            for (auto it = partitionMap.begin(); it != partitionMap.end(); ++it)
            {
                const std::list<const Edge<T> *> partitionEdgeSet = it->second->getEdgeSet();
                for (auto it2 = partitionEdgeSet.begin(); it2 != partitionEdgeSet.end(); ++it2)
                {
                    if (std::find_if(edgeSet.begin(), edgeSet.end(), [it2](const Edge<T> *edge)
                                     { return (*(*it2) == *edge); }) == edgeSet.end())
                    {
                        edgeSet.push_back(*it2);
                    }
                }
            }

            return edgeSet.size();
        }

        template <typename T>
        unsigned int getNumberOfNodes(const PartitionMap<T> &partitionMap)
        {
            unsigned int numberOfNodes = 0;
            std::list<const Node<T> *> nodeSet;

            for (auto it = partitionMap.begin(); it != partitionMap.end(); ++it)
            {
                const std::list<const Node<T> *> partitionNodeSet = it->second->getNodeSet();
                for (auto it2 = partitionNodeSet.begin(); it2 != partitionNodeSet.end(); ++it2)
                {
                    if (std::find_if(nodeSet.begin(), nodeSet.end(), [it2](const Node<T> *node)
                                     { return (*(*it2) == *node); }) == nodeSet.end())
                    {
                        nodeSet.push_back(*it2);
                    }
                }
            }

            return nodeSet.size();
        }

        template <typename T>
        unsigned int getNumberOfReplicatedEdges(const PartitionMap<T> &partitionMap)
        {

            unsigned int numberOfEdges = 0;
            for (auto it = partitionMap.begin(); it != partitionMap.end(); ++it)
            {
                numberOfEdges += it->second->getEdgeSet().size();
            }
            return numberOfEdges;
        }

        template <typename T>
        unsigned int getNumberOfReplicatedNodes(const PartitionMap<T> &partitionMap)
        {
            unsigned int numberOfNodes = 0;
            for (auto it = partitionMap.begin(); it != partitionMap.end(); ++it)
            {
                numberOfNodes += it->second->getNodeSet().size();
            }
            return numberOfNodes;
        }

        template <typename T>
        std::ostream &operator<<(std::ostream &os, const Partition<T> &partition)
        {
            os << "Partition " << partition.getPartitionId() << ":\n";
            auto edgeList = partition.getEdgeSet();
            auto it = edgeList.begin();
            for (it; it != edgeList.end(); ++it)
            {
                if (((*it)->isDirected().has_value()&& (*it)->isDirected().value()) && ((*it)->isWeighted().has_value() && (*it)->isWeighted().value()))
                {
                    os << dynamic_cast<const DirectedWeightedEdge<T> &>(**it) << "\n";
                }
                else if (((*it)->isDirected().has_value() && (*it)->isDirected().value())  && !((*it)->isWeighted().has_value() && (*it)->isWeighted().value()))
                {
                    os << dynamic_cast<const DirectedEdge<T> &>(**it) << "\n";
                }
                else if (!((*it)->isDirected().has_value() && (*it)->isDirected().value()) && ((*it)->isWeighted().has_value() && (*it)->isWeighted().value()))
                {
                    os << dynamic_cast<const UndirectedWeightedEdge<T> &>(**it) << "\n";
                }
                else if (!((*it)->isDirected().has_value() && (*it)->isDirected().value()) && !((*it)->isWeighted().has_value() && (*it)->isWeighted().value()))
                {
                    os << dynamic_cast<const UndirectedEdge<T> &>(**it) << "\n";
                }
                else
                {
                    os << **it << "\n";
                }
            }
            return os;
        }
    }

}

#endif // __CXXGRAPH_PARTITION_H__