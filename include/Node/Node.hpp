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
#include <openssl/sha.h>
#include <iomanip>


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
		unsigned long long id;
		std::string userId;
		T data;

	public:
		Node(const unsigned long id, const T &data);
		Node(std::string id, const T &data);
		~Node() = default;
		const unsigned long long &getId() const;
		const std::string &getUserId() const;
		const T &getData() const;
		//operator
		bool operator==(const Node<T> &b) const;
		bool operator<(const Node<T> &b) const;
		friend std::ostream &operator<<<>(std::ostream &os, const Node<T> &node);
	};

	template <typename T>
	Node<T>::Node(const unsigned long id, const T &data)
	{
		this->userId = std::to_string(id);
		this->id = id;
		this->data = data;
	}

	template <typename T>
	Node<T>::Node(std::string id, const T &data)
	{
		this->userId = id;
		this->data = data;
		const unsigned char* userId = reinterpret_cast<const unsigned char *>(id.c_str() );
		unsigned char obuf[64];
		SHA512(userId, id.length(), obuf);
		// Transform byte-array to string
		std::stringstream shastr;
		shastr << std::hex << std::setfill('0');
		int i = 0;
		//unsigned long can only store 8 bytes so we truncate the hash to 8 bytes
		for (const auto &byte: obuf)
		{
			shastr << std::setw(2) << (int)byte;
			i++;
			if (i==8) break;
		}
		auto idStr =  shastr.str();
		// convert hex string to unsigned long long
		size_t hashId;
		std::istringstream iss(idStr);
		iss >> std::hex >> this->id;
	}

	template <typename T>
	const unsigned long long &Node<T>::getId() const
	{
		return id;
	}

	template <typename T>
	const std::string &Node<T>::getUserId() const
	{
		return userId;
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