#include <fstream>
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

inline bool exists_test(const std::string &name) {
  struct stat buffer;
  return (stat(name.c_str(), &buffer) == 0);
}

static std::unordered_map<unsigned long, shared<CXXGraph::Node<int>>>
generateRandomNodes(unsigned long numberOfNodes, int MaxValue) {
  std::unordered_map<unsigned long, shared<CXXGraph::Node<int>>> nodes;
  srand(static_cast<unsigned>(time(NULL)));
  int randomNumber;
  for (unsigned long index = 0; index < numberOfNodes; ++index) {
    // auto index = std::to_string(index);
    randomNumber = (rand() % MaxValue) + 1;
    auto newNode =
        make_shared<CXXGraph::Node<int>>(std::to_string(index), randomNumber);
    nodes[index] = newNode;
  }
  return nodes;
}

static std::unordered_map<unsigned long, shared<CXXGraph::Edge<int>>>
generateRandomEdges(
    unsigned long numberOfEdges,
    std::unordered_map<unsigned long, shared<CXXGraph::Node<int>>> nodes) {
  std::unordered_map<unsigned long, shared<CXXGraph::Edge<int>>> edges;
  srand(static_cast<unsigned>(time(NULL)));
  int randomNumber1;
  int randomNumber2;
  auto MaxValue = nodes.size();
  for (unsigned long index = 0; index < numberOfEdges; ++index) {
    randomNumber1 = (rand() % MaxValue);
    randomNumber2 = (rand() % MaxValue);
    auto newEdge = make_shared<CXXGraph::Edge<int>>(
        index, *(nodes.at(randomNumber1)), *(nodes.at(randomNumber2)));
    edges[index] = newEdge;
  }
  return edges;
}

static auto nodes = generateRandomNodes(10000, 2);
static auto edges = generateRandomEdges(10000, nodes);

//************* CSV ***************//

TEST(RWOutputTest, test_1) {
  CXXGraph::Node<int> node1("1", 1);
  CXXGraph::Node<int> node2("2", 2);
  CXXGraph::Node<int> node3("3", 3);
  std::pair<const CXXGraph::Node<int> *, const CXXGraph::Node<int> *> pairNode(
      &node1, &node2);
  CXXGraph::DirectedWeightedEdge<int> edge1(1, pairNode, 1);
  CXXGraph::DirectedWeightedEdge<int> edge2(2, node2, node3, 1);
  CXXGraph::UndirectedWeightedEdge<int> edge3(3, node1, node3, 6);
  CXXGraph::T_EdgeSet<int> edgeSet;
  edgeSet.insert(make_shared<CXXGraph::DirectedWeightedEdge<int>>(edge1));
  edgeSet.insert(make_shared<CXXGraph::DirectedWeightedEdge<int>>(edge2));
  edgeSet.insert(make_shared<CXXGraph::UndirectedWeightedEdge<int>>(edge3));
  CXXGraph::Graph<int> graph(edgeSet);
  int res = graph.writeToFile();
  ASSERT_EQ(res, 0);
  ASSERT_TRUE(exists_test("graph.csv"));
  ASSERT_FALSE(exists_test("graph_NodeFeat.csv"));
  ASSERT_FALSE(exists_test("graph_EdgeWeight.csv"));

  remove("graph.csv");
  ASSERT_FALSE(exists_test("graph.csv"));
}

TEST(RWOutputTest, test_2) {
  CXXGraph::Node<int> node1("1", 1);
  CXXGraph::Node<int> node2("2", 2);
  CXXGraph::Node<int> node3("3", 3);
  std::pair<const CXXGraph::Node<int> *, const CXXGraph::Node<int> *> pairNode(
      &node1, &node2);
  CXXGraph::DirectedWeightedEdge<int> edge1(1, pairNode, 5);
  CXXGraph::DirectedWeightedEdge<int> edge2(2, node2, node3, 4);
  CXXGraph::UndirectedWeightedEdge<int> edge3(3, node1, node3, 6);
  CXXGraph::T_EdgeSet<int> edgeSet;
  edgeSet.insert(make_shared<CXXGraph::DirectedWeightedEdge<int>>(edge1));
  edgeSet.insert(make_shared<CXXGraph::DirectedWeightedEdge<int>>(edge2));
  edgeSet.insert(make_shared<CXXGraph::UndirectedWeightedEdge<int>>(edge3));
  CXXGraph::Graph<int> graph(edgeSet);
  int res = graph.writeToFile(CXXGraph::InputOutputFormat::STANDARD_CSV);
  ASSERT_EQ(res, 0);
  ASSERT_TRUE(exists_test("graph.csv"));
  ASSERT_FALSE(exists_test("graph_NodeFeat.csv"));
  ASSERT_FALSE(exists_test("graph_EdgeWeight.csv"));

  remove("graph.csv");
  ASSERT_FALSE(exists_test("graph.csv"));
}

TEST(RWOutputTest, test_3) {
  CXXGraph::Node<int> node1("1", 1);
  CXXGraph::Node<int> node2("2", 2);
  CXXGraph::Node<int> node3("3", 3);
  std::pair<const CXXGraph::Node<int> *, const CXXGraph::Node<int> *> pairNode(
      &node1, &node2);
  CXXGraph::DirectedWeightedEdge<int> edge1(1, pairNode, 5);
  CXXGraph::DirectedEdge<int> edge2(2, node2, node3);
  CXXGraph::UndirectedWeightedEdge<int> edge3(3, node1, node3, 6);
  CXXGraph::T_EdgeSet<int> edgeSet;
  edgeSet.insert(make_shared<CXXGraph::DirectedWeightedEdge<int>>(edge1));
  edgeSet.insert(make_shared<CXXGraph::DirectedEdge<int>>(edge2));
  edgeSet.insert(make_shared<CXXGraph::UndirectedWeightedEdge<int>>(edge3));
  CXXGraph::Graph<int> graph(edgeSet);
  int res = graph.writeToFile(CXXGraph::InputOutputFormat::STANDARD_CSV, ".",
                              "test_3");
  ASSERT_EQ(res, 0);
  ASSERT_TRUE(exists_test("test_3.csv"));
  ASSERT_FALSE(exists_test("test_3_NodeFeat.csv"));
  ASSERT_FALSE(exists_test("test_3_EdgeWeight.csv"));

  remove("test_3.csv");
  ASSERT_FALSE(exists_test("test_3.csv"));
}

TEST(RWOutputTest, test_4) {
  CXXGraph::Node<int> node1("1", 1);
  CXXGraph::Node<int> node2("2", 2);
  CXXGraph::Node<int> node3("3", 3);
  CXXGraph::DirectedEdge<int> edge2(2, node2, node3);
  CXXGraph::UndirectedWeightedEdge<int> edge3(3, node1, node3, 6);
  CXXGraph::T_EdgeSet<int> edgeSet;
  edgeSet.insert(make_shared<CXXGraph::DirectedEdge<int>>(edge2));
  edgeSet.insert(make_shared<CXXGraph::UndirectedWeightedEdge<int>>(edge3));
  CXXGraph::Graph<int> graph(edgeSet);
  int res = graph.writeToFile(CXXGraph::InputOutputFormat::OUT_1, "test_4");
  ASSERT_EQ(res, -1);
  ASSERT_FALSE(exists_test("test_4.csv"));
  ASSERT_FALSE(exists_test("test_4_NodeFeat.csv"));
  ASSERT_FALSE(exists_test("test_4_EdgeWeight.csv"));
}

TEST(RWOutputTest, test_5) {
  CXXGraph::Node<int> node1("1", 1);
  CXXGraph::Node<int> node2("2", 2);
  CXXGraph::Node<int> node3("3", 3);
  CXXGraph::DirectedEdge<int> edge2(2, node2, node3);
  CXXGraph::UndirectedWeightedEdge<int> edge3(3, node1, node3, 6);
  CXXGraph::T_EdgeSet<int> edgeSet;
  edgeSet.insert(make_shared<CXXGraph::DirectedEdge<int>>(edge2));
  edgeSet.insert(make_shared<CXXGraph::UndirectedWeightedEdge<int>>(edge3));
  CXXGraph::Graph<int> graph(edgeSet);
  int res = graph.writeToFile(CXXGraph::InputOutputFormat::STANDARD_CSV, ".",
                              "test_5", false, true, true);
  ASSERT_EQ(res, 0);
  ASSERT_TRUE(exists_test("test_5.csv"));
  ASSERT_TRUE(exists_test("test_5_NodeFeat.csv"));
  ASSERT_TRUE(exists_test("test_5_EdgeWeight.csv"));

  remove("test_5.csv");
  remove("test_5_NodeFeat.csv");
  remove("test_5_EdgeWeight.csv");
  ASSERT_FALSE(exists_test("test_5.csv"));
  ASSERT_FALSE(exists_test("test_5_NodeFeat.csv"));
  ASSERT_FALSE(exists_test("test_5_EdgeWeight.csv"));
}

TEST(RWOutputTest, test_6) {
  CXXGraph::Node<int> node1("1", 1);
  CXXGraph::Node<int> node2("2", 2);
  CXXGraph::Node<int> node3("3", 3);
  CXXGraph::DirectedWeightedEdge<int> edge2(2, node2, node3, 1);
  CXXGraph::UndirectedWeightedEdge<int> edge3(3, node1, node3, 6);
  CXXGraph::T_EdgeSet<int> edgeSet;
  edgeSet.insert(make_shared<CXXGraph::DirectedWeightedEdge<int>>(edge2));
  edgeSet.insert(make_shared<CXXGraph::UndirectedWeightedEdge<int>>(edge3));
  CXXGraph::Graph<int> graph(edgeSet);
  int res = graph.writeToFile(CXXGraph::InputOutputFormat::STANDARD_CSV, ".",
                              "test_6", false, false, true);
  ASSERT_EQ(res, 0);
  ASSERT_TRUE(exists_test("test_6.csv"));
  ASSERT_FALSE(exists_test("test_6_NodeFeat.csv"));
  ASSERT_TRUE(exists_test("test_6_EdgeWeight.csv"));

  remove("test_6.csv");
  remove("test_6_EdgeWeight.csv");
  ASSERT_FALSE(exists_test("test_6.csv"));
  ASSERT_FALSE(exists_test("test_6_EdgeWeight.csv"));
}

TEST(RWOutputTest, test_7) {
  CXXGraph::Node<int> node1("1", 1);
  CXXGraph::Node<int> node2("2", 2);
  CXXGraph::Node<int> node3("3", 3);
  CXXGraph::DirectedWeightedEdge<int> edge2(2, node2, node3, 1);
  CXXGraph::UndirectedWeightedEdge<int> edge3(3, node1, node3, 6);
  CXXGraph::T_EdgeSet<int> edgeSet;
  edgeSet.insert(make_shared<CXXGraph::DirectedWeightedEdge<int>>(edge2));
  edgeSet.insert(make_shared<CXXGraph::UndirectedWeightedEdge<int>>(edge3));
  CXXGraph::Graph<int> graph(edgeSet);
  int res = graph.writeToFile(CXXGraph::InputOutputFormat::STANDARD_CSV, ".",
                              "test_7", false, true, false);
  ASSERT_EQ(res, 0);
  ASSERT_TRUE(exists_test("test_7.csv"));
  ASSERT_TRUE(exists_test("test_7_NodeFeat.csv"));
  ASSERT_FALSE(exists_test("test_7_EdgeWeight.csv"));

  remove("test_7.csv");
  remove("test_7_NodeFeat.csv");
  ASSERT_FALSE(exists_test("test_7.csv"));
  ASSERT_FALSE(exists_test("test_7_NodeFeat.csv"));
}

TEST(RWOutputTest, test_8) {
  CXXGraph::Node<int> node1("1", 1);
  CXXGraph::Node<int> node2("2", 2);
  CXXGraph::Node<int> node3("3", 3);
  std::pair<const CXXGraph::Node<int> *, const CXXGraph::Node<int> *> pairNode(
      &node1, &node2);
  CXXGraph::DirectedWeightedEdge<int> edge1(1, pairNode, 5);
  CXXGraph::DirectedEdge<int> edge2(2, node2, node3);
  CXXGraph::UndirectedWeightedEdge<int> edge3(3, node1, node3, 6);
  CXXGraph::T_EdgeSet<int> edgeSet;
  edgeSet.insert(make_shared<CXXGraph::DirectedWeightedEdge<int>>(edge1));
  edgeSet.insert(make_shared<CXXGraph::DirectedEdge<int>>(edge2));
  edgeSet.insert(make_shared<CXXGraph::UndirectedWeightedEdge<int>>(edge3));
  CXXGraph::Graph<int> graph(edgeSet);
  int res = graph.writeToFile(CXXGraph::InputOutputFormat::STANDARD_CSV, ".",
                              "test_8");
  ASSERT_EQ(res, 0);
  ASSERT_TRUE(exists_test("test_8.csv"));
  ASSERT_FALSE(exists_test("test_8_NodeFeat.csv"));
  ASSERT_FALSE(exists_test("test_8_EdgeWeight.csv"));

  CXXGraph::Graph<int> readGraph;
  readGraph.readFromFile(CXXGraph::InputOutputFormat::STANDARD_CSV, ".",
                         "test_8");
  auto readNode = readGraph.getNodeSet();
  auto readEdge = readGraph.getEdgeSet();
  ASSERT_EQ(readEdge.size(), 3);
  ASSERT_EQ(readNode.size(), 3);

  for (const auto &readEdgeIt : readEdge) {
    if (readEdgeIt->getId() == 1) {
      ASSERT_TRUE(readEdgeIt->isDirected().has_value() &&
                  readEdgeIt->isDirected().value());
      ASSERT_EQ(readEdgeIt->getNodePair().first->getUserId(),
                node1.getUserId());
      // ASSERT_EQ(readEdgeIt->getNodePair().first->getData(), node1.getData());
      ASSERT_EQ(readEdgeIt->getNodePair().second->getUserId(),
                node2.getUserId());
      // ASSERT_EQ(readEdgeIt->getNodePair().second->getData(),
      // node2.getData());
    } else if (readEdgeIt->getId() == 2) {
      ASSERT_TRUE(readEdgeIt->isDirected().has_value() &&
                  readEdgeIt->isDirected().value());
      ASSERT_EQ(readEdgeIt->getNodePair().first->getUserId(),
                node2.getUserId());
      // ASSERT_EQ(readEdgeIt->getNodePair().first->getData(), node2.getData());
      ASSERT_EQ(readEdgeIt->getNodePair().second->getUserId(),
                node3.getUserId());
      // ASSERT_EQ(readEdgeIt->getNodePair().second->getData(),
      // node3.getData());
    } else if (readEdgeIt->getId() == 3) {
      ASSERT_TRUE(readEdgeIt->isDirected().has_value() &&
                  !readEdgeIt->isDirected().value());
      ASSERT_EQ(readEdgeIt->getNodePair().first->getUserId(),
                node1.getUserId());
      // ASSERT_EQ(readEdgeIt->getNodePair().first->getData(), node1.getData());
      ASSERT_EQ(readEdgeIt->getNodePair().second->getUserId(),
                node3.getUserId());
      // ASSERT_EQ(readEdgeIt->getNodePair().second->getData(),
      // node3.getData());
    } else {
      ASSERT_TRUE(false);  // forced Error
    }
  }

  remove("test_8.csv");
  ASSERT_FALSE(exists_test("test_8.csv"));
}

TEST(RWOutputTest, test_9) {
  CXXGraph::Node<int> node1("1", 1);
  CXXGraph::Node<int> node2("2", 2);
  CXXGraph::Node<int> node3("3", 3);
  std::pair<const CXXGraph::Node<int> *, const CXXGraph::Node<int> *> pairNode(
      &node1, &node2);
  CXXGraph::DirectedWeightedEdge<int> edge1(1, pairNode, 5);
  CXXGraph::DirectedEdge<int> edge2(2, node2, node3);
  CXXGraph::UndirectedWeightedEdge<int> edge3(3, node1, node3, 6);
  CXXGraph::T_EdgeSet<int> edgeSet;
  edgeSet.insert(make_shared<CXXGraph::DirectedWeightedEdge<int>>(edge1));
  edgeSet.insert(make_shared<CXXGraph::DirectedEdge<int>>(edge2));
  edgeSet.insert(make_shared<CXXGraph::UndirectedWeightedEdge<int>>(edge3));
  CXXGraph::Graph<int> graph(edgeSet);
  int res = graph.writeToFile(CXXGraph::InputOutputFormat::STANDARD_CSV, ".",
                              "test_9", false, true);
  ASSERT_EQ(res, 0);
  ASSERT_TRUE(exists_test("test_9.csv"));
  ASSERT_TRUE(exists_test("test_9_NodeFeat.csv"));
  ASSERT_FALSE(exists_test("test_9_EdgeWeight.csv"));

  CXXGraph::Graph<int> readGraph;
  readGraph.readFromFile(CXXGraph::InputOutputFormat::STANDARD_CSV, ".",
                         "test_9", false, true);
  auto readNode = readGraph.getNodeSet();
  auto readEdge = readGraph.getEdgeSet();
  ASSERT_EQ(readEdge.size(), 3);
  ASSERT_EQ(readNode.size(), 3);

  for (const auto &readEdgeIt : readEdge) {
    if (readEdgeIt->getId() == 1) {
      ASSERT_TRUE(readEdgeIt->isDirected().has_value() &&
                  readEdgeIt->isDirected().value());
      ASSERT_EQ(readEdgeIt->getNodePair().first->getUserId(),
                node1.getUserId());
      ASSERT_EQ(readEdgeIt->getNodePair().first->getData(), node1.getData());
      ASSERT_EQ(readEdgeIt->getNodePair().second->getUserId(),
                node2.getUserId());
      ASSERT_EQ(readEdgeIt->getNodePair().second->getData(), node2.getData());
    } else if (readEdgeIt->getId() == 2) {
      ASSERT_TRUE(readEdgeIt->isDirected().has_value() &&
                  readEdgeIt->isDirected().value());
      ASSERT_EQ(readEdgeIt->getNodePair().first->getUserId(),
                node2.getUserId());
      ASSERT_EQ(readEdgeIt->getNodePair().first->getData(), node2.getData());
      ASSERT_EQ(readEdgeIt->getNodePair().second->getUserId(),
                node3.getUserId());
      ASSERT_EQ(readEdgeIt->getNodePair().second->getData(), node3.getData());
    } else if (readEdgeIt->getId() == 3) {
      ASSERT_TRUE(readEdgeIt->isDirected().has_value() &&
                  !readEdgeIt->isDirected().value());
      ASSERT_EQ(readEdgeIt->getNodePair().first->getUserId(),
                node1.getUserId());
      ASSERT_EQ(readEdgeIt->getNodePair().first->getData(), node1.getData());
      ASSERT_EQ(readEdgeIt->getNodePair().second->getUserId(),
                node3.getUserId());
      ASSERT_EQ(readEdgeIt->getNodePair().second->getData(), node3.getData());
    } else {
      ASSERT_TRUE(false);  // forced Error
    }
  }

  remove("test_9.csv");
  remove("test_9_NodeFeat.csv");
  ASSERT_FALSE(exists_test("test_9.csv"));
  ASSERT_FALSE(exists_test("test_9_NodeFeat.csv"));
}

TEST(RWOutputTest, test_10) {
  CXXGraph::Node<int> node1("1", 1);
  CXXGraph::Node<int> node2("2", 2);
  CXXGraph::Node<int> node3("3", 3);
  std::pair<const CXXGraph::Node<int> *, const CXXGraph::Node<int> *> pairNode(
      &node1, &node2);
  CXXGraph::DirectedWeightedEdge<int> edge1(1, pairNode, 5);
  CXXGraph::DirectedEdge<int> edge2(2, node2, node3);
  CXXGraph::UndirectedWeightedEdge<int> edge3(3, node1, node3, 6);
  CXXGraph::T_EdgeSet<int> edgeSet;
  edgeSet.insert(make_shared<CXXGraph::DirectedWeightedEdge<int>>(edge1));
  edgeSet.insert(make_shared<CXXGraph::DirectedEdge<int>>(edge2));
  edgeSet.insert(make_shared<CXXGraph::UndirectedWeightedEdge<int>>(edge3));
  CXXGraph::Graph<int> graph(edgeSet);
  int res = graph.writeToFile(CXXGraph::InputOutputFormat::STANDARD_CSV, ".",
                              "test_10", false, true, true);
  ASSERT_EQ(res, 0);
  ASSERT_TRUE(exists_test("test_10.csv"));
  ASSERT_TRUE(exists_test("test_10_NodeFeat.csv"));
  ASSERT_TRUE(exists_test("test_10_EdgeWeight.csv"));

  CXXGraph::Graph<int> readGraph;
  readGraph.readFromFile(CXXGraph::InputOutputFormat::STANDARD_CSV, ".",
                         "test_10", false, true, true);
  auto readNode = readGraph.getNodeSet();
  auto readEdge = readGraph.getEdgeSet();
  ASSERT_EQ(readEdge.size(), 3);
  ASSERT_EQ(readNode.size(), 3);

  for (const auto &readEdgeIt : readEdge) {
    if (readEdgeIt->getId() == 1) {
      ASSERT_TRUE(readEdgeIt->isDirected().has_value() &&
                  readEdgeIt->isDirected().value());
      ASSERT_TRUE(readEdgeIt->isWeighted().has_value() &&
                  readEdgeIt->isWeighted().value());
      ASSERT_EQ((dynamic_cast<const CXXGraph::Weighted *>(readEdgeIt.get()))
                    ->getWeight(),
                5);
      ASSERT_EQ(readEdgeIt->getNodePair().first->getUserId(),
                node1.getUserId());
      ASSERT_EQ(readEdgeIt->getNodePair().first->getData(), node1.getData());
      ASSERT_EQ(readEdgeIt->getNodePair().second->getUserId(),
                node2.getUserId());
      ASSERT_EQ(readEdgeIt->getNodePair().second->getData(), node2.getData());
    } else if (readEdgeIt->getId() == 2) {
      ASSERT_TRUE(readEdgeIt->isDirected().has_value() &&
                  readEdgeIt->isDirected().value());
      ASSERT_TRUE(readEdgeIt->isWeighted().has_value() &&
                  !readEdgeIt->isWeighted().value());
      ASSERT_EQ(readEdgeIt->getNodePair().first->getUserId(),
                node2.getUserId());
      ASSERT_EQ(readEdgeIt->getNodePair().first->getData(), node2.getData());
      ASSERT_EQ(readEdgeIt->getNodePair().second->getUserId(),
                node3.getUserId());
      ASSERT_EQ(readEdgeIt->getNodePair().second->getData(), node3.getData());
    } else if (readEdgeIt->getId() == 3) {
      ASSERT_TRUE(readEdgeIt->isDirected().has_value() &&
                  !readEdgeIt->isDirected().value());
      ASSERT_TRUE(readEdgeIt->isWeighted().has_value() &&
                  readEdgeIt->isWeighted().value());
      ASSERT_EQ((dynamic_cast<const CXXGraph::Weighted *>(readEdgeIt.get()))
                    ->getWeight(),
                6);
      ASSERT_EQ(readEdgeIt->getNodePair().first->getUserId(),
                node1.getUserId());
      ASSERT_EQ(readEdgeIt->getNodePair().first->getData(), node1.getData());
      ASSERT_EQ(readEdgeIt->getNodePair().second->getUserId(),
                node3.getUserId());
      ASSERT_EQ(readEdgeIt->getNodePair().second->getData(), node3.getData());
    } else {
      ASSERT_TRUE(false);  // forced Error
    }
  }

  remove("test_10.csv");
  remove("test_10_NodeFeat.csv");
  remove("test_10_EdgeWeight.csv");
  ASSERT_FALSE(exists_test("test_10.csv"));
  ASSERT_FALSE(exists_test("test_10_NodeFeat.csv"));
  ASSERT_FALSE(exists_test("test_10_EdgeWeight.csv"));
}

//************* TSV ***************//

TEST(RWOutputTest, test_11) {
  CXXGraph::Node<int> node1("1", 1);
  CXXGraph::Node<int> node2("2", 2);
  CXXGraph::Node<int> node3("3", 3);
  std::pair<const CXXGraph::Node<int> *, const CXXGraph::Node<int> *> pairNode(
      &node1, &node2);
  CXXGraph::DirectedWeightedEdge<int> edge1(1, pairNode, 1);
  CXXGraph::DirectedWeightedEdge<int> edge2(2, node2, node3, 1);
  CXXGraph::UndirectedWeightedEdge<int> edge3(3, node1, node3, 6);
  CXXGraph::T_EdgeSet<int> edgeSet;
  edgeSet.insert(make_shared<CXXGraph::DirectedWeightedEdge<int>>(edge1));
  edgeSet.insert(make_shared<CXXGraph::DirectedWeightedEdge<int>>(edge2));
  edgeSet.insert(make_shared<CXXGraph::UndirectedWeightedEdge<int>>(edge3));
  CXXGraph::Graph<int> graph(edgeSet);
  int res = graph.writeToFile();
  ASSERT_EQ(res, 0);
  ASSERT_FALSE(exists_test("graph.tsv"));
  ASSERT_TRUE(exists_test("graph.csv"));
  ASSERT_FALSE(exists_test("graph_NodeFeat.tsv"));
  ASSERT_FALSE(exists_test("graph_EdgeWeight.tsv"));

  remove("graph.csv");
  ASSERT_FALSE(exists_test("graph.csv"));
}

TEST(RWOutputTest, test_12) {
  CXXGraph::Node<int> node1("1", 1);
  CXXGraph::Node<int> node2("2", 2);
  CXXGraph::Node<int> node3("3", 3);
  std::pair<const CXXGraph::Node<int> *, const CXXGraph::Node<int> *> pairNode(
      &node1, &node2);
  CXXGraph::DirectedWeightedEdge<int> edge1(1, pairNode, 5);
  CXXGraph::DirectedWeightedEdge<int> edge2(2, node2, node3, 4);
  CXXGraph::UndirectedWeightedEdge<int> edge3(3, node1, node3, 6);
  CXXGraph::T_EdgeSet<int> edgeSet;
  edgeSet.insert(make_shared<CXXGraph::DirectedWeightedEdge<int>>(edge1));
  edgeSet.insert(make_shared<CXXGraph::DirectedWeightedEdge<int>>(edge2));
  edgeSet.insert(make_shared<CXXGraph::UndirectedWeightedEdge<int>>(edge3));
  CXXGraph::Graph<int> graph(edgeSet);
  int res = graph.writeToFile(CXXGraph::InputOutputFormat::STANDARD_TSV);
  ASSERT_EQ(res, 0);
  ASSERT_TRUE(exists_test("graph.tsv"));
  ASSERT_FALSE(exists_test("graph_NodeFeat.tsv"));
  ASSERT_FALSE(exists_test("graph_EdgeWeight.tsv"));

  remove("graph.tsv");
  ASSERT_FALSE(exists_test("graph.tsv"));
}

TEST(RWOutputTest, test_13) {
  CXXGraph::Node<int> node1("1", 1);
  CXXGraph::Node<int> node2("2", 2);
  CXXGraph::Node<int> node3("3", 3);
  std::pair<const CXXGraph::Node<int> *, const CXXGraph::Node<int> *> pairNode(
      &node1, &node2);
  CXXGraph::DirectedWeightedEdge<int> edge1(1, pairNode, 5);
  CXXGraph::DirectedEdge<int> edge2(2, node2, node3);
  CXXGraph::UndirectedWeightedEdge<int> edge3(3, node1, node3, 6);
  CXXGraph::T_EdgeSet<int> edgeSet;
  edgeSet.insert(make_shared<CXXGraph::DirectedWeightedEdge<int>>(edge1));
  edgeSet.insert(make_shared<CXXGraph::DirectedEdge<int>>(edge2));
  edgeSet.insert(make_shared<CXXGraph::UndirectedWeightedEdge<int>>(edge3));
  CXXGraph::Graph<int> graph(edgeSet);
  int res = graph.writeToFile(CXXGraph::InputOutputFormat::STANDARD_TSV, ".",
                              "test_13");
  ASSERT_EQ(res, 0);
  ASSERT_TRUE(exists_test("test_13.tsv"));
  ASSERT_FALSE(exists_test("test_13_NodeFeat.tsv"));
  ASSERT_FALSE(exists_test("test_13_EdgeWeight.tsv"));

  remove("test_13.tsv");
  ASSERT_FALSE(exists_test("test_13.tsv"));
}

TEST(RWOutputTest, test_14) {
  CXXGraph::Node<int> node1("1", 1);
  CXXGraph::Node<int> node2("2", 2);
  CXXGraph::Node<int> node3("3", 3);
  CXXGraph::DirectedEdge<int> edge2(2, node2, node3);
  CXXGraph::UndirectedWeightedEdge<int> edge3(3, node1, node3, 6);
  CXXGraph::T_EdgeSet<int> edgeSet;
  edgeSet.insert(make_shared<CXXGraph::DirectedEdge<int>>(edge2));
  edgeSet.insert(make_shared<CXXGraph::UndirectedWeightedEdge<int>>(edge3));
  CXXGraph::Graph<int> graph(edgeSet);
  int res = graph.writeToFile(CXXGraph::InputOutputFormat::OUT_1, "test_14");
  ASSERT_EQ(res, -1);
  ASSERT_FALSE(exists_test("test_14.tsv"));
  ASSERT_FALSE(exists_test("test_14_NodeFeat.tsv"));
  ASSERT_FALSE(exists_test("test_14_EdgeWeight.tsv"));
}

TEST(RWOutputTest, test_15) {
  CXXGraph::Node<int> node1("1", 1);
  CXXGraph::Node<int> node2("2", 2);
  CXXGraph::Node<int> node3("3", 3);
  CXXGraph::DirectedEdge<int> edge2(2, node2, node3);
  CXXGraph::UndirectedWeightedEdge<int> edge3(3, node1, node3, 6);
  CXXGraph::T_EdgeSet<int> edgeSet;
  edgeSet.insert(make_shared<CXXGraph::DirectedEdge<int>>(edge2));
  edgeSet.insert(make_shared<CXXGraph::UndirectedWeightedEdge<int>>(edge3));
  CXXGraph::Graph<int> graph(edgeSet);
  int res = graph.writeToFile(CXXGraph::InputOutputFormat::STANDARD_TSV, ".",
                              "test_15", false, true, true);
  ASSERT_EQ(res, 0);
  ASSERT_TRUE(exists_test("test_15.tsv"));
  ASSERT_TRUE(exists_test("test_15_NodeFeat.tsv"));
  ASSERT_TRUE(exists_test("test_15_EdgeWeight.tsv"));

  remove("test_15.tsv");
  remove("test_15_NodeFeat.tsv");
  remove("test_15_EdgeWeight.tsv");
  ASSERT_FALSE(exists_test("test_15.tsv"));
  ASSERT_FALSE(exists_test("test_15_NodeFeat.tsv"));
  ASSERT_FALSE(exists_test("test_15_EdgeWeight.tsv"));
}

TEST(RWOutputTest, test_16) {
  CXXGraph::Node<int> node1("1", 1);
  CXXGraph::Node<int> node2("2", 2);
  CXXGraph::Node<int> node3("3", 3);
  CXXGraph::DirectedWeightedEdge<int> edge2(2, node2, node3, 1);
  CXXGraph::UndirectedWeightedEdge<int> edge3(3, node1, node3, 6);
  CXXGraph::T_EdgeSet<int> edgeSet;
  edgeSet.insert(make_shared<CXXGraph::DirectedWeightedEdge<int>>(edge2));
  edgeSet.insert(make_shared<CXXGraph::UndirectedWeightedEdge<int>>(edge3));
  CXXGraph::Graph<int> graph(edgeSet);
  int res = graph.writeToFile(CXXGraph::InputOutputFormat::STANDARD_TSV, ".",
                              "test_16", false, false, true);
  ASSERT_EQ(res, 0);
  ASSERT_TRUE(exists_test("test_16.tsv"));
  ASSERT_FALSE(exists_test("test_16_NodeFeat.tsv"));
  ASSERT_TRUE(exists_test("test_16_EdgeWeight.tsv"));

  remove("test_16.tsv");
  remove("test_16_EdgeWeight.tsv");
  ASSERT_FALSE(exists_test("test_16.tsv"));
  ASSERT_FALSE(exists_test("test_16_EdgeWeight.tsv"));
}

TEST(RWOutputTest, test_17) {
  CXXGraph::Node<int> node1("1", 1);
  CXXGraph::Node<int> node2("2", 2);
  CXXGraph::Node<int> node3("3", 3);
  CXXGraph::DirectedWeightedEdge<int> edge2(2, node2, node3, 1);
  CXXGraph::UndirectedWeightedEdge<int> edge3(3, node1, node3, 6);
  CXXGraph::T_EdgeSet<int> edgeSet;
  edgeSet.insert(make_shared<CXXGraph::DirectedWeightedEdge<int>>(edge2));
  edgeSet.insert(make_shared<CXXGraph::UndirectedWeightedEdge<int>>(edge3));
  CXXGraph::Graph<int> graph(edgeSet);
  int res = graph.writeToFile(CXXGraph::InputOutputFormat::STANDARD_TSV, ".",
                              "test_17", false, true, false);
  ASSERT_EQ(res, 0);
  ASSERT_TRUE(exists_test("test_17.tsv"));
  ASSERT_TRUE(exists_test("test_17_NodeFeat.tsv"));
  ASSERT_FALSE(exists_test("test_17_EdgeWeight.tsv"));

  remove("test_17.tsv");
  remove("test_17_NodeFeat.tsv");
  ASSERT_FALSE(exists_test("test_17.tsv"));
  ASSERT_FALSE(exists_test("test_17_NodeFeat.tsv"));
}

TEST(RWOutputTest, test_18) {
  CXXGraph::Node<int> node1("1", 1);
  CXXGraph::Node<int> node2("2", 2);
  CXXGraph::Node<int> node3("3", 3);
  std::pair<const CXXGraph::Node<int> *, const CXXGraph::Node<int> *> pairNode(
      &node1, &node2);
  CXXGraph::DirectedWeightedEdge<int> edge1(1, pairNode, 5);
  CXXGraph::DirectedEdge<int> edge2(2, node2, node3);
  CXXGraph::UndirectedWeightedEdge<int> edge3(3, node1, node3, 6);
  CXXGraph::T_EdgeSet<int> edgeSet;
  edgeSet.insert(make_shared<CXXGraph::DirectedWeightedEdge<int>>(edge1));
  edgeSet.insert(make_shared<CXXGraph::DirectedEdge<int>>(edge2));
  edgeSet.insert(make_shared<CXXGraph::UndirectedWeightedEdge<int>>(edge3));
  CXXGraph::Graph<int> graph(edgeSet);
  int res = graph.writeToFile(CXXGraph::InputOutputFormat::STANDARD_TSV, ".",
                              "test_18");
  ASSERT_EQ(res, 0);
  ASSERT_TRUE(exists_test("test_18.tsv"));
  ASSERT_FALSE(exists_test("test_18_NodeFeat.tsv"));
  ASSERT_FALSE(exists_test("test_18_EdgeWeight.tsv"));

  CXXGraph::Graph<int> readGraph;
  readGraph.readFromFile(CXXGraph::InputOutputFormat::STANDARD_TSV, ".",
                         "test_18");
  auto readNode = readGraph.getNodeSet();
  auto readEdge = readGraph.getEdgeSet();
  ASSERT_EQ(readEdge.size(), 3);
  ASSERT_EQ(readNode.size(), 3);

  for (const auto &readEdgeIt : readEdge) {
    if (readEdgeIt->getId() == 1) {
      ASSERT_TRUE(readEdgeIt->isDirected().has_value() &&
                  readEdgeIt->isDirected().value());
      ASSERT_EQ(readEdgeIt->getNodePair().first->getUserId(),
                node1.getUserId());
      // ASSERT_EQ(readEdgeIt->getNodePair().first->getData(), node1.getData());
      ASSERT_EQ(readEdgeIt->getNodePair().second->getUserId(),
                node2.getUserId());
      // ASSERT_EQ(readEdgeIt->getNodePair().second->getData(),
      // node2.getData());
    } else if (readEdgeIt->getId() == 2) {
      ASSERT_TRUE(readEdgeIt->isDirected().has_value() &&
                  readEdgeIt->isDirected().value());
      ASSERT_EQ(readEdgeIt->getNodePair().first->getUserId(),
                node2.getUserId());
      // ASSERT_EQ(readEdgeIt->getNodePair().first->getData(), node2.getData());
      ASSERT_EQ(readEdgeIt->getNodePair().second->getUserId(),
                node3.getUserId());
      // ASSERT_EQ(readEdgeIt->getNodePair().second->getData(),
      // node3.getData());
    } else if (readEdgeIt->getId() == 3) {
      ASSERT_TRUE(readEdgeIt->isDirected().has_value() &&
                  !readEdgeIt->isDirected().value());
      ASSERT_EQ(readEdgeIt->getNodePair().first->getUserId(),
                node1.getUserId());
      // ASSERT_EQ(readEdgeIt->getNodePair().first->getData(), node1.getData());
      ASSERT_EQ(readEdgeIt->getNodePair().second->getUserId(),
                node3.getUserId());
      // ASSERT_EQ(readEdgeIt->getNodePair().second->getData(),
      // node3.getData());
    } else {
      ASSERT_TRUE(false);  // forced Error
    }
  }

  remove("test_18.tsv");
  ASSERT_FALSE(exists_test("test_18.tsv"));
}

TEST(RWOutputTest, test_19) {
  CXXGraph::Node<int> node1("1", 1);
  CXXGraph::Node<int> node2("2", 2);
  CXXGraph::Node<int> node3("3", 3);
  std::pair<const CXXGraph::Node<int> *, const CXXGraph::Node<int> *> pairNode(
      &node1, &node2);
  CXXGraph::DirectedWeightedEdge<int> edge1(1, pairNode, 5);
  CXXGraph::DirectedEdge<int> edge2(2, node2, node3);
  CXXGraph::UndirectedWeightedEdge<int> edge3(3, node1, node3, 6);
  CXXGraph::T_EdgeSet<int> edgeSet;
  edgeSet.insert(make_shared<CXXGraph::DirectedWeightedEdge<int>>(edge1));
  edgeSet.insert(make_shared<CXXGraph::DirectedEdge<int>>(edge2));
  edgeSet.insert(make_shared<CXXGraph::UndirectedWeightedEdge<int>>(edge3));
  CXXGraph::Graph<int> graph(edgeSet);
  int res = graph.writeToFile(CXXGraph::InputOutputFormat::STANDARD_TSV, ".",
                              "test_19", false, true);
  ASSERT_EQ(res, 0);
  ASSERT_TRUE(exists_test("test_19.tsv"));
  ASSERT_TRUE(exists_test("test_19_NodeFeat.tsv"));
  ASSERT_FALSE(exists_test("test_19_EdgeWeight.tsv"));

  CXXGraph::Graph<int> readGraph;
  readGraph.readFromFile(CXXGraph::InputOutputFormat::STANDARD_TSV, ".",
                         "test_19", false, true);
  auto readNode = readGraph.getNodeSet();
  auto readEdge = readGraph.getEdgeSet();
  ASSERT_EQ(readEdge.size(), 3);
  ASSERT_EQ(readNode.size(), 3);

  for (const auto &readEdgeIt : readEdge) {
    if (readEdgeIt->getId() == 1) {
      ASSERT_TRUE(readEdgeIt->isDirected().has_value() &&
                  readEdgeIt->isDirected().value());
      ASSERT_EQ(readEdgeIt->getNodePair().first->getUserId(),
                node1.getUserId());
      ASSERT_EQ(readEdgeIt->getNodePair().first->getData(), node1.getData());
      ASSERT_EQ(readEdgeIt->getNodePair().second->getUserId(),
                node2.getUserId());
      ASSERT_EQ(readEdgeIt->getNodePair().second->getData(), node2.getData());
    } else if (readEdgeIt->getId() == 2) {
      ASSERT_TRUE(readEdgeIt->isDirected().has_value() &&
                  readEdgeIt->isDirected().value());
      ASSERT_EQ(readEdgeIt->getNodePair().first->getUserId(),
                node2.getUserId());
      ASSERT_EQ(readEdgeIt->getNodePair().first->getData(), node2.getData());
      ASSERT_EQ(readEdgeIt->getNodePair().second->getUserId(),
                node3.getUserId());
      ASSERT_EQ(readEdgeIt->getNodePair().second->getData(), node3.getData());
    } else if (readEdgeIt->getId() == 3) {
      ASSERT_TRUE(readEdgeIt->isDirected().has_value() &&
                  !readEdgeIt->isDirected().value());
      ASSERT_EQ(readEdgeIt->getNodePair().first->getUserId(),
                node1.getUserId());
      ASSERT_EQ(readEdgeIt->getNodePair().first->getData(), node1.getData());
      ASSERT_EQ(readEdgeIt->getNodePair().second->getUserId(),
                node3.getUserId());
      ASSERT_EQ(readEdgeIt->getNodePair().second->getData(), node3.getData());
    } else {
      ASSERT_TRUE(false);  // forced Error
    }
  }

  remove("test_19.tsv");
  remove("test_19_NodeFeat.tsv");
  ASSERT_FALSE(exists_test("test_19.tsv"));
  ASSERT_FALSE(exists_test("test_19_NodeFeat.tsv"));
}

TEST(RWOutputTest, test_20) {
  CXXGraph::Node<int> node1("1", 1);
  CXXGraph::Node<int> node2("2", 2);
  CXXGraph::Node<int> node3("3", 3);
  std::pair<const CXXGraph::Node<int> *, const CXXGraph::Node<int> *> pairNode(
      &node1, &node2);
  CXXGraph::DirectedWeightedEdge<int> edge1(1, pairNode, 5);
  CXXGraph::DirectedEdge<int> edge2(2, node2, node3);
  CXXGraph::UndirectedWeightedEdge<int> edge3(3, node1, node3, 6);
  CXXGraph::T_EdgeSet<int> edgeSet;
  edgeSet.insert(make_shared<CXXGraph::DirectedWeightedEdge<int>>(edge1));
  edgeSet.insert(make_shared<CXXGraph::DirectedEdge<int>>(edge2));
  edgeSet.insert(make_shared<CXXGraph::UndirectedWeightedEdge<int>>(edge3));
  CXXGraph::Graph<int> graph(edgeSet);
  int res = graph.writeToFile(CXXGraph::InputOutputFormat::STANDARD_TSV, ".",
                              "test_20", false, true, true);
  ASSERT_EQ(res, 0);
  ASSERT_TRUE(exists_test("test_20.tsv"));
  ASSERT_TRUE(exists_test("test_20_NodeFeat.tsv"));
  ASSERT_TRUE(exists_test("test_20_EdgeWeight.tsv"));

  CXXGraph::Graph<int> readGraph;
  readGraph.readFromFile(CXXGraph::InputOutputFormat::STANDARD_TSV, ".",
                         "test_20", false, true, true);
  auto readNode = readGraph.getNodeSet();
  auto readEdge = readGraph.getEdgeSet();
  ASSERT_EQ(readEdge.size(), 3);
  ASSERT_EQ(readNode.size(), 3);

  for (const auto &readEdgeIt : readEdge) {
    if (readEdgeIt->getId() == 1) {
      ASSERT_TRUE(readEdgeIt->isDirected().has_value() &&
                  readEdgeIt->isDirected().value());
      ASSERT_TRUE(readEdgeIt->isWeighted().has_value() &&
                  readEdgeIt->isWeighted().value());
      ASSERT_EQ((dynamic_cast<const CXXGraph::Weighted *>(readEdgeIt.get()))
                    ->getWeight(),
                5);
      ASSERT_EQ(readEdgeIt->getNodePair().first->getUserId(),
                node1.getUserId());
      ASSERT_EQ(readEdgeIt->getNodePair().first->getData(), node1.getData());
      ASSERT_EQ(readEdgeIt->getNodePair().second->getUserId(),
                node2.getUserId());
      ASSERT_EQ(readEdgeIt->getNodePair().second->getData(), node2.getData());
    } else if (readEdgeIt->getId() == 2) {
      ASSERT_TRUE(readEdgeIt->isDirected().has_value() &&
                  readEdgeIt->isDirected().value());
      ASSERT_TRUE(readEdgeIt->isWeighted().has_value() &&
                  !readEdgeIt->isWeighted().value());
      ASSERT_EQ(readEdgeIt->getNodePair().first->getUserId(),
                node2.getUserId());
      ASSERT_EQ(readEdgeIt->getNodePair().first->getData(), node2.getData());
      ASSERT_EQ(readEdgeIt->getNodePair().second->getUserId(),
                node3.getUserId());
      ASSERT_EQ(readEdgeIt->getNodePair().second->getData(), node3.getData());
    } else if (readEdgeIt->getId() == 3) {
      ASSERT_TRUE(readEdgeIt->isDirected().has_value() &&
                  !readEdgeIt->isDirected().value());
      ASSERT_TRUE(readEdgeIt->isWeighted().has_value() &&
                  readEdgeIt->isWeighted().value());
      ASSERT_EQ((dynamic_cast<const CXXGraph::Weighted *>(readEdgeIt.get()))
                    ->getWeight(),
                6);
      ASSERT_EQ(readEdgeIt->getNodePair().first->getUserId(),
                node1.getUserId());
      ASSERT_EQ(readEdgeIt->getNodePair().first->getData(), node1.getData());
      ASSERT_EQ(readEdgeIt->getNodePair().second->getUserId(),
                node3.getUserId());
      ASSERT_EQ(readEdgeIt->getNodePair().second->getData(), node3.getData());
    } else {
      ASSERT_TRUE(false);  // forced Error
    }
  }

  remove("test_20.tsv");
  remove("test_20_NodeFeat.tsv");
  remove("test_20_EdgeWeight.tsv");
  ASSERT_FALSE(exists_test("test_20.tsv"));
  ASSERT_FALSE(exists_test("test_20_NodeFeat.tsv"));
  ASSERT_FALSE(exists_test("test_20_EdgeWeight.tsv"));
}

TEST(RWOutputTest, test_21) {
  CXXGraph::Node<int> node1("1", 1);
  CXXGraph::Node<int> node2("2", 2);
  CXXGraph::Node<int> node3("3", 3);
  CXXGraph::DirectedWeightedEdge<int> edge2(2, node2, node3, 1);
  CXXGraph::UndirectedWeightedEdge<int> edge3(3, node1, node3, 6);
  CXXGraph::T_EdgeSet<int> edgeSet;
  edgeSet.insert(make_shared<CXXGraph::DirectedWeightedEdge<int>>(edge2));
  edgeSet.insert(make_shared<CXXGraph::UndirectedWeightedEdge<int>>(edge3));
  CXXGraph::Graph<int> graph(edgeSet);
  int res = graph.writeToFile(CXXGraph::InputOutputFormat::STANDARD_CSV, ".",
                              "test_21", true, true, false);
  ASSERT_EQ(res, 0);
  ASSERT_FALSE(exists_test("test_21.csv"));
  ASSERT_FALSE(exists_test("test_21_NodeFeat.csv"));
  ASSERT_FALSE(exists_test("test_21_EdgeWeight.csv"));
  ASSERT_TRUE(exists_test("test_21.csv.gz"));
  ASSERT_TRUE(exists_test("test_21_NodeFeat.csv.gz"));
  ASSERT_FALSE(exists_test("test_21_EdgeWeight.csv.gz"));

  remove("test_21.csv.gz");
  remove("test_21_NodeFeat.csv.gz");
  ASSERT_FALSE(exists_test("test_21.csv.gz"));
  ASSERT_FALSE(exists_test("test_21_NodeFeat.csv.gz"));
}

TEST(RWOutputTest, test_22) {
  CXXGraph::Node<int> node1("1", 1);
  CXXGraph::Node<int> node2("2", 2);
  CXXGraph::Node<int> node3("3", 3);
  std::pair<const CXXGraph::Node<int> *, const CXXGraph::Node<int> *> pairNode(
      &node1, &node2);
  CXXGraph::DirectedWeightedEdge<int> edge1(1, pairNode, 5);
  CXXGraph::DirectedEdge<int> edge2(2, node2, node3);
  CXXGraph::UndirectedWeightedEdge<int> edge3(3, node1, node3, 6);
  CXXGraph::T_EdgeSet<int> edgeSet;
  edgeSet.insert(make_shared<CXXGraph::DirectedWeightedEdge<int>>(edge1));
  edgeSet.insert(make_shared<CXXGraph::DirectedEdge<int>>(edge2));
  edgeSet.insert(make_shared<CXXGraph::UndirectedWeightedEdge<int>>(edge3));
  CXXGraph::Graph<int> graph(edgeSet);
  int res = graph.writeToFile(CXXGraph::InputOutputFormat::STANDARD_CSV, ".",
                              "test_22", true, true, true);
  ASSERT_EQ(res, 0);
  ASSERT_FALSE(exists_test("test_22.csv"));
  ASSERT_FALSE(exists_test("test_22_NodeFeat.csv"));
  ASSERT_FALSE(exists_test("test_22_EdgeWeight.csv"));
  ASSERT_TRUE(exists_test("test_22.csv.gz"));
  ASSERT_TRUE(exists_test("test_22_NodeFeat.csv.gz"));
  ASSERT_TRUE(exists_test("test_22_EdgeWeight.csv.gz"));

  CXXGraph::Graph<int> readGraph;
  auto readResult =
      readGraph.readFromFile(CXXGraph::InputOutputFormat::STANDARD_CSV, ".",
                             "test_22", true, true, true);
  ASSERT_EQ(readResult, 0);
  auto readNode = readGraph.getNodeSet();
  auto readEdge = readGraph.getEdgeSet();
  ASSERT_EQ(readEdge.size(), 3);
  ASSERT_EQ(readNode.size(), 3);

  for (const auto &readEdgeIt : readEdge) {
    if (readEdgeIt->getId() == 1) {
      ASSERT_TRUE(readEdgeIt->isDirected().has_value() &&
                  readEdgeIt->isDirected().value());
      ASSERT_TRUE(readEdgeIt->isWeighted().has_value() &&
                  readEdgeIt->isWeighted().value());
      ASSERT_EQ((dynamic_cast<const CXXGraph::Weighted *>(readEdgeIt.get()))
                    ->getWeight(),
                5);
      ASSERT_EQ(readEdgeIt->getNodePair().first->getUserId(),
                node1.getUserId());
      ASSERT_EQ(readEdgeIt->getNodePair().first->getData(), node1.getData());
      ASSERT_EQ(readEdgeIt->getNodePair().second->getUserId(),
                node2.getUserId());
      ASSERT_EQ(readEdgeIt->getNodePair().second->getData(), node2.getData());
    } else if (readEdgeIt->getId() == 2) {
      ASSERT_TRUE(readEdgeIt->isDirected().has_value() &&
                  readEdgeIt->isDirected().value());
      ASSERT_TRUE(readEdgeIt->isWeighted().has_value() &&
                  !readEdgeIt->isWeighted().value());
      ASSERT_EQ(readEdgeIt->getNodePair().first->getUserId(),
                node2.getUserId());
      ASSERT_EQ(readEdgeIt->getNodePair().first->getData(), node2.getData());
      ASSERT_EQ(readEdgeIt->getNodePair().second->getUserId(),
                node3.getUserId());
      ASSERT_EQ(readEdgeIt->getNodePair().second->getData(), node3.getData());
    } else if (readEdgeIt->getId() == 3) {
      ASSERT_TRUE(readEdgeIt->isDirected().has_value() &&
                  !readEdgeIt->isDirected().value());
      ASSERT_TRUE(readEdgeIt->isWeighted().has_value() &&
                  readEdgeIt->isWeighted().value());
      ASSERT_EQ((dynamic_cast<const CXXGraph::Weighted *>(readEdgeIt.get()))
                    ->getWeight(),
                6);
      ASSERT_EQ(readEdgeIt->getNodePair().first->getUserId(),
                node1.getUserId());
      ASSERT_EQ(readEdgeIt->getNodePair().first->getData(), node1.getData());
      ASSERT_EQ(readEdgeIt->getNodePair().second->getUserId(),
                node3.getUserId());
      ASSERT_EQ(readEdgeIt->getNodePair().second->getData(), node3.getData());
    } else {
      ASSERT_TRUE(false);  // forced Error
    }
  }

  remove("test_22.csv.gz");
  remove("test_22_NodeFeat.csv.gz");
  remove("test_22_EdgeWeight.csv.gz");
  ASSERT_FALSE(exists_test("test_22.csv"));
  ASSERT_FALSE(exists_test("test_22_NodeFeat.csv"));
  ASSERT_FALSE(exists_test("test_22_EdgeWeight.csv"));
  ASSERT_FALSE(exists_test("test_22.csv.gz"));
  ASSERT_FALSE(exists_test("test_22_NodeFeat.csv.gz"));
  ASSERT_FALSE(exists_test("test_22_EdgeWeight.csv.gz"));
}

TEST(RWOutputTest, test_23) {
  CXXGraph::Node<int> node1("1", 1);
  CXXGraph::Node<int> node2("2", 2);
  CXXGraph::Node<int> node3("3", 3);
  CXXGraph::DirectedWeightedEdge<int> edge2(2, node2, node3, 1);
  CXXGraph::UndirectedWeightedEdge<int> edge3(3, node1, node3, 6);
  CXXGraph::T_EdgeSet<int> edgeSet;
  edgeSet.insert(make_shared<CXXGraph::DirectedWeightedEdge<int>>(edge2));
  edgeSet.insert(make_shared<CXXGraph::UndirectedWeightedEdge<int>>(edge3));
  CXXGraph::Graph<int> graph(edgeSet);
  int res = graph.writeToFile(CXXGraph::InputOutputFormat::STANDARD_CSV, ".",
                              "test_23", true, false, false);
  ASSERT_EQ(res, 0);
  ASSERT_FALSE(exists_test("test_23.csv"));
  ASSERT_FALSE(exists_test("test_23_NodeFeat.csv"));
  ASSERT_FALSE(exists_test("test_23_EdgeWeight.csv"));
  ASSERT_TRUE(exists_test("test_23.csv.gz"));
  ASSERT_FALSE(exists_test("test_23_NodeFeat.csv.gz"));
  ASSERT_FALSE(exists_test("test_23_EdgeWeight.csv.gz"));

  remove("test_23.csv.gz");
  ASSERT_FALSE(exists_test("test_23.csv.gz"));
}

TEST(RWOutputTest, test_24) {
  CXXGraph::Node<int> node1("1", 1);
  CXXGraph::Node<int> node2("2", 2);
  CXXGraph::Node<int> node3("3", 3);
  CXXGraph::DirectedWeightedEdge<int> edge2(2, node2, node3, 1);
  CXXGraph::UndirectedWeightedEdge<int> edge3(3, node1, node3, 6);
  CXXGraph::T_EdgeSet<int> edgeSet;
  edgeSet.insert(make_shared<CXXGraph::DirectedWeightedEdge<int>>(edge2));
  edgeSet.insert(make_shared<CXXGraph::UndirectedWeightedEdge<int>>(edge3));
  CXXGraph::Graph<int> graph(edgeSet);
  int res = graph.writeToFile(CXXGraph::InputOutputFormat::STANDARD_TSV, ".",
                              "test_24", true, true, false);
  ASSERT_EQ(res, 0);
  ASSERT_FALSE(exists_test("test_24.tsv"));
  ASSERT_FALSE(exists_test("test_24_NodeFeat.tsv"));
  ASSERT_FALSE(exists_test("test_24_EdgeWeight.tsv"));
  ASSERT_TRUE(exists_test("test_24.tsv.gz"));
  ASSERT_TRUE(exists_test("test_24_NodeFeat.tsv.gz"));
  ASSERT_FALSE(exists_test("test_24_EdgeWeight.tsv.gz"));

  remove("test_24.tsv.gz");
  remove("test_24_NodeFeat.tsv.gz");
  ASSERT_FALSE(exists_test("test_24.tsv.gz"));
  ASSERT_FALSE(exists_test("test_24_NodeFeat.tsv.gz"));
}

TEST(RWOutputTest, test_25) {
  CXXGraph::Node<int> node1("1", 1);
  CXXGraph::Node<int> node2("2", 2);
  CXXGraph::Node<int> node3("3", 3);
  std::pair<const CXXGraph::Node<int> *, const CXXGraph::Node<int> *> pairNode(
      &node1, &node2);
  CXXGraph::DirectedWeightedEdge<int> edge1(1, pairNode, 5);
  CXXGraph::DirectedEdge<int> edge2(2, node2, node3);
  CXXGraph::UndirectedWeightedEdge<int> edge3(3, node1, node3, 6);
  CXXGraph::T_EdgeSet<int> edgeSet;
  edgeSet.insert(make_shared<CXXGraph::DirectedWeightedEdge<int>>(edge1));
  edgeSet.insert(make_shared<CXXGraph::DirectedEdge<int>>(edge2));
  edgeSet.insert(make_shared<CXXGraph::UndirectedWeightedEdge<int>>(edge3));
  CXXGraph::Graph<int> graph(edgeSet);
  int res = graph.writeToFile(CXXGraph::InputOutputFormat::STANDARD_TSV, ".",
                              "test_25", true, true, true);
  ASSERT_EQ(res, 0);
  ASSERT_FALSE(exists_test("test_25.tsv"));
  ASSERT_FALSE(exists_test("test_25_NodeFeat.tsv"));
  ASSERT_FALSE(exists_test("test_25_EdgeWeight.tsv"));
  ASSERT_TRUE(exists_test("test_25.tsv.gz"));
  ASSERT_TRUE(exists_test("test_25_NodeFeat.tsv.gz"));
  ASSERT_TRUE(exists_test("test_25_EdgeWeight.tsv.gz"));

  CXXGraph::Graph<int> readGraph;
  auto readResult =
      readGraph.readFromFile(CXXGraph::InputOutputFormat::STANDARD_TSV, ".",
                             "test_25", true, true, true);
  ASSERT_EQ(readResult, 0);
  auto readNode = readGraph.getNodeSet();
  auto readEdge = readGraph.getEdgeSet();
  ASSERT_EQ(readEdge.size(), 3);
  ASSERT_EQ(readNode.size(), 3);

  for (const auto &readEdgeIt : readEdge) {
    if (readEdgeIt->getId() == 1) {
      ASSERT_TRUE(readEdgeIt->isDirected().has_value() &&
                  readEdgeIt->isDirected().value());
      ASSERT_TRUE(readEdgeIt->isWeighted().has_value() &&
                  readEdgeIt->isWeighted().value());
      ASSERT_EQ((dynamic_cast<const CXXGraph::Weighted *>(readEdgeIt.get()))
                    ->getWeight(),
                5);
      ASSERT_EQ(readEdgeIt->getNodePair().first->getUserId(),
                node1.getUserId());
      ASSERT_EQ(readEdgeIt->getNodePair().first->getData(), node1.getData());
      ASSERT_EQ(readEdgeIt->getNodePair().second->getUserId(),
                node2.getUserId());
      ASSERT_EQ(readEdgeIt->getNodePair().second->getData(), node2.getData());
    } else if (readEdgeIt->getId() == 2) {
      ASSERT_TRUE(readEdgeIt->isDirected().has_value() &&
                  readEdgeIt->isDirected().value());
      ASSERT_TRUE(readEdgeIt->isWeighted().has_value() &&
                  !readEdgeIt->isWeighted().value());
      ASSERT_EQ(readEdgeIt->getNodePair().first->getUserId(),
                node2.getUserId());
      ASSERT_EQ(readEdgeIt->getNodePair().first->getData(), node2.getData());
      ASSERT_EQ(readEdgeIt->getNodePair().second->getUserId(),
                node3.getUserId());
      ASSERT_EQ(readEdgeIt->getNodePair().second->getData(), node3.getData());
    } else if (readEdgeIt->getId() == 3) {
      ASSERT_TRUE(readEdgeIt->isDirected().has_value() &&
                  !readEdgeIt->isDirected().value());
      ASSERT_TRUE(readEdgeIt->isWeighted().has_value() &&
                  readEdgeIt->isWeighted().value());
      ASSERT_EQ((dynamic_cast<const CXXGraph::Weighted *>(readEdgeIt.get()))
                    ->getWeight(),
                6);
      ASSERT_EQ(readEdgeIt->getNodePair().first->getUserId(),
                node1.getUserId());
      ASSERT_EQ(readEdgeIt->getNodePair().first->getData(), node1.getData());
      ASSERT_EQ(readEdgeIt->getNodePair().second->getUserId(),
                node3.getUserId());
      ASSERT_EQ(readEdgeIt->getNodePair().second->getData(), node3.getData());
    } else {
      ASSERT_TRUE(false);  // forced Error
    }
  }

  remove("test_25.tsv.gz");
  remove("test_25_NodeFeat.tsv.gz");
  remove("test_25_EdgeWeight.tsv.gz");
  ASSERT_FALSE(exists_test("test_25.tsv"));
  ASSERT_FALSE(exists_test("test_25_NodeFeat.tsv"));
  ASSERT_FALSE(exists_test("test_25_EdgeWeight.tsv"));
  ASSERT_FALSE(exists_test("test_25.tsv.gz"));
  ASSERT_FALSE(exists_test("test_25_NodeFeat.tsv.gz"));
  ASSERT_FALSE(exists_test("test_25_EdgeWeight.tsv.gz"));
}

TEST(RWOutputTest, test_26) {
  CXXGraph::Node<int> node1("1", 1);
  CXXGraph::Node<int> node2("2", 2);
  CXXGraph::Node<int> node3("3", 3);
  CXXGraph::DirectedWeightedEdge<int> edge2(2, node2, node3, 1);
  CXXGraph::UndirectedWeightedEdge<int> edge3(3, node1, node3, 6);
  CXXGraph::T_EdgeSet<int> edgeSet;
  edgeSet.insert(make_shared<CXXGraph::DirectedWeightedEdge<int>>(edge2));
  edgeSet.insert(make_shared<CXXGraph::UndirectedWeightedEdge<int>>(edge3));
  CXXGraph::Graph<int> graph(edgeSet);
  int res = graph.writeToFile(CXXGraph::InputOutputFormat::STANDARD_TSV, ".",
                              "test_26", true, false, false);
  ASSERT_EQ(res, 0);
  ASSERT_FALSE(exists_test("test_26.tsv"));
  ASSERT_FALSE(exists_test("test_26_NodeFeat.tsv"));
  ASSERT_FALSE(exists_test("test_26_EdgeWeight.tsv"));
  ASSERT_TRUE(exists_test("test_26.tsv.gz"));
  ASSERT_FALSE(exists_test("test_26_NodeFeat.tsv.gz"));
  ASSERT_FALSE(exists_test("test_26_EdgeWeight.tsv.gz"));

  remove("test_26.tsv.gz");
  ASSERT_FALSE(exists_test("test_26.tsv.gz"));
}

TEST(RWOutputTest, test_27) {
  CXXGraph::T_EdgeSet<int> edgeSet;
  for (const auto &edge : edges) {
    edgeSet.insert(make_shared<CXXGraph::Edge<int>>(*(edge.second)));
  }
  CXXGraph::Graph<int> graph(edgeSet);
  int res = graph.writeToFile(CXXGraph::InputOutputFormat::STANDARD_TSV, ".",
                              "test_27", true, false, false);
  ASSERT_EQ(res, 0);
  ASSERT_FALSE(exists_test("test_27.tsv"));
  ASSERT_FALSE(exists_test("test_27_NodeFeat.tsv"));
  ASSERT_FALSE(exists_test("test_27_EdgeWeight.tsv"));
  ASSERT_TRUE(exists_test("test_27.tsv.gz"));
  ASSERT_FALSE(exists_test("test_27_NodeFeat.tsv.gz"));
  ASSERT_FALSE(exists_test("test_27_EdgeWeight.tsv.gz"));
  std::ifstream file("test_27.tsv", std::ios::binary);
  file.seekg(0, std::ios::end);
  std::streampos file_size = file.tellg();
  std::ifstream fileCompressed("a.txt", std::ios::binary);
  fileCompressed.seekg(0, std::ios::end);
  std::streampos file_compressed_size = fileCompressed.tellg();
  ASSERT_LE(file_compressed_size, file_size);

  remove("test_27.tsv.gz");
  ASSERT_FALSE(exists_test("test_27.tsv.gz"));
}

TEST(RWOutputTest, test_28) {
  CXXGraph::Node<int> node1("1", 1);
  CXXGraph::Node<int> node2("2", 2);
  CXXGraph::DirectedWeightedEdge<int> edge1(2, node1, node2, 1);
  CXXGraph::T_EdgeSet<int> edgeSet;
  edgeSet.insert(make_shared<CXXGraph::DirectedWeightedEdge<int>>(edge1));
  CXXGraph::Graph<int> graph(edgeSet);
  // force error by writing to a non-existent directory
  int res = graph.writeToFile(CXXGraph::InputOutputFormat::STANDARD_TSV,
                              "./sid", "test_26", true, false, false);
  ASSERT_EQ(res, -1);
  CXXGraph::Graph<int> readGraph;
  // read from a non-existent file
  res = readGraph.readFromFile(CXXGraph::InputOutputFormat::STANDARD_CSV, ".",
                               "./sid/test_8");
  ASSERT_EQ(res, -1);
  // try to read csv file in tst format
  // should result in OUTPUT FORMAT NOT RECOGNIZED
  res = readGraph.readFromFile(CXXGraph::InputOutputFormat::STANDARD_TSV, ".",
                               "test_8");
  ASSERT_EQ(res, -1);
  res = readGraph.readFromFile(CXXGraph::InputOutputFormat::STANDARD_TSV, ".",
                               "test_8", true);
  ASSERT_EQ(res, -1);
}

TEST(RWOutputTest, test_29) {
  CXXGraph::Node<int> node1("first", 1);
  CXXGraph::Node<int> node2("second", 2);
  CXXGraph::Node<int> node3("Third", 3);
  std::pair<const CXXGraph::Node<int> *, const CXXGraph::Node<int> *> pairNode(
      &node1, &node2);
  CXXGraph::DirectedWeightedEdge<int> edge1(1, pairNode, 5);
  CXXGraph::DirectedEdge<int> edge2(2, node2, node3);
  CXXGraph::UndirectedWeightedEdge<int> edge3(3, node1, node3, 6);
  CXXGraph::T_EdgeSet<int> edgeSet;
  edgeSet.insert(make_shared<CXXGraph::DirectedWeightedEdge<int>>(edge1));
  edgeSet.insert(make_shared<CXXGraph::DirectedEdge<int>>(edge2));
  edgeSet.insert(make_shared<CXXGraph::UndirectedWeightedEdge<int>>(edge3));
  CXXGraph::Graph<int> graph(edgeSet);
  int res = graph.writeToFile(CXXGraph::InputOutputFormat::STANDARD_TSV, ".",
                              "test_29", true, true, true);
  ASSERT_EQ(res, 0);
  ASSERT_FALSE(exists_test("test_29.tsv"));
  ASSERT_FALSE(exists_test("test_29_NodeFeat.tsv"));
  ASSERT_FALSE(exists_test("test_29_EdgeWeight.tsv"));
  ASSERT_TRUE(exists_test("test_29.tsv.gz"));
  ASSERT_TRUE(exists_test("test_29_NodeFeat.tsv.gz"));
  ASSERT_TRUE(exists_test("test_29_EdgeWeight.tsv.gz"));

  CXXGraph::Graph<int> readGraph;
  auto readResult =
      readGraph.readFromFile(CXXGraph::InputOutputFormat::STANDARD_TSV, ".",
                             "test_29", true, true, true);
  ASSERT_EQ(readResult, 0);
  auto readNode = readGraph.getNodeSet();
  auto readEdge = readGraph.getEdgeSet();
  ASSERT_EQ(readEdge.size(), 3);
  ASSERT_EQ(readNode.size(), 3);

  for (const auto &readEdgeIt : readEdge) {
    if (readEdgeIt->getId() == 1) {
      ASSERT_TRUE(readEdgeIt->isDirected().has_value() &&
                  readEdgeIt->isDirected().value());
      ASSERT_TRUE(readEdgeIt->isWeighted().has_value() &&
                  readEdgeIt->isWeighted().value());
      ASSERT_EQ((dynamic_cast<const CXXGraph::Weighted *>(readEdgeIt.get()))
                    ->getWeight(),
                5);
      ASSERT_EQ(readEdgeIt->getNodePair().first->getUserId(),
                node1.getUserId());
      ASSERT_EQ(readEdgeIt->getNodePair().first->getData(), node1.getData());
      ASSERT_EQ(readEdgeIt->getNodePair().second->getUserId(),
                node2.getUserId());
      ASSERT_EQ(readEdgeIt->getNodePair().second->getData(), node2.getData());
    } else if (readEdgeIt->getId() == 2) {
      ASSERT_TRUE(readEdgeIt->isDirected().has_value() &&
                  readEdgeIt->isDirected().value());
      ASSERT_TRUE(readEdgeIt->isWeighted().has_value() &&
                  !readEdgeIt->isWeighted().value());
      ASSERT_EQ(readEdgeIt->getNodePair().first->getUserId(),
                node2.getUserId());
      ASSERT_EQ(readEdgeIt->getNodePair().first->getData(), node2.getData());
      ASSERT_EQ(readEdgeIt->getNodePair().second->getUserId(),
                node3.getUserId());
      ASSERT_EQ(readEdgeIt->getNodePair().second->getData(), node3.getData());
    } else if (readEdgeIt->getId() == 3) {
      ASSERT_TRUE(readEdgeIt->isDirected().has_value() &&
                  !readEdgeIt->isDirected().value());
      ASSERT_TRUE(readEdgeIt->isWeighted().has_value() &&
                  readEdgeIt->isWeighted().value());
      ASSERT_EQ((dynamic_cast<const CXXGraph::Weighted *>(readEdgeIt.get()))
                    ->getWeight(),
                6);
      ASSERT_EQ(readEdgeIt->getNodePair().first->getUserId(),
                node1.getUserId());
      ASSERT_EQ(readEdgeIt->getNodePair().first->getData(), node1.getData());
      ASSERT_EQ(readEdgeIt->getNodePair().second->getUserId(),
                node3.getUserId());
      ASSERT_EQ(readEdgeIt->getNodePair().second->getData(), node3.getData());
    } else {
      ASSERT_TRUE(false);  // forced Error
    }
  }

  remove("test_29.tsv.gz");
  remove("test_29_NodeFeat.tsv.gz");
  remove("test_29_EdgeWeight.tsv.gz");
  ASSERT_FALSE(exists_test("test_29.tsv"));
  ASSERT_FALSE(exists_test("test_29_NodeFeat.tsv"));
  ASSERT_FALSE(exists_test("test_29_EdgeWeight.tsv"));
  ASSERT_FALSE(exists_test("test_29.tsv.gz"));
  ASSERT_FALSE(exists_test("test_29_NodeFeat.tsv.gz"));
  ASSERT_FALSE(exists_test("test_29_EdgeWeight.tsv.gz"));
}
