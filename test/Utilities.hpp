#ifndef __UTILITIES_H__
#define __UTILITIES_H__
#include <time.h>

#include <memory>
#include <random>

#include "CXXGraph.hpp"
#include "../include/Utility/PointerHash.hpp"

template <typename T>
using shared = std::shared_ptr<T>;
using std::make_shared;

static std::map<unsigned long, shared<CXXGraph::Node<int>>> generateRandomNodes(
    unsigned long numberOfNodes, int MaxValue) {
  thread_local static std::default_random_engine rand;
  thread_local static std::uniform_int_distribution distribution(0, RAND_MAX);

  std::map<unsigned long, shared<CXXGraph::Node<int>>> nodes;

  unsigned int randSeed = (unsigned int)time(NULL);
  rand.seed(randSeed);

  for (auto index = 0; index < numberOfNodes; index++) {
    int randomNumber = (distribution(rand) % MaxValue) + 1;
    auto newNode =
        make_shared<CXXGraph::Node<int>>(std::to_string(index), randomNumber);
    nodes[index] = newNode;
  }
  return nodes;
}

static std::map<unsigned long, shared<CXXGraph::Edge<int>>> generateRandomEdges(
    unsigned long numberOfEdges,
    std::map<unsigned long, shared<CXXGraph::Node<int>>> nodes) {
  thread_local static std::default_random_engine rand;
  thread_local static std::uniform_int_distribution distribution(0, RAND_MAX);

  std::map<unsigned long, shared<CXXGraph::Edge<int>>> edges;

  unsigned int randSeed = (unsigned int)time(NULL);
  rand.seed(randSeed);

  auto MaxValue = nodes.size();
  for (auto index = 0; index < numberOfEdges; index++) {
    int randomNumber1 = (distribution(rand) % MaxValue);
    int randomNumber2 = (distribution(rand) % MaxValue);
    auto newEdge = make_shared<CXXGraph::Edge<int>>(
        index, *(nodes.at(randomNumber1)), *(nodes.at(randomNumber2)));
    edges[index] = newEdge;
  }
  return edges;
}

#endif  // __UTILITIES_H__
