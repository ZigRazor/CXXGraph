#include <CXXGraph/CXXGraph.hpp>
#include <memory>

using std::make_shared;
// example taken from
// https://www.youtube.com/watch?v=B06q2yjr-Cc
int main() {
  CXXGraph::Node<int> node0("0", 0);
  CXXGraph::Node<int> node1("1", 1);
  CXXGraph::Node<int> node2("2", 2);
  CXXGraph::Node<int> node3("3", 3);
  CXXGraph::Node<int> node4("4", 4);

  CXXGraph::UndirectedWeightedEdge<int> edge1("1", node0, node1, 1);
  CXXGraph::UndirectedWeightedEdge<int> edge2("2", node0, node2, 2);
  CXXGraph::UndirectedWeightedEdge<int> edge3("3", node1, node2, 6);
  CXXGraph::UndirectedWeightedEdge<int> edge4("4", node1, node3, 4);
  CXXGraph::UndirectedWeightedEdge<int> edge5("5", node2, node3, 5);
  CXXGraph::UndirectedWeightedEdge<int> edge6("6", node3, node4, 3);

  CXXGraph::T_EdgeSet<int> edgeSet;
  edgeSet.insert(make_shared<CXXGraph::UndirectedWeightedEdge<int>>(edge1));
  edgeSet.insert(make_shared<CXXGraph::UndirectedWeightedEdge<int>>(edge2));
  edgeSet.insert(make_shared<CXXGraph::UndirectedWeightedEdge<int>>(edge3));
  edgeSet.insert(make_shared<CXXGraph::UndirectedWeightedEdge<int>>(edge4));
  edgeSet.insert(make_shared<CXXGraph::UndirectedWeightedEdge<int>>(edge5));
  edgeSet.insert(make_shared<CXXGraph::UndirectedWeightedEdge<int>>(edge6));
  // Can print out the edges for debugging
  std::cout << edge1 << "\n";
  std::cout << edge2 << "\n";
  std::cout << edge3 << "\n";
  std::cout << edge4 << "\n";
  std::cout << edge5 << "\n";
  std::cout << edge6 << "\n";

  CXXGraph::Graph<int> graph(edgeSet);
  CXXGraph::FWResult res = graph.floydWarshall();
  std::cout << "floyd Warshall Result: "
            << "\n";
  for (const auto& i : res.result) {
    std::cout << "distance of: " << i.first.first << " " << i.first.second
              << " = " << i.second << "\n";
  }
  return 0;
}
