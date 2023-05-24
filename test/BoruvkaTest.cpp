#include <memory>
#include "CXXGraph.hpp"
#include "gtest/gtest.h"

// Smart pointers alias
template <typename T>
using unique = std::unique_ptr<T>;
template <typename T>
using shared= std::shared_ptr<T>;

using std::make_unique;
using std::make_shared;

// minimum spanning tree can differ so instead of checking
// the exact order of elements, we can check some properties
// like the length & cost of mst which must remain the same

// example taken from
// https://www.geeksforgeeks.org/prims-mst-for-adjacency-list-representation-greedy-algo-6/
TEST(BoruvkaTest, test_1) {
  CXXGraph::Node<int> node0("0", 0);
  CXXGraph::Node<int> node1("1", 1);
  CXXGraph::Node<int> node2("2", 2);
  CXXGraph::Node<int> node3("3", 3);
  CXXGraph::Node<int> node4("4", 4);
  CXXGraph::Node<int> node5("5", 5);
  CXXGraph::Node<int> node6("6", 6);
  CXXGraph::Node<int> node7("7", 7);
  CXXGraph::Node<int> node8("8", 8);

  CXXGraph::UndirectedWeightedEdge<int> edge1(1, node0, node1, 4);
  CXXGraph::UndirectedWeightedEdge<int> edge2(2, node0, node7, 8);
  CXXGraph::UndirectedWeightedEdge<int> edge3(3, node1, node7, 11);
  CXXGraph::UndirectedWeightedEdge<int> edge4(4, node1, node2, 8);
  CXXGraph::UndirectedWeightedEdge<int> edge5(5, node7, node8, 7);
  CXXGraph::UndirectedWeightedEdge<int> edge6(6, node7, node6, 1);
  CXXGraph::UndirectedWeightedEdge<int> edge7(7, node8, node2, 2);
  CXXGraph::UndirectedWeightedEdge<int> edge8(8, node8, node6, 6);
  CXXGraph::UndirectedWeightedEdge<int> edge9(9, node2, node5, 4);
  CXXGraph::UndirectedWeightedEdge<int> edge10(19, node2, node3, 7);
  CXXGraph::UndirectedWeightedEdge<int> edge11(11, node6, node5, 2);
  CXXGraph::UndirectedWeightedEdge<int> edge12(12, node3, node4, 9);
  CXXGraph::UndirectedWeightedEdge<int> edge13(13, node3, node5, 14);
  CXXGraph::UndirectedWeightedEdge<int> edge14(14, node5, node4, 10);

  CXXGraph::T_EdgeSet<int> edgeSet;
  edgeSet.insert(make_shared<CXXGraph::UndirectedWeightedEdge<int>>(edge1));
  edgeSet.insert(make_shared<CXXGraph::UndirectedWeightedEdge<int>>(edge2));
  edgeSet.insert(make_shared<CXXGraph::UndirectedWeightedEdge<int>>(edge3));
  edgeSet.insert(make_shared<CXXGraph::UndirectedWeightedEdge<int>>(edge4));
  edgeSet.insert(make_shared<CXXGraph::UndirectedWeightedEdge<int>>(edge5));
  edgeSet.insert(make_shared<CXXGraph::UndirectedWeightedEdge<int>>(edge6));
  edgeSet.insert(make_shared<CXXGraph::UndirectedWeightedEdge<int>>(edge7));
  edgeSet.insert(make_shared<CXXGraph::UndirectedWeightedEdge<int>>(edge8));
  edgeSet.insert(make_shared<CXXGraph::UndirectedWeightedEdge<int>>(edge9));
  edgeSet.insert(make_shared<CXXGraph::UndirectedWeightedEdge<int>>(edge10));
  edgeSet.insert(make_shared<CXXGraph::UndirectedWeightedEdge<int>>(edge11));
  edgeSet.insert(make_shared<CXXGraph::UndirectedWeightedEdge<int>>(edge12));
  edgeSet.insert(make_shared<CXXGraph::UndirectedWeightedEdge<int>>(edge13));
  edgeSet.insert(make_shared<CXXGraph::UndirectedWeightedEdge<int>>(edge14));

  CXXGraph::Graph<int> graph(edgeSet);
  CXXGraph::MstResult res = graph.boruvka();

  ASSERT_TRUE(res.success);
  ASSERT_EQ(res.mst.size(), graph.getNodeSet().size() - 1);
  ASSERT_EQ(res.mstCost, 37);
  ASSERT_EQ(res.errorMessage, "");
}

// example taken from
// https://www.gatevidyalay.com/prims-algorithm-prim-algorithm-example/
TEST(BoruvkaTest, test_2) {
  CXXGraph::Node<int> node1("1", 1);
  CXXGraph::Node<int> node2("2", 2);
  CXXGraph::Node<int> node3("3", 3);
  CXXGraph::Node<int> node4("4", 4);
  CXXGraph::Node<int> node5("5", 5);
  CXXGraph::Node<int> node6("6", 6);
  CXXGraph::Node<int> node7("7", 7);

  CXXGraph::UndirectedWeightedEdge<int> edge1(1, node1, node2, 28);
  CXXGraph::UndirectedWeightedEdge<int> edge2(2, node1, node6, 10);
  CXXGraph::UndirectedWeightedEdge<int> edge3(3, node2, node7, 14);
  CXXGraph::UndirectedWeightedEdge<int> edge4(4, node2, node3, 16);
  CXXGraph::UndirectedWeightedEdge<int> edge5(5, node6, node5, 25);
  CXXGraph::UndirectedWeightedEdge<int> edge6(6, node7, node5, 24);
  CXXGraph::UndirectedWeightedEdge<int> edge7(7, node7, node4, 18);
  CXXGraph::UndirectedWeightedEdge<int> edge8(8, node5, node4, 22);
  CXXGraph::UndirectedWeightedEdge<int> edge9(9, node4, node3, 12);

  CXXGraph::T_EdgeSet<int> edgeSet;
  edgeSet.insert(make_shared<CXXGraph::UndirectedWeightedEdge<int>>(edge1));
  edgeSet.insert(make_shared<CXXGraph::UndirectedWeightedEdge<int>>(edge2));
  edgeSet.insert(make_shared<CXXGraph::UndirectedWeightedEdge<int>>(edge3));
  edgeSet.insert(make_shared<CXXGraph::UndirectedWeightedEdge<int>>(edge4));
  edgeSet.insert(make_shared<CXXGraph::UndirectedWeightedEdge<int>>(edge5));
  edgeSet.insert(make_shared<CXXGraph::UndirectedWeightedEdge<int>>(edge6));
  edgeSet.insert(make_shared<CXXGraph::UndirectedWeightedEdge<int>>(edge7));
  edgeSet.insert(make_shared<CXXGraph::UndirectedWeightedEdge<int>>(edge8));
  edgeSet.insert(make_shared<CXXGraph::UndirectedWeightedEdge<int>>(edge9));

  CXXGraph::Graph<int> graph(edgeSet);
  CXXGraph::MstResult res = graph.boruvka();
  ASSERT_TRUE(res.success);
  ASSERT_EQ(res.mst.size(), graph.getNodeSet().size() - 1);
  ASSERT_EQ(res.mstCost, 99);
  ASSERT_EQ(res.errorMessage, "");
}

// example taken from
// https://www.gatevidyalay.com/prims-algorithm-prim-algorithm-example/
TEST(BoruvkaTest, test_3) {
  CXXGraph::Node<int> node1("1", 1);
  CXXGraph::Node<int> node2("2", 2);
  CXXGraph::Node<int> node3("3", 3);
  CXXGraph::Node<int> node4("4", 4);
  CXXGraph::Node<int> node5("5", 5);
  CXXGraph::Node<int> node6("6", 6);
  CXXGraph::Node<int> node7("7", 7);

  CXXGraph::UndirectedWeightedEdge<int> edge1(1, node1, node2, 1);
  CXXGraph::UndirectedWeightedEdge<int> edge2(2, node1, node3, 5);
  CXXGraph::UndirectedWeightedEdge<int> edge3(3, node2, node5, 7);
  CXXGraph::UndirectedWeightedEdge<int> edge4(4, node2, node4, 8);
  CXXGraph::UndirectedWeightedEdge<int> edge5(5, node2, node3, 4);
  CXXGraph::UndirectedWeightedEdge<int> edge6(6, node3, node4, 6);
  CXXGraph::UndirectedWeightedEdge<int> edge7(7, node3, node6, 2);
  CXXGraph::UndirectedWeightedEdge<int> edge8(8, node4, node6, 9);
  CXXGraph::UndirectedWeightedEdge<int> edge9(9, node4, node5, 11);
  CXXGraph::UndirectedWeightedEdge<int> edge10(10, node5, node7, 10);
  CXXGraph::UndirectedWeightedEdge<int> edge11(11, node5, node6, 3);
  CXXGraph::UndirectedWeightedEdge<int> edge12(12, node6, node7, 12);

  CXXGraph::T_EdgeSet<int> edgeSet;
  edgeSet.insert(make_shared<CXXGraph::UndirectedWeightedEdge<int>>(edge1));
  edgeSet.insert(make_shared<CXXGraph::UndirectedWeightedEdge<int>>(edge2));
  edgeSet.insert(make_shared<CXXGraph::UndirectedWeightedEdge<int>>(edge3));
  edgeSet.insert(make_shared<CXXGraph::UndirectedWeightedEdge<int>>(edge4));
  edgeSet.insert(make_shared<CXXGraph::UndirectedWeightedEdge<int>>(edge5));
  edgeSet.insert(make_shared<CXXGraph::UndirectedWeightedEdge<int>>(edge6));
  edgeSet.insert(make_shared<CXXGraph::UndirectedWeightedEdge<int>>(edge7));
  edgeSet.insert(make_shared<CXXGraph::UndirectedWeightedEdge<int>>(edge8));
  edgeSet.insert(make_shared<CXXGraph::UndirectedWeightedEdge<int>>(edge9));
  edgeSet.insert(make_shared<CXXGraph::UndirectedWeightedEdge<int>>(edge10));
  edgeSet.insert(make_shared<CXXGraph::UndirectedWeightedEdge<int>>(edge11));
  edgeSet.insert(make_shared<CXXGraph::UndirectedWeightedEdge<int>>(edge12));

  CXXGraph::Graph<int> graph(edgeSet);
  CXXGraph::MstResult res = graph.boruvka();
  ASSERT_TRUE(res.success);
  ASSERT_EQ(res.mst.size(), graph.getNodeSet().size() - 1);
  ASSERT_EQ(res.mstCost, 26);
  ASSERT_EQ(res.errorMessage, "");
}

// test for directed and no weighted edge errors
TEST(BoruvkaTest, test_4) {
  CXXGraph::Node<int> node1("1", 1);
  CXXGraph::Node<int> node2("2", 2);
  CXXGraph::Node<int> node3("3", 3);
  CXXGraph::DirectedWeightedEdge<int> edge1(1, node1, node2, 1);
  CXXGraph::DirectedWeightedEdge<int> edge2(2, node2, node3, 1);
  CXXGraph::T_EdgeSet<int> edgeSet;
  edgeSet.insert(make_shared<CXXGraph::DirectedWeightedEdge<int>>(edge1));
  edgeSet.insert(make_shared<CXXGraph::DirectedWeightedEdge<int>>(edge2));

  CXXGraph::Graph<int> graph(edgeSet);
  CXXGraph::MstResult res = graph.boruvka();
  ASSERT_FALSE(res.success);
  ASSERT_EQ(res.errorMessage, CXXGraph::ERR_DIR_GRAPH);

  CXXGraph::UndirectedEdge<int> edge3(3, node1, node2);
  CXXGraph::T_EdgeSet<int> edgeSet1;
  edgeSet.insert(make_shared<CXXGraph::UndirectedEdge<int>>(edge3));

  CXXGraph::Graph<int> graph1(edgeSet1);
  res = graph1.boruvka();
  ASSERT_FALSE(res.success);
  ASSERT_EQ(res.errorMessage, CXXGraph::ERR_NO_WEIGHTED_EDGE);
}
