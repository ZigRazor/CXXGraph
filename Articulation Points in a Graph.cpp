Articulation Points in a Graph.

//Articulation Points in a Graph using Tarjan’s Algorithm: 
  
The idea is to use DFS (Depth First Search). In DFS, follow vertices in a tree form called the DFS tree. In the DFS tree, a vertex u is the parent of another
vertex v, if v is discovered by u. 
In DFS tree, a vertex u is an articulation point if one of the following two conditions is true. 
-u is the root of the DFS tree and it has at least two children. 
-u is not the root of the DFS tree and it has a child v such that no vertex in the subtree rooted with v has a back edge to one of the ancestors in DFS tree of u.  

Follow the below steps to Implement the idea:

-Do DFS traversal of the given graph 
-In DFS traversal, maintain a parent[] array where parent[u] stores the parent of vertex u.
-To check if u is the root of the DFS tree and it has at least two children. For every vertex, count children. If the currently visited vertex u is root
 (parent[u] is NULL) and has more than two children, print it. 
-To handle a second case where u is not the root of the DFS tree and it has a child v such that no vertex in the subtree rooted with v has a back edge to one of 
 the ancestors in DFS tree of u maintain an array disc[] to store the discovery time of vertices.
-For every node u, find out the earliest visited vertex (the vertex with minimum discovery time) that can be reached from the subtree rooted with u. So we 
 maintain an additional array low[] such that: low[u] = min(disc[u], disc[w]) , Here w is an ancestor of u and there is a back edge from some descendant of u to w.
  
  
// code
  
#include <bits/stdc++.h>
using namespace std;

void APUtil(vector<int> adj[], int u, bool visited[],
			int disc[], int low[], int& time, int parent,
			bool isAP[])
{
	int children = 0;
	visited[u] = true;
	disc[u] = low[u] = ++time;

	for (auto v : adj[u]) {
		if (!visited[v]) {
			children++;
			APUtil(adj, v, visited, disc, low, time, u, isAP);

			low[u] = min(low[u], low[v]);

			if (parent != -1 && low[v] >= disc[u])
				isAP[u] = true;
		}

		else if (v != parent)
			low[u] = min(low[u], disc[v]);
	}

	if (parent == -1 && children > 1)
		isAP[u] = true;
}

void AP(vector<int> adj[], int V)
{
	int disc[V] = { 0 };
	int low[V];
	bool visited[V] = { false };
	bool isAP[V] = { false };
	int time = 0, par = -1;
  
	for (int u = 0; u < V; u++)
		if (!visited[u])
			APUtil(adj, u, visited, disc, low,
				time, par, isAP);

	for (int u = 0; u < V; u++)
		if (isAP[u] == true)
			cout << u << " ";
}

void addEdge(vector<int> adj[], int u, int v)
{
	adj[u].push_back(v);
	adj[v].push_back(u);
}

int main()
{
	cout << "Articulation points in first graph \n";
	int V = 5;
	vector<int> adj1[V];
	addEdge(adj1, 1, 0);
	addEdge(adj1, 0, 2);
	addEdge(adj1, 2, 1);
	addEdge(adj1, 0, 3);
	addEdge(adj1, 3, 4);
	AP(adj1, V);

	cout << "\nArticulation points in second graph \n";
	V = 4;
	vector<int> adj2[V];
	addEdge(adj2, 0, 1);
	addEdge(adj2, 1, 2);
	addEdge(adj2, 2, 3);
	AP(adj2, V);

	cout << "\nArticulation points in third graph \n";
	V = 7;
	vector<int> adj3[V];
	addEdge(adj3, 0, 1);
	addEdge(adj3, 1, 2);
	addEdge(adj3, 2, 0);
	addEdge(adj3, 1, 3);
	addEdge(adj3, 1, 4);
	addEdge(adj3, 1, 6);
	addEdge(adj3, 3, 5);
	addEdge(adj3, 4, 5);
	AP(adj3, V);

	return 0;
}
