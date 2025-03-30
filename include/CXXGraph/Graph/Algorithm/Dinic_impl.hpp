#include <iostream>
#include <queue>
#include <limits>
#include <unordered_map>
#include <vector>
#include "Node_impl.h"
#include "CXXGraph/Graph/Graph_decl.h"


namespace CXXGraph {

template <typename T>
class Graph {
private:
    std::unordered_map<CXXGraph::id_t, Node<T>> nodes;
    std::unordered_map<CXXGraph::id_t, std::unordered_map<CXXGraph::id_t, int>> capacities;
    std::unordered_map<CXXGraph::id_t, std::unordered_map<CXXGraph::id_t, int>> flow;
    
    bool bfs(const CXXGraph::id_t& source, const CXXGraph::id_t& sink, std::unordered_map<CXXGraph::id_t, int>& distance) {
        for (auto& pair : nodes) {
            distance[pair.first] = -1;
        }
        distance[source] = 0;
        
        std::queue<CXXGraph::id_t> q;
        q.push(source);
        
        while (!q.empty()) {
            CXXGraph::id_t current = q.front();
            q.pop();
            for (auto& [neighbor_id, capacity] : capacities[current]) {
                if (distance[neighbor_id] == -1 && flow[current][neighbor_id] < capacity) {
                    distance[neighbor_id] = distance[current] + 1;
                    q.push(neighbor_id);
                }
            }
        }
        
        return distance[sink] != -1;
    }
    
    int dfs(const CXXGraph::id_t& current, const CXXGraph::id_t& sink, int flow_value, std::unordered_map<CXXGraph::id_t, int>& distance) {
        if (current == sink) {
            return flow_value;
        }
        
        for (auto& [neighbor_id, capacity] : capacities[current]) {
            if (distance[neighbor_id] == distance[current] + 1 && flow[current][neighbor_id] < capacity) {
                int new_flow = dfs(neighbor_id, sink, std::min(flow_value, capacity - flow[current][neighbor_id]), distance);
                if (new_flow > 0) {
                    flow[current][neighbor_id] += new_flow;
                    flow[neighbor_id][current] -= new_flow;
                    return new_flow;
                }
            }
        }
        
        return 0;
    }
    
public:
    // Other graph methods...

    // Function to add an edge with capacity
    void addEdge(const std::string& from_id, const std::string& to_id, int capacity) {
        capacities[from_id][to_id] = capacity;
        flow[from_id][to_id] = 0;
        // Assuming nodes are already added to the graph
    }
    
    // Dinic's algorithm to find maximum flow
    int dinicsAlgorithm(const CXXGraph::id_t& source, const CXXGraph::id_t& sink) {
        int max_flow = 0;
        std::unordered_map<CXXGraph::id_t, int> distance;
        
        while (bfs(source, sink, distance)) {
            int path_flow = 0;
            while ((path_flow = dfs(source, sink, std::numeric_limits<int>::max(), distance)) != 0) {
                max_flow += path_flow;
            }
        }
        
        return max_flow;
    }
};

} // namespace CXXGraph
