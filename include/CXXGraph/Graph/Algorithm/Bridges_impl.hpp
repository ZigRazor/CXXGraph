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
/***	 Collaboration: John Ronchetto 				     ***/
/***********************************************************/
/***	 License: MPL v2.0 ***/
/***********************************************************/

// NOT OPTIMIZED SOLUTION
// UNDIRECTED GRAPH ASSUMPTION

#ifndef __CXXGRAPH_BRIDGES_IMPL_H__
#define __CXXGRAPH_BRIDGES_IMPL_H__

#pragma once

#include <algorithm>
#include <functional>
#include <vector>

#include "CXXGraph/Graph/Graph_decl.h"



namespace CXXGraph {

// Returns list of edges that are bridges in the graph
template <typename T>
const std::vector<std::pair<Node<T>, Node<T>>> Graph<T>::bridges(
    const Node<T> &start) const {

	std::vector<std::pair<Node<T>, Node<T>>> bridge;

	auto &nodeSet = Graph<T>::getNodeSet();

	// Check that start node actually exists
	auto startNodeIt = std::find_if(
		nodeSet.begin(), nodeSet.end(),
		[&start](auto &node) {return node->getUserId() == start.getUserId();});
	// If start node not in graph, then return wmpty result
	if (startNodeIt == nodeSet.end())
		return bridge;

	// Helper that runs dfs on node and skips a specific edge (skipU-SkipV)
	std::function<void(const std::shared_ptr<AdjacencyList<T>>,
						shared<const Node<T>>,
						shared<const Node<T>>,
						shared<const Node<T>>,
						std::vector<Node<T>> &)>
		dfs;

	dfs = [&dfs](const std::shared_ptr<AdjacencyList<T>> adj,
					shared<const Node<T>> node,
					shared<const Node<T>> skipU,
					shared<const Node<T>> skipV,
					std::vector<Node<T>> &visited) -> void {

		// Mark current node as visited
		visited.push_back(*node);

		// if node has no out edges, then we're done
		if (adj->find(node) == adj->end()) {
			return;
		}

		// Explore all nighbors of current node
		for (const auto &x : adj->at(node)) {
			auto next = x.first;

			// Check whether the current edge (node-next) is
			// the one we want to remove. Check both directions.

			bool edgeRemoved =
				(node->getUserId() == skipU->getUserId() &&
				next->getUserId() == skipV->getUserId()) ||
 				(node->getUserId() == skipV->getUserId() &&
 				next->getUserId() == skipU->getUserId());

			// Pretend that edge doesn't exist
			if (edgeRemoved) {
				continue;
			}

			// Standard dfs check using Node<T> value
			if (std::find(visited.begin(), visited.end(), *next) ==
				visited.end()) {
				dfs(adj, next, skipU, skipV, visited);
			}
		}
	};

	// Iterate over every node in the graph
	for (auto &uPtr : nodeSet) {
		// cachedAdjListOut maps each node in the graph to its outgoing neighbors
		auto adjIt = cachedAdjListOut->find(uPtr);

		if (adjIt == cachedAdjListOut->end()) {
			continue;
		}

		// Look at every neighbor
		for (const auto &edge : adjIt->second) {
			auto vPtr = edge.first;

			// Run dfs form u and skipping edge u-v
			std::vector<Node<T>> visited;
			dfs(cachedAdjListOut, uPtr, uPtr, vPtr, visited);

			// Check if v was reached
			// if NOT, then u-v is a bridge
			bool reached =
				std::find(visited.begin(), visited.end(), *vPtr) !=
				visited.end();

		        auto uId = uPtr->getUserId();
		        auto vId = vPtr->getUserId();

			if (!reached) {
			    if (uId < vId) {
			        bridge.emplace_back(*uPtr, *vPtr);
			    }
			}
		}
	}

	return bridge;
}

} // namespace CXXGraph

#endif // __CXXGRAPH_BRIDGES_IMPL_H__