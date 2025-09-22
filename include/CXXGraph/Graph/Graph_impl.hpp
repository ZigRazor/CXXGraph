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

#ifndef __CXXGRAPH_GRAPH_IMPL_H__
#define __CXXGRAPH_GRAPH_IMPL_H__

#pragma once

#include <algorithm>
#include <deque>

#include "CXXGraph/Graph/Graph_decl.h"
#include "CXXGraph/Utility/ConstString.hpp"

namespace CXXGraph {

using std::make_shared;
using std::make_unique;

template <typename T>
Graph<T>::Graph() {
  /* Caching the adjacency matrix */
  invalidateCache(true);
}

template <typename T>
Graph<T>::Graph(const T_EdgeSet<T> &edgeSet) {
  for (auto edgeIt : edgeSet) {
    this->edgeSet.insert(edgeIt);
  }
  /* Caching the adjacency matrix */
  invalidateCache(true);
}

template <typename T>
const T_EdgeSet<T> &Graph<T>::getEdgeSet() const {
  return edgeSet;
}

template <typename T>
T_EdgeVector<T> Graph<T>::getEdgeVector() const {
  T_EdgeVector<T> edgeVector(edgeSet.begin(), edgeSet.end());
  return edgeVector;
}

template <typename T>
void Graph<T>::setEdgeSet(const T_EdgeSet<T> &edgeSet) {
  this->edgeSet.clear();
  for (auto edgeIt : edgeSet) {
    this->edgeSet.insert(edgeIt);
  }
  /* Caching the adjacency matrix */
  invalidateCache(false);
}

template <typename T>
bool Graph<T>::addEdge(const Edge<T> *edge) {
  /* Checking if new edge is nullptr */
  if(edge == nullptr){
    return false;
  }

  shared<const Edge<T>> edge_shared;

  bool is_directed = edge->isDirected().value_or(false);
  bool is_weighted = edge->isWeighted().value_or(false);

  if (is_directed) {
    if (is_weighted) {
      auto cast = dynamic_cast<const DirectedWeightedEdge<T> *>(edge);
      
      /* Checking if cast succeeds */
      if(cast == nullptr) {
        return false;
      }

      edge_shared = make_shared<DirectedWeightedEdge<T>>(*cast);
    } else {
      edge_shared = make_shared<DirectedEdge<T>>(*edge);
    }
  } else {
    if (is_weighted) {
      auto cast = dynamic_cast<const UndirectedWeightedEdge<T> *>(edge);
      
      /* Checking if cast succeeds */
      if(cast == nullptr) {
        return false;
      }
      
      edge_shared = make_shared<UndirectedWeightedEdge<T>>(*cast);
    } else {
      edge_shared = make_shared<UndirectedEdge<T>>(*edge);
    }
  }

  return addEdge(edge_shared);
}

template <typename T>
bool Graph<T>::addEdge(shared<const Edge<T>> edge) {
  auto res = this->edgeSet.insert(edge);
  
  /* Checking if new edge was inserted into set of edges */
  bool is_added = res.second;
  if(!is_added) {
    return false;
  }

  auto &[from, to] = edge->getNodePair();

  /* Adding new edge in cached adjacency lists if edge was inserted */
  (*cachedAdjListOut)[from].emplace_back(to, edge);
  (*cachedAdjListIn)[to].emplace_back(from, edge);
  if (!edge.get()->isDirected().value_or(true)) {
    (*cachedAdjListOut)[to].emplace_back(from, edge);
    (*cachedAdjListIn)[from].emplace_back(to, edge);
  }

  return true;
}

template <typename T>
template <typename... Tn>
void Graph<T>::addEdges() {
  return;
}

template <typename T>
template <typename T1, typename... Tn>
std::enable_if_t<all_are_edge_ptrs_v<T1, Tn...>, void> Graph<T>::addEdges(
    T1 edge, Tn... edges) {
  addEdge(edge);
  addEdges(edges...);
}

template <typename T>
void Graph<T>::addNode(const Node<T> *node) {
  auto node_shared = make_shared<const Node<T>>(*node);
  this->isolatedNodesSet.insert(node_shared);
}

template <typename T>
void Graph<T>::addNode(shared<const Node<T>> node) {
  this->isolatedNodesSet.insert(node);
}

template <typename T>
template <typename... Tn>
void Graph<T>::addNodes() {
  return;
}

template <typename T>
template <typename T1, typename... Tn>
std::enable_if_t<all_are_node_ptrs_v<T1, Tn...>, void> Graph<T>::addNodes(
    T1 node, Tn... nodes) {
  addNode(node);
  addNodes(nodes...);
}

template <typename T>
void Graph<T>::removeEdge(const CXXGraph::id_t edgeId) {
  auto edgeOpt = Graph<T>::getEdge(edgeId);
  if (edgeOpt.has_value()) {
    /*
    edgeSet.erase(std::find_if(this->edgeSet.begin(), this->edgeSet.end(),
    [edgeOpt](const Edge<T> *edge) { return (*(edgeOpt.value()) == *edge); }));
    */
    edgeSet.erase(edgeSet.find(edgeOpt.value()));

    auto &[from, to] = edgeOpt.value().get()->getNodePair();

    int delIndex = -1;
    int i = 0;
    /* Removing the edge from the cached adjacency lists */
    for (auto elem : (*cachedAdjListOut)[from]) {
      if (elem.second.get()->getId() == edgeId) {
        delIndex = i;
        break;
      }
      i++;
    }
    if (delIndex != -1) {
      (*cachedAdjListOut)[from].erase((*cachedAdjListOut)[from].begin() +
                                      delIndex);
      if ((*cachedAdjListOut)[from].empty()) {
        cachedAdjListOut->erase(from);
      }
    }

    delIndex = -1;
    i = 0;
    for (auto elem : (*cachedAdjListIn)[to]) {
      if (elem.second.get()->getId() == edgeId) {
        delIndex = i;
        break;
      }
      i++;
    }
    if (delIndex != -1) {
      (*cachedAdjListIn)[to].erase((*cachedAdjListIn)[to].begin() + delIndex);
      if ((*cachedAdjListIn)[to].empty()) {
        cachedAdjListIn->erase(to);
      }
    }

    // If the edge is just he base class Edge it is treated as an undirected
    // edge
    if (!edgeOpt.value().get()->isDirected().value_or(false)) {
      delIndex = -1;
      i = 0;
      for (auto elem : (*cachedAdjListOut)[to]) {
        if (elem.second.get()->getId() == edgeId) {
          delIndex = i;
          break;
        }
        i++;
      }
      if (delIndex != -1) {
        (*cachedAdjListOut)[to].erase((*cachedAdjListOut)[to].begin() +
                                      delIndex);
        if ((*cachedAdjListOut)[to].empty()) {
          cachedAdjListOut->erase(to);
        }
      }

      delIndex = -1;
      i = 0;
      for (auto elem : (*cachedAdjListIn)[from]) {
        if (elem.second.get()->getId() == edgeId) {
          delIndex = i;
          break;
        }
        i++;
      }
      if (delIndex != -1) {
        (*cachedAdjListIn)[from].erase((*cachedAdjListIn)[from].begin() +
                                       delIndex);
        if ((*cachedAdjListIn)[from].empty()) {
          cachedAdjListIn->erase(from);
        }
      }
    }
  }
}

template <typename T>
void Graph<T>::removeNode(const std::string &nodeUserId) {
  auto nodeOpt = getNode(nodeUserId);
  if (nodeOpt.has_value()) {
    auto isolatedNodeIt = isolatedNodesSet.find(nodeOpt.value());
    if (isolatedNodeIt != isolatedNodesSet.end()) {
      // The node is isolated
      isolatedNodesSet.erase(isolatedNodeIt);
    } else {
      // The node is not isolated
      // Remove the edges containing the node
      auto edgeIt = edgeSet.begin();
      auto nextIt = edgeIt;
      while (edgeIt != edgeSet.end()) {
        nextIt = std::next(edgeIt);
        if ((*edgeIt)->getNodePair().first->getUserId() == nodeUserId ||
            (*edgeIt)->getNodePair().second->getUserId() == nodeUserId) {
          this->removeEdge((*edgeIt)->getId());
        }
        edgeIt = nextIt;
      }
    }
  }
}

template <typename T>
bool Graph<T>::findEdge(const Node<T> *v1, const Node<T> *v2,
                        CXXGraph::id_t &id) const {
  auto v1_shared = make_shared<const Node<T>>(*v1);
  auto v2_shared = make_shared<const Node<T>>(*v2);

  return findEdge(v1_shared, v2_shared, id);
}

template <typename T>
bool Graph<T>::findEdge(shared<const Node<T>> v1, shared<const Node<T>> v2,
                        CXXGraph::id_t &id) const {
  // This could be made faster by looking for the edge hash, assuming we hash
  // based on node data, instead of a unique integer
  if (cachedAdjListOut.get() != NULL && cachedAdjListOut->size() != 0) {
    /* Searching for the edge using cached adjacency list out */

    for (auto elem : (*cachedAdjListOut)[v1]) {
      if (elem.first == v2) {
        id = elem.second.get()->getId();
        return true;
      }
    }
  } else {
    /* Searching for the edge using edgeset */

    for (auto e : this->edgeSet) {
      if ((e->getNodePair().first == v1) && (e->getNodePair().second == v2)) {
        id = e->getId();
        return true;
      }
      if (!e->isDirected() &&
          ((e->getNodePair().second == v1) && (e->getNodePair().first == v2))) {
        id = e->getId();
        return true;
      }
    }
  }
  id = 0;
  return false;
}

template <typename T>
const T_NodeSet<T> Graph<T>::getNodeSet() const {
  T_NodeSet<T> nodeSet;

  for (const auto &adjListInIt : *cachedAdjListIn) {
    nodeSet.insert(adjListInIt.first);
  }

  for (const auto &adjListOutIt : *cachedAdjListOut) {
    nodeSet.insert(adjListOutIt.first);
  }

  // Add the isolated nodes
  nodeSet.insert(isolatedNodesSet.begin(), isolatedNodesSet.end());

  return nodeSet;
}

template <typename T>
const T_NodeVector<T> Graph<T>::getNodeVector() const {
  auto &nodeSet = getNodeSet();
  T_NodeVector<T> nodeVector(nodeSet.begin(), nodeSet.end());

  return nodeVector;
}

template <typename T>
const T_NodeSet<T> Graph<T>::getIsolatedNodeSet() const {
  return isolatedNodesSet;
}

template <typename T>
void Graph<T>::setNodeData(const std::string &nodeUserId, T data) {
  auto nodeSet = this->nodeSet();
  auto nodeIt = std::find_if(
      nodeSet.begin(), nodeSet.end(),
      [&nodeUserId](auto node) { return node->getUserId() == nodeUserId; });
  std::const_pointer_cast<Node<T>>(*nodeIt)->setData(std::move(data));
}

template <typename T>
void Graph<T>::setNodeData(std::map<std::string, T> &dataMap) {
  // Construct the set of all the nodes in the graph
  for (auto &nodeSetIt : this->nodeSet()) {
    nodeSetIt->setData(std::move(dataMap[nodeSetIt->getUserId()]));
  }
}

template <typename T>
const std::optional<shared<const Edge<T>>> Graph<T>::getEdge(
    const CXXGraph::id_t edgeId) const {
  for (const auto &it : edgeSet) {
    if (it->getId() == edgeId) {
      return it;
    }
  }

  return std::nullopt;
}

template <typename T>
const std::optional<shared<const Node<T>>> Graph<T>::getNode(
    const std::string &nodeUserId) const {
  for (const auto &it : getNodeSet()) {
    if (it->getUserId() == nodeUserId) {
      return it;
    }
  }

  return std::nullopt;
}

template <typename T>
std::unordered_set<shared<Node<T>>, nodeHash<T>> Graph<T>::nodeSet() {
  std::unordered_set<shared<Node<T>>, nodeHash<T>> nodeSet;

  for (const auto &adjListInIt : *cachedAdjListIn) {
    nodeSet.insert(std::const_pointer_cast<Node<T>>(adjListInIt.first));
  }

  for (const auto &adjListOutIt : *cachedAdjListOut) {
    nodeSet.insert(std::const_pointer_cast<Node<T>> (adjListOutIt.first));
  }

  for (auto &isNodeIt : isolatedNodesSet) {
    nodeSet.insert(std::const_pointer_cast<Node<T>>(isNodeIt));
  }

  return nodeSet;
}

template <typename T>
CXXGraph::id_t Graph<T>::setFind(
    std::unordered_map<CXXGraph::id_t, Subset> *subsets,
    const CXXGraph::id_t nodeId) const {
  auto subsets_ptr =
      make_shared<std::unordered_map<CXXGraph::id_t, Subset>>(*subsets);
  // find root and make root as parent of i
  // (path compression)
  if ((*subsets)[nodeId].parent != nodeId) {
    (*subsets)[nodeId].parent =
        Graph<T>::setFind(subsets_ptr, (*subsets)[nodeId].parent);
  }

  return (*subsets)[nodeId].parent;
}

template <typename T>
CXXGraph::id_t Graph<T>::setFind(
    shared<std::unordered_map<CXXGraph::id_t, Subset>> subsets,
    const CXXGraph::id_t nodeId) const {
  // find root and make root as parent of i
  // (path compression)
  if ((*subsets)[nodeId].parent != nodeId) {
    (*subsets)[nodeId].parent =
        Graph<T>::setFind(subsets, (*subsets)[nodeId].parent);
  }

  return (*subsets)[nodeId].parent;
}

template <typename T>
void Graph<T>::setUnion(std::unordered_map<CXXGraph::id_t, Subset> *subsets,
                        const CXXGraph::id_t elem1,
                        const CXXGraph::id_t elem2) const {
  /* auto subsets_ptr = make_shared<std::unordered_map<CXXGraph::id_t,
   * Subset>>(*subsets); */
  // if both sets have same parent
  // then there's nothing to be done
  /* if ((*subsets_ptr)[elem1].parent == (*subsets_ptr)[elem2].parent) return;
   */
  /* auto elem1Parent = Graph<T>::setFind(subsets_ptr, elem1); */
  /* auto elem2Parent = Graph<T>::setFind(subsets_ptr, elem2); */
  /* if ((*subsets_ptr)[elem1Parent].rank < (*subsets_ptr)[elem2Parent].rank) */
  /*   (*subsets_ptr)[elem1].parent = elem2Parent; */
  /* else if ((*subsets_ptr)[elem1Parent].rank >
   * (*subsets_ptr)[elem2Parent].rank) */
  /*   (*subsets_ptr)[elem2].parent = elem1Parent; */
  /* else { */
  /*   (*subsets_ptr)[elem2].parent = elem1Parent; */
  /*   (*subsets_ptr)[elem1Parent].rank++; */
  /* } */
  if ((*subsets)[elem1].parent == (*subsets)[elem2].parent) return;
  auto elem1Parent = Graph<T>::setFind(subsets, elem1);
  auto elem2Parent = Graph<T>::setFind(subsets, elem2);
  if ((*subsets)[elem1Parent].rank < (*subsets)[elem2Parent].rank)
    (*subsets)[elem1].parent = elem2Parent;
  else if ((*subsets)[elem1Parent].rank > (*subsets)[elem2Parent].rank)
    (*subsets)[elem2].parent = elem1Parent;
  else {
    (*subsets)[elem2].parent = elem1Parent;
    (*subsets)[elem1Parent].rank++;
  }
}

template <typename T>
void Graph<T>::setUnion(
    shared<std::unordered_map<CXXGraph::id_t, Subset>> subsets,
    const CXXGraph::id_t elem1, const CXXGraph::id_t elem2) const {
  // if both sets have same parent
  // then there's nothing to be done
  if ((*subsets)[elem1].parent == (*subsets)[elem2].parent) return;
  auto elem1Parent = Graph<T>::setFind(subsets, elem1);
  auto elem2Parent = Graph<T>::setFind(subsets, elem2);
  if ((*subsets)[elem1Parent].rank < (*subsets)[elem2Parent].rank)
    (*subsets)[elem1].parent = elem2Parent;
  else if ((*subsets)[elem1Parent].rank > (*subsets)[elem2Parent].rank)
    (*subsets)[elem2].parent = elem1Parent;
  else {
    (*subsets)[elem2].parent = elem1Parent;
    (*subsets)[elem1Parent].rank++;
  }
}

template <typename T>
shared<AdjacencyList<T>> Graph<T>::getAdjListOut() const {
  auto adj = std::make_shared<AdjacencyList<T>>();
  auto addElementToAdjList = [&adj](shared<const Node<T>> nodeFrom,
                                    shared<const Node<T>> nodeTo,
                                    shared<const Edge<T>> edge) {
    std::pair<shared<const Node<T>>, shared<const Edge<T>>> elem = {nodeTo,
                                                                    edge};
    (*adj)[nodeFrom].push_back(std::move(elem));
  };
  for (const auto &edgeSetIt : edgeSet) {
    shared<const Edge<T>> edge =
        std::static_pointer_cast<const Edge<T>>(edgeSetIt);

    addElementToAdjList(edge->getNodePair().first, edge->getNodePair().second,
                        edge);

    // If the type is the base Edge type then it is treated as an undirected
    // edge
    if (!edgeSetIt->isDirected().value_or(false))
      addElementToAdjList(edge->getNodePair().second, edge->getNodePair().first,
                          edge);
  }
  return adj;
}

template <typename T>
shared<AdjacencyList<T>> Graph<T>::getAdjListIn() const {
  auto adj = std::make_shared<AdjacencyList<T>>();
  auto addElementToAdjList = [&adj](shared<const Node<T>> nodeFrom,
                                    shared<const Node<T>> nodeTo,
                                    shared<const Edge<T>> edge) {
    std::pair<shared<const Node<T>>, shared<const Edge<T>>> elem = {nodeFrom,
                                                                    edge};
    (*adj)[nodeTo].push_back(std::move(elem));
  };
  for (const auto &edgeSetIt : edgeSet) {
    shared<const Edge<T>> edge =
        std::static_pointer_cast<const Edge<T>>(edgeSetIt);

    addElementToAdjList(edge->getNodePair().first, edge->getNodePair().second,
                        edge);

    // If the type is the base Edge type then it is treated as an undirected
    // edge
    if (!edgeSetIt->isDirected().value_or(false))
      addElementToAdjList(edge->getNodePair().second, edge->getNodePair().first,
                          edge);
  }
  return adj;
}

template <typename T>
void Graph<T>::cacheAdjLists() {
  const auto adjOut = getAdjListOut();
  this->cachedAdjListOut = adjOut;

  const auto adjIn = getAdjListIn();
  this->cachedAdjListIn = adjIn;
}

template <typename T>
shared<DegreeMatrix<T>> Graph<T>::getDegreeMatrix() const {
  auto degreeMatrix = std::make_shared<DegreeMatrix<T>>();

  for (const auto &nodePair : *this->cachedAdjListOut) {
    const shared<const Node<T>> &node = nodePair.first;
    const std::vector<std::pair<shared<const Node<T>>, shared<const Edge<T>>>>
        &neighbors = nodePair.second;

    (*degreeMatrix)[node] = neighbors.size();
  }

  return degreeMatrix;
}

template <typename T>
void Graph<T>::cacheDegreeMatrix() {
  const auto degreeMatrix = Graph<T>::getDegreeMatrix();
  this->cachedDegreeMatrix = degreeMatrix;
}

template <typename T>
shared<LaplacianMatrix<T>> Graph<T>::getLaplacianMatrix() const {
  const auto AdjacencyList = this->cachedAdjListOut;
  const auto degreeMatrix = this->cachedDegreeMatrix;

  auto laplacianMatrix = std::make_shared<LaplacianMatrix<T>>();
  for (const auto &nodePair : *AdjacencyList) {
    const shared<const Node<T>> &node = nodePair.first;
    (*laplacianMatrix)[node] =
        std::vector<std::pair<shared<const Node<T>>, shared<const Edge<T>>>>();
  }

  for (const auto &nodePair : *AdjacencyList) {
    const shared<const Node<T>> &node = nodePair.first;
    const std::vector<std::pair<shared<const Node<T>>, shared<const Edge<T>>>>
        &neighbors = nodePair.second;

    (*laplacianMatrix)[node].emplace_back(node,
                                          nullptr);  // Insere o nó na diagonal
    for (const auto &neighborPair : neighbors) {
      const shared<const Node<T>> &neighbor = neighborPair.first;
      (*laplacianMatrix)[node].emplace_back(
          neighbor, neighborPair.second);  // Insere os pares de vizinhos
    }
  }

  return laplacianMatrix;
}

template <typename T>
void Graph<T>::cacheLaplacianMatrix() {
  const auto laplacianMatrix = Graph<T>::getLaplacianMatrix();
  this->cachedLaplacianMatrix = laplacianMatrix;
}

template <typename T>
void Graph<T>::invalidateCache(bool includeTransitionMatrix) {
  cacheAdjLists();
  cacheDegreeMatrix();
  cacheLaplacianMatrix();

  if (includeTransitionMatrix) {
    cacheTransitionMatrix();
  }
}

template <typename T>
shared<TransitionMatrix<T>> Graph<T>::getTransitionMatrix() const {
  const auto AdjacencyList = this->cachedAdjListOut;

  auto transitionMatrix = std::make_shared<TransitionMatrix<T>>();
  for (const auto &nodePair : *AdjacencyList) {
    const shared<const Node<T>> &node = nodePair.first;
    (*transitionMatrix)[node] =
        std::vector<std::pair<shared<const Node<T>>, double>>();
  }

  for (const auto &nodePair : *AdjacencyList) {
    const shared<const Node<T>> &node = nodePair.first;
    const std::vector<std::pair<shared<const Node<T>>, shared<const Edge<T>>>>
        &neighbors = nodePair.second;

    int degree = (int)neighbors.size();

    double transitionProbability = 1.0 / degree;

    for (const auto &neighborPair : neighbors) {
      const shared<const Node<T>> &neighbor = neighborPair.first;
      (*transitionMatrix)[node].emplace_back(neighbor, transitionProbability);
    }
  }

  return transitionMatrix;
}

template <typename T>
void Graph<T>::cacheTransitionMatrix() {
  const auto transitionMatrix = Graph<T>::getTransitionMatrix();
  this->cachedTransitionMatrix = transitionMatrix;
}

template <typename T>
const std::unordered_set<shared<const Node<T>>, nodeHash<T>>
Graph<T>::outNotInNeighbors(const Node<T> *node) const {
  auto node_shared = make_shared<const Node<T>>(*node);

  return outNotInNeighbors(node_shared);
}

template <typename T>
const std::unordered_set<shared<const Node<T>>, nodeHash<T>>
Graph<T>::outNotInNeighbors(shared<const Node<T>> node) const {
  if (cachedAdjListOut->find(node) == cachedAdjListOut->end()) {
    return std::unordered_set<shared<const Node<T>>, nodeHash<T>>();
  }
  auto nodeEdgePairsOut = cachedAdjListOut->at(node);

  std::unordered_set<shared<const Node<T>>, nodeHash<T>> outNotInNeighbors;
  for (auto pair : nodeEdgePairsOut) {
    if (pair.second->isDirected().value_or(false)) {
      outNotInNeighbors.insert(pair.first);
    }
  }

  return outNotInNeighbors;
}

template <typename T>
const std::unordered_set<shared<const Node<T>>, nodeHash<T>>
Graph<T>::inNotOutNeighbors(const Node<T> *node) const {
  auto node_shared = make_shared<const Node<T>>(*node);

  return inNotOutNeighbors(node_shared);
}

template <typename T>
const std::unordered_set<shared<const Node<T>>, nodeHash<T>>
Graph<T>::inNotOutNeighbors(shared<const Node<T>> node) const {
  if (cachedAdjListIn->find(node) == cachedAdjListIn->end()) {
    return std::unordered_set<shared<const Node<T>>, nodeHash<T>>();
  }
  auto nodeEdgePairsIn = cachedAdjListIn->at(node);

  std::unordered_set<shared<const Node<T>>, nodeHash<T>> inNotOutNeighbors;
  for (auto pair : nodeEdgePairsIn) {
    if (pair.second->isDirected().value_or(false)) {
      inNotOutNeighbors.insert(pair.first);
    }
  }

  return inNotOutNeighbors;
}

template <typename T>
const std::unordered_set<shared<const Node<T>>, nodeHash<T>>
Graph<T>::inOrOutNeighbors(const Node<T> *node) const {
  auto node_shared = make_shared<const Node<T>>(*node);

  return inOrOutNeighbors(node_shared);
}

template <typename T>
const std::unordered_set<shared<const Node<T>>, nodeHash<T>>
Graph<T>::inOrOutNeighbors(shared<const Node<T>> node) const {
  if (cachedAdjListOut->find(node) == cachedAdjListOut->end() &&
      cachedAdjListIn->find(node) == cachedAdjListIn->end()) {
    return std::unordered_set<shared<const Node<T>>, nodeHash<T>>();
  }

  std::unordered_set<shared<const Node<T>>, nodeHash<T>> inOrOutNeighbors;
  if (cachedAdjListOut->find(node) != cachedAdjListOut->end()) {
    auto nodeEdgePairsOut = cachedAdjListOut->at(node);
    for (auto pair : nodeEdgePairsOut) {
      inOrOutNeighbors.insert(pair.first);
    }
  }
  if (cachedAdjListIn->find(node) != cachedAdjListIn->end()) {
    auto nodeEdgePairsIn = cachedAdjListIn->at(node);
    for (auto pair : nodeEdgePairsIn) {
      inOrOutNeighbors.insert(pair.first);
    }
  }

  return inOrOutNeighbors;
}

template <typename T>
const std::unordered_set<shared<const Edge<T>>, edgeHash<T>>
Graph<T>::outNotInEdges(const Node<T> *node) const {
  auto node_shared = make_shared<const Node<T>>(*node);

  return outNotInEdges(node_shared);
}

template <typename T>
const std::unordered_set<shared<const Edge<T>>, edgeHash<T>>
Graph<T>::outNotInEdges(shared<const Node<T>> node) const {
  if (cachedAdjListOut->find(node) == cachedAdjListOut->end()) {
    return std::unordered_set<shared<const Edge<T>>, edgeHash<T>>();
  }
  auto nodeEdgePairsOut = cachedAdjListOut->at(node);

  std::unordered_set<shared<const Edge<T>>, edgeHash<T>> outNotInEdges;
  for (auto pair : nodeEdgePairsOut) {
    if (pair.second->isDirected().value_or(false)) {
      outNotInEdges.insert(pair.second);
    }
  }

  return outNotInEdges;
}

template <typename T>
const std::unordered_set<shared<const Edge<T>>, edgeHash<T>>
Graph<T>::inNotOutEdges(const Node<T> *node) const {
  auto node_shared = make_shared<const Node<T>>(*node);

  return inNotOutEdges(node_shared);
}

template <typename T>
const std::unordered_set<shared<const Edge<T>>, edgeHash<T>>
Graph<T>::inNotOutEdges(shared<const Node<T>> node) const {
  if (cachedAdjListIn->find(node) == cachedAdjListIn->end()) {
    return std::unordered_set<shared<const Edge<T>>, edgeHash<T>>();
  }
  auto nodeEdgePairsIn = cachedAdjListIn->at(node);

  std::unordered_set<shared<const Edge<T>>, edgeHash<T>> inNotOutEdges;
  for (auto pair : nodeEdgePairsIn) {
    if (pair.second->isDirected().value_or(false)) {
      inNotOutEdges.insert(pair.second);
    }
  }

  return inNotOutEdges;
}

template <typename T>
const std::unordered_set<shared<const Edge<T>>, edgeHash<T>>
Graph<T>::inOrOutEdges(const Node<T> *node) const {
  auto node_shared = make_shared<const Node<T>>(*node);

  return inOrOutEdges(node_shared);
}

template <typename T>
const std::unordered_set<shared<const Edge<T>>, edgeHash<T>>
Graph<T>::inOrOutEdges(shared<const Node<T>> node) const {
  if (cachedAdjListOut->find(node) == cachedAdjListOut->end() &&
      cachedAdjListIn->find(node) == cachedAdjListIn->end()) {
    return std::unordered_set<shared<const Edge<T>>, edgeHash<T>>();
  }

  std::unordered_set<shared<const Edge<T>>, edgeHash<T>> inOrOutEdges;
  if (cachedAdjListOut->find(node) != cachedAdjListOut->end()) {
    auto nodeEdgePairsOut = cachedAdjListOut->at(node);
    for (auto pair : nodeEdgePairsOut) {
      inOrOutEdges.insert(pair.second);
    }
  }
  if (cachedAdjListIn->find(node) != cachedAdjListIn->end()) {
    auto nodeEdgePairsIn = cachedAdjListIn->at(node);
    for (auto pair : nodeEdgePairsIn) {
      inOrOutEdges.insert(pair.second);
    }
  }

  return inOrOutEdges;
}

template <typename T>
bool Graph<T>::isDirectedGraph() const {
  auto edgeSet = getEdgeSet();
  for (const auto &edge : edgeSet) {
    if (!(edge->isDirected().has_value() && edge->isDirected().value())) {
      // Found Undirected Edge
      return false;
    }
  }
  // No Undirected Edge
  return true;
}

template <typename T>
bool Graph<T>::isUndirectedGraph() const {
  auto edgeSet = Graph<T>::getEdgeSet();
  for (const auto &edge : edgeSet) {
    if ((edge->isDirected().has_value() && edge->isDirected().value())) {
      // Found Directed Edge
      return false;
    }
  }
  // No Directed Edge
  return true;
}

template <typename T>
void Graph<T>::reverseDirectedGraph() {
  if (!isDirectedGraph()) {
    throw std::runtime_error(ERR_UNDIR_GRAPH);
  }
  auto oldEdgeSet = Graph<T>::getEdgeSet();
  for (const auto &edge : oldEdgeSet) {
    auto &[first, second] = edge->getNodePair();
    auto id = edge->getId();
    this->removeEdge(id);
    auto newEdge = std::make_shared<DirectedEdge<T>>(id, second, first);
    this->addEdge(newEdge);
  }
}

template <typename T>
const std::vector<Node<T>> Graph<T>::graph_slicing(const Node<T> &start) const {
  std::vector<Node<T>> result;

  auto nodeSet = Graph<T>::getNodeSet();
  // check if start node in the graph
  auto start_node_it = std::find_if(
      nodeSet.begin(), nodeSet.end(),
      [&start](auto node) { return node->getUserId() == start.getUserId(); });
  if (start_node_it == nodeSet.end()) {
    return result;
  }
  std::vector<Node<T>> C = Graph<T>::depth_first_search(start);
  std::deque<shared<const Node<T>>> C1;  // complement of C i.e. nodeSet - C
  for (auto const &node : nodeSet) {
    // from the set of all nodes, remove nodes that exist in C
    if (std::find_if(C.begin(), C.end(), [node](const Node<T> nodeC) {
          return (*node == nodeC);
        }) == C.end())
      C1.push_back(node);
  }

  // For all nodes in C', apply DFS
  //  and get the list of reachable nodes and store in M
  std::vector<Node<T>> M;
  for (auto const &node : C1) {
    std::vector<Node<T>> reachableNodes = Graph<T>::depth_first_search(*node);
    M.insert(M.end(), reachableNodes.begin(), reachableNodes.end());
  }
  // removes nodes from C that are reachable from M.
  for (const auto &nodeC : C) {
    if (std::find_if(M.begin(), M.end(), [nodeC](const Node<T> nodeM) {
          return (nodeM == nodeC);
        }) == M.end())
      result.push_back(nodeC);
  }
  return result;
}

}  // namespace CXXGraph
#endif  // __CXXGRAPH_GRAPH_IMPL_H__
