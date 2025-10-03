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

#ifndef __CXXGRAPH_EDGE_IMPL_H__
#define __CXXGRAPH_EDGE_IMPL_H__

#pragma once

#include "CXXGraph/Edge/Edge_decl.h"

namespace CXXGraph {
// Smart pointers alias
template <typename T>
using unique = std::unique_ptr<T>;
template <typename T>
using shared = std::shared_ptr<T>;

using std::make_shared;
using std::make_unique;

template <typename T>
Edge<T>::Edge(const std::string &userId, const Node<T> &node1,
              const Node<T> &node2) {
  this->nodePair.first = make_shared<const Node<T>>(node1);
  this->nodePair.second = make_shared<const Node<T>>(node2);
  this->userId = userId;
  setId(userId);
}

template <typename T>
Edge<T>::Edge(const std::string &userId, shared<const Node<T>> node1,
              shared<const Node<T>> node2) {
  this->nodePair.first = node1;
  this->nodePair.second = node2;
  this->userId = userId;
  setId(userId);
}

template <typename T>
Edge<T>::Edge(const std::string &userId,
              const std::pair<const Node<T> *, const Node<T> *> &nodepair) {
  this->nodePair.first = make_shared<const Node<T>>(*(nodepair.first));
  this->nodePair.second = make_shared<const Node<T>>(*(nodepair.second));
  this->userId = userId;
  setId(userId);
}

template <typename T>
Edge<T>::Edge(
    const std::string &userId,
    const std::pair<shared<const Node<T>>, shared<const Node<T>>> &nodepair)
    : nodePair(nodepair) {
  this->userId = userId;
  setId(userId);
}

template <typename T>
void Edge<T>::setId(const std::string &inpId) {
  this->id = std::hash<std::string>{}(inpId);
}

template <typename T>
void Edge<T>::setFirstNode(shared<const Node<T>> node) {
  /* this->nodePair = std::make_pair(node, this->nodePair.second); */
  this->nodePair.first = node;
}

template <typename T>
void Edge<T>::setSecondNode(shared<const Node<T>> node) {
  /* this->nodePair = std::make_pair(this->nodePair.first, node); */
  this->nodePair.second = node;
}

template <typename T>
CXXGraph::id_t Edge<T>::getId() const {
  return id;
}

template <typename T>
const std::string &Edge<T>::getUserId() const {
  return userId;
}

template <typename T>
const std::pair<shared<const Node<T>>, shared<const Node<T>>> &
Edge<T>::getNodePair() const {
  return nodePair;
}

template <typename T>
shared<const Node<T>> Edge<T>::getOtherNode(shared<const Node<T>> node) const {
  if (this->getNodePair().first == node) {
    return this->getNodePair().second;
  } else {
    return this->getNodePair().first;
  }
}

template <typename T>
const std::optional<bool> Edge<T>::isDirected() const {
  return std::nullopt;
}

template <typename T>
const std::optional<bool> Edge<T>::isWeighted() const {
  return std::nullopt;
}

template <typename T>
bool Edge<T>::operator==(const Edge<T> &b) const {
  return (this->id == b.id && this->nodePair == b.nodePair);
}

template <typename T>
bool Edge<T>::operator<(const Edge<T> &b) const {
  return (this->id < b.id);
}

template <typename T>
std::ostream &operator<<(std::ostream &os, const Edge<T> &edge) {
  os << "((Node: " << edge.nodePair.first->getId()
     << ")) ?----- |Edge: " << edge.id
     << "|-----? ((Node: " << edge.nodePair.second->getId() << "))";
  return os;
}
}  // namespace CXXGraph

#endif  // __CXXGRAPH_EDGE_IMPL_H__
