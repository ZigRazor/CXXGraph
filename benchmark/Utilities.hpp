#ifndef __UTILITIES_H__
#define __UTILITIES_H__
#include "CXXGraph.hpp"
#include <time.h>
#include <stdlib.h>

static std::unordered_map<unsigned long, CXXGRAPH::Node<int> *> generateRandomNodes(unsigned long numberOfNodes, int MaxValue)
{
    std::unordered_map<unsigned long, CXXGRAPH::Node<int> *> nodes;
    srand((unsigned)time(NULL));
    int randomNumber;
    for (auto index = 0; index < numberOfNodes; index++)
    {
        randomNumber = (rand() % MaxValue) + 1;
        CXXGRAPH::Node<int> *newNode = new CXXGRAPH::Node<int>(std::to_string(index), randomNumber);
        nodes[index] = newNode;
    }
    return nodes;
}

static std::unordered_map<unsigned long, CXXGRAPH::Edge<int> *> generateRandomEdges(unsigned long numberOfEdges, std::unordered_map<unsigned long, CXXGRAPH::Node<int> *> nodes)
{
    std::unordered_map<unsigned long, CXXGRAPH::Edge<int> *> edges;
    srand((unsigned)time(NULL));
    int randomNumber1;
    int randomNumber2;
    auto MaxValue = nodes.size();
    for (auto index = 0; index < numberOfEdges; index++)
    {
        randomNumber1 = (rand() % MaxValue);
        randomNumber2 = (rand() % MaxValue);
        CXXGRAPH::Edge<int> *newEdge = new CXXGRAPH::Edge<int>(index, *(nodes.at(randomNumber1)), *(nodes.at(randomNumber2)));
        edges[index] = newEdge;
    }
    return edges;
}

#endif // __UTILITIES_H__