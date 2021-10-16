#include "gtest/gtest.h"
#include "CXXGraph.hpp"

TEST(UnionFindTest, test_1)
{
    CXXGRAPH::Node<int> node0(0, 0);
    CXXGRAPH::Node<int> node1(1, 1);
    CXXGRAPH::Node<int> node2(2, 2);
    CXXGRAPH::Node<int> node3(3, 3);

    /*
            0
           1 2
          3
    */
    CXXGRAPH::UndirectedWeightedEdge<int> edge1(0, node0, node1, 5);
    CXXGRAPH::UndirectedWeightedEdge<int> edge2(1, node0, node2, 10);
    CXXGRAPH::UndirectedWeightedEdge<int> edge3(2, node1, node3, 5);

    std::list<const CXXGRAPH::Edge<int> *> edgeSet;
    edgeSet.push_back(&edge1);

    CXXGRAPH::Graph<int> graph(edgeSet);

    // every element is a subset of itself
    CXXGRAPH::Subset subset[4] = {{0, 0}, {1, 0}, {2, 0}, {3, 0}};
    auto res = graph.setFind(subset, node0.getId());
    ASSERT_EQ(res, 0);
    res = graph.setFind(subset, node1.getId());
    ASSERT_EQ(res, 1);
    res = graph.setFind(subset, node2.getId());
    ASSERT_EQ(res, 2);

    // element 1 & 2 are subset of 0
    // element 3 is subset of 1
    CXXGRAPH::Subset subset1[4] = {{0, 0}, {0, 0}, {0, 0}, {1, 0}};
    auto res1 = graph.setFind(subset1, node0.getId());
    ASSERT_EQ(res1, 0);
    res = graph.setFind(subset1, node3.getId());
    ASSERT_EQ(res1, 0);
    res = graph.setFind(subset1, node2.getId());
    ASSERT_EQ(res1, 0);

    // union of (node 1 & node3)  should increase node0 rank by 1
    CXXGRAPH::Subset subset2[4] = {{0, 0}, {0, 0}, {0, 0}, {1, 0}};
    graph.setUnion(subset2, node1.getId(), node3.getId());
    ASSERT_EQ(subset2[0].rank, 1);
    ASSERT_EQ(subset2[3].parent, 0);

    // rank shouldn't increase since both have the same parent
    graph.setUnion(subset2, node2.getId(), node3.getId());
    ASSERT_EQ(subset2[0].rank, 1);
    ASSERT_EQ(subset2[3].parent, 0);
}