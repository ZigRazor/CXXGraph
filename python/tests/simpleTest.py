import sys
sys.path.append("../../build/python/bindings")

import cxxgraph

g = cxxgraph.Graph()
node1 = cxxgraph.Node("Node_1", 1)
node2 = cxxgraph.Node("Node_2", 2)
g.add_node(node1)
g.add_node(node1)
edge1 = cxxgraph.Edge(1,node1,node2)
g.add_edge(edge1)


result = g.dfs(node1)

for node in result:
    print(node.get_id(), node.get_user_id(), node.get_data())

