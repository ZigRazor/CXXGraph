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
  ASSERT_EQ(res.bridges.size(), 0);
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
  ASSERT_EQ(res.bridges.size(), 0);
  ASSERT_EQ(res.edgeBiconnectedComps.size(), 0);
  ASSERT_EQ(res.verticeBiconnectedComps.size(), 0);
}

TEST(TarjanTest, test_3) {
  // the undirected graph used in this case is a block-cut tree in wiki
  // https://en.wikipedia.org/wiki/Biconnected_component#/media/File:Block-cut_tree2.svg
  std::vector<CXXGraph::Node<int>> nodes;
  nodes.emplace_back("0", 0);
  for (int i = 1; i <= 18; ++i) {
    nodes.emplace_back(std::to_string(i), i);
  };
  std::vector<std::pair<int,int>> pairs{
    {1, 2}, {2, 3}, {3, 4}, {2, 4}, {2, 5}, {2, 6},
    {5, 6}, {5, 7}, {6, 7}, {7, 8}, {7, 11}, {8, 11},
    {8, 9}, {9, 11}, {8, 12}, {8, 14}, {8, 15}, 
    {12, 13}, {14, 13}, {15, 13}, {9, 10}, {11, 10}, 
    {10, 16}, {10, 17}, {10, 18}, {17, 18}
  };
  std::vector<CXXGraph::UndirectedWeightedEdge<int>> edges;
  for (const auto& [id1, id2] : pairs) {
    edges.emplace_back(edges.size() + 1, nodes[id1], nodes[id2], 1);
  }
  CXXGraph::T_EdgeSet<int> edgeSet;
  for (const auto &edge : edges) {
    edgeSet.insert(make_shared<CXXGraph::UndirectedWeightedEdge<int>>(edge));
  }
  CXXGraph::Graph<int> graph(edgeSet);
  CXXGraph::TarjanResult<int> res = graph.tarjan(CXXGraph::TARJAN_FIND_CUTV);
  ASSERT_EQ(res.success, true);

  std::vector<int> expectRes{2, 7, 8, 10};
  ASSERT_EQ(res.cutVertices.size(), expectRes.size());
  std::sort(res.cutVertices.begin(), res.cutVertices.end(), [&](const auto &node1, const auto &node2) {
      return node1.getData() < node2.getData();
  });
  for (int i = 0; i < expectRes.size(); ++i) {
    ASSERT_EQ(res.cutVertices[i], nodes[expectRes[i]]);
  }
  // check whether other types of functions are not be executed
  ASSERT_EQ(res.stronglyConnectedComps.size(), 0);
  ASSERT_EQ(res.bridges.size(), 0);
  ASSERT_EQ(res.edgeBiconnectedComps.size(), 0);
  ASSERT_EQ(res.verticeBiconnectedComps.size(), 0);
}

TEST(TarjanTest, test_4) {
  // the undirected graph used in this case is a block-cut tree in wiki
  // https://en.wikipedia.org/wiki/Biconnected_component#/media/File:Block-cut_tree2.svg
  std::vector<CXXGraph::Node<int>> nodes;
  nodes.emplace_back("0", 0);
  for (int i = 1; i <= 18; ++i) {
    nodes.emplace_back(std::to_string(i), i);
  };
  std::vector<std::pair<int,int>> pairs{
    {1, 2}, {2, 3}, {3, 4}, {2, 4}, {2, 5}, {2, 6},
    {5, 6}, {5, 7}, {6, 7}, {7, 8}, {7, 11}, {8, 11},
    {8, 9}, {9, 11}, {8, 12}, {8, 14}, {8, 15}, 
    {12, 13}, {14, 13}, {15, 13}, {9, 10}, {11, 10}, 
    {10, 16}, {10, 17}, {10, 18}, {17, 18}
  };
  std::vector<CXXGraph::UndirectedWeightedEdge<int>> edges;
  for (const auto& [id1, id2] : pairs) {
    edges.emplace_back(edges.size() + 1, nodes[id1], nodes[id2], 1);
  }
  CXXGraph::T_EdgeSet<int> edgeSet;
  for (const auto &edge : edges) {
    edgeSet.insert(make_shared<CXXGraph::UndirectedWeightedEdge<int>>(edge));
  }
  CXXGraph::Graph<int> graph(edgeSet);
  CXXGraph::TarjanResult<int> res = graph.tarjan(CXXGraph::TARJAN_FIND_VBCC);
  ASSERT_EQ(res.success, true);

  std::vector<std::vector<CXXGraph::Node<int>>> expectRes{
      {nodes[1], nodes[2]}, {nodes[2], nodes[3], nodes[4]}, 
      {nodes[2], nodes[5], nodes[6], nodes[7]}, 
      {nodes[7], nodes[8], nodes[9], nodes[10], nodes[11]},
      {nodes[8], nodes[12], nodes[13], nodes[14], nodes[15]},
      {nodes[10], nodes[16]},
      {nodes[10], nodes[17], nodes[18]}
  };
  ASSERT_EQ(res.verticeBiconnectedComps.size(), expectRes.size());

  // sort nodes in a vbcc by node id
  for (auto &vbcc : res.verticeBiconnectedComps) {
    sort(vbcc.begin(), vbcc.end(), [&](const auto &node1, const auto &node2) {
      return node1.getData() < node2.getData();
    });
  }
  // sort vbccs by first node and size
  std::sort(res.verticeBiconnectedComps.begin(),
            res.verticeBiconnectedComps.end(),
            [&](const auto &scc1, const auto &scc2) {
              if ((scc1.size() == 0) || (scc2.size() == 0) || (scc1[0].getData() == scc2[0].getData())) {
                return scc1.size() < scc2.size();
              }
              return scc1[0].getData() < scc2[0].getData(); 
            });
  for (int i = 0; i < res.verticeBiconnectedComps.size(); ++i) {
    ASSERT_EQ(res.verticeBiconnectedComps[i].size(), expectRes[i].size());
    for (int j = 0; j < expectRes[i].size(); ++j) {
      ASSERT_EQ(res.verticeBiconnectedComps[i][j], expectRes[i][j]);
    }
  }
  // check whether other types of functions are not be executed
  ASSERT_EQ(res.stronglyConnectedComps.size(), 0);
  ASSERT_EQ(res.bridges.size(), 0);
  ASSERT_EQ(res.edgeBiconnectedComps.size(), 0);
  ASSERT_EQ(res.cutVertices.size(), 0);
}


TEST(TarjanTest, test_5) {
  // the undirected graph used in this case is a bridge tree from a tutorial on codeforce
  // https://codeforces.com/blog/entry/99259
  std::vector<CXXGraph::Node<int>> nodes;
  nodes.emplace_back("0", 0);
  for (int i = 1; i <= 12; ++i) {
    nodes.emplace_back(std::to_string(i), i);
  };
  std::vector<std::pair<int,int>> pairs{
    {1, 2}, {2, 3}, {1, 3}, {3, 4}, {3, 9}, 
    {4, 5}, {5, 6}, {4, 7}, {6, 7}, {6, 8}, 
    {7, 8}, {9, 10}, {9, 11}, {10, 12}, {11, 12},
  };
  std::vector<CXXGraph::UndirectedWeightedEdge<int>> edges;
  for (const auto& [id1, id2] : pairs) {
    edges.emplace_back(edges.size() + 1, nodes[id1], nodes[id2], 1);
  }
  CXXGraph::T_EdgeSet<int> edgeSet;
  for (const auto &edge : edges) {
    edgeSet.insert(make_shared<CXXGraph::UndirectedWeightedEdge<int>>(edge));
  }
  CXXGraph::Graph<int> graph(edgeSet);
  CXXGraph::TarjanResult<int> res = graph.tarjan(CXXGraph::TARJAN_FIND_BRIDGE);
  ASSERT_EQ(res.success, true);

  std::vector<int> expectRes{3, 4};
  ASSERT_EQ(res.bridges.size(), expectRes.size());
  std::sort(res.bridges.begin(), res.bridges.end(), [&](const auto &edge1, const auto &edge2) {
      return edge1.getId() < edge2.getId();
  });
  for (int i = 0; i < expectRes.size(); ++i) {
    ASSERT_EQ(res.bridges[i], edges[expectRes[i]]);
  }
  // check whether other types of functions are not be executed
  ASSERT_EQ(res.stronglyConnectedComps.size(), 0);
  ASSERT_EQ(res.cutVertices.size(), 0);
  ASSERT_EQ(res.edgeBiconnectedComps.size(), 0);
  ASSERT_EQ(res.verticeBiconnectedComps.size(), 0);
}

TEST(TarjanTest, test_6) {
  // the undirected graph used in this case is a bridge tree from a tutorial on codeforce
  // https://codeforces.com/blog/entry/99259
  std::vector<CXXGraph::Node<int>> nodes;
  nodes.emplace_back("0", 0);
  for (int i = 1; i <= 12; ++i) {
    nodes.emplace_back(std::to_string(i), i);
  };
  std::vector<std::pair<int,int>> pairs{
    {1, 2}, {2, 3}, {1, 3}, {3, 4}, {3, 9}, 
    {4, 5}, {5, 6}, {4, 7}, {6, 7}, {6, 8}, 
    {7, 8}, {9, 10}, {9, 11}, {10, 12}, {11, 12},
  };
  std::vector<CXXGraph::UndirectedWeightedEdge<int>> edges;
  for (const auto& [id1, id2] : pairs) {
    edges.emplace_back(edges.size() + 1, nodes[id1], nodes[id2], 1);
  }
  CXXGraph::T_EdgeSet<int> edgeSet;
  for (const auto &edge : edges) {
    edgeSet.insert(make_shared<CXXGraph::UndirectedWeightedEdge<int>>(edge));
  }
  CXXGraph::Graph<int> graph(edgeSet);
  CXXGraph::TarjanResult<int> res = graph.tarjan(CXXGraph::TARJAN_FIND_EBCC);
  ASSERT_EQ(res.success, true);

  std::vector<std::vector<CXXGraph::Node<int>>> expectRes{
      {nodes[1], nodes[2], nodes[3]}, 
      {nodes[4], nodes[5], nodes[6], nodes[7], nodes[8]}, 
      {nodes[9], nodes[10], nodes[11], nodes[12]}
  };
  ASSERT_EQ(res.edgeBiconnectedComps.size(), expectRes.size());

  // sort nodes in a vbcc by node id
  for (auto &ebcc : res.edgeBiconnectedComps) {
    sort(ebcc.begin(), ebcc.end(), [&](const auto &node1, const auto &node2) {
      return node1.getData() < node2.getData();
    });
  }
  // sort vbccs by first node and size
  std::sort(res.edgeBiconnectedComps.begin(),
            res.edgeBiconnectedComps.end(),
            [&](const auto &scc1, const auto &scc2) {
              if ((scc1.size() == 0) || (scc2.size() == 0) || (scc1[0].getData() == scc2[0].getData())) {
                return scc1.size() < scc2.size();
              }
              return scc1[0].getData() < scc2[0].getData(); 
            });
  for (int i = 0; i < res.edgeBiconnectedComps.size(); ++i) {
    ASSERT_EQ(res.edgeBiconnectedComps[i].size(), expectRes[i].size());
    for (int j = 0; j < expectRes[i].size(); ++j) {
      ASSERT_EQ(res.edgeBiconnectedComps[i][j], expectRes[i][j]);
    }
  }
  // check whether other types of functions are not be executed
  ASSERT_EQ(res.stronglyConnectedComps.size(), 0);
  ASSERT_EQ(res.bridges.size(), 0);
  ASSERT_EQ(res.verticeBiconnectedComps.size(), 0);
  ASSERT_EQ(res.cutVertices.size(), 0);
}

TEST(TarjanTest, test_7) {
  // the undirected graph used in this case is a block-cut tree in wiki
  // https://en.wikipedia.org/wiki/Biconnected_component#/media/File:Block-cut_tree2.svg
  std::vector<CXXGraph::Node<int>> nodes;
  nodes.emplace_back("0", 0);
  for (int i = 1; i <= 18; ++i) {
    nodes.emplace_back(std::to_string(i), i);
  };
  std::vector<std::pair<int,int>> pairs{
    {1, 2}, {2, 3}, {3, 4}, {2, 4}, {2, 5}, {2, 6},
    {5, 6}, {5, 7}, {6, 7}, {7, 8}, {7, 11}, {8, 11},
    {8, 9}, {9, 11}, {8, 12}, {8, 14}, {8, 15}, 
    {12, 13}, {14, 13}, {15, 13}, {9, 10}, {11, 10}, 
    {10, 16}, {10, 17}, {10, 18}, {17, 18}
  };
  std::vector<CXXGraph::UndirectedWeightedEdge<int>> edges;
  for (const auto& [id1, id2] : pairs) {
    edges.emplace_back(edges.size() + 1, nodes[id1], nodes[id2], 1);
  }
  CXXGraph::T_EdgeSet<int> edgeSet;
  for (const auto &edge : edges) {
    edgeSet.insert(make_shared<CXXGraph::UndirectedWeightedEdge<int>>(edge));
  }
  CXXGraph::Graph<int> graph(edgeSet);

  CXXGraph::TarjanResult<int> cutvRes = graph.tarjan(CXXGraph::TARJAN_FIND_CUTV);
  CXXGraph::TarjanResult<int> bridgeRes = graph.tarjan(CXXGraph::TARJAN_FIND_BRIDGE);
  CXXGraph::TarjanResult<int> vbccRes = graph.tarjan(CXXGraph::TARJAN_FIND_VBCC);
  CXXGraph::TarjanResult<int> ebccRes = graph.tarjan(CXXGraph::TARJAN_FIND_EBCC);
  CXXGraph::TarjanResult<int> res = graph.tarjan(CXXGraph::TARJAN_FIND_CUTV | CXXGraph::TARJAN_FIND_BRIDGE | CXXGraph::TARJAN_FIND_EBCC | CXXGraph::TARJAN_FIND_VBCC);
  ASSERT_EQ(res.success, true);

  ASSERT_EQ(res.cutVertices.size(), cutvRes.cutVertices.size());
  for (int i = 0; i < cutvRes.cutVertices.size(); ++i) {
    ASSERT_EQ(cutvRes.cutVertices[i], res.cutVertices[i]);
  }
  ASSERT_EQ(res.bridges.size(), bridgeRes.bridges.size());
  for (int i = 0; i < bridgeRes.cutVertices.size(); ++i) {
    ASSERT_EQ(bridgeRes.bridges[i], res.bridges[i]);
  }
  ASSERT_EQ(res.edgeBiconnectedComps.size(), ebccRes.edgeBiconnectedComps.size());
  for (int i = 0; i < res.edgeBiconnectedComps.size(); ++i) {
    ASSERT_EQ(res.edgeBiconnectedComps[i].size(), ebccRes.edgeBiconnectedComps[i].size());
    for (int j = 0; j < ebccRes.edgeBiconnectedComps[i].size(); ++j) {
      ASSERT_EQ(res.edgeBiconnectedComps[i][j], ebccRes.edgeBiconnectedComps[i][j]);
    }
  }
  ASSERT_EQ(res.verticeBiconnectedComps.size(), vbccRes.verticeBiconnectedComps.size());
  for (int i = 0; i < res.verticeBiconnectedComps.size(); ++i) {
    ASSERT_EQ(res.verticeBiconnectedComps[i].size(), vbccRes.verticeBiconnectedComps[i].size());
    for (int j = 0; j < vbccRes.verticeBiconnectedComps[i].size(); ++j) {
      ASSERT_EQ(res.verticeBiconnectedComps[i][j], vbccRes.verticeBiconnectedComps[i][j]);
    }
  }
}