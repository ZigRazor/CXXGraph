#include "gtest/gtest.h"
#include "CXXGraph.hpp"
#include "Utilities.hpp"

static auto nodes = generateRandomNodes(10000, 2);
static auto edges = generateRandomEdges(10000, nodes);

TEST(PartitionTest, test_1)
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
    CXXGRAPH::DirectedWeightedEdge<int> edge1(1, pairNode, 1);
    CXXGRAPH::DirectedWeightedEdge<int> edge2(2, node2, node3, 1);
    CXXGRAPH::UndirectedWeightedEdge<int> edge3(3, node1, node3, 1);
    CXXGRAPH::UndirectedWeightedEdge<int> edge4(4, node4, node5, 1);
    CXXGRAPH::UndirectedWeightedEdge<int> edge5(5, node4, node6, 1);
    CXXGRAPH::UndirectedWeightedEdge<int> edge6(6, node3, node4, 1);
    CXXGRAPH::UndirectedWeightedEdge<int> edge7(7, node2, node8, 1);
    CXXGRAPH::UndirectedWeightedEdge<int> edge8(8, node7, node8, 1);
    CXXGRAPH::UndirectedWeightedEdge<int> edge9(9, node1, node6, 1);
    CXXGRAPH::UndirectedWeightedEdge<int> edge10(10, node3, node5, 1);
    CXXGRAPH::UndirectedWeightedEdge<int> edge11(11, node3, node6, 1);
    CXXGRAPH::UndirectedWeightedEdge<int> edge12(12, node4, node8, 1);
    std::list<const CXXGRAPH::Edge<int> *> edgeSet;
    edgeSet.push_back(&edge1);
    edgeSet.push_back(&edge2);
    edgeSet.push_back(&edge3);
    edgeSet.push_back(&edge4);
    edgeSet.push_back(&edge5);
    edgeSet.push_back(&edge6);
    edgeSet.push_back(&edge7);
    edgeSet.push_back(&edge8);
    edgeSet.push_back(&edge9);
    edgeSet.push_back(&edge10);
    edgeSet.push_back(&edge11);
    edgeSet.push_back(&edge12);
    CXXGRAPH::Graph<int> graph(edgeSet);
    ASSERT_EQ(graph.getEdgeSet().size(), 12);
    auto partitionMap = graph.partitionGraph(CXXGRAPH::PARTITIONING::PartitionAlgorithm::HDRF_ALG,4,1,0.001);
    unsigned int totalEdgeInPartition = 0;
    for (auto elem : partitionMap)
    {
        totalEdgeInPartition += elem.second->getEdgeSet().size();
    }
    //std::cout << "Total Edge in Partition: " << totalEdgeInPartition << std::endl;
    ASSERT_EQ(totalEdgeInPartition, 12);
    for (int i = 0; i < 4; ++i)
    {
        //std::cout << *partitionMap.at(i) << std::endl;
        ASSERT_EQ(partitionMap.at(i)->getPartitionId(), i);
    }
}

TEST(PartitionTest, test_2)
{
    CXXGRAPH::Graph<int> graph;
    for (auto e : edges)
    {
        graph.addEdge(&(*e.second));
    }
    auto partitionMap = graph.partitionGraph(CXXGRAPH::PARTITIONING::PartitionAlgorithm::HDRF_ALG, 4,1,0.001);
    unsigned int totalEdgeInPartition = 0;
    for (auto elem : partitionMap)
    {
        totalEdgeInPartition += elem.second->getEdgeSet().size();
    }
    //std::cout << "Total Edge in Partition: " << totalEdgeInPartition << std::endl;
    ASSERT_EQ(totalEdgeInPartition, 10000);
    for (int i = 0; i < 4; ++i)
    {
        //std::cout << *partitionMap.at(i) << std::endl;
        ASSERT_EQ(partitionMap.at(i)->getPartitionId(), i);
    }
}


TEST(PartitionTest, test_3)
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
    CXXGRAPH::DirectedWeightedEdge<int> edge1(1, pairNode, 1);
    CXXGRAPH::DirectedWeightedEdge<int> edge2(2, node2, node3, 1);
    CXXGRAPH::UndirectedWeightedEdge<int> edge3(3, node1, node3, 1);
    CXXGRAPH::UndirectedWeightedEdge<int> edge4(4, node4, node5, 1);
    CXXGRAPH::UndirectedWeightedEdge<int> edge5(5, node4, node6, 1);
    CXXGRAPH::UndirectedWeightedEdge<int> edge6(6, node3, node4, 1);
    CXXGRAPH::UndirectedWeightedEdge<int> edge7(7, node2, node8, 1);
    CXXGRAPH::UndirectedWeightedEdge<int> edge8(8, node7, node8, 1);
    CXXGRAPH::UndirectedWeightedEdge<int> edge9(9, node1, node6, 1);
    CXXGRAPH::UndirectedWeightedEdge<int> edge10(10, node3, node5, 1);
    CXXGRAPH::UndirectedWeightedEdge<int> edge11(11, node3, node6, 1);
    CXXGRAPH::UndirectedWeightedEdge<int> edge12(12, node4, node8, 1);
    std::list<const CXXGRAPH::Edge<int> *> edgeSet;
    edgeSet.push_back(&edge1);
    edgeSet.push_back(&edge2);
    edgeSet.push_back(&edge3);
    edgeSet.push_back(&edge4);
    edgeSet.push_back(&edge5);
    edgeSet.push_back(&edge6);
    edgeSet.push_back(&edge7);
    edgeSet.push_back(&edge8);
    edgeSet.push_back(&edge9);
    edgeSet.push_back(&edge10);
    edgeSet.push_back(&edge11);
    edgeSet.push_back(&edge12);
    CXXGRAPH::Graph<int> graph(edgeSet);
    ASSERT_EQ(graph.getEdgeSet().size(), 12);
    auto partitionMap = graph.partitionGraph(CXXGRAPH::PARTITIONING::PartitionAlgorithm::EDGEBALANCED_VC_ALG, 4);
    unsigned int totalEdgeInPartition = 0;
    for (const auto& elem : partitionMap)
    {
        totalEdgeInPartition += elem.second->getEdgeSet().size();
    }
    //std::cout << "Total Edge in Partition: " << totalEdgeInPartition << std::endl;git 
    ASSERT_EQ(totalEdgeInPartition, 12);
    for (int i = 0; i < 4; ++i)
    {
        //std::cout << *partitionMap.at(i) << std::endl;
        ASSERT_EQ(partitionMap.at(i)->getPartitionId(), i);
    }
}

TEST(PartitionTest, test_4)
{
    CXXGRAPH::Graph<int> graph;
    for (auto e : edges)
    {
        graph.addEdge(&(*e.second));
    }
    auto partitionMap = graph.partitionGraph(CXXGRAPH::PARTITIONING::PartitionAlgorithm::EDGEBALANCED_VC_ALG, 4);
    unsigned int totalEdgeInPartition = 0;
    for (auto elem : partitionMap)
    {
        totalEdgeInPartition += elem.second->getEdgeSet().size();
    }
    //std::cout << "Total Edge in Partition: " << totalEdgeInPartition << std::endl;
    ASSERT_EQ(totalEdgeInPartition, 10000);
    for (int i = 0; i < 4; ++i)
    {
        //std::cout << *partitionMap.at(i) << std::endl;
        ASSERT_EQ(partitionMap.at(i)->getPartitionId(), i);
    }
}

TEST(PartitionTest, test_5)
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
    CXXGRAPH::DirectedWeightedEdge<int> edge1(1, pairNode, 1);
    CXXGRAPH::DirectedWeightedEdge<int> edge2(2, node2, node3, 1);
    CXXGRAPH::UndirectedWeightedEdge<int> edge3(3, node1, node3, 1);
    CXXGRAPH::UndirectedWeightedEdge<int> edge4(4, node4, node5, 1);
    CXXGRAPH::UndirectedWeightedEdge<int> edge5(5, node4, node6, 1);
    CXXGRAPH::UndirectedWeightedEdge<int> edge6(6, node3, node4, 1);
    CXXGRAPH::UndirectedWeightedEdge<int> edge7(7, node2, node8, 1);
    CXXGRAPH::UndirectedWeightedEdge<int> edge8(8, node7, node8, 1);
    CXXGRAPH::UndirectedWeightedEdge<int> edge9(9, node1, node6, 1);
    CXXGRAPH::UndirectedWeightedEdge<int> edge10(10, node3, node5, 1);
    CXXGRAPH::UndirectedWeightedEdge<int> edge11(11, node3, node6, 1);
    CXXGRAPH::UndirectedWeightedEdge<int> edge12(12, node4, node8, 1);
    std::list<const CXXGRAPH::Edge<int> *> edgeSet;
    edgeSet.push_back(&edge1);
    edgeSet.push_back(&edge2);
    edgeSet.push_back(&edge3);
    edgeSet.push_back(&edge4);
    edgeSet.push_back(&edge5);
    edgeSet.push_back(&edge6);
    edgeSet.push_back(&edge7);
    edgeSet.push_back(&edge8);
    edgeSet.push_back(&edge9);
    edgeSet.push_back(&edge10);
    edgeSet.push_back(&edge11);
    edgeSet.push_back(&edge12);
    CXXGRAPH::Graph<int> graph(edgeSet);
    ASSERT_EQ(graph.getEdgeSet().size(), 12);
    auto partitionMap = graph.partitionGraph(CXXGRAPH::PARTITIONING::PartitionAlgorithm::GREEDY_VC_ALG, 4);
    unsigned int totalEdgeInPartition = 0;
    for (const auto& elem : partitionMap)
    {
        totalEdgeInPartition += elem.second->getEdgeSet().size();
    }
    //std::cout << "Total Edge in Partition: " << totalEdgeInPartition << std::endl;
    ASSERT_EQ(totalEdgeInPartition, 12);
    for (int i = 0; i < 4; ++i)
    {
        //std::cout << *partitionMap.at(i) << std::endl;
        ASSERT_EQ(partitionMap.at(i)->getPartitionId(), i);
    }
}

TEST(PartitionTest, test_6)
{
    CXXGRAPH::Graph<int> graph;
    for (auto e : edges)
    {
        graph.addEdge(&(*e.second));
    }
    auto partitionMap = graph.partitionGraph(CXXGRAPH::PARTITIONING::PartitionAlgorithm::GREEDY_VC_ALG, 4);
    unsigned int totalEdgeInPartition = 0;
    for (auto elem : partitionMap)
    {
        totalEdgeInPartition += elem.second->getEdgeSet().size();
    }
    //std::cout << "Total Edge in Partition: " << totalEdgeInPartition << std::endl;
    ASSERT_EQ(totalEdgeInPartition, 10000);
    for (int i = 0; i < 4; ++i)
    {
        //std::cout << *partitionMap.at(i) << std::endl;
        ASSERT_EQ(partitionMap.at(i)->getPartitionId(), i);
    }
}

TEST(PartitionTest, test_7)
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
    CXXGRAPH::DirectedWeightedEdge<int> edge1(1, pairNode, 1);
    CXXGRAPH::DirectedWeightedEdge<int> edge2(2, node2, node3, 1);
    CXXGRAPH::UndirectedWeightedEdge<int> edge3(3, node1, node3, 1);
    CXXGRAPH::UndirectedWeightedEdge<int> edge4(4, node4, node5, 1);
    CXXGRAPH::UndirectedWeightedEdge<int> edge5(5, node4, node6, 1);
    CXXGRAPH::UndirectedWeightedEdge<int> edge6(6, node3, node4, 1);
    CXXGRAPH::UndirectedWeightedEdge<int> edge7(7, node2, node8, 1);
    CXXGRAPH::UndirectedWeightedEdge<int> edge8(8, node7, node8, 1);
    CXXGRAPH::UndirectedWeightedEdge<int> edge9(9, node1, node6, 1);
    CXXGRAPH::UndirectedWeightedEdge<int> edge10(10, node3, node5, 1);
    CXXGRAPH::UndirectedWeightedEdge<int> edge11(11, node3, node6, 1);
    CXXGRAPH::UndirectedWeightedEdge<int> edge12(12, node4, node8, 1);
    std::list<const CXXGRAPH::Edge<int> *> edgeSet;
    edgeSet.push_back(&edge1);
    edgeSet.push_back(&edge2);
    edgeSet.push_back(&edge3);
    edgeSet.push_back(&edge4);
    edgeSet.push_back(&edge5);
    edgeSet.push_back(&edge6);
    edgeSet.push_back(&edge7);
    edgeSet.push_back(&edge8);
    edgeSet.push_back(&edge9);
    edgeSet.push_back(&edge10);
    edgeSet.push_back(&edge11);
    edgeSet.push_back(&edge12);
    CXXGRAPH::Graph<int> graph(edgeSet);
    ASSERT_EQ(graph.getEdgeSet().size(), 12);
    auto partitionMap = graph.partitionGraph(CXXGRAPH::PARTITIONING::PartitionAlgorithm::EBV_ALG, 4,1,1);
    unsigned int totalEdgeInPartition = 0;
    for (const auto& elem : partitionMap)
    {
        totalEdgeInPartition += elem.second->getEdgeSet().size();
    }
    //std::cout << "Total Edge in Partition: " << totalEdgeInPartition << std::endl;
    ASSERT_EQ(totalEdgeInPartition, 12);
    for (int i = 0; i < 4; ++i)
    {
        //std::cout << *partitionMap.at(i) << std::endl;
        ASSERT_EQ(partitionMap.at(i)->getPartitionId(), i);
    }
}

TEST(PartitionTest, test_8)
{
    CXXGRAPH::Graph<int> graph;
    for (auto e : edges)
    {
        graph.addEdge(&(*e.second));
    }
    auto partitionMap = graph.partitionGraph(CXXGRAPH::PARTITIONING::PartitionAlgorithm::EBV_ALG, 4,1,1);
    unsigned int totalEdgeInPartition = 0;
    for (auto elem : partitionMap)
    {
        totalEdgeInPartition += elem.second->getEdgeSet().size();
    }
    //std::cout << "Total Edge in Partition: " << totalEdgeInPartition << std::endl;
    ASSERT_EQ(totalEdgeInPartition, 10000);
    for (int i = 0; i < 4; ++i)
    {
        //std::cout << *partitionMap.at(i) << std::endl;
        ASSERT_EQ(partitionMap.at(i)->getPartitionId(), i);
    }
}