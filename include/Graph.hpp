
#pragma once

#include <utility>
#include <set>
#include <optional>

namespace CXXGRAPH
{
	template <typename T>
	class Node;
	template <typename T>
	class Edge;
	template <typename T>
	class DirectedEdge;
	template <typename T>
	class UndirectedEdge;
	template <typename T>
	class Graph;

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
	class Edge
	{
	private:
		unsigned long id;
		std::pair<Node<T>, Node<T>> nodePair;

	public:
		Edge(const unsigned long id, const Node<T> &node1, const Node<T> &node2);
		Edge(const unsigned long id, const std::pair<Node<T>, Node<T>> &nodepair);
		virtual ~Edge() = default;
		const unsigned long &getId() const;
		const std::pair<Node<T>, Node<T>> &getNodePair() const;
		virtual const std::optional<bool> isDirected() const;
		virtual const std::optional<bool> isWeighted() const;
		//operator
		virtual bool operator==(const Edge<T> &b) const;
		bool operator<(const Edge<T> &b) const;
		operator DirectedEdge<T>() const { return DirectedEdge<T>(id, nodePair); }
		operator UndirectedEdge<T>() const { return UndirectedEdge<T>(id, nodePair); }
	};

	template <typename T>
	Edge<T>::Edge(const unsigned long id, const Node<T> &node1,const Node<T> &node2) : nodePair(node1, node2)
	{
		this->id = id;
	}

	template <typename T>
	Edge<T>::Edge(const unsigned long id, const std::pair<Node<T>, Node<T>> &nodepair) : nodePair(nodepair)
	{
		this->id = id;
	}

	template <typename T>
	const unsigned long &Edge<T>::getId() const
	{
		return id;
	}

	template <typename T>
	const std::pair<Node<T>, Node<T>> &Edge<T>::getNodePair() const
	{
		return nodePair;
	}

	
	template<typename T>
	const std::optional<bool> Edge<T>::isDirected() const
	{
		return std::nullopt;
	}
	
	template<typename T>
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
		DirectedEdge(const unsigned long id, const std::pair<Node<T>, Node<T>> &nodepair);
		DirectedEdge(const Edge<T> &edge);
		virtual ~DirectedEdge() = default;
		const Node<T> &getFrom() const;
		const Node<T> &getTo() const;
		const std::optional<bool> isDirected() const override;
		virtual const std::optional<bool> isWeighted() const override;
		//operator
		explicit operator UndirectedEdge<T>() const { return UndirectedEdge<T>(Edge<T>::getId(), Edge<T>::getNodePair()); }
	};

	template <typename T>
	DirectedEdge<T>::DirectedEdge(const unsigned long id, const Node<T> &node1,const Node<T> &node2) : Edge<T>(id, node1, node2)
	{
	}

	template <typename T>
	DirectedEdge<T>::DirectedEdge(const unsigned long id, const std::pair<Node<T>, Node<T>> &nodepair) : Edge<T>(id, nodepair)
	{
	}

	template <typename T>
	DirectedEdge<T>::DirectedEdge(const Edge<T> &edge) : DirectedEdge(edge.getId(), edge.getNodePair().first, edge.getNodePair().second)
	{
	}

	template <typename T>
	const Node<T> &DirectedEdge<T>::getFrom() const
	{
		return Edge<T>::getNodePair().first;
	}

	template <typename T>
	const Node<T> &DirectedEdge<T>::getTo() const
	{
		return Edge<T>::getNodePair().second;
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
		UndirectedEdge(const unsigned long id, const std::pair<Node<T>, Node<T>> &nodepair);
		UndirectedEdge(const Edge<T> &edge);
		virtual ~UndirectedEdge() = default;
		const Node<T> &getNode1() const;
		const Node<T> &getNode2() const;
		const std::optional<bool> isDirected() const override;
		const std::optional<bool> isWeighted() const override;
		//operator
		explicit operator DirectedEdge<T>() const { return DirectedEdge<T>(Edge<T>::getId(), Edge<T>::getNodePair()); }
	};

	template <typename T>
	UndirectedEdge<T>::UndirectedEdge(const unsigned long id, const Node<T> &node1,const Node<T> &node2) : Edge<T>(id, node1, node2)
	{
	}

	template <typename T>
	UndirectedEdge<T>::UndirectedEdge(const unsigned long id, const std::pair<Node<T>, Node<T>> &nodepair) : Edge<T>(id, nodepair)
	{
	}

	template <typename T>
	UndirectedEdge<T>::UndirectedEdge(const Edge<T> &edge) : UndirectedEdge(edge.getId(), edge.getNodePair().first, edge.getNodePair().second)
	{
	}

	template <typename T>
	const Node<T> &UndirectedEdge<T>::getNode1() const
	{
		return Edge<T>::getNodePair().first;
	}

	template <typename T>
	const Node<T> &UndirectedEdge<T>::getNode2() const
	{
		return Edge<T>::getNodePair().second;
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
	class Graph
	{
	private:
		std::set<Edge<T>> edgeSet;

	public:
		Graph() = default;
		Graph(const std::set<Edge<T>> &edgeSet);
		~Graph() = default;
		const std::set<Edge<T>> &getEdgeSet() const;
		void setEdgeSet(std::set<Edge<T>> &edgeSet);
		void addEdge(const Edge<T> &edge);
		void removeEdge(unsigned long edgeId);
		const std::optional<const Edge<T>> getEdge(unsigned long edgeId) const;
	};

	template <typename T>
	Graph<T>::Graph(const std::set<Edge<T>> &edgeSet)
	{
		this->edgeSet = edgeSet;
	}

	template <typename T>
	const std::set<Edge<T>> &Graph<T>::getEdgeSet() const
	{
		return edgeSet;
	}

	template <typename T>
	void Graph<T>::setEdgeSet(std::set<Edge<T>> &edgeSet)
	{
		this->edgeSet = edgeSet;
	}

	template <typename T>
	void Graph<T>::addEdge(const Edge<T> &edge)
	{
		edgeSet.insert(edge);
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
	const std::optional<const Edge<T>> Graph<T>::getEdge(unsigned long edgeId) const
	{

		auto it = edgeSet.begin();
		for (it; it != edgeSet.end(); ++it)
		{
			if (it->getId() == edgeId)
			{
				return *it;
			}
		}
		
		return std::nullopt;
	}

} // namespace CXXGRAPH