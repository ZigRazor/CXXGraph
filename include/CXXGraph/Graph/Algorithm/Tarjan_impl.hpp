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

#ifndef __CXXGRAPH_TARJAN_IMPL_H__
#define __CXXGRAPH_TARJAN_IMPL_H__

#pragma once

#include "CXXGraph/Graph/Graph_decl.h"

namespace CXXGraph {

template <typename T>
const TarjanResult<T> Graph<T>::tarjan(const unsigned int typeMask) const {
  TarjanResult<T> result;
  result.success = false;
  bool isDirected = this->isDirectedGraph();
  if (isDirected) {
    // check whether targetMask is a subset of the mask for directed graph
    unsigned int directedMask = TARJAN_FIND_SCC;
    if ((typeMask | directedMask) != directedMask) {
      result.errorMessage = ERR_DIR_GRAPH;
      return result;
    }
  } else {
    // check whether targetMask is a subset of the mask for undirected graph
    unsigned int undirectedMask = (TARJAN_FIND_CUTV | TARJAN_FIND_BRIDGE |
                                   TARJAN_FIND_VBCC | TARJAN_FIND_EBCC);
    if ((typeMask | undirectedMask) != undirectedMask) {
      result.errorMessage = ERR_UNDIR_GRAPH;
      return result;
    }
  }

  const auto &nodeSet = getNodeSet();
  std::unordered_map<CXXGraph::id_t, int>
      discoveryTime;  // the timestamp when a node is visited
  std::unordered_map<CXXGraph::id_t, int>
      lowestDisc;  // the lowest discovery time of all
                   // reachable nodes from current node
  int timestamp = 0;
  CXXGraph::id_t rootId = 0;
  std::stack<Node<T>> sccNodeStack;
  std::stack<Node<T>> ebccNodeStack;
  std::stack<Node<T>> vbccNodeStack;
  std::unordered_set<CXXGraph::id_t> inStack;
  std::function<void(const shared<const Node<T>>, const shared<const Edge<T>>)>
      dfs_helper = [this, typeMask, isDirected, &dfs_helper, &discoveryTime,
                    &lowestDisc, &timestamp, &rootId, &sccNodeStack,
                    &ebccNodeStack, &vbccNodeStack, &inStack,
                    &result](const shared<const Node<T>> curNode,
                             const shared<const Edge<T>> prevEdge) {
        // record the visited time of current node
        discoveryTime[curNode->getId()] = timestamp;
        lowestDisc[curNode->getId()] = timestamp;
        timestamp++;
        if (typeMask & TARJAN_FIND_SCC) {
          sccNodeStack.emplace(*curNode);
          inStack.emplace(curNode->getId());
        }
        if (typeMask & TARJAN_FIND_EBCC) {
          ebccNodeStack.emplace(*curNode);
        }
        if (typeMask & TARJAN_FIND_VBCC) {
          vbccNodeStack.emplace(*curNode);
        }
        // travel the neighbors
        if (cachedAdjMatrix->find(curNode) != cachedAdjMatrix->end()) {
          int numSon = 0;
          bool nodeIsAdded =
              false;  // whether a node has been marked as a cut vertice
          for (const auto &[neighborNode, edge] :
               cachedAdjMatrix->at(curNode)) {
            if (!discoveryTime.count(neighborNode->getId())) {
              dfs_helper(neighborNode, edge);
              lowestDisc[curNode->getId()] =
                  std::min(lowestDisc[curNode->getId()],
                           lowestDisc[neighborNode->getId()]);

              if (typeMask & TARJAN_FIND_BRIDGE) {
                // lowestDisc of neighbor node is larger than that of current
                // node means we can travel back to a visited node only through
                // this edge
                if (discoveryTime[curNode->getId()] <
                    lowestDisc[neighborNode->getId()]) {
                  result.bridges.emplace_back(*edge);
                }
              }

              if ((typeMask & TARJAN_FIND_CUTV) && (nodeIsAdded == false)) {
                if (curNode->getId() == rootId) {
                  numSon++;
                  // a root node is a cut vertices only when it connects at
                  // least two connected components
                  if (numSon == 2) {
                    nodeIsAdded = true;
                    result.cutVertices.emplace_back(*curNode);
                  }
                } else {
                  if (discoveryTime[curNode->getId()] <=
                      lowestDisc[neighborNode->getId()]) {
                    nodeIsAdded = true;
                    result.cutVertices.emplace_back(*curNode);
                  }
                }
              }

              if (typeMask & TARJAN_FIND_VBCC) {
                if (discoveryTime[curNode->getId()] <=
                    lowestDisc[neighborNode->getId()]) {
                  // if current node is a cut vertice or the root node, the vbcc
                  // a vertice-biconnect-component which contains the neighbor
                  // node
                  std::vector<Node<T>> vbcc;
                  while (true) {
                    // pop a top node out of stack until
                    // the neighbor node has been poped out
                    Node<T> nodeAtTop = vbccNodeStack.top();
                    vbccNodeStack.pop();
                    vbcc.emplace_back(nodeAtTop);
                    if (nodeAtTop == *neighborNode) {
                      break;
                    }
                  }
                  vbcc.emplace_back(*curNode);
                  result.verticeBiconnectedComps.emplace_back(std::move(vbcc));
                }
              }
            } else if ((edge != prevEdge) &&
                       ((isDirected == false) ||
                        (inStack.count(neighborNode->getId())))) {
              // it's not allowed to go through the previous edge back
              // for a directed graph, it's also not allowed to visit
              // a node that is not in stack
              lowestDisc[curNode->getId()] = std::min(lowestDisc[curNode->getId()], discoveryTime[neighborNode->getId()]);
            }
          }
        }
        // find sccs for a undirected graph is very similar with
        // find ebccs for a directed graph
        if ((typeMask & TARJAN_FIND_SCC) || (typeMask & TARJAN_FIND_EBCC)) {
          std::stack<Node<T>> &nodeStack =
              (typeMask & TARJAN_FIND_SCC) ? sccNodeStack : ebccNodeStack;
          if (discoveryTime[curNode->getId()] == lowestDisc[curNode->getId()]) {
            std::vector<Node<T>> connectedComp;
            while (true) {
              // pop a top node out of stack until
              // the current node has been poped out
              Node<T> nodeAtTop = nodeStack.top();
              nodeStack.pop();
              if (typeMask & TARJAN_FIND_SCC) {
                inStack.erase(nodeAtTop.getId());
              }
              connectedComp.emplace_back(nodeAtTop);
              if (nodeAtTop == *curNode) {
                break;
              }
            }
            // store this component in result
            (typeMask & TARJAN_FIND_SCC)
                ? result.stronglyConnectedComps.emplace_back(
                      std::move(connectedComp))
                : result.edgeBiconnectedComps.emplace_back(
                      std::move(connectedComp));
          }
        }
      };

  for (const auto &node : nodeSet) {
    if (!discoveryTime.count(node->getId())) {
      rootId = node->getId();
      dfs_helper(node, nullptr);
    }
  }

  result.success = true;
  return result;
}
}  // namespace CXXGraph
#endif  // __CXXGRAPH_TARJAN_IMPL_H__
