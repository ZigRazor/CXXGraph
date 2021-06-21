#ifndef __CXXGRAPH_H__
#define __CXXGRAPH_H__

#pragma once

#include <utility>
#include <set>
#include <map>
#include <optional>
#include <iostream>
#include <limits>
#include <queue>
#include <string>
#include <functional>

namespace CXXGRAPH
{
	//STRING ERROR CONST EXPRESSION
	constexpr char ERR_NO_DIR_OR_UNDIR_EDGE[] = "Edge are neither Directed neither Undirected";
	constexpr char ERR_NO_WEIGHTED_EDGE[] = "Edge are not Weighted";
	constexpr char ERR_DIJ_TARGET_NODE_NOT_REACHABLE[] = "Target Node not Reachable";
	constexpr char ERR_DIJ_TARGET_NODE_NOT_IN_GRAPH[] = "Target Node not inside Graph";
	constexpr char ERR_DIJ_SOURCE_NODE_NOT_IN_GRAPH[] = "Source Node not inside Graph";
	///////////////////////////////
	constexpr double INF_DOUBLE = std::numeric_limits<double>::max();
	template <typename T>
	class Node;
	template <typename T>
	class Edge;
	template <typename T>
	class DirectedEdge;
	template <typename T>
	class UndirectedEdge;
	template <typename T>
	class DirectedWeightedEdge;
	template <typename T>
	class UndirectedWeightedEdge;
	template <typename T>
	class Graph;

	class Weighted;

	template <typename T>
	using AdjacencyMatrix = std::map<const Node<T> *, std::vector<std::pair<const Node<T> *, const Edge<T> *>>>;

	template <typename T>
	std::ostream &operator<<(std::ostream &o, const Node<T> &node);
	template <typename T>
	std::ostream &operator<<(std::ostream &o, const Edge<T> &edge);
	template <typename T>
	std::ostream &operator<<(std::ostream &o, const DirectedEdge<T> &edge);
	template <typename T>
	std::ostream &operator<<(std::ostream &o, const UndirectedEdge<T> &edge);
	template <typename T>
	std::ostream &operator<<(std::ostream &o, const DirectedWeightedEdge<T> &edge);
	template <typename T>
	std::ostream &operator<<(std::ostream &o, const UndirectedWeightedEdge<T> &edge);
	template <typename T>
	std::ostream &operator<<(std::ostream &o, const Graph<T> &graph);
	template <typename T>
	std::ostream &operator<<(std::ostream &o, const AdjacencyMatrix<T> &adj);

	typedef struct DijkstraResult_struct
	{
		bool success;			  // TRUE if the function does not return error, FALSE otherwise
		std::string errorMessage; //message of error
		double result;			  //result (valid only if success is TRUE)
	} DijkstraResult;

	template <typename T>
	class Node
	{
	private:
		unsigned long id;
		T data;

	public:
		Node(const unsigned long id, const T &data);
		~Node() = default;
		const unsigned long &getId() const;
		const T &getData() const;
		//operator
		bool operator==(const Node<T> &b) const;
		bool operator<(const Node<T> &b) const;
		friend std::ostream &operator<<<>(std::ostream &os, const Node<T> &node);
	};

	template <typename T>
	Node<T>::Node(const unsigned long id, const T &data)
	{
		this->id = id;
		this->data = data;
	}

	template <typename T>
	const unsigned long &Node<T>::getId() const
	{
		return id;
	}

	template <typename T>
	const T &Node<T>::getData() const
	{
		return data;
	}

	template <typename T>
	bool Node<T>::operator==(const Node<T> &b) const
	{
		return (this->id == b.id && this->data == b.data);
	}

	template <typename T>
	bool Node<T>::operator<(const Node<T> &b) const
	{
		return (this->id < b.id);
	}

	class Weighted
	{
	private:
		double weight;

	public:
		Weighted();
		Weighted(const double weight);
		virtual ~Weighted() = default;
		double getWeight() const;
		void setWeight(const double weight);
	};

	inline Weighted::Weighted() //inline because the implementation of non-template function in header file
	{
		weight = 0.0;
	}

	inline Weighted::Weighted(const double weight) //inline because the implementation of non-template function in header file
	{
		this->weight = weight;
	}

	inline double Weighted::getWeight() const //inline because the implementation of non-template function in header file
	{
		return weight;
	}

	inline void Weighted::setWeight(const double weight) //inline because the implementation of non-template function in header file
	{
		this->weight = weight;
	}

	template <typename T>
	class Edge
	{
	private:
		unsigned long id;
		std::pair<const Node<T> *, const Node<T> *> nodePair;

	public:
		Edge(const unsigned long id, const Node<T> &node1, const Node<T> &node2);
		Edge(const unsigned long id, const std::pair<const Node<T> *, const Node<T> *> &nodepair);
		virtual ~Edge() = default;
		const unsigned long &getId() const;
		const std::pair<const Node<T> *, const Node<T> *> &getNodePair() const;
		virtual const std::optional<bool> isDirected() const;
		virtual const std::optional<bool> isWeighted() const;
		//operator
		virtual bool operator==(const Edge<T> &b) const;
		bool operator<(const Edge<T> &b) const;
		//operator DirectedEdge<T>() const { return DirectedEdge<T>(id, nodePair); }
		//operator UndirectedEdge<T>() const { return UndirectedEdge<T>(id, nodePair); }

		friend std::ostream &operator<<<>(std::ostream &os, const Edge<T> &edge);
	};

	template <typename T>
	Edge<T>::Edge(const unsigned long id, const Node<T> &node1, const Node<T> &node2) : nodePair(&node1, &node2)
	{
		this->id = id;
	}

	template <typename T>
	Edge<T>::Edge(const unsigned long id, const std::pair<const Node<T> *, const Node<T> *> &nodepair) : nodePair(nodepair)
	{
		this->id = id;
	}

	template <typename T>
	const unsigned long &Edge<T>::getId() const
	{
		return id;
	}

	template <typename T>
	const std::pair<const Node<T> *, const Node<T> *> &Edge<T>::getNodePair() const
	{
		return nodePair;
	}

	template <typename T>
	const std::optional<bool> Edge<T>::isDirected() const
	{
		return std::nullopt;
	}

	template <typename T>
	const std::optional<bool> Edge<T>::isWeighted() const
	{
		return std::nullopt;
	}

	template <typename T>
	bool Edge<T>::operator==(const Edge<T> &b) const
	{
		return (this->id == b.id && this->nodePair == b.nodePair);
	}

	template <typename T>
	bool Edge<T>::operator<(const Edge<T> &b) const
	{
		return (this->id < b.id);
	}

	template <typename T>
	class DirectedEdge : public Edge<T>
	{
	public:
		DirectedEdge(const unsigned long id, const Node<T> &node1, const Node<T> &node2);
		DirectedEdge(const unsigned long id, const std::pair<const Node<T> *, const Node<T> *> &nodepair);
		DirectedEdge(const Edge<T> &edge);
		virtual ~DirectedEdge() = default;
		const Node<T> &getFrom() const;
		const Node<T> &getTo() const;
		const std::optional<bool> isDirected() const override;
		virtual const std::optional<bool> isWeighted() const override;
		//operator
		explicit operator UndirectedEdge<T>() const { return UndirectedEdge<T>(Edge<T>::getId(), Edge<T>::getNodePair()); }

		friend std::ostream &operator<<<>(std::ostream &os, const DirectedEdge<T> &edge);
	};

	template <typename T>
	DirectedEdge<T>::DirectedEdge(const unsigned long id, const Node<T> &node1, const Node<T> &node2) : Edge<T>(id, node1, node2)
	{
	}

	template <typename T>
	DirectedEdge<T>::DirectedEdge(const unsigned long id, const std::pair<const Node<T> *, const Node<T> *> &nodepair) : Edge<T>(id, nodepair)
	{
	}

	template <typename T>
	DirectedEdge<T>::DirectedEdge(const Edge<T> &edge) : DirectedEdge(edge.getId(), *(edge.getNodePair().first), *(edge.getNodePair().second))
	{
	}

	template <typename T>
	const Node<T> &DirectedEdge<T>::getFrom() const
	{
		return *(Edge<T>::getNodePair().first);
	}

	template <typename T>
	const Node<T> &DirectedEdge<T>::getTo() const
	{
		return *(Edge<T>::getNodePair().second);
	}

	template <typename T>
	const std::optional<bool> DirectedEdge<T>::isDirected() const
	{
		return true;
	}

	template <typename T>
	const std::optional<bool> DirectedEdge<T>::isWeighted() const
	{
		return false;
	}

	template <typename T>
	class UndirectedEdge : public Edge<T>
	{
	public:
		UndirectedEdge(const unsigned long id, const Node<T> &node1, const Node<T> &node2);
		UndirectedEdge(const unsigned long id, const std::pair<const Node<T> *, const Node<T> *> &nodepair);
		UndirectedEdge(const Edge<T> &edge);
		virtual ~UndirectedEdge() = default;
		const Node<T> &getNode1() const;
		const Node<T> &getNode2() const;
		const std::optional<bool> isDirected() const override;
		const std::optional<bool> isWeighted() const override;
		//operator
		explicit operator DirectedEdge<T>() const { return DirectedEdge<T>(Edge<T>::getId(), Edge<T>::getNodePair()); }

		friend std::ostream &operator<<<>(std::ostream &os, const UndirectedEdge<T> &edge);
	};

	template <typename T>
	UndirectedEdge<T>::UndirectedEdge(const unsigned long id, const Node<T> &node1, const Node<T> &node2) : Edge<T>(id, node1, node2)
	{
	}

	template <typename T>
	UndirectedEdge<T>::UndirectedEdge(const unsigned long id, const std::pair<const Node<T> *, const Node<T> *> &nodepair) : Edge<T>(id, nodepair)
	{
	}

	template <typename T>
	UndirectedEdge<T>::UndirectedEdge(const Edge<T> &edge) : UndirectedEdge(edge.getId(), *(edge.getNodePair().first), *(edge.getNodePair().second))
	{
	}

	template <typename T>
	const Node<T> &UndirectedEdge<T>::getNode1() const
	{
		return *(Edge<T>::getNodePair().first);
	}

	template <typename T>
	const Node<T> &UndirectedEdge<T>::getNode2() const
	{
		return *(Edge<T>::getNodePair().second);
	}

	template <typename T>
	const std::optional<bool> UndirectedEdge<T>::isDirected() const
	{
		return false;
	}

	template <typename T>
	const std::optional<bool> UndirectedEdge<T>::isWeighted() const
	{
		return false;
	}

	template <typename T>
	class DirectedWeightedEdge : public DirectedEdge<T>, public Weighted
	{
	public:
		DirectedWeightedEdge(const unsigned long id, const Node<T> &node1, const Node<T> &node2, const double weight);
		DirectedWeightedEdge(const unsigned long id, const std::pair<const Node<T> *, const Node<T> *> &nodepair, const double weight);
		DirectedWeightedEdge(const DirectedEdge<T> &edge, const double weight);
		DirectedWeightedEdge(const Edge<T> &edge, const double weight);
		DirectedWeightedEdge(const DirectedEdge<T> &edge);
		DirectedWeightedEdge(const Edge<T> &edge);
		DirectedWeightedEdge(const UndirectedWeightedEdge<T> &edge);
		virtual ~DirectedWeightedEdge() = default;
		const std::optional<bool> isWeighted() const override;
		//operator
		explicit operator UndirectedWeightedEdge<T>() const { return UndirectedWeightedEdge<T>(Edge<T>::getId(), Edge<T>::getNodePair(), Weighted::getWeight()); }

		friend std::ostream &operator<<<>(std::ostream &os, const DirectedWeightedEdge<T> &edge);
	};

	template <typename T>
	DirectedWeightedEdge<T>::DirectedWeightedEdge(const unsigned long id, const Node<T> &node1, const Node<T> &node2, const double weight) : DirectedEdge<T>(id, node1, node2), Weighted(weight)
	{
	}

	template <typename T>
	DirectedWeightedEdge<T>::DirectedWeightedEdge(const unsigned long id, const std::pair<const Node<T> *, const Node<T> *> &nodepair, const double weight) : DirectedEdge<T>(id, nodepair), Weighted(weight)
	{
	}

	template <typename T>
	DirectedWeightedEdge<T>::DirectedWeightedEdge(const DirectedEdge<T> &edge, const double weight) : DirectedEdge<T>(edge), Weighted(weight)
	{
	}

	template <typename T>
	DirectedWeightedEdge<T>::DirectedWeightedEdge(const Edge<T> &edge, const double weight) : DirectedEdge<T>(edge), Weighted(weight)
	{
	}

	template <typename T>
	DirectedWeightedEdge<T>::DirectedWeightedEdge(const DirectedEdge<T> &edge) : DirectedEdge<T>(edge), Weighted()
	{
	}

	template <typename T>
	DirectedWeightedEdge<T>::DirectedWeightedEdge(const Edge<T> &edge) : DirectedEdge<T>(edge), Weighted()
	{
	}

	template <typename T>
	DirectedWeightedEdge<T>::DirectedWeightedEdge(const UndirectedWeightedEdge<T> &edge) : DirectedEdge<T>(edge), Weighted(edge.getWeight())
	{
	}

	template <typename T>
	const std::optional<bool> DirectedWeightedEdge<T>::isWeighted() const
	{
		return true;
	}

	template <typename T>
	class UndirectedWeightedEdge : public UndirectedEdge<T>, public Weighted
	{
	public:
		UndirectedWeightedEdge(const unsigned long id, const Node<T> &node1, const Node<T> &node2, const double weight);
		UndirectedWeightedEdge(const unsigned long id, const std::pair<const Node<T> *, const Node<T> *> &nodepair, const double weight);
		UndirectedWeightedEdge(const UndirectedEdge<T> &edge, const double weight);
		UndirectedWeightedEdge(const Edge<T> &edge, const double weight);
		UndirectedWeightedEdge(const UndirectedEdge<T> &edge);
		UndirectedWeightedEdge(const Edge<T> &edge);
		UndirectedWeightedEdge(const DirectedWeightedEdge<T> &edge);
		virtual ~UndirectedWeightedEdge() = default;
		const std::optional<bool> isWeighted() const override;
		//operator
		explicit operator DirectedWeightedEdge<T>() const { return DirectedWeightedEdge<T>(Edge<T>::getId(), Edge<T>::getNodePair(), Weighted::getWeight()); }

		friend std::ostream &operator<<<>(std::ostream &os, const UndirectedWeightedEdge<T> &edge);
	};

	template <typename T>
	UndirectedWeightedEdge<T>::UndirectedWeightedEdge(const unsigned long id, const Node<T> &node1, const Node<T> &node2, const double weight) : UndirectedEdge<T>(id, node1, node2), Weighted(weight)
	{
	}

	template <typename T>
	UndirectedWeightedEdge<T>::UndirectedWeightedEdge(const unsigned long id, const std::pair<const Node<T> *, const Node<T> *> &nodepair, const double weight) : UndirectedEdge<T>(id, nodepair), Weighted(weight)
	{
	}

	template <typename T>
	UndirectedWeightedEdge<T>::UndirectedWeightedEdge(const UndirectedEdge<T> &edge, const double weight) : UndirectedEdge<T>(edge), Weighted(weight)
	{
	}

	template <typename T>
	UndirectedWeightedEdge<T>::UndirectedWeightedEdge(const Edge<T> &edge, const double weight) : UndirectedEdge<T>(edge), Weighted(weight)
	{
	}

	template <typename T>
	UndirectedWeightedEdge<T>::UndirectedWeightedEdge(const UndirectedEdge<T> &edge) : UndirectedEdge<T>(edge), Weighted()
	{
	}

	template <typename T>
	UndirectedWeightedEdge<T>::UndirectedWeightedEdge(const Edge<T> &edge) : UndirectedEdge<T>(edge), Weighted()
	{
	}

	template <typename T>
	UndirectedWeightedEdge<T>::UndirectedWeightedEdge(const DirectedWeightedEdge<T> &edge) : UndirectedEdge<T>(edge), Weighted(edge.getWeight())
	{
	}

	template <typename T>
	const std::optional<bool> UndirectedWeightedEdge<T>::isWeighted() const
	{
		return true;
	}

	template <typename T>
	class Graph
	{
	private:
		std::set<const Edge<T> *> edgeSet;
		void addElementToAdjMatrix(AdjacencyMatrix<T> &adjMatrix, const Node<T> *nodeFrom, const Node<T> *nodeTo, const Edge<T> *edge) const;

	public:
		Graph() = default;
		Graph(const std::set<const Edge<T> *> &edgeSet);
		~Graph() = default;
		const std::set<const Edge<T> *> &getEdgeSet() const;
		void setEdgeSet(std::set<const Edge<T> *> &edgeSet);
		void addEdge(const Edge<T> &edge);
		void removeEdge(unsigned long edgeId);
		const std::set<const Node<T> *> getNodeSet() const;
		const std::optional<const Edge<T> *> getEdge(unsigned long edgeId) const;
		/*This function generate a list of adjacency matrix with every element of the matrix 
		***contain the node where is directed the link and the Edge corrispondent to the link
		*/
		const AdjacencyMatrix<T> getAdjMatrix() const;
		/**
 		* @brief Function runs the dijkstra algorithm for some source node and
 		* target node in the graph and returns the shortest distance of target
 		* from the source.
 		*
		* @param source source vertex
 		* @param target target vertex
 		*
 		* @return shortest distance if target is reachable from source else ERROR in
 		* case if target is not reachable from source or there is error in the computation.
 		*/
		const DijkstraResult dijkstra(const Node<T> &source, const Node<T> &target) const;
		/**
 		* \brief
 		* Function performs the breadth first search algorithm over the graph
 		*
 		* @param start Node from where traversing starts
 		* @returns a vector of Node indicating which Node were visited during the
 		* search.
 		*
 		*/
		const std::vector<Node<T>> breadth_first_search(const Node<T> &start) const;
		/**
 		* \brief
 		* Function performs the depth first search algorithm over the graph
 		*
 		* @param start Node from where traversing starts
 		* @returns a vector of Node indicating which Node were visited during the
 		* search.
 		*
 		*/
		const std::vector<Node<T>> depth_first_search(const Node<T> &start) const;

		/** 
		* \brief
     	* This function uses DFS to check for cycle in the graph.
     	* Pay Attention, this function work only with directed Graph
     	* 
     	* @return true if a cycle is detected, else false. ( false is returned also if the graph in indirected)
     	*/
		const bool isCyclicDirectedGraphDFS() const;
		/**
     	* \brief
     	* This function checks if a graph is directed
     	* 
     	* @return true if the graph is directed, else false.
     	*/
		const bool isDirectedGraph() const;

		friend std::ostream &operator<<<>(std::ostream &os, const Graph<T> &graph);
		friend std::ostream &operator<<<>(std::ostream &os, const AdjacencyMatrix<T> &adj);
	};

	template <typename T>
	Graph<T>::Graph(const std::set<const Edge<T> *> &edgeSet)
	{
		this->edgeSet = edgeSet;
	}

	template <typename T>
	const std::set<const Edge<T> *> &Graph<T>::getEdgeSet() const
	{
		return edgeSet;
	}

	template <typename T>
	void Graph<T>::setEdgeSet(std::set<const Edge<T> *> &edgeSet)
	{
		this->edgeSet = edgeSet;
	}

	template <typename T>
	void Graph<T>::addEdge(const Edge<T> &edge)
	{
		edgeSet.insert(&edge);
	}

	template <typename T>
	void Graph<T>::removeEdge(unsigned long edgeId)
	{
		auto edgeOpt = getEdge(edgeId);
		if (edgeOpt.has_value())
		{
			edgeSet.erase(edgeSet.find(edgeOpt.value()));
		}
	}

	template <typename T>
	const std::set<const Node<T> *> Graph<T>::getNodeSet() const
	{
		std::set<const Node<T> *> nodeSet;
		for (auto edge : edgeSet)
		{
			nodeSet.insert(edge->getNodePair().first);
			nodeSet.insert(edge->getNodePair().second);
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
		auto nodeSet = getNodeSet();
		if (nodeSet.find(&source) == nodeSet.end())
		{ // check if source node exist in the graph
			result.errorMessage = ERR_DIJ_SOURCE_NODE_NOT_IN_GRAPH;
			return result;
		}
		if (nodeSet.find(&target) == nodeSet.end())
		{ // check if target node exist in the graph
			result.errorMessage = ERR_DIJ_TARGET_NODE_NOT_IN_GRAPH;
			return result;
		}
		const AdjacencyMatrix<T> adj = getAdjMatrix();
		/// n denotes the number of vertices in graph
		int n = adj.size();

		/// setting all the distances initially to INF_DOUBLE
		std::map<const Node<T> *, double> dist;

		for (auto elem : adj)
		{
			dist[elem.first] = INF_DOUBLE;
		}

		/// creating a min heap using priority queue
		/// first element of pair contains the distance
		/// second element of pair contains the vertex
		std::priority_queue<std::pair<double, const Node<T> *>, std::vector<std::pair<double, const Node<T> *>>,
							std::greater<std::pair<double, const Node<T> *>>>
			pq;

		/// pushing the source vertex 's' with 0 distance in min heap
		pq.push(std::make_pair(0.0, &source));

		/// marking the distance of source as 0
		dist[&source] = 0;

		while (!pq.empty())
		{
			/// second element of pair denotes the node / vertex
			const Node<T> *currentNode = pq.top().second;

			/// first element of pair denotes the distance
			double currentDist = pq.top().first;

			pq.pop();

			/// for all the reachable vertex from the currently exploring vertex
			/// we will try to minimize the distance
			if (adj.find(currentNode) != adj.end())
			{
				for (std::pair<const Node<T> *, const Edge<T> *> elem : adj.at(currentNode))
				{
					/// minimizing distances
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
					{ // No Weighted Edge
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
		result.errorMessage = ERR_DIJ_TARGET_NODE_NOT_REACHABLE;
		result.result = -1;
		return result;
	}

	template <typename T>
	const std::vector<Node<T>> Graph<T>::breadth_first_search(const Node<T> &start) const
	{
		/// vector to keep track of visited nodes
		std::vector<Node<T>> visited;
		auto nodeSet = getNodeSet();
		if (nodeSet.find(&start) == nodeSet.end()) //check is exist node in the graph
		{
			return visited;
		}
		const AdjacencyMatrix<T> adj = getAdjMatrix();
		/// queue that stores vertices that need to be further explored
		std::queue<const Node<T> *> tracker;

		/// mark the starting node as visited
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
					/// if the node is not visited then mark it as visited
					/// and push it to the queue
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
		/// vector to keep track of visited nodes
		std::vector<Node<T>> visited;
		auto nodeSet = getNodeSet();
		if (nodeSet.find(&start) == nodeSet.end()) //check is exist node in the graph
		{
			return visited;
		}
		const AdjacencyMatrix<T> adj = getAdjMatrix();
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
	const bool Graph<T>::isCyclicDirectedGraphDFS() const
	{
		if(!isDirectedGraph()){
			return false;
		}
		enum nodeStates : uint8_t
		{
			not_visited,
			in_stack,
			visited
		};
		auto nodeSet = this->getNodeSet();
		auto adjMatrix = this->getAdjMatrix();

		/** State of the node.
         *
         * It is a vector of "nodeStates" which represents the state node is in.
         * It can take only 3 values: "not_visited", "in_stack", and "visited".
         *
         * Initially, all nodes are in "not_visited" state.
         */
		std::map<unsigned long,nodeStates> state;
		for (auto node : nodeSet){
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
				std::function<bool(AdjacencyMatrix<T>&,std::map<unsigned long,nodeStates>&,const Node<T>*)> isCyclicDFSHelper;
				isCyclicDFSHelper = [this, &isCyclicDFSHelper](AdjacencyMatrix<T>& adjMatrix, std::map<unsigned long,nodeStates>& states, const Node<T>* node)
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
	
	template<typename T>
	const bool Graph<T>::isDirectedGraph() const
	{
		auto edgeSet = this->getEdgeSet();
		for( auto edge : edgeSet){
			if( !(edge->isDirected().has_value() && edge->isDirected().value())){
				//Found Undirected Edge
				return false;
			}
		}
		//No Undirected Edge
		return true;
	}

	//ostream overload
	template <typename T>
	std::ostream &operator<<(std::ostream &os, const Node<T> &node)
	{
		os << "Node: {\n"
		   << "  Id:\t" << node.id << "\n  Data:\t" << node.data << "\n}";
		return os;
	}

	template <typename T>
	std::ostream &operator<<(std::ostream &os, const Edge<T> &edge)
	{
		os << "((Node: " << edge.nodePair.first->getId() << ")) ?----- |Edge: " << edge.id << "|-----? ((Node: " << edge.nodePair.second->getId() << "))";
		return os;
	}

	template <typename T>
	std::ostream &operator<<(std::ostream &os, const DirectedEdge<T> &edge)
	{
		os << "((Node: " << edge.getFrom().getId() << ")) +----- |Edge: #" << edge.getId() << "|-----> ((Node: " << edge.getTo().getId() << "))";
		return os;
	}

	template <typename T>
	std::ostream &operator<<(std::ostream &os, const UndirectedEdge<T> &edge)
	{
		os << "((Node: " << edge.getNode1().getId() << ")) <----- |Edge: #" << edge.getId() << "|-----> ((Node: " << edge.getNode2().getId() << "))";
		return os;
	}

	template <typename T>
	std::ostream &operator<<(std::ostream &os, const DirectedWeightedEdge<T> &edge)
	{
		os << "((Node: " << edge.getFrom().getId() << ")) +----- |Edge: #" << edge.getId() << " W:" << edge.getWeight() << "|-----> ((Node: " << edge.getTo().getId() << "))";
		return os;
	}

	template <typename T>
	std::ostream &operator<<(std::ostream &os, const UndirectedWeightedEdge<T> &edge)
	{
		os << "((Node: " << edge.getNode1().getId() << ")) <----- |Edge: #" << edge.getId() << " W:" << edge.getWeight() << "|-----> ((Node: " << edge.getNode2().getId() << "))";
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
#endif // __CXXGRAPH_H__