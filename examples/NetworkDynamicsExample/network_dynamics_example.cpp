#include <memory>

#include "CXXGraph/CXXGraph.hpp"

using std::make_shared;

int main() {
  CXXGraph::Node<int> node0("0", 0);
  CXXGraph::Node<int> node1("1", 1);
  CXXGraph::Node<int> node2("2", 2);
  CXXGraph::Node<int> node3("3", 3);

  CXXGraph::UndirectedWeightedEdge<int> edge1(1, node1, node2, 2.0);
  CXXGraph::UndirectedWeightedEdge<int> edge2(2, node2, node3, 2.0);
  CXXGraph::UndirectedWeightedEdge<int> edge3(3, node0, node1, 2.0);
  CXXGraph::UndirectedWeightedEdge<int> edge4(4, node0, node3, 1.0);

  CXXGraph::T_EdgeSet<int> edgeSet;
  edgeSet.insert(make_shared<CXXGraph::UndirectedWeightedEdge<int>>(edge1));
  edgeSet.insert(make_shared<CXXGraph::UndirectedWeightedEdge<int>>(edge2));
  edgeSet.insert(make_shared<CXXGraph::UndirectedWeightedEdge<int>>(edge3));
  edgeSet.insert(make_shared<CXXGraph::UndirectedWeightedEdge<int>>(edge4));

  CXXGraph::Graph<int> graph(edgeSet);

  auto degreeMatrix = graph.getDegreeMatrix();
  for (const auto& nodePair : *degreeMatrix) {
    const CXXGraph::shared<const CXXGraph::Node<int>>& node = nodePair.first;
    const std::vector<int>& degrees = nodePair.second;

    std::cout << "Node: " << node->getId() << ", Degree: " << degrees[0]
              << "\n";
  }
  auto laplacianMatrix = graph.getLaplacianMatrix();
  for (const auto& nodePair : *laplacianMatrix) {
    const auto& node = nodePair.first;
    const auto& neighbors = nodePair.second;

    std::cout << "Node " << node->getId() << " connected to:" << std::endl;
    for (const auto& neighbor : neighbors) {
      if (neighbor.first == node) {
        std::cout << "  -> Itself" << std::endl;
      } else {
        std::cout << "  -> Node " << neighbor.first->getId() << " with Edge ID "
                  << (neighbor.second ? neighbor.second->getId() : -1)
                  << std::endl;
      }
    }
    std::cout << std::endl;
  }

  auto transitionMatrix = graph.getTransitionMatrix();
  for (const auto& nodePair : *transitionMatrix) {
    const auto& node = nodePair.first;
    const auto& transitions = nodePair.second;

    std::cout << "Transitions from Node " << node->getId() << ":" << std::endl;
    for (const auto& transition : transitions) {
      std::cout << "  -> To Node " << transition.first->getId()
                << " with Probability " << transition.second << std::endl;
    }
    std::cout << std::endl;
  }

  return 0;
}
