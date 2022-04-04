#include <CXXGraph.hpp>
#include <math.h>

typedef struct euclid_point {
    double x;
    double y;
    double z;
} euclid_point_t;

double norm(const euclid_point& point_a, const euclid_point& point_b) {
    return sqrt(pow(point_a.x-point_b.x, 2) + pow(point_a.y-point_b.y, 2) + pow(point_a.z-point_b.z, 2));
}

int main() {
    euclid_point_t point_a{1, 1, 0};
    euclid_point_t point_b{2, 2, 3};
    euclid_point_t point_c{4, 4, 5};
    euclid_point_t point_d{10, 10, 0};

    std::vector<euclid_point> points_vector = {
        point_a,
        point_b,
        point_c,
        point_d
    };

    CXXGRAPH::Node<int> node0("0", 0);
    CXXGRAPH::Node<int> node1("1", 1);
    CXXGRAPH::Node<int> node2("2", 2);
    CXXGRAPH::Node<int> node3("3", 3);


    CXXGRAPH::DirectedWeightedEdge<int> edge1(1, node1, node2, norm(points_vector.at(node1.getData()), points_vector.at(node2.getData())));
    CXXGRAPH::DirectedWeightedEdge<int> edge2(2, node2, node3, norm(points_vector.at(node2.getData()), points_vector.at(node3.getData())));
    CXXGRAPH::DirectedWeightedEdge<int> edge3(3, node1, node3, norm(points_vector.at(node1.getData()), points_vector.at(node3.getData())));
    CXXGRAPH::DirectedWeightedEdge<int> edge4(4, node0, node1, norm(points_vector.at(node0.getData()), points_vector.at(node1.getData())));
    CXXGRAPH::DirectedWeightedEdge<int> edge5(5, node0, node2, norm(points_vector.at(node0.getData()), points_vector.at(node2.getData())));

    std::set<const CXXGRAPH::Edge<int> *> edgeSet;
    edgeSet.insert(&edge1);
    edgeSet.insert(&edge2);
    edgeSet.insert(&edge3);
    edgeSet.insert(&edge4);
    edgeSet.insert(&edge5);

    // Can print out the edges for debugging
    std::cout << edge1 << "\n";
    std::cout << edge2 << "\n";
    std::cout << edge3 << "\n";
    std::cout << edge4 << "\n";
    std::cout << edge5 << "\n";

    CXXGRAPH::Graph<int> graph(edgeSet);
    CXXGRAPH::DialResult res = graph.dial(node0, 100);

    std::cout << "Dial Result: " << res.minDistanceMap.at(node3.getId()) << ", " << res.success << "\n";
    return 0;
}