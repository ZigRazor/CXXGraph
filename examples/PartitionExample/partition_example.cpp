#include <cassert>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <string>

#include "CXXGraph/CXXGraph.hpp"

static CXXGraph::Graph<int> *readGraph(const std::string &filename) {
  CXXGraph::Graph<int> *graph_ptr = new CXXGraph::Graph<int>();
  auto result =
      graph_ptr->readFromFile(CXXGraph::InputOutputFormat::STANDARD_CSV,
                              "../../../benchmark/dataset", filename);
  assert(result == 0);
  return graph_ptr;
}

static const auto cit_graph_ptr = readGraph("CitHepPh");

int main() {
  // std::cout << *cit_graph_ptr << std::endl;
  std::cout << cit_graph_ptr->getEdgeSet().size() << std::endl;
  std::cout << cit_graph_ptr->getNodeSet().size() << std::endl;
  auto partitionedTwo =
      CXXGraph::Partitioning::Partitioner<int>::partitionGraph(
          *cit_graph_ptr, CXXGraph::Partitioning::HDRF_ALG, 2, 1, 1, 1, 4);
  std::cout << "end partition two" << std::endl;
  auto partitionedFour =
      CXXGraph::Partitioning::Partitioner<int>::partitionGraph(
          *cit_graph_ptr, CXXGraph::Partitioning::HDRF_ALG, 4, 1, 1, 1, 4);
  std::cout << "end partition four" << std::endl;
  auto partitionedEight =
      CXXGraph::Partitioning::Partitioner<int>::partitionGraph(
          *cit_graph_ptr, CXXGraph::Partitioning::HDRF_ALG, 8, 1, 1, 1, 4);
  std::cout << "end partition eight" << std::endl;
  auto statsTwo = CXXGraph::Partitioning::getPartitionStats(partitionedTwo);
  auto statsFour = CXXGraph::Partitioning::getPartitionStats(partitionedFour);
  auto statsEight = CXXGraph::Partitioning::getPartitionStats(partitionedEight);
  std::cout << "TWO: " << statsTwo << std::endl;
  std::cout << "FOUR: " << statsFour << std::endl;
  std::cout << "EIGHT: " << statsEight << std::endl;

  return 0;
}
