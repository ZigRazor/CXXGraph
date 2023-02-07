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

#ifndef __CXXGRAPH_GRAPH_H__
#define __CXXGRAPH_GRAPH_H__

#pragma once

#include <utility>
#include <set>
#include <unordered_set>
#include <map>
#include <optional>
#include <iostream>
#include <limits>
#include <list>
#include <deque>
#include <queue>
#include <stack>
#include <string>
#include <cstring>
#include <functional>
#include <fstream>
#include <limits.h>
#include <mutex>
#include <condition_variable>
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
	//Typedef for Allocator
	//typedef size_t DataType;
    //typedef Moya::Allocator<const Edge<T> *,16* 1024> MemoryPoolAllocator;
	template<typename T>
	using T_EdgeSet = std::unordered_set<const Edge<T> *>;

	namespace PARTITIONING
	{
		template <typename T>
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
		T_EdgeSet<T> edgeSet = {};
		std::optional<std::pair<std::string, char>> getExtenstionAndSeparator(InputOutputFormat format) const;
		int writeToStandardFile(const std::string &workingDir, const std::string &OFileName, bool compress, bool writeNodeFeat, bool writeEdgeWeight, InputOutputFormat format) const;
		int readFromStandardFile(const std::string &workingDir, const std::string &OFileName, bool compress, bool readNodeFeat, bool readEdgeWeight, InputOutputFormat format);
		void recreateGraphFromReadFiles(std::unordered_map<unsigned long long, std::pair<std::string, std::string>> &edgeMap, std::unordered_map<unsigned long long, bool> &edgeDirectedMap, std::unordered_map<std::string, T> &nodeFeatMap, std::unordered_map<unsigned long long, double> &edgeWeightMap);
		int compressFile(const std::string &inputFile, const std::string &outputFile) const;
		int decompressFile(const std::string &inputFile, const std::string &outputFile) const;

	public:
		Graph() = default;
		Graph(const T_EdgeSet<T> &edgeSet);
		virtual ~Graph() = default;
		/**
		 * \brief
		 * Function that return the Edge set of the Graph
		 * Note: No Thread Safe
		 *
		 * @returns a list of Edges of the graph
		 *
		 */
		virtual const T_EdgeSet<T> &getEdgeSet() const;
		/**
		 * \brief
		 * Function set the Edge Set of the Graph
		 * Note: No Thread Safe
		 *
		 * @param edgeSet The Edge Set
		 *
		 */
		virtual void setEdgeSet(T_EdgeSet<T> &edgeSet);
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
		virtual void removeEdge(unsigned long long edgeId);
		/**
		 * \brief
		 * Function that return the Node Set of the Graph
		 * Note: No Thread Safe
		 *
		 * @returns a list of Nodes of the graph
		 *
		 */
		virtual const std::set<const Node<T> *> getNodeSet() const;
		/**
		 * \brief
		 * Function that return an Edge with specific ID if Exist in the Graph
		 * Note: No Thread Safe
		 *
		 * @param edgeId The Edge Id to return
		 * @returns the Edge if exist
		 *
		 */
		virtual const std::optional<const Edge<T> *> getEdge(unsigned long long edgeId) const;
		/**
		 * @brief This function generate a list of adjacency matrix with every element of the matrix
		 * contain the node where is directed the link and the Edge corrispondent to the link
		 * Note: No Thread Safe
		 */
		virtual const AdjacencyMatrix<T> getAdjMatrix() const;
		/**
		 * @brief This function finds the subset of given a nodeId
		 * Subset is stored in a map where keys are the hash-id of the node & values is the subset.
		 * @param subset query subset, we want to find target in this subset
		 * @param elem elem that we wish to find in the subset
		 *
		 * @return parent node of elem
		 * Note: No Thread Safe
		 */
		virtual unsigned long long setFind(std::unordered_map<unsigned long long, Subset> *, const unsigned long long elem) const;
		/**
		 * @brief This function modifies the original subset array
		 * such that it the union of two sets a and b
		 * @param subset original subset is modified to obtain union of a & b
		 * @param a parent id of set1
		 * @param b parent id of set2
		 * NOTE: Original subset is no longer available after union.
		 * Note: No Thread Safe
		 */
		virtual void setUnion(std::unordered_map<unsigned long long, Subset> *, const unsigned long long set1, const unsigned long long elem2) const;
		/**
		 * @brief This function finds the eulerian path of a directed graph using hierholzers algorithm
		 *
		 * @return a vector containing nodes in eulerian path
		 * Note: No Thread Safe
		 */
		virtual std::vector<Node<T>> eulerianPath() const;
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
		 * @return a vector containing id of nodes in minimum spanning tree & cost of MST
		 */
		virtual const MstResult prim() const;
		/**
		 * @brief Function runs the boruvka algorithm and returns the minimum spanning tree & cost
		 * if the graph is undirected.
		 * Note: No Thread Safe
		 * @return struct of type MstResult with following fields
		 * success: true if algorithm completed successfully ELSE false
		 * mst: vector containing id of nodes in minimum spanning tree & cost of MST
		 * mstCost: Cost of MST
		 * errorMessage: "" if no error ELSE report the encountered error
		 */
		virtual const MstResult boruvka() const;
		/**
		 * @brief Function runs the kruskal algorithm and returns the minimum spanning tree
		 * if the graph is undirected.
		 * Note: No Thread Safe
		 * @return struct of type MstResult with following fields
		 * success: true if algorithm completed successfully ELSE false
		 * mst: vector containing id of nodes in minimum spanning tree & cost of MST
		 * mstCost: Cost of MST
		 * errorMessage: "" if no error ELSE report the encountered error
		 */
		virtual const MstResult kruskal() const;
		/**
		 * \brief
		 * Function runs the best first search algorithm over the graph
		 * using an evaluation function to decide which adjacent node is
		 * most promising to explore
		 * Note: No Thread Safe
		 *
		 * @param source source node
		 * @param target target node
		 * @returns a struct with a vector of Nodes if target is reachable else ERROR in case
		 * if target is not reachable or there is an error in the computation.
		 *
		 */
		virtual BestFirstSearchResult<T> best_first_search(const Node<T> &source, const Node<T> &target) const;
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
		 * The multithreaded version of breadth_first_search
         * It turns out to be two indepentent functions because of implemntation differences
		 *
		 * @param start Node from where traversing starts
         * @param num_threads number of threads
		 * @returns a vector of Node indicating which Node were visited during the
		 * search.
		 *
		 */
		virtual const std::vector<Node<T>> concurrency_breadth_first_search(const Node<T> &start, size_t num_threads) const;
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
		 * @brief
		 * This function checks if the given set of edges
		 * forms a cycle or not using union-find method.
		 *
		 * @return true if a cycle is detected, else false
		 */
		virtual bool containsCycle(const T_EdgeSet<T> *) const;
		/**
		 * @brief
		 * This function checks if the given Subset
		 * forms a cycle or not using union-find method.
		 *
		 * @return true if a cycle is detected, else false
		 */
		virtual bool containsCycle(const T_EdgeSet<T> *edgeSet, std::unordered_map<unsigned long long, Subset> *) const;

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
		 * @brief This function checks if the graph is connected or not
		 * 	Applicable for Undirected Graph, for Directed Graph use the isStronglyConnectedGraph() function
		 *
		 * @return true if the graph is connected
		 * @return false otherwise
		 */
		virtual bool isConnectedGraph() const;

		/**
		 * @brief This function checks if the graph is strongly connected or not
		 * 	Applicable for Directed Graph, for Undirected Graph use the isConnectedGraph() function
		 *
		 * @return true if the graph is connected
		 * @return false otherwise
		 */
		virtual bool isStronglyConnectedGraph() const;

        /**
		 * @brief This function sort nodes in topological order.
		 * 	Applicable for Directed Acyclic Graph
		 *
		 * @return a struct with a vector of Nodes ordered topologically else ERROR in case
		 * of undirected or cyclic graph
		 */
		virtual TopoSortResult<T> topologicalSort() const;

		/**
		 * @brief This function sort nodes in topological order using kahn's algorithm
		 * 	Applicable for Directed Acyclic Graph
		 *
		 * @return a struct with a vector of Nodes ordered topologically else ERROR in case
		 * of undirected or cyclic graph
		 */
		virtual TopoSortResult<T> kahn() const;

		/**
		* \brief
		* This function performs performs the kosaraju algorthm on the graph to find the strongly connected components.
		*
		* Mathematical definition of the problem:
		* A strongly connected component (SCC) of a directed graph is a maximal strongly connected subgraph.

		* Note: No Thread Safe
		* @return a vector of vector of strongly connected components.
		*/
		virtual SCCResult<T> kosaraju() const;

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
		 * @brief Function runs the Ford-Fulkerson algorithm for some source node and
		 * target node in the graph and returns the maximum flow of the graph
		 *
		 * @param source source vertex
		 * @param target  target vertex
		 * @return double Max-Flow value or -1 in case of error
		 */
		virtual double fordFulkersonMaxFlow(const Node<T> &source, const Node<T> &target) const;

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
		 * @param readNodeFeat Indicates if import also Node Features
		 * @param readEdgeWeight Indicates if import also Edge Weights
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
		virtual PartitionMap<T> partitionGraph(PARTITIONING::PartitionAlgorithm algorithm, unsigned int numberOfPartitions, double param1 = 0.0, double param2 = 0.0, double param3 = 0.0, unsigned int numberOfthreads = std::thread::hardware_concurrency()) const;

		friend std::ostream &operator<<<>(std::ostream &os, const Graph<T> &graph);
		friend std::ostream &operator<<<>(std::ostream &os, const AdjacencyMatrix<T> &adj);
	};

	template <typename T>
	Graph<T>::Graph(const T_EdgeSet<T> &edgeSet)
	{
		for (const auto &edgeSetIt : edgeSet)
		{
			/*
			if (std::find_if(this->edgeSet.begin(), this->edgeSet.end(), [edgeSetIt](const Edge<T> *edge)
							 { return (*edge == *edgeSetIt); }) == this->edgeSet.end())
			{
				this->edgeSet.insert(edgeSetIt);
			}
			*/
			this->edgeSet.insert(edgeSetIt);
		}
	}

	template <typename T>
	const T_EdgeSet<T> &Graph<T>::getEdgeSet() const
	{
		return edgeSet;
	}

	template <typename T>
	void Graph<T>::setEdgeSet(T_EdgeSet<T> &edgeSet)
	{
		this->edgeSet.clear();
		for (const auto &edgeSetIt : edgeSet)
		{
			/*
			if (std::find_if(this->edgeSet.begin(), this->edgeSet.end(), [edgeSetIt](const Edge<T> *edge)
							 { return (*edge == *edgeSetIt); }) == this->edgeSet.end())
			{
				this->edgeSet.insert(edgeSetIt);
			}
			*/
			this->edgeSet.insert(edgeSetIt);
		}
	}

	template <typename T>
	void Graph<T>::addEdge(const Edge<T> *edge)
	{
		/*
		if (std::find_if(edgeSet.begin(), edgeSet.end(), [edge](const Edge<T> *edge_a)
						 { return (*edge == *edge_a); }) == edgeSet.end())
		{
			edgeSet.insert(edge);
		}
		*/
		edgeSet.insert(edge);
	}

	template <typename T>
	void Graph<T>::removeEdge(unsigned long long edgeId)
	{
		auto edgeOpt = Graph<T>::getEdge(edgeId);
		if (edgeOpt.has_value())
		{
			/*
			edgeSet.erase(std::find_if(this->edgeSet.begin(), this->edgeSet.end(), [edgeOpt](const Edge<T> *edge)
									   { return (*(edgeOpt.value()) == *edge); }));
			*/
			edgeSet.erase(edgeSet.find(edgeOpt.value()));
		}
	}

	template <typename T>
	const std::set<const Node<T> *> Graph<T>::getNodeSet() const
	{
		std::set <const Node<T> *> nodeSet;
		for (const auto &edgeSetIt : edgeSet)
		{
			nodeSet.insert(edgeSetIt->getNodePair().first);
			nodeSet.insert(edgeSetIt->getNodePair().second);
		}
		/*
		std::deque<const Node<T> *> nodeSet;
		for (const auto &edge : edgeSet)
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
		*/
		return nodeSet;
	}

	template <typename T>
	const std::optional<const Edge<T> *> Graph<T>::getEdge(unsigned long long edgeId) const
	{
		for (const auto &it : edgeSet)
		{
			if (it->getId() == edgeId)
			{
				return it;
			}
		}

		return std::nullopt;
	}

	template <typename T>
	std::optional<std::pair<std::string, char>> Graph<T>::getExtenstionAndSeparator(InputOutputFormat format) const
	{
		if (format == InputOutputFormat::STANDARD_CSV)
		{
			return std::pair<std::string, char>(".csv", ',');
		}
		else if (format == InputOutputFormat::STANDARD_TSV)
		{
			return std::pair<std::string, char>(".tsv", '\t');
		}
		else
		{
			return std::nullopt;
		}
	}

	template <typename T>
	int Graph<T>::writeToStandardFile(const std::string &workingDir, const std::string &OFileName, bool compress, bool writeNodeFeat, bool writeEdgeWeight, InputOutputFormat format) const
	{
		auto result = getExtenstionAndSeparator(format);
		if (!result)
		{
			std::cerr << "Unknown format\n";
			return -1;
		}
		auto &[extension, separator] = *result;

		std::ofstream ofileGraph;
		std::string completePathToFileGraph = workingDir + "/" + OFileName + extension;
		ofileGraph.open(completePathToFileGraph);
		if (!ofileGraph.is_open())
		{
			// ERROR File Not Open
			return -1;
		}

		for (const auto &edge : edgeSet)
		{
			ofileGraph << edge->getId() << separator
					   << edge->getNodePair().first->getUserId() << separator
					   << edge->getNodePair().second->getUserId() << separator
					   << ((edge->isDirected().has_value() && edge->isDirected().value()) ? 1 : 0)
					   << std::endl;
		}
		ofileGraph.close();

		if (writeNodeFeat)
		{
			std::ofstream ofileNodeFeat;
			std::string completePathToFileNodeFeat = workingDir + "/" + OFileName + "_NodeFeat" + extension;
			ofileNodeFeat.open(completePathToFileNodeFeat);
			if (!ofileNodeFeat.is_open())
			{
				// ERROR File Not Open
				return -1;
			}
			auto nodeSet = getNodeSet();
			for (const auto &node : nodeSet)
			{
				ofileNodeFeat << node->getUserId() << separator << node->getData() << std::endl;
			}
			ofileNodeFeat.close();
		}

		if (writeEdgeWeight)
		{
			std::ofstream ofileEdgeWeight;
			std::string completePathToFileEdgeWeight = workingDir + "/" + OFileName + "_EdgeWeight" + extension;
			ofileEdgeWeight.open(completePathToFileEdgeWeight);
			if (!ofileEdgeWeight.is_open())
			{
				// ERROR File Not Open
				std::cout << "ERROR File Not Open" << std::endl;
				return -1;
			}

			for (const auto &edge : edgeSet)
			{
				ofileEdgeWeight << edge->getId() << separator
								<< (edge->isWeighted().has_value() && edge->isWeighted().value() ? (dynamic_cast<const Weighted *>(edge))->getWeight() : 0.0) << separator
								<< (edge->isWeighted().has_value() && edge->isWeighted().value() ? 1 : 0)
								<< std::endl;
			}
			ofileEdgeWeight.close();
		}
		return 0;
	}

	// This ctype facet classifies ',' and '\t' as whitespace
	struct csv_whitespace : std::ctype<char>
	{
		static const mask *make_table()
		{
			// make a copy of the "C" locale table
			static std::vector<mask> v(classic_table(), classic_table() + table_size);
			v[','] |= space; // comma will be classified as whitespace
			v['\t'] |= space;
			v[' '] &= ~space; // space will not be classified as whitespace
			return &v[0];
		}
		csv_whitespace(std::size_t refs = 0) : ctype(make_table(), false, refs) {}
	};

	template <typename T>
	int Graph<T>::readFromStandardFile(const std::string &workingDir, const std::string &OFileName, bool compress, bool readNodeFeat, bool readEdgeWeight, InputOutputFormat format)
	{
		auto result = getExtenstionAndSeparator(format);
		if (!result)
		{
			std::cerr << "Unknown format\n";
			return -1;
		}
		auto &[extension, separator] = *result;

		std::ifstream ifileGraph;
		std::ifstream ifileNodeFeat;
		std::ifstream ifileEdgeWeight;

		std::unordered_map<unsigned long long, std::pair<std::string, std::string>> edgeMap;
		std::unordered_map<unsigned long long, bool> edgeDirectedMap;
		std::unordered_map<std::string, T> nodeFeatMap;
		std::unordered_map<unsigned long long, double> edgeWeightMap;
		std::string completePathToFileGraph = workingDir + "/" + OFileName + extension;

		ifileGraph.open(completePathToFileGraph);
		if (!ifileGraph.is_open())
		{
			// ERROR File Not Open
			//std::cout << "ERROR File Not Open : " << completePathToFileGraph << std::endl;
			return -1;
		}

		ifileGraph.imbue(std::locale(ifileGraph.getloc(), new csv_whitespace));
		unsigned long long edgeId;
		std::string nodeId1;
		std::string nodeId2;
		bool directed;
		while (ifileGraph >> edgeId >> nodeId1 >> nodeId2 >> directed)
		{ /* loop continually */
			edgeMap[edgeId] = std::pair<std::string, std::string>(nodeId1, nodeId2);
			edgeDirectedMap[edgeId] = directed;
		}
		ifileGraph.close();
		if (compress)
			remove(completePathToFileGraph.c_str());

		if (readNodeFeat)
		{
			std::string completePathToFileNodeFeat = workingDir + "/" + OFileName + "_NodeFeat" + extension;
			ifileNodeFeat.open(completePathToFileNodeFeat);
			if (!ifileNodeFeat.is_open())
			{
				// ERROR File Not Open
				//std::cout << "ERROR File Not Open" << std::endl;
				return -1;
			}
			ifileNodeFeat.imbue(std::locale(ifileGraph.getloc(), new csv_whitespace));
			std::string nodeId;
			T nodeFeat;
			while (ifileNodeFeat >> nodeId >> nodeFeat)
			{
				nodeFeatMap[nodeId] = nodeFeat;
			}
			ifileNodeFeat.close();
			if (compress)
				remove(completePathToFileNodeFeat.c_str());
		}

		if (readEdgeWeight)
		{
			std::string completePathToFileEdgeWeight = workingDir + "/" + OFileName + "_EdgeWeight" + extension;
			ifileEdgeWeight.open(completePathToFileEdgeWeight);
			if (!ifileEdgeWeight.is_open())
			{
				// ERROR File Not Open
				//std::cout << "ERROR File Not Open" << std::endl;
				return -1;
			}
			ifileEdgeWeight.imbue(std::locale(ifileGraph.getloc(), new csv_whitespace));
			unsigned long long edgeId;
			double weight;
			bool weighted;
			while (ifileEdgeWeight >> edgeId >> weight >> weighted)
			{ /* loop continually */
				if (weighted)
				{
					edgeWeightMap[edgeId] = weight;
				}
			}
			ifileEdgeWeight.close();
			if (compress)
				remove(completePathToFileEdgeWeight.c_str());
		}
		recreateGraphFromReadFiles(edgeMap, edgeDirectedMap, nodeFeatMap, edgeWeightMap);
		return 0;
	}

	template <typename T>
	void Graph<T>::recreateGraphFromReadFiles(std::unordered_map<unsigned long long, std::pair<std::string, std::string>> &edgeMap, std::unordered_map<unsigned long long, bool> &edgeDirectedMap, std::unordered_map<std::string, T> &nodeFeatMap, std::unordered_map<unsigned long long, double> &edgeWeightMap)
	{
		std::unordered_map<std::string, Node<T> *> nodeMap;
		for (const auto &edgeIt : edgeMap)
		{
			Node<T> *node1 = nullptr;
			Node<T> *node2 = nullptr;
			if (nodeMap.find(edgeIt.second.first) == nodeMap.end())
			{
				// Create new Node
				T feat;
				if (nodeFeatMap.find(edgeIt.second.first) != nodeFeatMap.end())
				{
					feat = nodeFeatMap.at(edgeIt.second.first);
				}
				node1 = new Node<T>(edgeIt.second.first, feat);
				nodeMap[edgeIt.second.first] = node1;
			}
			else
			{
				node1 = nodeMap.at(edgeIt.second.first);
			}
			if (nodeMap.find(edgeIt.second.second) == nodeMap.end())
			{
				// Create new Node
				T feat;
				if (nodeFeatMap.find(edgeIt.second.second) != nodeFeatMap.end())
				{
					feat = nodeFeatMap.at(edgeIt.second.second);
				}
				node2 = new Node<T>(edgeIt.second.second, feat);
				nodeMap[edgeIt.second.second] = node2;
			}
			else
			{
				node2 = nodeMap.at(edgeIt.second.second);
			}

			if (edgeWeightMap.find(edgeIt.first) != edgeWeightMap.end())
			{
				if (edgeDirectedMap.find(edgeIt.first) != edgeDirectedMap.end() && edgeDirectedMap.at(edgeIt.first))
				{
					auto edge = new DirectedWeightedEdge<T>(edgeIt.first, *node1, *node2, edgeWeightMap.at(edgeIt.first));
					addEdge(edge);
				}
				else
				{
					auto edge = new UndirectedWeightedEdge<T>(edgeIt.first, *node1, *node2, edgeWeightMap.at(edgeIt.first));
					addEdge(edge);
				}
			}
			else
			{
				if (edgeDirectedMap.find(edgeIt.first) != edgeDirectedMap.end() && edgeDirectedMap.at(edgeIt.first))
				{
					auto edge = new DirectedEdge<T>(edgeIt.first, *node1, *node2);
					addEdge(edge);
				}
				else
				{
					auto edge = new UndirectedEdge<T>(edgeIt.first, *node1, *node2);
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
			// printf("Error: Failed to gzopen %s\n", outputFile.c_str());
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
			// printf("Error: Failed to gzopen %s\n", inputFile.c_str());
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
		for (const auto &c : unzippedData)
		{
			ofs << c;
		}
		ofs << std::endl;
		ofs.close();
		gzclose(inFileZ);
		return 0;
	}

	template <typename T>
	unsigned long long Graph<T>::setFind(std::unordered_map<unsigned long long, Subset> *subsets, const unsigned long long nodeId) const
	{
		// find root and make root as parent of i
		// (path compression)
		if ((*subsets)[nodeId].parent != nodeId)
		{
			(*subsets)[nodeId].parent = Graph<T>::setFind(subsets, (*subsets)[nodeId].parent);
		}

		return (*subsets)[nodeId].parent;
	}

	template <typename T>
	void Graph<T>::setUnion(std::unordered_map<unsigned long long, Subset> *subsets, const unsigned long long elem1, const unsigned long long elem2) const
	{
		// if both sets have same parent
		// then there's nothing to be done
		if ((*subsets)[elem1].parent == (*subsets)[elem2].parent)
			return;
		auto elem1Parent = Graph<T>::setFind(subsets, elem1);
		auto elem2Parent = Graph<T>::setFind(subsets, elem2);
		if ((*subsets)[elem1Parent].rank < (*subsets)[elem2Parent].rank)
			(*subsets)[elem1].parent = elem2Parent;
		else if ((*subsets)[elem1Parent].rank > (*subsets)[elem2Parent].rank)
			(*subsets)[elem2].parent = elem1Parent;
		else
		{
			(*subsets)[elem2].parent = elem1Parent;
			(*subsets)[elem1Parent].rank++;
		}
	}

	template <typename T>
	std::vector<Node<T>> Graph<T>::eulerianPath() const
	{
		const auto nodeSet = Graph<T>::getNodeSet();
		auto adj = Graph<T>::getAdjMatrix();
		std::vector<Node<T>> eulerPath;
		std::vector<const Node<T> *> currentPath;
		auto currentNode = *(nodeSet.begin());
		currentPath.push_back(currentNode);
		while (currentPath.size() > 0)
		{
			auto &edges = adj.at(currentNode);
			// we keep removing the edges that
			// have been traversed from the adjacency list
			if (edges.size())
			{
				auto firstEdge = edges.back().second;
				auto nextNodeId = firstEdge->getNodePair().second;
				currentPath.push_back(nextNodeId);
				currentNode = nextNodeId;
				edges.pop_back();
			}
			else
			{
				eulerPath.push_back(*currentNode);
				currentNode = currentPath.back();
				currentPath.pop_back();
			}
		}
		return eulerPath;
	}

	template <typename T>
	const AdjacencyMatrix<T> Graph<T>::getAdjMatrix() const
	{

		AdjacencyMatrix<T> adj;
		auto addElementToAdjMatrix = [&adj](const Node<T> *nodeFrom, const Node<T> *nodeTo, const Edge<T> *edge){
			std::pair<const Node<T> *, const Edge<T> *> elem = {nodeTo, edge};
			adj[nodeFrom].push_back(std::move(elem));
		};
		for (const auto &edgeSetIt : edgeSet)
		{
			if (edgeSetIt->isDirected().has_value() && edgeSetIt->isDirected().value())
			{
				const DirectedEdge<T> *d_edge = dynamic_cast<const DirectedEdge<T> *>(edgeSetIt);
				addElementToAdjMatrix(&(d_edge->getFrom()), &(d_edge->getTo()), d_edge);
			}
			else if (edgeSetIt->isDirected().has_value() && !edgeSetIt->isDirected().value())
			{
				const UndirectedEdge<T> *ud_edge = dynamic_cast<const UndirectedEdge<T> *>(edgeSetIt);
				;
				addElementToAdjMatrix(&(ud_edge->getNode1()), &(ud_edge->getNode2()), ud_edge);
				addElementToAdjMatrix(&(ud_edge->getNode2()), &(ud_edge->getNode1()), ud_edge);
			}
			else
			{ // is a simple edge we cannot create adj matrix
				return adj;
			}
		}
		return adj;
	}

	template <typename T>
	const DijkstraResult Graph<T>::dijkstra(const Node<T> &source, const Node<T> &target) const
	{
		DijkstraResult result;
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
		std::unordered_map<const Node<T> *, double> dist;

		for (const auto &node : nodeSet )
		{
			dist[node] = INF_DOUBLE;
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
				for (const auto &elem : adj.at(currentNode))
				{
					// minimizing distances
					if (elem.second->isWeighted().has_value() && elem.second->isWeighted().value())
					{
						if (elem.second->isDirected().has_value() && elem.second->isDirected().value())
						{
							const DirectedWeightedEdge<T> *dw_edge = dynamic_cast<const DirectedWeightedEdge<T> *>(elem.second);
							if (dw_edge->getWeight() < 0)
							{
								result.errorMessage = ERR_NEGATIVE_WEIGHTED_EDGE;
								return result;
							}
							else if (currentDist + dw_edge->getWeight() < dist[elem.first])
							{
								dist[elem.first] = currentDist + dw_edge->getWeight();
								pq.push(std::make_pair(dist[elem.first], elem.first));
							}
						}
						else if (elem.second->isDirected().has_value() && !elem.second->isDirected().value())
						{
							const UndirectedWeightedEdge<T> *udw_edge = dynamic_cast<const UndirectedWeightedEdge<T> *>(elem.second);
							if (udw_edge->getWeight() < 0)
							{
								result.errorMessage = ERR_NEGATIVE_WEIGHTED_EDGE;
								return result;
							}
							else if (currentDist + udw_edge->getWeight() < dist[elem.first])
							{
								dist[elem.first] = currentDist + udw_edge->getWeight();
								pq.push(std::make_pair(dist[elem.first], elem.first));
							}
						}
						else
						{
							// ERROR it shouldn't never returned ( does not exist a Node Weighted and not Directed/Undirected)
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
		std::unordered_map<const Node<T> *, double> dist, currentDist;
		// n denotes the number of vertices in graph
		auto n = nodeSet.size();
		for (const auto &elem : nodeSet)
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
		for (int i = 0; i < n - 1; ++i)
		{
			auto edgeSet = Graph<T>::getEdgeSet();
			// inner loop for distance updates of
			// each relaxation
			for (const auto &edge : edgeSet)
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
			for (const auto &[key, value] : dist)
			{
				if (currentDist[key] != value)
				{
					flag = false;
					break;
				}
			}
			for (const auto &[key, value] : dist)
			{
				currentDist[key] = value; // update the current distance
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
			for (const auto &edge : edgeSet)
			{
				auto elem = edge->getNodePair();
				auto edge_weight = (dynamic_cast<const Weighted *>(edge))->getWeight();
				if (dist[elem.first] + edge_weight < dist[elem.second])
				{
					result.success = true;
					result.negativeCycle = true;
					result.errorMessage = "";
					return result;
				}
			}
		}

		if (dist[&target] != INF_DOUBLE)
		{
			result.success = true;
			result.errorMessage = "";
			result.negativeCycle = false;
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
		std::unordered_map<std::pair<std::string, std::string>, double, CXXGRAPH::pair_hash> pairwise_dist;
		const auto &nodeSet = Graph<T>::getNodeSet();
		// create a pairwise distance matrix with distance node distances
		// set to inf. Distance of node to itself is set as 0.
		for (const auto &elem1 : nodeSet)
		{
			for (const auto &elem2 : nodeSet)
			{
				auto key = std::make_pair(elem1->getUserId(), elem2->getUserId());
				if (elem1 != elem2)
					pairwise_dist[key] = INF_DOUBLE;
				else
					pairwise_dist[key] = 0.0;
			}
		}

		const auto &edgeSet = Graph<T>::getEdgeSet();
		// update the weights of nodes
		// connected by edges
		for (const auto &edge : edgeSet)
		{
			const auto &elem = edge->getNodePair();
			if (edge->isWeighted().has_value() && edge->isWeighted().value())
			{
				auto edgeWeight = (dynamic_cast<const Weighted *>(edge))->getWeight();
				auto key = std::make_pair(elem.first->getUserId(), elem.second->getUserId());
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

		for (const auto &k : nodeSet)
		{
			// set all vertices as source one by one
			for (const auto &src : nodeSet)
			{
				// iterate through all vertices as destination for the
				// current source
				auto src_k = std::make_pair(src->getUserId(), k->getUserId());
				for (const auto &dst : nodeSet)
				{
					// If vertex k provides a shorter path than
					// src to dst, update the value of
					// pairwise_dist[src_to_dst]
					auto src_dst = std::make_pair(src->getUserId(), dst->getUserId());
					auto k_dst = std::make_pair(k->getUserId(), dst->getUserId());
					if (pairwise_dist[src_dst] > (pairwise_dist[src_k] + pairwise_dist[k_dst]) && (pairwise_dist[k_dst] != INF_DOUBLE && pairwise_dist[src_k] != INF_DOUBLE))
						pairwise_dist[src_dst] = pairwise_dist[src_k] + pairwise_dist[k_dst];
				}
			}
		}

		result.success = true;
		// presense of negative number in the diagonal indicates
		// that that the graph contains a negative cycle
		for (const auto &node : nodeSet)
		{
			auto diag = std::make_pair(node->getUserId(), node->getUserId());
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
	const MstResult Graph<T>::prim() const
	{
		MstResult result;
		result.success = false;
		result.errorMessage = "";
		result.mstCost = INF_DOUBLE;
		if (!isUndirectedGraph())
		{
			result.errorMessage = ERR_DIR_GRAPH;
			return result;
		}
		if (!isConnectedGraph())
		{
			result.errorMessage = ERR_NOT_STRONG_CONNECTED;
			return result;
		}
		auto nodeSet = Graph<T>::getNodeSet();
		auto n = nodeSet.size();
		const AdjacencyMatrix<T> adj = Graph<T>::getAdjMatrix();

		// setting all the distances initially to INF_DOUBLE
		std::unordered_map<const Node<T> *, double> dist;
		for (const auto &elem : adj)
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
		auto source = *(nodeSet.begin());
		pq.push(std::make_pair(0.0, source));
		result.mstCost = 0;
		std::vector<unsigned long long> doneNode;
		// mark source node as done
		// otherwise we get (0, 0) also in mst
		doneNode.push_back(source->getId());
		// stores the parent and corresponding child node
		// of the edges that are part of MST
		std::unordered_map<unsigned long long, std::string> parentNode;
		while (!pq.empty())
		{
			// second element of pair denotes the node / vertex
			const Node<T> *currentNode = pq.top().second;
			auto nodeId = currentNode->getId();
			if (std::find(doneNode.begin(), doneNode.end(), nodeId) == doneNode.end())
			{
				auto pair = std::make_pair(parentNode[nodeId], currentNode->getUserId());
				result.mst.push_back(pair);
				result.mstCost += pq.top().first;
				doneNode.push_back(nodeId);
			}

			pq.pop();
			// for all the reachable vertex from the currently exploring vertex
			// we will try to minimize the distance
			if (adj.find(currentNode) != adj.end())
			{
				for (const auto &elem : adj.at(currentNode))
				{
					// minimizing distances
					if (elem.second->isWeighted().has_value() && elem.second->isWeighted().value())
					{
						const UndirectedWeightedEdge<T> *udw_edge = dynamic_cast<const UndirectedWeightedEdge<T> *>(elem.second);
						if (
							(udw_edge->getWeight() < dist[elem.first]) &&
							(std::find(doneNode.begin(), doneNode.end(), elem.first->getId()) == doneNode.end()))
						{
							dist[elem.first] = udw_edge->getWeight();
							parentNode[elem.first->getId()] = currentNode->getUserId();
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
	const MstResult Graph<T>::boruvka() const
	{
		MstResult result;
		result.success = false;
		result.errorMessage = "";
		result.mstCost = INF_DOUBLE;
		if (!isUndirectedGraph())
		{
			result.errorMessage = ERR_DIR_GRAPH;
			return result;
		}
		const auto nodeSet = Graph<T>::getNodeSet();
		const auto n = nodeSet.size();

		// Use std map for storing n subsets.
		std::unordered_map<unsigned long long, Subset> subsets;

		// Initially there are n different trees.
		// Finally there will be one tree that will be MST
		int numTrees = n;

		// check if all edges are weighted and store the weights
		// in a map whose keys are the edge ids and values are the edge weights
		const auto edgeSet = Graph<T>::getEdgeSet();
		std::unordered_map<unsigned long long, double> edgeWeight;
		for (const auto &edge : edgeSet)
		{
			if (edge->isWeighted().has_value() && edge->isWeighted().value())
				edgeWeight[edge->getId()] = (dynamic_cast<const Weighted *>(edge))->getWeight();
			else
			{
				// No Weighted Edge
				result.errorMessage = ERR_NO_WEIGHTED_EDGE;
				return result;
			}
		}

		for (const auto &node : nodeSet)
		{
			Subset set{node->getId(), 0};
			subsets[node->getId()] = set;
		}

		result.mstCost = 0; // we will store the cost here
		// exit when only 1 tree i.e. mst
		while (numTrees > 1)
		{
			// Everytime initialize cheapest map
			// It stores index of the cheapest edge of subset.
			std::unordered_map<unsigned long long, unsigned long long> cheapest;
			for (const auto &node : nodeSet)
				cheapest[node->getId()] = INT_MAX;

			// Traverse through all edges and update
			// cheapest of every component
			for (const auto &edge : edgeSet)
			{
				auto elem = edge->getNodePair();
				auto edgeId = edge->getId();
				// Find sets of two corners of current edge
				auto set1 = Graph<T>::setFind(&subsets, elem.first->getId());
				auto set2 = Graph<T>::setFind(&subsets, elem.second->getId());

				// If two corners of current edge belong to
				// same set, ignore current edge
				if (set1 == set2)
					continue;

				// Else check if current edge is closer to previous
				// cheapest edges of set1 and set2
				if (cheapest[set1] == INT_MAX ||
					edgeWeight[cheapest[set1]] > edgeWeight[edgeId])
					cheapest[set1] = edgeId;

				if (cheapest[set2] == INT_MAX ||
					edgeWeight[cheapest[set2]] > edgeWeight[edgeId])
					cheapest[set2] = edgeId;
			}

			// iterate over all the vertices and add picked
			// cheapest edges to MST
			for (const auto &[nodeId, edgeId] : cheapest)
			{
				// Check if cheapest for current set exists
				if (edgeId != INT_MAX)
				{
					auto cheapestNode = Graph<T>::getEdge(edgeId).value()->getNodePair();
					auto set1 = Graph<T>::setFind(&subsets, cheapestNode.first->getId());
					auto set2 = Graph<T>::setFind(&subsets, cheapestNode.second->getId());
					if (set1 == set2)
						continue;
					result.mstCost += edgeWeight[edgeId];
					auto newEdgeMST = std::make_pair(cheapestNode.first->getUserId(), cheapestNode.second->getUserId());
					result.mst.push_back(newEdgeMST);
					// take union of set1 and set2 and decrease number of trees
					Graph<T>::setUnion(&subsets, set1, set2);
					numTrees--;
				}
			}
		}
		result.success = true;
		return result;
	}

	template <typename T>
	const MstResult Graph<T>::kruskal() const
	{
		MstResult result;
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

		// check if all edges are weighted and store the weights
		// in a map whose keys are the edge ids and values are the edge weights
		auto edgeSet = Graph<T>::getEdgeSet();
		std::priority_queue<std::pair<double, const Edge<T> *>, std::vector<std::pair<double, const Edge<T> *>>,
							std::greater<std::pair<double, const Edge<T> *>>>
			sortedEdges;
		for (const auto &edge : edgeSet)
		{
			if (edge->isWeighted().has_value() && edge->isWeighted().value())
			{
				auto weight = (dynamic_cast<const Weighted *>(edge))->getWeight();
				sortedEdges.push(std::make_pair(weight, edge));
			}
			else
			{
				// No Weighted Edge
				result.errorMessage = ERR_NO_WEIGHTED_EDGE;
				return result;
			}
		}

		std::unordered_map<unsigned long long, Subset> subset;

		for (const auto &node : nodeSet)
		{
			Subset set{node->getId(), 0};
			subset[node->getId()] = set;
		}
		result.mstCost = 0;
		while ((!sortedEdges.empty()) && (result.mst.size() < n))
		{
			auto [edgeWeight, cheapestEdge] = sortedEdges.top();
			sortedEdges.pop();
			auto &[first, second] = cheapestEdge->getNodePair();
			auto set1 = Graph<T>::setFind(&subset, first->getId());
			auto set2 = Graph<T>::setFind(&subset, second->getId());
			if (set1 != set2)
			{
				result.mst.push_back(std::make_pair(first->getUserId(), second->getUserId()));
				result.mstCost += edgeWeight;
			}
			Graph<T>::setUnion(&subset, set1, set2);
		}
		result.success = true;
		return result;
	}

	template <typename T>
	BestFirstSearchResult<T> Graph<T>::best_first_search(const Node<T> &source, const Node<T> &target) const
	{
		BestFirstSearchResult<T> result;
		auto &nodeSet = Graph<T>::getNodeSet();
		using pq_type = std::pair<double, const Node<T> *>;

		if(std::find(nodeSet.begin(), nodeSet.end(), &source) == nodeSet.end())
		{
			result.errorMessage = ERR_SOURCE_NODE_NOT_IN_GRAPH;
			return result;
		}

		if(std::find(nodeSet.begin(), nodeSet.end(), &target) == nodeSet.end())
		{
			result.errorMessage = ERR_TARGET_NODE_NOT_IN_GRAPH;
			return result;
		}

		auto adj = Graph<T>::getAdjMatrix();
		std::priority_queue<pq_type, std::vector<pq_type>, std::greater<pq_type>> pq;

		std::vector<Node<T>> visited;
		visited.push_back(source);
		pq.push(std::make_pair(static_cast<T>(0), &source));

		while (!pq.empty())
		{
			const Node<T> *currentNode = pq.top().second;
			pq.pop();
			result.nodesInBestSearchOrder.push_back(*currentNode);

			if (*currentNode == target)
			{
				break;
			}
			if (adj.find(currentNode) != adj.end())
			{
				for (const auto &elem : adj.at(currentNode))
				{
					if (elem.second->isWeighted().has_value())
					{
						if (elem.second->isDirected().has_value())
						{
							const DirectedWeightedEdge<T> *dw_edge = static_cast<const DirectedWeightedEdge<T> *>(elem.second);
							if (std::find(visited.begin(), visited.end(), *(elem.first)) == visited.end())
							{
								visited.push_back(*(elem.first));
								pq.push(std::make_pair(dw_edge->getWeight(), elem.first));
							}
						}
						else
						{
							const UndirectedWeightedEdge<T> *dw_edge = static_cast<const UndirectedWeightedEdge<T> *>(elem.second);
							if (std::find(visited.begin(), visited.end(), *(elem.first)) == visited.end())
							{
								visited.push_back(*(elem.first));
								pq.push(std::make_pair(dw_edge->getWeight(), elem.first));
							}
						}
					}
					else
					{
						result.errorMessage = ERR_NO_WEIGHTED_EDGE;
						result.nodesInBestSearchOrder.clear();
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
		auto &nodeSet = Graph<T>::getNodeSet();
		// check is exist node in the graph
		if (std::find(nodeSet.begin(), nodeSet.end(), &start) == nodeSet.end())
		{
			return visited;
		}
		const AdjacencyMatrix<T> &adj = Graph<T>::getAdjMatrix();
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
				for (const auto &elem : adj.at(node))
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
	const std::vector<Node<T>> Graph<T>::concurrency_breadth_first_search(const Node<T> &start, size_t num_threads) const
	{
		std::vector<Node<T>> bfs_result;
		// check is exist node in the graph
		auto &nodeSet = Graph<T>::getNodeSet();
		if (std::find(nodeSet.begin(), nodeSet.end(), &start) == nodeSet.end())
		{
			return bfs_result;
		}

        std::unordered_map<const Node<T> *, int> node_to_index;
        for (const auto &node : nodeSet)
        {
            node_to_index[node] = node_to_index.size();
        }
        std::vector<int> visited(nodeSet.size(), 0);

        // parameter limitations
        if (num_threads <= 0)
        {
            std::cout << "Error: number of threads should be greater than 0" << std::endl;
            num_threads = 2;
        }

		const AdjacencyMatrix<T> &adj = Graph<T>::getAdjMatrix();
		// vector that stores vertices to be visit
		std::vector<const Node<T> *> level_tracker, next_level_tracker;
        level_tracker.reserve(static_cast<int>(1.0 *nodeSet.size()));
        next_level_tracker.reserve(static_cast<int>(1.0 * nodeSet.size()));

		// mark the starting node as visited
        visited[node_to_index[&start]] = 1;
		level_tracker.push_back(&start);

        // a worker is assigned a small part of tasks for each time
        // assignments of tasks in current level and updates of tasks in next level are inclusive
        std::mutex tracker_mutex;
        std::mutex next_tracker_mutex;
        std::atomic<int> assigned_tasks = 0;
        int num_tasks = 1;
        // unit of task assignment, which mean assign block_size tasks to a worker each time
        int block_size = 1;
        int level = 1;

        auto extract_tasks = [&level_tracker, &tracker_mutex, &assigned_tasks, &num_tasks, &block_size] () -> std::pair<int,int>
        {
            /*
            std::lock_guard<std::mutex> tracker_guard(tracker_mutex);
            int task_block_size = std::min(num_tasks - assigned_tasks, block_size);
            std::pair<int,int> task_block{assigned_tasks, assigned_tasks + task_block_size};
            assigned_tasks += task_block_size;
            return task_block;
            */
            int start = assigned_tasks.fetch_add(block_size);
            int end = std::min(num_tasks, start + block_size);
            return {start, end};
        };

        auto submit_result = [&next_level_tracker, &next_tracker_mutex] (std::vector<const Node<T> *> &submission) -> void
        {
            std::lock_guard<std::mutex> tracker_guard(next_tracker_mutex);
            next_level_tracker.insert(std::end(next_level_tracker), std::begin(submission), std::end(submission));
        };

        // worker thread sleep until it begin to search nodes of next level
        std::mutex next_level_mutex;
        std::condition_variable next_level_cond;
        std::atomic<int> waiting_workers = 0;

        auto bfs_worker = [&] () -> void
        {
            // algorithm is not done
            while (!level_tracker.empty())
            {
                // search for nodes in a level is not done
                std::vector<const Node<T> *> local_tracker;
                while (1)
                {
                    auto [start_index, end_index] = extract_tasks();
                    if (start_index >= end_index)
                    {
                        break;
                    }

                    for (int i = start_index; i < end_index; ++i)
                    {
                        if (adj.count(level_tracker[i]))
                        {
                            for (const auto &elem : adj.at(level_tracker[i]))
                            {
                                int index = node_to_index[elem.first];
                                if (visited[index] == 0)
                                {
                                    visited[index] = 1;
                                    local_tracker.push_back(elem.first);
                                }
                            }
                        }
                    }
                }

                // submit local result to global result
                if (!local_tracker.empty())
                {
                    submit_result(local_tracker);
                }

                // last worker need to do preparation for the next iteration
                int cur_level = level;
                if (num_threads == 1 + waiting_workers.fetch_add(1))
                {
                    swap(level_tracker, next_level_tracker);
                    next_level_tracker.clear();

                    // adjust block_size according to number of nodes in next level
                    block_size = 4;
                    if (level_tracker.size() <= num_threads * 4)
                    {
                        block_size = std::max(1, static_cast<int>(std::ceil(static_cast<double>(level_tracker.size()) / num_threads)));
                    }
                    else if (level_tracker.size() >= num_threads * 64)
                    {
                        block_size = 16;
                    }

                    num_tasks = level_tracker.size();
                    waiting_workers = 0;
                    assigned_tasks = 0;
                    level = level + 1;
                    next_level_cond.notify_all();
                }
                else
                {
                    // not to wait if last worker reachs last statement before notify all or even further
                    std::unique_lock<std::mutex> next_level_lock(next_level_mutex);
                    next_level_cond.wait(next_level_lock,
                                        [&level, cur_level] () { return level != cur_level;});
                }
            }
        };

        std::vector<std::thread> workers;
        for (int i = 0; i < num_threads - 1; ++i)
        {
            workers.emplace_back(std::thread(bfs_worker));
        }
        bfs_worker();

        for (auto &worker : workers)
        {
            if (worker.joinable())
            {
                worker.join();
            }
        }

        for (const auto &visited_node : nodeSet)
        {
            if (visited[node_to_index[visited_node]] != 0)
            {
                bfs_result.push_back(*visited_node);
            }
        }

		return bfs_result;
	}
	template <typename T>
	const std::vector<Node<T>> Graph<T>::depth_first_search(const Node<T> &start) const
	{
		// vector to keep track of visited nodes
		std::vector<Node<T>> visited;
		auto nodeSet = Graph<T>::getNodeSet();
		// check is exist node in the graph
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
				for (const auto &x : adj.at(&node))
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
		std::unordered_map<unsigned long long, nodeStates> state;
		for (const auto &node : nodeSet)
		{
			state[node->getId()] = not_visited;
		}
		int stateCounter = 0;

		// Start visiting each node.
		for (const auto &node : nodeSet)
		{
			// If a node is not visited, only then check for presence of cycle.
			// There is no need to check for presence of cycle for a visited
			// node as it has already been checked for presence of cycle.
			if (state[node->getId()] == not_visited)
			{
				// Check for cycle.
				std::function<bool(AdjacencyMatrix<T> &, std::unordered_map<unsigned long long, nodeStates> &, const Node<T> *)> isCyclicDFSHelper;
				isCyclicDFSHelper = [this, &isCyclicDFSHelper](AdjacencyMatrix<T> &adjMatrix, std::unordered_map<unsigned long long, nodeStates> &states, const Node<T> *node)
				{
					// Add node "in_stack" state.
					states[node->getId()] = in_stack;

					// If the node has children, then recursively visit all children of the
					// node.
					auto const it = adjMatrix.find(node);
					if (it != adjMatrix.end())
					{
						for (const auto &child : it->second)
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
	bool Graph<T>::containsCycle(const T_EdgeSet<T> *edgeSet) const
	{
		std::unordered_map<unsigned long long, Subset> subset;
		// initialize the subset parent and rank values
		for (const auto &edge : *edgeSet)
		{
			auto &[first, second] = edge->getNodePair();
			std::vector<unsigned long long> nodeId(2);
			nodeId.push_back(first->getId());
			nodeId.push_back(second->getId());
			for (const auto &id : nodeId)
			{
				auto nodeExists = [id](const auto &it)
				{ return (id == (it.second).parent); };

				if (std::find_if(subset.begin(), subset.end(), nodeExists) == subset.end())
				{
					Subset set;
					set.parent = id;
					set.rank = 0;
					subset[id] = set;
				}
			}
		}
		return Graph<T>::containsCycle(edgeSet, &subset);
	}

	template <typename T>
	bool Graph<T>::containsCycle(const T_EdgeSet<T> *edgeSet, std::unordered_map<unsigned long long, Subset> *subset) const
	{
		for (const auto &edge : *edgeSet)
		{
			auto &[first, second] = edge->getNodePair();
			auto set1 = Graph<T>::setFind(subset, first->getId());
			auto set2 = Graph<T>::setFind(subset, second->getId());
			if (set1 == set2)
				return true;
			Graph<T>::setUnion(subset, set1, set2);
		}
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

		std::unordered_map<unsigned long, unsigned int> indegree;
		for (const auto &node : nodeSet)
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
		for (const auto &node : nodeSet)
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
				for (const auto &child : it->second)
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
		for (const auto &edge : edgeSet)
		{
			if (!(edge->isDirected().has_value() && edge->isDirected().value()))
			{
				// Found Undirected Edge
				return false;
			}
		}
		// No Undirected Edge
		return true;
	}

	template <typename T>
	bool Graph<T>::isUndirectedGraph() const
	{
		auto edgeSet = Graph<T>::getEdgeSet();
		for (const auto &edge : edgeSet)
		{
			if ((edge->isDirected().has_value() && edge->isDirected().value()))
			{
				// Found Directed Edge
				return false;
			}
		}
		// No Directed Edge
		return true;
	}

	template <typename T>
	bool Graph<T>::isConnectedGraph() const
	{
		if (!isUndirectedGraph())
		{
			return false;
		}
		else
		{
			auto nodeSet = getNodeSet();
			auto adjMatrix = getAdjMatrix();
			// created visited map
			std::unordered_map<unsigned long, bool> visited;
			for (const auto &node : nodeSet)
			{
				visited[node->getId()] = false;
			}
			std::function<void(const Node<T> *)> dfs_helper = [this, &adjMatrix, &visited, &dfs_helper](const Node<T> *source)
			{
				// mark the vertex visited
				visited[source->getId()] = true;

				// travel the neighbors
				for (int i = 0; i < adjMatrix[source].size(); i++)
				{
					const Node<T> *neighbor = adjMatrix[source].at(i).first;
					if (visited[neighbor->getId()] == false)
					{
						// make recursive call from neighbor
						dfs_helper(neighbor);
					}
				}
			};
			// call dfs_helper for the first node
			dfs_helper(*(nodeSet.begin()));

			// check if all the nodes are visited
			for (const auto &node : nodeSet)
			{
				if (visited[node->getId()] == false)
				{
					return false;
				}
			}
			return true;
		}
	}

	template <typename T>
	bool Graph<T>::isStronglyConnectedGraph() const
	{
		if (!isDirectedGraph())
		{
			return false;
		}
		else
		{
			auto nodeSet = getNodeSet();
			auto adjMatrix = getAdjMatrix();
			for (const auto &start_node : nodeSet)
			{
				// created visited map
				std::unordered_map<unsigned long, bool> visited;
				for (const auto &node : nodeSet)
				{
					visited[node->getId()] = false;
				}
				std::function<void(const Node<T> *)> dfs_helper = [this, &adjMatrix, &visited, &dfs_helper](const Node<T> *source)
				{
					// mark the vertex visited
					visited[source->getId()] = true;

					// travel the neighbors
					for (int i = 0; i < adjMatrix[source].size(); i++)
					{
						const Node<T> *neighbor = adjMatrix[source].at(i).first;
						if (visited[neighbor->getId()] == false)
						{
							// make recursive call from neighbor
							dfs_helper(neighbor);
						}
					}
				};
				// call dfs_helper for the first node
				dfs_helper(start_node);

				// check if all the nodes are visited
				for (const auto &node : nodeSet)
				{
					if (visited[node->getId()] == false)
					{
						return false;
					}
				}
			}
			return true;
		}
	}

    template <typename T>
	TopoSortResult<T> Graph<T>::topologicalSort() const
    {
        TopoSortResult<T> result;
        result.success = false;

        if (!isDirectedGraph())
		{
            result.errorMessage = ERR_UNDIR_GRAPH;
			return result;
		}
        else if (isCyclicDirectedGraphBFS())
        {
            result.errorMessage = ERR_CYCLIC_GRAPH;
            return result;
        }
        else
        {
            const auto &adjMatrix = getAdjMatrix();
            const auto &nodeSet = getNodeSet();
            std::unordered_map<const Node<T> *, bool> visited;

            std::function<void(const Node<T> *)> postorder_helper = [&postorder_helper, &adjMatrix, &visited, &result] (const Node<T> *curNode)
            {
                visited[curNode] = true;

                if (adjMatrix.find(curNode) != adjMatrix.end())
                {
                    for (const auto &edge : adjMatrix.at(curNode))
                    {
                        const auto &nextNode = edge.first;
                        if (false == visited[nextNode])
                        {
                            postorder_helper(nextNode);
                        }
                    }
                }

                result.nodesInTopoOrder.push_back(*curNode);
            };

            int numNodes = adjMatrix.size();
            result.nodesInTopoOrder.reserve(numNodes);

            for (const auto &node : nodeSet)
            {
                if (false == visited[node])
                {
                    postorder_helper(node);
                }
            }

            result.success = true;
            std::reverse(result.nodesInTopoOrder.begin(), result.nodesInTopoOrder.end());
            return result;
        }
    }

	template <typename T>
<<<<<<< HEAD
        SCCResult<T> Graph<T>::kosaraju() const
=======
	TopoSortResult<T> Graph<T>::kahn() const
	{
		TopoSortResult<T> result;

		if (!isDirectedGraph())
		{
			result.errorMessage = ERR_UNDIR_GRAPH;
			return result;
		}
		else
		{
			const auto adjMatrix = Graph<T>::getAdjMatrix();
			const auto nodeSet = Graph<T>::getNodeSet();
			result.nodesInTopoOrder.reserve(adjMatrix.size());

			std::unordered_map<size_t, unsigned int> indegree;
			for (const auto &node : nodeSet)
			{
				indegree[node->getId()] = 0;
			}
			for (const auto &list : adjMatrix)
			{
				auto children = list.second;
				for (const auto &child : children)
				{
					indegree[std::get<0>(child)->getId()]++;
				}
			}

			std::queue<const Node<T>*> topologicalOrder;

			for (const auto &node : nodeSet)
			{
				if (!indegree[node->getId()])
				{
					topologicalOrder.emplace(node);
				}
			}

			size_t visited = 0;
			while(!topologicalOrder.empty())
			{
				const Node<T> *currentNode = topologicalOrder.front();
				topologicalOrder.pop();
				result.nodesInTopoOrder.push_back(*currentNode);

				if (adjMatrix.find(currentNode) != adjMatrix.end())
				{
					for (const auto &child : adjMatrix.at(currentNode))
					{
						if (--indegree[std::get<0>(child)->getId()] == 0)
						{
							topologicalOrder.emplace(std::get<0>(child));
						}
					}
				}
				visited++;

			}

			if (visited != nodeSet.size())
			{
				result.errorMessage = ERR_CYCLIC_GRAPH;
				result.nodesInTopoOrder.clear();
				return result;
			}

			result.success = true;
			return result;
		}
	}

	template <typename T>
	std::vector<std::vector<Node<T>>> Graph<T>::kosaraju() const
>>>>>>> 9c05b354549f97b5c29431dbae605d4664348fd0
	{
                SCCResult<T> result;
                result.success = false;

		if (!isDirectedGraph())
		{
                    result.errorMessage = ERR_UNDIR_GRAPH;
                    return result;
		}
		else
		{
			auto nodeSet = getNodeSet();
			auto adjMatrix = getAdjMatrix();
			// created visited map
			std::unordered_map<unsigned long, bool> visited;
			for (const auto &node : nodeSet)
			{
				visited[node->getId()] = false;
			}

			std::stack<const Node<T> *> st;
			std::function<void(const Node<T> *)> dfs_helper = [this, &adjMatrix, &visited, &dfs_helper, &st](const Node<T> *source)
			{
				// mark the vertex visited
				visited[source->getId()] = true;

				// travel the neighbors
				for (int i = 0; i < adjMatrix[source].size(); i++)
				{
					const Node<T> *neighbor = adjMatrix[source].at(i).first;
					if (visited[neighbor->getId()] == false)
					{
						// make recursive call from neighbor
						dfs_helper(neighbor);
					}
				}

				st.push(source);
			};

			for (const auto &node : nodeSet)
			{
				if (visited[node->getId()] == false)
				{
					dfs_helper(node);
				}
			}

			//construct the transpose of the given graph
			AdjacencyMatrix<T> rev;
			auto addElementToAdjMatrix = [&rev](const Node<T> *nodeFrom, const Node<T> *nodeTo, const Edge<T> *edge){
				std::pair<const Node<T> *, const Edge<T> *> elem = {nodeTo, edge};
				rev[nodeFrom].push_back(std::move(elem));
			};
			for (const auto &edgeSetIt : edgeSet)
			{
				const DirectedEdge<T> *d_edge = dynamic_cast<const DirectedEdge<T> *>(edgeSetIt);
				//Add the reverse edge to the reverse adjacency matrix
				addElementToAdjMatrix(&(d_edge->getTo()), &(d_edge->getFrom()), d_edge);
			}

			visited.clear();

			std::function<void(const Node<T> *, std::vector<Node<T>> &)> dfs_helper1 = [this, &rev, &visited, &dfs_helper1](const Node<T> *source, std::vector<Node<T>> &comp)
			{
				// mark the vertex visited
				visited[source->getId()] = true;
				//Add the current vertex to the strongly connected component
				comp.push_back(*source);

				// travel the neighbors
				for (int i = 0; i < rev[source].size(); i++)
				{
					const Node<T> *neighbor = rev[source].at(i).first;
					if (visited[neighbor->getId()] == false)
					{
						// make recursive call from neighbor
						dfs_helper1(neighbor, comp);
					}
				}
			};

			while(st.size()!=0){
				auto rem = st.top();
				st.pop();
				if(visited[rem->getId()] == false){
					std::vector<Node<T>> comp;
					dfs_helper1(rem, comp);
					result.stronglyConnectedComps.push_back(comp);
				}
			}
                        
                        result.success = true;
			return result;
		}
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
		std::unordered_map<const Node<T> *, std::pair<long, const Node<T> *>> dist;

		// Initialize all distances as infinite (INF)
		for (const auto &node : nodeSet)
		{
			dist[&(*node)].first = std::numeric_limits<long>::max();
		}

		// Create buckets B[].
		// B[i] keep vertex of distance label i
		std::deque<const Node<T> *> B[maxWeight * V + 1];

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
			for (const auto &i : adj[u])
			{
				auto v = i.first;
				int weight = 0;
				if (i.second->isWeighted().has_value() && i.second->isWeighted().value())
				{
					if (i.second->isDirected().has_value() && i.second->isDirected().value())
					{
						const DirectedWeightedEdge<T> *dw_edge = dynamic_cast<const DirectedWeightedEdge<T> *>(i.second);
						weight = dw_edge->getWeight();
					}
					else if (i.second->isDirected().has_value() && !i.second->isDirected().value())
					{
						const UndirectedWeightedEdge<T> *udw_edge = dynamic_cast<const UndirectedWeightedEdge<T> *>(i.second);
						weight = udw_edge->getWeight();
					}
					else
					{
						// ERROR it shouldn't never returned ( does not exist a Node Weighted and not Directed/Undirected)
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
		for (const auto &dist_i : dist)
		{
			result.minDistanceMap[dist_i.first->getId()] = dist_i.second.first;
		}
		result.success = true;

		return result;
	}

	template <typename T>
	double Graph<T>::fordFulkersonMaxFlow(const Node<T> &source, const Node<T> &target) const
	{
		if (!isDirectedGraph())
		{
			return -1;
		}
		double maxFlow = 0;
		std::unordered_map<const Node<T> *, const Node<T> *> parent;
		std::map<const Node<T> *, std::map<const Node<T> *, double>> weightMap;
		// build weight map
		auto edgeSet = this->getEdgeSet();
		for (const auto &edge : edgeSet)
		{
			// The Edge are all Directed at this point because is checked at the start
			if (edge->isWeighted().value_or(false))
			{
				const DirectedWeightedEdge<T> *dw_edge = dynamic_cast<const DirectedWeightedEdge<T> *>(edge);
				weightMap[edge->getNodePair().first][edge->getNodePair().second] = dw_edge->getWeight();
			}
			else
			{
				weightMap[edge->getNodePair().first][edge->getNodePair().second] = 0; // No Weighted Edge are assumed to be 0 weigthed
			}
		}

		auto bfs_helper = [this, &source, &target, &parent, &weightMap]() -> bool
		{
			std::unordered_map<const Node<T> *, bool> visited;
			std::queue<const Node<T> *> queue;
			queue.push(&source);
			visited[&source] = true;
			parent[&source] = nullptr;
			while (!queue.empty())
			{
				auto u = queue.front();
				queue.pop();
				for (auto &v : weightMap[u])
				{
					if (!visited[v.first] && v.second > 0)
					{
						queue.push(v.first);
						visited[v.first] = true;
						parent[v.first] = u;
					}
				}
			}

			return (visited[&target]);
		};
		// Updating the residual values of edges
		while (bfs_helper())
		{
			double pathFlow = std::numeric_limits<double>::max();
			for (auto v = &target; v != &source; v = parent[v])
			{
				auto u = parent[v];
				pathFlow = std::min(pathFlow, weightMap[u][v]);
			}
			for (auto v = &target; v != &source; v = parent[v])
			{
				auto u = parent[v];
				weightMap[u][v] -= pathFlow;
				weightMap[v][u] += pathFlow;
			}
			// Adding the path flows
			maxFlow += pathFlow;
		}

		return maxFlow;
	}

	template <typename T>
	const std::vector<Node<T>> Graph<T>::graph_slicing(const Node<T> &start) const
	{
		std::vector<Node<T>> result;

		auto nodeSet = Graph<T>::getNodeSet();
		// check if start node in the graph
		if (std::find(nodeSet.begin(), nodeSet.end(), &start) == nodeSet.end())
		{
			return result;
		}
		std::vector<Node<T>> C = Graph<T>::depth_first_search(start);
		std::deque<const Node<T> *> C1; // complement of C i.e. nodeSet - C
		for (auto const &node : nodeSet)
		{
			// from the set of all nodes, remove nodes that exist in C
			if (std::find_if(C.begin(), C.end(), [node](const Node<T> nodeC)
							 { return (*node == nodeC); }) == C.end())
				C1.push_back(node);
		}

		// For all nodes in C', apply DFS
		//  and get the list of reachable nodes and store in M
		std::vector<Node<T>> M;
		for (auto const &node : C1)
		{
			std::vector<Node<T>> reachableNodes = Graph<T>::depth_first_search(*node);
			M.insert(M.end(), reachableNodes.begin(), reachableNodes.end());
		}
		// removes nodes from C that are reachable from M.
		for (const auto &nodeC : C)
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
		result = writeToStandardFile(workingDir, OFileName, compress, writeNodeFeat, writeEdgeWeight, format);
		if (result == 0 && compress)
		{
			auto _compress = [this, &workingDir, &OFileName, &writeNodeFeat, &writeEdgeWeight](const std::string &extension)
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
				auto result = _compress(".csv");
			}
			else if (format == InputOutputFormat::STANDARD_TSV)
			{
				auto result = _compress(".tsv");
			}
			else
			{
				// OUTPUT FORMAT NOT RECOGNIZED
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
				// INPUT FORMAT NOT RECOGNIZED
				result = -1;
			}
		}
		if (result == 0)
		{
			result = readFromStandardFile(workingDir, OFileName, compress, readNodeFeat, readEdgeWeight, format);
		}
		return result;
	}

	template <typename T>
	PartitionMap<T> Graph<T>::partitionGraph(PARTITIONING::PartitionAlgorithm algorithm, unsigned int numberOfPartitions, double param1, double param2, double param3, unsigned int numberOfThreads) const
	{
		PartitionMap<T> partitionMap;
		PARTITIONING::Globals globals(numberOfPartitions, algorithm, param1, param2, param3, numberOfThreads);
		const T_EdgeSet<T> & edgeSet = getEdgeSet();
		globals.edgeCardinality = edgeSet.size();
		globals.vertexCardinality = this->getNodeSet().size();
		PARTITIONING::Partitioner<T> partitioner(&edgeSet, globals);
		PARTITIONING::CoordinatedPartitionState<T> partitionState = partitioner.performCoordinatedPartition();
		partitionMap = partitionState.getPartitionMap();
		return partitionMap;
	}

	template <typename T>
	std::ostream &operator<<(std::ostream &os, const Graph<T> &graph)
	{
		os << "Graph:\n";
		auto edgeList = graph.getEdgeSet();
		auto it = edgeList.begin();
		for (it; it != edgeList.end(); ++it)
		{
			if (!(*it)->isDirected().has_value() && !(*it)->isWeighted().has_value())
			{
				// Edge Case
				os << **it << "\n";
			}
			else if (((*it)->isDirected().has_value() && (*it)->isDirected().value()) && ((*it)->isWeighted().has_value() && (*it)->isWeighted().value()))
			{
				os << dynamic_cast<const DirectedWeightedEdge<T> &>(*it) << "\n";
			}
			else if (((*it)->isDirected().has_value() && (*it)->isDirected().value()) && !((*it)->isWeighted().has_value() && (*it)->isWeighted().value()))
			{
				os << dynamic_cast<const DirectedEdge<T> &>(*it) << "\n";
			}
			else if (!(it->isDirected().has_value() && it->isDirected().value()) && (it->isWeighted().has_value() && it->isWeighted().value()))
			{
				os << dynamic_cast<const UndirectedWeightedEdge<T> &>(*it) << "\n";
			}
			else if (!(it->isDirected().has_value() && it->isDirected().value()) && !(it->isWeighted().has_value() && it->isWeighted().value()))
			{
				os << dynamic_cast<const UndirectedEdge<T> &>(*it) << "\n";
			}
			else
			{
				os << *it << "\n";
			}
		}
		return os;
	}

	template <typename T>
	std::ostream &operator<<(std::ostream &os, const AdjacencyMatrix<T> &adj)
	{
		os << "Adjacency Matrix:\n";
		unsigned long max_column = 0;
		for (const auto &it : adj)
		{
			if (it.second.size() > max_column)
			{
				max_column = it.second.size();
			}
		}
		if (max_column == 0)
		{
			os << "ERROR in Print\n";
			return os;
		}
		else
		{
			os << "|--|";
			for (int i = 0; i < max_column; ++i)
			{
				os << "-----|";
			}
			os << "\n";
			for (const auto &it : adj)
			{
				os << "|N" << it.first->getId() << "|";
				for (const auto &it2 : it.second)
				{
					os << "N" << it2.first->getId() << ",E" << it2.second->getId() << "|";
				}
				os << "\n|--|";
				for (int i = 0; i < max_column; ++i)
				{
					os << "-----|";
				}
				os << "\n";
			}
		}
		return os;
	}

} // namespace CXXGRAPH
#endif // __CXXGRAPH_GRAPH_H__
