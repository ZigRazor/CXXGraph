#ifndef __UTILITIES_H__
#define __UTILITIES_H__
#include <time.h>

#include <random>

#include "CXXGraph.hpp"

static std::map<unsigned long, CXXGraph::Node<int> *> generateRandomNodes(
    unsigned long numberOfNodes, int MaxValue) {
  thread_local static std::default_random_engine rand;
  thread_local static std::uniform_int_distribution distribution(0, RAND_MAX);

  std::map<unsigned long, CXXGraph::Node<int> *> nodes;

  unsigned int randSeed = (unsigned int)time(NULL);
  rand.seed(randSeed);
  int randomNumber;
  for (auto index = 0; index < numberOfNodes; index++) {
    randomNumber = (distribution(rand) % MaxValue) + 1;
    CXXGraph::Node<int> *newNode =
        new CXXGraph::Node<int>(std::to_string(index), randomNumber);
    nodes[index] = newNode;
  }
  return nodes;
}

static std::map<unsigned long, CXXGraph::Edge<int> *> generateRandomEdges(
    unsigned long numberOfEdges,
    std::map<unsigned long, CXXGraph::Node<int> *> nodes) {
  thread_local static std::default_random_engine rand;
  thread_local static std::uniform_int_distribution distribution(0, RAND_MAX);

  std::map<unsigned long, CXXGraph::Edge<int> *> edges;

  unsigned int randSeed = (unsigned int)time(NULL);
  rand.seed(randSeed);
  int randomNumber1;
  int randomNumber2;
  auto MaxValue = nodes.size();
  for (auto index = 0; index < numberOfEdges; index++) {
    randomNumber1 = (distribution(rand) % MaxValue);
    randomNumber2 = (distribution(rand) % MaxValue);
    CXXGraph::Edge<int> *newEdge = new CXXGraph::Edge<int>(
        index, *(nodes.at(randomNumber1)), *(nodes.at(randomNumber2)));
    edges[index] = newEdge;
  }
  return edges;
}

static std::map<unsigned long, CXXGraph::UndirectedEdge<int> *>
generateRandomUndirectedEdges(
    unsigned long numberOfEdges,
    std::map<unsigned long, CXXGraph::Node<int> *> nodes) {
  thread_local static std::default_random_engine rand;
  thread_local static std::uniform_int_distribution distribution(0, RAND_MAX);

  std::map<unsigned long, CXXGraph::UndirectedEdge<int> *> edges;

  unsigned int randSeed = (unsigned int)time(NULL);
  rand.seed(randSeed);

  int randomNumber1;
  int randomNumber2;
  auto MaxValue = nodes.size();
  for (auto index = 0; index < numberOfEdges; index++) {
    randomNumber1 = (distribution(rand) % MaxValue);
    randomNumber2 = (distribution(rand) % MaxValue);
    CXXGraph::UndirectedEdge<int> *newEdge = new CXXGraph::UndirectedEdge<int>(
        index, *(nodes.at(randomNumber1)), *(nodes.at(randomNumber2)));
    edges[index] = newEdge;
  }
  return edges;
}

static CXXGraph::Graph<int> *readGraph(const std::string &filename) {
  CXXGraph::Graph<int> *graph_ptr = new CXXGraph::Graph<int>();
  auto result =
      graph_ptr->readFromFile(CXXGraph::InputOutputFormat::STANDARD_CSV,
                              "../benchmark/dataset", filename);
  return graph_ptr;
}

// Static Generation

static auto nodes = generateRandomNodes(100000, 2);
static auto edges = generateRandomEdges(100000, nodes);
static auto undirectedEdges = generateRandomUndirectedEdges(100000, nodes);
static auto cit_graph_ptr = readGraph("CitHepPh");

#endif  // __UTILITIES_H__
