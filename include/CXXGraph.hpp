#ifndef __CXXGRAPH_H__
#define __CXXGRAPH_H__

// the configured options and settings for CXXGraph
#define CXXGraph_VERSION_MAJOR 1
#define CXXGraph_VERSION_MINOR 0
#define CXXGraph_VERSION_PATCH 0

#include "Edge/Edge.hpp"
#include "Edge/DirectedEdge.hpp"
#include "Edge/DirectedWeightedEdge.hpp"
#include "Edge/UndirectedEdge.hpp"
#include "Edge/UndirectedWeightedEdge.hpp"
#include "Edge/Weighted.hpp"
#include "Graph/Graph.hpp"
#include "Node/Node.hpp"
#include "Partitioning/Partition.hpp"
#include "Partitioning/CoordinatedPartitionState.hpp"
#include "Partitioning/CoordinatedRecord.hpp"
#include "Partitioning/HDRF.hpp"
#include "Partitioning/EBV.hpp"
#include "Partitioning/EdgeBalancedVertexCut.hpp"
#include "Partitioning/GreedyVertexCut.hpp"
#include "Partitioning/PartitionAlgorithm.hpp"
#include "Partitioning/Partitioner.hpp"
#include "Partitioning/PartitionerThread.hpp"
#include "Partitioning/PartitioningStats.hpp"
#include "Partitioning/PartitionState.hpp"
#include "Partitioning/PartitionStrategy.hpp"
#include "Partitioning/Record.hpp"

#endif // __CXXGRAPH_H__
