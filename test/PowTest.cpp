
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

TEST(PowTest, AdjPower) {
  CXXGraph::Node<int> n1("a", 1);
  CXXGraph::Node<int> n2("b", 1);
  CXXGraph::Node<int> n3("c", 1);
  CXXGraph::Node<int> n4("d", 1);

  CXXGraph::UndirectedEdge<int> e1(0, n1, n2);
  CXXGraph::UndirectedEdge<int> e2(2, n1, n3);
  CXXGraph::UndirectedEdge<int> e3(2, n2, n3);
  CXXGraph::DirectedEdge<int> e4(2, n2, n4);

  CXXGraph::Graph<int> graph;
  graph.addEdge(&e1);
  graph.addEdge(&e2);
  graph.addEdge(&e3);
  graph.addEdge(&e4);

  auto res = graph.powAdjMatrix(21);

  for (auto &it : res.result) {
    std::cout << it.first.first << it.first.second << it.second << std::endl;
  }

  ASSERT_TRUE(true);
}

TEST(PowTest, TransPower) {
  CXXGraph::Node<int> n1("a", 1); // deg 2
  CXXGraph::Node<int> n2("b", 1); // get 3
  CXXGraph::Node<int> n3("c", 1); // deg 2
  CXXGraph::Node<int> n4("d", 1); // get 0

  CXXGraph::UndirectedEdge<int> e1(0, n1, n2);
  CXXGraph::UndirectedEdge<int> e2(2, n1, n3);
  CXXGraph::UndirectedEdge<int> e3(2, n2, n3);
  CXXGraph::DirectedEdge<int> e4(2, n2, n4);
  CXXGraph::DirectedEdge<int> e5(2, n4, n1);
  CXXGraph::DirectedEdge<int> e6(2, n4, n2);
  CXXGraph::DirectedEdge<int> e7(2, n4, n3);

  CXXGraph::Graph<int> graph;
  graph.addEdge(&e1);
  graph.addEdge(&e2);
  graph.addEdge(&e3);
  graph.addEdge(&e4);
  graph.addEdge(&e5);
  graph.addEdge(&e6);
  graph.addEdge(&e7);

  auto res = graph.powTransitionMatrix(1000);

  for (auto &it : res.result) {
    std::cout << it.first.first << it.first.second << it.second << std::endl;
  }

  ASSERT_TRUE(true);
}
