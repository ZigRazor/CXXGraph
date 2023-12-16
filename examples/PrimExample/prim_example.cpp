#include <CXXGraph/CXXGraph.hpp>
#include <memory>

using std::make_shared;

// example taken from
// https://www.geeksforgeeks.org/prims-mst-for-adjacency-list-representation-greedy-algo-6/TEST(FWTest,
// test_1)
int main() {
  CXXGraph::Node<int> node0("0", 0);
  CXXGraph::Node<int> node1("1", 1);
  CXXGraph::Node<int> node2("2", 2);
  CXXGraph::Node<int> node3("3", 3);
  CXXGraph::Node<int> node4("4", 4);
  CXXGraph::Node<int> node5("5", 5);
  CXXGraph::Node<int> node6("6", 6);
  CXXGraph::Node<int> node7("7", 7);
  CXXGraph::Node<int> node8("8", 8);

  CXXGraph::UndirectedWeightedEdge<int> edge1(1, node0, node1, 4);
  CXXGraph::UndirectedWeightedEdge<int> edge2(2, node0, node7, 8);
  CXXGraph::UndirectedWeightedEdge<int> edge3(3, node1, node7, 11);
  CXXGraph::UndirectedWeightedEdge<int> edge4(4, node1, node2, 8);
  CXXGraph::UndirectedWeightedEdge<int> edge5(5, node2, node8, 2);
  CXXGraph::UndirectedWeightedEdge<int> edge6(6, node2, node5, 4);
  CXXGraph::UndirectedWeightedEdge<int> edge7(7, node2, node3, 7);
  CXXGraph::UndirectedWeightedEdge<int> edge8(8, node3, node3, 1);
  CXXGraph::UndirectedWeightedEdge<int> edge9(9, node3, node4, 9);
  CXXGraph::UndirectedWeightedEdge<int> edge10(10, node3, node5, 14);
  CXXGraph::UndirectedWeightedEdge<int> edge11(11, node4, node5, 10);
  CXXGraph::UndirectedWeightedEdge<int> edge12(12, node5, node6, 2);
  CXXGraph::UndirectedWeightedEdge<int> edge13(13, node6, node8, 6);
  CXXGraph::UndirectedWeightedEdge<int> edge14(14, node6, node7, 1);
  CXXGraph::UndirectedWeightedEdge<int> edge15(15, node7, node8, 7);

  CXXGraph::T_EdgeSet<int> edgeSet;
  edgeSet.insert(make_shared<CXXGraph::UndirectedWeightedEdge<int>>(edge1));
  edgeSet.insert(make_shared<CXXGraph::UndirectedWeightedEdge<int>>(edge2));
  edgeSet.insert(make_shared<CXXGraph::UndirectedWeightedEdge<int>>(edge3));
  edgeSet.insert(make_shared<CXXGraph::UndirectedWeightedEdge<int>>(edge4));
  edgeSet.insert(make_shared<CXXGraph::UndirectedWeightedEdge<int>>(edge5));
  edgeSet.insert(make_shared<CXXGraph::UndirectedWeightedEdge<int>>(edge6));
  edgeSet.insert(make_shared<CXXGraph::UndirectedWeightedEdge<int>>(edge7));
  edgeSet.insert(make_shared<CXXGraph::UndirectedWeightedEdge<int>>(edge8));
  edgeSet.insert(make_shared<CXXGraph::UndirectedWeightedEdge<int>>(edge9));
  edgeSet.insert(make_shared<CXXGraph::UndirectedWeightedEdge<int>>(edge10));
  edgeSet.insert(make_shared<CXXGraph::UndirectedWeightedEdge<int>>(edge11));
  edgeSet.insert(make_shared<CXXGraph::UndirectedWeightedEdge<int>>(edge12));
  edgeSet.insert(make_shared<CXXGraph::UndirectedWeightedEdge<int>>(edge13));
  edgeSet.insert(make_shared<CXXGraph::UndirectedWeightedEdge<int>>(edge14));
  edgeSet.insert(make_shared<CXXGraph::UndirectedWeightedEdge<int>>(edge15));

  // Can print out the edges for debugging
  std::cout << edge1 << "\n";
  std::cout << edge2 << "\n";
  std::cout << edge3 << "\n";
  std::cout << edge4 << "\n";
  std::cout << edge5 << "\n";
  std::cout << edge6 << "\n";
  std::cout << edge7 << "\n";
  std::cout << edge8 << "\n";
  std::cout << edge9 << "\n";
  std::cout << edge10 << "\n";
  std::cout << edge11 << "\n";
  std::cout << edge12 << "\n";
  std::cout << edge13 << "\n";
  std::cout << edge14 << "\n";
  std::cout << edge15 << "\n";

  CXXGraph::Graph<int> graph(edgeSet);
  auto res = graph.prim();
  std::cout << "Prim Result: "
            << "\n";
  for (auto edge : res.mst) {
    std::cout << edge.first << " " << edge.second << "\n";
  }
  std::cout << "mstCost: " << res.mstCost << "\n";

  return 0;
}
