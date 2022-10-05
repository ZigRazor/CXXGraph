#include "gtest/gtest.h"
#include "CXXGraph.hpp"

// minimum spanning tree can differ so instead of checking 
// the exact order of elements, we can check some properties 
// like the length & cost of mst which must remain the same

// example taken from
// https://www.geeksforgeeks.org/prims-mst-for-adjacency-list-representation-greedy-algo-6/TEST(FWTest, test_1)
TEST(PrimTest, test_1)
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
    CXXGRAPH::MstResult res = graph.prim();

    ASSERT_TRUE(res.success);
    ASSERT_EQ(res.mst.size(), graph.getNodeSet().size()-1);
    ASSERT_EQ(res.mstCost, 37);
    ASSERT_EQ(res.errorMessage, "");

}


// example taken from
// https://www.gatevidyalay.com/prims-algorithm-prim-algorithm-example/
TEST(PrimTest, test_2)
{
    CXXGRAPH::Node<int> node1("1", 1);
    CXXGRAPH::Node<int> node2("2", 2);
    CXXGRAPH::Node<int> node3("3", 3);
    CXXGRAPH::Node<int> node4("4", 4);
    CXXGRAPH::Node<int> node5("5", 5);
    CXXGRAPH::Node<int> node6("6", 6);
    CXXGRAPH::Node<int> node7("7", 7);

    CXXGRAPH::UndirectedWeightedEdge<int> edge1(1, node1, node2, 28);
    CXXGRAPH::UndirectedWeightedEdge<int> edge2(2, node1, node6, 10);
    CXXGRAPH::UndirectedWeightedEdge<int> edge3(3, node2, node7, 14);
    CXXGRAPH::UndirectedWeightedEdge<int> edge4(4, node2, node3, 16);
    CXXGRAPH::UndirectedWeightedEdge<int> edge5(5, node6, node5, 25);
    CXXGRAPH::UndirectedWeightedEdge<int> edge6(6, node7, node5, 24);
    CXXGRAPH::UndirectedWeightedEdge<int> edge7(7, node7, node4, 18);
    CXXGRAPH::UndirectedWeightedEdge<int> edge8(8, node5, node4, 22);
    CXXGRAPH::UndirectedWeightedEdge<int> edge9(9, node4, node3, 12);

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

    CXXGRAPH::Graph<int> graph(edgeSet);
    CXXGRAPH::MstResult res = graph.prim();
    ASSERT_TRUE(res.success);
    ASSERT_EQ(res.mst.size(), graph.getNodeSet().size()-1);
    ASSERT_EQ(res.mstCost, 99);
    ASSERT_EQ(res.errorMessage, "");

}


// example taken from
// https://www.gatevidyalay.com/prims-algorithm-prim-algorithm-example/
TEST(PrimTest, test_3)
{
    CXXGRAPH::Node<int> node1("1", 1);
    CXXGRAPH::Node<int> node2("2", 2);
    CXXGRAPH::Node<int> node3("3", 3);
    CXXGRAPH::Node<int> node4("4", 4);
    CXXGRAPH::Node<int> node5("5", 5);
    CXXGRAPH::Node<int> node6("6", 6);
    CXXGRAPH::Node<int> node7("7", 7);

    CXXGRAPH::UndirectedWeightedEdge<int> edge1(1, node1, node2, 1);
    CXXGRAPH::UndirectedWeightedEdge<int> edge2(2, node1, node3, 5);
    CXXGRAPH::UndirectedWeightedEdge<int> edge3(3, node2, node5, 7);
    CXXGRAPH::UndirectedWeightedEdge<int> edge4(4, node2, node4, 8);
    CXXGRAPH::UndirectedWeightedEdge<int> edge5(5, node2, node3, 4);
    CXXGRAPH::UndirectedWeightedEdge<int> edge6(6, node3, node4, 6);
    CXXGRAPH::UndirectedWeightedEdge<int> edge7(7, node3, node6, 2);
    CXXGRAPH::UndirectedWeightedEdge<int> edge8(8, node4, node6, 9);
    CXXGRAPH::UndirectedWeightedEdge<int> edge9(9, node4, node5, 11);
    CXXGRAPH::UndirectedWeightedEdge<int> edge10(9, node5, node7, 10);
    CXXGRAPH::UndirectedWeightedEdge<int> edge11(9, node5, node6, 3);
    CXXGRAPH::UndirectedWeightedEdge<int> edge12(9, node6, node7, 12);

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

    CXXGRAPH::Graph<int> graph(edgeSet);
    CXXGRAPH::MstResult res = graph.prim();
    ASSERT_TRUE(res.success);
    ASSERT_EQ(res.mst.size(), graph.getNodeSet().size()-1);
    ASSERT_EQ(res.mstCost, 26);
    ASSERT_EQ(res.errorMessage, "");

}

// test for directed and no weighted edge errors
TEST(PrimTest, test_4)
{
    CXXGRAPH::Node<int> node1("1", 1);
    CXXGRAPH::Node<int> node2("2", 2);
    CXXGRAPH::Node<int> node3("3", 3);
    CXXGRAPH::DirectedWeightedEdge<int> edge1(1, node1, node2, 1);
    CXXGRAPH::DirectedWeightedEdge<int> edge2(2, node2, node3, 1);
    CXXGRAPH::T_EdgeSet<int> edgeSet;
    edgeSet.insert(&edge1);
    edgeSet.insert(&edge2);
 
    CXXGRAPH::Graph<int> graph(edgeSet);
    CXXGRAPH::MstResult res = graph.prim();
    ASSERT_FALSE(res.success);
    ASSERT_EQ(res.errorMessage, CXXGRAPH::ERR_DIR_GRAPH);

    CXXGRAPH::UndirectedEdge<int> edge3(3, node1, node2);
    CXXGRAPH::T_EdgeSet<int> edgeSet1;
    edgeSet1.insert(&edge3);
 
    CXXGRAPH::Graph<int> graph1(edgeSet1);
    res = graph1.prim();
    ASSERT_FALSE(res.success);
    ASSERT_EQ(res.errorMessage, CXXGRAPH::ERR_NO_WEIGHTED_EDGE);

}