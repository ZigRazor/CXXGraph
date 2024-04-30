---
id: how-to-make-a-graph
title: 'Making a Graph'
tags: ['introduction', 'how-to', 'getting started']
---

### Requirements
* C++17 or later
* GCC compiler v7.3.0 OR MSVC compiler supporting C++17 or later

## Creating the Graph

At the heart of CXXGraph is the graph object. The graph object contains the nodes and edges to be worked upon.

Syntax for creating the graph object:

```
Graph<int> myGraph; 
```

Whether a graph is directed or undirected is controlled by the edges added, *not the graph object itself.*

### Adding Nodes and Edges

To begin using the graph, we require nodes to create edges between. Nodes are created individually.

Here we create two nodes...

```
CXXGRAPH::Node<int> node1("1", 1);
CXXGRAPH::Node<int> node2("2", 2);
```

...and then pair them together.

```
std::pair<const CXXGRAPH::Node<int> *, const CXXGRAPH::Node<int> *> pairNode(
      &node1, &node2);
```

These nodes are ready to have an edge created between them. 

**Undirected**

```
CXXGRAPH::UndirectedEdge<int> edge(1, pairNode);
```

**Directed**

```
CXXGRAPH::DirectedEdge<int> edge(1, pairNode);
```

With the edge created, add the edge to the graph object with the `addEdge` function.

```
myGraph.addEdge(edge);
```

*The graph type is determined by the edges added to it.*

To explore the full possibilities of CXXGraph, you can find a rundown of every CXXGraph class, function, and object [here](https://rawcdn.githack.com/ZigRazor/CXXGraph/master/docs/html/annotated.html).

## Manipulating the Graph Object

CXXGraph comes packed with many useful algorithms for your graphs. To use an algorithm, simply apply it to the graph object.

**Traversal Algorithm**

The staple Depth First Search can be added to a graph like so:
```
auto res = myGraph.depth_first_search(node1, node2);
```

**Advanced Algorithm**

Adding a more targeted algorithim is done the same way:
```
auto res = myGraph.dijkstra(node1, node3);
```

For a Minimum Spanning Tree algorithim such as Kruskal's, simply ensure the right args are sent to the graph function. In this case, none, as Kruskal's traverses the entire graph.
```
auto mst = myGraph.kruskal();
```

A full selection of CXXGraph's Algorithms are available [here](https://zigrazor.github.io/CXXGraph/component-explanation/regular-algorithm).


