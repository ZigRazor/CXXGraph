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

#ifndef __CXXGRAPH_TYPEDEF_H__
#define __CXXGRAPH_TYPEDEF_H__

#pragma once

#include <map>
#include <string>
#include <fstream>

#include "Node/Node.hpp"
#include "Edge/Edge.hpp"
#include "Partitioning/Partition.hpp"

namespace CXXGRAPH
{
    // ENUMERATION //////////////////////////////////////

    /// Specify the Input/Output format of the Graph for Import/Export functions
	enum E_InputOutputFormat
	{
		STANDARD_CSV, ///< A standard csv format
		STANDARD_TSV, ///< A standard tsv format
		OUT_1,
		OUT_2
	};

	typedef E_InputOutputFormat InputOutputFormat;

	

    /////////////////////////////////////////////////////
    // Structures ///////////////////////////////////////
    
    /// Struct that contains the information about Dijsktra's Algorithm results
	struct DijkstraResult_struct
	{
		bool success;			  // TRUE if the function does not return error, FALSE otherwise
		std::string errorMessage; //message of error
		double result;			  //result (valid only if success is TRUE)
	};
	typedef DijkstraResult_struct DijkstraResult;

	/// Struct that contains the information about Dijsktra's Algorithm results
	struct DialResult_struct
	{
		bool success;								  // TRUE if the function does not return error, FALSE otherwise
		std::string errorMessage;					  //message of error
		std::map<unsigned long, long> minDistanceMap; //result a map that contains the node id and the minumum distance from source (valid only if success is TRUE)
	};
	typedef DialResult_struct DialResult;

	/// Struct that contains the information about the partitioning statistics
	

    ///////////////////////////////////////////////////////////////////////////////////
    // Using Definition ///////////////////////////////////////////////////////////////

	template <typename T>
	using AdjacencyMatrix = std::map<const Node<T> *, std::vector<std::pair<const Node<T> *, const Edge<T> *>>>;

	template <typename T>
	using PartitionMap = std::map<unsigned int, PARTITIONING::Partition<T> *>;

	///////////////////////////////////////////////////////////////////////////////////	
}

#endif // __CXXGRAPH_TYPEDEF_H__