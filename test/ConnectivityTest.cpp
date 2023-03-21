#include "CXXGraph.hpp"
#include "gtest/gtest.h"

TEST(ConnectivityTest, test_1) {
  CXXGRAPH::Node<int> node0("0", 0);
  CXXGRAPH::Node<int> node1("1", 1);
  CXXGRAPH::Node<int> node2("2", 2);
  CXXGRAPH::Node<int> node3("3", 3);
  CXXGRAPH::Node<int> node4("4", 4);
  CXXGRAPH::Node<int> node5("5", 5);
  CXXGRAPH::Node<int> node6("6", 6);
  CXXGRAPH::Node<int> node7("7", 7);
  CXXGRAPH::Node<int> node8("8", 8);

  CXXGRAPH::UndirectedWeightedEdge<int> edge1(1, node0, node1, 4);
  CXXGRAPH::UndirectedWeightedEdge<int> edge2(2, node0, node7, 8);
  CXXGRAPH::UndirectedWeightedEdge<int> edge3(3, node1, node7, 11);
  CXXGRAPH::UndirectedWeightedEdge<int> edge4(3, node1, node2, 8);
  CXXGRAPH::UndirectedWeightedEdge<int> edge5(4, node7, node8, 7);
  CXXGRAPH::UndirectedWeightedEdge<int> edge6(3, node7, node6, 1);
  CXXGRAPH::UndirectedWeightedEdge<int> edge7(3, node8, node2, 2);
  CXXGRAPH::UndirectedWeightedEdge<int> edge8(3, node8, node6, 6);
  CXXGRAPH::UndirectedWeightedEdge<int> edge9(3, node2, node5, 4);
  CXXGRAPH::UndirectedWeightedEdge<int> edge10(3, node2, node3, 7);
  CXXGRAPH::UndirectedWeightedEdge<int> edge11(3, node6, node5, 2);
  CXXGRAPH::UndirectedWeightedEdge<int> edge12(3, node3, node4, 9);
  CXXGRAPH::UndirectedWeightedEdge<int> edge13(3, node3, node5, 14);
  CXXGRAPH::UndirectedWeightedEdge<int> edge14(3, node5, node4, 10);

  CXXGRAPH::T_EdgeSet<int> edgeSet;
  edgeSet.insert(&edge1);
  edgeSet.insert(&edge2);
  edgeSet.insert(&edge3);
  edgeSet.insert(&edge4);
  edgeSet.insert(&edge5);
  edgeSet.insert(&edge6);
  edgeSet.insert(&edge7);
  edgeSet.insert(&edge8);
  edgeSet.insert(&edge9);
  edgeSet.insert(&edge10);
  edgeSet.insert(&edge11);
  edgeSet.insert(&edge12);
  edgeSet.insert(&edge13);
  edgeSet.insert(&edge14);

  CXXGRAPH::Graph<int> graph(edgeSet);

  ASSERT_TRUE(graph.isConnectedGraph());
}

TEST(ConnectivityTest, test_2) {
  CXXGRAPH::Node<int> node0("0", 0);
  CXXGRAPH::Node<int> node1("1", 1);
  CXXGRAPH::Node<int> node2("2", 2);
  CXXGRAPH::Node<int> node3("3", 3);
  CXXGRAPH::Node<int> node4("4", 4);
  CXXGRAPH::Node<int> node5("5", 5);
  CXXGRAPH::Node<int> node6("6", 6);
  CXXGRAPH::Node<int> node7("7", 7);
  CXXGRAPH::Node<int> node8("8", 8);

  CXXGRAPH::UndirectedWeightedEdge<int> edge1(1, node0, node1, 4);
  CXXGRAPH::UndirectedWeightedEdge<int> edge2(2, node0, node7, 8);
  CXXGRAPH::UndirectedWeightedEdge<int> edge3(3, node1, node7, 11);
  CXXGRAPH::UndirectedWeightedEdge<int> edge4(3, node1, node2, 8);
  CXXGRAPH::UndirectedWeightedEdge<int> edge5(4, node7, node8, 7);
  CXXGRAPH::UndirectedWeightedEdge<int> edge6(3, node7, node6, 1);
  CXXGRAPH::UndirectedWeightedEdge<int> edge7(3, node8, node2, 2);
  CXXGRAPH::UndirectedWeightedEdge<int> edge8(3, node8, node6, 6);
  CXXGRAPH::UndirectedWeightedEdge<int> edge9(3, node2, node5, 4);
  CXXGRAPH::UndirectedWeightedEdge<int> edge10(3, node2, node3, 7);
  CXXGRAPH::UndirectedWeightedEdge<int> edge11(3, node6, node5, 2);
  CXXGRAPH::UndirectedWeightedEdge<int> edge12(3, node3, node4, 9);
  CXXGRAPH::UndirectedWeightedEdge<int> edge13(3, node3, node5, 14);
  CXXGRAPH::UndirectedWeightedEdge<int> edge14(3, node5, node4, 10);

  CXXGRAPH::T_EdgeSet<int> edgeSet;
  edgeSet.insert(&edge1);
  edgeSet.insert(&edge2);
  edgeSet.insert(&edge3);
  edgeSet.insert(&edge4);
  edgeSet.insert(&edge5);
  edgeSet.insert(&edge6);
  edgeSet.insert(&edge7);
  edgeSet.insert(&edge8);
  edgeSet.insert(&edge9);
  edgeSet.insert(&edge10);
  edgeSet.insert(&edge11);
  edgeSet.insert(&edge12);
  edgeSet.insert(&edge13);
  edgeSet.insert(&edge14);

  CXXGRAPH::Graph<int> graph(edgeSet);

  ASSERT_FALSE(graph.isStronglyConnectedGraph());
}

TEST(ConnectivityTest, test_3) {
  CXXGRAPH::Node<int> node0("0", 0);
  CXXGRAPH::Node<int> node1("1", 1);
  CXXGRAPH::Node<int> node2("2", 2);
  CXXGRAPH::Node<int> node3("3", 3);
  CXXGRAPH::Node<int> node4("4", 4);
  CXXGRAPH::Node<int> node5("5", 5);
  CXXGRAPH::Node<int> node6("6", 6);
  CXXGRAPH::Node<int> node7("7", 7);
  CXXGRAPH::Node<int> node8("8", 8);

  CXXGRAPH::DirectedWeightedEdge<int> edge1(1, node0, node1, 4);
  CXXGRAPH::DirectedWeightedEdge<int> edge2(2, node0, node7, 8);
  CXXGRAPH::DirectedWeightedEdge<int> edge3(3, node1, node7, 11);
  CXXGRAPH::DirectedWeightedEdge<int> edge4(3, node1, node2, 8);
  CXXGRAPH::DirectedWeightedEdge<int> edge5(4, node7, node8, 7);
  CXXGRAPH::DirectedWeightedEdge<int> edge6(3, node7, node6, 1);
  CXXGRAPH::DirectedWeightedEdge<int> edge7(3, node8, node2, 2);
  CXXGRAPH::DirectedWeightedEdge<int> edge8(3, node8, node6, 6);
  CXXGRAPH::DirectedWeightedEdge<int> edge9(3, node2, node5, 4);
  CXXGRAPH::DirectedWeightedEdge<int> edge10(3, node2, node3, 7);
  CXXGRAPH::DirectedWeightedEdge<int> edge11(3, node6, node5, 2);
  CXXGRAPH::DirectedWeightedEdge<int> edge12(3, node3, node4, 9);
  CXXGRAPH::DirectedWeightedEdge<int> edge13(3, node3, node5, 14);
  CXXGRAPH::DirectedWeightedEdge<int> edge14(3, node5, node4, 10);
  CXXGRAPH::DirectedWeightedEdge<int> edge15(3, node1, node0, 10);
  CXXGRAPH::DirectedWeightedEdge<int> edge16(3, node2, node0, 10);
  CXXGRAPH::DirectedWeightedEdge<int> edge17(3, node3, node0, 10);
  CXXGRAPH::DirectedWeightedEdge<int> edge18(3, node4, node0, 10);
  CXXGRAPH::DirectedWeightedEdge<int> edge19(3, node5, node0, 10);
  CXXGRAPH::DirectedWeightedEdge<int> edge20(3, node6, node0, 10);
  CXXGRAPH::DirectedWeightedEdge<int> edge21(3, node7, node0, 10);
  CXXGRAPH::DirectedWeightedEdge<int> edge22(3, node8, node0, 10);

  CXXGRAPH::T_EdgeSet<int> edgeSet;
  edgeSet.insert(&edge1);
  edgeSet.insert(&edge2);
  edgeSet.insert(&edge3);
  edgeSet.insert(&edge4);
  edgeSet.insert(&edge5);
  edgeSet.insert(&edge6);
  edgeSet.insert(&edge7);
  edgeSet.insert(&edge8);
  edgeSet.insert(&edge9);
  edgeSet.insert(&edge10);
  edgeSet.insert(&edge11);
  edgeSet.insert(&edge12);
  edgeSet.insert(&edge13);
  edgeSet.insert(&edge14);
  edgeSet.insert(&edge15);
  edgeSet.insert(&edge16);
  edgeSet.insert(&edge17);
  edgeSet.insert(&edge18);
  edgeSet.insert(&edge19);
  edgeSet.insert(&edge20);
  edgeSet.insert(&edge21);
  edgeSet.insert(&edge22);

  CXXGRAPH::Graph<int> graph(edgeSet);

  ASSERT_TRUE(graph.isStronglyConnectedGraph());
}

TEST(ConnectivityTest, test_4) {
  CXXGRAPH::Node<int> node0("0", 0);
  CXXGRAPH::Node<int> node1("1", 1);
  CXXGRAPH::Node<int> node2("2", 2);
  CXXGRAPH::Node<int> node3("3", 3);
  CXXGRAPH::Node<int> node4("4", 4);
  CXXGRAPH::Node<int> node5("5", 5);
  CXXGRAPH::Node<int> node6("6", 6);
  CXXGRAPH::Node<int> node7("7", 7);
  CXXGRAPH::Node<int> node8("8", 8);

  CXXGRAPH::DirectedWeightedEdge<int> edge1(1, node0, node1, 4);
  CXXGRAPH::DirectedWeightedEdge<int> edge2(2, node0, node7, 8);
  CXXGRAPH::DirectedWeightedEdge<int> edge3(3, node1, node7, 11);
  CXXGRAPH::DirectedWeightedEdge<int> edge4(3, node1, node2, 8);
  CXXGRAPH::DirectedWeightedEdge<int> edge5(4, node7, node8, 7);
  CXXGRAPH::DirectedWeightedEdge<int> edge6(3, node7, node6, 1);
  CXXGRAPH::DirectedWeightedEdge<int> edge7(3, node8, node2, 2);
  CXXGRAPH::DirectedWeightedEdge<int> edge8(3, node8, node6, 6);
  CXXGRAPH::DirectedWeightedEdge<int> edge9(3, node2, node5, 4);
  CXXGRAPH::DirectedWeightedEdge<int> edge10(3, node2, node3, 7);
  CXXGRAPH::DirectedWeightedEdge<int> edge11(3, node6, node5, 2);
  CXXGRAPH::DirectedWeightedEdge<int> edge12(3, node3, node4, 9);
  CXXGRAPH::DirectedWeightedEdge<int> edge13(3, node3, node5, 14);
  CXXGRAPH::DirectedWeightedEdge<int> edge14(3, node5, node4, 10);

  CXXGRAPH::T_EdgeSet<int> edgeSet;
  edgeSet.insert(&edge1);
  edgeSet.insert(&edge2);
  edgeSet.insert(&edge3);
  edgeSet.insert(&edge4);
  edgeSet.insert(&edge5);
  edgeSet.insert(&edge6);
  edgeSet.insert(&edge7);
  edgeSet.insert(&edge8);
  edgeSet.insert(&edge9);
  edgeSet.insert(&edge10);
  edgeSet.insert(&edge11);
  edgeSet.insert(&edge12);
  edgeSet.insert(&edge13);
  edgeSet.insert(&edge14);

  CXXGRAPH::Graph<int> graph(edgeSet);

  ASSERT_FALSE(graph.isConnectedGraph());
}
/////////////////////////////////////////////////////////
// Not a possible test until not implemented addNode function. All the
// undirected graph can be only connected with this interface.
/*
TEST(ConnectivityTest, test_5)
{
    CXXGRAPH::Node<int> node0("0", 0);
    CXXGRAPH::Node<int> node1("1", 1);
    CXXGRAPH::Node<int> node2("2", 2);
    CXXGRAPH::Node<int> node3("3", 3);
    CXXGRAPH::Node<int> node4("4", 4);
    CXXGRAPH::Node<int> node5("5", 5);
    CXXGRAPH::Node<int> node6("6", 6);
    CXXGRAPH::Node<int> node7("7", 7);
    CXXGRAPH::Node<int> node8("8", 8);

    CXXGRAPH::UndirectedWeightedEdge<int> edge1(1, node0, node1, 4);
    CXXGRAPH::UndirectedWeightedEdge<int> edge2(2, node0, node7, 8);
    CXXGRAPH::UndirectedWeightedEdge<int> edge3(3, node1, node7, 11);
    CXXGRAPH::UndirectedWeightedEdge<int> edge4(3, node1, node2, 8);
    CXXGRAPH::UndirectedWeightedEdge<int> edge5(4, node7, node8, 7);
    CXXGRAPH::UndirectedWeightedEdge<int> edge6(3, node7, node6, 1);
    CXXGRAPH::UndirectedWeightedEdge<int> edge7(3, node8, node2, 2);
    CXXGRAPH::UndirectedWeightedEdge<int> edge8(3, node8, node6, 6);
    CXXGRAPH::UndirectedWeightedEdge<int> edge9(3, node2, node5, 4);
    CXXGRAPH::UndirectedWeightedEdge<int> edge10(3, node2, node3, 7);
    CXXGRAPH::UndirectedWeightedEdge<int> edge11(3, node6, node5, 2);
    CXXGRAPH::UndirectedWeightedEdge<int> edge12(3, node3, node4, 9);
    CXXGRAPH::UndirectedWeightedEdge<int> edge13(3, node3, node5, 14);
    CXXGRAPH::UndirectedWeightedEdge<int> edge14(3, node5, node4, 10);

    CXXGRAPH::T_EdgeSet<int> edgeSet;
    edgeSet.insert(&edge1);
    edgeSet.insert(&edge2);
    edgeSet.insert(&edge3);
    edgeSet.insert(&edge4);
    edgeSet.insert(&edge5);
    edgeSet.insert(&edge6);
    edgeSet.insert(&edge7);
    edgeSet.insert(&edge8);
    edgeSet.insert(&edge9);
    edgeSet.insert(&edge10);
    edgeSet.insert(&edge11);
    edgeSet.insert(&edge12);
    edgeSet.insert(&edge13);
    edgeSet.insert(&edge14);

    CXXGRAPH::Graph<int> graph(edgeSet);

    ASSERT_FALSE(graph.isConnectedGraph());

}
*/
////////////////////////////////////////////////////////////////////

TEST(ConnectivityTest, test_6) {
  CXXGRAPH::Node<int> node0("0", 0);
  CXXGRAPH::Node<int> node1("1", 1);
  CXXGRAPH::Node<int> node2("2", 2);
  CXXGRAPH::Node<int> node3("3", 3);
  CXXGRAPH::Node<int> node4("4", 4);
  CXXGRAPH::Node<int> node5("5", 5);
  CXXGRAPH::Node<int> node6("6", 6);
  CXXGRAPH::Node<int> node7("7", 7);
  CXXGRAPH::Node<int> node8("8", 8);

  CXXGRAPH::DirectedWeightedEdge<int> edge1(1, node0, node1, 4);
  CXXGRAPH::DirectedWeightedEdge<int> edge2(2, node0, node7, 8);
  CXXGRAPH::DirectedWeightedEdge<int> edge3(3, node1, node7, 11);
  CXXGRAPH::DirectedWeightedEdge<int> edge4(3, node1, node2, 8);
  CXXGRAPH::DirectedWeightedEdge<int> edge5(4, node7, node8, 7);
  CXXGRAPH::DirectedWeightedEdge<int> edge6(3, node7, node6, 1);
  CXXGRAPH::DirectedWeightedEdge<int> edge9(3, node2, node5, 4);
  CXXGRAPH::DirectedWeightedEdge<int> edge10(3, node2, node3, 7);
  CXXGRAPH::DirectedWeightedEdge<int> edge11(3, node6, node5, 2);
  CXXGRAPH::DirectedWeightedEdge<int> edge12(3, node3, node4, 9);
  CXXGRAPH::DirectedWeightedEdge<int> edge13(3, node3, node5, 14);
  CXXGRAPH::DirectedWeightedEdge<int> edge14(3, node5, node4, 10);
  CXXGRAPH::DirectedWeightedEdge<int> edge15(3, node1, node0, 10);
  CXXGRAPH::DirectedWeightedEdge<int> edge16(3, node2, node0, 10);
  CXXGRAPH::DirectedWeightedEdge<int> edge17(3, node3, node0, 10);
  CXXGRAPH::DirectedWeightedEdge<int> edge18(3, node4, node0, 10);
  CXXGRAPH::DirectedWeightedEdge<int> edge19(3, node5, node0, 10);
  CXXGRAPH::DirectedWeightedEdge<int> edge20(3, node6, node0, 10);
  CXXGRAPH::DirectedWeightedEdge<int> edge21(3, node7, node0, 10);

  CXXGRAPH::T_EdgeSet<int> edgeSet;
  edgeSet.insert(&edge1);
  edgeSet.insert(&edge2);
  edgeSet.insert(&edge3);
  edgeSet.insert(&edge4);
  edgeSet.insert(&edge5);
  edgeSet.insert(&edge6);
  edgeSet.insert(&edge9);
  edgeSet.insert(&edge10);
  edgeSet.insert(&edge11);
  edgeSet.insert(&edge12);
  edgeSet.insert(&edge13);
  edgeSet.insert(&edge14);
  edgeSet.insert(&edge15);
  edgeSet.insert(&edge16);
  edgeSet.insert(&edge17);
  edgeSet.insert(&edge18);
  edgeSet.insert(&edge19);
  edgeSet.insert(&edge20);
  edgeSet.insert(&edge21);

  CXXGRAPH::Graph<int> graph(edgeSet);

  ASSERT_FALSE(graph.isStronglyConnectedGraph());
}

TEST(ConnectivityTest, test_7) {
  CXXGRAPH::Node<int> node0("0", 0);
  CXXGRAPH::Node<int> node1("1", 1);
  CXXGRAPH::Node<int> node2("2", 2);
  CXXGRAPH::Node<int> node3("3", 3);
  CXXGRAPH::Node<int> node4("4", 4);
  CXXGRAPH::Node<int> node5("5", 5);
  CXXGRAPH::Node<int> node6("6", 6);
  CXXGRAPH::Node<int> node7("7", 7);
  CXXGRAPH::Node<int> node8("8", 8);

  CXXGRAPH::DirectedWeightedEdge<int> edge1(1, node0, node1, 4);
  CXXGRAPH::UndirectedWeightedEdge<int> edge2(2, node0, node7, 8);
  CXXGRAPH::UndirectedWeightedEdge<int> edge3(3, node1, node7, 11);
  CXXGRAPH::UndirectedWeightedEdge<int> edge4(3, node1, node2, 8);
  CXXGRAPH::UndirectedWeightedEdge<int> edge5(4, node7, node8, 7);
  CXXGRAPH::UndirectedWeightedEdge<int> edge6(3, node7, node6, 1);
  CXXGRAPH::UndirectedWeightedEdge<int> edge7(3, node8, node2, 2);
  CXXGRAPH::UndirectedWeightedEdge<int> edge8(3, node8, node6, 6);
  CXXGRAPH::UndirectedWeightedEdge<int> edge9(3, node2, node5, 4);
  CXXGRAPH::UndirectedWeightedEdge<int> edge10(3, node2, node3, 7);
  CXXGRAPH::UndirectedWeightedEdge<int> edge11(3, node6, node5, 2);
  CXXGRAPH::UndirectedWeightedEdge<int> edge12(3, node3, node4, 9);
  CXXGRAPH::UndirectedWeightedEdge<int> edge13(3, node3, node5, 14);
  CXXGRAPH::UndirectedWeightedEdge<int> edge14(3, node5, node4, 10);

  CXXGRAPH::T_EdgeSet<int> edgeSet;
  edgeSet.insert(&edge1);
  edgeSet.insert(&edge2);
  edgeSet.insert(&edge3);
  edgeSet.insert(&edge4);
  edgeSet.insert(&edge5);
  edgeSet.insert(&edge6);
  edgeSet.insert(&edge7);
  edgeSet.insert(&edge8);
  edgeSet.insert(&edge9);
  edgeSet.insert(&edge10);
  edgeSet.insert(&edge11);
  edgeSet.insert(&edge12);
  edgeSet.insert(&edge13);
  edgeSet.insert(&edge14);

  CXXGRAPH::Graph<int> graph(edgeSet);

  ASSERT_FALSE(graph.isConnectedGraph());
}

TEST(ConnectivityTest, test_8) {
  CXXGRAPH::Node<int> node0("0", 0);
  CXXGRAPH::Node<int> node1("1", 1);
  CXXGRAPH::Node<int> node2("2", 2);
  CXXGRAPH::Node<int> node3("3", 3);
  CXXGRAPH::Node<int> node4("4", 4);
  CXXGRAPH::Node<int> node5("5", 5);
  CXXGRAPH::Node<int> node6("6", 6);
  CXXGRAPH::Node<int> node7("7", 7);
  CXXGRAPH::Node<int> node8("8", 8);

  CXXGRAPH::UndirectedWeightedEdge<int> edge1(1, node0, node1, 4);
  CXXGRAPH::DirectedWeightedEdge<int> edge2(2, node0, node7, 8);
  CXXGRAPH::DirectedWeightedEdge<int> edge3(3, node1, node7, 11);
  CXXGRAPH::DirectedWeightedEdge<int> edge4(3, node1, node2, 8);
  CXXGRAPH::DirectedWeightedEdge<int> edge5(4, node7, node8, 7);
  CXXGRAPH::DirectedWeightedEdge<int> edge6(3, node7, node6, 1);
  CXXGRAPH::DirectedWeightedEdge<int> edge7(3, node8, node2, 2);
  CXXGRAPH::DirectedWeightedEdge<int> edge8(3, node8, node6, 6);
  CXXGRAPH::DirectedWeightedEdge<int> edge9(3, node2, node5, 4);
  CXXGRAPH::DirectedWeightedEdge<int> edge10(3, node2, node3, 7);
  CXXGRAPH::DirectedWeightedEdge<int> edge11(3, node6, node5, 2);
  CXXGRAPH::DirectedWeightedEdge<int> edge12(3, node3, node4, 9);
  CXXGRAPH::DirectedWeightedEdge<int> edge13(3, node3, node5, 14);
  CXXGRAPH::DirectedWeightedEdge<int> edge14(3, node5, node4, 10);
  CXXGRAPH::DirectedWeightedEdge<int> edge15(3, node1, node0, 10);
  CXXGRAPH::DirectedWeightedEdge<int> edge16(3, node2, node0, 10);
  CXXGRAPH::DirectedWeightedEdge<int> edge17(3, node3, node0, 10);
  CXXGRAPH::DirectedWeightedEdge<int> edge18(3, node4, node0, 10);
  CXXGRAPH::DirectedWeightedEdge<int> edge19(3, node5, node0, 10);
  CXXGRAPH::DirectedWeightedEdge<int> edge20(3, node6, node0, 10);
  CXXGRAPH::DirectedWeightedEdge<int> edge21(3, node7, node0, 10);
  CXXGRAPH::DirectedWeightedEdge<int> edge22(3, node8, node0, 10);

  CXXGRAPH::T_EdgeSet<int> edgeSet;
  edgeSet.insert(&edge1);
  edgeSet.insert(&edge2);
  edgeSet.insert(&edge3);
  edgeSet.insert(&edge4);
  edgeSet.insert(&edge5);
  edgeSet.insert(&edge6);
  edgeSet.insert(&edge7);
  edgeSet.insert(&edge8);
  edgeSet.insert(&edge9);
  edgeSet.insert(&edge10);
  edgeSet.insert(&edge11);
  edgeSet.insert(&edge12);
  edgeSet.insert(&edge13);
  edgeSet.insert(&edge14);
  edgeSet.insert(&edge15);
  edgeSet.insert(&edge16);
  edgeSet.insert(&edge17);
  edgeSet.insert(&edge18);
  edgeSet.insert(&edge19);
  edgeSet.insert(&edge20);
  edgeSet.insert(&edge21);
  edgeSet.insert(&edge22);

  CXXGRAPH::Graph<int> graph(edgeSet);

  ASSERT_FALSE(graph.isStronglyConnectedGraph());
}