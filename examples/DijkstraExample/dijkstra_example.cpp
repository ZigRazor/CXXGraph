#include <CXXGraph/CXXGraph.hpp>
#include <iostream>
#include <memory>

using std::make_shared;

int main() {
  CXXGraph::Node<int> node0("0", 0);
  CXXGraph::Node<int> node1("1", 1);
  CXXGraph::Node<int> node2("2", 2);
  CXXGraph::Node<int> node3("3", 3);

  CXXGraph::DirectedWeightedEdge<int> edge1(1, node1, node2, 2.0);
  CXXGraph::DirectedWeightedEdge<int> edge2(2, node2, node3, 2.0);
  CXXGraph::DirectedWeightedEdge<int> edge3(3, node0, node1, 2.0);
  CXXGraph::DirectedWeightedEdge<int> edge4(4, node0, node3, 1.0);

  CXXGraph::T_EdgeSet<int> edgeSet;
  edgeSet.insert(make_shared<CXXGraph::DirectedWeightedEdge<int>>(edge1));
  edgeSet.insert(make_shared<CXXGraph::DirectedWeightedEdge<int>>(edge2));
  edgeSet.insert(make_shared<CXXGraph::DirectedWeightedEdge<int>>(edge3));
  edgeSet.insert(make_shared<CXXGraph::DirectedWeightedEdge<int>>(edge4));

  // Can print out the edges for debugging
  std::cout << edge1 << "\n";
  std::cout << edge2 << "\n";
  std::cout << edge3 << "\n";
  std::cout << edge4 << "\n";

  CXXGraph::Graph<int> graph(edgeSet);
  auto res = graph.dijkstra(node0, node3);

  std::cout << "Dijkstra Result: " << res.result << "\n";
  for (auto& name : res.path) {
    std::cout << "->" << name << std::endl;
  }

  std::cout << " ======= CP ====== " << std::endl;
  res = graph.criticalpath_deterministic(node0, node3);

  std::cout << "CP Result: " << res.result << "\n";
  std::cout << "CP path size: " << res.path.size() << "\n";
  for (auto& name : res.path) {
    std::cout << "->" << name << std::endl;
  }

  return 0;
}
