#ifndef __UTILITIES_H__
#define __UTILITIES_H__
#include "CXXGraph.hpp"
#include <time.h>
#include <stdlib.h>

static std::map<unsigned long, CXXGRAPH::Node<int> *> generateRandomNodes(unsigned long numberOfNodes, int MaxValue)
{
    std::map<unsigned long, CXXGRAPH::Node<int> *> nodes;
    unsigned int randSeed = (unsigned int)time(NULL);
    srand(randSeed);
    for (auto index = 0; index < numberOfNodes; index++)
    {
        int randomNumber = (rand_r(&randSeed) % MaxValue) + 1;
        CXXGRAPH::Node<int> *newNode = new CXXGRAPH::Node<int>(std::to_string(index), randomNumber);
        nodes[index] = newNode;
    }
    return nodes;
}

static std::map<unsigned long, CXXGRAPH::Edge<int> *> generateRandomEdges(unsigned long numberOfEdges, std::map<unsigned long, CXXGRAPH::Node<int> *> nodes)
{
    std::map<unsigned long, CXXGRAPH::Edge<int> *> edges;
    unsigned int randSeed = (unsigned int)time(NULL);
    srand(randSeed);
    auto MaxValue = nodes.size();
    for (auto index = 0; index < numberOfEdges; index++)
    {
        int randomNumber1 = (rand_r(&randSeed) % MaxValue);
        int randomNumber2 = (rand_r(&randSeed) % MaxValue);
        CXXGRAPH::Edge<int> *newEdge = new CXXGRAPH::Edge<int>(index, *(nodes.at(randomNumber1)), *(nodes.at(randomNumber2)));
        edges[index] = newEdge;
    }
    return edges;
}

#endif // __UTILITIES_H__