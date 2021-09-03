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

#ifndef __PARTITIONINGSTATS_H__
#define __PARTITIONINGSTATS_H__

#include <iostream>
#include "Utility/Typedef.hpp"

namespace CXXGRAPH
{
    namespace PARTITIONING
    {
        class PartitioningStats
        {
        public:
            unsigned int numberOfPartitions;   // The number of Partitions
            unsigned int numberOfNodes;        // The number of Nodes
            unsigned int replicatedNodesCount; // The number of Nodes that are replicated
            unsigned int numberOfEdges;        // The number of edges
            unsigned int replicatedEdgesCount; // The number of edges that are replicated
            unsigned int maxEdgesLoad;         // Maximum edges load of the partitions
            unsigned int minEdgesLoad;         // Minimun edges load of the partitions
            unsigned int maxNodesLoad;         // Maximum nodes load of the partitions
            unsigned int minNodesLoad;         // Minimun nodes load of the partitions
            double balanceEdgesFactor;         // The balance edges factor of the partitions (maxEdgesLoad - minEdgesLoad) / (maxEdgesLoad), 0 is the optimal partitioning
            double balanceNodesFactor;         // The balance edges factor of the partitions (maxNodesLoad - minNodesLoad) / (maxNodesLoad), 0 is the optimal partitioning
            double nodesReplicationFactor;     // The replication factor of the Nodes (replicatedNodesCount / numberOfNodes), 1 is the optimal partitioning
            double edgesReplicationFactor;     // The replication factor of the edges (replicatedEdgesCount / numberOfEdges), 1 is the optimal partitioning

            friend std::ostream &operator<<(std::ostream &os, const PartitioningStats &partitionStats)
            {
                os << "Partitioning Stats:\n";
                os << "\tNumber of Partitions: " << partitionStats.numberOfPartitions << "\n";
                os << "\tNumber of Nodes: " << partitionStats.numberOfNodes << "\n";
                os << "\tNumber of Edges: " << partitionStats.numberOfEdges << "\n";
                os << "\tNumber of Nodes Replica: " << partitionStats.replicatedNodesCount << "\n";
                os << "\tNumber of Edges Replica: " << partitionStats.replicatedEdgesCount << "\n";
                os << "\tNodes Replication Factor: " << partitionStats.nodesReplicationFactor << "\n";
                os << "\tEdges Replication Factor: " << partitionStats.edgesReplicationFactor << "\n";
                os << "\tMax Edges Load: " << partitionStats.maxEdgesLoad << "\n";
                os << "\tMin Edges Load: " << partitionStats.minEdgesLoad << "\n";
                os << "\tBalance Edges Factor: " << partitionStats.balanceEdgesFactor << "\n";
                os << "\tMax Nodes Load: " << partitionStats.maxNodesLoad << "\n";
                os << "\tMin Nodes Load: " << partitionStats.minNodesLoad << "\n";
                os << "\tBalance Nodes Factor: " << partitionStats.balanceNodesFactor << "\n";
                return os;
            }
        };

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
    }
}

#endif // __PARTITIONINGSTATS_H__