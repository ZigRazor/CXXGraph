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
		std::size_t id = 0;
		std::string userId = "";
		T data;
		void setId(std::string_view);

	public:
		Node(std::string_view, const T &data);
		~Node() = default;
		const std::size_t &getId() const;
		const std::string &getUserId() const;
		const T &getData() const;
		//operator
		bool operator==(const Node<T> &b) const;
		bool operator<(const Node<T> &b) const;
		friend std::ostream &operator<<<>(std::ostream &os, const Node<T> &node);
	};

	template <typename T>
	Node<T>::Node(std::string_view id, const T &data)
	{
		this->userId = id;
		// the userid is set as sha512 hash of the user provided id
		setId(id);
		this->data = data;
	}

	template <typename T>
	void Node<T>::setId(std::string_view inpId)
	{
		//const unsigned char* userId = reinterpret_cast<const unsigned char *>((*inpId).c_str() );
		//unsigned char obuf[64];
		//unsigned long long obuf[8];
		//SHA512(userId, (*inpId).length(), reinterpret_cast<unsigned char*>(obuf));
		/**
		// Transform byte-array to string
		std::stringstream shastr;
		shastr << std::hex << std::setfill('0');
		int i = 0;
		//unsigned long can only store 8 bytes so we truncate the hash to 8 bytes
		for (const auto &byte: obuf)
		{
			shastr << std::setw(2) << static_cast<int>(byte);
			i++;
			if (i==8) break;
		}
		auto idStr =  shastr.str();
		// convert hex string to unsigned long long
		std::istringstream iss(idStr);
		iss >> std::hex >> this->id;
		
		**/
		this->id = std::hash<std::string_view>{}(inpId);
		
	}	

	template <typename T>
	const std::size_t &Node<T>::getId() const
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
		   << "  Id:\t" << node.userId << "\n  Data:\t" << node.data << "\n}";
		return os;
	}
}

#endif // __CXXGRAPH_NODE_H__