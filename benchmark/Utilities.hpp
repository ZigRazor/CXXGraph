#ifndef __UTILITIES_H__
#define __UTILITIES_H__
#include "CXXGraph.hpp"
#include <time.h>
#include <stdlib.h>

static std::map<unsigned long, CXXGRAPH::Node<int> *> generateRandomNodes(unsigned long numberOfNodes, int MaxValue)
{
    std::map<unsigned long, CXXGRAPH::Node<int> *> nodes;
    srand((unsigned)time(NULL));
    int randomNumber;
    for (auto index = 0; index < numberOfNodes; index++)
    {
        randomNumber = (rand_r() % MaxValue) + 1;
        CXXGRAPH::Node<int> *newNode = new CXXGRAPH::Node<int>(std::to_string(index), randomNumber);
        nodes[index] = newNode;
    }
    return nodes;
}

static std::map<unsigned long, CXXGRAPH::Edge<int> *> generateRandomEdges(unsigned long numberOfEdges, std::map<unsigned long, CXXGRAPH::Node<int> *> nodes)
{
    std::map<unsigned long, CXXGRAPH::Edge<int> *> edges;
    srand((unsigned)time(NULL));
    int randomNumber1;
    int randomNumber2;
    auto MaxValue = nodes.size();
    for (auto index = 0; index < numberOfEdges; index++)
    {
        randomNumber1 = (rand_r() % MaxValue);
        randomNumber2 = (rand_r() % MaxValue);
        CXXGRAPH::Edge<int> *newEdge = new CXXGRAPH::Edge<int>(index, *(nodes.at(randomNumber1)), *(nodes.at(randomNumber2)));
        edges[index] = newEdge;
    }
    return edges;
}

static std::map<unsigned long, CXXGRAPH::UndirectedEdge<int> *> generateRandomUndirectedEdges(unsigned long numberOfEdges, std::map<unsigned long, CXXGRAPH::Node<int> *> nodes)
{
    std::map<unsigned long, CXXGRAPH::UndirectedEdge<int> *> edges;
    srand((unsigned)time(NULL));
    int randomNumber1;
    int randomNumber2;
    auto MaxValue = nodes.size();
    for (auto index = 0; index < numberOfEdges; index++)
    {
        randomNumber1 = (rand_r() % MaxValue);
        randomNumber2 = (rand_r() % MaxValue);
        CXXGRAPH::UndirectedEdge<int> *newEdge = new CXXGRAPH::UndirectedEdge<int>(index, *(nodes.at(randomNumber1)), *(nodes.at(randomNumber2)));
        edges[index] = newEdge;
    }
    return edges;
}

static CXXGRAPH::Graph<int> *readGraph(const std::string &filename)
{
    CXXGRAPH::Graph<int> *graph_ptr = new CXXGRAPH::Graph<int>();
    auto result = graph_ptr->readFromFile(CXXGRAPH::InputOutputFormat::STANDARD_CSV, "../benchmark/dataset", filename);
    return graph_ptr;
}

#endif // __UTILITIES_H__
