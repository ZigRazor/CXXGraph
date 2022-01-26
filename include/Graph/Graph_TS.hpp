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

#ifndef __CXXGRAPH_GRAPH_TS_H__
#define __CXXGRAPH_GRAPH_TS_H__

#pragma once

#include "Graph/Graph.hpp"

namespace CXXGRAPH
{

    /// Class that implement the Thread Safe Graph.
    template <typename T>
    class Graph_TS : public Graph<T>, public ThreadSafe
    {
    public:
        Graph_TS() = default;
        Graph_TS(const std::list<const Edge<T> *> &edgeSet);
        Graph_TS(const Graph<T> &graph);
        ~Graph_TS() = default;
        /**
 		* \brief
 		* Function that return the Edge set of the Graph
		* Note: Thread Safe
		*
 		* @returns a list of Edges of the graph
 		*
 		*/
        const std::list<const Edge<T> *> &getEdgeSet() const override;
        /**
 		* \brief
 		* Function set the Edge Set of the Graph
		* Note: Thread Safe
 		*
 		* @param edgeSet The Edge Set
 		*
 		*/
        void setEdgeSet(std::list<const Edge<T> *> &edgeSet) override;
        /**
 		* \brief
 		* Function add an Edge to the Graph Edge Set
		* Note: Thread Safe
 		*
 		* @param edge The Edge to insert
 		*
 		*/
        void addEdge(const Edge<T> *edge) override;
        /**
 		* \brief
 		* Function remove an Edge from the Graph Edge Set
		* Note: Thread Safe
 		*
 		* @param edgeId The Edge Id to remove
 		*
 		*/
        void removeEdge(unsigned long long edgeId) override;
        /**
 		* \brief
 		* Function that return the Node Set of the Graph
		* Note: Thread Safe
 		*
 		* @returns a list of Nodes of the graph
 		*
 		*/
        const std::list<const Node<T> *> getNodeSet() const override;
        /**
 		* \brief
 		* Function that return an Edge with specific ID if Exist in the Graph
		* Note: Thread Safe
 		*
		* @param edgeId The Edge Id to return
 		* @returns the Edge if exist
 		*
 		*/
        const std::optional<const Edge<T> *> getEdge(unsigned long long edgeId) const override;
        /**
		* @brief This function generate a list of adjacency matrix with every element of the matrix
		* contain the node where is directed the link and the Edge corrispondent to the link
		* Note: Thread Safe
		*/
        const AdjacencyMatrix<T> getAdjMatrix() const override;
        /**
 		* @brief Function runs the dijkstra algorithm for some source node and
 		* target node in the graph and returns the shortest distance of target
 		* from the source.
		* Note: Thread Safe
 		*
		* @param source source vertex
 		* @param target target vertex
 		*
 		* @return shortest distance if target is reachable from source else ERROR in
 		* case if target is not reachable from source or there is error in the computation.
 		*/
        const DijkstraResult dijkstra(const Node<T> &source, const Node<T> &target) const override;
	/**
 		* @brief Function runs the bellmanford algorithm for some source node and
 		* target node in the graph and returns the shortest distance of target
 		* from the source if there is no negative cycle in the graph.
		* Note: Thread Safe
 		*
		* @param source source vertex
 		* @param target target vertex
 		*
 		* @return shortest distance if target is reachable from source else ERROR in
 		* case if target is not reachable from source or there is negative cycle or
		* there is error in the computation.
 		*/
	const BellmanFordResult bellmanford(const Node<T> &source, const Node<T> &target) const override;
	/**
 		* @brief Function runs the floyd-Warshall algorithm for every node
 		* in the graph and returns the shortest distance of each node from
 		* another node if there is no negative cycle in the graph.
		* Note: Thread Safe
 		*
 		* @return shortest distance if any node is reachable from other node else ERROR in
 		* case if target is not reachable from source or there is negative cycle or
		* there is error in the computation.
 		*/
	const FWResult floydWarshall() const override;
        /**
 		* \brief
 		* Function performs the breadth first search algorithm over the graph
		* Note: Thread Safe
 		*
 		* @param start Node from where traversing starts
 		* @returns a vector of Node indicating which Node were visited during the
 		* search.
 		*
 		*/
        const std::vector<Node<T>> breadth_first_search(const Node<T> &start) const override;
        /**
 		* \brief
 		* Function performs the depth first search algorithm over the graph
		* Note: Thread Safe
 		*
 		* @param start Node from where traversing starts
 		* @returns a vector of Node indicating which Node were visited during the
 		* search.
 		*
 		*/
        const std::vector<Node<T>> depth_first_search(const Node<T> &start) const override;

        /**
		* \brief
     	* This function uses DFS to check for cycle in the graph.
     	* Pay Attention, this function work only with directed Graph
		* Note: Thread Safe
     	*
     	* @return true if a cycle is detected, else false. ( false is returned also if the graph in indirected)
     	*/
        bool isCyclicDirectedGraphDFS() const override;

        /**
		* \brief
     	* This function uses BFS to check for cycle in the graph.
     	* Pay Attention, this function work only with directed Graph
		* Note: Thread Safe
     	*
     	* @return true if a cycle is detected, else false. ( false is returned also if the graph in indirected)
     	*/
        bool isCyclicDirectedGraphBFS() const override;

        /**
     	* \brief
     	* This function checks if a graph is directed
		* Note: Thread Safe
     	*
     	* @return true if the graph is directed, else false.
     	*/
        bool isDirectedGraph() const override;

        /**
     	* \brief
     	* This function write the graph in an output file
		* Note: Thread Safe
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
		* Note: Thread Safe
 		*
		* @param source source vertex
		* @param maxWeight maximum weight of the edge
 		*
 		* @return shortest distance for all nodes reachable from source else ERROR in
 		* case there is error in the computation.
 		*/
        const DialResult dial(const Node<T> &source, int maxWeight) const override;

        /**
     	* \brief
     	* This function write the graph in an output file
		* Note: Thread Safe
     	*
		* @param format The Output format of the file
		* @param workingDir The path to the directory in which is placed the Output file
		* @param OFileName The Output File Name ( )
		* @param compress Indicates if the Output will be compressed ( Pay Attention if compress flag is true, not compressed files will be deleted [ #48 ] )
		* @param writeNodeFeat Indicates if export also Node Features
		* @param writeEdgeWeight Indicates if export also Edge Weights
     	* @return 0 if all OK, else return a negative value
     	*/
        int writeToFile(InputOutputFormat format = InputOutputFormat::STANDARD_CSV, const std::string &workingDir = ".", const std::string &OFileName = "graph", bool compress = false, bool writeNodeFeat = false, bool writeEdgeWeight = false) const override;

        /**
     	* \brief
     	* This function read the graph from an input file
		* Note: Thread Safe
     	*
		* @param format The Input format of the file
		* @param workingDir The path to the directory in which is placed the Input file
		* @param OFileName The Input File Name ( )
		* @param compress Indicates if the Input is compressed
		* @param readNodeFeat Indicates if import also Node Features
		* @param readEdgeWeight Indicates if import also Edge Weights
     	* @return 0 if all OK, else return a negative value
     	*/
        int readFromFile(InputOutputFormat format = InputOutputFormat::STANDARD_CSV, const std::string &workingDir = ".", const std::string &OFileName = "graph", bool compress = false, bool readNodeFeat = false, bool readEdgeWeight = false) override;

        /**
     	* \brief
     	* This function partition a graph in a set of partitions
		* Note: Thread Safe
     	*
		* @param algorithm The partition algorithm
		* @param numberOfPartition The number of partitions
		* @return The partiton Map of the partitioned graph
     	*/
        PartitionMap<T> partitionGraph(PARTITIONING::PartitionAlgorithm algorithm, unsigned int numberOfPartitions,double param1 = 0.0,double param2 = 0.0,double param3 = 0.0,unsigned int numberOfthreads = std::thread::hardware_concurrency()) const override;
    };

    template <typename T>
    Graph_TS<T>::Graph_TS(const std::list<const Edge<T> *> &edgeSet) : Graph<T>(edgeSet), ThreadSafe() {}

    template <typename T>
    Graph_TS<T>::Graph_TS(const Graph<T> &graph) : Graph<T>(graph), ThreadSafe() {}

    template <typename T>
    const std::list<const Edge<T> *> &Graph_TS<T>::getEdgeSet() const
    {
        std::lock_guard<std::mutex> lock(mutex);
        return Graph<T>::getEdgeSet();
    }

    template <typename T>
    void Graph_TS<T>::setEdgeSet(std::list<const Edge<T> *> &edgeSet)
    {
        getLock();
        Graph<T>::setEdgeSet(edgeSet);
        releaseLock();
    }

    template <typename T>
    void Graph_TS<T>::addEdge(const Edge<T> *edge)
    {
        getLock();
        Graph<T>::addEdge(edge);
        releaseLock();
    }

    template <typename T>
    void Graph_TS<T>::removeEdge(unsigned long long edgeId)
    {
        getLock();
        Graph<T>::removeEdge(edgeId);
        releaseLock();
    }

    template <typename T>
    const std::list<const Node<T> *> Graph_TS<T>::getNodeSet() const
    {
        getLock();
        auto ns = Graph<T>::getNodeSet();
        releaseLock();
        return ns;
    }

    template <typename T>
    const std::optional<const Edge<T> *> Graph_TS<T>::getEdge(unsigned long long edgeId) const
    {
        getLock();
        auto e = Graph<T>::getEdge(edgeId);
        releaseLock();
        return e;
    }

    template <typename T>
    const AdjacencyMatrix<T> Graph_TS<T>::getAdjMatrix() const
    {
        getLock();
        auto adjm = Graph<T>::getAdjMatrix();
        releaseLock();
        return adjm;
    }

    template <typename T>
    const DijkstraResult Graph_TS<T>::dijkstra(const Node<T> &source, const Node<T> &target) const
    {
        getLock();
        auto dij = Graph<T>::dijkstra(source, target);
        releaseLock();
        return dij;
    }
	
    template <typename T>
    const BellmanFordResult Graph_TS<T>::bellmanford(const Node<T> &source, const Node<T> &target) const
    {
        getLock();
        auto bellford = Graph<T>::bellmanford(source, target);
        releaseLock();
        return bellford;
    }
	
    template <typename T>
    const FWResult Graph_TS<T>::floydWarshall() const
    {
        getLock();
        auto fw = Graph<T>::floydWarshall();
        releaseLock();
        return fw;
    }
	
    template <typename T>
    const std::vector<Node<T>> Graph_TS<T>::breadth_first_search(const Node<T> &start) const
    {
        getLock();
        auto bfs = Graph<T>::breadth_first_search(start);
        releaseLock();
        return bfs;
    }

    template <typename T>
    const std::vector<Node<T>> Graph_TS<T>::depth_first_search(const Node<T> &start) const
    {
        getLock();
        auto dfs = Graph<T>::depth_first_search(start);
        releaseLock();
        return dfs;
    }

    template <typename T>
    bool Graph_TS<T>::isCyclicDirectedGraphDFS() const
    {
        getLock();
        auto result = Graph<T>::isCyclicDirectedGraphDFS();
        releaseLock();
        return result;
    }

    template <typename T>
    bool Graph_TS<T>::isCyclicDirectedGraphBFS() const
    {
        getLock();
        auto result = Graph<T>::isCyclicDirectedGraphBFS();
        releaseLock();
        return result;
    }

    template <typename T>
    bool Graph_TS<T>::isDirectedGraph() const
    {
        getLock();
        auto result = Graph<T>::isDirectedGraph();
        releaseLock();
        return result;
    }

    template <typename T>
    const DialResult Graph_TS<T>::dial(const Node<T> &source, int maxWeight) const
    {
        getLock();
        auto dial = Graph<T>::dial(source, maxWeight);
        releaseLock();
        return dial;
    }

    template <typename T>
    int Graph_TS<T>::writeToFile(InputOutputFormat format, const std::string &workingDir, const std::string &OFileName, bool compress, bool writeNodeFeat, bool writeEdgeWeight) const
    {
        getLock();
        auto result = Graph<T>::writeToFile(format, workingDir, OFileName, compress, writeNodeFeat, writeEdgeWeight);
        releaseLock();
        return result;
    }

    template <typename T>
    int Graph_TS<T>::readFromFile(InputOutputFormat format, const std::string &workingDir, const std::string &OFileName, bool compress, bool readNodeFeat, bool readEdgeWeight)
    {
        getLock();
        auto result = Graph<T>::readFromFile(format, workingDir, OFileName, compress, readNodeFeat, readEdgeWeight);
        releaseLock();
        return result;
    }

    template <typename T>
    PartitionMap<T> Graph_TS<T>::partitionGraph(PARTITIONING::PartitionAlgorithm algorithm, unsigned int numberOfPartitions,double param1,double param2,double param3,unsigned int numberOfthreads) const
    {
        getLock();
        auto partitions = Graph<T>::partitionGraph(algorithm, numberOfPartitions, param1, param2, param3, numberOfthreads);
        releaseLock();
        return partitions;
    }
}
#endif // __CXXGRAPH_GRAPH_TS_H__
