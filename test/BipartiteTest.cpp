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

TEST(IsBipartiteTest, bipartite_graph) {
  // Bipartite graph
  CXXGraph::Node<int> node1("1", 1);
  CXXGraph::Node<int> node2("2", 2);
  CXXGraph::Node<int> node3("3", 3);
  CXXGraph::Node<int> node4("4", 4);

  CXXGraph::UndirectedEdge<int> edge1(1, node1, node2);
  CXXGraph::UndirectedEdge<int> edge2(2, node1, node3);
  CXXGraph::UndirectedEdge<int> edge3(3, node3, node4);
  CXXGraph::UndirectedEdge<int> edge4(4, node2, node4);

  CXXGraph::T_EdgeSet<int> edgeSet;
  edgeSet.insert(make_shared<CXXGraph::UndirectedEdge<int>>(edge1));
  edgeSet.insert(make_shared<CXXGraph::UndirectedEdge<int>>(edge2));
  edgeSet.insert(make_shared<CXXGraph::UndirectedEdge<int>>(edge3));
  edgeSet.insert(make_shared<CXXGraph::UndirectedEdge<int>>(edge4));

  CXXGraph::Graph<int> graph(edgeSet);

  bool isBipartite = graph.isBipartite();
  ASSERT_EQ(isBipartite, true);  // This graph is bipartite
}

TEST(IsBipartiteTest, non_bipartite_graph) {
  // Non-bipartite graph with odd cycle
  CXXGraph::Node<int> node1("1", 1);
  CXXGraph::Node<int> node2("2", 2);
  CXXGraph::Node<int> node3("3", 3);

  CXXGraph::UndirectedEdge<int> edge1(1, node1, node2);
  CXXGraph::UndirectedEdge<int> edge2(2, node2, node3);
  CXXGraph::UndirectedEdge<int> edge3(3, node3, node1);  // Forms a cycle of 3 nodes

  CXXGraph::T_EdgeSet<int> edgeSet;
  edgeSet.insert(make_shared<CXXGraph::UndirectedEdge<int>>(edge1));
  edgeSet.insert(make_shared<CXXGraph::UndirectedEdge<int>>(edge2));
  edgeSet.insert(make_shared<CXXGraph::UndirectedEdge<int>>(edge3));

  CXXGraph::Graph<int> graph(edgeSet);

  bool isBipartite = graph.isBipartite();
  ASSERT_EQ(isBipartite, false);  // This graph has an odd-length cycle, so it's not bipartite
}

TEST(IsBipartiteTest, empty_graph) {
  // Empty graph
  CXXGraph::T_EdgeSet<int> edgeSet;
  CXXGraph::Graph<int> graph(edgeSet);

  bool isBipartite = graph.isBipartite();
  ASSERT_EQ(isBipartite, true);  // An empty graph is trivially bipartite
}

TEST(IsBipartiteTest, single_node_graph) {
  // Single node graph (trivially bipartite)
  CXXGraph::Node<int> node1("1", 1);
  CXXGraph::T_EdgeSet<int> edgeSet;
  CXXGraph::Graph<int> graph(edgeSet);

  bool isBipartite = graph.isBipartite();
  ASSERT_EQ(isBipartite, true);  // A graph with a single node is bipartite
}

TEST(IsBipartiteTest, complex_bipartite_graph) {
  // More complex bipartite graph
  CXXGraph::Node<int> node1("1", 1);
  CXXGraph::Node<int> node2("2", 2);
  CXXGraph::Node<int> node3("3", 3);
  CXXGraph::Node<int> node4("4", 4);
  CXXGraph::Node<int> node5("5", 5);
  CXXGraph::Node<int> node6("6", 6);

  CXXGraph::UndirectedEdge<int> edge1(1, node1, node2);
  CXXGraph::UndirectedEdge<int> edge2(2, node1, node3);
  CXXGraph::UndirectedEdge<int> edge3(3, node4, node5);
  CXXGraph::UndirectedEdge<int> edge4(4, node4, node6);
  CXXGraph::UndirectedEdge<int> edge5(5, node2, node4);
  CXXGraph::UndirectedEdge<int> edge6(6, node3, node5);

  CXXGraph::T_EdgeSet<int> edgeSet;
  edgeSet.insert(make_shared<CXXGraph::UndirectedEdge<int>>(edge1));
  edgeSet.insert(make_shared<CXXGraph::UndirectedEdge<int>>(edge2));
  edgeSet.insert(make_shared<CXXGraph::UndirectedEdge<int>>(edge3));
  edgeSet.insert(make_shared<CXXGraph::UndirectedEdge<int>>(edge4));
  edgeSet.insert(make_shared<CXXGraph::UndirectedEdge<int>>(edge5));
  edgeSet.insert(make_shared<CXXGraph::UndirectedEdge<int>>(edge6));

  CXXGraph::Graph<int> graph(edgeSet);

  bool isBipartite = graph.isBipartite();
  ASSERT_EQ(isBipartite, true);  // This graph is bipartite
}
