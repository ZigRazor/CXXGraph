---
sidebar_position: 7
---

[Bellman-Ford Algorithm](https://en.wikipedia.org/wiki/Bellman%E2%80%93Ford_algorithm) can be used to find the shortest distance between a source and a target node. Time Complexity O(|V| . |E|) where V is number of vertices and E is number of edges in graph which is higher than Dijkstra's shortest path algorithm. The time complexity of dijkstra's algorithm is O(|E| + |V| log |v| ). The advantage of bellman-ford over dijkstra is that it can handle graphs with negative edge weights. Further, if the graph contains a negative weight cycle then the algorithm can detect and report the presense of negative cycle.

[This video](https://www.youtube.com/watch?v=24HziTZ8_xo) gives a nice overview of the algorithm implementation. This [MIT lecture](https://courses.csail.mit.edu/6.006/spring11/lectures/lec15.pdf) gives a proof of Bellman-Ford's correctness & its ability to detect negative cycles.
Applications:

- Distance‐vector routing protocol
- Routing Information Protocol (RIP)
- Interior Gateway Routing Protocol (IGRP)
