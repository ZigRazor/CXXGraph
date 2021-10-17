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


#ifndef __CXXGRAPH_NODE_H__
#define __CXXGRAPH_NODE_H__

#pragma once
#include <iostream>

namespace CXXGRAPH
{
	template <typename T>
	class Node;	
	template <typename T>
	std::ostream &operator<<(std::ostream &os, const Node<T> &node);
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


	//ostream overload
	template <typename T>
	std::ostream &operator<<(std::ostream &os, const Node<T> &node)
	{
		os << "Node: {\n"
		   << "  Id:\t" << node.id << "\n  Data:\t" << node.data << "\n}";
		return os;
	}
}

#endif // __CXXGRAPH_NODE_H__