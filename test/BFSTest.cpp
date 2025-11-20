#include <memory>
#include <random>
#include <set>
#include <string>
#include <utility>
#include <vector>

#include "CXXGraph/CXXGraph.hpp"
#include "gtest/gtest.h"

// Smart pointers alias
template <typename T>
using unique = std::unique_ptr<T>;
template <typename T>
using shared = std::shared_ptr<T>;

using std::make_shared;
using std::make_unique;

TEST(BFSTest, test_1) {
  CXXGraph::Node<int> node1("1", 1);
  CXXGraph::Node<int> node2("2", 2);
  CXXGraph::Node<int> node3("3", 3);
  std::pair<const CXXGraph::Node<int> *, const CXXGraph::Node<int> *> pairNode(
      &node1, &node2);
  CXXGraph::DirectedWeightedEdge<int> edge1("1", pairNode, 1);
  CXXGraph::DirectedWeightedEdge<int> edge2("2", node2, node3, 1);
  CXXGraph::UndirectedWeightedEdge<int> edge3("3", node1, node3, 6);
  CXXGraph::T_EdgeSet<int> edgeSet;
  edgeSet.insert(make_shared<CXXGraph::DirectedWeightedEdge<int>>(edge1));
  edgeSet.insert(make_shared<CXXGraph::DirectedWeightedEdge<int>>(edge2));
  edgeSet.insert(make_shared<CXXGraph::UndirectedWeightedEdge<int>>(edge3));
  CXXGraph::Graph<int> graph(edgeSet);
  std::vector<CXXGraph::Node<int>> res = graph.breadth_first_search(node1);
  ASSERT_EQ(res.size(), 3);
  ASSERT_TRUE(std::find(res.begin(), res.end(), node1) != res.end());
  ASSERT_TRUE(std::find(res.begin(), res.end(), node2) != res.end());
  ASSERT_TRUE(std::find(res.begin(), res.end(), node3) != res.end());
}

TEST(BFSTest, test_2) {
  CXXGraph::Node<int> node1("1", 1);
  CXXGraph::Node<int> node2("2", 2);
  CXXGraph::Node<int> node3("3", 3);
  std::pair<const CXXGraph::Node<int> *, const CXXGraph::Node<int> *> pairNode(
      &node1, &node2);
  CXXGraph::DirectedWeightedEdge<int> edge1("1", pairNode, 1);
  CXXGraph::DirectedWeightedEdge<int> edge2("2", node2, node3, 1);
  CXXGraph::DirectedWeightedEdge<int> edge3("3", node1, node3, 6);
  CXXGraph::T_EdgeSet<int> edgeSet;
  edgeSet.insert(make_shared<CXXGraph::DirectedWeightedEdge<int>>(edge1));
  edgeSet.insert(make_shared<CXXGraph::DirectedWeightedEdge<int>>(edge2));
  edgeSet.insert(make_shared<CXXGraph::DirectedWeightedEdge<int>>(edge3));
  CXXGraph::Graph<int> graph(edgeSet);
  std::vector<CXXGraph::Node<int>> res = graph.breadth_first_search(node2);
  ASSERT_EQ(res.size(), 2);
  ASSERT_FALSE(std::find(res.begin(), res.end(), node1) != res.end());
  ASSERT_TRUE(std::find(res.begin(), res.end(), node2) != res.end());
  ASSERT_TRUE(std::find(res.begin(), res.end(), node3) != res.end());
}

TEST(BFSTest, test_3) {
  CXXGraph::Node<int> node1("1", 1);
  CXXGraph::Node<int> node2("2", 2);
  CXXGraph::Node<int> node3("3", 3);
  std::pair<const CXXGraph::Node<int> *, const CXXGraph::Node<int> *> pairNode(
      &node1, &node2);
  CXXGraph::DirectedWeightedEdge<int> edge1("1", pairNode, 1);
  CXXGraph::DirectedWeightedEdge<int> edge2("2", node2, node3, 1);
  CXXGraph::UndirectedWeightedEdge<int> edge3("3", node1, node3, 6);
  CXXGraph::T_EdgeSet<int> edgeSet;
  edgeSet.insert(make_shared<CXXGraph::DirectedWeightedEdge<int>>(edge1));
  edgeSet.insert(make_shared<CXXGraph::DirectedWeightedEdge<int>>(edge2));
  edgeSet.insert(make_shared<CXXGraph::UndirectedWeightedEdge<int>>(edge3));
  CXXGraph::Graph<int> graph(edgeSet);
  std::vector<CXXGraph::Node<int>> res = graph.breadth_first_search(node2);
  ASSERT_EQ(res.size(), 3);
  ASSERT_TRUE(std::find(res.begin(), res.end(), node1) != res.end());
  ASSERT_TRUE(std::find(res.begin(), res.end(), node2) != res.end());
  ASSERT_TRUE(std::find(res.begin(), res.end(), node3) != res.end());
}

TEST(BFSTest, test_4) {
  CXXGraph::Node<int> node1("1", 1);
  CXXGraph::Node<int> node2("2", 2);
  CXXGraph::Node<int> node3("3", 3);
  std::pair<const CXXGraph::Node<int> *, const CXXGraph::Node<int> *> pairNode(
      &node1, &node2);
  CXXGraph::DirectedWeightedEdge<int> edge1("1", pairNode, 1);
  CXXGraph::DirectedWeightedEdge<int> edge2("2", node2, node3, 1);
  CXXGraph::UndirectedWeightedEdge<int> edge3("3", node1, node3, 6);
  CXXGraph::T_EdgeSet<int> edgeSet;
  edgeSet.insert(make_shared<CXXGraph::DirectedWeightedEdge<int>>(edge1));
  edgeSet.insert(make_shared<CXXGraph::DirectedWeightedEdge<int>>(edge2));
  edgeSet.insert(make_shared<CXXGraph::UndirectedWeightedEdge<int>>(edge3));
  CXXGraph::Graph<int> graph(edgeSet);
  std::vector<CXXGraph::Node<int>> res = graph.breadth_first_search(node3);
  ASSERT_EQ(res.size(), 3);
  ASSERT_TRUE(std::find(res.begin(), res.end(), node1) != res.end());
  ASSERT_TRUE(std::find(res.begin(), res.end(), node2) != res.end());
  ASSERT_TRUE(std::find(res.begin(), res.end(), node3) != res.end());
}

TEST(BFSTest, test_5) {
  CXXGraph::Node<int> node1("1", 1);
  CXXGraph::Node<int> node2("2", 2);
  CXXGraph::Node<int> node3("3", 3);
  std::pair<const CXXGraph::Node<int> *, const CXXGraph::Node<int> *> pairNode(
      &node1, &node2);
  CXXGraph::DirectedWeightedEdge<int> edge1("1", pairNode, 1);
  CXXGraph::DirectedWeightedEdge<int> edge2("2", node2, node3, 1);
  CXXGraph::DirectedWeightedEdge<int> edge3("3", node1, node3, 6);
  CXXGraph::T_EdgeSet<int> edgeSet;
  edgeSet.insert(make_shared<CXXGraph::DirectedWeightedEdge<int>>(edge1));
  edgeSet.insert(make_shared<CXXGraph::DirectedWeightedEdge<int>>(edge2));
  edgeSet.insert(make_shared<CXXGraph::DirectedWeightedEdge<int>>(edge3));
  CXXGraph::Graph<int> graph(edgeSet);
  std::vector<CXXGraph::Node<int>> res = graph.breadth_first_search(node3);
  ASSERT_EQ(res.size(), 1);
  ASSERT_FALSE(std::find(res.begin(), res.end(), node1) != res.end());
  ASSERT_FALSE(std::find(res.begin(), res.end(), node2) != res.end());
  ASSERT_TRUE(std::find(res.begin(), res.end(), node3) != res.end());
}

TEST(BFSTest, test_6) {
  CXXGraph::Node<int> node1("1", 1);
  CXXGraph::Node<int> node2("2", 2);
  CXXGraph::Node<int> node3("3", 3);
  CXXGraph::Node<int> node4("4", 4);
  std::pair<const CXXGraph::Node<int> *, const CXXGraph::Node<int> *> pairNode(
      &node1, &node2);
  CXXGraph::DirectedWeightedEdge<int> edge1("1", pairNode, 1);
  CXXGraph::DirectedWeightedEdge<int> edge2("2", node2, node3, 1);
  CXXGraph::DirectedWeightedEdge<int> edge3("3", node1, node3, 6);
  CXXGraph::T_EdgeSet<int> edgeSet;
  edgeSet.insert(make_shared<CXXGraph::DirectedWeightedEdge<int>>(edge1));
  edgeSet.insert(make_shared<CXXGraph::DirectedWeightedEdge<int>>(edge2));
  edgeSet.insert(make_shared<CXXGraph::DirectedWeightedEdge<int>>(edge3));
  CXXGraph::Graph<int> graph(edgeSet);
  std::vector<CXXGraph::Node<int>> res = graph.breadth_first_search(node4);
  ASSERT_EQ(res.size(), 0);
  ASSERT_FALSE(std::find(res.begin(), res.end(), node1) != res.end());
  ASSERT_FALSE(std::find(res.begin(), res.end(), node2) != res.end());
  ASSERT_FALSE(std::find(res.begin(), res.end(), node3) != res.end());
  ASSERT_FALSE(std::find(res.begin(), res.end(), node4) != res.end());
}

// test cases of concurrency bfs
TEST(BFSTest, test_7) {
  CXXGraph::Node<int> node1("1", 1);
  CXXGraph::Node<int> node2("2", 2);
  CXXGraph::Node<int> node3("3", 3);
  std::pair<const CXXGraph::Node<int> *, const CXXGraph::Node<int> *> pairNode(
      &node1, &node2);
  CXXGraph::DirectedWeightedEdge<int> edge1("1", pairNode, 1);
  CXXGraph::DirectedWeightedEdge<int> edge2("2", node2, node3, 1);
  CXXGraph::UndirectedWeightedEdge<int> edge3("3", node1, node3, 6);
  CXXGraph::T_EdgeSet<int> edgeSet;
  edgeSet.insert(make_shared<CXXGraph::DirectedWeightedEdge<int>>(edge1));
  edgeSet.insert(make_shared<CXXGraph::DirectedWeightedEdge<int>>(edge2));
  edgeSet.insert(make_shared<CXXGraph::UndirectedWeightedEdge<int>>(edge3));
  CXXGraph::Graph<int> graph(edgeSet);
  std::vector<CXXGraph::Node<int>> res =
      graph.concurrency_breadth_first_search(node1, 4);
  ASSERT_EQ(res.size(), 3);
  ASSERT_TRUE(std::find(res.begin(), res.end(), node1) != res.end());
  ASSERT_TRUE(std::find(res.begin(), res.end(), node2) != res.end());
  ASSERT_TRUE(std::find(res.begin(), res.end(), node3) != res.end());
}

TEST(BFSTest, test_8) {
  CXXGraph::Node<int> node1("1", 1);
  CXXGraph::Node<int> node2("2", 2);
  CXXGraph::Node<int> node3("3", 3);
  std::pair<const CXXGraph::Node<int> *, const CXXGraph::Node<int> *> pairNode(
      &node1, &node2);
  CXXGraph::DirectedWeightedEdge<int> edge1("1", pairNode, 1);
  CXXGraph::DirectedWeightedEdge<int> edge2("2", node2, node3, 1);
  CXXGraph::DirectedWeightedEdge<int> edge3("3", node1, node3, 6);
  CXXGraph::T_EdgeSet<int> edgeSet;
  edgeSet.insert(make_shared<CXXGraph::DirectedWeightedEdge<int>>(edge1));
  edgeSet.insert(make_shared<CXXGraph::DirectedWeightedEdge<int>>(edge2));
  edgeSet.insert(make_shared<CXXGraph::DirectedWeightedEdge<int>>(edge3));
  CXXGraph::Graph<int> graph(edgeSet);
  std::vector<CXXGraph::Node<int>> res =
      graph.concurrency_breadth_first_search(node2, 4);
  ASSERT_EQ(res.size(), 2);
  ASSERT_FALSE(std::find(res.begin(), res.end(), node1) != res.end());
  ASSERT_TRUE(std::find(res.begin(), res.end(), node2) != res.end());
  ASSERT_TRUE(std::find(res.begin(), res.end(), node3) != res.end());
}

TEST(BFSTest, test_9) {
  CXXGraph::Node<int> node1("1", 1);
  CXXGraph::Node<int> node2("2", 2);
  CXXGraph::Node<int> node3("3", 3);
  std::pair<const CXXGraph::Node<int> *, const CXXGraph::Node<int> *> pairNode(
      &node1, &node2);
  CXXGraph::DirectedWeightedEdge<int> edge1("1", pairNode, 1);
  CXXGraph::DirectedWeightedEdge<int> edge2("2", node2, node3, 1);
  CXXGraph::UndirectedWeightedEdge<int> edge3("3", node1, node3, 6);
  CXXGraph::T_EdgeSet<int> edgeSet;
  edgeSet.insert(make_shared<CXXGraph::DirectedWeightedEdge<int>>(edge1));
  edgeSet.insert(make_shared<CXXGraph::DirectedWeightedEdge<int>>(edge2));
  edgeSet.insert(make_shared<CXXGraph::UndirectedWeightedEdge<int>>(edge3));
  CXXGraph::Graph<int> graph(edgeSet);
  std::vector<CXXGraph::Node<int>> res =
      graph.concurrency_breadth_first_search(node2, 4);
  ASSERT_EQ(res.size(), 3);
  ASSERT_TRUE(std::find(res.begin(), res.end(), node1) != res.end());
  ASSERT_TRUE(std::find(res.begin(), res.end(), node2) != res.end());
  ASSERT_TRUE(std::find(res.begin(), res.end(), node3) != res.end());
}

TEST(BFSTest, test_10) {
  CXXGraph::Node<int> node1("1", 1);
  CXXGraph::Node<int> node2("2", 2);
  CXXGraph::Node<int> node3("3", 3);
  std::pair<const CXXGraph::Node<int> *, const CXXGraph::Node<int> *> pairNode(
      &node1, &node2);
  CXXGraph::DirectedWeightedEdge<int> edge1("1", pairNode, 1);
  CXXGraph::DirectedWeightedEdge<int> edge2("2", node2, node3, 1);
  CXXGraph::UndirectedWeightedEdge<int> edge3("3", node1, node3, 6);
  CXXGraph::T_EdgeSet<int> edgeSet;
  edgeSet.insert(make_shared<CXXGraph::DirectedWeightedEdge<int>>(edge1));
  edgeSet.insert(make_shared<CXXGraph::DirectedWeightedEdge<int>>(edge2));
  edgeSet.insert(make_shared<CXXGraph::UndirectedWeightedEdge<int>>(edge3));
  CXXGraph::Graph<int> graph(edgeSet);
  std::vector<CXXGraph::Node<int>> res =
      graph.concurrency_breadth_first_search(node3, 4);
  ASSERT_EQ(res.size(), 3);
  ASSERT_TRUE(std::find(res.begin(), res.end(), node1) != res.end());
  ASSERT_TRUE(std::find(res.begin(), res.end(), node2) != res.end());
  ASSERT_TRUE(std::find(res.begin(), res.end(), node3) != res.end());
}

TEST(BFSTest, test_11) {
  CXXGraph::Node<int> node1("1", 1);
  CXXGraph::Node<int> node2("2", 2);
  CXXGraph::Node<int> node3("3", 3);
  std::pair<const CXXGraph::Node<int> *, const CXXGraph::Node<int> *> pairNode(
      &node1, &node2);
  CXXGraph::DirectedWeightedEdge<int> edge1("1", pairNode, 1);
  CXXGraph::DirectedWeightedEdge<int> edge2("2", node2, node3, 1);
  CXXGraph::DirectedWeightedEdge<int> edge3("3", node1, node3, 6);
  CXXGraph::T_EdgeSet<int> edgeSet;
  edgeSet.insert(make_shared<CXXGraph::DirectedWeightedEdge<int>>(edge1));
  edgeSet.insert(make_shared<CXXGraph::DirectedWeightedEdge<int>>(edge2));
  edgeSet.insert(make_shared<CXXGraph::DirectedWeightedEdge<int>>(edge3));
  CXXGraph::Graph<int> graph(edgeSet);
  std::vector<CXXGraph::Node<int>> res =
      graph.concurrency_breadth_first_search(node3, 4);
  ASSERT_EQ(res.size(), 1);
  ASSERT_FALSE(std::find(res.begin(), res.end(), node1) != res.end());
  ASSERT_FALSE(std::find(res.begin(), res.end(), node2) != res.end());
  ASSERT_TRUE(std::find(res.begin(), res.end(), node3) != res.end());
}

TEST(BFSTest, test_12) {
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
  CXXGraph::UndirectedWeightedEdge<int> edge1("1", pairNode, 1);
  CXXGraph::UndirectedWeightedEdge<int> edge2("2", node2, node3, 1);
  CXXGraph::UndirectedWeightedEdge<int> edge3("3", node2, node6, 6);
  CXXGraph::UndirectedWeightedEdge<int> edge4("3", node3, node4, 6);
  CXXGraph::UndirectedWeightedEdge<int> edge5("3", node3, node5, 6);
  CXXGraph::UndirectedWeightedEdge<int> edge6("3", node6, node7, 6);
  CXXGraph::UndirectedWeightedEdge<int> edge7("3", node8, node6, 6);
  CXXGraph::UndirectedWeightedEdge<int> edge8("3", node8, node7, 6);
  CXXGraph::T_EdgeSet<int> edgeSet;
  edgeSet.insert(make_shared<CXXGraph::UndirectedWeightedEdge<int>>(edge1));
  edgeSet.insert(make_shared<CXXGraph::UndirectedWeightedEdge<int>>(edge2));
  edgeSet.insert(make_shared<CXXGraph::UndirectedWeightedEdge<int>>(edge3));
  edgeSet.insert(make_shared<CXXGraph::UndirectedWeightedEdge<int>>(edge4));
  edgeSet.insert(make_shared<CXXGraph::UndirectedWeightedEdge<int>>(edge5));
  edgeSet.insert(make_shared<CXXGraph::UndirectedWeightedEdge<int>>(edge6));
  edgeSet.insert(make_shared<CXXGraph::UndirectedWeightedEdge<int>>(edge7));
  edgeSet.insert(make_shared<CXXGraph::UndirectedWeightedEdge<int>>(edge8));
  CXXGraph::Graph<int> graph(edgeSet);
  std::vector<CXXGraph::Node<int>> res =
      graph.concurrency_breadth_first_search(node8, 4);
  ASSERT_EQ(res.size(), 8);
}

// this case is to verify result correction when number of threads more than 1
TEST(BFSTest, test_13) {
  thread_local static std::default_random_engine rand;
  thread_local static std::uniform_int_distribution distribution(0, RAND_MAX);

  unsigned int randSeed = (unsigned int)time(NULL);
  rand.seed(randSeed);

  int nodes_size = 60, edges_size = 2000;
  std::vector<shared<CXXGraph::Node<int>>> nodes;
  for (auto index = 0; index < nodes_size; index++) {
    int randomNumber = (distribution(rand) % nodes_size) + 1;
    auto newNode =
        make_shared<CXXGraph::Node<int>>(std::to_string(index), randomNumber);
    nodes.push_back(newNode);
  }

  CXXGraph::T_EdgeSet<int> edgeSet;
  auto MaxValue = nodes.size();
  for (auto index = 0; index < edges_size; index++) {
    int randomNumber1 = (distribution(rand) % MaxValue);
    int randomNumber2 = (distribution(rand) % MaxValue);
    if (randomNumber1 != randomNumber2) {
      shared<CXXGraph::UndirectedEdge<int>> newEdge =
          make_shared<CXXGraph::UndirectedEdge<int>>(
              std::to_string(index), *(nodes.at(randomNumber1)),
              *(nodes.at(randomNumber2)));
      edgeSet.insert(newEdge);
    }
  }
  for (size_t i = 1; i < nodes.size(); i += 2) {
    shared<CXXGraph::UndirectedEdge<int>> newEdge =
        make_shared<CXXGraph::UndirectedEdge<int>>(
            std::to_string(edges_size + i + 1), *(nodes.at(0)), *(nodes.at(i)));
    edgeSet.insert(newEdge);
  }
  CXXGraph::Graph<int> graph(edgeSet);

  auto &result1 = graph.breadth_first_search(*(nodes[0]));
  std::set<CXXGraph::Node<int>> st1;
  for (const auto &node : result1) {
    st1.emplace(node);
  }

  auto &result2 = graph.concurrency_breadth_first_search(*(nodes[0]), 4);
  ASSERT_EQ(result1.size(), result2.size());

  for (const auto &node : result2) {
    ASSERT_TRUE(st1.count(node));
    if (!st1.count(node)) {
      std::cout << node;
    }
  }
}
