#include <memory>

#include "CXXGraph/CXXGraph.hpp"
#include "gtest/gtest.h"

// Smart pointers alias
template <typename T>
using unique = std::unique_ptr<T>;
template <typename T>
using shared = std::shared_ptr<T>;

using std::make_shared;
using std::make_unique;

// minimum spanning tree can differ so instead of checking
// the exact order of elements, we can check some properties
// like the length & cost of mst which must remain the same

// example taken from
// https://www.geeksforgeeks.org/prims-mst-for-adjacency-list-representation-greedy-algo-6/TEST(FWTest,
// test_1)
TEST(FloydWarshallTest, test_1) {
  CXXGraph::Node<int> node0("0", 0);
  CXXGraph::Node<int> node1("1", 1);
  CXXGraph::Node<int> node2("2", 2);
  CXXGraph::Node<int> node3("3", 3);
  CXXGraph::Node<int> node4("4", 4);
  CXXGraph::Node<int> node5("5", 5);
  CXXGraph::Node<int> node6("6", 6);
  CXXGraph::Node<int> node7("7", 7);
  CXXGraph::Node<int> node8("8", 8);

  CXXGraph::UndirectedWeightedEdge<int> edge1("1", node0, node1, 4);
  CXXGraph::UndirectedWeightedEdge<int> edge2("2", node0, node7, 8);
  CXXGraph::UndirectedWeightedEdge<int> edge3("3", node1, node7, 11);
  CXXGraph::UndirectedWeightedEdge<int> edge4("3", node1, node2, 8);
  CXXGraph::UndirectedWeightedEdge<int> edge5("4", node7, node8, 7);
  CXXGraph::UndirectedWeightedEdge<int> edge6("3", node7, node6, 1);
  CXXGraph::UndirectedWeightedEdge<int> edge7("3", node8, node2, 2);
  CXXGraph::UndirectedWeightedEdge<int> edge8("3", node8, node6, 6);
  CXXGraph::UndirectedWeightedEdge<int> edge9("3", node2, node5, 4);
  CXXGraph::UndirectedWeightedEdge<int> edge10("3", node2, node3, 7);
  CXXGraph::UndirectedWeightedEdge<int> edge11("3", node6, node5, 2);
  CXXGraph::UndirectedWeightedEdge<int> edge12("3", node3, node4, 9);
  CXXGraph::UndirectedWeightedEdge<int> edge13("3", node3, node5, 14);
  CXXGraph::UndirectedWeightedEdge<int> edge14("3", node5, node4, 10);

  CXXGraph::T_EdgeSet<int> edgeSet;
  edgeSet.insert(make_shared<CXXGraph::UndirectedWeightedEdge<int>>(edge1));
  edgeSet.insert(make_shared<CXXGraph::UndirectedWeightedEdge<int>>(edge5));
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
  CXXGraph::FWResult res = graph.floydWarshall();

  ASSERT_TRUE(res.success);
  ASSERT_FALSE(res.negativeCycle);
  ASSERT_EQ(res.errorMessage, "");
}

TEST(FloydWarshallTest, test_2) {
  CXXGraph::Node<int> node0("0", 0);
  CXXGraph::Node<int> node1("1", 1);

  CXXGraph::UndirectedWeightedEdge<int> edge1("1", node0, node1, 1);

  CXXGraph::T_EdgeSet<int> edgeSet;
  edgeSet.insert(make_shared<CXXGraph::UndirectedWeightedEdge<int>>(edge1));

  CXXGraph::Graph<int> graph(edgeSet);
  CXXGraph::FWResult res = graph.floydWarshall();

  auto distance_0_1 = res.result.find(std::make_pair("0", "1"));
  auto distance_1_0 = res.result.find(std::make_pair("1", "0"));

  ASSERT_TRUE(res.success);
  ASSERT_FALSE(res.negativeCycle);
  ASSERT_EQ(res.errorMessage, "");
  ASSERT_EQ(distance_0_1->second, distance_1_0->second);
}