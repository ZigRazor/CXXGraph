#include <random>
#include <vector>

#include "CXXGraph.hpp"
#include "Utility/ConstString.hpp"
#include "Utility/Typedef.hpp"
#include "gtest/gtest.h"

// Smart pointers alias
template <typename T>
using unique = std::unique_ptr<T>;
template <typename T>
using shared = std::shared_ptr<T>;

using std::make_shared;

TEST(TarjanTest, test_1) {
  CXXGraph::Node<int> node1("1", 1);
  CXXGraph::Node<int> node2("2", 2);
  CXXGraph::Node<int> node3("3", 3);
  CXXGraph::DirectedWeightedEdge<int> edge1(1, node1, node2, 1);
  CXXGraph::DirectedWeightedEdge<int> edge2(2, node2, node3, 1);
  CXXGraph::T_EdgeSet<int> edgeSet;
  edgeSet.insert(make_shared<CXXGraph::DirectedWeightedEdge<int>>(edge1));
  edgeSet.insert(make_shared<CXXGraph::DirectedWeightedEdge<int>>(edge2));
  CXXGraph::Graph<int> graph(edgeSet);
  CXXGraph::TarjanResult<int> res = graph.tarjan(CXXGraph::TARJAN_FIND_SCC);
  ASSERT_EQ(res.success, true);
  ASSERT_EQ(res.stronglyConnectedComps.size(), 3);
  ASSERT_EQ(res.stronglyConnectedComps[0].size(), 1);
  ASSERT_EQ(res.stronglyConnectedComps[1].size(), 1);
  ASSERT_EQ(res.stronglyConnectedComps[2].size(), 1);
  // check whether nodes in the result are different from each other and are all
  // real nodes in the graph
  auto scc1 = res.stronglyConnectedComps[0][0];
  auto scc2 = res.stronglyConnectedComps[1][0];
  auto scc3 = res.stronglyConnectedComps[2][0];
  ASSERT_EQ((scc1 == scc2) || (scc2 == scc3) || (scc1 == scc3), false);
  int equalCount = 0;
  if ((scc1 == node1) || (scc1 == node2) || (scc1 == node3)) {
    equalCount++;
  }
  if ((scc2 == node1) || (scc2 == node2) || (scc2 == node3)) {
    equalCount++;
  }
  if ((scc3 == node1) || (scc3 == node2) || (scc3 == node3)) {
    equalCount++;
  }
  ASSERT_EQ(equalCount, 3);
  // check whether other types of functions are not be executed
  ASSERT_EQ(res.cutVertices.size(), 0);
  ASSERT_EQ(res.edgeBiconnectedComps.size(), 0);
  ASSERT_EQ(res.verticeBiconnectedComps.size(), 0);
}

TEST(TarjanTest, test_2) {
  CXXGraph::Node<int> node1("1", 1);
  CXXGraph::Node<int> node2("2", 2);
  CXXGraph::Node<int> node3("3", 3);
  CXXGraph::Node<int> node4("4", 4);
  CXXGraph::Node<int> node5("5", 5);
  CXXGraph::Node<int> node6("6", 6);
  CXXGraph::Node<int> node7("7", 7);
  CXXGraph::Node<int> node8("8", 8);
  CXXGraph::Node<int> node9("9", 9);
  std::vector<CXXGraph::DirectedWeightedEdge<int>> edges{
      {1, node1, node2, 1},  {2, node2, node1, 1},  {3, node1, node3, 1},
      {4, node3, node1, 1},  {5, node2, node4, 1},  {6, node3, node4, 1},
      {7, node5, node4, 1},  {8, node4, node5, 1},  {9, node6, node2, 1},
      {10, node7, node6, 1}, {11, node6, node8, 1}, {12, node8, node7, 1},
      {13, node6, node5, 1}, {14, node8, node5, 1}, {15, node9, node7, 1},
      {16, node9, node8, 1},
  };
  CXXGraph::T_EdgeSet<int> edgeSet;
  for (const auto &edge : edges) {
    edgeSet.insert(make_shared<CXXGraph::DirectedWeightedEdge<int>>(edge));
  }
  CXXGraph::Graph<int> graph(edgeSet);
  CXXGraph::TarjanResult<int> res = graph.tarjan(CXXGraph::TARJAN_FIND_SCC);
  ASSERT_EQ(res.success, true);
  ASSERT_EQ(res.stronglyConnectedComps.size(), 4);
  // sort scc by size
  std::sort(res.stronglyConnectedComps.begin(),
            res.stronglyConnectedComps.end(),
            [&](const auto &scc1, const auto &scc2) {
              if ((scc1.size() == scc2.size()) && (scc1.size() > 0)) {
                return scc1[0].getData() < scc2[0].getData();
              }
              return scc1.size() < scc2.size();
            });
  // sort nodes in a scc by node id
  for (auto &scc : res.stronglyConnectedComps) {
    sort(scc.begin(), scc.end(), [&](const auto &node1, const auto &node2) {
      return node1.getData() < node2.getData();
    });
    printf("Scc:\n");
    for (int i = 0; i < scc.size(); ++i) {
      printf("id %lu, data %lu\n", scc[i].getId(), scc[i].getData());
    }
  }
  std::vector<std::vector<CXXGraph::Node<int>>> expectRes{
      {node9}, {node4, node5}, {node1, node2, node3}, {node6, node7, node8}};
  for (int i = 0; i < 4; ++i) {
    ASSERT_EQ(res.stronglyConnectedComps[i].size(), expectRes[i].size());
    for (int j = 0; j < expectRes[i].size(); ++j) {
      ASSERT_EQ(res.stronglyConnectedComps[i][j], expectRes[i][j]);
    }
  }
  // check whether other types of functions are not be executed
  ASSERT_EQ(res.cutVertices.size(), 0);
  ASSERT_EQ(res.edgeBiconnectedComps.size(), 0);
  ASSERT_EQ(res.verticeBiconnectedComps.size(), 0);
}
