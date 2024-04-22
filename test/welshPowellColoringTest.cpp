#include "CXXGraph/CXXGraph.hpp"
#include "gtest/gtest.h"

TEST(welshPowellColoring, one_edge_two_nodes_undirected) {
  CXXGraph::Node<int> node1("1", 1);
  CXXGraph::Node<int> node2("2", 2);

  CXXGraph::UndirectedWeightedEdge<int> edge12(3, node1, node2, 4);

  CXXGraph::T_EdgeSet<int> edgeSet;
  edgeSet.insert(
      std::make_shared<CXXGraph::UndirectedWeightedEdge<int>>(edge12));

  CXXGraph::Graph<int> graph(edgeSet);

  auto result = graph.welshPowellColoring();

  // get the highest coloring order
  auto highest_coloring_order =
      std::max_element(result.begin(), result.end(),
                       [](const auto& lhs, const auto& rhs) {
                         return lhs.second < rhs.second;
                       })
          ->second;
  ASSERT_EQ(graph.isUndirectedGraph(), true);

  // Asserts that the chromatic color of the graph is 2
  ASSERT_EQ(highest_coloring_order, 2);
}

TEST(welshPowellColoring, undirected_simon_james) {
  // https://www.youtube.com/watch?v=CQIW2mLfG04&ab_channel=SimonJames
  CXXGraph::Node<int> nodeA("a", 1);
  CXXGraph::Node<int> nodeB("b", 1);
  CXXGraph::Node<int> nodeC("c", 1);
  CXXGraph::Node<int> nodeD("d", 1);
  CXXGraph::Node<int> nodeE("e", 1);
  CXXGraph::Node<int> nodeF("f", 1);
  CXXGraph::Node<int> nodeG("g", 1);
  CXXGraph::Node<int> nodeH("h", 1);
  CXXGraph::Node<int> nodeI("i", 1);
  CXXGraph::Node<int> nodeJ("j", 1);
  CXXGraph::Node<int> nodeK("k", 1);

  CXXGraph::UndirectedEdge<int> edgeAB(1, nodeA, nodeB),
      edgeBA(1, nodeB, nodeA),  //

      edgeAC(1, nodeA, nodeC), edgeCA(1, nodeC, nodeA),  //

      edgeAD(1, nodeA, nodeD), edgeDA(1, nodeD, nodeA),  //

      edgeAK(1, nodeA, nodeK), edgeKA(1, nodeK, nodeA),

      edgeAH(1, nodeA, nodeH), edgeHA(1, nodeA, nodeH),  //

      edgeAE(1, nodeA, nodeE), edgeEA(1, nodeA, nodeH),  //

      edgeAG(1, nodeA, nodeG), edgeGA(1, nodeA, nodeG),  //

      edgeBK(1, nodeB, nodeK), edgeKB(1, nodeK, nodeB),  //

      edgeBI(1, nodeB, nodeI), edgeIB(1, nodeI, nodeB),  //

      edgeBJ(1, nodeB, nodeJ), edgeJB(1, nodeJ, nodeB),

      edgeBF(1, nodeB, nodeF), edgeFB(1, nodeF, nodeB),  //

      edgeBD(1, nodeB, nodeD), edgeDB(1, nodeD, nodeB),  //

      edgeCE(1, nodeC, nodeE), edgeEC(1, nodeE, nodeC),  //

      edgeCD(1, nodeC, nodeD), edgeDC(1, nodeD, nodeC),  //

      edgeCH(1, nodeC, nodeH), edgeHC(1, nodeH, nodeC),  //

      edgeCG(1, nodeC, nodeG), edgeGC(1, nodeG, nodeC),  //

      edgeDE(1, nodeD, nodeE), edgeED(1, nodeD, nodeE),  //

      edgeEK(1, nodeE, nodeK), edgeKE(1, nodeK, nodeE),  //

      edgeFI(1, nodeF, nodeI), edgeIF(1, nodeI, nodeF),

      edgeFJ(1, nodeF, nodeJ), edgeJF(1, nodeJ, nodeF),

      edgeFG(1, nodeF, nodeG), edgeGF(1, nodeG, nodeF),

      edgeGH(1, nodeG, nodeH), edgeHG(1, nodeH, nodeG),

      edgeIJ(1, nodeI, nodeJ),  //
      edgeJI(1, nodeJ, nodeI);  //

  CXXGraph::T_EdgeSet<int> edgeSet;

  edgeSet.insert(std::make_shared<CXXGraph::UndirectedEdge<int>>(edgeAB));

  edgeSet.insert(std::make_shared<CXXGraph::UndirectedEdge<int>>(edgeAC));

  edgeSet.insert(std::make_shared<CXXGraph::UndirectedEdge<int>>(edgeAD));

  edgeSet.insert(std::make_shared<CXXGraph::UndirectedEdge<int>>(edgeAK));

  edgeSet.insert(std::make_shared<CXXGraph::UndirectedEdge<int>>(edgeAH));

  edgeSet.insert(std::make_shared<CXXGraph::UndirectedEdge<int>>(edgeAE));

  edgeSet.insert(std::make_shared<CXXGraph::UndirectedEdge<int>>(edgeAG));

  edgeSet.insert(std::make_shared<CXXGraph::UndirectedEdge<int>>(edgeBK));

  edgeSet.insert(std::make_shared<CXXGraph::UndirectedEdge<int>>(edgeBI));

  edgeSet.insert(std::make_shared<CXXGraph::UndirectedEdge<int>>(edgeBJ));

  edgeSet.insert(std::make_shared<CXXGraph::UndirectedEdge<int>>(edgeBF));

  edgeSet.insert(std::make_shared<CXXGraph::UndirectedEdge<int>>(edgeBD));

  edgeSet.insert(std::make_shared<CXXGraph::UndirectedEdge<int>>(edgeCE));

  edgeSet.insert(std::make_shared<CXXGraph::UndirectedEdge<int>>(edgeCD));

  edgeSet.insert(std::make_shared<CXXGraph::UndirectedEdge<int>>(edgeCH));

  edgeSet.insert(std::make_shared<CXXGraph::UndirectedEdge<int>>(edgeCG));

  edgeSet.insert(std::make_shared<CXXGraph::UndirectedEdge<int>>(edgeDE));

  edgeSet.insert(std::make_shared<CXXGraph::UndirectedEdge<int>>(edgeEK));

  edgeSet.insert(std::make_shared<CXXGraph::UndirectedEdge<int>>(edgeFI));

  edgeSet.insert(std::make_shared<CXXGraph::UndirectedEdge<int>>(edgeFJ));

  edgeSet.insert(std::make_shared<CXXGraph::UndirectedEdge<int>>(edgeFG));

  edgeSet.insert(std::make_shared<CXXGraph::UndirectedEdge<int>>(edgeGH));

  edgeSet.insert(std::make_shared<CXXGraph::UndirectedEdge<int>>(edgeIJ));

  CXXGraph::Graph<int> graph(edgeSet);

  auto result = graph.welshPowellColoring();
  auto highest_coloring_order =
      std::max_element(result.begin(), result.end(),
                       [](const auto& lhs, const auto& rhs) {
                         return lhs.second < rhs.second;
                       })
          ->second;

  ASSERT_EQ(graph.isUndirectedGraph(), true);
  // Asserts that the chromatic color of the graph is 4, as indicated in 2:30 of
  // video
  ASSERT_EQ(highest_coloring_order, 4);
}