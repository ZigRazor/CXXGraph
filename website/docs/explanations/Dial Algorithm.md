---
sidebar_position: 4

---

**Dial specialization of Dijkstra’s algorithm.**

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