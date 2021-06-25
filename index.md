# CXXGraph

<img src="https://img.shields.io/badge/c++%20-%2300599C.svg?&style=for-the-badge&logo=c%2B%2B&ogoColor=white"/> <img src="https://img.shields.io/badge/github%20-%23121011.svg?&style=for-the-badge&logo=github&logoColor=white"/>

[![GitHub license](https://img.shields.io/github/license/ZigRazor/CXXGraph.svg)](https://github.com/ZigRazor/CXXGraph/blob/master/LICENSE) [![GitHub release](https://img.shields.io/github/release/ZigRazor/CXXGraph.svg)](https://GitHub.com/ZigRazor/CXXGraph/releases/)

[![Generic badge](https://img.shields.io/badge/Required-G++7.3.0-Green.svg)](https://shields.io/) [![Generic badge](https://img.shields.io/badge/required-C++17-Green.svg)](https://shields.io/) [![Generic badge](https://img.shields.io/badge/Required-CMake3.9-Green.svg)](https://shields.io/)

[![Generic badge](https://img.shields.io/badge/Build-Passed-Green.svg)](https://shields.io/) [![Generic badge](https://img.shields.io/badge/UnitTest-Passed-Green.svg)](https://shields.io/)

## Introduction
**CXXGraph** is a small library, header only, that manages the Graph and it's algorithm in **C++**

## Algorithm Explanation

#### Dijkstra
[Graph Dijkstras Shortest Path Algorithm(Dijkstra's Shortest Path)](https://en.wikipedia.org/wiki/Dijkstra%27s_algorithm)
**Dijkstra's Algorithm** is used to find the shortest path from a source node to all other reachable nodes in the graph. The algorithm initially assumes all the nodes are unreachable from the given source node so we mark the distances of all nodes as infinity.
(infinity) from source node (INF / infinity denotes unable to reach).

#### BFS (Breadth First Search)
[Breadth First Search Algorithm(Breadth First Search)](https://en.wikipedia.org/wiki/Breadth-first_search)
**Breadth First Search**, also quoted as **BFS**, is a Graph Traversal Algorithm. Time Complexity O(|V| + |E|) where V are the number of vertices and E are the number of edges in the graph.
Applications of Breadth First Search are :

 1. Finding shortest path between two vertices say u and v, with path length measured by number of edges (an advantage over depth first search algorithm)
 2. Ford-Fulkerson Method for computing the maximum flow in a flow network.
 3. Testing bipartiteness of a graph.
 4. Cheney's Algorithm, Copying garbage collection.
 
  And there are many more...

#### DFS (Depth First Search)
[Depth First Search Algorithm (Depth First Search)](https://en.wikipedia.org/wiki/Depth-first_search)
**Depth First Search**, also quoted as **DFS**, is a Graph Traversal Algorithm. Time Complexity O(|V| + |E|) where V is number of vertices and E is number of edges in graph.
Application of Depth First Search are:
  1. Finding connected components
  2. Finding 2-(edge or vertex)-connected components.
  3. Finding 3-(edge or vertex)-connected components.
  4. Finding the bridges of a graph.
  5. Generating words in order to plot the limit set of a group.
  6. Finding strongly connected components.
 
  And there are many more...

#### Cycle Detection
[Cycle (graph theory)](https://en.wikipedia.org/wiki/Cycle_(graph_theory))
   
The existence of a cycle in directed and undirected graphs can be determined by whether depth-first search (DFS) finds an edge that points to an ancestor of the current vertex (it contains a back edge). All the back edges which DFS skips over are part of cycles. In an undirected graph, the edge to the parent of a node should not be counted as a back edge, but finding any other already visited vertex will indicate a back edge. In the case of undirected graphs, only O(n) time is required to find a cycle in an n-vertex graph, since at most n − 1 edges can be tree edges.

Many topological sorting algorithms will detect cycles too, since those are obstacles for topological order to exist. Also, if a directed graph has been divided into strongly connected components, cycles only exist within the components and not between them, since cycles are strongly connected.

For directed graphs, distributed message based algorithms can be used. These algorithms rely on the idea that a message sent by a vertex in a cycle will come back to itself.    Distributed cycle detection algorithms are useful for processing large-scale graphs using a distributed graph processing system on a computer cluster (or supercomputer).

Applications of cycle detection include the use of wait-for graphs to detect deadlocks in concurrent systems.

WORK IN PROGRESS

## Classes Explanation

WORK IN PROGRESS

## Requirements
The minimun C++ standard required is **C++17** and a G++ compiler version greater than 7.3.0.

## How to use
The use of the library is very simple, **just put the header file where you need!**

## Unit-Test Execution
The Unit-Test required the CMake version greater than 3.9 and the **google test** library.

#### How to Compile
-   If not exist create a directory "build" under the base directory.
-   Enter the directory
-   execute command `cmake ..`
-   if all is succesfull execute the command `make`

### How to Run
After the compilation, you can run the executable that is under the "build" directory with the name "test_exe", with the simple command `./test_exe`.

## Example
Work in Progess

## How to contribute [![GitHub contributors](https://img.shields.io/github/contributors/ZigRazor/CXXGraph.svg)](https://GitHub.com/ZigRazor/CXXGraph/graphs/contributors/)
If you want give your support you can create a ***pull request***   [![GitHub pull-requests](https://img.shields.io/github/issues-pr/ZigRazor/CXXGraph.svg)](https://GitHub.com/ZigRazor/CXXGraph/pull/) or report an ***issue***  [![GitHub issues](https://img.shields.io/github/issues/ZigRazor/CXXGraph.svg)](https://GitHub.com/ZigRazor/CXXGraph/issues/).

## Contact
E-Mail : zigrazor@gmail.com

[GitHub Profile](https://github.com/ZigRazor) ![Profile views](https://gpvc.arturio.dev/ZigRazor)

![ZigRazor's github stats](https://github-readme-stats.vercel.app/api?username=ZigRazor&show_icons=true&title_color=fff&icon_color=79ff97&text_color=9f9f9f&bg_color=151515)

## Support
To support me just add ***Star*** the project  [![GitHub stars](https://img.shields.io/github/stars/ZigRazor/CXXGraph.svg?style=social&label=Star&maxAge=2592000)](https://GitHub.com/ZigRazor/CXXGraph/stargazers/) or ***follow me***  [![GitHub followers](https://img.shields.io/github/followers/ZigRazor.svg?style=social&label=Follow&maxAge=2592000)](https://github.com/ZigRazor?tab=followers)

To get updated ***watch*** the project  [![GitHub watchers](https://img.shields.io/github/watchers/ZigRazor/CXXGraph.svg?style=social&label=Watch&maxAge=2592000)](https://GitHub.com/ZigRazor/CXXGraph/watchers/)


## Credits

Thanks to the community of [TheAlgorithms](https://github.com/TheAlgorithms) for some algorithm ispiration.
