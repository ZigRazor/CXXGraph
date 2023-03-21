#include <zlib.h>

#include "CXXGraph.hpp"
#include "Edge/DirectedEdge.hpp"
#include "Edge/UndirectedEdge.hpp"
#include "Graph/Graph.hpp"
#include "gtest/gtest.h"

// helper function to compare strongly connected components (SCC) as computed
// by the algorithm with expected (correct) SCC
void compareComponents(CXXGRAPH::Components<int>& comp1,
                       CXXGRAPH::Components<int>& comp2) {
  ASSERT_EQ(comp1.size(), comp2.size());

  for (size_t i = 0; i < comp1.size(); ++i) {
    std::sort(comp1[i].begin(), comp1[i].end());
    std::sort(comp2[i].begin(), comp2[i].end());
  }

  std::sort(comp1.begin(), comp1.end(),
            [](auto& c1, auto& c2) { return c1.front() < c2.front(); });

  std::sort(comp2.begin(), comp2.end(),
            [](auto& c1, auto& c2) { return c1.front() < c2.front(); });

  ASSERT_EQ(comp1, comp2);
}

// undirected graph
TEST(KosarajuTest, test_1) {
  CXXGRAPH::Node<int> node1("1", 1);
  CXXGRAPH::Node<int> node2("2", 2);
  CXXGRAPH::UndirectedEdge<int> edge(1, node1, node2);
  CXXGRAPH::T_EdgeSet<int> edgeSet;
  edgeSet.insert(&edge);
  CXXGRAPH::Graph<int> graph(edgeSet);
  auto res = graph.kosaraju();
  ASSERT_EQ(res.stronglyConnectedComps.size(), 0);
  ASSERT_FALSE(res.success);
  ASSERT_EQ(res.errorMessage, CXXGRAPH::ERR_UNDIR_GRAPH);
}

// 1 comp, 1 strongly connected comp
TEST(KosarajuTest, test_2) {
  CXXGRAPH::Node<int> node1("1", 1);
  CXXGRAPH::Node<int> node2("2", 2);
  CXXGRAPH::DirectedEdge<int> edge1(1, node1, node2);
  CXXGRAPH::DirectedEdge<int> edge2(2, node2, node1);
  CXXGRAPH::T_EdgeSet<int> edgeSet;
  edgeSet.insert(&edge1);
  edgeSet.insert(&edge2);
  CXXGRAPH::Graph<int> graph(edgeSet);
  auto res = graph.kosaraju();
  ASSERT_TRUE(res.success);
  ASSERT_EQ(res.errorMessage, "");
  ASSERT_EQ(res.stronglyConnectedComps.size(), 1);
  ASSERT_EQ(res.stronglyConnectedComps[0].size(), 2);
}

// 1 comp, 2 strongly connected comp
TEST(KosarajuTest, test_3) {
  CXXGRAPH::Node<int> node1("1", 1);
  CXXGRAPH::Node<int> node2("2", 2);
  CXXGRAPH::Node<int> node3("3", 3);
  CXXGRAPH::DirectedEdge<int> edge1(1, node1, node2);
  CXXGRAPH::DirectedEdge<int> edge2(2, node2, node1);
  CXXGRAPH::DirectedEdge<int> edge3(3, node3, node1);
  CXXGRAPH::T_EdgeSet<int> edgeSet;
  edgeSet.insert(&edge1);
  edgeSet.insert(&edge2);
  edgeSet.insert(&edge3);
  CXXGRAPH::Graph<int> graph(edgeSet);
  auto res = graph.kosaraju();
  ASSERT_TRUE(res.success);
  ASSERT_EQ(res.errorMessage, "");

  CXXGRAPH::Components<int> expectedComponents = {{node1, node2}, {node3}};
  compareComponents(res.stronglyConnectedComps, expectedComponents);
}

// 2 components, 2 strongly connected comps
TEST(KosarajuTest, test_4) {
  CXXGRAPH::Node<int> node1("1", 1);
  CXXGRAPH::Node<int> node2("2", 2);
  CXXGRAPH::Node<int> node3("3", 3);
  CXXGRAPH::Node<int> node4("4", 4);
  CXXGRAPH::DirectedEdge<int> edge1(1, node1, node2);
  CXXGRAPH::DirectedEdge<int> edge2(2, node2, node1);
  CXXGRAPH::DirectedEdge<int> edge3(3, node3, node4);
  CXXGRAPH::DirectedEdge<int> edge4(4, node4, node3);
  CXXGRAPH::T_EdgeSet<int> edgeSet;
  edgeSet.insert(&edge1);
  edgeSet.insert(&edge2);
  edgeSet.insert(&edge3);
  edgeSet.insert(&edge4);
  CXXGRAPH::Graph<int> graph(edgeSet);
  auto res = graph.kosaraju();
  ASSERT_TRUE(res.success);
  ASSERT_EQ(res.errorMessage, "");
  CXXGRAPH::Components<int> expectedComponents = {{node1, node2},
                                                  {node3, node4}};
  compareComponents(res.stronglyConnectedComps, expectedComponents);
}

TEST(KosarajuTest, test_5) {
  CXXGRAPH::Node<int> node1("1", 1);
  CXXGRAPH::Node<int> node2("2", 2);
  CXXGRAPH::Node<int> node3("3", 3);
  CXXGRAPH::Node<int> node4("4", 4);
  CXXGRAPH::Node<int> node5("5", 5);
  CXXGRAPH::Node<int> node6("6", 6);
  CXXGRAPH::Node<int> node7("7", 7);
  CXXGRAPH::Node<int> node8("8", 8);
  CXXGRAPH::Node<int> node9("9", 9);
  CXXGRAPH::Node<int> node10("10", 10);
  CXXGRAPH::Node<int> node11("11", 11);
  CXXGRAPH::Node<int> node12("12", 12);
  CXXGRAPH::Node<int> node13("13", 13);

  CXXGRAPH::DirectedEdge<int> edge1(1, node1, node2);
  CXXGRAPH::DirectedEdge<int> edge2(2, node1, node6);
  CXXGRAPH::DirectedEdge<int> edge3(3, node3, node1);
  CXXGRAPH::DirectedEdge<int> edge4(4, node3, node4);
  CXXGRAPH::DirectedEdge<int> edge5(5, node4, node5);
  CXXGRAPH::DirectedEdge<int> edge6(6, node4, node6);
  CXXGRAPH::DirectedEdge<int> edge7(7, node6, node5);
  CXXGRAPH::DirectedEdge<int> edge8(8, node5, node3);
  CXXGRAPH::DirectedEdge<int> edge9(9, node7, node1);
  CXXGRAPH::DirectedEdge<int> edge10(10, node7, node5);
  CXXGRAPH::DirectedEdge<int> edge11(11, node7, node10);
  CXXGRAPH::DirectedEdge<int> edge12(12, node12, node5);
  CXXGRAPH::DirectedEdge<int> edge13(13, node8, node7);
  CXXGRAPH::DirectedEdge<int> edge14(14, node8, node9);
  CXXGRAPH::DirectedEdge<int> edge15(15, node9, node8);
  CXXGRAPH::DirectedEdge<int> edge16(16, node9, node10);
  CXXGRAPH::DirectedEdge<int> edge17(17, node10, node11);
  CXXGRAPH::DirectedEdge<int> edge18(18, node10, node12);
  CXXGRAPH::DirectedEdge<int> edge19(19, node12, node13);
  CXXGRAPH::DirectedEdge<int> edge20(20, node11, node13);
  CXXGRAPH::DirectedEdge<int> edge21(21, node13, node10);

  CXXGRAPH::T_EdgeSet<int> edgeSet;
  edgeSet.insert(&edge1);
  edgeSet.insert(&edge2);
  edgeSet.insert(&edge3);
  edgeSet.insert(&edge4);
  edgeSet.insert(&edge5);
  edgeSet.insert(&edge6);
  edgeSet.insert(&edge7);
  edgeSet.insert(&edge8);
  edgeSet.insert(&edge9);
  edgeSet.insert(&edge10);
  edgeSet.insert(&edge11);
  edgeSet.insert(&edge12);
  edgeSet.insert(&edge13);
  edgeSet.insert(&edge14);
  edgeSet.insert(&edge15);
  edgeSet.insert(&edge16);
  edgeSet.insert(&edge17);
  edgeSet.insert(&edge18);
  edgeSet.insert(&edge19);
  edgeSet.insert(&edge20);
  edgeSet.insert(&edge21);

  CXXGRAPH::Graph graph(edgeSet);
  auto res = graph.kosaraju();
  ASSERT_TRUE(res.success);
  ASSERT_EQ(res.errorMessage, "");

  CXXGRAPH::Components<int> expectedComponents = {
      {node2},
      {node1, node3, node4, node5, node6},
      {node7},
      {node8, node9},
      {node10, node11, node12, node13}};

  compareComponents(res.stronglyConnectedComps, expectedComponents);
}
