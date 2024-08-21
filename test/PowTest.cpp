
#include <memory>

#include "CXXGraph/CXXGraph.hpp"
#include "gtest/gtest.h"

// include it to check that the static asserts don't fail
#include "TypeTraitsTest.hpp"

// Smart pointers alias
template <typename T>
using unique = std::unique_ptr<T>;
template <typename T>
using shared = std::shared_ptr<T>;

using std::make_shared;
using std::make_unique;

// https://eng.libretexts.org/Bookshelves/Computer_Science/Programming_and_Computation_Fundamentals/Mathematics_for_Computer_Science_(Lehman_Leighton_and_Meyer)/02%3A_Structures/09%3A_Directed_graphs_and_Partial_Orders/9.03%3A_Adjacency_Matrices
TEST(PowAdjTest, libre_texts) {
  CXXGraph::Node<int> a("a", 1);
  CXXGraph::Node<int> b("b", 1);
  CXXGraph::Node<int> c("c", 1);
  CXXGraph::Node<int> d("d", 1);

  CXXGraph::DirectedEdge<int> e1(0, a, b);
  CXXGraph::DirectedEdge<int> e2(1, a, d);
  CXXGraph::DirectedEdge<int> e3(2, b, c);
  CXXGraph::DirectedEdge<int> e4(3, b, d);
  CXXGraph::DirectedEdge<int> e5(4, c, b);
  CXXGraph::DirectedEdge<int> e6(5, d, c);

  CXXGraph::Graph<int> graph;
  graph.addEdge(&e1);
  graph.addEdge(&e2);
  graph.addEdge(&e3);
  graph.addEdge(&e4);
  graph.addEdge(&e5);
  graph.addEdge(&e6);

  auto res = graph.powAdjMatrix(2);

  ASSERT_TRUE(res.success);
  ASSERT_TRUE(res.result[std::make_pair("a", "c")] == 2);
  ASSERT_TRUE(res.result[std::make_pair("a", "d")] == 1);
  ASSERT_TRUE(res.result[std::make_pair("b", "b")] == 1);
  ASSERT_TRUE(res.result[std::make_pair("b", "c")] == 1);
  ASSERT_TRUE(res.result[std::make_pair("c", "c")] == 1);
  ASSERT_TRUE(res.result[std::make_pair("c", "d")] == 1);
  ASSERT_TRUE(res.result[std::make_pair("d", "b")] == 1);
  ASSERT_TRUE(res.result[std::make_pair("c", "a")] == 0);
  ASSERT_TRUE(res.result[std::make_pair("d", "c")] == 0);
}

// https://docs.dgl.ai/generated/dgl.khop_adj.html#dgl.khop_adj
TEST(PowAdjTest, dgl) {
  CXXGraph::Node<int> a("a", 1);
  CXXGraph::Node<int> b("b", 1);
  CXXGraph::Node<int> c("c", 1);
  CXXGraph::Node<int> d("d", 1);
  CXXGraph::Node<int> e("e", 1);

  CXXGraph::DirectedEdge<int> e1(0, a, a);
  CXXGraph::DirectedEdge<int> e2(1, b, b);
  CXXGraph::DirectedEdge<int> e3(2, c, c);
  CXXGraph::DirectedEdge<int> e4(3, d, d);
  CXXGraph::DirectedEdge<int> e5(4, e, e);
  CXXGraph::DirectedEdge<int> e6(5, a, b);
  CXXGraph::DirectedEdge<int> e7(6, b, c);
  CXXGraph::DirectedEdge<int> e8(7, c, d);
  CXXGraph::DirectedEdge<int> e9(8, d, e);
  CXXGraph::DirectedEdge<int> e10(9, d, a);

  CXXGraph::Graph<int> graph;
  graph.addEdge(&e1);
  graph.addEdge(&e2);
  graph.addEdge(&e3);
  graph.addEdge(&e4);
  graph.addEdge(&e5);
  graph.addEdge(&e6);
  graph.addEdge(&e7);
  graph.addEdge(&e8);
  graph.addEdge(&e9);
  graph.addEdge(&e10);

  auto res = graph.powAdjMatrix(3);

  ASSERT_TRUE(res.success);
  ASSERT_TRUE(res.result[std::make_pair("a", "a")] == 1);
  ASSERT_TRUE(res.result[std::make_pair("b", "b")] == 1);
  ASSERT_TRUE(res.result[std::make_pair("c", "c")] == 1);
  ASSERT_TRUE(res.result[std::make_pair("d", "d")] == 1);
  ASSERT_TRUE(res.result[std::make_pair("e", "e")] == 1);
  ASSERT_TRUE(res.result[std::make_pair("a", "b")] == 3);
  ASSERT_TRUE(res.result[std::make_pair("c", "d")] == 3);
  ASSERT_TRUE(res.result[std::make_pair("c", "e")] == 3);
  ASSERT_TRUE(res.result[std::make_pair("e", "d")] == 0);
}

TEST(PowTransTest, transition_matrix) {
  CXXGraph::Node<int> n1("a", 1); // deg 2
  CXXGraph::Node<int> n2("b", 1); // get 3
  CXXGraph::Node<int> n3("c", 1); // deg 2
  CXXGraph::Node<int> n4("d", 1); // get 0

  CXXGraph::UndirectedEdge<int> e1(0, n1, n2);
  CXXGraph::UndirectedEdge<int> e2(1, n1, n3);
  CXXGraph::UndirectedEdge<int> e3(2, n2, n3);
  CXXGraph::DirectedEdge<int> e4(3, n2, n4);
  CXXGraph::DirectedEdge<int> e5(4, n4, n1);
  CXXGraph::DirectedEdge<int> e6(5, n4, n2);
  CXXGraph::DirectedEdge<int> e7(6, n4, n3);

  CXXGraph::Graph<int> graph;
  graph.addEdge(&e1);
  graph.addEdge(&e2);
  graph.addEdge(&e3);
  graph.addEdge(&e4);
  graph.addEdge(&e5);
  graph.addEdge(&e6);
  graph.addEdge(&e7);

  auto res = graph.powTransitionMatrix(10);

  const double threshold = 1e-3;

  ASSERT_TRUE(res.success);
  ASSERT_NEAR(res.result[std::make_pair("a", "a")], 0.286, threshold);
  ASSERT_NEAR(res.result[std::make_pair("a", "b")], 0.321, threshold);
  ASSERT_NEAR(res.result[std::make_pair("c", "d")], 0.107, threshold);
  ASSERT_NEAR(res.result[std::make_pair("c", "c")], 0.286, threshold);
  ASSERT_NEAR(res.result[std::make_pair("d", "a")], 0.286, threshold);
  ASSERT_NEAR(res.result[std::make_pair("a", "d")], 0.107, threshold);
}
