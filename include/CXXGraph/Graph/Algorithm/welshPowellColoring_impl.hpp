//
// Created by jjsm on 1/22/24.
//

#ifndef CXXGRAPH_WELSHPOWELLCOLORING_IMPL_H__
#define CXXGRAPH_WELSHPOWELLCOLORING_IMPL_H__

#pragma once

#include "CXXGraph/Graph/Graph_decl.h"

namespace CXXGraph {
template <typename T>
std::map<Node<T>, int> Graph<T>::welshPowellColoring() const {
  auto adjMatrix = *getAdjMatrixOut();

  std::vector<std::pair<std::shared_ptr<const Node<T>>, int>>
      degreeOfVertexVector = {};
  // Find the degree of each vertex and put them in a vector
  for (const auto& [nodeFrom, nodeToEdgeVec] : adjMatrix) {
    degreeOfVertexVector.push_back({nodeFrom, (int)nodeToEdgeVec.size()});
  }

  // Sort them based on the vertex degree
  std::sort(degreeOfVertexVector.begin(), degreeOfVertexVector.end(),
            [](const auto& left, const auto& right) {
              return left.second > right.second;
            });

  // Create a new map of coloring, where the keys a	re the nodes, and the
  // value is the color order (assigned by integer)
  std::map<Node<T>, int> mapOfColoring;
  for (const auto& [nodeFrom, _] : adjMatrix) {
    mapOfColoring[*nodeFrom] = 0;
  }

  // Going down the list of vertex based on degrees
  std::vector<int> usedColors(degreeOfVertexVector.size() + 1, 0);
  for (const auto& [node, _] : degreeOfVertexVector) {
    // Find the smallest unused color for the current vertex
    std::fill(usedColors.begin(), usedColors.end(), 0);
    for (const auto& [neighbor, _] : adjMatrix[node]) {
      usedColors[mapOfColoring[*neighbor]] = 1;
    }

    // Assign the smallest unused color to the current vertex
    auto it = std::find(usedColors.begin() + 1, usedColors.end(), 0);
    mapOfColoring[*node] = (int)std::distance(usedColors.begin(), it);
  }

  return mapOfColoring;
}
}  // namespace CXXGraph
#endif  // CXXGRAPH_WELSHPOWELLCOLORING_IMPL_H__
