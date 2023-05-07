#ifndef __UTILITIES_H__
#define __UTILITIES_H__
#include <time.h>
#include <random>

#include "CXXGraph.hpp"

static std::map<unsigned long, CXXGRAPH::Node<int> *> generateRandomNodes(
    unsigned long numberOfNodes, int MaxValue) {
  thread_local static std::default_random_engine rand;
  thread_local static std::uniform_int_distribution distribution(0, RAND_MAX);

  std::map<unsigned long, CXXGRAPH::Node<int> *> nodes;
  
  unsigned int randSeed = (unsigned int)time(NULL);
  rand.seed(randSeed);
  
  for (auto index = 0; index < numberOfNodes; index++) {
    int randomNumber = (distribution(rand) % MaxValue) + 1;
    CXXGRAPH::Node<int> *newNode =
        new CXXGRAPH::Node<int>(std::to_string(index), randomNumber);
    nodes[index] = newNode;
  }
  return nodes;
}

static std::map<unsigned long, CXXGRAPH::Edge<int> *> generateRandomEdges(
    unsigned long numberOfEdges,
    std::map<unsigned long, CXXGRAPH::Node<int> *> nodes) {
  thread_local static std::default_random_engine rand;
  thread_local static std::uniform_int_distribution distribution(0, RAND_MAX);

  std::map<unsigned long, CXXGRAPH::Edge<int> *> edges;

  unsigned int randSeed = (unsigned int)time(NULL);
  rand.seed(randSeed);

  auto MaxValue = nodes.size();
  for (auto index = 0; index < numberOfEdges; index++) {
    int randomNumber1 = (distribution(rand) % MaxValue);
    int randomNumber2 = (distribution(rand) % MaxValue);
    CXXGRAPH::Edge<int> *newEdge = new CXXGRAPH::Edge<int>(
        index, *(nodes.at(randomNumber1)), *(nodes.at(randomNumber2)));
    edges[index] = newEdge;
  }
  return edges;
}

#endif  // __UTILITIES_H__