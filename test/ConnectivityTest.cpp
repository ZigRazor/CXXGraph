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

TEST(ConnectivityTest, test_1) {
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

  ASSERT_TRUE(graph.isConnectedGraph());
}

TEST(ConnectivityTest, test_2) {
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

  ASSERT_FALSE(graph.isStronglyConnectedGraph());
}

TEST(ConnectivityTest, test_3) {
  CXXGraph::Node<int> node0("0", 0);
  CXXGraph::Node<int> node1("1", 1);
  CXXGraph::Node<int> node2("2", 2);
  CXXGraph::Node<int> node3("3", 3);
  CXXGraph::Node<int> node4("4", 4);
  CXXGraph::Node<int> node5("5", 5);
  CXXGraph::Node<int> node6("6", 6);
  CXXGraph::Node<int> node7("7", 7);
  CXXGraph::Node<int> node8("8", 8);

  CXXGraph::DirectedWeightedEdge<int> edge1("1", node0, node1, 4);
  CXXGraph::DirectedWeightedEdge<int> edge2("2", node0, node7, 8);
  CXXGraph::DirectedWeightedEdge<int> edge3("3", node1, node7, 11);
  CXXGraph::DirectedWeightedEdge<int> edge4("3", node1, node2, 8);
  CXXGraph::DirectedWeightedEdge<int> edge5("4", node7, node8, 7);
  CXXGraph::DirectedWeightedEdge<int> edge6("3", node7, node6, 1);
  CXXGraph::DirectedWeightedEdge<int> edge7("3", node8, node2, 2);
  CXXGraph::DirectedWeightedEdge<int> edge8("3", node8, node6, 6);
  CXXGraph::DirectedWeightedEdge<int> edge9("3", node2, node5, 4);
  CXXGraph::DirectedWeightedEdge<int> edge10("3", node2, node3, 7);
  CXXGraph::DirectedWeightedEdge<int> edge11("3", node6, node5, 2);
  CXXGraph::DirectedWeightedEdge<int> edge12("3", node3, node4, 9);
  CXXGraph::DirectedWeightedEdge<int> edge13("3", node3, node5, 14);
  CXXGraph::DirectedWeightedEdge<int> edge14("3", node5, node4, 10);
  CXXGraph::DirectedWeightedEdge<int> edge15("3", node1, node0, 10);
  CXXGraph::DirectedWeightedEdge<int> edge16("3", node2, node0, 10);
  CXXGraph::DirectedWeightedEdge<int> edge17("3", node3, node0, 10);
  CXXGraph::DirectedWeightedEdge<int> edge18("3", node4, node0, 10);
  CXXGraph::DirectedWeightedEdge<int> edge19("3", node5, node0, 10);
  CXXGraph::DirectedWeightedEdge<int> edge20("3", node6, node0, 10);
  CXXGraph::DirectedWeightedEdge<int> edge21("3", node7, node0, 10);
  CXXGraph::DirectedWeightedEdge<int> edge22("3", node8, node0, 10);

  CXXGraph::T_EdgeSet<int> edgeSet;
  edgeSet.insert(make_shared<CXXGraph::DirectedWeightedEdge<int>>(edge1));
  edgeSet.insert(make_shared<CXXGraph::DirectedWeightedEdge<int>>(edge2));
  edgeSet.insert(make_shared<CXXGraph::DirectedWeightedEdge<int>>(edge3));
  edgeSet.insert(make_shared<CXXGraph::DirectedWeightedEdge<int>>(edge4));
  edgeSet.insert(make_shared<CXXGraph::DirectedWeightedEdge<int>>(edge5));
  edgeSet.insert(make_shared<CXXGraph::DirectedWeightedEdge<int>>(edge6));
  edgeSet.insert(make_shared<CXXGraph::DirectedWeightedEdge<int>>(edge7));
  edgeSet.insert(make_shared<CXXGraph::DirectedWeightedEdge<int>>(edge8));
  edgeSet.insert(make_shared<CXXGraph::DirectedWeightedEdge<int>>(edge9));
  edgeSet.insert(make_shared<CXXGraph::DirectedWeightedEdge<int>>(edge10));
  edgeSet.insert(make_shared<CXXGraph::DirectedWeightedEdge<int>>(edge11));
  edgeSet.insert(make_shared<CXXGraph::DirectedWeightedEdge<int>>(edge12));
  edgeSet.insert(make_shared<CXXGraph::DirectedWeightedEdge<int>>(edge13));
  edgeSet.insert(make_shared<CXXGraph::DirectedWeightedEdge<int>>(edge14));
  edgeSet.insert(make_shared<CXXGraph::DirectedWeightedEdge<int>>(edge15));
  edgeSet.insert(make_shared<CXXGraph::DirectedWeightedEdge<int>>(edge16));
  edgeSet.insert(make_shared<CXXGraph::DirectedWeightedEdge<int>>(edge17));
  edgeSet.insert(make_shared<CXXGraph::DirectedWeightedEdge<int>>(edge18));
  edgeSet.insert(make_shared<CXXGraph::DirectedWeightedEdge<int>>(edge19));
  edgeSet.insert(make_shared<CXXGraph::DirectedWeightedEdge<int>>(edge20));
  edgeSet.insert(make_shared<CXXGraph::DirectedWeightedEdge<int>>(edge21));
  edgeSet.insert(make_shared<CXXGraph::DirectedWeightedEdge<int>>(edge22));

  CXXGraph::Graph<int> graph(edgeSet);

  ASSERT_TRUE(graph.isStronglyConnectedGraph());
}

TEST(ConnectivityTest, test_4) {
  CXXGraph::Node<int> node0("0", 0);
  CXXGraph::Node<int> node1("1", 1);
  CXXGraph::Node<int> node2("2", 2);
  CXXGraph::Node<int> node3("3", 3);
  CXXGraph::Node<int> node4("4", 4);
  CXXGraph::Node<int> node5("5", 5);
  CXXGraph::Node<int> node6("6", 6);
  CXXGraph::Node<int> node7("7", 7);
  CXXGraph::Node<int> node8("8", 8);

  CXXGraph::DirectedWeightedEdge<int> edge1("1", node0, node1, 4);
  CXXGraph::DirectedWeightedEdge<int> edge2("2", node0, node7, 8);
  CXXGraph::DirectedWeightedEdge<int> edge3("3", node1, node7, 11);
  CXXGraph::DirectedWeightedEdge<int> edge4("3", node1, node2, 8);
  CXXGraph::DirectedWeightedEdge<int> edge5("4", node7, node8, 7);
  CXXGraph::DirectedWeightedEdge<int> edge6("3", node7, node6, 1);
  CXXGraph::DirectedWeightedEdge<int> edge7("3", node8, node2, 2);
  CXXGraph::DirectedWeightedEdge<int> edge8("3", node8, node6, 6);
  CXXGraph::DirectedWeightedEdge<int> edge9("3", node2, node5, 4);
  CXXGraph::DirectedWeightedEdge<int> edge10("3", node2, node3, 7);
  CXXGraph::DirectedWeightedEdge<int> edge11("3", node6, node5, 2);
  CXXGraph::DirectedWeightedEdge<int> edge12("3", node3, node4, 9);
  CXXGraph::DirectedWeightedEdge<int> edge13("3", node3, node5, 14);
  CXXGraph::DirectedWeightedEdge<int> edge14("3", node5, node4, 10);

  CXXGraph::T_EdgeSet<int> edgeSet;
  edgeSet.insert(make_shared<CXXGraph::DirectedWeightedEdge<int>>(edge1));
  edgeSet.insert(make_shared<CXXGraph::DirectedWeightedEdge<int>>(edge2));
  edgeSet.insert(make_shared<CXXGraph::DirectedWeightedEdge<int>>(edge3));
  edgeSet.insert(make_shared<CXXGraph::DirectedWeightedEdge<int>>(edge4));
  edgeSet.insert(make_shared<CXXGraph::DirectedWeightedEdge<int>>(edge5));
  edgeSet.insert(make_shared<CXXGraph::DirectedWeightedEdge<int>>(edge6));
  edgeSet.insert(make_shared<CXXGraph::DirectedWeightedEdge<int>>(edge7));
  edgeSet.insert(make_shared<CXXGraph::DirectedWeightedEdge<int>>(edge8));
  edgeSet.insert(make_shared<CXXGraph::DirectedWeightedEdge<int>>(edge9));
  edgeSet.insert(make_shared<CXXGraph::DirectedWeightedEdge<int>>(edge10));
  edgeSet.insert(make_shared<CXXGraph::DirectedWeightedEdge<int>>(edge11));
  edgeSet.insert(make_shared<CXXGraph::DirectedWeightedEdge<int>>(edge12));
  edgeSet.insert(make_shared<CXXGraph::DirectedWeightedEdge<int>>(edge13));
  edgeSet.insert(make_shared<CXXGraph::DirectedWeightedEdge<int>>(edge14));

  CXXGraph::Graph<int> graph(edgeSet);

  ASSERT_FALSE(graph.isConnectedGraph());
}

TEST(ConnectivityTest, test_5) {
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
  edgeSet.insert(make_shared<CXXGraph::DirectedWeightedEdge<int>>(edge1));
  edgeSet.insert(make_shared<CXXGraph::DirectedWeightedEdge<int>>(edge2));
  edgeSet.insert(make_shared<CXXGraph::DirectedWeightedEdge<int>>(edge3));
  edgeSet.insert(make_shared<CXXGraph::DirectedWeightedEdge<int>>(edge4));
  edgeSet.insert(make_shared<CXXGraph::DirectedWeightedEdge<int>>(edge5));
  edgeSet.insert(make_shared<CXXGraph::DirectedWeightedEdge<int>>(edge6));
  edgeSet.insert(make_shared<CXXGraph::DirectedWeightedEdge<int>>(edge7));
  edgeSet.insert(make_shared<CXXGraph::DirectedWeightedEdge<int>>(edge8));
  edgeSet.insert(make_shared<CXXGraph::DirectedWeightedEdge<int>>(edge9));
  edgeSet.insert(make_shared<CXXGraph::DirectedWeightedEdge<int>>(edge10));
  edgeSet.insert(make_shared<CXXGraph::DirectedWeightedEdge<int>>(edge11));
  edgeSet.insert(make_shared<CXXGraph::DirectedWeightedEdge<int>>(edge12));
  edgeSet.insert(make_shared<CXXGraph::DirectedWeightedEdge<int>>(edge13));
  edgeSet.insert(make_shared<CXXGraph::DirectedWeightedEdge<int>>(edge14));

  CXXGraph::Graph<int> graph(edgeSet);

  ASSERT_FALSE(graph.isConnectedGraph());
}

TEST(ConnectivityTest, test_6) {
  CXXGraph::Node<int> node0("0", 0);
  CXXGraph::Node<int> node1("1", 1);
  CXXGraph::Node<int> node2("2", 2);
  CXXGraph::Node<int> node3("3", 3);
  CXXGraph::Node<int> node4("4", 4);
  CXXGraph::Node<int> node5("5", 5);
  CXXGraph::Node<int> node6("6", 6);
  CXXGraph::Node<int> node7("7", 7);
  CXXGraph::Node<int> node8("8", 8);

  CXXGraph::DirectedWeightedEdge<int> edge1("1", node0, node1, 4);
  CXXGraph::DirectedWeightedEdge<int> edge2("2", node0, node7, 8);
  CXXGraph::DirectedWeightedEdge<int> edge3("3", node1, node7, 11);
  CXXGraph::DirectedWeightedEdge<int> edge4("3", node1, node2, 8);
  CXXGraph::DirectedWeightedEdge<int> edge5("4", node7, node8, 7);
  CXXGraph::DirectedWeightedEdge<int> edge6("3", node7, node6, 1);
  CXXGraph::DirectedWeightedEdge<int> edge9("3", node2, node5, 4);
  CXXGraph::DirectedWeightedEdge<int> edge10("3", node2, node3, 7);
  CXXGraph::DirectedWeightedEdge<int> edge11("3", node6, node5, 2);
  CXXGraph::DirectedWeightedEdge<int> edge12("3", node3, node4, 9);
  CXXGraph::DirectedWeightedEdge<int> edge13("3", node3, node5, 14);
  CXXGraph::DirectedWeightedEdge<int> edge14("3", node5, node4, 10);
  CXXGraph::DirectedWeightedEdge<int> edge15("3", node1, node0, 10);
  CXXGraph::DirectedWeightedEdge<int> edge16("3", node2, node0, 10);
  CXXGraph::DirectedWeightedEdge<int> edge17("3", node3, node0, 10);
  CXXGraph::DirectedWeightedEdge<int> edge18("3", node4, node0, 10);
  CXXGraph::DirectedWeightedEdge<int> edge19("3", node5, node0, 10);
  CXXGraph::DirectedWeightedEdge<int> edge20("3", node6, node0, 10);
  CXXGraph::DirectedWeightedEdge<int> edge21("3", node7, node0, 10);

  CXXGraph::T_EdgeSet<int> edgeSet;
  edgeSet.insert(make_shared<CXXGraph::DirectedWeightedEdge<int>>(edge1));
  edgeSet.insert(make_shared<CXXGraph::DirectedWeightedEdge<int>>(edge2));
  edgeSet.insert(make_shared<CXXGraph::DirectedWeightedEdge<int>>(edge3));
  edgeSet.insert(make_shared<CXXGraph::DirectedWeightedEdge<int>>(edge4));
  edgeSet.insert(make_shared<CXXGraph::DirectedWeightedEdge<int>>(edge5));
  edgeSet.insert(make_shared<CXXGraph::DirectedWeightedEdge<int>>(edge6));
  edgeSet.insert(make_shared<CXXGraph::DirectedWeightedEdge<int>>(edge9));
  edgeSet.insert(make_shared<CXXGraph::DirectedWeightedEdge<int>>(edge10));
  edgeSet.insert(make_shared<CXXGraph::DirectedWeightedEdge<int>>(edge11));
  edgeSet.insert(make_shared<CXXGraph::DirectedWeightedEdge<int>>(edge12));
  edgeSet.insert(make_shared<CXXGraph::DirectedWeightedEdge<int>>(edge13));
  edgeSet.insert(make_shared<CXXGraph::DirectedWeightedEdge<int>>(edge14));
  edgeSet.insert(make_shared<CXXGraph::DirectedWeightedEdge<int>>(edge15));
  edgeSet.insert(make_shared<CXXGraph::DirectedWeightedEdge<int>>(edge16));
  edgeSet.insert(make_shared<CXXGraph::DirectedWeightedEdge<int>>(edge17));
  edgeSet.insert(make_shared<CXXGraph::DirectedWeightedEdge<int>>(edge18));
  edgeSet.insert(make_shared<CXXGraph::DirectedWeightedEdge<int>>(edge19));
  edgeSet.insert(make_shared<CXXGraph::DirectedWeightedEdge<int>>(edge20));
  edgeSet.insert(make_shared<CXXGraph::DirectedWeightedEdge<int>>(edge21));

  CXXGraph::Graph<int> graph(edgeSet);

  ASSERT_FALSE(graph.isStronglyConnectedGraph());
}

TEST(ConnectivityTest, test_7) {
  CXXGraph::Node<int> node0("0", 0);
  CXXGraph::Node<int> node1("1", 1);
  CXXGraph::Node<int> node2("2", 2);
  CXXGraph::Node<int> node3("3", 3);
  CXXGraph::Node<int> node4("4", 4);
  CXXGraph::Node<int> node5("5", 5);
  CXXGraph::Node<int> node6("6", 6);
  CXXGraph::Node<int> node7("7", 7);
  CXXGraph::Node<int> node8("8", 8);

  CXXGraph::DirectedWeightedEdge<int> edge1("1", node0, node1, 4);
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
  edgeSet.insert(make_shared<CXXGraph::DirectedWeightedEdge<int>>(edge1));
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

  ASSERT_FALSE(graph.isConnectedGraph());
}

TEST(ConnectivityTest, test_8) {
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
  CXXGraph::DirectedWeightedEdge<int> edge2("2", node0, node7, 8);
  CXXGraph::DirectedWeightedEdge<int> edge3("3", node1, node7, 11);
  CXXGraph::DirectedWeightedEdge<int> edge4("3", node1, node2, 8);
  CXXGraph::DirectedWeightedEdge<int> edge5("4", node7, node8, 7);
  CXXGraph::DirectedWeightedEdge<int> edge6("3", node7, node6, 1);
  CXXGraph::DirectedWeightedEdge<int> edge7("3", node8, node2, 2);
  CXXGraph::DirectedWeightedEdge<int> edge8("3", node8, node6, 6);
  CXXGraph::DirectedWeightedEdge<int> edge9("3", node2, node5, 4);
  CXXGraph::DirectedWeightedEdge<int> edge10("3", node2, node3, 7);
  CXXGraph::DirectedWeightedEdge<int> edge11("3", node6, node5, 2);
  CXXGraph::DirectedWeightedEdge<int> edge12("3", node3, node4, 9);
  CXXGraph::DirectedWeightedEdge<int> edge13("3", node3, node5, 14);
  CXXGraph::DirectedWeightedEdge<int> edge14("3", node5, node4, 10);
  CXXGraph::DirectedWeightedEdge<int> edge15("3", node1, node0, 10);
  CXXGraph::DirectedWeightedEdge<int> edge16("3", node2, node0, 10);
  CXXGraph::DirectedWeightedEdge<int> edge17("3", node3, node0, 10);
  CXXGraph::DirectedWeightedEdge<int> edge18("3", node4, node0, 10);
  CXXGraph::DirectedWeightedEdge<int> edge19("3", node5, node0, 10);
  CXXGraph::DirectedWeightedEdge<int> edge20("3", node6, node0, 10);
  CXXGraph::DirectedWeightedEdge<int> edge21("3", node7, node0, 10);
  CXXGraph::DirectedWeightedEdge<int> edge22("3", node8, node0, 10);

  CXXGraph::T_EdgeSet<int> edgeSet;
  edgeSet.insert(make_shared<CXXGraph::UndirectedWeightedEdge<int>>(edge1));
  edgeSet.insert(make_shared<CXXGraph::DirectedWeightedEdge<int>>(edge2));
  edgeSet.insert(make_shared<CXXGraph::DirectedWeightedEdge<int>>(edge3));
  edgeSet.insert(make_shared<CXXGraph::DirectedWeightedEdge<int>>(edge4));
  edgeSet.insert(make_shared<CXXGraph::DirectedWeightedEdge<int>>(edge5));
  edgeSet.insert(make_shared<CXXGraph::DirectedWeightedEdge<int>>(edge6));
  edgeSet.insert(make_shared<CXXGraph::DirectedWeightedEdge<int>>(edge7));
  edgeSet.insert(make_shared<CXXGraph::DirectedWeightedEdge<int>>(edge8));
  edgeSet.insert(make_shared<CXXGraph::DirectedWeightedEdge<int>>(edge9));
  edgeSet.insert(make_shared<CXXGraph::DirectedWeightedEdge<int>>(edge10));
  edgeSet.insert(make_shared<CXXGraph::DirectedWeightedEdge<int>>(edge11));
  edgeSet.insert(make_shared<CXXGraph::DirectedWeightedEdge<int>>(edge12));
  edgeSet.insert(make_shared<CXXGraph::DirectedWeightedEdge<int>>(edge13));
  edgeSet.insert(make_shared<CXXGraph::DirectedWeightedEdge<int>>(edge14));
  edgeSet.insert(make_shared<CXXGraph::DirectedWeightedEdge<int>>(edge15));
  edgeSet.insert(make_shared<CXXGraph::DirectedWeightedEdge<int>>(edge16));
  edgeSet.insert(make_shared<CXXGraph::DirectedWeightedEdge<int>>(edge17));
  edgeSet.insert(make_shared<CXXGraph::DirectedWeightedEdge<int>>(edge18));
  edgeSet.insert(make_shared<CXXGraph::DirectedWeightedEdge<int>>(edge19));
  edgeSet.insert(make_shared<CXXGraph::DirectedWeightedEdge<int>>(edge20));
  edgeSet.insert(make_shared<CXXGraph::DirectedWeightedEdge<int>>(edge21));
  edgeSet.insert(make_shared<CXXGraph::DirectedWeightedEdge<int>>(edge22));

  CXXGraph::Graph<int> graph(edgeSet);

  ASSERT_FALSE(graph.isStronglyConnectedGraph());
}
