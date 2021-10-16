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

#ifndef __GRAPH_H__
#define __GRAPH_H__

#pragma once

#include <utility>
#include <set>
#include <map>
#include <optional>
#include <iostream>
#include <limits>
#include <list>
#include <queue>
#include <string>
#include <cstring>
#include <functional>
#include <fstream>
#include <limits.h>
#include <mutex>
#include <set>
#include <atomic>
#include <thread>
#include <cmath>
#include "zlib.h"

#include "Edge/Weighted.hpp"
#include "Node/Node.hpp"
#include "Edge/Edge.hpp"
#include "Edge/DirectedEdge.hpp"
#include "Edge/UndirectedEdge.hpp"
#include "Edge/DirectedWeightedEdge.hpp"
#include "Edge/UndirectedWeightedEdge.hpp"
#include "Utility/ThreadSafe.hpp"
#include "Utility/Writer.hpp"
#include "Utility/Reader.hpp"
#include "Utility/ConstString.hpp"
#include "Utility/ConstValue.hpp"
#include "Utility/Typedef.hpp"
#include "Partitioning/Partition.hpp"
#include "Partitioning/PartitionAlgorithm.hpp"
#include "Partitioning/Partitioner.hpp"
#include "Partitioning/Utility/Globals.hpp"

namespace CXXGRAPH
{
	namespace PARTITIONING{
		template<typename T>
		class Partition;
	}

	template <typename T>
	std::ostream &operator<<(std::ostream &o, const Graph<T> &graph);
	template <typename T>
	std::ostream &operator<<(std::ostream &o, const AdjacencyMatrix<T> &adj);

	/// Class that implement the Graph. ( This class is not Thread Safe )
	template <typename T>
	class Graph
	{
	private:
		std::list<const Edge<T> *> edgeSet;
		void addElementToAdjMatrix(AdjacencyMatrix<T> &adjMatrix, const Node<T> *nodeFrom, const Node<T> *nodeTo, const Edge<T> *edge) const;
		int writeToStandardFile_csv(const std::string &workingDir, const std::string &OFileName, bool compress, bool writeNodeFeat, bool writeEdgeWeight) const;
		int readFromStandardFile_csv(const std::string &workingDir, const std::string &OFileName, bool compress, bool readNodeFeat, bool readEdgeWeight);
		int writeToStandardFile_tsv(const std::string &workingDir, const std::string &OFileName, bool compress, bool writeNodeFeat, bool writeEdgeWeight) const;
		int readFromStandardFile_tsv(const std::string &workingDir, const std::string &OFileName, bool compress, bool readNodeFeat, bool readEdgeWeight);
		void recreateGraphFromReadFiles(std::map<unsigned long, std::pair<unsigned long, unsigned long>> &edgeMap, std::map<unsigned long, bool> &edgeDirectedMap, std::map<unsigned long, T> &nodeFeatMap, std::map<unsigned long, double> &edgeWeightMap);
		int compressFile(const std::string &inputFile, const std::string &outputFile) const;
		int decompressFile(const std::string &inputFile, const std::string &outputFile) const;

	public:
		Graph() = default;
		Graph(const std::list<const Edge<T> *> &edgeSet);
		~Graph() = default;
		/**
 		* \brief
 		* Function that return the Edge set of the Graph
		* Note: No Thread Safe
		*
 		* @returns a list of Edges of the graph
 		*
 		*/
		virtual const std::list<const Edge<T> *> &getEdgeSet() const;
		/**
 		* \brief
 		* Function set the Edge Set of the Graph
		* Note: No Thread Safe
 		*
 		* @param edgeSet The Edge Set
 		*
 		*/
		virtual void setEdgeSet(std::list<const Edge<T> *> &edgeSet);
		/**
 		* \brief
 		* Function add an Edge to the Graph Edge Set
		* Note: No Thread Safe
 		*
 		* @param edge The Edge to insert
 		*
 		*/
		virtual void addEdge(const Edge<T> *edge);
		/**
 		* \brief
 		* Function remove an Edge from the Graph Edge Set
		* Note: No Thread Safe
 		*
 		* @param edgeId The Edge Id to remove
 		*
 		*/
		virtual void removeEdge(unsigned long edgeId);
		/**
 		* \brief
 		* Function that return the Node Set of the Graph
		* Note: No Thread Safe
 		*
 		* @returns a list of Nodes of the graph
 		*
 		*/
		virtual const std::list<const Node<T> *> getNodeSet() const;
		/**
 		* \brief
 		* Function that return an Edge with specific ID if Exist in the Graph
		* Note: No Thread Safe
 		*
		* @param edgeId The Edge Id to return
 		* @returns the Edge if exist
 		*
 		*/
		virtual const std::optional<const Edge<T> *> getEdge(unsigned long edgeId) const;
		/**
		* @brief This function generate a list of adjacency matrix with every element of the matrix
		* contain the node where is directed the link and the Edge corrispondent to the link
		* Note: No Thread Safe
		*/
		virtual const AdjacencyMatrix<T> getAdjMatrix() const;
		/**
		* @brief This function finds the subset of given a nodeId
		* @param subset query subset, we want to find target in this subset
		* @param elem elem that we wish to find in the subset
 		*
 		* @return parent node of elem 
		* Note: No Thread Safe
		*/
		virtual const unsigned long setFind(Subset subsets [], const unsigned long elem) const;
		/**
		* @brief This function modifies the original subset array
		* such that it the union of two sets a and b
		* @param subset query subset, we want to find target in this subset
		* @param a parent id of set1
		* @param b parent id of set2
 		*
		* Note: No Thread Safe
		*/
		virtual void setUnion(Subset subsets [], const unsigned long set1, const unsigned long elem2) const;		
		/**
 		* @brief Function runs the dijkstra algorithm for some source node and
 		* target node in the graph and returns the shortest distance of target
 		* from the source.
		* Note: No Thread Safe
 		*
		* @param source source vertex
 		* @param target target vertex
 		*
 		* @return shortest distance if target is reachable from source else ERROR in
 		* case if target is not reachable from source or there is error in the computation.
 		*/
		virtual const DijkstraResult dijkstra(const Node<T> &source, const Node<T> &target) const;
		/**
 		* @brief Function runs the bellman-ford algorithm for some source node and
 		* target node in the graph and returns the shortest distance of target
 		* from the source. It can also detect if a negative cycle exists in the graph.
		* Note: No Thread Safe
 		*
		* @param source source vertex
 		* @param target target vertex
 		*
 		* @return shortest distance if target is reachable from source else ERROR in
 		* case if target is not reachable from source. If there is no error then also 
		* returns if the graph contains a negative cycle.
 		*/
		virtual const BellmanFordResult bellmanford(const Node<T> &source, const Node<T> &target) const;
		/**
 		* @brief Function runs the floyd-warshall algorithm and returns the shortest distance of
 		* all pair of nodes. It can also detect if a negative cycle exists in the graph.
		* Note: No Thread Safe
 		* @return a map whose keys are node ids and values are the shortest distance. If there is no error then also 
		* returns if the graph contains a negative cycle.
 		*/
		virtual const FWResult floydWarshall() const;
		/**
 		* @brief Function runs the prim algorithm and returns the minimum spanning tree
 		* if the graph is undirected.
		* Note: No Thread Safe
 		* @return a vector containing id of nodes in minimum spanning tree.
 		*/
		virtual const PrimResult prim() const;
		/**
 		* \brief
 		* Function performs the breadth first search algorithm over the graph
		* Note: No Thread Safe
 		*
 		* @param start Node from where traversing starts
 		* @returns a vector of Node indicating which Node were visited during the
 		* search.
 		*
 		*/
		virtual const std::vector<Node<T>> breadth_first_search(const Node<T> &start) const;
		/**
 		* \brief
 		* Function performs the depth first search algorithm over the graph
		* Note: No Thread Safe
 		*
 		* @param start Node from where traversing starts
 		* @returns a vector of Node indicating which Node were visited during the
 		* search.
 		*
 		*/
		virtual const std::vector<Node<T>> depth_first_search(const Node<T> &start) const;

		/**
		* \brief
     	* This function uses DFS to check for cycle in the graph.
     	* Pay Attention, this function work only with directed Graph
		* Note: No Thread Safe
     	*
     	* @return true if a cycle is detected, else false. ( false is returned also if the graph in indirected)
     	*/
		virtual bool isCyclicDirectedGraphDFS() const;

		/**
		* \brief
     	* This function uses BFS to check for cycle in the graph.
     	* Pay Attention, this function work only with directed Graph
		* Note: No Thread Safe
     	*
     	* @return true if a cycle is detected, else false. ( false is returned also if the graph in indirected)
     	*/
		virtual bool isCyclicDirectedGraphBFS() const;

		/**
     	* \brief
     	* This function checks if a graph is directed
		* Note: No Thread Safe
     	*
     	* @return true if the graph is directed, else false.
     	*/
		virtual bool isDirectedGraph() const;

		/**
     	* \brief
     	* This function checks if a graph is undirected
		* Note: No Thread Safe
     	*
     	* @return true if the graph is undirected, else false.
     	*/
		virtual bool isUndirectedGraph() const;
		
		/**
     	* \brief
     	* This function performs Graph Slicing based on connectivity
		* 
		* Mathematical definition of the problem:
		*
		* Let G be the set of nodes in a graph and n be a given node in that set.
		* Let C be the non-strict subset of G containing both n and all nodes reachable
		* from n, and let C' be its complement. There's a third set M, which is the
		* non-strict subset of C containing all nodes that are reachable from any node in C'.
		* The problem consists of finding all nodes that belong to C but not to M.
		 
		* Note: No Thread Safe
		* @param start Node from where traversing starts
     	* @return a vector of nodes that belong to C but not to M.
     	*/
		virtual const std::vector<Node<T>> graph_slicing(const Node<T> &start) const;

		/**
     	* \brief
     	* This function write the graph in an output file
		* Note: No Thread Safe
     	*
		* @param format The Output format of the file
		* @param workingDir The path to the directory in which will be placed the output file
		* @param OFileName The Output File Name ( )
		* @param compress Indicates if the output will be compressed
		* @param writeNodeFeat Indicates if export also Node Features
		* @param writeEdgeWeight Indicates if export also Edge Weights
     	* @return 0 if all OK, else return a negative value
     	*/

		/**
 		* @brief Function runs the Dial algorithm  (Optimized Dijkstra for small range weights) for some source node and
 		* target node in the graph and returns the shortest distance of target
 		* from the source.
		* Note: No Thread Safe
 		*
		* @param source source vertex
		* @param maxWeight maximum weight of the edge
 		*
 		* @return shortest distance for all nodes reachable from source else ERROR in
 		* case there is error in the computation.
 		*/
		virtual const DialResult dial(const Node<T> &source, int maxWeight) const;

		/**
     	* \brief
     	* This function write the graph in an output file
		* Note: No Thread Safe
     	*
		* @param format The Output format of the file
		* @param workingDir The path to the directory in which is placed the Output file
		* @param OFileName The Output File Name ( )
		* @param compress Indicates if the Output will be compressed ( Pay Attention if compress flag is true, not compressed files will be deleted [ #48 ] )
		* @param writeNodeFeat Indicates if export also Node Features
		* @param writeEdgeWeight Indicates if export also Edge Weights
     	* @return 0 if all OK, else return a negative value
     	*/
		virtual int writeToFile(InputOutputFormat format = InputOutputFormat::STANDARD_CSV, const std::string &workingDir = ".", const std::string &OFileName = "graph", bool compress = false, bool writeNodeFeat = false, bool writeEdgeWeight = false) const;

		/**
     	* \brief
     	* This function read the graph from an input file
		* Note: No Thread Safe
     	*
		* @param format The Input format of the file
		* @param workingDir The path to the directory in which is placed the Input file
		* @param OFileName The Input File Name ( )
		* @param compress Indicates if the Input is compressed
		* @param writeNodeFeat Indicates if import also Node Features
		* @param writeEdgeWeight Indicates if import also Edge Weights
     	* @return 0 if all OK, else return a negative value
     	*/
		virtual int readFromFile(InputOutputFormat format = InputOutputFormat::STANDARD_CSV, const std::string &workingDir = ".", const std::string &OFileName = "graph", bool compress = false, bool readNodeFeat = false, bool readEdgeWeight = false);

		/**
     	* \brief
     	* This function partition a graph in a set of partitions
		* Note: No Thread Safe
     	*
		* @param algorithm The partition algorithm
		* @param numberOfPartition The number of partitions
		* @return The partiton Map of the partitioned graph
     	*/
		virtual PartitionMap<T> partitionGraph(PARTITIONING::PartitionAlgorithm algorithm, unsigned int numberOfPartitions) const;

		friend std::ostream &operator<<<>(std::ostream &os, const Graph<T> &graph);
		friend std::ostream &operator<<<>(std::ostream &os, const AdjacencyMatrix<T> &adj);
	};

	template <typename T>
	Graph<T>::Graph(const std::list<const Edge<T> *> &edgeSet)
	{
		for (auto edgeSetIt = edgeSet.begin(); edgeSetIt != edgeSet.end(); ++edgeSetIt)
		{
			if (std::find_if(this->edgeSet.begin(), this->edgeSet.end(), [edgeSetIt](const Edge<T> *edge)
							 { return (*edge == **edgeSetIt); }) == this->edgeSet.end())
			{
				this->edgeSet.push_back(*edgeSetIt);
			}
		}
	}

	template <typename T>
	const std::list<const Edge<T> *> &Graph<T>::getEdgeSet() const
	{
		return edgeSet;
	}

	template <typename T>
	void Graph<T>::setEdgeSet(std::list<const Edge<T> *> &edgeSet)
	{
		this->edgeSet.clear();
		for (auto edgeSetIt = edgeSet.begin(); edgeSetIt != edgeSet.end(); ++edgeSetIt)
		{
			if (std::find_if(this->edgeSet.begin(), this->edgeSet.end(), [edgeSetIt](const Edge<T> *edge)
							 { return (*edge == **edgeSetIt); }) == this->edgeSet.end())
			{
				this->edgeSet.push_back(*edgeSetIt);
			}
		}
	}

	template <typename T>
	void Graph<T>::addEdge(const Edge<T> *edge)
	{
		if (std::find_if(edgeSet.begin(), edgeSet.end(), [edge](const Edge<T> *edge_a)
						 { return (*edge == *edge_a); }) == edgeSet.end())
		{
			edgeSet.push_back(edge);
		}
	}

	template <typename T>
	void Graph<T>::removeEdge(unsigned long edgeId)
	{
		auto edgeOpt = Graph<T>::getEdge(edgeId);
		if (edgeOpt.has_value())
		{
			edgeSet.erase(std::find_if(this->edgeSet.begin(), this->edgeSet.end(), [edgeOpt](const Edge<T> *edge)
									   { return (*(edgeOpt.value()) == *edge); }));
		}
	}

	template <typename T>
	const std::list<const Node<T> *> Graph<T>::getNodeSet() const
	{
		std::list<const Node<T> *> nodeSet;
		for (auto edge : edgeSet)
		{
			if (std::find_if(nodeSet.begin(), nodeSet.end(), [edge](const Node<T> *node)
							 { return (*edge->getNodePair().first == *node); }) == nodeSet.end())
			{
				nodeSet.push_back(edge->getNodePair().first);
			}
			if (std::find_if(nodeSet.begin(), nodeSet.end(), [edge](const Node<T> *node)
							 { return (*edge->getNodePair().second == *node); }) == nodeSet.end())
			{
				nodeSet.push_back(edge->getNodePair().second);
			}
		}
		return nodeSet;
	}

	template <typename T>
	const std::optional<const Edge<T> *> Graph<T>::getEdge(unsigned long edgeId) const
	{

		auto it = edgeSet.begin();
		for (it; it != edgeSet.end(); ++it)
		{
			if ((*it)->getId() == edgeId)
			{
				return *it;
			}
		}

		return std::nullopt;
	}

	template <typename T>
	void Graph<T>::addElementToAdjMatrix(AdjacencyMatrix<T> &adjMatrix, const Node<T> *nodeFrom, const Node<T> *nodeTo, const Edge<T> *edge) const
	{
		std::pair<const Node<T> *, const Edge<T> *> elem = {nodeTo, edge};
		adjMatrix[nodeFrom].push_back(elem);

		//adjMatrix[nodeFrom.getId()].push_back(std::make_pair<const Node<T>,const Edge<T>>(nodeTo, edge));
	}

	template <typename T>
	int Graph<T>::writeToStandardFile_csv(const std::string &workingDir, const std::string &OFileName, bool compress, bool writeNodeFeat, bool writeEdgeWeight) const
	{
		std::ofstream ofileGraph;
		std::string completePathToFileGraph = workingDir + "/" + OFileName + ".csv";
		ofileGraph.open(completePathToFileGraph);
		if (!ofileGraph.is_open())
		{
			// ERROR File Not Open
			return -1;
		}
		auto printOutGraph = [&ofileGraph](const Edge<T> *e)
		{ ofileGraph << e->getId() << "," << e->getNodePair().first->getId() << "," << e->getNodePair().second->getId() << "," << ((e->isDirected().has_value() && e->isDirected().value()) ? 1 : 0) << std::endl; };
		std::for_each(edgeSet.cbegin(), edgeSet.cend(), printOutGraph);
		ofileGraph.close();

		if (writeNodeFeat)
		{
			std::ofstream ofileNodeFeat;
			std::string completePathToFileNodeFeat = workingDir + "/" + OFileName + "_NodeFeat"
																					".csv";
			ofileNodeFeat.open(completePathToFileNodeFeat);
			if (!ofileNodeFeat.is_open())
			{
				// ERROR File Not Open
				return -1;
			}
			auto printOutNodeFeat = [&ofileNodeFeat](const Node<T> *node)
			{ ofileNodeFeat << node->getId() << "," << node->getData() << std::endl; };
			auto nodeSet = getNodeSet();
			std::for_each(nodeSet.cbegin(), nodeSet.cend(), printOutNodeFeat);
			ofileNodeFeat.close();
		}

		if (writeEdgeWeight)
		{
			std::ofstream ofileEdgeWeight;
			std::string completePathToFileEdgeWeight = workingDir + "/" + OFileName + "_EdgeWeight"
																					  ".csv";
			ofileEdgeWeight.open(completePathToFileEdgeWeight);
			if (!ofileEdgeWeight.is_open())
			{
				// ERROR File Not Open
				return -1;
			}
			auto printOutEdgeWeight = [&ofileEdgeWeight](const Edge<T> *e)
			{ ofileEdgeWeight << e->getId() << "," << (e->isWeighted().has_value() && e->isWeighted().value() ? (dynamic_cast<const Weighted *>(e))->getWeight() : 0.0) << "," << (e->isWeighted().has_value() && e->isWeighted().value() ? 1 : 0) << std::endl; };

			std::for_each(edgeSet.cbegin(), edgeSet.cend(), printOutEdgeWeight);
			ofileEdgeWeight.close();
		}
		return 0;
	}

	template <typename T>
	int Graph<T>::readFromStandardFile_csv(const std::string &workingDir, const std::string &OFileName, bool compress, bool readNodeFeat, bool readEdgeWeight)
	{
		std::ifstream ifileGraph;
		std::ifstream ifileNodeFeat;
		std::ifstream ifileEdgeWeight;
		std::map<unsigned long, std::pair<unsigned long, unsigned long>> edgeMap;
		std::map<unsigned long, bool> edgeDirectedMap;
		std::map<unsigned long, T> nodeFeatMap;
		std::map<unsigned long, double> edgeWeightMap;
		std::string completePathToFileGraph = workingDir + "/" + OFileName + ".csv";
		ifileGraph.open(completePathToFileGraph);
		if (!ifileGraph.is_open())
		{
			// ERROR File Not Open
			return -1;
		}
		char comma;
		for (;;)
		{ /* loop continually */
			unsigned long edgeId;
			unsigned long nodeId1;
			unsigned long nodeId2;
			bool directed;
			ifileGraph >> edgeId >> comma >> nodeId1 >> comma >> nodeId2 >> comma >> directed;
			edgeMap[edgeId] = std::pair<unsigned long, unsigned long>(nodeId1, nodeId2);
			edgeDirectedMap[edgeId] = directed;
			if (ifileGraph.fail() || ifileGraph.eof())
				break;
			ifileGraph.ignore(128, '\n');
		}
		ifileGraph.close();

		if (readNodeFeat)
		{
			std::string completePathToFileNodeFeat = workingDir + "/" + OFileName + "_NodeFeat"
																					".csv";
			ifileNodeFeat.open(completePathToFileNodeFeat);
			if (!ifileNodeFeat.is_open())
			{
				// ERROR File Not Open
				return -1;
			}
			for (;;)
			{ /* loop continually */
				unsigned long nodeId;
				T nodeFeat;
				ifileNodeFeat >> nodeId >> comma >> nodeFeat;
				nodeFeatMap[nodeId] = nodeFeat;
				if (ifileNodeFeat.fail() || ifileNodeFeat.eof())
					break;
				ifileNodeFeat.ignore(128, '\n');
			}
			ifileNodeFeat.close();
		}

		if (readEdgeWeight)
		{
			std::string completePathToFileEdgeWeight = workingDir + "/" + OFileName + "_EdgeWeight"
																					  ".csv";
			ifileEdgeWeight.open(completePathToFileEdgeWeight);
			if (!ifileEdgeWeight.is_open())
			{
				// ERROR File Not Open
				return -1;
			}
			for (;;)
			{ /* loop continually */
				unsigned long edgeId;
				double weight;
				bool weighted;
				ifileEdgeWeight >> edgeId >> comma >> weight >> comma >> weighted;
				if (weighted)
				{
					edgeWeightMap[edgeId] = weight;
				}
				if (ifileEdgeWeight.fail() || ifileEdgeWeight.eof())
					break;
				ifileEdgeWeight.ignore(128, '\n');
			}
			ifileEdgeWeight.close();
		}
		recreateGraphFromReadFiles(edgeMap, edgeDirectedMap, nodeFeatMap, edgeWeightMap);
		return 0;
	}

	template <typename T>
	int Graph<T>::writeToStandardFile_tsv(const std::string &workingDir, const std::string &OFileName, bool compress, bool writeNodeFeat, bool writeEdgeWeight) const
	{
		std::ofstream ofileGraph;
		std::string completePathToFileGraph = workingDir + "/" + OFileName + ".tsv";
		ofileGraph.open(completePathToFileGraph);
		if (!ofileGraph.is_open())
		{
			// ERROR File Not Open
			return -1;
		}
		auto printOutGraph = [&ofileGraph](const Edge<T> *e)
		{ ofileGraph << e->getId() << "\t" << e->getNodePair().first->getId() << "\t" << e->getNodePair().second->getId() << "\t" << ((e->isDirected().has_value() && e->isDirected().value()) ? 1 : 0) << std::endl; };
		std::for_each(edgeSet.cbegin(), edgeSet.cend(), printOutGraph);
		ofileGraph.close();

		if (writeNodeFeat)
		{
			std::ofstream ofileNodeFeat;
			std::string completePathToFileNodeFeat = workingDir + "/" + OFileName + "_NodeFeat"
																					".tsv";
			ofileNodeFeat.open(completePathToFileNodeFeat);
			if (!ofileNodeFeat.is_open())
			{
				// ERROR File Not Open
				return -1;
			}
			auto printOutNodeFeat = [&ofileNodeFeat](const Node<T> *node)
			{ ofileNodeFeat << node->getId() << "\t" << node->getData() << std::endl; };
			auto nodeSet = getNodeSet();
			std::for_each(nodeSet.cbegin(), nodeSet.cend(), printOutNodeFeat);
			ofileNodeFeat.close();
		}

		if (writeEdgeWeight)
		{
			std::ofstream ofileEdgeWeight;
			std::string completePathToFileEdgeWeight = workingDir + "/" + OFileName + "_EdgeWeight"
																					  ".tsv";
			ofileEdgeWeight.open(completePathToFileEdgeWeight);
			if (!ofileEdgeWeight.is_open())
			{
				// ERROR File Not Open
				return -1;
			}
			auto printOutEdgeWeight = [&ofileEdgeWeight](const Edge<T> *e)
			{ ofileEdgeWeight << e->getId() << "\t" << (e->isWeighted().has_value() && e->isWeighted().value() ? (dynamic_cast<const Weighted *>(e))->getWeight() : 0.0) << "\t" << (e->isWeighted().has_value() && e->isWeighted().value() ? 1 : 0) << std::endl; };

			std::for_each(edgeSet.cbegin(), edgeSet.cend(), printOutEdgeWeight);
			ofileEdgeWeight.close();
		}
		return 0;
	}

	template <typename T>
	int Graph<T>::readFromStandardFile_tsv(const std::string &workingDir, const std::string &OFileName, bool compress, bool readNodeFeat, bool readEdgeWeight)
	{
		std::ifstream ifileGraph;
		std::ifstream ifileNodeFeat;
		std::ifstream ifileEdgeWeight;
		std::map<unsigned long, std::pair<unsigned long, unsigned long>> edgeMap;
		std::map<unsigned long, bool> edgeDirectedMap;
		std::map<unsigned long, T> nodeFeatMap;
		std::map<unsigned long, double> edgeWeightMap;
		std::string completePathToFileGraph = workingDir + "/" + OFileName + ".tsv";
		ifileGraph.open(completePathToFileGraph);
		if (!ifileGraph.is_open())
		{
			// ERROR File Not Open
			return -1;
		}
		for (;;)
		{ /* loop continually */
			unsigned long edgeId;
			unsigned long nodeId1;
			unsigned long nodeId2;
			bool directed;
			ifileGraph >> edgeId >> std::ws >> nodeId1 >> std::ws >> nodeId2 >> std::ws >> directed;
			edgeMap[edgeId] = std::pair<unsigned long, unsigned long>(nodeId1, nodeId2);
			edgeDirectedMap[edgeId] = directed;
			if (ifileGraph.fail() || ifileGraph.eof())
				break;
			ifileGraph.ignore(128, '\n');
		}
		ifileGraph.close();

		if (readNodeFeat)
		{
			std::string completePathToFileNodeFeat = workingDir + "/" + OFileName + "_NodeFeat"
																					".tsv";
			ifileNodeFeat.open(completePathToFileNodeFeat);
			if (!ifileNodeFeat.is_open())
			{
				// ERROR File Not Open
				return -1;
			}
			for (;;)
			{ /* loop continually */
				unsigned long nodeId;
				T nodeFeat;
				ifileNodeFeat >> nodeId >> std::ws >> nodeFeat;
				nodeFeatMap[nodeId] = nodeFeat;
				if (ifileNodeFeat.fail() || ifileNodeFeat.eof())
					break;
				ifileNodeFeat.ignore(128, '\n');
			}
			ifileNodeFeat.close();
		}

		if (readEdgeWeight)
		{
			std::string completePathToFileEdgeWeight = workingDir + "/" + OFileName + "_EdgeWeight"
																					  ".tsv";
			ifileEdgeWeight.open(completePathToFileEdgeWeight);
			if (!ifileEdgeWeight.is_open())
			{
				// ERROR File Not Open
				return -1;
			}
			for (;;)
			{ /* loop continually */
				unsigned long edgeId;
				double weight;
				bool weighted;
				ifileEdgeWeight >> edgeId >> std::ws >> weight >> std::ws >> weighted;
				if (weighted)
				{
					edgeWeightMap[edgeId] = weight;
				}
				if (ifileEdgeWeight.fail() || ifileEdgeWeight.eof())
					break;
				ifileEdgeWeight.ignore(128, '\n');
			}
			ifileEdgeWeight.close();
		}
		recreateGraphFromReadFiles(edgeMap, edgeDirectedMap, nodeFeatMap, edgeWeightMap);
		return 0;
	}

	template <typename T>
	void Graph<T>::recreateGraphFromReadFiles(std::map<unsigned long, std::pair<unsigned long, unsigned long>> &edgeMap, std::map<unsigned long, bool> &edgeDirectedMap, std::map<unsigned long, T> &nodeFeatMap, std::map<unsigned long, double> &edgeWeightMap)
	{
		std::map<unsigned long, Node<T> *> nodeMap;
		for (auto edgeIt = edgeMap.begin(); edgeIt != edgeMap.end(); ++edgeIt)
		{
			Node<T> *node1 = nullptr;
			Node<T> *node2 = nullptr;
			if (nodeMap.find(edgeIt->second.first) == nodeMap.end())
			{
				//Create new Node
				T feat;
				if (nodeFeatMap.find(edgeIt->second.first) != nodeFeatMap.end())
				{
					feat = nodeFeatMap.at(edgeIt->second.first);
				}
				node1 = new Node<T>(edgeIt->second.first, feat);
				nodeMap[edgeIt->second.first] = node1;
			}
			else
			{
				node1 = nodeMap.at(edgeIt->second.first);
			}
			if (nodeMap.find(edgeIt->second.second) == nodeMap.end())
			{
				//Create new Node
				T feat;
				if (nodeFeatMap.find(edgeIt->second.second) != nodeFeatMap.end())
				{
					feat = nodeFeatMap.at(edgeIt->second.second);
				}
				node2 = new Node<T>(edgeIt->second.second, feat);
				nodeMap[edgeIt->second.second] = node2;
			}
			else
			{
				node2 = nodeMap.at(edgeIt->second.second);
			}

			if (edgeWeightMap.find(edgeIt->first) != edgeWeightMap.end())
			{
				if (edgeDirectedMap.find(edgeIt->first) != edgeDirectedMap.end() && edgeDirectedMap.at(edgeIt->first))
				{
					auto edge = new DirectedWeightedEdge<T>(edgeIt->first, *node1, *node2, edgeWeightMap.at(edgeIt->first));
					addEdge(edge);
				}
				else
				{
					auto edge = new UndirectedWeightedEdge<T>(edgeIt->first, *node1, *node2, edgeWeightMap.at(edgeIt->first));
					addEdge(edge);
				}
			}
			else
			{
				if (edgeDirectedMap.find(edgeIt->first) != edgeDirectedMap.end() && edgeDirectedMap.at(edgeIt->first))
				{
					auto edge = new DirectedEdge<T>(edgeIt->first, *node1, *node2);
					addEdge(edge);
				}
				else
				{
					auto edge = new UndirectedEdge<T>(edgeIt->first, *node1, *node2);
					addEdge(edge);
				}
			}
		}
	}

	template <typename T>
	int Graph<T>::compressFile(const std::string &inputFile, const std::string &outputFile) const
	{

		std::ifstream ifs;
		ifs.open(inputFile);
		if (!ifs.is_open())
		{
			// ERROR File Not Open
			return -1;
		}
		std::string content((std::istreambuf_iterator<char>(ifs)),
							(std::istreambuf_iterator<char>()));

		const char *content_ptr = content.c_str();
		gzFile outFileZ = gzopen(outputFile.c_str(), "wb");
		if (outFileZ == NULL)
		{
			//printf("Error: Failed to gzopen %s\n", outputFile.c_str());
			return -1;
		}

		unsigned int zippedBytes;
		zippedBytes = gzwrite(outFileZ, content_ptr, strlen(content_ptr));

		ifs.close();
		gzclose(outFileZ);
		return 0;
	}

	template <typename T>
	int Graph<T>::decompressFile(const std::string &inputFile, const std::string &outputFile) const
	{

		gzFile inFileZ = gzopen(inputFile.c_str(), "rb");
		if (inFileZ == NULL)
		{
			//printf("Error: Failed to gzopen %s\n", inputFile.c_str());
			return -1;
		}
		unsigned char unzipBuffer[8192];
		unsigned int unzippedBytes;
		std::vector<unsigned char> unzippedData;
		std::ofstream ofs;
		ofs.open(outputFile);
		if (!ofs.is_open())
		{
			// ERROR File Not Open
			return -1;
		}
		while (true)
		{
			unzippedBytes = gzread(inFileZ, unzipBuffer, 8192);
			if (unzippedBytes > 0)
			{
				unzippedData.insert(unzippedData.end(), unzipBuffer, unzipBuffer + unzippedBytes);
			}
			else
			{
				break;
			}
		}
		for (auto c : unzippedData)
		{
			ofs << c;
		}
		ofs << std::endl;
		ofs.close();
		gzclose(inFileZ);
		return 0;
	}

	template <typename T>
	const unsigned long Graph<T>::setFind(Subset subsets [], const unsigned long nodeId) const
	{
		// find root and make root as parent of i
		// (path compression)
		if (subsets[nodeId].parent != nodeId)
		{
			subsets[nodeId].parent = Graph<T>::setFind(subsets, subsets[nodeId].parent);
		}
		
		return subsets[nodeId].parent;
	}

	template <typename T>
	void Graph<T>::setUnion(Subset subsets [], const unsigned long elem1, const unsigned long elem2) const
	{
		// if both sets have same parent
		// then there's nothing to be done
		if (subsets[elem1].parent==subsets[elem2].parent)
			return;
		auto elem1Parent = Graph<T>::setFind(subsets, elem1);
		auto elem2Parent = Graph<T>::setFind(subsets, elem2);
		if(subsets[elem1Parent].rank < subsets[elem2Parent].rank) 
			subsets[elem1Parent].parent = elem2Parent;
		else if(subsets[elem1Parent].rank > subsets[elem2Parent].rank) 
			subsets[elem2Parent].parent = elem1Parent;
		else
		{
			subsets[elem2Parent].parent = elem1Parent;
			subsets[elem1Parent].rank++;
		}	
	}
	
	template <typename T>
	const AdjacencyMatrix<T> Graph<T>::getAdjMatrix() const
	{
		AdjacencyMatrix<T> adj;
		auto edgeSetIt = edgeSet.begin();
		for (edgeSetIt; edgeSetIt != edgeSet.end(); ++edgeSetIt)
		{
			if ((*edgeSetIt)->isDirected().has_value() && (*edgeSetIt)->isDirected().value())
			{
				const DirectedEdge<T> *d_edge = dynamic_cast<const DirectedEdge<T> *>(*edgeSetIt);
				addElementToAdjMatrix(adj, &(d_edge->getFrom()), &(d_edge->getTo()), d_edge);
			}
			else if ((*edgeSetIt)->isDirected().has_value() && !(*edgeSetIt)->isDirected().value())
			{
				const UndirectedEdge<T> *ud_edge = dynamic_cast<const UndirectedEdge<T> *>(*edgeSetIt);
				;
				addElementToAdjMatrix(adj, &(ud_edge->getNode1()), &(ud_edge->getNode2()), ud_edge);
				addElementToAdjMatrix(adj, &(ud_edge->getNode2()), &(ud_edge->getNode1()), ud_edge);
			}
			else
			{ //is a simple edge we cannot create adj matrix
				return adj;
			}
		}
		return adj;
	}

	template <typename T>
	const DijkstraResult Graph<T>::dijkstra(const Node<T> &source, const Node<T> &target) const
	{
		DijkstraResult result;
		result.success = false;
		result.errorMessage = "";
		result.result = INF_DOUBLE;
		auto nodeSet = Graph<T>::getNodeSet();
		if (std::find(nodeSet.begin(), nodeSet.end(), &source) == nodeSet.end())
		{
			// check if source node exist in the graph
			result.errorMessage = ERR_SOURCE_NODE_NOT_IN_GRAPH;
			return result;
		}
		if (std::find(nodeSet.begin(), nodeSet.end(), &target) == nodeSet.end())
		{
			// check if target node exist in the graph
			result.errorMessage = ERR_TARGET_NODE_NOT_IN_GRAPH;
			return result;
		}
		const AdjacencyMatrix<T> adj = Graph<T>::getAdjMatrix();
		// n denotes the number of vertices in graph
		int n = adj.size();

		// setting all the distances initially to INF_DOUBLE
		std::map<const Node<T> *, double> dist;

		for (auto elem : adj)
		{
			dist[elem.first] = INF_DOUBLE;
		}

		// creating a min heap using priority queue
		// first element of pair contains the distance
		// second element of pair contains the vertex
		std::priority_queue<std::pair<double, const Node<T> *>, std::vector<std::pair<double, const Node<T> *>>,
							std::greater<std::pair<double, const Node<T> *>>>
			pq;

		// pushing the source vertex 's' with 0 distance in min heap
		pq.push(std::make_pair(0.0, &source));

		// marking the distance of source as 0
		dist[&source] = 0;

		while (!pq.empty())
		{
			// second element of pair denotes the node / vertex
			const Node<T> *currentNode = pq.top().second;

			// first element of pair denotes the distance
			double currentDist = pq.top().first;

			pq.pop();

			// for all the reachable vertex from the currently exploring vertex
			// we will try to minimize the distance
			if (adj.find(currentNode) != adj.end())
			{
				for (std::pair<const Node<T> *, const Edge<T> *> elem : adj.at(currentNode))
				{
					// minimizing distances
					if (elem.second->isWeighted().has_value() && elem.second->isWeighted().value())
					{
						if (elem.second->isDirected().has_value() && elem.second->isDirected().value())
						{
							const DirectedWeightedEdge<T> *dw_edge = dynamic_cast<const DirectedWeightedEdge<T> *>(elem.second);
							if (currentDist + dw_edge->getWeight() < dist[elem.first])
							{
								dist[elem.first] = currentDist + dw_edge->getWeight();
								pq.push(std::make_pair(dist[elem.first], elem.first));
							}
						}
						else if (elem.second->isDirected().has_value() && !elem.second->isDirected().value())
						{
							const UndirectedWeightedEdge<T> *udw_edge = dynamic_cast<const UndirectedWeightedEdge<T> *>(elem.second);
							if (currentDist + udw_edge->getWeight() < dist[elem.first])
							{
								dist[elem.first] = currentDist + udw_edge->getWeight();
								pq.push(std::make_pair(dist[elem.first], elem.first));
							}
						}
						else
						{
							//ERROR it shouldn't never returned ( does not exist a Node Weighted and not Directed/Undirected)
							result.errorMessage = ERR_NO_DIR_OR_UNDIR_EDGE;
							return result;
						}
					}
					else
					{
						// No Weighted Edge
						result.errorMessage = ERR_NO_WEIGHTED_EDGE;
						return result;
					}
				}
			}
		}
		if (dist[&target] != INF_DOUBLE)
		{
			result.success = true;
			result.errorMessage = "";
			result.result = dist[&target];
			return result;
		}
		result.errorMessage = ERR_TARGET_NODE_NOT_REACHABLE;
		result.result = -1;
		return result;
	}

	template <typename T>
	const BellmanFordResult Graph<T>::bellmanford(const Node<T> &source, const Node<T> &target) const
	{
		BellmanFordResult result;
		result.success = false;
		result.errorMessage = "";
		result.result = INF_DOUBLE;
		auto nodeSet = Graph<T>::getNodeSet();
		if (std::find(nodeSet.begin(), nodeSet.end(), &source) == nodeSet.end())
		{
			// check if source node exist in the graph
			result.errorMessage = ERR_SOURCE_NODE_NOT_IN_GRAPH;
			return result;
		}
		if (std::find(nodeSet.begin(), nodeSet.end(), &target) == nodeSet.end())
		{
			// check if target node exist in the graph
			result.errorMessage = ERR_TARGET_NODE_NOT_IN_GRAPH;
			return result;
		}
		// setting all the distances initially to INF_DOUBLE
		std::map<const Node<T> *, double> dist, currentDist;
		// n denotes the number of vertices in graph
		auto n = nodeSet.size();
		for (auto elem : nodeSet)
		{
			dist[elem] = INF_DOUBLE;
			currentDist[elem] = INF_DOUBLE;
		}

		// marking the distance of source as 0
		dist[&source] = 0;
		// set if node distances in two consecutive
		// iterations remain the same.
		auto earlyStopping = false;
		// outer loop for vertex relaxation
		for (int i=0; i<n-1; i++)
		{
			auto edgeSet = Graph<T>::getEdgeSet();
			// inner loop for distance updates of
			// each relaxation
			for (auto edge : edgeSet)
			{
				auto elem = edge->getNodePair();
				if (edge->isWeighted().has_value() && edge->isWeighted().value())
				{
					auto edge_weight = (dynamic_cast<const Weighted *>(edge))->getWeight();
					if (dist[elem.first] + edge_weight < dist[elem.second])
						dist[elem.second] = dist[elem.first] + edge_weight;
				}
				else
				{
					// No Weighted Edge
					result.errorMessage = ERR_NO_WEIGHTED_EDGE;
					return result;
				}
			}
			auto flag = true;
			for (const auto& [key, value] : dist) {
				if (currentDist[key]!=value)
				{
					flag = false;
					break;
				}
			}
			for (const auto& [key, value] : dist) {
				currentDist[key] = value;  //update the current distance
			}
			if (flag)
			{
				earlyStopping = true;
				break;
			}
		}

		// check if there exists a negative cycle
		if (!earlyStopping)
		{
			auto edgeSet = Graph<T>::getEdgeSet();
			for (auto edge : edgeSet)
			{
				auto elem = edge->getNodePair();
				auto edge_weight = (dynamic_cast<const Weighted *>(edge))->getWeight();
				if (dist[elem.first] + edge_weight < dist[elem.second])
				{
					result.success = true;
					result.negativeCycle =  true;
					result.errorMessage = "";
					return result;
				}
			}
		}

		if (dist[&target] != INF_DOUBLE)
		{
			result.success = true;
			result.errorMessage = "";
			result.negativeCycle =  false;
			result.result = dist[&target];
			return result;
		}
		result.errorMessage = ERR_TARGET_NODE_NOT_REACHABLE;
		result.result = -1;
		return result;
	}

	template <typename T>
	const FWResult Graph<T>::floydWarshall() const
	{
		FWResult result;
		result.success = false;
		result.errorMessage = "";
		std::map<std::pair<unsigned long, unsigned long>, double> pairwise_dist;
		auto nodeSet = Graph<T>::getNodeSet();
		// create a pairwise distance matrix with distance node distances
		// set to inf. Distance of node to itself is set as 0.
		for (auto elem1 : nodeSet)
		{
			for (auto elem2 : nodeSet)
			{
				auto key = std::make_pair(elem1->getId(), elem2->getId());
				if (elem1 != elem2)
					pairwise_dist[key] = INF_DOUBLE;
				else
					pairwise_dist[key] = 0.0;
			}
		}

		auto edgeSet = Graph<T>::getEdgeSet();
		// update the weights of nodes
		// connected by edges
		for (auto edge : edgeSet)
		{
			auto elem = edge->getNodePair();
			if (edge->isWeighted().has_value() && edge->isWeighted().value())
			{
				auto edgeWeight = (dynamic_cast<const Weighted *>(edge))->getWeight();
				auto key = std::make_pair(elem.first->getId(), elem.second->getId());
				pairwise_dist[key] = edgeWeight;
			}
			else
			{
				// if an edge exists but has no weight associated
				// with it, we return an error message
				result.errorMessage = ERR_NO_WEIGHTED_EDGE;
				return result;
			}
		}

		for (auto k : nodeSet)
		{
			// set all vertices as source one by one
			for (auto src : nodeSet)
			{
				// iterate through all vertices as destination for the
				// current source
				auto src_k = std::make_pair(src->getId(), k->getId());
				for (auto dst : nodeSet)
				{
					// If vertex k provides a shorter path than
					// src to dst, update the value of
					// pairwise_dist[src_to_dst]
					auto src_dst = std::make_pair(src->getId(), dst->getId());
					auto k_dst = std::make_pair(k->getId(), dst->getId());
					if (pairwise_dist[src_dst] > (pairwise_dist[src_k] + pairwise_dist[k_dst]) && (pairwise_dist[k_dst] != INF_DOUBLE && pairwise_dist[src_k] != INF_DOUBLE))
						pairwise_dist[src_dst] = pairwise_dist[src_k] + pairwise_dist[k_dst];
				}
			}
		}

		result.success = true;
		// presense of negative number in the diagonal indicates
		// that that the graph contains a negative cycle
		for (auto node : nodeSet)
		{
			auto diag = std::make_pair(node->getId(), node->getId());
			if (pairwise_dist[diag] < 0.)
			{
				result.negativeCycle = true;
				return result;
			}
		}
		result.result = std::move(pairwise_dist);
		return result;
	}

	template <typename T>
	const PrimResult Graph<T>::prim() const
	{
		PrimResult result;
		result.success = false;
		result.errorMessage = "";
		result.mstCost = INF_DOUBLE;
		if (!isUndirectedGraph())
		{
			result.errorMessage = ERR_DIR_GRAPH;
			return result;
		}
		auto nodeSet = Graph<T>::getNodeSet();
		auto n = nodeSet.size();
		const AdjacencyMatrix<T> adj = Graph<T>::getAdjMatrix();

		// setting all the distances initially to INF_DOUBLE
		std::map<const Node<T> *, double> dist;
		for (auto elem : adj)
		{
			dist[elem.first] = INF_DOUBLE;
		}

		// creating a min heap using priority queue
		// first element of pair contains the distance
		// second element of pair contains the vertex
		std::priority_queue<std::pair<double, const Node<T> *>, std::vector<std::pair<double, const Node<T> *>>,
							std::greater<std::pair<double, const Node<T> *>>>
			pq;

		// pushing the source vertex 's' with 0 distance in min heap
		auto source = nodeSet.front();
		pq.push(std::make_pair(0.0, source));
		// initialize cost and start node of mst
		result.result.push_back(source->getId());
		result.mstCost = 0;
		while (!pq.empty())
		{
			// second element of pair denotes the node / vertex
			const Node<T> *currentNode = pq.top().second;
			auto nodeId = currentNode->getId();			
			if (std::find(result.result.begin(), result.result.end(), nodeId) == result.result.end())
			{
				result.result.push_back(nodeId);
				result.mstCost += pq.top().first;
			}

			pq.pop();
			// for all the reachable vertex from the currently exploring vertex
			// we will try to minimize the distance
			if (adj.find(currentNode) != adj.end())
			{
				for (std::pair<const Node<T> *, const Edge<T> *> elem : adj.at(currentNode))
				{
					// minimizing distances
					if (elem.second->isWeighted().has_value() && elem.second->isWeighted().value())
					{
						const UndirectedWeightedEdge<T> *udw_edge = dynamic_cast<const UndirectedWeightedEdge<T> *>(elem.second);
						if ( 
							(udw_edge->getWeight() < dist[elem.first]) &&
							(std::find(result.result.begin(), result.result.end(), elem.first->getId()) == result.result.end())
						)

						{
							dist[elem.first] = udw_edge->getWeight();
							pq.push(std::make_pair(dist[elem.first], elem.first));
						}
					}
					else
					{
						// No Weighted Edge
						result.errorMessage = ERR_NO_WEIGHTED_EDGE;
						return result;
					}
				}
			}
		}
		result.success = true;
		return result;
	}

	template <typename T>
	const std::vector<Node<T>> Graph<T>::breadth_first_search(const Node<T> &start) const
	{
		// vector to keep track of visited nodes
		std::vector<Node<T>> visited;
		auto nodeSet = Graph<T>::getNodeSet();
		//check is exist node in the graph
		if (std::find(nodeSet.begin(), nodeSet.end(), &start) == nodeSet.end())
		{
			return visited;
		}
		const AdjacencyMatrix<T> adj = Graph<T>::getAdjMatrix();
		// queue that stores vertices that need to be further explored
		std::queue<const Node<T> *> tracker;

		// mark the starting node as visited
		visited.push_back(start);
		tracker.push(&start);
		while (!tracker.empty())
		{
			const Node<T> *node = tracker.front();
			tracker.pop();
			if (adj.find(node) != adj.end())
			{
				for (auto elem : adj.at(node))
				{
					// if the node is not visited then mark it as visited
					// and push it to the queue
					if (std::find(visited.begin(), visited.end(), *(elem.first)) == visited.end())
					{
						visited.push_back(*(elem.first));
						tracker.push(elem.first);
					}
				}
			}
		}

		return visited;
	}

	template <typename T>
	const std::vector<Node<T>> Graph<T>::depth_first_search(const Node<T> &start) const
	{
		// vector to keep track of visited nodes
		std::vector<Node<T>> visited;
		auto nodeSet = Graph<T>::getNodeSet();
		//check is exist node in the graph
		if (std::find(nodeSet.begin(), nodeSet.end(), &start) == nodeSet.end())
		{
			return visited;
		}
		const AdjacencyMatrix<T> adj = Graph<T>::getAdjMatrix();
		std::function<void(const AdjacencyMatrix<T> &, const Node<T> &, std::vector<Node<T>> &)> explore;
		explore = [&explore](const AdjacencyMatrix<T> &adj, const Node<T> &node, std::vector<Node<T>> &visited) -> void
		{
			visited.push_back(node);
			if (adj.find(&node) != adj.end())
			{
				for (auto x : adj.at(&node))
				{
					if (std::find(visited.begin(), visited.end(), *(x.first)) == visited.end())
					{
						explore(adj, *(x.first), visited);
					}
				}
			}
		};
		explore(adj, start, visited);

		return visited;
	}

	template <typename T>
	bool Graph<T>::isCyclicDirectedGraphDFS() const
	{
		if (!isDirectedGraph())
		{
			return false;
		}
		enum nodeStates : uint8_t
		{
			not_visited,
			in_stack,
			visited
		};
		auto nodeSet = Graph<T>::getNodeSet();
		auto adjMatrix = Graph<T>::getAdjMatrix();

		/* State of the node.
         *
         * It is a vector of "nodeStates" which represents the state node is in.
         * It can take only 3 values: "not_visited", "in_stack", and "visited".
         *
         * Initially, all nodes are in "not_visited" state.
         */
		std::map<unsigned long, nodeStates> state;
		for (auto node : nodeSet)
		{
			state[node->getId()] = not_visited;
		}
		int stateCounter = 0;

		// Start visiting each node.
		for (auto node : nodeSet)
		{
			// If a node is not visited, only then check for presence of cycle.
			// There is no need to check for presence of cycle for a visited
			// node as it has already been checked for presence of cycle.
			if (state[node->getId()] == not_visited)
			{
				// Check for cycle.
				std::function<bool(AdjacencyMatrix<T> &, std::map<unsigned long, nodeStates> &, const Node<T> *)> isCyclicDFSHelper;
				isCyclicDFSHelper = [this, &isCyclicDFSHelper](AdjacencyMatrix<T> &adjMatrix, std::map<unsigned long, nodeStates> &states, const Node<T> *node)
				{
					// Add node "in_stack" state.
					states[node->getId()] = in_stack;

					// If the node has children, then recursively visit all children of the
					// node.
					auto const it = adjMatrix.find(node);
					if (it != adjMatrix.end())
					{
						for (auto child : it->second)
						{
							// If state of child node is "not_visited", evaluate that child
							// for presence of cycle.
							auto state_of_child = states.at((std::get<0>(child))->getId());
							if (state_of_child == not_visited)
							{
								if (isCyclicDFSHelper(adjMatrix, states, std::get<0>(child)))
								{
									return true;
								}
							}
							else if (state_of_child == in_stack)
							{
								// If child node was "in_stack", then that means that there
								// is a cycle in the graph. Return true for presence of the
								// cycle.
								return true;
							}
						}
					}

					// Current node has been evaluated for the presence of cycle and had no
					// cycle. Mark current node as "visited".
					states[node->getId()] = visited;
					// Return that current node didn't result in any cycles.
					return false;
				};
				if (isCyclicDFSHelper(adjMatrix, state, node))
				{
					return true;
				}
			}
		}

		// All nodes have been safely traversed, that means there is no cycle in
		// the graph. Return false.
		return false;
	}

	template <typename T>
	bool Graph<T>::isCyclicDirectedGraphBFS() const
	{
		if (!isDirectedGraph())
		{
			return false;
		}
		auto adjMatrix = Graph<T>::getAdjMatrix();
		auto nodeSet = Graph<T>::getNodeSet();

		std::map<unsigned long, unsigned int> indegree;
		for (auto node : nodeSet)
		{
			indegree[node->getId()] = 0;
		}
		// Calculate the indegree i.e. the number of incident edges to the node.
		for (auto const &list : adjMatrix)
		{
			auto children = list.second;
			for (auto const &child : children)
			{
				indegree[std::get<0>(child)->getId()]++;
			}
		}

		std::queue<const Node<T> *> can_be_solved;
		for (auto node : nodeSet)
		{
			// If a node doesn't have any input edges, then that node will
			// definately not result in a cycle and can be visited safely.
			if (!indegree[node->getId()])
			{
				can_be_solved.emplace(&(*node));
			}
		}

		// Vertices that need to be traversed.
		auto remain = Graph<T>::getNodeSet().size();
		// While there are safe nodes that we can visit.
		while (!can_be_solved.empty())
		{
			auto solved = can_be_solved.front();
			// Visit the node.
			can_be_solved.pop();
			// Decrease number of nodes that need to be traversed.
			remain--;

			// Visit all the children of the visited node.
			auto it = adjMatrix.find(solved);
			if (it != adjMatrix.end())
			{
				for (auto child : it->second)
				{
					// Check if we can visited the node safely.
					if (--indegree[std::get<0>(child)->getId()] == 0)
					{
						// if node can be visited safely, then add that node to
						// the visit queue.
						can_be_solved.emplace(std::get<0>(child));
					}
				}
			}
		}

		// If there are still nodes that we can't visit, then it means that
		// there is a cycle and return true, else return false.
		return !(remain == 0);
	}

	template <typename T>
	bool Graph<T>::isDirectedGraph() const
	{
		auto edgeSet = Graph<T>::getEdgeSet();
		for (auto edge : edgeSet)
		{
			if (!(edge->isDirected().has_value() && edge->isDirected().value()))
			{
				//Found Undirected Edge
				return false;
			}
		}
		//No Undirected Edge
		return true;
	}

	template <typename T>
	bool Graph<T>::isUndirectedGraph() const
	{
		auto edgeSet = Graph<T>::getEdgeSet();
		for (auto edge : edgeSet)
		{
			if ((edge->isDirected().has_value() && edge->isDirected().value()))
			{
				//Found Directed Edge
				return false;
			}
		}
		//No Directed Edge
		return true;
	}

	template <typename T>
	const DialResult Graph<T>::dial(const Node<T> &source, int maxWeight) const
	{
		DialResult result;
		result.success = false;

		auto adj = Graph<T>::getAdjMatrix();
		auto nodeSet = Graph<T>::getNodeSet();

		if (std::find(nodeSet.begin(), nodeSet.end(), &source) == nodeSet.end())
		{
			// check if source node exist in the graph
			result.errorMessage = ERR_SOURCE_NODE_NOT_IN_GRAPH;
			return result;
		}
		/* With each distance, iterator to that vertex in
       		its bucket is stored so that vertex can be deleted
       		in O(1) at time of updation. So
    		dist[i].first = distance of ith vertex from src vertex
    		dits[i].second = vertex i in bucket number */
		unsigned int V = nodeSet.size();
		std::map<const Node<T> *, std::pair<long, const Node<T> *>> dist;

		// Initialize all distances as infinite (INF)
		for (auto node : nodeSet)
		{
			dist[&(*node)].first = std::numeric_limits<long>::max();
		}

		// Create buckets B[].
		// B[i] keep vertex of distance label i
		std::list<const Node<T> *> B[maxWeight * V + 1];

		B[0].push_back(&source);
		dist[&source].first = 0;

		int idx = 0;
		while (1)
		{
			// Go sequentially through buckets till one non-empty
			// bucket is found
			while (B[idx].size() == 0 && idx < maxWeight * V)
			{
				idx++;
			}

			// If all buckets are empty, we are done.
			if (idx == maxWeight * V)
			{
				break;
			}

			// Take top vertex from bucket and pop it
			auto u = B[idx].front();
			B[idx].pop_front();

			// Process all adjacents of extracted vertex 'u' and
			// update their distanced if required.
			for (auto i = adj[u].begin(); i != adj[u].end(); ++i)
			{
				auto v = (*i).first;
				int weight = 0;
				if ((*i).second->isWeighted().has_value() && (*i).second->isWeighted().value())
				{
					if ((*i).second->isDirected().has_value() && (*i).second->isDirected().value())
					{
						const DirectedWeightedEdge<T> *dw_edge = dynamic_cast<const DirectedWeightedEdge<T> *>((*i).second);
						weight = dw_edge->getWeight();
					}
					else if ((*i).second->isDirected().has_value() && !(*i).second->isDirected().value())
					{
						const UndirectedWeightedEdge<T> *udw_edge = dynamic_cast<const UndirectedWeightedEdge<T> *>((*i).second);
						weight = udw_edge->getWeight();
					}
					else
					{
						//ERROR it shouldn't never returned ( does not exist a Node Weighted and not Directed/Undirected)
						result.errorMessage = ERR_NO_DIR_OR_UNDIR_EDGE;
						return result;
					}
				}
				else
				{
					// No Weighted Edge
					result.errorMessage = ERR_NO_WEIGHTED_EDGE;
					return result;
				}
				auto u_i = std::find_if(dist.begin(), dist.end(), [u](std::pair<const Node<T> *, std::pair<long, const Node<T> *>> const &it)
										{ return (*u == *(it.first)); });

				auto v_i = std::find_if(dist.begin(), dist.end(), [v](std::pair<const Node<T> *, std::pair<long, const Node<T> *>> const &it)
										{ return (*v == *(it.first)); });
				long du = u_i->second.first;
				long dv = v_i->second.first;

				// If there is shorted path to v through u.
				if (dv > du + weight)
				{
					// If dv is not INF then it must be in B[dv]
					// bucket, so erase its entry using iterator
					// in O(1)
					if (dv != std::numeric_limits<long>::max())
					{
						auto findIter = std::find(B[dv].begin(), B[dv].end(), dist[v].second);
						B[dv].erase(findIter);
					}

					//  updating the distance
					dist[v].first = du + weight;
					dv = dist[v].first;

					// pushing vertex v into updated distance's bucket
					B[dv].push_front(v);

					// storing updated iterator in dist[v].second
					dist[v].second = *(B[dv].begin());
				}
			}
		}
		for (auto dist_i : dist)
		{
			result.minDistanceMap[dist_i.first->getId()] = dist_i.second.first;
		}
		result.success = true;

		return result;
	}

	template <typename T>
	const std::vector<Node<T>> Graph<T>::graph_slicing(const Node<T> &start) const
	{
		std::vector<Node<T>> result;

		std::list<const Node<T> *> nodeSet = Graph<T>::getNodeSet();
		//check if start node in the graph
		if (std::find(nodeSet.begin(), nodeSet.end(), &start) == nodeSet.end())
		{
			return result;
		}
		std::vector<Node<T>> C = Graph<T>::depth_first_search(start);
		std::list<const Node<T> *> C1; //complement of C i.e. nodeSet - C
		for (auto const node : nodeSet)
		{
			// from the set of all nodes, remove nodes that exist in C
			if (std::find_if(C.begin(), C.end(), [node](const Node<T> nodeC)
							 { return (*node == nodeC); }) == C.end())
				C1.push_back(node);
		}

		// For all nodes in C', apply DFS
		//  and get the list of reachable nodes and store in M
		std::vector<Node<T>> M;
		for (auto const node : C1)
		{
			std::vector<Node<T>> reachableNodes = Graph<T>::depth_first_search(*node);
			M.insert(M.end(),reachableNodes.begin(),reachableNodes.end());
		}
		// removes nodes from C that are reachable from M.
		for (const Node<T> nodeC : C)
		{
			if (std::find_if(M.begin(), M.end(), [nodeC](const Node<T> nodeM)
								{ return (nodeM == nodeC); }) == M.end())
				result.push_back(nodeC);
		}
		return result;
	}

	template <typename T>
	int Graph<T>::writeToFile(InputOutputFormat format, const std::string &workingDir, const std::string &OFileName, bool compress, bool writeNodeFeat, bool writeEdgeWeight) const
	{
		int result = 0;
		if (format == InputOutputFormat::STANDARD_CSV)
		{
			result = writeToStandardFile_csv(workingDir, OFileName, compress, writeNodeFeat, writeEdgeWeight);
		}
		else if (format == InputOutputFormat::STANDARD_TSV)
		{
			result = writeToStandardFile_tsv(workingDir, OFileName, compress, writeNodeFeat, writeEdgeWeight);
		}
		else
		{
			//OUTPUT FORMAT NOT RECOGNIZED
			return -1;
		}
		if (result == 0 && compress)
		{
			auto compress = [this, &workingDir, &OFileName, &writeNodeFeat, &writeEdgeWeight](const std::string &extension)
			{
				std::string completePathToFileGraph = workingDir + "/" + OFileName + extension;
				std::string completePathToFileGraphCompressed = workingDir + "/" + OFileName + extension + ".gz";
				int _result = compressFile(completePathToFileGraph, completePathToFileGraphCompressed);
				if (_result == 0)
				{
					_result = remove(completePathToFileGraph.c_str());
				}
				if (_result == 0)
				{
					if (writeNodeFeat)
					{
						std::string completePathToFileNodeFeat = workingDir + "/" + OFileName + "_NodeFeat" + extension;
						std::string completePathToFileNodeFeatCompressed = workingDir + "/" + OFileName + "_NodeFeat" + extension + ".gz";
						_result = compressFile(completePathToFileNodeFeat, completePathToFileNodeFeatCompressed);
						if (_result == 0)
						{
							_result = remove(completePathToFileNodeFeat.c_str());
						}
					}
				}
				if (_result == 0)
				{
					if (writeEdgeWeight)
					{
						std::string completePathToFileEdgeWeight = workingDir + "/" + OFileName + "_EdgeWeight" + extension;
						std::string completePathToFileEdgeWeightCompressed = workingDir + "/" + OFileName + "_EdgeWeight" + extension + ".gz";
						_result = compressFile(completePathToFileEdgeWeight, completePathToFileEdgeWeightCompressed);
						if (_result == 0)
						{
							_result = remove(completePathToFileEdgeWeight.c_str());
						}
					}
				}
				return _result;
			};
			if (format == InputOutputFormat::STANDARD_CSV)
			{
				auto result = compress(".csv");
			}
			else if (format == InputOutputFormat::STANDARD_TSV)
			{
				auto result = compress(".tsv");
			}
			else
			{
				//OUTPUT FORMAT NOT RECOGNIZED
				result = -1;
			}
		}
		return result;
	}

	template <typename T>
	int Graph<T>::readFromFile(InputOutputFormat format, const std::string &workingDir, const std::string &OFileName, bool compress, bool readNodeFeat, bool readEdgeWeight)
	{
		int result = 0;
		if (compress)
		{
			auto decompress = [this, &workingDir, &OFileName, &readNodeFeat, &readEdgeWeight](const std::string &extension)
			{
				std::string completePathToFileGraph = workingDir + "/" + OFileName + extension;
				std::string completePathToFileGraphCompressed = workingDir + "/" + OFileName + extension + ".gz";
				int _result = decompressFile(completePathToFileGraphCompressed, completePathToFileGraph);
				if (_result == 0)
				{
					if (readNodeFeat)
					{
						std::string completePathToFileNodeFeat = workingDir + "/" + OFileName + "_NodeFeat" + extension;
						std::string completePathToFileNodeFeatCompressed = workingDir + "/" + OFileName + "_NodeFeat" + extension + ".gz";
						_result = decompressFile(completePathToFileNodeFeatCompressed, completePathToFileNodeFeat);
					}
				}
				if (_result == 0)
				{
					if (readEdgeWeight)
					{
						std::string completePathToFileEdgeWeight = workingDir + "/" + OFileName + "_EdgeWeight" + extension;
						std::string completePathToFileEdgeWeightCompressed = workingDir + "/" + OFileName + "_EdgeWeight" + extension + ".gz";
						_result = decompressFile(completePathToFileEdgeWeightCompressed, completePathToFileEdgeWeight);
					}
				}
				return _result;
			};
			if (format == InputOutputFormat::STANDARD_CSV)
			{
				result = decompress(".csv");
			}
			else if (format == InputOutputFormat::STANDARD_TSV)
			{
				result = decompress(".tsv");
			}
			else
			{
				//OUTPUT FORMAT NOT RECOGNIZED
				result = -1;
			}
		}
		if (result == 0)
		{
			if (format == InputOutputFormat::STANDARD_CSV)
			{
				result = readFromStandardFile_csv(workingDir, OFileName, compress, readNodeFeat, readEdgeWeight);
			}
			else if (format == InputOutputFormat::STANDARD_TSV)
			{
				result = readFromStandardFile_tsv(workingDir, OFileName, compress, readNodeFeat, readEdgeWeight);
			}
			else
			{
				//OUTPUT FORMAT NOT RECOGNIZED
				result = -1;
			}
		}
		return result;
	}

	template <typename T>
	PartitionMap<T> Graph<T>::partitionGraph(PARTITIONING::PartitionAlgorithm algorithm, unsigned int numberOfPartitions) const
	{
		PartitionMap<T> partitionMap;
		PARTITIONING::Globals globals(numberOfPartitions,algorithm);

		PARTITIONING::Partitioner<T> partitioner(getEdgeSet(), globals);
		PARTITIONING::CoordinatedPartitionState<T> partitionState = partitioner.performCoordinatedPartition();
		partitionMap = partitionState.getPartitionMap();

		return partitionMap;

	}

	template <typename T>
	std::ostream &operator<<(std::ostream &os, const Graph<T> &graph){
		os << "Graph:\n";
		auto edgeList = graph.getEdgeSet();
		auto it = edgeList.begin();
		for(it; it != edgeList.end(); ++it){
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

	template <typename T>
	std::ostream &operator<<(std::ostream &os, const AdjacencyMatrix<T> &adj)
	{
		os << "Adjacency Matrix:\n";
		auto it = adj.begin();
		unsigned long max_column = 0;
		for (it; it != adj.end(); ++it)
		{
			if (it->second.size() > max_column)
			{
				max_column = it->second.size();
			}
		}
		if (max_column == 0)
		{
			os << "ERROR in Print\n";
			return os;
		}
		else
		{
			it = adj.begin();
			os << "|--|";
			for (int i = 0; i < max_column; i++)
			{
				os << "-----|";
			}
			os << "\n";
			for (it; it != adj.end(); ++it)
			{
				os << "|N" << it->first->getId() << "|";
				auto it2 = it->second.begin();
				for (it2; it2 != it->second.end(); ++it2)
				{
					os << "N" << it2->first->getId() << ",E" << it2->second->getId() << "|";
				}
				os << "\n|--|";
				for (int i = 0; i < max_column; i++)
				{
					os << "-----|";
				}
				os << "\n";
			}
		}
		return os;
	}

} // namespace CXXGRAPH
#endif // __GRAPH_H__