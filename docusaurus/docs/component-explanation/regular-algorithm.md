---
id: regular-algorithm
title: 'Algorithms Explanation'
tags: ['algorithm', 'partition-algorithm', 'components', 'graphing-components', 'graphing']
---
### Dijsktra
Graph Dijkstras Shortest Path Algorithm (Dijkstra’s Shortest Path). [Dijkstra’s Algorithm](https://www.interviewbit.com/blog/find-shortest-path-dijkstras-algorithm/) is used to find the shortest path from a source node to all other reachable nodes in the graph. The algorithm initially assumes all the nodes are unreachable from the given source node so we mark the distances of all nodes as infinity. (infinity) from source node (INF / infinity denotes unable to reach).

### Dial
Dial specialization of dijkstra’s algorithm.

When edge weights are small integers (bounded by a parameter C), specialized queues which take advantage of this fact can be used to speed up Dijkstra’s algorithm. The first algorithm of this type was Dial’s algorithm (Dial 1969) for graphs with positive integer edge weights, which uses a bucket queue to obtain a running time O(|E|+|V|C).([source wikipedia](https://en.wikipedia.org/wiki/Dijkstra%27s_algorithm#Specialized_variants))

Below is complete algorithm:

    Maintains some buckets, numbered 0, 1, 2,…,wV.
    Bucket k contains all temporarily labeled nodes with distance equal to k.
    Nodes in each bucket are represented by list of vertices.
    Buckets 0, 1, 2,..wV are checked sequentially until the first non-empty bucket is found. Each node contained in the first non-empty bucket has the minimum distance label by definition.
    One by one, these nodes with minimum distance label are permanently labeled and deleted from the bucket during the scanning process.
    Thus operations involving vertex include:
        Checking if a bucket is empty
        Adding a vertex to a bucket
        Deleting a vertex from a bucket.
    The position of a temporarily labeled vertex in the buckets is updated accordingly when the distance label of a vertex changes.
    Process repeated until all vertices are permanently labeled (or distances of all vertices are finalized).

At this [link](https://ocw.mit.edu/courses/15-082j-network-optimization-fall-2010/pages/animations/) you can find a step-by-step illustrations.

### Prim's Algorithm
[Prim’s Algorithm](https://en.wikipedia.org/wiki/Prim%27s_algorithm) is a greedy algorithm that finds a minimum spanning tree for a weighted undirected graph. This means it finds a subset of the edges that forms a tree that includes every vertex, where the total weight of all the edges in the tree is minimized. The algorithm operates by building this tree one vertex at a time, from an arbitrary starting vertex, at each step adding the cheapest possible connection from the tree to another vertex.

Steps:
1. Initialize a tree with a single vertex, chosen arbitrarily from the graph.
2. Grow the tree by one edge: of the edges that connect the tree to vertices not yet in the tree, find the minimum-weight edge, and transfer it to the tree.
3. Repeat step 2 (until all vertices are in the tree).

### BFS
[Breadth First Search](https://en.wikipedia.org/wiki/Breadth-first_search), also quoted as BFS, is a Graph Traversal Algorithm. Time Complexity O(|V| + |E|) where V are the number of vertices and E are the number of edges in the graph. Applications of Breadth First Search are :

1. Finding shortest path between two vertices say u and v, with path length measured by number of edges (an advantage over depth first search algorithm)
2. Ford-Fulkerson Method for computing the maximum flow in a flow network.
3. Testing bipartiteness of a graph.
4. Cheney’s Algorithm, Copying garbage collection.
And there are many more…

### DFS
[Depth First Search](https://en.wikipedia.org/wiki/Depth-first_search), also quoted as DFS, is a Graph Traversal Algorithm. Time Complexity O(|V| + |E|) where V is number of vertices and E is number of edges in graph. Application of Depth First Search are:

1. Finding connected components
2. Finding 2-(edge or vertex)-connected components.
3. Finding 3-(edge or vertex)-connected components.
4. Finding the bridges of a graph.
5. Generating words in order to plot the limit set of a group.
6. Finding strongly connected components.
And there are many more…

### Best First Search
[Best First Search](https://en.wikipedia.org/wiki/Best-first_search) is a class of search algorithms which traverses the graph by exploring the most promising node chosen according to an evaluation function. The worst-case time complexity is O(n * log n) where n is the number of nodes in the graph.

### Cycle Detection
[Cycle Detection](https://en.wikipedia.org/wiki/Cycle_(graph_theory))

The existence of a cycle in directed and undirected graphs can be determined by whether depth-first search (DFS) finds an edge that points to an ancestor of the current vertex (it contains a back edge). All the back edges which DFS skips over are part of cycles. In an undirected graph, the edge to the parent of a node should not be counted as a back edge, but finding any other already visited vertex will indicate a back edge. In the case of undirected graphs, only O(n) time is required to find a cycle in an n-vertex graph, since at most n − 1 edges can be tree edges.

Many topological sorting algorithms will detect cycles too, since those are obstacles for topological order to exist. Also, if a directed graph has been divided into strongly connected components, cycles only exist within the components and not between them, since cycles are strongly connected.

For directed graphs, distributed message based algorithms can be used. These algorithms rely on the idea that a message sent by a vertex in a cycle will come back to itself. Distributed cycle detection algorithms are useful for processing large-scale graphs using a distributed graph processing system on a computer cluster (or supercomputer).

Applications of cycle detection include the use of wait-for graphs to detect deadlocks in concurrent systems.

### Bellmann-Ford
[Bellmann-Ford](https://en.wikipedia.org/wiki/Bellman%E2%80%93Ford_algorithm) can be used to find the shortest distance between a source and a target node. Time Complexity  **O(|V|\cdot |E|)** where *V* is number of vertices and *E* is number of edges in graph which is higher than Dijkstra’s shortest path algorithm. The time complexity of dijkstra’s algorithm is **O( E + V logv)**. The advantage of bellman-ford over dijkstra is that it can handle graphs with negative edge weights. Further, if the graph contains a negative weight cycle then the algorithm can detect and report the presence of negative cycle.

[This video](https://www.youtube.com/watch?v=24HziTZ8_xo) gives a nice overview of the algorithm implementation. This [MIT lecture](https://courses.csail.mit.edu/6.006/spring11/lectures/lec15.pdf) gives a proof of Bellman-Ford’s correctness & its ability to detect negative cycles. 

Applications:

1. Distance‐vector routing protocol
2. Routing Information Protocol (RIP)
3. Interior Gateway Routing Protocol (IGRP)

### Floyd-Warshall
[Floyd-Warshall](https://en.wikipedia.org/wiki/Floyd%E2%80%93Warshall_algorithm)

We initialize the solution matrix same as the input graph matrix as a first step. Then we update the solution matrix by considering all vertices as an intermediate vertex. The idea is to one by one pick all vertices and updates all shortest paths which include the picked vertex as an intermediate vertex in the shortest path. When we pick vertex number **k** as an intermediate vertex, we already have considered vertices **\{0, 1, 2, .. k-1\}** as intermediate vertices. For every pair **(i, j)** of the source and destination vertices respectively, there are two possible cases.

1. k is not an intermediate vertex in shortest path from i to j. We keep the value of dist[i][j] as it is.
2) k is an intermediate vertex in shortest path from i to j. We update the value of dist[i][j] as dist[i][k] + dist[k][j] if dist[i][j] > dist[i][k] + dist[k][j]

### Transitive Reduction
[Transitive Reduction](https://en.wikipedia.org/wiki/Transitive_reduction) is used to construct a directed graph with the same reachability and satisfies transitive closure, with as few edges as possible. More concretely, it creates a minimum equivalent graph with as few edges as possible, removing “short-circuit” paths through the graph.

This is done by iterating through each node-pair, checking to see if two edges exist that leads out of the first node OR out of the last node, removing the node-pair edge if it exists.

In pseudocode: foreach x in graph.vertices foreach y in graph.vertices foreach z in graph.vertices delete edge xz if edges xy and yz exist

Our implementation has if gates that do early checking for edges in multiple places, which gives it a slightly faster runtime than the cubic pseudocode here.

### Kruskal Algorithm
[Kruskal Algorithm](https://en.wikipedia.org/wiki/Kruskal%27s_algorithm) can be used to find the minimum spanning forest of an undirected edge-weighted graph. Time Complexity O(E log E) = O(E log V) where V is number of vertices and E is number of edges in graph. The main speed limitation for this algorithm is sorting the edges.

For a quick understanding of the algorithm procedure, check this video. Some of the real life applications are:

- LAN/TV Network
- Tour Operations
- Water/gas pipe network
- Electric grid

Other algorithms to find the minimum spanning forest are Prim’s algorithm or Borůvka’s algorithm.

### Borůvka's algorithm
[Borůvka's algorithm](https://en.wikipedia.org/wiki/Bor%C5%AFvka%27s_algorithm#) is a greedy algorithm that can be used for finding a minimum spanning tree in a graph, or a minimum spanning forest in the case of a graph that is not connected.

The algorithm begins by finding the minimum-weight edge incident to each vertex of the graph, and adding all of those edges to the forest. Then, it repeats a similar process of finding the minimum-weight edge from each tree constructed so far to a different tree, and adding all of those edges to the forest. Each repetition of this process reduces the number of trees, within each connected component of the graph, to at most half of this former value, so after logarithmically many repetitions the process finishes. When it does, the set of edges it has added forms the minimum spanning forest.

Borůvka’s algorithm can be shown to take O(log V) iterations of the outer loop until it terminates, and therefore to run in time O(E log V), where E is the number of edges, and V is the number of vertices in G (assuming E ≥ V).

### Graph Slicing Based on Connectivity
Mathematical definition of the problem: Let G be the set of nodes in a graph and n be a given node in that set. Let C be the non-strict subset of G containing both n and all nodes reachable from n, and let C’ be its complement. There’s a third set M, which is the non-strict subset of C containing all nodes that are reachable from any node in C’. The problem consists of finding all nodes that belong to C but not to M.

Currently implemented Algorithm:

- Use DFS to find all nodes reachable from n. These are elements of set C.
- Initialize C’ to be complement of C (i.e. all nodes - nodes that are in C)
- For all nodes in C’, apply DFS and get the list of reachable nodes. This is set M.
- Finally removes nodes from C that belong to M. This is our solution.

Application:

This algorithm is used in garbage collection systems to decide which other objects need to be released, given that one object is about to be released.

### Ford-Fulkerson
[Ford-Fulkerson](https://en.wikipedia.org/wiki/Ford%E2%80%93Fulkerson_algorithm) is a greedy algorithm for finding a maximum flow in a flow network. The idea behind the algorithm is as follows: as long as there is a path from the source (start node) to the sink (end node), with available capacity on all edges in the path, we send flow along one of the paths. Then we find another path, and so on. A path with available capacity is called an augmenting path.

### Kosaraju's Algorithm
[Kosaraju's Algorithm](https://en.wikipedia.org/wiki/Kosaraju%27s_algorithm) is a linear time algorithm to find the strongly connected components of a directed graph. It is based on the idea that if one is able to reach a vertex v starting from vertex u, then one should be able to reach vertex u starting from vertex v and if such is the case, one can say that vertices u and v are strongly connected - they are in a strongly connected sub-graph. Following is an example:

1. Create an empty stack ‘S’ and do DFS traversal of a graph. In DFS traversal, after calling recursive DFS for adjacent vertices of a vertex, push the vertex to stack.
2. Reverse directions of all arcs to obtain the transpose graph.
3. One by one pop a vertex from S while S is not empty. Let the popped vertex be ‘v’. Take v as source and do DFS (call DFSUtil(v)). The DFS starting from v prints strongly connected component of v.

### Kahn's Algorithm
[Kahn's Algorithm](https://en.wikipedia.org/wiki/Topological_sorting#Kahn's_algorithm) finds topological ordering by iteratively removing nodes in the graph which have no incoming edges. When a node is removed from the graph, it is added to the topological ordering and all its edges are removed allowing for the next set of nodes with no incoming edges to be selected.

### Welsh Powell Graph Colouring Algorithm
[Welsh Powell Graph Colouring Algorithm](https://www.geeksforgeeks.org/welsh-powell-graph-colouring-algorithm/) is a greedy vertex coloring algorithm. This algorithm is also used to find the chromatic number of a graph.

Welsh Powell Algorithm consists of following steps :

1. Find the degree of each vertex.
2. List the vertices in order of descending degrees.
3. Colour the first vertex with color 1.
4. Move down the list and color all the vertices not connected to the coloured vertex, with the same color.
5. Repeat step 4 on all uncolored vertices with a new color, in descending order of degrees until all the vertices are coloured.

The algorithm returns a std::map\<Node, int\> result that assigns each node to a color ordered by integers. Users can also query the minimum chromatic order of the graph by querying the highest value from the resulting map.

```
std::map<Node, int> result = graph.welshPowellColoring();
auto chromatic_color = std::max_element(result.begin(), result.end(),
                                [](const auto& lhs, const auto& rhs) {
                                    return lhs.second < rhs.second;
                                }
```

The minimum coloring starts from 1 instead of 0.

The algorithm assumes the graph to be undirected. All sources and inspirations are linked in the declaration of the algorithm and test cases.