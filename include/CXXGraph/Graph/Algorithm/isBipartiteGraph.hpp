/***********************************************************/
/***      ______  ____  ______                 _         ***/
/***     / ___\ \/ /\ \/ / ___|_ __ __ _ _ __ | |__      ***/
/***    | |    \  /  \  / |  _| '__/ _` | '_ \| '_ \     ***/
/***    | |___ /  \  /  \ |_| | | | (_| | |_) | | | |    ***/
/***     \____/_/\_\/_/\_\____|_|  \__,_| .__/|_| |_|    ***/
/***                                    |_|             ***/
/***********************************************************/
/***     Header-Only C++ Library for Graph               ***/
/***   Representation and Algorithms                     ***/
/***********************************************************/
/***     Author: ZigRazor ***/
/***    E-Mail: zigrazor@gmail.com                       ***/
/***********************************************************/
/***    Collaboration: -----------                       ***/
/***********************************************************/
/***    License: AGPL v3.0 ***/
/***********************************************************/

#ifndef __CXXGRAPH_CHECK_ODD_NODES_CYCLE_H__
#define __CXXGRAPH_CHECK_ODD_NODES_CYCLE_H__

#pragma once

#include "CXXGraph/Graph/Graph_decl.h"

namespace CXXGraph {

template <typename T>
class Graph {
public:
    TopoSortResult<T> checkOddNodesCycleDir() const;

private:
    void checkOddNodesCycleUtil(std::vector<int>& visited, std::vector<int>& chainNo, 
                                int root, int cycleLength, bool &isBiPartite) const;
};

template <typename T>
TopoSortResult<T> Graph<T>::checkOddNodesCycleDir() const {
    TopoSortResult<T> result;

    // Check if the graph is undirected
    if (isDirectedGraph()) {
        result.errorMessage = ERR_UNDIR_GRAPH; // Error: Graph is directed
        return result;
    }

    const auto nodeSet = Graph<T>::getNodeSet();
    std::vector<int> visited(nodeSet.size(), 0);
    std::vector<int> chainNo(nodeSet.size(), -1);
    bool isBiPartite = true;

    for (const auto& node : nodeSet) {
        if (!visited[node->getId()]) {
            visited[node->getId()] = 1;
            checkOddNodesCycleUtil(visited, chainNo, node->getId(), 0, isBiPartite);
            if (!isBiPartite) {
                result.errorMessage = "The graph contains an odd-length cycle.";
                return result;
            }
        }
    }

    result.success = true;
    return result;
}

template <typename T>
void Graph<T>::checkOddNodesCycleUtil(std::vector<int>& visited, std::vector<int>& chainNo, 
                                      int root, int cycleLength, bool &isBiPartite) const {
    chainNo[root] = cycleLength;
    for (const auto& child : cachedAdjMatrix->find(root)) {
        if (!visited[std::get<0>(child)->getId()]) {
            visited[std::get<0>(child)->getId()] = 1;
            checkOddNodesCycleUtil(visited, chainNo, std::get<0>(child)->getId(), cycleLength + 1, isBiPartite);
            if (!isBiPartite) return;
        } else if (chainNo[root] == chainNo[std::get<0>(child)->getId()]) {
            isBiPartite = false;
            return;
        }
    }
}

}  // namespace CXXGraph

#endif  // __CXXGRAPH_CHECK_ODD_NODES_CYCLE_H__
