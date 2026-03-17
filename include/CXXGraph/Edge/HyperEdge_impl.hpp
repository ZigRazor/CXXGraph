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

#ifndef CXXGRAPH_HYPEREDGE_IMPL_HPP_
#define CXXGRAPH_HYPEREDGE_IMPL_HPP_

#pragma once

#include <ostream>
#include <string>
#include <utility>

#include "CXXGraph/Edge/HyperEdge_decl.h"

namespace CXXGraph {

// ── HyperEdge<T> private helper ─────────────────────────────────────────────

template <typename T>
void HyperEdge<T>::setId(const std::string& s) noexcept {
  // Mirror the hashing convention used by Edge<T> and Node<T>
  id_ = std::hash<std::string>{}(s);
}

// ── HyperEdge<T> constructors ────────────────────────────────────────────────

template <typename T>
HyperEdge<T>::HyperEdge(const std::string& userId,
                         std::vector<shared<const Node<T>>> nodes)
    : userId_(userId), nodes_(std::move(nodes)) {
  setId(userId_);
}

template <typename T>
HyperEdge<T>::HyperEdge(const std::string& userId,
                         std::initializer_list<shared<const Node<T>>> nodes)
    : userId_(userId), nodes_(nodes) {
  setId(userId_);
}

// ── HyperEdge<T>::contains ───────────────────────────────────────────────────

template <typename T>
bool HyperEdge<T>::contains(
    const shared<const Node<T>>& node) const noexcept {
  for (const auto& n : nodes_) {
    if (n->getId() == node->getId()) return true;
  }
  return false;
}

template <typename T>
bool HyperEdge<T>::contains(const std::string& nodeUserId) const noexcept {
  for (const auto& n : nodes_) {
    if (n->getUserId() == nodeUserId) return true;
  }
  return false;
}

// ── HyperEdge<T> stream operator ────────────────────────────────────────────

template <typename T>
std::ostream& operator<<(std::ostream& os, const HyperEdge<T>& he) {
  os << "HyperEdge #" << he.userId_ << " {";
  for (std::size_t i = 0; i < he.nodes_.size(); ++i) {
    os << he.nodes_[i]->getUserId();
    if (i + 1 < he.nodes_.size()) os << ", ";
  }
  os << "}";
  if (he.isWeighted() && he.getWeight().has_value()) {
    os << " W:" << he.getWeight().value();
  }
  return os;
}

// ── WeightedHyperEdge<T> constructor ────────────────────────────────────────

template <typename T>
WeightedHyperEdge<T>::WeightedHyperEdge(
    const std::string& userId,
    std::vector<shared<const Node<T>>> nodes,
    double weight)
    : HyperEdge<T>(userId, std::move(nodes)), weight_(weight) {}

}  // namespace CXXGraph

#endif  // CXXGRAPH_HYPEREDGE_IMPL_HPP_
