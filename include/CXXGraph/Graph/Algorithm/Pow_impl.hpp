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
std::vector<std::vector<T>> matMult(std::vector<std::vector<T>> &a, std::vector<std::vector<T>> &b) {
    static_assert(std::is_same<T, unsigned long long>::value || std::is_same<T, double>::value,
                  "Type T must be either unsigned long long or double");

    int n = (int)a.size(); // N x N matrix
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

template <typename T>
std::vector<std::vector<T>> exponentiation(std::vector<std::vector<T>> &mat, unsigned int k) {
    // typechecking
    static_assert(std::is_same<T, unsigned long long>::value || std::is_same<T, double>::value,
                  "Type T must be either unsigned long long or double");

    int n = (int)mat.size();
    std::vector<std::vector<T>> res(n, std::vector<T>(n, 0)); 

    // build identity matrix    
    for (int i = 0; i < n; i++) res[i][i] = 1;

    // fast exponentation!
    while (k) {
        if (k & 1) res = matMult(res, mat);
        mat = matMult(mat, mat);
        k >>= 1;
    }

    return res;
}

namespace CXXGraph {
    
template <typename T>
const PowAdjResult Graph<T>::powAdjMatrix(unsigned int k) const {
    PowAdjResult result;
    result.success = false;
    result.errorMessage = "";
    std::unordered_map<std::pair<std::string, std::string>, unsigned long long,
                        CXXGraph::pair_hash> powAdj;

    // get graph sets
    const auto &nodeSet = Graph<T>::getNodeSet();
    const auto &edgeSet = Graph<T>::getEdgeSet();

    int n = (int)nodeSet.size();

    // convert back and forth between user id's and index in temporary adj matrix
    std::unordered_map<std::string, int> userIdToIdx;
    std::unordered_map<int, std::string> idxToUserId;
    
    // adj int will store the temporary (integer) adjacency matrix
    std::vector<std::vector<unsigned long long>> tempIntAdj(n, std::vector<unsigned long long>(n, 0));

    // write forwards and backwards mapping
    int i = 0;
    for (const auto &node : nodeSet) { 
        userIdToIdx[node->getUserId()] = i;
        idxToUserId[i] = node->getUserId();
        i++;
    }

    // populated temporary adjacency matrix w/ edges
    // can handle both directed and undirected
    for (const auto &e : edgeSet) {
        const auto &edge = e->getNodePair();

        const auto firstId = edge.first->getUserId();
        const auto secondId = edge.second->getUserId();

        // if undirected, add both sides
        if (e->isDirected() == false)
            tempIntAdj[userIdToIdx[secondId]][userIdToIdx[firstId]] = 1;
        tempIntAdj[userIdToIdx[firstId]][userIdToIdx[secondId]] = 1;
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

template <typename T>
const PowTransResult Graph<T>::powTransitionMatrix(unsigned int k) const {
    PowTransResult result;
    result.success = false;
    result.errorMessage = "";
    std::unordered_map<std::pair<std::string, std::string>, double,
                        CXXGraph::pair_hash> powTrans;

    // get graph sets
    const auto &nodeSet = Graph<T>::getNodeSet();
    const auto &edgeSet = Graph<T>::getEdgeSet();

    int n = (int)nodeSet.size();

    const auto &transMatrix = Graph<T>::getTransitionMatrix();
    std::unordered_map<std::string, int> userIdToIdx;
    std::unordered_map<int, std::string> idxToUserId;

    std::vector<std::vector<double>> tempDoubleTrans(n, std::vector<double>(n, 0));

    // get a map between index in adj matrix
    // and userId
    int i = 0;
    for (const auto &node : nodeSet) { 
        userIdToIdx[node->getUserId()] = i;
        idxToUserId[i] = node->getUserId();
        i++;
    }

    // given transition matrix, convert it to 
    // stochastic matrix
    for (const auto &it : *transMatrix) {
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
}

#endif //_CXXGRAPH_POW_IMPL_H__