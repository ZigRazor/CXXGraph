---
id: 'partition-algorithm'
title: 'Partition Algorithms Explanation'
tags: ['algorithm', 'partition-algorithm', 'components', 'graphing-components', 'graphing']
---
### Vertex-Cut
A vertex-cut partitioning divides edges of a graph into equal size partitions. The vertices that hold the endpoints of an edge are also placed in the same partition as the edge itself. However, the vertices are not unique across partitions and might have to be replicated (cut), due to the distribution of their edge across different partitions.

Replication factor quantifies how many vertices are replicated over computers compared with the the number of vertices of the original input graph.

### Edge Balanced Vertex-Cut
This Algorithm is a simple vertex-cut in Round-Robin fashion. It takes the original graph edges and assign them to the partitions, dividing it in equal(or similar) size. This algorithm does not take care of optimization in vertex replication ( Replication Factor) but only balance the edge in the partitions.

### Greedy Vertex-Cut
Greedy partitioning algorithms uses the entire history of the edge assignments to make the next decision. The algorithm stores the set of partitions A(v) to which each already observed vertex v has been assigned and the current partition sizes. When processing edge e ∈ E connecting vertices vi, vj ∈ V , the greedy algorithm follows this simple set of rules:

1. If neither vi nor vj have been assigned to a partition, then e is placed in the partition with the smallest size in P.
2. If only one of the two vertices has been already assigned (without loss of generality assume that vi is the assigned vertex) then e is placed in the partition with the smallest size in A(vi).
3. If A(vi) ∩ A(vj ) 6= ∅, then edge e is placed in the partition with the smallest size in A(vi) ∩ A(vj).
4. If A(vi) != ∅, A(vj ) != ∅ and A(vi)∩A(vj ) = ∅, then e is placed in the partition with the smallest size in A(vi)∪A(vj) and a new vertex replica is created accordingly.

### HDRF
High Degree (are) Replicated First(HDRF) Algorithm is a greedy vertex-cut algorithm as described by this [paper](https://www.fabiopetroni.com/Download/petroni2015HDRF.pdf). This Algorithm try to optimize Replication Factor by using the history of the edge assignements amd the incremental vertex degree. With a function that take in consideration this two factors calculate the best partition to assign the analyzed edge. The replica created are based on the degree of the verteices, and the vertices replicated are probably a so called “Hub-Node”, which are the vertices with higher degree.

### EBV
Efficient and Balanced Vertex-cut(EBV) is an offline vertex-cut algorithm as described by this paper. This algorithm try to balance the partitions with respect to the number of edges and vertices of each partitions and the Replication Factor. It apply a formula to evaluate the partition in which assigns the edge that take into consideration also the total number of edges and vertices of the graph. The evaluation formula is the following:

`
Eva(u,v)(i) =I(u ∈ keep[i]) + I(v ∈ keep[i]) +α * \frac{ecount[i]}{(|E|/p)} + β * \frac{vcount[i]}{(|V|/p)}
`
The lowest value is taken as partition Id.