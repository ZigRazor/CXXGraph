#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <random>
#include "Node_impl.h"
#include "CXXGraph/Graph/Graph_decl.h"


namespace CXXGraph {

template <typename T>
class Graph {
private:
    std::unordered_map<CXXGraph::id_t, Node<T>> nodes;
    std::unordered_map<CXXGraph::id_t, std::unordered_set<CXXGraph::id_t>> adjacency_list;

public:
    // Other graph methods...

    // Function to add an edge between two nodes
    void addEdge(const std::string& from_id, const std::string& to_id) {
        adjacency_list[from_id].insert(to_id);
        adjacency_list[to_id].insert(from_id);
        // Assuming nodes are already added to the graph
    }

    // Krager's algorithm for graph partitioning
    std::pair<std::unordered_set<CXXGraph::id_t>, std::unordered_set<CXXGraph::id_t>> kragersAlgorithm() {
        // Initialize clusters
        std::unordered_set<CXXGraph::id_t> cluster1;
        std::unordered_set<CXXGraph::id_t> cluster2;
        for (const auto& node_pair : nodes) {
            cluster1.insert(node_pair.first);
        }

        // Perform Krager's algorithm
        std::random_device rd;
        std::mt19937 gen(rd());
        while (cluster1.size() > 2) {
            // Select a random edge
            std::uniform_int_distribution<size_t> dist(0, adjacency_list.size() - 1);
            size_t rand_index = dist(gen);
            auto it = std::next(std::begin(adjacency_list), rand_index);
            CXXGraph::id_t u = it->first;
            auto& neighbors = it->second;
            std::uniform_int_distribution<size_t> dist_neighbor(0, neighbors.size() - 1);
            size_t rand_neighbor_index = dist_neighbor(gen);
            auto neighbor_it = std::next(std::begin(neighbors), rand_neighbor_index);
            CXXGraph::id_t v = *neighbor_it;

            // Merge clusters if the vertices belong to different clusters
            if (cluster1.count(u) && cluster1.count(v)) {
                cluster1.erase(v);
                cluster2.insert(v);
            } else if (cluster2.count(u) && cluster1.count(v)) {
                cluster1.erase(v);
                cluster2.insert(v);
            }
        }

        return {cluster1, cluster2};
    }
};

} // namespace CXXGraph
