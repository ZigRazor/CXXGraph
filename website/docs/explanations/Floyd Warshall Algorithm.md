---
sidebar_position: 8
---

[Floyd Warshall Algorithm](https://en.wikipedia.org/wiki/Floyd%E2%80%93Warshall_algorithm)

We initialize the solution matrix same as the input graph matrix as a first step. Then we update the solution matrix by considering all vertices as an intermediate vertex. The idea is to one by one pick all vertices and updates all shortest paths which include the picked vertex as an intermediate vertex in the shortest path.   

When we pick vertex number k as an intermediate vertex, we already have considered vertices {0, 1, 2, .. k-1} as intermediate vertices. For every pair (i, j) of the source and destination vertices respectively, there are two possible cases.

- 1) k is not an intermediate vertex in shortest path from i to j. We keep the value of dist[i][j] as it is.
- 2) k is an intermediate vertex in shortest path from i to j. We update the value of `dist[i][j]` as `dist[i][k] + dist[k][j]` if `dist[i][j] > dist[i][k] + dist[k][j]`
