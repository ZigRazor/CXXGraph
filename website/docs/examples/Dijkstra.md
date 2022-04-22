---
sidebar_position: 2
---

### CMake Lists
```bash 
cmake_minimum_required(VERSION 3.9)
project(DijkstraExample)

# specify the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(CMAKE_CXX_IMPLICIT_LINK_DIRECTORIES /usr/local/lib ${CMAKE_CXX_IMPLICIT_LINK_DIRECTORIES})

add_executable(dijkstra_example dijkstra_example.cpp)
target_include_directories(dijkstra_example PUBLIC "${CMAKE_SOURCE_DIR}/../../include")

target_link_libraries(dijkstra_example
                        pthread
                        ssl
                        crypto
                        z)
```

### Example

```C++
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


    std::list<const CXXGRAPH::Edge<int> *> edgeSet;
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
```