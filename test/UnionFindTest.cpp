#include "CXXGraph.hpp"
#include "gtest/gtest.h"

TEST(UnionFindTest, setFindTest1) {
  CXXGRAPH::Node<int> node0("0", 0);
  CXXGRAPH::Node<int> node1("1", 1);
  CXXGRAPH::Node<int> node2("2", 2);
  CXXGRAPH::Node<int> node3("3", 3);

  /*
          0
         1 2
        3
  */
  CXXGRAPH::UndirectedWeightedEdge<int> edge1(0, node0, node1, 5);
  CXXGRAPH::UndirectedWeightedEdge<int> edge2(1, node0, node2, 10);
  CXXGRAPH::UndirectedWeightedEdge<int> edge3(2, node1, node3, 5);

  // currently we are forced to construct a graph since currently setFind and
  // setUnion are functions belonging to graph class
  // can be removed if Subset becomes a class of its own
  CXXGRAPH::T_EdgeSet<int> edgeSet;
  edgeSet.insert(&edge1);
  CXXGRAPH::Graph<int> graph(edgeSet);

  // every element is a subset of itself
  std::unordered_map<unsigned long long, CXXGRAPH::Subset> subset;
  // {{0, 0}, {1, 0}, {2, 0}, {3, 0}};
  CXXGRAPH::Subset set1{0, 0}, set2{1, 0}, set3{2, 0}, set4{3, 0};
  subset = {{0, set1}, {1, set2}, {2, set3}, {3, set4}};

  auto res = graph.setFind(&subset, std::stoi(node0.getUserId()));
  ASSERT_EQ(res, 0);
  res = graph.setFind(&subset, std::stoi(node1.getUserId()));
  ASSERT_EQ(res, 1);
  res = graph.setFind(&subset, std::stoi(node2.getUserId()));
  ASSERT_EQ(res, 2);
}

TEST(UnionFindTest, setFindTest2) {
  CXXGRAPH::Node<int> node0("0", 0);
  CXXGRAPH::Node<int> node1("1", 1);
  CXXGRAPH::Node<int> node2("2", 2);
  CXXGRAPH::Node<int> node3("3", 3);
  // element 2 & 4 are subset of 0
  // element 4 is subset of 1
  std::unordered_map<unsigned long long, CXXGRAPH::Subset> subset;
  CXXGRAPH::Subset set1{0, 0}, set2{0, 0}, set3{0, 0}, set4{1, 0};
  subset = {{0, set1}, {1, set2}, {2, set3}, {3, set4}};

  CXXGRAPH::UndirectedWeightedEdge<int> edge1(0, node0, node1, 5);
  CXXGRAPH::T_EdgeSet<int> edgeSet;
  edgeSet.insert(&edge1);
  CXXGRAPH::Graph<int> graph(edgeSet);

  auto res = graph.setFind(&subset, std::stoi(node0.getUserId()));
  ASSERT_EQ(res, 0);
  res = graph.setFind(&subset, std::stoi(node3.getUserId()));
  ASSERT_EQ(res, 0);
  res = graph.setFind(&subset, std::stoi(node2.getUserId()));
  ASSERT_EQ(res, 0);
}

TEST(UnionFindTest, setUnionTest3) {
  CXXGRAPH::Node<int> node0("0", 0);
  CXXGRAPH::Node<int> node1("1", 1);
  CXXGRAPH::Node<int> node2("2", 2);
  CXXGRAPH::Node<int> node3("3", 3);
  // union of (node 1 & node3)  should increase node0 rank by 1
  std::unordered_map<unsigned long long, CXXGRAPH::Subset> subset;
  CXXGRAPH::Subset set1{0, 0}, set2{0, 0}, set3{0, 0}, set4{1, 0};
  subset = {{0, set1}, {1, set2}, {2, set3}, {3, set4}};

  // currently we are forced to construct a graph since currently setFind and
  // setUnion are functions belonging to graph class
  // can be removed if Subset becomes a class of its own
  CXXGRAPH::UndirectedWeightedEdge<int> edge1(0, node0, node1, 5);
  CXXGRAPH::T_EdgeSet<int> edgeSet;
  edgeSet.insert(&edge1);
  CXXGRAPH::Graph<int> graph(edgeSet);

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
  CXXGRAPH::Node<int> node0("0", 0);
  CXXGRAPH::Node<int> node1("1", 1);
  CXXGRAPH::Node<int> node2("2", 2);

  CXXGRAPH::T_EdgeSet<int> edgeSet;
  CXXGRAPH::UndirectedWeightedEdge<int> edge0(0, node0, node1, 5);
  edgeSet.insert(&edge0);

  CXXGRAPH::Graph<int> graph(edgeSet);
  bool containsCycle = graph.containsCycle(&edgeSet);
  ASSERT_EQ(containsCycle, false);

  CXXGRAPH::UndirectedWeightedEdge<int> edge1(1, node1, node2, 10);
  edgeSet.insert(&edge1);
  containsCycle = graph.containsCycle(&edgeSet);
  ASSERT_EQ(containsCycle, false);

  CXXGRAPH::UndirectedWeightedEdge<int> edge2(2, node2, node0, 5);
  edgeSet.insert(&edge2);
  containsCycle = graph.containsCycle(&edgeSet);
  ASSERT_EQ(containsCycle, true);
}