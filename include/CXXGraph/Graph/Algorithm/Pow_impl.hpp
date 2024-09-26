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

#ifndef __CXXGRAPH_POW_IMPL_H__
#define __CXXGRAPH_POW_IMPL_H__

#pragma once

#include "CXXGraph/Graph/Graph_decl.h"

template <typename T>
std::vector<std::vector<T>> matMult(std::vector<std::vector<T>> &a,
                                    std::vector<std::vector<T>> &b) {
  static_assert(std::is_arithmetic<T>::value,
                "Type T must be either unsigned long long or double");

  int n = static_cast<int>(a.size());  // N x N matrix
  std::vector<std::vector<T>> res(n, std::vector<T>(n, 0));

  // O(n^3) matrix multiplication
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      for (int k = 0; k < n; k++) {
        res[i][j] += a[i][k] * b[k][j];
      }
    }
  }

  return res;
}

/**
 * @brief exponentation takes a matrix of arithmetic type and
 * raises it to the power of k.
 * @param mat a square matrix
 * @param k a nonnegative integer
 * @return M, the result of mat^k
 */
template <typename T>
std::vector<std::vector<T>> exponentiation(std::vector<std::vector<T>> &mat,
                                           unsigned int k) {
  static_assert(std::is_arithmetic<T>::value,
                "Type T must be any arithmetic type");

  // validate size and shape of matrix
  if (mat.size() == 0 || mat.size() != mat[0].size()) {
    throw std::invalid_argument("Matrix must be square and at least 1x1.");
  }

  int n = static_cast<int>(mat.size());
  std::vector<std::vector<T>> res(n, std::vector<T>(n, 0));

  // build identity matrix
  for (int i = 0; i < n; i++) res[i][i] = 1;

  // fast exponentiation!
  while (k) {
    if (k & 1) res = matMult(res, mat);
    mat = matMult(mat, mat);
    k >>= 1;
  }

  return res;
}

namespace CXXGraph {

/**
 * @brief This function raises the adjacency matrix to some k.
 * Best used for counting number of k-length walks from i to j.
 * @param k value by which to raise matrix
 * @return (success, errorMessage, matrix): where matrix is equivalent to A^k
 */
template <typename T>
const PowAdjResult matrixPow(const shared<AdjacencyMatrix<T>> &adj,
                             unsigned int k) {
  PowAdjResult result;
  result.success = false;
  result.errorMessage = "";
  std::unordered_map<std::pair<std::string, std::string>, unsigned long long,
                     CXXGraph::pair_hash>
      powAdj;

  // convert back and forth between user ids and index in temporary adj matrix
  std::unordered_map<std::string, int> userIdToIdx;
  std::unordered_map<int, std::string> idxToUserId;

  int n = 0;
  for (const auto &[node, list] : *adj) {
    userIdToIdx[node->getUserId()] = n;
    idxToUserId[n] = node->getUserId();
    n++;
  }

  // adj int will store the temporary (integer) adjacency matrix
  std::vector<std::vector<unsigned long long>> tempIntAdj(
      n, std::vector<unsigned long long>(n, 0));

  // populate temporary adjacency matrix w/ edges
  // can handle both directed and undirected
  for (const auto &[node, edges] : *adj) {
    for (const auto &e : edges) {
      const auto edge = e.second->getNodePair();
      const auto firstId = edge.first->getUserId();
      const auto secondId = edge.second->getUserId();

      // if undirected, add both sides
      if (!(e.second->isDirected().has_value() &&
            e.second->isDirected().value()))
        tempIntAdj[userIdToIdx[secondId]][userIdToIdx[firstId]] = 1;
      tempIntAdj[userIdToIdx[firstId]][userIdToIdx[secondId]] = 1;
    }
  }

  // calculate the power matrix
  auto powerMatrix = exponentiation(tempIntAdj, k);

  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      auto pr = std::make_pair(idxToUserId[i], idxToUserId[j]);
      powAdj[pr] = powerMatrix[i][j];
    }
  }

  result.result = std::move(powAdj);
  result.success = true;

  return result;
}

/**
 * @brief This function raises a transition matrix to some k.
 * Best used for finding equilibrium.
 * @param k value by which to raise matrix
 * @return (success, errorMessage, matrix): where matrix is equivalent to S^k
 */
template <typename T>
const PowTransResult matrixPow(const shared<TransitionMatrix<T>> &trans,
                               unsigned int k) {
  PowTransResult result;
  result.success = false;
  result.errorMessage = "";
  std::unordered_map<std::pair<std::string, std::string>, double,
                     CXXGraph::pair_hash>
      powTrans;

  std::unordered_map<std::string, int> userIdToIdx;
  std::unordered_map<int, std::string> idxToUserId;

  // get a map between index in adj matrix
  // and userId
  int n = 0;
  for (const auto &[node, list] : *trans) {
    userIdToIdx[node->getUserId()] = n;
    idxToUserId[n] = node->getUserId();
    n++;
  }

  std::vector<std::vector<double>> tempDoubleTrans(n,
                                                   std::vector<double>(n, 0));

  // given transition matrix, convert it to
  // stochastic matrix
  for (const auto &it : *trans) {
    const auto f = it.first;
    const auto idx = userIdToIdx[f->getUserId()];

    for (const auto &e : it.second) {
      const auto idx2 = userIdToIdx[e.first->getUserId()];
      tempDoubleTrans[idx][idx2] = e.second;
    }
  }

  // exponentiate stochastic matrix
  auto powerTransMatrix = exponentiation(tempDoubleTrans, k);

  // turn back into a map between nodes
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      auto pr = std::make_pair(idxToUserId[i], idxToUserId[j]);
      powTrans[pr] = powerTransMatrix[i][j];
    }
  }

  result.result = std::move(powTrans);
  result.success = true;

  return result;
}
}  // namespace CXXGraph

#endif  //_CXXGRAPH_POW_IMPL_H__