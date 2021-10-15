<img style="float: right;" align="left" src="https://github.com/ZigRazor/CXXGraph/blob/master/Icon.png">

# CXXGraph

<img src="https://img.shields.io/badge/c++%20-%2300599C.svg?&style=for-the-badge&logo=c%2B%2B&ogoColor=white"/> <img src="https://img.shields.io/badge/github%20-%23121011.svg?&style=for-the-badge&logo=github&logoColor=white"/>

[![codecov](https://codecov.io/gh/ZigRazor/CXXGraph/branch/master/graph/badge.svg?token=773AQ2H9RQ)](https://codecov.io/gh/ZigRazor/CXXGraph)
[![CodeFactor](https://www.codefactor.io/repository/github/zigrazor/cxxgraph/badge)](https://www.codefactor.io/repository/github/zigrazor/cxxgraph)

[![GitHub license](https://img.shields.io/github/license/ZigRazor/CXXGraph.svg)](https://github.com/ZigRazor/CXXGraph/blob/master/LICENSE) [![GitHub release](https://img.shields.io/github/release/ZigRazor/CXXGraph.svg)](https://GitHub.com/ZigRazor/CXXGraph/releases/)

![LGTM Alerts](https://img.shields.io/lgtm/alerts/github/ZigRazor/CXXGraph?style=plastic)
![LGTM Grade](https://img.shields.io/lgtm/grade/cpp/github/ZigRazor/CXXGraph?style=plastic)

[![Generic badge](https://img.shields.io/badge/Required-G++7.3.0-Green.svg)](https://shields.io/) [![Generic badge](https://img.shields.io/badge/required-C++17-Green.svg)](https://shields.io/) [![Generic badge](https://img.shields.io/badge/Required-CMake3.9-Green.svg)](https://shields.io/)

[![Generic badge](https://img.shields.io/badge/Build-Passed-Green.svg)](https://shields.io/) [![Generic badge](https://img.shields.io/badge/UnitTest-Passed-Green.svg)](https://shields.io/)

Share on [![Tweet](https://img.shields.io/twitter/url/http/shields.io.svg?style=social)](https://twitter.com/intent/tweet?text=Header-Only%20C++%20Library%20for%20Graph%20Representation%20and%20Algorithms%204&url=https://github.com/ZigRazor/CXXGraph&hashtags=cpp,headeronly,library,opensource,developers)
<br/><br/>
<br/><br/>
<br/><br/>

## Introduction
**CXXGraph** is a small library, header only, that manages the Graph and it's algorithms in **C++**. In other words a "Comprehensive C++ Graph Library".
An alternative to [Boost Graph Library (BGL)](https://www.boost.org/doc/libs/1_77_0/libs/graph/doc/index.html).

## Table of Contents
- [CXXGraph](#cxxgraph)
  * [Introduction](#introduction)
  * [Table of Contents](#table-of-contents)
  * [Install and Uninstall](#install-and-uninstall)
    + [Install Linux Tarballs](#install-linux-tarballs)
    + [Install RPM](#install-rpm)
    + [Install DEB](#install-deb)
    + [Install From Source](#install-from-source)
  * [Classes Explanation](#classes-explanation)
  * [Requirements](#requirements)
  * [How to use](#how-to-use)
  * [Example](#example)
  * [Unit-Test Execution](#unit-test-execution)
    + [Google Test Installation](#google-test-installation)
    + [How to Compile Test](#how-to-compile-test)
    + [How to Run Test](#how-to-run-test)
  * [Benchmark Execution](#benchmark-execution)
    + [Google Benchmark Installation](#google-benchmark-installation)
    + [How to Compile Benchmark](#how-to-compile-benchmark)
    + [How to Run Benchmark](#how-to-run-benchmark)
    + [Benchmark Results](#benchmark-results)
  * [Packaging](#packaging)
    + [Tarballs](#tarballs)
    + [RPM](#rpm)
      - [(Fedora/CentOS/RedHat)](#-fedora-centos-redhat-)
    + [DEB](#deb)
      - [(Debian/Ubuntu)](#-debian-ubuntu-)
  * [Algorithm Explanation](#algorithm-explanation)
      - [Dijkstra](#dijkstra)
      - [Dial](#dial)
      - [BFS](#bfs)
      - [DFS](#dfs)
      - [Cycle Detection](#cycle-detection)
      - [Bellman-Ford](#bellman-ford)
      - [Floyd Warshall](#floyd-warshall)
  * [Partition Algorithm Explanation](#partition-algorithm-explanation)
    + [Vertex-Cut](#vertex-cut)
    + [Greedy Vertex-Cut](#greedy-vertex-cut)
    + [Graph Slicing based on connectivity](#graph-slicing-based-on-connectivity)
  * [How to contribute](#how-to-contribute)
  * [Site](#site)
  * [Contact](#contact)
  * [Support](#support)
  * [References](#references)
  * [Credits](#credits)
  * [Hacktoberfest 2k21](#hacktoberfest-2k21)
  * [We are Looking for...](#we-are-looking-for)
  * [Other Details](#other-details)


## Install and Uninstall

### Install Linux Tarballs
On Unix/Linux system you need to execute the following command to install:

`$ sudo tar xjf CXXGraph-{version}.tar.bz2`

to uninstall:

`$ sudo rm -f /usr/include/Graph.hpp /usr/include/CXXGraph*`

### Install RPM
On Fedora/CentOS/RedHat system you need to execute the following command to install:

`$ sudo rpm -ivh CXXGraph-{version}.noarch.rpm`

to uninstall:

`$ sudo rpm -e CXXGraph-{version}`

### Install DEB
On Debian/Ubuntu system you need to execute the following command to install:

`$ sudo dpkg -i CXXGraph_{version}.deb`

to uninstall:

`$ sudo apt-get remove CXXGraph`

### Install From Source
You can install from source the library using CMake. After the compilation phase, you can use:

`$ sudo make install`

to install the library.

## Classes Explanation

The Classes Explanation can be found in the [Doxygen Documentation](https://rawcdn.githack.com/ZigRazor/CXXGraph/master/docs/html/index.html), in the [Classes Section](https://rawcdn.githack.com/ZigRazor/CXXGraph/master/docs/html/classes.html)

## Requirements
The minimun C++ standard required is **C++17** and a G++ compiler version greater than 7.3.0.

## How to use
The use of the library is very simple, **just put the header file where you need!**

## Example
Work in Progess

## Unit-Test Execution
The Unit-Test required the CMake version greater than 3.9 and the **google test**  library.

### Google Test Installation

[GoogleTest](https://github.com/google/googletest)

```
git clone https://github.com/google/googletest.git
cd googletest        # Main directory of the cloned repository.
mkdir -p build       # Create a directory to hold the build output.
cd build
cmake ..             # Generate native build scripts for GoogleTest.
make                 # Compile
sudo make install    # Install in /usr/local/ by default
```

### How to Compile Test
From the base directory:
```
mkdir -p build       # Create a directory to hold the build output.
cd build             # Enter the build folder
cmake ..             # Generate native build scripts for GoogleTest.
make                 # Compile
```

### How to Run Test
After the compilation, you can run the executable that is under the "build" directory with the name "test_exe", with the simple command `./test_exe`.

## Benchmark Execution
The Benchmark required the CMake version greater than 3.9 and the **google test** and the **google benchmark** library.

### Google Benchmark Installation

[Google Benchmark](https://github.com/google/benchmark)

```
# Check out the library.
$ git clone https://github.com/google/benchmark.git
# Benchmark requires Google Test as a dependency. Add the source tree as a subdirectory.
$ git clone https://github.com/google/googletest.git benchmark/googletest
# Go to the library root directory
$ cd benchmark
# Make a build directory to place the build output.
$ cmake -E make_directory "build"
# Generate build system files with cmake.
$ cmake -E chdir "build" cmake -DCMAKE_BUILD_TYPE=Release ../
# or, starting with CMake 3.13, use a simpler form:
# cmake -DCMAKE_BUILD_TYPE=Release -S . -B "build"
# Build the library.
$ cmake --build "build" --config Release
# install library
$ sudo cmake --build "build" --config Release --target install
```

### How to Compile Benchmark
From the base directory:
```
mkdir -p build             # Create a directory to hold the build output.
cd build                   # Enter the build folder
cmake -DBENCHMARK=ON ..    # Generate native build scripts for GoogleTest.
make                       # Compile
```

### How to Run Benchmark
After the compilation, you can run the executable that is under the "build" directory with the name "benchmark", with the simple command `./benchmark`.

### Benchmark Results

You can check benchmark result at this [link](https://zigrazor.github.io/CXXGraph/dev/bench/)

## Packaging

### Tarballs
To create tarballs package you need to follow the following steps:
```
# Enter Packaging Directory
$ cd packaging
# execute the script to generate tarballs
$ ./tarballs.sh
```

### RPM
#### (Fedora/CentOS/RedHat)
To create rpm package you need to follow the following steps:
```
# Enter Packaging Directory
$ cd packaging/rpm
# execute the script to generate tarballs
$ ./make_rpm.sh
```

### DEB
#### (Debian/Ubuntu)
To create deb package you need to follow the following steps:
```
# Enter Packaging Directory
$ cd packaging/deb
# execute the script to generate tarballs
$ ./make_deb.sh
```

## Algorithm Explanation

#### Dijkstra
[Graph Dijkstras Shortest Path Algorithm(Dijkstra's Shortest Path)](https://en.wikipedia.org/wiki/Dijkstra%27s_algorithm)
**Dijkstra's Algorithm** is used to find the shortest path from a source node to all other reachable nodes in the graph. The algorithm initially assumes all the nodes are unreachable from the given source node so we mark the distances of all nodes as infinity.
(infinity) from source node (INF / infinity denotes unable to reach).

#### Dial
Dial specialization of dijkstra’s algorithm.

When edge weights are small integers (bounded by a parameter *C*), specialized queues which take advantage of this fact can be used to speed up Dijkstra's algorithm. The first algorithm of this type was Dial's algorithm (Dial 1969) for graphs with positive integer edge weights, which uses a bucket queue to obtain a running time
*O(|E|+|V|C)*.([source wikipedia](https://en.wikipedia.org/wiki/Dijkstra%27s_algorithm#Specialized_variants))

Below is complete algorithm:
 1. Maintains some buckets, numbered 0, 1, 2,…,wV.
 2. Bucket k contains all temporarily labeled nodes with distance equal to k.
 3. Nodes in each bucket are represented by list of vertices.
 4. Buckets 0, 1, 2,..wV are checked sequentially until the first non-empty bucket is found. Each node contained in the first non-empty bucket has the minimum distance label by definition.
 5. One by one, these nodes with minimum distance label are permanently labeled and deleted from the bucket during the scanning process.
 6. Thus operations involving vertex include:
    - Checking if a bucket is empty
    - Adding a vertex to a bucket
    - Deleting a vertex from a bucket.
 7. The position of a temporarily labeled vertex in the buckets is updated accordingly when the distance label of a vertex changes.
 8. Process repeated until all vertices are permanently labeled (or distances of all vertices are finalized).

At this [link](https://ocw.mit.edu/courses/sloan-school-of-management/15-082j-network-optimization-fall-2010/animations/MIT15_082JF10_av07.pdf) you can find a step-by-step illustrations.

### Prim's Algorithm
[Prim's Algorithm](https://en.wikipedia.org/wiki/Prim%27s_algorithm)
Prim's Algorithm is is a greedy algorithm that finds a minimum spanning tree for a weighted undirected graph. This means it finds a subset of the edges that forms a tree that includes every vertex, where the total weight of all the edges in the tree is minimized. The algorithm operates by building this tree one vertex at a time, from an arbitrary starting vertex, at each step adding the cheapest possible connection from the tree to another vertex.

Steps:

1. Initialize a tree with a single vertex, chosen arbitrarily from the graph.
2. Grow the tree by one edge: of the edges that connect the tree to vertices not yet in the tree, find the minimum-weight edge, and transfer it to the tree.
3. Repeat step 2 (until all vertices are in the tree).

#### BFS
(Breadth First Search)
[Breadth First Search Algorithm(Breadth First Search)](https://en.wikipedia.org/wiki/Breadth-first_search)
**Breadth First Search**, also quoted as **BFS**, is a Graph Traversal Algorithm. Time Complexity O(|V| + |E|) where V are the number of vertices and E are the number of edges in the graph.
Applications of Breadth First Search are :

 1. Finding shortest path between two vertices say u and v, with path length measured by number of edges (an advantage over depth first search algorithm)
 2. Ford-Fulkerson Method for computing the maximum flow in a flow network.
 3. Testing bipartiteness of a graph.
 4. Cheney's Algorithm, Copying garbage collection.

  And there are many more...

#### DFS
(Depth First Search)
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

#### Bellman-Ford
[Bellman-Ford Algorithm](https://en.wikipedia.org/wiki/Bellman%E2%80%93Ford_algorithm) can be used to find the shortest distance between a source and a target node. Time Complexity O(|V| . |E|) where V is number of vertices and E is number of edges in graph which is higher than Dijkstra's shortest path algorithm. The time complexity of dijkstra's algorithm is O(|E| + |V| log |v| ). The advantage of bellman-ford over dijkstra is that it can handle graphs with negative edge weights. Further, if the graph contains a negative weight cycle then the algorithm can detect and report the presense of negative cycle.

[This video](https://www.youtube.com/watch?v=24HziTZ8_xo) gives a nice overview of the algorithm implementation. This [MIT lecture](https://courses.csail.mit.edu/6.006/spring11/lectures/lec15.pdf) gives a proof of Bellman-Ford's correctness & its ability to detect negative cycles.
Applications:
- Distance‐vector routing protocol
- Routing Information Protocol (RIP)
- Interior Gateway Routing Protocol (IGRP)

#### Floyd Warshall
[Floyd Warshall Algorithm](https://en.wikipedia.org/wiki/Floyd%E2%80%93Warshall_algorithm)

We initialize the solution matrix same as the input graph matrix as a first step. Then we update the solution matrix by considering all vertices as an intermediate vertex. The idea is to one by one pick all vertices and updates all shortest paths which include the picked vertex as an intermediate vertex in the shortest path. When we pick vertex number k as an intermediate vertex, we already have considered vertices {0, 1, 2, .. k-1} as intermediate vertices. For every pair (i, j) of the source and destination vertices respectively, there are two possible cases.
1) k is not an intermediate vertex in shortest path from i to j. We keep the value of dist[i][j] as it is.
2) k is an intermediate vertex in shortest path from i to j. We update the value of dist[i][j] as dist[i][k] + dist[k][j] if dist[i][j] > dist[i][k] + dist[k][j]

## Partition Algorithm Explanation

### Vertex-Cut

A vertex-cut partitioning divides edges of a graph into equal size partitions. The vertices that hold the endpoints of an edge are also placed in the same partition as the edge itself. However, the vertices are not unique across partitions and might have to be replicated (cut), due to the distribution of their edge across different partitions.

Replication factor quantifies how many vertexes are replicated over computers compared with the the number of vertexes of the original input graph.

### Greedy Vertex-Cut
This Algorithm is a simple vertex-cut in Round-Robin fashion.
It takes the original graph edges and assign them to the partitions, dividing it in equal(or similar) size. This algorithm does not take care of optimization in vertex replication ( Replication Factor) but only balance the edge in the partitions.

### Graph Slicing based on connectivity
Mathematical definition of the problem:
Let G be the set of nodes in a graph and n be a given node in that set.
Let C be the non-strict subset of G containing both n and all nodes reachable
from n, and let C' be its complement. There's a third set M, which is the
non-strict subset of C containing all nodes that are reachable from any node in C'.
The problem consists of finding all nodes that belong to C but not to M.

Currently implemented Algorithm:
- Use DFS to find all nodes reachable from n. These are elements of set C.
- Initialize C' to be complement of C (i.e. all nodes - nodes that are in C)
- For all nodes in C', apply DFS and get the list of reachable nodes. This is set M.
- Finally removes nodes from C that belong to M. This is our solution.

Application:

This algorithm is used in garbage collection systems to decide which other objects need to be released, given that one object is about to be released.

## How to contribute
[![GitHub contributors](https://img.shields.io/github/contributors/ZigRazor/CXXGraph.svg)](https://GitHub.com/ZigRazor/CXXGraph/graphs/contributors/)
If you want give your support you can create a ***pull request***   [![GitHub pull-requests](https://img.shields.io/github/issues-pr/ZigRazor/CXXGraph.svg)](https://GitHub.com/ZigRazor/CXXGraph/pull/) or report an ***issue***  [![GitHub issues](https://img.shields.io/github/issues/ZigRazor/CXXGraph.svg)](https://GitHub.com/ZigRazor/CXXGraph/issues/).
If you want to change the code, or fix issue, or implement a new feature please read our [CONTRIBUTING Guide](https://github.com/ZigRazor/CXXGraph/blob/master/CONTRIBUTING.md)

## Site

[CXXGraph Site](https://zigrazor.github.io/CXXGraph/)

## Contact
E-Mail : zigrazor@gmail.com

[GitHub Profile](https://github.com/ZigRazor) ![Profile views](https://gpvc.arturio.dev/ZigRazor)

![ZigRazor's github stats](https://github-readme-stats.vercel.app/api?username=ZigRazor&show_icons=true&title_color=fff&icon_color=79ff97&text_color=9f9f9f&bg_color=151515)

## Support
To support me just add ***Star*** the project  [![GitHub stars](https://img.shields.io/github/stars/ZigRazor/CXXGraph.svg?style=social&label=Star&maxAge=2592000)](https://GitHub.com/ZigRazor/CXXGraph/stargazers/) or ***follow me***  [![GitHub followers](https://img.shields.io/github/followers/ZigRazor.svg?style=social&label=Follow&maxAge=2592000)](https://github.com/ZigRazor?tab=followers)

To get updated ***watch*** the project  [![GitHub watchers](https://img.shields.io/github/watchers/ZigRazor/CXXGraph.svg?style=social&label=Watch&maxAge=2592000)](https://GitHub.com/ZigRazor/CXXGraph/watchers/)

## References
We are referenced by:
- [awesome-hpp](https://github.com/p-ranav/awesome-hpp)
- [cppreference.com](https://en.cppreference.com/w/cpp/links/libs)
- [awesome-cpp](https://github.com/fffaraz/awesome-cpp)

## Credits

Thanks to the community of [TheAlgorithms](https://github.com/TheAlgorithms) for some algorithms ispiration.

Thanks to [GeeksForGeeks](https://www.geeksforgeeks.org/) for some algorithms inspiration.

## Hacktoberfest 2k21

We participate at Hacktoberfest 2021, if you want to contribute, you can take an [issue](https://github.com/ZigRazor/CXXGraph/issues) and solve it, or if you want to add a functionalities just open a PR with the label `hacktoberfest`.

Happy Hack!

## We are Looking for...

**We are looking for developers and committer**, also at *first experience*, we will guide you step by step to the open-source world!
If you are interested, please contact us at zigrazor@gmail.com or contribute to this project. We are waiting for you!

## Other Details

View the [Estimated Value of the Project](https://www.openhub.net/p/CXXGraph/estimated_cost)

![](https://github.com/ZigRazor/CXXGraph/blob/master/Icon2.png)
