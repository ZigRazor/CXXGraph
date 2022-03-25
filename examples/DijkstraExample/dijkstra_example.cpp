#include <CXXGraph.hpp>

int main() {
    CXXGRAPH::Node<int> node0("0", 0);
    CXXGRAPH::Node<int> node1("1", 1);
    CXXGRAPH::Node<int> node2("2", 2);
    CXXGRAPH::Node<int> node3("3", 3);

    CXXGRAPH::UndirectedWeightedEdge<int> edge1(1, node1, node2, 2.0);
    CXXGRAPH::UndirectedWeightedEdge<int> edge2(2, node2, node3, 2.0);
    CXXGRAPH::UndirectedWeightedEdge<int> edge3(3, node0, node1, 2.0);
    CXXGRAPH::UndirectedWeightedEdge<int> edge4(4, node0, node3, 1.0);


    std::deque<const CXXGRAPH::Edge<int> *> edgeSet;
    edgeSet.push_back(&edge1);
    edgeSet.push_back(&edge2);
    edgeSet.push_back(&edge3);
    edgeSet.push_back(&edge4);

    // Can print out the edges for debugging
    std::cout << edge1 << "\n";
    std::cout << edge2 << "\n";
    std::cout << edge3 << "\n";
    std::cout << edge4 << "\n";

    CXXGRAPH::Graph<int> graph(edgeSet);
    auto res = graph.dijkstra(node0, node2);

    std::cout << "Dijkstra Result: " << res.result << "\n";

    return 0;
}