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

TEST(BronKerboschTest, test_1) {
  CXXGraph::Node<int> node0("0", 0);
  CXXGraph::Node<int> node1("1", 1);
  CXXGraph::Node<int> node2("2", 2);
  CXXGraph::Node<int> node3("3", 3);
  CXXGraph::Node<int> node4("4", 4);

  CXXGraph::UndirectedEdge<int> edge0(0, node0, node1);
  CXXGraph::UndirectedEdge<int> edge1(0, node0, node2);
  CXXGraph::UndirectedEdge<int> edge2(0, node2, node1);
  CXXGraph::UndirectedEdge<int> edge3(0, node2, node3);
  CXXGraph::UndirectedEdge<int> edge4(0, node2, node4);
  CXXGraph::UndirectedEdge<int> edge5(0, node3, node4);

  CXXGraph::T_EdgeSet<int> edgeSet;
  edgeSet.insert(make_shared<CXXGraph::UndirectedEdge<int>>(edge0));
  edgeSet.insert(make_shared<CXXGraph::UndirectedEdge<int>>(edge1));
  edgeSet.insert(make_shared<CXXGraph::UndirectedEdge<int>>(edge2));
  edgeSet.insert(make_shared<CXXGraph::UndirectedEdge<int>>(edge3));
  edgeSet.insert(make_shared<CXXGraph::UndirectedEdge<int>>(edge4));
  edgeSet.insert(make_shared<CXXGraph::UndirectedEdge<int>>(edge5));

  CXXGraph::Graph<int> graph(edgeSet);
  CXXGraph::BronKerboschResult<int> res = graph.bron_kerbosch();

  ASSERT_TRUE(res.success);
  ASSERT_EQ(res.maximalCliques.size(), 2);
  ASSERT_EQ(res.errorMessage, "");
  ASSERT_TRUE(std::find(res.maximalCliques.begin(), res.maximalCliques.end(),
                        CXXGraph::T_NodeSet<int>{
                            make_shared<CXXGraph::Node<int>>(node0),
                            make_shared<CXXGraph::Node<int>>(node1),
                            make_shared<CXXGraph::Node<int>>(node2)}) !=
              res.maximalCliques.end());
  ASSERT_TRUE(std::find(res.maximalCliques.begin(), res.maximalCliques.end(),
                        CXXGraph::T_NodeSet<int>{
                            make_shared<CXXGraph::Node<int>>(node2),
                            make_shared<CXXGraph::Node<int>>(node3),
                            make_shared<CXXGraph::Node<int>>(node4)}) !=
              res.maximalCliques.end());
}

// Empty graph E_5
TEST(BronKerboschTest, test_2) {
  CXXGraph::Node<int> node0("0", 0);
  CXXGraph::Node<int> node1("1", 1);
  CXXGraph::Node<int> node2("2", 2);
  CXXGraph::Node<int> node3("3", 3);
  CXXGraph::Node<int> node4("4", 4);

  CXXGraph::T_EdgeSet<int> edgeSet;
  CXXGraph::Graph<int> graph(edgeSet);

  graph.addNode(&node0);
  graph.addNode(&node1);
  graph.addNode(&node2);
  graph.addNode(&node3);
  graph.addNode(&node4);

  CXXGraph::BronKerboschResult<int> res = graph.bron_kerbosch();
  ASSERT_TRUE(res.success);
  ASSERT_EQ(res.maximalCliques.size(), 5);
  ASSERT_EQ(res.errorMessage, "");
  ASSERT_TRUE(std::find(res.maximalCliques.begin(), res.maximalCliques.end(),
                        CXXGraph::T_NodeSet<int>{
                            make_shared<CXXGraph::Node<int>>(node0)}) !=
              res.maximalCliques.end());
  ASSERT_TRUE(std::find(res.maximalCliques.begin(), res.maximalCliques.end(),
                        CXXGraph::T_NodeSet<int>{
                            make_shared<CXXGraph::Node<int>>(node1)}) !=
              res.maximalCliques.end());
  ASSERT_TRUE(std::find(res.maximalCliques.begin(), res.maximalCliques.end(),
                        CXXGraph::T_NodeSet<int>{
                            make_shared<CXXGraph::Node<int>>(node2)}) !=
              res.maximalCliques.end());
  ASSERT_TRUE(std::find(res.maximalCliques.begin(), res.maximalCliques.end(),
                        CXXGraph::T_NodeSet<int>{
                            make_shared<CXXGraph::Node<int>>(node3)}) !=
              res.maximalCliques.end());
  ASSERT_TRUE(std::find(res.maximalCliques.begin(), res.maximalCliques.end(),
                        CXXGraph::T_NodeSet<int>{
                            make_shared<CXXGraph::Node<int>>(node4)}) !=
              res.maximalCliques.end());
}

// Complete graph K_5
TEST(BronKerboschTest, test_3) {
  CXXGraph::Node<int> node0("0", 0);
  CXXGraph::Node<int> node1("1", 1);
  CXXGraph::Node<int> node2("2", 2);
  CXXGraph::Node<int> node3("3", 3);
  CXXGraph::Node<int> node4("4", 4);

  CXXGraph::UndirectedEdge<int> edge0(0, node0, node1);
  CXXGraph::UndirectedEdge<int> edge1(1, node0, node2);
  CXXGraph::UndirectedEdge<int> edge2(2, node0, node3);
  CXXGraph::UndirectedEdge<int> edge3(3, node0, node4);
  CXXGraph::UndirectedEdge<int> edge4(4, node1, node2);
  CXXGraph::UndirectedEdge<int> edge5(5, node1, node3);
  CXXGraph::UndirectedEdge<int> edge6(6, node1, node4);
  CXXGraph::UndirectedEdge<int> edge7(7, node2, node3);
  CXXGraph::UndirectedEdge<int> edge8(8, node2, node4);
  CXXGraph::UndirectedEdge<int> edge9(9, node3, node4);

  CXXGraph::T_EdgeSet<int> edgeSet;
  edgeSet.insert(make_shared<CXXGraph::UndirectedEdge<int>>(edge0));
  edgeSet.insert(make_shared<CXXGraph::UndirectedEdge<int>>(edge1));
  edgeSet.insert(make_shared<CXXGraph::UndirectedEdge<int>>(edge2));
  edgeSet.insert(make_shared<CXXGraph::UndirectedEdge<int>>(edge3));
  edgeSet.insert(make_shared<CXXGraph::UndirectedEdge<int>>(edge4));
  edgeSet.insert(make_shared<CXXGraph::UndirectedEdge<int>>(edge5));
  edgeSet.insert(make_shared<CXXGraph::UndirectedEdge<int>>(edge6));
  edgeSet.insert(make_shared<CXXGraph::UndirectedEdge<int>>(edge7));
  edgeSet.insert(make_shared<CXXGraph::UndirectedEdge<int>>(edge8));
  edgeSet.insert(make_shared<CXXGraph::UndirectedEdge<int>>(edge9));

  CXXGraph::Graph<int> graph(edgeSet);
  CXXGraph::BronKerboschResult<int> res = graph.bron_kerbosch();

  ASSERT_TRUE(res.success);
  ASSERT_EQ(res.maximalCliques.size(), 1);
  ASSERT_EQ(res.errorMessage, "");
  ASSERT_TRUE(std::find(res.maximalCliques.begin(), res.maximalCliques.end(),
                        CXXGraph::T_NodeSet<int>{
                            make_shared<CXXGraph::Node<int>>(node0),
                            make_shared<CXXGraph::Node<int>>(node1),
                            make_shared<CXXGraph::Node<int>>(node2),
                            make_shared<CXXGraph::Node<int>>(node3),
                            make_shared<CXXGraph::Node<int>>(node4)}) !=
              res.maximalCliques.end());
}

// Graph with a directed edge
TEST(BronKerboschTest, test_4) {
  CXXGraph::Node<int> node0("0", 0);
  CXXGraph::Node<int> node1("1", 1);
  CXXGraph::Node<int> node2("2", 2);
  CXXGraph::Node<int> node3("3", 3);
  CXXGraph::Node<int> node4("4", 4);

  CXXGraph::DirectedEdge<int> edge0(0, node0, node1);
  CXXGraph::UndirectedEdge<int> edge1(0, node0, node2);
  CXXGraph::UndirectedEdge<int> edge2(0, node2, node1);
  CXXGraph::UndirectedEdge<int> edge3(0, node2, node3);
  CXXGraph::UndirectedEdge<int> edge4(0, node2, node4);
  CXXGraph::UndirectedEdge<int> edge5(0, node3, node4);

  CXXGraph::T_EdgeSet<int> edgeSet;
  edgeSet.insert(make_shared<CXXGraph::DirectedEdge<int>>(edge0));
  edgeSet.insert(make_shared<CXXGraph::UndirectedEdge<int>>(edge1));
  edgeSet.insert(make_shared<CXXGraph::UndirectedEdge<int>>(edge2));
  edgeSet.insert(make_shared<CXXGraph::UndirectedEdge<int>>(edge3));
  edgeSet.insert(make_shared<CXXGraph::UndirectedEdge<int>>(edge4));
  edgeSet.insert(make_shared<CXXGraph::UndirectedEdge<int>>(edge5));

  CXXGraph::Graph<int> graph(edgeSet);
  CXXGraph::BronKerboschResult<int> res = graph.bron_kerbosch();

  ASSERT_FALSE(res.success);
  ASSERT_EQ(res.errorMessage, "Graph is directed");
}
