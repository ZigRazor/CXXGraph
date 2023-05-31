#include <Edge/Edge.hpp>
#include <memory>
#include "CXXGraph.hpp"
#include "Utilities.hpp"
#include "gtest/gtest.h"

// Smart pointers alias
template <typename T>
using unique = std::unique_ptr<T>;
template <typename T>
using shared= std::shared_ptr<T>;

using std::make_unique;
using std::make_shared;

static auto nodes = generateRandomNodes(10000, 2);
static auto edges = generateRandomEdges(10000, nodes);

TEST(PartitionTest, test_1) {
  CXXGraph::Node<int> node1("1", 1);
  CXXGraph::Node<int> node2("2", 2);
  CXXGraph::Node<int> node3("3", 3);
  CXXGraph::Node<int> node4("4", 4);
  CXXGraph::Node<int> node5("5", 5);
  CXXGraph::Node<int> node6("6", 6);
  CXXGraph::Node<int> node7("7", 7);
  CXXGraph::Node<int> node8("8", 8);
  std::pair<const CXXGraph::Node<int> *, const CXXGraph::Node<int> *> pairNode(
      &node1, &node2);
  CXXGraph::DirectedWeightedEdge<int> edge1(1, pairNode, 1);
  CXXGraph::DirectedWeightedEdge<int> edge2(2, node2, node3, 1);
  CXXGraph::UndirectedWeightedEdge<int> edge3(3, node1, node3, 1);
  CXXGraph::UndirectedWeightedEdge<int> edge4(4, node4, node5, 1);
  CXXGraph::UndirectedWeightedEdge<int> edge5(5, node4, node6, 1);
  CXXGraph::UndirectedWeightedEdge<int> edge6(6, node3, node4, 1);
  CXXGraph::UndirectedWeightedEdge<int> edge7(7, node2, node8, 1);
  CXXGraph::UndirectedWeightedEdge<int> edge8(8, node7, node8, 1);
  CXXGraph::UndirectedWeightedEdge<int> edge9(9, node1, node6, 1);
  CXXGraph::UndirectedWeightedEdge<int> edge10(10, node3, node5, 1);
  CXXGraph::UndirectedWeightedEdge<int> edge11(11, node3, node6, 1);
  CXXGraph::UndirectedWeightedEdge<int> edge12(12, node4, node8, 1);
  CXXGraph::T_EdgeSet<int> edgeSet;
  edgeSet.insert(make_shared<CXXGraph::DirectedWeightedEdge<int>>(edge1));
  edgeSet.insert(make_shared<CXXGraph::DirectedWeightedEdge<int>>(edge2));
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
  CXXGraph::Graph<int> graph(edgeSet);
  ASSERT_EQ(graph.getEdgeSet().size(), 12);
  auto partitionMap = graph.partitionGraph(
      CXXGraph::Partitioning::PartitionAlgorithm::HDRF_ALG, 4, 1, 0.001);
  unsigned int totalEdgeInPartition = 0;
  for (const auto &elem : partitionMap) {
    totalEdgeInPartition += elem.second->getEdgeSet().size();
  }
  // std::cout << "Total Edge in Partition: " << totalEdgeInPartition <<
  // std::endl;
  ASSERT_EQ(totalEdgeInPartition, 12);
  for (int i = 0; i < 4; ++i) {
    // std::cout << *partitionMap.at(i) << std::endl;
    ASSERT_EQ(partitionMap.at(i)->getPartitionId(), i);
  }
}

TEST(PartitionTest, test_2) {
  CXXGraph::Graph<int> graph;
  for (auto e : edges) {
    graph.addEdge(e.second);
  }
  auto partitionMap = graph.partitionGraph(
      CXXGraph::Partitioning::PartitionAlgorithm::HDRF_ALG, 4, 1, 0.001);
  unsigned int totalEdgeInPartition = 0;
  for (const auto &elem : partitionMap) {
    totalEdgeInPartition += elem.second->getEdgeSet().size();
  }
  // std::cout << "Total Edge in Partition: " << totalEdgeInPartition <<
  // std::endl;
  ASSERT_EQ(totalEdgeInPartition, graph.getEdgeSet().size());
  for (int i = 0; i < 4; ++i) {
    // std::cout << *partitionMap.at(i) << std::endl;
    ASSERT_EQ(partitionMap.at(i)->getPartitionId(), i);
  }
}

TEST(PartitionTest, test_3) {
  CXXGraph::Node<int> node1("1", 1);
  CXXGraph::Node<int> node2("2", 2);
  CXXGraph::Node<int> node3("3", 3);
  CXXGraph::Node<int> node4("4", 4);
  CXXGraph::Node<int> node5("5", 5);
  CXXGraph::Node<int> node6("6", 6);
  CXXGraph::Node<int> node7("7", 7);
  CXXGraph::Node<int> node8("8", 8);
  std::pair<const CXXGraph::Node<int> *, const CXXGraph::Node<int> *> pairNode(
      &node1, &node2);
  CXXGraph::DirectedWeightedEdge<int> edge1(1, pairNode, 1);
  CXXGraph::DirectedWeightedEdge<int> edge2(2, node2, node3, 1);
  CXXGraph::UndirectedWeightedEdge<int> edge3(3, node1, node3, 1);
  CXXGraph::UndirectedWeightedEdge<int> edge4(4, node4, node5, 1);
  CXXGraph::UndirectedWeightedEdge<int> edge5(5, node4, node6, 1);
  CXXGraph::UndirectedWeightedEdge<int> edge6(6, node3, node4, 1);
  CXXGraph::UndirectedWeightedEdge<int> edge7(7, node2, node8, 1);
  CXXGraph::UndirectedWeightedEdge<int> edge8(8, node7, node8, 1);
  CXXGraph::UndirectedWeightedEdge<int> edge9(9, node1, node6, 1);
  CXXGraph::UndirectedWeightedEdge<int> edge10(10, node3, node5, 1);
  CXXGraph::UndirectedWeightedEdge<int> edge11(11, node3, node6, 1);
  CXXGraph::UndirectedWeightedEdge<int> edge12(12, node4, node8, 1);
  CXXGraph::T_EdgeSet<int> edgeSet;
  edgeSet.insert(make_shared<CXXGraph::DirectedWeightedEdge<int>>(edge1));
  edgeSet.insert(make_shared<CXXGraph::DirectedWeightedEdge<int>>(edge2));
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
  CXXGraph::Graph<int> graph(edgeSet);
  ASSERT_EQ(graph.getEdgeSet().size(), 12);
  auto partitionMap = graph.partitionGraph(
      CXXGraph::Partitioning::PartitionAlgorithm::EDGEBALANCED_VC_ALG, 4);
  unsigned int totalEdgeInPartition = 0;
  for (const auto &elem : partitionMap) {
    totalEdgeInPartition += elem.second->getEdgeSet().size();
  }
  // std::cout << "Total Edge in Partition: " << totalEdgeInPartition <<
  // std::endl;git
  ASSERT_EQ(totalEdgeInPartition, 12);
  for (int i = 0; i < 4; ++i) {
    // std::cout << *partitionMap.at(i) << std::endl;
    ASSERT_EQ(partitionMap.at(i)->getPartitionId(), i);
  }
}

TEST(PartitionTest, test_4) {
  CXXGraph::Graph<int> graph;
  for (auto e : edges) {
    graph.addEdge(e.second);
  }
  auto partitionMap = graph.partitionGraph(
      CXXGraph::Partitioning::PartitionAlgorithm::EDGEBALANCED_VC_ALG, 4);
  unsigned int totalEdgeInPartition = 0;
  for (const auto &elem : partitionMap) {
    totalEdgeInPartition += elem.second->getEdgeSet().size();
  }
  // std::cout << "Total Edge in Partition: " << totalEdgeInPartition <<
  // std::endl;
  ASSERT_EQ(totalEdgeInPartition, graph.getEdgeSet().size());
  for (int i = 0; i < 4; ++i) {
    // std::cout << *partitionMap.at(i) << std::endl;
    ASSERT_EQ(partitionMap.at(i)->getPartitionId(), i);
  }
}

TEST(PartitionTest, test_5) {
  CXXGraph::Node<int> node1("1", 1);
  CXXGraph::Node<int> node2("2", 2);
  CXXGraph::Node<int> node3("3", 3);
  CXXGraph::Node<int> node4("4", 4);
  CXXGraph::Node<int> node5("5", 5);
  CXXGraph::Node<int> node6("6", 6);
  CXXGraph::Node<int> node7("7", 7);
  CXXGraph::Node<int> node8("8", 8);
  std::pair<const CXXGraph::Node<int> *, const CXXGraph::Node<int> *> pairNode(
      &node1, &node2);
  CXXGraph::DirectedWeightedEdge<int> edge1(1, pairNode, 1);
  CXXGraph::DirectedWeightedEdge<int> edge2(2, node2, node3, 1);
  CXXGraph::UndirectedWeightedEdge<int> edge3(3, node1, node3, 1);
  CXXGraph::UndirectedWeightedEdge<int> edge4(4, node4, node5, 1);
  CXXGraph::UndirectedWeightedEdge<int> edge5(5, node4, node6, 1);
  CXXGraph::UndirectedWeightedEdge<int> edge6(6, node3, node4, 1);
  CXXGraph::UndirectedWeightedEdge<int> edge7(7, node2, node8, 1);
  CXXGraph::UndirectedWeightedEdge<int> edge8(8, node7, node8, 1);
  CXXGraph::UndirectedWeightedEdge<int> edge9(9, node1, node6, 1);
  CXXGraph::UndirectedWeightedEdge<int> edge10(10, node3, node5, 1);
  CXXGraph::UndirectedWeightedEdge<int> edge11(11, node3, node6, 1);
  CXXGraph::UndirectedWeightedEdge<int> edge12(12, node4, node8, 1);
  CXXGraph::T_EdgeSet<int> edgeSet;
  edgeSet.insert(make_shared<CXXGraph::DirectedWeightedEdge<int>>(edge1));
  edgeSet.insert(make_shared<CXXGraph::DirectedWeightedEdge<int>>(edge2));
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
  CXXGraph::Graph<int> graph(edgeSet);
  ASSERT_EQ(graph.getEdgeSet().size(), 12);
  auto partitionMap = graph.partitionGraph(
      CXXGraph::Partitioning::PartitionAlgorithm::GREEDY_VC_ALG, 4);
  unsigned int totalEdgeInPartition = 0;
  for (const auto &elem : partitionMap) {
    totalEdgeInPartition += elem.second->getEdgeSet().size();
  }
  // std::cout << "Total Edge in Partition: " << totalEdgeInPartition <<
  // std::endl;
  ASSERT_EQ(totalEdgeInPartition, 12);
  for (int i = 0; i < 4; ++i) {
    // std::cout << *partitionMap.at(i) << std::endl;
    ASSERT_EQ(partitionMap.at(i)->getPartitionId(), i);
  }
}

TEST(PartitionTest, test_6) {
  CXXGraph::Graph<int> graph;
  for (auto e : edges) {
    graph.addEdge(e.second);
  }
  auto partitionMap = graph.partitionGraph(
      CXXGraph::Partitioning::PartitionAlgorithm::GREEDY_VC_ALG, 4);
  unsigned int totalEdgeInPartition = 0;
  for (const auto &elem : partitionMap) {
    totalEdgeInPartition += elem.second->getEdgeSet().size();
  }
  // std::cout << "Total Edge in Partition: " << totalEdgeInPartition <<
  // std::endl;
  ASSERT_EQ(totalEdgeInPartition, graph.getEdgeSet().size());
  for (int i = 0; i < 4; ++i) {
    // std::cout << *partitionMap.at(i) << std::endl;
    ASSERT_EQ(partitionMap.at(i)->getPartitionId(), i);
  }
}

TEST(PartitionTest, test_7) {
  CXXGraph::Node<int> node1("1", 1);
  CXXGraph::Node<int> node2("2", 2);
  CXXGraph::Node<int> node3("3", 3);
  CXXGraph::Node<int> node4("4", 4);
  CXXGraph::Node<int> node5("5", 5);
  CXXGraph::Node<int> node6("6", 6);
  CXXGraph::Node<int> node7("7", 7);
  CXXGraph::Node<int> node8("8", 8);
  std::pair<const CXXGraph::Node<int> *, const CXXGraph::Node<int> *> pairNode(
      &node1, &node2);
  CXXGraph::DirectedWeightedEdge<int> edge1(1, pairNode, 1);
  CXXGraph::DirectedWeightedEdge<int> edge2(2, node2, node3, 1);
  CXXGraph::UndirectedWeightedEdge<int> edge3(3, node1, node3, 1);
  CXXGraph::UndirectedWeightedEdge<int> edge4(4, node4, node5, 1);
  CXXGraph::UndirectedWeightedEdge<int> edge5(5, node4, node6, 1);
  CXXGraph::UndirectedWeightedEdge<int> edge6(6, node3, node4, 1);
  CXXGraph::UndirectedWeightedEdge<int> edge7(7, node2, node8, 1);
  CXXGraph::UndirectedWeightedEdge<int> edge8(8, node7, node8, 1);
  CXXGraph::UndirectedWeightedEdge<int> edge9(9, node1, node6, 1);
  CXXGraph::UndirectedWeightedEdge<int> edge10(10, node3, node5, 1);
  CXXGraph::UndirectedWeightedEdge<int> edge11(11, node3, node6, 1);
  CXXGraph::UndirectedWeightedEdge<int> edge12(12, node4, node8, 1);
  CXXGraph::T_EdgeSet<int> edgeSet;
  edgeSet.insert(make_shared<CXXGraph::DirectedWeightedEdge<int>>(edge1));
  edgeSet.insert(make_shared<CXXGraph::DirectedWeightedEdge<int>>(edge2));
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
  CXXGraph::Graph<int> graph(edgeSet);
  ASSERT_EQ(graph.getEdgeSet().size(), 12);
  auto partitionMap = graph.partitionGraph(
      CXXGraph::Partitioning::PartitionAlgorithm::EBV_ALG, 4, 1, 1);
  unsigned int totalEdgeInPartition = 0;
  for (const auto &elem : partitionMap) {
    totalEdgeInPartition += elem.second->getEdgeSet().size();
  }
  // std::cout << "Total Edge in Partition: " << totalEdgeInPartition <<
  // std::endl;
  ASSERT_EQ(totalEdgeInPartition, 12);
  for (int i = 0; i < 4; ++i) {
    // std::cout << *partitionMap.at(i) << std::endl;
    ASSERT_EQ(partitionMap.at(i)->getPartitionId(), i);
  }
}

TEST(PartitionTest, test_8) {
  CXXGraph::Graph<int> graph;
  for (auto e : edges) {
    graph.addEdge(e.second);
  }
  auto partitionMap = graph.partitionGraph(
      CXXGraph::Partitioning::PartitionAlgorithm::EBV_ALG, 4, 1, 1);
  unsigned int totalEdgeInPartition = 0;
  for (const auto &elem : partitionMap) {
    totalEdgeInPartition += elem.second->getEdgeSet().size();
  }
  // std::cout << "Total Edge in Partition: " << totalEdgeInPartition <<
  // std::endl;
  ASSERT_EQ(totalEdgeInPartition, graph.getEdgeSet().size());
  for (int i = 0; i < 4; ++i) {
    // std::cout << *partitionMap.at(i) << std::endl;
    ASSERT_EQ(partitionMap.at(i)->getPartitionId(), i);
  }
}

TEST(PartitionTest, test_9) {
  CXXGraph::Graph<int> graph;
  for (auto e : edges) {
    graph.addEdge(e.second);
  }
  auto partitionMap =
      graph.partitionGraph(CXXGraph::Partitioning::PartitionAlgorithm::WB_LIBRA,
                           4, 1.0, 0.0, 0.0, 4);
  unsigned int totalEdgeInPartition = 0;
  for (const auto &elem : partitionMap) {
    totalEdgeInPartition += elem.second->getEdgeSet().size();
    // std::cout << elem.second->getEdgeSet().size() << std::endl;
  }
  // std::cout << "Total Edge in Partition: " << totalEdgeInPartition <<
  // std::endl;
  ASSERT_EQ(totalEdgeInPartition, graph.getEdgeSet().size());
  for (int i = 0; i < 4; ++i) {
    ASSERT_EQ(partitionMap.at(i)->getPartitionId(), i);
  }
}
