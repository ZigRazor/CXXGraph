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
/***	 License: MPL v2.0 ***/
/***********************************************************/

#ifndef __CXXGRAPH_HOPCROFTKARP_IMPL_H__
#define __CXXGRAPH_HOPCROFTKARP_IMPL_H__

#pragma once

#include "CXXGraph/Graph/Graph_decl.h"
#include <queue>
#include <iostream>

namespace CXXGraph {
    template <typename T>
    const HopcroftKarpResult_struct Graph<T>::hopcroftKarp() const {
        HopcroftKarpResult_struct result;
        result.success = false;
        result.errorMessage = "";
        result.maxMatching = 0;

        // If the graph is empty or has no edges, the maximum matching is 0.
        // The graph is still bipartite.
        if (this->getNodeSet().empty() || this->getEdgeSet().empty()) {
            result.success = true;
            result.maxMatching = 0;
            return result;
        }

        auto nodeSet = getNodeSet();

        // need at least 2 nodes for matching
        if(nodeSet.size() < 2) {
            result.errorMessage = "Graph must have at least 2 nodes for bipartite matching.";
            return result;
        }

        // algorithm requires undirected graph
        if(isDirectedGraph()) {
            result.errorMessage = ERR_DIR_GRAPH;
            return result;
        }

        // convert nodes to vector for easier iteration
        std::vector<shared<const Node<T>>> nodes(nodeSet.begin(), nodeSet.end());

        // verify graph is bipartite using BFS 2-coloring
        std::unordered_map<std::string, int> color; // use node IDs to avoid pointer issues
        bool isBipartite = true;

        // process each connected component separately
        for(const auto& startNode : nodes) {
            if(color.find(startNode->getUserId()) == color.end() && isBipartite) {
                std::queue<shared<const Node<T>>> queue;
                queue.push(startNode);
                color[startNode->getUserId()] = 0;

                while(!queue.empty() && isBipartite) {
                    auto current = queue.front();
                    queue.pop();

                    auto neighbors = this->inOutNeighbors(current);
                    for(const auto& neighbor : neighbors) {
                        if(color.find(neighbor->getUserId()) == color.end()) {
                            // assign opposite color
                            color[neighbor->getUserId()] = 1 - color[current->getUserId()];
                            queue.push(neighbor);
                        }
                        else if(color[neighbor->getUserId()] == color[current->getUserId()]) {
                            // same color means odd cycle - not bipartite
                            isBipartite = false;
                            break;
                        }
                    }
                }
            }
        }

        if(!isBipartite) {
            result.errorMessage = "Graph is not bipartite.";
            return result;
        }

        // partition nodes into left (U) and right (V) sets
        std::vector<shared<const Node<T>>> U, V;
        for(const auto& node : nodes) {
            auto colorIt = color.find(node->getUserId());
            if(colorIt != color.end()) {
                if(colorIt->second == 0) {
                    U.push_back(node);
                }
                else {
                    V.push_back(node);
                }
            }
        }

        // assign isolated vertices to left partition
        for(const auto& node : nodes) {
            if(color.find(node->getUserId()) == color.end()) {
                U.push_back(node);
            }
        }

        // no matching possible if either partition is empty
        if(U.empty() || V.empty()) {
            result.success = true;
            result.maxMatching = 0;
            return result;
        }

        std::unordered_map<shared<const Node<T>>, shared<const Node<T>>, nodeHash<T>> match;
        std::unordered_map<shared<const Node<T>>, int, nodeHash<T>> dist;
        int matchingSize = 0;
        int path_len = -1;

        // BFS: builds layered graph and finds shortest augmenting path length
        auto bfs = [&]() {
            dist.clear();
            path_len = -1;
            std::queue<shared<const Node<T>>> q;
            
            // start from unmatched nodes in left partition
            for (const auto& u : U) {
                if (match.find(u) == match.end()) {
                    dist[u] = 0;
                    q.push(u);
                }
            }

            while (!q.empty()) {
                auto u = q.front();
                q.pop();

                // stop if shortest path already found
                if (path_len != -1 && dist.at(u) >= path_len) continue;

                auto neighbors = this->inOutNeighbors(u);
                for (const auto& v : neighbors) {
                    if (match.find(v) == match.end()) {
                        // found unmatched node - augmenting path exists
                        if (path_len == -1) path_len = dist.at(u) + 1;
                    } else {
                        // add matched partner to next layer
                        auto matched_u = match.at(v);
                        if (dist.find(matched_u) == dist.end()) {
                            dist[matched_u] = dist.at(u) + 1;
                            q.push(matched_u);
                        }
                    }
                }
            }
            return path_len != -1;
        };

        // DFS: finds vertex-disjoint augmenting paths
        auto dfs = [&](auto&& self, shared<const Node<T>> u) -> bool {
            if (dist.find(u) == dist.end()) return false;

            auto neighbors = this->inOutNeighbors(u);
            for (const auto& v : neighbors) {
                if (match.find(v) == match.end()) {
                    // found unmatched node at correct distance
                    if (dist.at(u) + 1 == path_len) {
                        match[v] = u;
                        match[u] = v;
                        return true;
                    }
                } else {
                    // try extending through matched partner
                    auto matched_u = match.at(v);
                    if (dist.count(matched_u) && dist.at(matched_u) == dist.at(u) + 1) {
                        if (self(self, matched_u)) {
                            match[v] = u;
                            match[u] = v;
                            return true;
                        }
                    }
                }
            }
            dist.erase(u); // remove processed node
            return false;
        };

        // main loop: alternate BFS and DFS phases
        while (bfs()) {
            for (const auto& u : U) {
                if (match.find(u) == match.end()) {
                    if (dfs(dfs, u)) {
                        matchingSize++;
                    }
                }
            }
        }

        // prepare result
        result.success = true;
        result.maxMatching = matchingSize;
        
        // build matching pairs (only from U to avoid duplicates)
        for (const auto& u : U) {
            if (match.count(u)) {
                result.matching.push_back({u->getUserId(), match.at(u)->getUserId()});
            }
        }
        
        return result;
    }

}  // namespace CXXGraph

#endif  // __CXXGRAPH_HOPCROFTKARP_IMPL_H__
