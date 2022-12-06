#include "gtest/gtest.h"
#include "CXXGraph.hpp"
#include <vector>

TEST(BFSTest, test_1)
{
    CXXGRAPH::Node<int> node1("1", 1);
    CXXGRAPH::Node<int> node2("2", 2);
    CXXGRAPH::Node<int> node3("3", 3);
    std::pair<const CXXGRAPH::Node<int> *, const CXXGRAPH::Node<int> *> pairNode(&node1, &node2);
    CXXGRAPH::DirectedWeightedEdge<int> edge1(1, pairNode, 1);
    CXXGRAPH::DirectedWeightedEdge<int> edge2(2, node2, node3, 1);
    CXXGRAPH::UndirectedWeightedEdge<int> edge3(3, node1, node3, 6);
    CXXGRAPH::T_EdgeSet<int> edgeSet;
    edgeSet.insert(&edge1);
    edgeSet.insert(&edge2);
    edgeSet.insert(&edge3);
    CXXGRAPH::Graph<int> graph(edgeSet);
    std::vector<CXXGRAPH::Node<int>> res = graph.breadth_first_search(node1);
    ASSERT_EQ(res.size(), 3);
    ASSERT_TRUE(std::find(res.begin(), res.end(), node1) != res.end());
    ASSERT_TRUE(std::find(res.begin(), res.end(), node2) != res.end());
    ASSERT_TRUE(std::find(res.begin(), res.end(), node3) != res.end());

}

TEST(BFSTest, test_2)
{
    CXXGRAPH::Node<int> node1("1", 1);
    CXXGRAPH::Node<int> node2("2", 2);
    CXXGRAPH::Node<int> node3("3", 3);
    std::pair<const CXXGRAPH::Node<int> *, const CXXGRAPH::Node<int> *> pairNode(&node1, &node2);
    CXXGRAPH::DirectedWeightedEdge<int> edge1(1, pairNode, 1);
    CXXGRAPH::DirectedWeightedEdge<int> edge2(2, node2, node3, 1);
    CXXGRAPH::DirectedWeightedEdge<int> edge3(3, node1, node3, 6);
    CXXGRAPH::T_EdgeSet<int> edgeSet;
    edgeSet.insert(&edge1);
    edgeSet.insert(&edge2);
    edgeSet.insert(&edge3);
    CXXGRAPH::Graph<int> graph(edgeSet);
    std::vector<CXXGRAPH::Node<int>> res = graph.breadth_first_search(node2);
    ASSERT_EQ(res.size(), 2);
    ASSERT_FALSE(std::find(res.begin(), res.end(), node1) != res.end());
    ASSERT_TRUE(std::find(res.begin(), res.end(), node2) != res.end());
    ASSERT_TRUE(std::find(res.begin(), res.end(), node3) != res.end());

}

TEST(BFSTest, test_3)
{
    CXXGRAPH::Node<int> node1("1", 1);
    CXXGRAPH::Node<int> node2("2", 2);
    CXXGRAPH::Node<int> node3("3", 3);
    std::pair<const CXXGRAPH::Node<int> *, const CXXGRAPH::Node<int> *> pairNode(&node1, &node2);
    CXXGRAPH::DirectedWeightedEdge<int> edge1(1, pairNode, 1);
    CXXGRAPH::DirectedWeightedEdge<int> edge2(2, node2, node3, 1);
    CXXGRAPH::UndirectedWeightedEdge<int> edge3(3, node1, node3, 6);
    CXXGRAPH::T_EdgeSet<int> edgeSet;
    edgeSet.insert(&edge1);
    edgeSet.insert(&edge2);
    edgeSet.insert(&edge3);
    CXXGRAPH::Graph<int> graph(edgeSet);
    std::vector<CXXGRAPH::Node<int>> res = graph.breadth_first_search(node2);
    ASSERT_EQ(res.size(), 3);
    ASSERT_TRUE(std::find(res.begin(), res.end(), node1) != res.end());
    ASSERT_TRUE(std::find(res.begin(), res.end(), node2) != res.end());
    ASSERT_TRUE(std::find(res.begin(), res.end(), node3) != res.end());
}

TEST(BFSTest, test_4)
{
    CXXGRAPH::Node<int> node1("1", 1);
    CXXGRAPH::Node<int> node2("2", 2);
    CXXGRAPH::Node<int> node3("3", 3);
    std::pair<const CXXGRAPH::Node<int> *, const CXXGRAPH::Node<int> *> pairNode(&node1, &node2);
    CXXGRAPH::DirectedWeightedEdge<int> edge1(1, pairNode, 1);
    CXXGRAPH::DirectedWeightedEdge<int> edge2(2, node2, node3, 1);
    CXXGRAPH::UndirectedWeightedEdge<int> edge3(3, node1, node3, 6);
    CXXGRAPH::T_EdgeSet<int> edgeSet;
    edgeSet.insert(&edge1);
    edgeSet.insert(&edge2);
    edgeSet.insert(&edge3);
    CXXGRAPH::Graph<int> graph(edgeSet);
    std::vector<CXXGRAPH::Node<int>> res = graph.breadth_first_search(node3);
    ASSERT_EQ(res.size(), 3);
    ASSERT_TRUE(std::find(res.begin(), res.end(), node1) != res.end());
    ASSERT_TRUE(std::find(res.begin(), res.end(), node2) != res.end());
    ASSERT_TRUE(std::find(res.begin(), res.end(), node3) != res.end());

}

TEST(BFSTest, test_5)
{
    CXXGRAPH::Node<int> node1("1", 1);
    CXXGRAPH::Node<int> node2("2", 2);
    CXXGRAPH::Node<int> node3("3", 3);
    std::pair<const CXXGRAPH::Node<int> *, const CXXGRAPH::Node<int> *> pairNode(&node1, &node2);
    CXXGRAPH::DirectedWeightedEdge<int> edge1(1, pairNode, 1);
    CXXGRAPH::DirectedWeightedEdge<int> edge2(2, node2, node3, 1);
    CXXGRAPH::DirectedWeightedEdge<int> edge3(3, node1, node3, 6);
    CXXGRAPH::T_EdgeSet<int> edgeSet;
    edgeSet.insert(&edge1);
    edgeSet.insert(&edge2);
    edgeSet.insert(&edge3);
    CXXGRAPH::Graph<int> graph(edgeSet);
    std::vector<CXXGRAPH::Node<int>> res = graph.breadth_first_search(node3);
    ASSERT_EQ(res.size(), 1);
    ASSERT_FALSE(std::find(res.begin(), res.end(), node1) != res.end());
    ASSERT_FALSE(std::find(res.begin(), res.end(), node2) != res.end());
    ASSERT_TRUE(std::find(res.begin(), res.end(), node3) != res.end());

}

TEST(BFSTest, test_6)
{
    CXXGRAPH::Node<int> node1("1", 1);
    CXXGRAPH::Node<int> node2("2", 2);
    CXXGRAPH::Node<int> node3("3", 3);
    CXXGRAPH::Node<int> node4("4", 4);
    std::pair<const CXXGRAPH::Node<int> *, const CXXGRAPH::Node<int> *> pairNode(&node1, &node2);
    CXXGRAPH::DirectedWeightedEdge<int> edge1(1, pairNode, 1);
    CXXGRAPH::DirectedWeightedEdge<int> edge2(2, node2, node3, 1);
    CXXGRAPH::DirectedWeightedEdge<int> edge3(3, node1, node3, 6);
    CXXGRAPH::T_EdgeSet<int> edgeSet;
    edgeSet.insert(&edge1);
    edgeSet.insert(&edge2);
    edgeSet.insert(&edge3);
    CXXGRAPH::Graph<int> graph(edgeSet);
    std::vector<CXXGRAPH::Node<int>> res = graph.breadth_first_search(node4);
    ASSERT_EQ(res.size(), 0);
    ASSERT_FALSE(std::find(res.begin(), res.end(), node1) != res.end());
    ASSERT_FALSE(std::find(res.begin(), res.end(), node2) != res.end());
    ASSERT_FALSE(std::find(res.begin(), res.end(), node3) != res.end());
    ASSERT_FALSE(std::find(res.begin(), res.end(), node4) != res.end());

}

// test cases of concurrency bfs
TEST(BFSTest, test_7)
{
    CXXGRAPH::Node<int> node1("1", 1);
    CXXGRAPH::Node<int> node2("2", 2);
    CXXGRAPH::Node<int> node3("3", 3);
    std::pair<const CXXGRAPH::Node<int> *, const CXXGRAPH::Node<int> *> pairNode(&node1, &node2);
    CXXGRAPH::DirectedWeightedEdge<int> edge1(1, pairNode, 1);
    CXXGRAPH::DirectedWeightedEdge<int> edge2(2, node2, node3, 1);
    CXXGRAPH::UndirectedWeightedEdge<int> edge3(3, node1, node3, 6);
    CXXGRAPH::T_EdgeSet<int> edgeSet;
    edgeSet.insert(&edge1);
    edgeSet.insert(&edge2);
    edgeSet.insert(&edge3);
    CXXGRAPH::Graph<int> graph(edgeSet);
    std::vector<CXXGRAPH::Node<int>> res = graph.concurrency_breadth_first_search(node1, 4);
    ASSERT_EQ(res.size(), 3);
    ASSERT_TRUE(std::find(res.begin(), res.end(), node1) != res.end());
    ASSERT_TRUE(std::find(res.begin(), res.end(), node2) != res.end());
    ASSERT_TRUE(std::find(res.begin(), res.end(), node3) != res.end());

}

TEST(BFSTest, test_8)
{
    CXXGRAPH::Node<int> node1("1", 1);
    CXXGRAPH::Node<int> node2("2", 2);
    CXXGRAPH::Node<int> node3("3", 3);
    std::pair<const CXXGRAPH::Node<int> *, const CXXGRAPH::Node<int> *> pairNode(&node1, &node2);
    CXXGRAPH::DirectedWeightedEdge<int> edge1(1, pairNode, 1);
    CXXGRAPH::DirectedWeightedEdge<int> edge2(2, node2, node3, 1);
    CXXGRAPH::DirectedWeightedEdge<int> edge3(3, node1, node3, 6);
    CXXGRAPH::T_EdgeSet<int> edgeSet;
    edgeSet.insert(&edge1);
    edgeSet.insert(&edge2);
    edgeSet.insert(&edge3);
    CXXGRAPH::Graph<int> graph(edgeSet);
    std::vector<CXXGRAPH::Node<int>> res = graph.concurrency_breadth_first_search(node2, 4);
    ASSERT_EQ(res.size(), 2);
    ASSERT_FALSE(std::find(res.begin(), res.end(), node1) != res.end());
    ASSERT_TRUE(std::find(res.begin(), res.end(), node2) != res.end());
    ASSERT_TRUE(std::find(res.begin(), res.end(), node3) != res.end());

}

TEST(BFSTest, test_9)
{
    CXXGRAPH::Node<int> node1("1", 1);
    CXXGRAPH::Node<int> node2("2", 2);
    CXXGRAPH::Node<int> node3("3", 3);
    std::pair<const CXXGRAPH::Node<int> *, const CXXGRAPH::Node<int> *> pairNode(&node1, &node2);
    CXXGRAPH::DirectedWeightedEdge<int> edge1(1, pairNode, 1);
    CXXGRAPH::DirectedWeightedEdge<int> edge2(2, node2, node3, 1);
    CXXGRAPH::UndirectedWeightedEdge<int> edge3(3, node1, node3, 6);
    CXXGRAPH::T_EdgeSet<int> edgeSet;
    edgeSet.insert(&edge1);
    edgeSet.insert(&edge2);
    edgeSet.insert(&edge3);
    CXXGRAPH::Graph<int> graph(edgeSet);
    std::vector<CXXGRAPH::Node<int>> res = graph.concurrency_breadth_first_search(node2, 4);
    ASSERT_EQ(res.size(), 3);
    ASSERT_TRUE(std::find(res.begin(), res.end(), node1) != res.end());
    ASSERT_TRUE(std::find(res.begin(), res.end(), node2) != res.end());
    ASSERT_TRUE(std::find(res.begin(), res.end(), node3) != res.end());
}

TEST(BFSTest, test_10)
{
    CXXGRAPH::Node<int> node1("1", 1);
    CXXGRAPH::Node<int> node2("2", 2);
    CXXGRAPH::Node<int> node3("3", 3);
    std::pair<const CXXGRAPH::Node<int> *, const CXXGRAPH::Node<int> *> pairNode(&node1, &node2);
    CXXGRAPH::DirectedWeightedEdge<int> edge1(1, pairNode, 1);
    CXXGRAPH::DirectedWeightedEdge<int> edge2(2, node2, node3, 1);
    CXXGRAPH::UndirectedWeightedEdge<int> edge3(3, node1, node3, 6);
    CXXGRAPH::T_EdgeSet<int> edgeSet;
    edgeSet.insert(&edge1);
    edgeSet.insert(&edge2);
    edgeSet.insert(&edge3);
    CXXGRAPH::Graph<int> graph(edgeSet);
    std::vector<CXXGRAPH::Node<int>> res = graph.concurrency_breadth_first_search(node3, 4);
    ASSERT_EQ(res.size(), 3);
    ASSERT_TRUE(std::find(res.begin(), res.end(), node1) != res.end());
    ASSERT_TRUE(std::find(res.begin(), res.end(), node2) != res.end());
    ASSERT_TRUE(std::find(res.begin(), res.end(), node3) != res.end());

}

TEST(BFSTest, test_11)
{
    CXXGRAPH::Node<int> node1("1", 1);
    CXXGRAPH::Node<int> node2("2", 2);
    CXXGRAPH::Node<int> node3("3", 3);
    std::pair<const CXXGRAPH::Node<int> *, const CXXGRAPH::Node<int> *> pairNode(&node1, &node2);
    CXXGRAPH::DirectedWeightedEdge<int> edge1(1, pairNode, 1);
    CXXGRAPH::DirectedWeightedEdge<int> edge2(2, node2, node3, 1);
    CXXGRAPH::DirectedWeightedEdge<int> edge3(3, node1, node3, 6);
    CXXGRAPH::T_EdgeSet<int> edgeSet;
    edgeSet.insert(&edge1);
    edgeSet.insert(&edge2);
    edgeSet.insert(&edge3);
    CXXGRAPH::Graph<int> graph(edgeSet);
    std::vector<CXXGRAPH::Node<int>> res = graph.concurrency_breadth_first_search(node3, 4);
    ASSERT_EQ(res.size(), 1);
    ASSERT_FALSE(std::find(res.begin(), res.end(), node1) != res.end());
    ASSERT_FALSE(std::find(res.begin(), res.end(), node2) != res.end());
    ASSERT_TRUE(std::find(res.begin(), res.end(), node3) != res.end());

}

TEST(BFSTest, test_12)
{
    CXXGRAPH::Node<int> node1("1", 1);
    CXXGRAPH::Node<int> node2("2", 2);
    CXXGRAPH::Node<int> node3("3", 3);
    CXXGRAPH::Node<int> node4("4", 4);
    CXXGRAPH::Node<int> node5("5", 5);
    CXXGRAPH::Node<int> node6("6", 6);
    CXXGRAPH::Node<int> node7("7", 7);
    CXXGRAPH::Node<int> node8("8", 8);
    std::pair<const CXXGRAPH::Node<int> *, const CXXGRAPH::Node<int> *> pairNode(&node1, &node2);
    CXXGRAPH::UndirectedWeightedEdge<int> edge1(1, pairNode, 1);
    CXXGRAPH::UndirectedWeightedEdge<int> edge2(2, node2, node3, 1);
    CXXGRAPH::UndirectedWeightedEdge<int> edge3(3, node2, node6, 6);
    CXXGRAPH::UndirectedWeightedEdge<int> edge4(3, node3, node4, 6);
    CXXGRAPH::UndirectedWeightedEdge<int> edge5(3, node3, node5, 6);
    CXXGRAPH::UndirectedWeightedEdge<int> edge6(3, node6, node7, 6);
    CXXGRAPH::UndirectedWeightedEdge<int> edge7(3, node8, node6, 6);
    CXXGRAPH::UndirectedWeightedEdge<int> edge8(3, node8, node7, 6);
    CXXGRAPH::T_EdgeSet<int> edgeSet;
    edgeSet.insert(&edge1);
    edgeSet.insert(&edge2);
    edgeSet.insert(&edge3);
    edgeSet.insert(&edge4);
    edgeSet.insert(&edge5);
    edgeSet.insert(&edge6);
    edgeSet.insert(&edge7);
    edgeSet.insert(&edge8);
    CXXGRAPH::Graph<int> graph(edgeSet);
    std::vector<CXXGRAPH::Node<int>> res = graph.concurrency_breadth_first_search(node8, 4);
    ASSERT_EQ(res.size(), 8);
}

// this case is to verify result correction when number of threads more than 1  
TEST(BFSTest, test_13)
{
    unsigned int randSeed = (unsigned int)time(NULL);
    srand(randSeed);

    int nodes_size = 60, edges_size = 2000;
    std::vector<CXXGRAPH::Node<int> *> nodes;
    for (auto index = 0; index < nodes_size; index++)
    {
        int randomNumber = (rand_r(&randSeed) % nodes_size) + 1;
        CXXGRAPH::Node<int> *newNode = new CXXGRAPH::Node<int>(std::to_string(index), randomNumber);
        nodes.push_back(newNode);
    }
        
    CXXGRAPH::T_EdgeSet<int> edgeSet;
    auto MaxValue = nodes.size();
    for (auto index = 0; index < edges_size; index++)
    {
        int randomNumber1 = (rand_r(&randSeed) % MaxValue);
        int randomNumber2 = (rand_r(&randSeed) % MaxValue);
        if (randomNumber1 != randomNumber2)
        {
            CXXGRAPH::UndirectedEdge<int> *newEdge = new CXXGRAPH::UndirectedEdge<int>(index, *(nodes.at(randomNumber1)), *(nodes.at(randomNumber2)));
            edgeSet.insert(newEdge);
        }
    }
    for (int i = 1; i < nodes.size(); i += 2)
    {
        CXXGRAPH::UndirectedEdge<int> *newEdge = new CXXGRAPH::UndirectedEdge<int>(edges_size + i + 1, *(nodes.at(0)), *(nodes.at(i)));
        edgeSet.insert(newEdge);
    }
    CXXGRAPH::Graph<int> graph(edgeSet);
   
    auto &result1 = graph.breadth_first_search(*(nodes[0]));
    std::set<CXXGRAPH::Node<int>> st1;
    for (const auto &node : result1)
    {
        st1.emplace(node);
    }

    auto &result2 = graph.concurrency_breadth_first_search(*(nodes[0]), 4);
    ASSERT_EQ(result1.size(), result2.size());

    for (const auto &node : result2)
    {
        ASSERT_TRUE(st1.count(node));
        if (!st1.count(node))
        {
            std::cout << node;
        }
    }
}
