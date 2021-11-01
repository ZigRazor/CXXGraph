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

#ifndef __CXXGRAPH_CONSTSTRING_H__
#define __CXXGRAPH_CONSTSTRING_H__

#pragma once

namespace CXXGRAPH
{
    //STRING ERROR CONST EXPRESSION
	constexpr char ERR_NO_DIR_OR_UNDIR_EDGE[] = "Edge are neither Directed neither Undirected";
	constexpr char ERR_DIR_GRAPH[] = "Graph is directed";
	constexpr char ERR_NO_WEIGHTED_EDGE[] = "Edge are not Weighted";
	constexpr char ERR_NEGATIVE_WEIGHTED_EDGE[] = "Edge negative Weighted";
	constexpr char ERR_TARGET_NODE_NOT_REACHABLE[] = "Target Node not Reachable";
	constexpr char ERR_TARGET_NODE_NOT_IN_GRAPH[] = "Target Node not inside Graph";
	constexpr char ERR_SOURCE_NODE_NOT_IN_GRAPH[] = "Source Node not inside Graph";
	///////////////////////////////
}
#endif // __CXXGRAPH_CONSTSTRING_H__