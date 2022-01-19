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

#ifndef __CXXGRAPH_EDGE_H__
#define __CXXGRAPH_EDGE_H__

#pragma once

#include <utility>
#include <optional>

#include "Node/Node.hpp"

namespace CXXGRAPH
{
	template <typename T>
	class Edge;
	// ostream operator
	template <typename T>
	std::ostream &operator<<(std::ostream &o, const Edge<T> &edge);
	template <typename T>
	class Edge
	{
	private:
		unsigned long long id = 0;
		std::pair<const Node<T> *, const Node<T> *> nodePair;

	public:
		Edge(const unsigned long long id, const Node<T> &node1, const Node<T> &node2);
		Edge(const unsigned long long id, const std::pair<const Node<T> *, const Node<T> *> &nodepair);
		virtual ~Edge() = default;
		const unsigned long long &getId() const;
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
	Edge<T>::Edge(const unsigned long long id, const Node<T> &node1, const Node<T> &node2) : nodePair(&node1, &node2)
	{
		this->id = id;
	}

	template <typename T>
	Edge<T>::Edge(const unsigned long long id, const std::pair<const Node<T> *, const Node<T> *> &nodepair) : nodePair(nodepair)
	{
		this->id = id;
	}

	template <typename T>
	const unsigned long long &Edge<T>::getId() const
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
	std::ostream &operator<<(std::ostream &os, const Edge<T> &edge)
	{
		os << "((Node: " << edge.nodePair.first->getId() << ")) ?----- |Edge: " << edge.id << "|-----? ((Node: " << edge.nodePair.second->getId() << "))";
		return os;
	}
}

#endif // __CXXGRAPH_EDGE_H__