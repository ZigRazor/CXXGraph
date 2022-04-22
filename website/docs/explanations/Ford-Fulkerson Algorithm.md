---
sidebar_position: 12
---

[Ford-Fulkerson Algorithm](https://en.wikipedia.org/wiki/Ford%E2%80%93Fulkerson_algorithm) is a greedy algorithm for finding a maximum flow in a flow network.  
The idea behind the algorithm is as follows:   
- as long as there is a path from the source (start node) to the sink (end node), with available capacity on all edges in the path, we send flow along one of the paths. Then we find another path, and so on. A path with available capacity is called an augmenting path.
