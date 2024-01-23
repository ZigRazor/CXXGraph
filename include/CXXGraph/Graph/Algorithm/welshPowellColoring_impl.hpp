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
  auto adjMatrix = *getAdjMatrix();
  std::unordered_map<std::shared_ptr<const Node<T>>, int> degreeOfVertexMap = {};

  // Find the degree of each vertex and put them in a map
  for (auto &[nodeFrom, nodeToEdgeVec] : adjMatrix) {
    degreeOfVertexMap[nodeFrom] = nodeToEdgeVec.size();
  }

  // Transform the map to the vector to sort
  std::vector<std::pair<std::shared_ptr<const Node<T>>, int>> degreeOfVertexVector(degreeOfVertexMap.begin(), degreeOfVertexMap.end());

  // Sort them based on the vertex degree
  std::sort(degreeOfVertexVector.begin(), degreeOfVertexVector.end(), [](const auto& left, const auto& right) {
    return left.second > right.second;
  });

  // Create a new map of coloring, where the keys are the nodes, and the value is the color order (assigned by integer)
  std::map<Node<T>, int> mapOfColoring;
  for (auto &[nodeFrom, _] : adjMatrix) {
    mapOfColoring[*nodeFrom] = 0;
  }

  // Going down the list of vertex based on degrees
  for (const auto& [node, _] : degreeOfVertexVector) {
    // Find the smallest unused color for the current vertex
    std::vector<int> usedColors(degreeOfVertexVector.size() + 1, 0);

    for (const auto &[neighbor, _] : adjMatrix[node]) {
      usedColors[mapOfColoring[*neighbor]] = 1;
    }

    // Assign the smallest unused color to the current vertex
    for (int c = 1; c < usedColors.size(); c++) {
      if (usedColors[c] == 0) {
        mapOfColoring[*node] = c;
        break;
      }
    }
  }

  return mapOfColoring;
}
}
#endif  // CXXGRAPH_WELSHPOWELLCOLORING_IMPL_H__
