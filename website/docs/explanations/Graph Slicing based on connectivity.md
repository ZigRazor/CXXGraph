---
sidebar_position: 11
---


**Mathematical definition of the problem**:
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

**Application**

This algorithm is used in garbage collection systems to decide which other objects need to be released, given that one object is about to be released.
