#include <memory>
#include "CXXGraph/CXXGraph.hpp"
#include "gtest/gtest.h"

// Smart pointers alias
template <typename T>
using unique = std::unique_ptr<T>;
template <typename T>
using shared= std::shared_ptr<T>;

using std::make_unique;
using std::make_shared;

// helper function to compare strongly connected components (SCC) as computed
// by the algorithm with expected (correct) SCC
void compareComponents(CXXGraph::Components<int>& comp1,
                       CXXGraph::Components<int>& comp2) {
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
  CXXGraph::Node<int> node1("1", 1);
  CXXGraph::Node<int> node2("2", 2);
  CXXGraph::UndirectedEdge<int> edge(1, node1, node2);
  CXXGraph::T_EdgeSet<int> edgeSet;
  edgeSet.insert(make_shared<CXXGraph::UndirectedEdge<int>>(edge));
  CXXGraph::Graph<int> graph(edgeSet);
  auto res = graph.kosaraju();
  ASSERT_EQ(res.stronglyConnectedComps.size(), 0);
  ASSERT_FALSE(res.success);
  ASSERT_EQ(res.errorMessage, CXXGraph::ERR_UNDIR_GRAPH);
}

// 1 comp, 1 strongly connected comp
TEST(KosarajuTest, test_2) {
  CXXGraph::Node<int> node1("1", 1);
  CXXGraph::Node<int> node2("2", 2);
  CXXGraph::DirectedEdge<int> edge1(1, node1, node2);
  CXXGraph::DirectedEdge<int> edge2(2, node2, node1);
  CXXGraph::T_EdgeSet<int> edgeSet;
  edgeSet.insert(make_shared<CXXGraph::DirectedEdge<int>>(edge1));
  edgeSet.insert(make_shared<CXXGraph::DirectedEdge<int>>(edge2));
  CXXGraph::Graph<int> graph(edgeSet);
  auto res = graph.kosaraju();
  ASSERT_TRUE(res.success);
  ASSERT_EQ(res.errorMessage, "");
  ASSERT_EQ(res.stronglyConnectedComps.size(), 1);
  ASSERT_EQ(res.stronglyConnectedComps[0].size(), 2);
}

// 1 comp, 2 strongly connected comp
TEST(KosarajuTest, test_3) {
  CXXGraph::Node<int> node1("1", 1);
  CXXGraph::Node<int> node2("2", 2);
  CXXGraph::Node<int> node3("3", 3);
  CXXGraph::DirectedEdge<int> edge1(1, node1, node2);
  CXXGraph::DirectedEdge<int> edge2(2, node2, node1);
  CXXGraph::DirectedEdge<int> edge3(3, node3, node1);
  CXXGraph::T_EdgeSet<int> edgeSet;
  edgeSet.insert(make_shared<CXXGraph::DirectedEdge<int>>(edge1));
  edgeSet.insert(make_shared<CXXGraph::DirectedEdge<int>>(edge2));
  edgeSet.insert(make_shared<CXXGraph::DirectedEdge<int>>(edge3));
  CXXGraph::Graph<int> graph(edgeSet);
  auto res = graph.kosaraju();
  ASSERT_TRUE(res.success);
  ASSERT_EQ(res.errorMessage, "");

  CXXGraph::Components<int> expectedComponents = {{node1, node2}, {node3}};
  compareComponents(res.stronglyConnectedComps, expectedComponents);
}

// 2 components, 2 strongly connected comps
TEST(KosarajuTest, test_4) {
  CXXGraph::Node<int> node1("1", 1);
  CXXGraph::Node<int> node2("2", 2);
  CXXGraph::Node<int> node3("3", 3);
  CXXGraph::Node<int> node4("4", 4);
  CXXGraph::DirectedEdge<int> edge1(1, node1, node2);
  CXXGraph::DirectedEdge<int> edge2(2, node2, node1);
  CXXGraph::DirectedEdge<int> edge3(3, node3, node4);
  CXXGraph::DirectedEdge<int> edge4(4, node4, node3);
  CXXGraph::T_EdgeSet<int> edgeSet;
  edgeSet.insert(make_shared<CXXGraph::DirectedEdge<int>>(edge1));
  edgeSet.insert(make_shared<CXXGraph::DirectedEdge<int>>(edge2));
  edgeSet.insert(make_shared<CXXGraph::DirectedEdge<int>>(edge3));
  edgeSet.insert(make_shared<CXXGraph::DirectedEdge<int>>(edge4));
  CXXGraph::Graph<int> graph(edgeSet);
  auto res = graph.kosaraju();
  ASSERT_TRUE(res.success);
  ASSERT_EQ(res.errorMessage, "");
  CXXGraph::Components<int> expectedComponents = {{node1, node2},
                                                  {node3, node4}};
  compareComponents(res.stronglyConnectedComps, expectedComponents);
}

TEST(KosarajuTest, test_5) {
  CXXGraph::Node<int> node1("1", 1);
  CXXGraph::Node<int> node2("2", 2);
  CXXGraph::Node<int> node3("3", 3);
  CXXGraph::Node<int> node4("4", 4);
  CXXGraph::Node<int> node5("5", 5);
  CXXGraph::Node<int> node6("6", 6);
  CXXGraph::Node<int> node7("7", 7);
  CXXGraph::Node<int> node8("8", 8);
  CXXGraph::Node<int> node9("9", 9);
  CXXGraph::Node<int> node10("10", 10);
  CXXGraph::Node<int> node11("11", 11);
  CXXGraph::Node<int> node12("12", 12);
  CXXGraph::Node<int> node13("13", 13);

  CXXGraph::DirectedEdge<int> edge1(1, node1, node2);
  CXXGraph::DirectedEdge<int> edge2(2, node1, node6);
  CXXGraph::DirectedEdge<int> edge3(3, node3, node1);
  CXXGraph::DirectedEdge<int> edge4(4, node3, node4);
  CXXGraph::DirectedEdge<int> edge5(5, node4, node5);
  CXXGraph::DirectedEdge<int> edge6(6, node4, node6);
  CXXGraph::DirectedEdge<int> edge7(7, node6, node5);
  CXXGraph::DirectedEdge<int> edge8(8, node5, node3);
  CXXGraph::DirectedEdge<int> edge9(9, node7, node1);
  CXXGraph::DirectedEdge<int> edge10(10, node7, node5);
  CXXGraph::DirectedEdge<int> edge11(11, node7, node10);
  CXXGraph::DirectedEdge<int> edge12(12, node12, node5);
  CXXGraph::DirectedEdge<int> edge13(13, node8, node7);
  CXXGraph::DirectedEdge<int> edge14(14, node8, node9);
  CXXGraph::DirectedEdge<int> edge15(15, node9, node8);
  CXXGraph::DirectedEdge<int> edge16(16, node9, node10);
  CXXGraph::DirectedEdge<int> edge17(17, node10, node11);
  CXXGraph::DirectedEdge<int> edge18(18, node10, node12);
  CXXGraph::DirectedEdge<int> edge19(19, node12, node13);
  CXXGraph::DirectedEdge<int> edge20(20, node11, node13);
  CXXGraph::DirectedEdge<int> edge21(21, node13, node10);

  CXXGraph::T_EdgeSet<int> edgeSet;
  edgeSet.insert(make_shared<CXXGraph::DirectedEdge<int>>(edge1));
  edgeSet.insert(make_shared<CXXGraph::DirectedEdge<int>>(edge2));
  edgeSet.insert(make_shared<CXXGraph::DirectedEdge<int>>(edge3));
  edgeSet.insert(make_shared<CXXGraph::DirectedEdge<int>>(edge4));
  edgeSet.insert(make_shared<CXXGraph::DirectedEdge<int>>(edge5));
  edgeSet.insert(make_shared<CXXGraph::DirectedEdge<int>>(edge6));
  edgeSet.insert(make_shared<CXXGraph::DirectedEdge<int>>(edge7));
  edgeSet.insert(make_shared<CXXGraph::DirectedEdge<int>>(edge8));
  edgeSet.insert(make_shared<CXXGraph::DirectedEdge<int>>(edge9));
  edgeSet.insert(make_shared<CXXGraph::DirectedEdge<int>>(edge10));
  edgeSet.insert(make_shared<CXXGraph::DirectedEdge<int>>(edge11));
  edgeSet.insert(make_shared<CXXGraph::DirectedEdge<int>>(edge12));
  edgeSet.insert(make_shared<CXXGraph::DirectedEdge<int>>(edge13));
  edgeSet.insert(make_shared<CXXGraph::DirectedEdge<int>>(edge14));
  edgeSet.insert(make_shared<CXXGraph::DirectedEdge<int>>(edge15));
  edgeSet.insert(make_shared<CXXGraph::DirectedEdge<int>>(edge16));
  edgeSet.insert(make_shared<CXXGraph::DirectedEdge<int>>(edge17));
  edgeSet.insert(make_shared<CXXGraph::DirectedEdge<int>>(edge18));
  edgeSet.insert(make_shared<CXXGraph::DirectedEdge<int>>(edge19));
  edgeSet.insert(make_shared<CXXGraph::DirectedEdge<int>>(edge20));
  edgeSet.insert(make_shared<CXXGraph::DirectedEdge<int>>(edge21));

  CXXGraph::Graph graph(edgeSet);
  auto res = graph.kosaraju();
  ASSERT_TRUE(res.success);
  ASSERT_EQ(res.errorMessage, "");

  CXXGraph::Components<int> expectedComponents = {
      {node2},
      {node1, node3, node4, node5, node6},
      {node7},
      {node8, node9},
      {node10, node11, node12, node13}};

  compareComponents(res.stronglyConnectedComps, expectedComponents);
}
