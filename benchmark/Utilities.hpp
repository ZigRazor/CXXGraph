#ifndef __UTILITIES_H__
#define __UTILITIES_H__
#include <stdlib.h>
#include <time.h>

#include "CXXGraph.hpp"

static std::map<unsigned long, CXXGRAPH::Node<int> *> generateRandomNodes(
    unsigned long numberOfNodes, int MaxValue) {
  std::map<unsigned long, CXXGRAPH::Node<int> *> nodes;
  unsigned int randSeed = (unsigned int)time(NULL);
  srand(randSeed);
  int randomNumber;
  for (auto index = 0; index < numberOfNodes; index++) {
    randomNumber = (rand_r(&randSeed) % MaxValue) + 1;
    CXXGRAPH::Node<int> *newNode =
        new CXXGRAPH::Node<int>(std::to_string(index), randomNumber);
    nodes[index] = newNode;
  }
  return nodes;
}

static std::map<unsigned long, CXXGRAPH::Edge<int> *> generateRandomEdges(
    unsigned long numberOfEdges,
    std::map<unsigned long, CXXGRAPH::Node<int> *> nodes) {
  std::map<unsigned long, CXXGRAPH::Edge<int> *> edges;
  unsigned int randSeed = (unsigned int)time(NULL);
  srand(randSeed);
  int randomNumber1;
  int randomNumber2;
  auto MaxValue = nodes.size();
  for (auto index = 0; index < numberOfEdges; index++) {
    randomNumber1 = (rand_r(&randSeed) % MaxValue);
    randomNumber2 = (rand_r(&randSeed) % MaxValue);
    CXXGRAPH::Edge<int> *newEdge = new CXXGRAPH::Edge<int>(
        index, *(nodes.at(randomNumber1)), *(nodes.at(randomNumber2)));
    edges[index] = newEdge;
  }
  return edges;
}

static std::map<unsigned long, CXXGRAPH::UndirectedEdge<int> *>
generateRandomUndirectedEdges(
    unsigned long numberOfEdges,
    std::map<unsigned long, CXXGRAPH::Node<int> *> nodes) {
  std::map<unsigned long, CXXGRAPH::UndirectedEdge<int> *> edges;
  unsigned int randSeed = (unsigned int)time(NULL);
  srand(randSeed);
  int randomNumber1;
  int randomNumber2;
  auto MaxValue = nodes.size();
  for (auto index = 0; index < numberOfEdges; index++) {
    randomNumber1 = (rand_r(&randSeed) % MaxValue);
    randomNumber2 = (rand_r(&randSeed) % MaxValue);
    CXXGRAPH::UndirectedEdge<int> *newEdge = new CXXGRAPH::UndirectedEdge<int>(
        index, *(nodes.at(randomNumber1)), *(nodes.at(randomNumber2)));
    edges[index] = newEdge;
  }
  return edges;
}

static CXXGRAPH::Graph<int> *readGraph(const std::string &filename) {
  CXXGRAPH::Graph<int> *graph_ptr = new CXXGRAPH::Graph<int>();
  auto result =
      graph_ptr->readFromFile(CXXGRAPH::InputOutputFormat::STANDARD_CSV,
                              "../benchmark/dataset", filename);
  return graph_ptr;
}

// Static Generation

static auto nodes = generateRandomNodes(100000, 2);
static auto edges = generateRandomEdges(100000, nodes);
static auto undirectedEdges = generateRandomUndirectedEdges(100000, nodes);
static auto cit_graph_ptr = readGraph("CitHepPh");

#endif  // __UTILITIES_H__
