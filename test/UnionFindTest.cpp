#include "CXXGraph.hpp"
#include "gtest/gtest.h"

// Smart pointers alias
template <typename T>
using unique = std::unique_ptr<T>;
template <typename T>
using shared= std::shared_ptr<T>;

using std::make_unique;
using std::make_shared;

TEST(UnionFindTest, setFindTest1) {
  CXXGraph::Node<int> node0("0", 0);
  CXXGraph::Node<int> node1("1", 1);
  CXXGraph::Node<int> node2("2", 2);
  CXXGraph::Node<int> node3("3", 3);

  /*
          0
         1 2
        3
  */
  CXXGraph::UndirectedWeightedEdge<int> edge1(0, node0, node1, 5);
  CXXGraph::UndirectedWeightedEdge<int> edge2(1, node0, node2, 10);
  CXXGraph::UndirectedWeightedEdge<int> edge3(2, node1, node3, 5);

  // currently we are forced to construct a graph since currently setFind and
  // setUnion are functions belonging to graph class
  // can be removed if Subset becomes a class of its own
  CXXGraph::T_EdgeSet<int> edgeSet;
  edgeSet.insert(make_shared<CXXGraph::UndirectedWeightedEdge<int>>(edge1));
  CXXGraph::Graph<int> graph(edgeSet);

  // every element is a subset of itself
  std::unordered_map<unsigned long long, CXXGraph::Subset> subset;
  // {{0, 0}, {1, 0}, {2, 0}, {3, 0}};
  CXXGraph::Subset set1{0, 0}, set2{1, 0}, set3{2, 0}, set4{3, 0};
  subset = {{0, set1}, {1, set2}, {2, set3}, {3, set4}};

  auto res = graph.setFind(&subset, std::stoi(node0.getUserId()));
  ASSERT_EQ(res, 0);
  res = graph.setFind(&subset, std::stoi(node1.getUserId()));
  ASSERT_EQ(res, 1);
  res = graph.setFind(&subset, std::stoi(node2.getUserId()));
  ASSERT_EQ(res, 2);
}

TEST(UnionFindTest, setFindTest2) {
  CXXGraph::Node<int> node0("0", 0);
  CXXGraph::Node<int> node1("1", 1);
  CXXGraph::Node<int> node2("2", 2);
  CXXGraph::Node<int> node3("3", 3);
  // element 2 & 4 are subset of 0
  // element 4 is subset of 1
  std::unordered_map<unsigned long long, CXXGraph::Subset> subset;
  CXXGraph::Subset set1{0, 0}, set2{0, 0}, set3{0, 0}, set4{1, 0};
  subset = {{0, set1}, {1, set2}, {2, set3}, {3, set4}};

  CXXGraph::UndirectedWeightedEdge<int> edge1(0, node0, node1, 5);
  CXXGraph::T_EdgeSet<int> edgeSet;
  edgeSet.insert(&edge1);
  CXXGraph::Graph<int> graph(edgeSet);

  auto res = graph.setFind(&subset, std::stoi(node0.getUserId()));
  ASSERT_EQ(res, 0);
  res = graph.setFind(&subset, std::stoi(node3.getUserId()));
  ASSERT_EQ(res, 0);
  res = graph.setFind(&subset, std::stoi(node2.getUserId()));
  ASSERT_EQ(res, 0);
}

TEST(UnionFindTest, setUnionTest3) {
  CXXGraph::Node<int> node0("0", 0);
  CXXGraph::Node<int> node1("1", 1);
  CXXGraph::Node<int> node2("2", 2);
  CXXGraph::Node<int> node3("3", 3);
  // union of (node 1 & node3)  should increase node0 rank by 1
  std::unordered_map<unsigned long long, CXXGraph::Subset> subset;
  CXXGraph::Subset set1{0, 0}, set2{0, 0}, set3{0, 0}, set4{1, 0};
  subset = {{0, set1}, {1, set2}, {2, set3}, {3, set4}};

  // currently we are forced to construct a graph since currently setFind and
  // setUnion are functions belonging to graph class
  // can be removed if Subset becomes a class of its own
  CXXGraph::UndirectedWeightedEdge<int> edge1(0, node0, node1, 5);
  CXXGraph::T_EdgeSet<int> edgeSet;
  edgeSet.insert(&edge1);
  CXXGraph::Graph<int> graph(edgeSet);

  graph.setUnion(&subset, std::stoi(node1.getUserId()),
                 std::stoi(node3.getUserId()));
  ASSERT_EQ(subset[0].rank, 1);
  ASSERT_EQ(subset[3].parent, 0);

  // rank shouldn't increase since both have the same parent
  graph.setUnion(&subset, std::stoi(node2.getUserId()),
                 std::stoi(node3.getUserId()));
  ASSERT_EQ(subset[0].rank, 1);
  ASSERT_EQ(subset[3].parent, 0);
}

TEST(UnionFindTest, containsCycle) {
  CXXGraph::Node<int> node0("0", 0);
  CXXGraph::Node<int> node1("1", 1);
  CXXGraph::Node<int> node2("2", 2);

  CXXGraph::T_EdgeSet<int> edgeSet;
  CXXGraph::UndirectedWeightedEdge<int> edge0(0, node0, node1, 5);
  edgeSet.insert(&edge0);

  CXXGraph::Graph<int> graph(edgeSet);
  bool containsCycle = graph.containsCycle(&edgeSet);
  ASSERT_EQ(containsCycle, false);

  CXXGraph::UndirectedWeightedEdge<int> edge1(1, node1, node2, 10);
  edgeSet.insert(&edge1);
  containsCycle = graph.containsCycle(&edgeSet);
  ASSERT_EQ(containsCycle, false);

  CXXGraph::UndirectedWeightedEdge<int> edge2(2, node2, node0, 5);
  edgeSet.insert(&edge2);
  containsCycle = graph.containsCycle(&edgeSet);
  ASSERT_EQ(containsCycle, true);
}
