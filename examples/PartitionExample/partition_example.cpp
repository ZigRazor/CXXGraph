#include "CXXGraph.hpp"
#include <time.h>
#include <stdlib.h>
#include <iterator>

static CXXGRAPH::Graph<int> *readGraph(const std::string &filename)
{
    CXXGRAPH::Graph<int> *graph_ptr = new CXXGRAPH::Graph<int>();
    auto result = graph_ptr->readFromFile(CXXGRAPH::InputOutputFormat::STANDARD_CSV, "../../../benchmark/dataset", filename);
    return graph_ptr;
}

static auto cit_graph_ptr = readGraph("CitHepPh");

int main(){

    // std::cout << *cit_graph_ptr << std::endl;
    std::cout << cit_graph_ptr->getEdgeSet().size() << std::endl;
    std::cout << cit_graph_ptr->getNodeSet().size() << std::endl;
    auto partitionedTwo = cit_graph_ptr->partitionGraph(CXXGRAPH::PARTITIONING::HDRF_ALG, 2,1,1,1,4);
    std::cout << "end partition two" << std::endl;
    auto partitionedFour = cit_graph_ptr->partitionGraph(CXXGRAPH::PARTITIONING::HDRF_ALG, 4,1,1,1,4);
    std::cout << "end partition four" << std::endl;
    auto partitionedEight = cit_graph_ptr->partitionGraph(CXXGRAPH::PARTITIONING::HDRF_ALG, 8,1,1,1,4);
    std::cout << "end partition eight" << std::endl;
    auto statsTwo = CXXGRAPH::PARTITIONING::getPartitionStats(partitionedTwo);
    auto statsFour = CXXGRAPH::PARTITIONING::getPartitionStats(partitionedFour);
    auto statsEight = CXXGRAPH::PARTITIONING::getPartitionStats(partitionedEight);
    std::cout << "TWO: " << statsTwo << std::endl;
    std::cout << "FOUR: " << statsFour << std::endl;
    std::cout << "EIGHT: " << statsEight << std::endl;

     return 0;
}

