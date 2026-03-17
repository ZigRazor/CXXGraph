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

#pragma once

#include "CXXGraph/Graph/Graph_decl.h"
#include "CXXGraph/Utility/Parallel.hpp"
#include "CXXGraph/Utility/Typedef.hpp"

namespace CXXGraph {

template <typename T>
std::map<Node<T>, int> Graph<T>::welshPowellColoring_parallel() const {
  // ── Parallel degree computation ───────────────────────────────────────────
  auto rawNodeSet = getNodeSet();
  std::vector<shared<const Node<T>>> nodes(rawNodeSet.begin(),
                                           rawNodeSet.end());

  std::vector<std::size_t> degrees(nodes.size());

  Parallel::parallel_for(std::size_t{0}, nodes.size(), [&](std::size_t i) {
    degrees[i] = inOrOutNeighbors(nodes[i]).size();
  });

  // ── Parallel sort by degree (descending) ─────────────────────────────────
  std::vector<std::size_t> order(nodes.size());
  std::iota(order.begin(), order.end(), 0);
  Parallel::parallel_sort(
      order.begin(), order.end(),
      [&](std::size_t a, std::size_t b) { return degrees[a] > degrees[b]; });

  // ── Sequential greedy coloring ────────────────────────────────────────────
  // Each node's color depends on already-colored neighbors — strictly serial.
  std::map<Node<T>, int> colorMap;
  for (std::size_t oi : order) {
    const auto& node = nodes[oi];
    std::unordered_set<int> usedColors;
    for (const auto& nb : inOrOutNeighbors(node)) {
      auto it = colorMap.find(*nb);
      if (it != colorMap.end()) usedColors.insert(it->second);
    }
    int color = 1;
    while (usedColors.count(color)) ++color;
    colorMap[*node] = color;
  }

  return colorMap;
}
}  // namespace CXXGraph