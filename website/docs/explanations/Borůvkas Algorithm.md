---
sidebar_position: 10
---


[Borůvka's Algorithm](https://en.wikipedia.org/wiki/Bor%C5%AFvka%27s_algorithm#)  is a greedy algorithm that can be used for finding a minimum spanning tree in a graph, or a minimum spanning forest in the case of a graph that is not connected.

The algorithm begins by finding the minimum-weight edge incident to each vertex of the graph, and adding all of those edges to the forest. Then, it repeats a similar process of finding the minimum-weight edge from each tree constructed so far to a different tree, and adding all of those edges to the forest. Each repetition of this process reduces the number of trees, within each connected component of the graph, to at most half of this former value, so after logarithmically many repetitions the process finishes. When it does, the set of edges it has added forms the minimum spanning forest.

Borůvka's algorithm can be shown to take O(log V) iterations of the outer loop until it terminates, and therefore to run in time O(E log V), where E is the number of edges, and V is the number of vertices in G (assuming E ≥ V).
