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
/***     Author: ZigRazor ***/
/***	 E-Mail: zigrazor@gmail.com 				     ***/
/***********************************************************/
/***	 Collaboration: ----------- 				     ***/
/***********************************************************/
/***	 License: AGPL v3.0 ***/
/***********************************************************/

#ifndef __CXXGRAPH_GRAPH_H__
#define __CXXGRAPH_GRAPH_H__

#include "CXXGraph/Graph/Graph_impl.hpp"

// Algorithm
#include "CXXGraph/Graph/Algorithm/BellmanFord_impl.hpp"
#include "CXXGraph/Graph/Algorithm/BestFirstSearch_impl.hpp"
#include "CXXGraph/Graph/Algorithm/Boruvka_impl.hpp"
#include "CXXGraph/Graph/Algorithm/BreadthFirstSearch_impl.hpp"
#include "CXXGraph/Graph/Algorithm/Connectivity_impl.hpp"
#include "CXXGraph/Graph/Algorithm/CycleDetection_impl.hpp"
#include "CXXGraph/Graph/Algorithm/DepthFirstSearch_impl.hpp"
#include "CXXGraph/Graph/Algorithm/Dial_impl.hpp"
#include "CXXGraph/Graph/Algorithm/Dijkstra_impl.hpp"
#include "CXXGraph/Graph/Algorithm/FloydWarshall_impl.hpp"
#include "CXXGraph/Graph/Algorithm/FordFulkerson_impl.hpp"
#include "CXXGraph/Graph/Algorithm/Kahn_impl.hpp"
#include "CXXGraph/Graph/Algorithm/Kosaraju_impl.hpp"
#include "CXXGraph/Graph/Algorithm/Kruskal_impl.hpp"
#include "CXXGraph/Graph/Algorithm/Pow_impl.hpp"
#include "CXXGraph/Graph/Algorithm/Prim_impl.hpp"
#include "CXXGraph/Graph/Algorithm/Tarjan_impl.hpp"
#include "CXXGraph/Graph/Algorithm/TopologicalSort_impl.hpp"
#include "CXXGraph/Graph/Algorithm/TransitiveReduction_impl.hpp"
#include "CXXGraph/Graph/Algorithm/welshPowellColoring_impl.hpp"

// IO Operation
#include "CXXGraph/Graph/IO/IOUtility_impl.hpp"
#include "CXXGraph/Graph/IO/InputOperation_impl.hpp"
#include "CXXGraph/Graph/IO/OutputOperation_impl.hpp"

#endif  // __CXXGRAPH_GRAPH_H__
