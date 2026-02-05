#include <memory>
#include <string>

#include "CXXGraph/CXXGraph.hpp"
#include "gtest/gtest.h"

// Smart pointers alias
template <typename T>
using unique = std::unique_ptr<T>;
template <typename T>
using shared = std::shared_ptr<T>;

using std::make_shared;
using std::make_unique;

/*
 * 3 Nodes
 * Node1 -> Node2 weight = 1
 * Node2 -> Node3 weight = 1
 * Node1 <-> Node3 weight = 6
 */
TEST(DialTest, test_1) {
  CXXGraph::Node<int> node1("1", 1);
  CXXGraph::Node<int> node2("2", 2);
  CXXGraph::Node<int> node3("3", 3);
  std::pair<const CXXGraph::Node<int> *, const CXXGraph::Node<int> *> pairNode(
      &node1, &node2);
  CXXGraph::DirectedWeightedEdge<int> edge1("1", pairNode, 1);
  CXXGraph::DirectedWeightedEdge<int> edge2("2", node2, node3, 1);
  CXXGraph::UndirectedWeightedEdge<int> edge3("3", node1, node3, 6);
  CXXGraph::T_EdgeSet<int> edgeSet;
  edgeSet.insert(make_shared<CXXGraph::DirectedWeightedEdge<int>>(edge1));
  edgeSet.insert(make_shared<CXXGraph::DirectedWeightedEdge<int>>(edge2));
  edgeSet.insert(make_shared<CXXGraph::UndirectedWeightedEdge<int>>(edge3));
  CXXGraph::Graph<int> graph(edgeSet);
  auto res = graph.dial(node1, 6);
  ASSERT_TRUE(res.success);
  ASSERT_EQ(res.errorMessage, "");
  ASSERT_EQ(res.minDistanceMap.at(node1.getId()), 0);
  ASSERT_EQ(res.minDistanceMap.at(node2.getId()), 1);
  ASSERT_EQ(res.minDistanceMap.at(node3.getId()), 2);
}

/*
 * 3 Nodes
 * Node1 -> Node2 weight = 5
 * Node2 -> Node3 weight = 4
 * Node1 <-> Node3 weight = 6
 */
TEST(DialTest, test_2) {
  CXXGraph::Node<int> node1("1", 1);
  CXXGraph::Node<int> node2("2", 2);
  CXXGraph::Node<int> node3("3", 3);
  std::pair<const CXXGraph::Node<int> *, const CXXGraph::Node<int> *> pairNode(
      &node1, &node2);
  CXXGraph::DirectedWeightedEdge<int> edge1("1", pairNode, 5);
  CXXGraph::DirectedWeightedEdge<int> edge2("2", node2, node3, 4);
  CXXGraph::UndirectedWeightedEdge<int> edge3("3", node1, node3, 6);
  CXXGraph::T_EdgeSet<int> edgeSet;
  edgeSet.insert(make_shared<CXXGraph::DirectedWeightedEdge<int>>(edge1));
  edgeSet.insert(make_shared<CXXGraph::DirectedWeightedEdge<int>>(edge2));
  edgeSet.insert(make_shared<CXXGraph::UndirectedWeightedEdge<int>>(edge3));
  CXXGraph::Graph<int> graph(edgeSet);
  auto res = graph.dial(node1, 6);
  ;
  ASSERT_TRUE(res.success);
  ASSERT_EQ(res.errorMessage, "");
  ASSERT_EQ(res.minDistanceMap.at(node1.getId()), 0);
  ASSERT_EQ(res.minDistanceMap.at(node2.getId()), 5);
  ASSERT_EQ(res.minDistanceMap.at(node3.getId()), 6);
}

/*
 * 3 Nodes
 * Node1 -> Node2 weight = 5
 * Node2 -> Node3 unweighted
 * Node1 <-> Node3 weight = 6
 */
TEST(DialTest, test_3) {
  CXXGraph::Node<int> node1("1", 1);
  CXXGraph::Node<int> node2("2", 2);
  CXXGraph::Node<int> node3("3", 3);
  std::pair<const CXXGraph::Node<int> *, const CXXGraph::Node<int> *> pairNode(
      &node1, &node2);
  CXXGraph::DirectedWeightedEdge<int> edge1("1", pairNode, 5);
  CXXGraph::DirectedEdge<int> edge2("2", node2, node3);
  CXXGraph::UndirectedWeightedEdge<int> edge3("3", node1, node3, 6);
  CXXGraph::T_EdgeSet<int> edgeSet;
  edgeSet.insert(make_shared<CXXGraph::DirectedWeightedEdge<int>>(edge1));
  edgeSet.insert(make_shared<CXXGraph::DirectedEdge<int>>(edge2));
  edgeSet.insert(make_shared<CXXGraph::UndirectedWeightedEdge<int>>(edge3));
  CXXGraph::Graph<int> graph(edgeSet);
  auto res = graph.dial(node1, 6);
  ASSERT_FALSE(res.success);
  ASSERT_EQ(res.errorMessage, CXXGraph::ERR_NO_WEIGHTED_EDGE);
  ASSERT_TRUE(res.minDistanceMap.empty());
}

/*
 * 3 Nodes
 * Node2 -> Node3 unweighted
 * Node1 <-> Node3 weight = 6
 */
TEST(DialTest, test_4) {
  CXXGraph::Node<int> node1("1", 1);
  CXXGraph::Node<int> node2("2", 2);
  CXXGraph::Node<int> node3("3", 3);
  CXXGraph::DirectedEdge<int> edge2("2", node2, node3);
  CXXGraph::UndirectedWeightedEdge<int> edge3("3", node1, node3, 6);
  CXXGraph::T_EdgeSet<int> edgeSet;
  edgeSet.insert(make_shared<CXXGraph::DirectedWeightedEdge<int>>(edge2));
  edgeSet.insert(make_shared<CXXGraph::UndirectedWeightedEdge<int>>(edge3));
  CXXGraph::Graph<int> graph(edgeSet);
  auto res = graph.dial(node1, 6);
  ASSERT_TRUE(res.success);
  ASSERT_EQ(res.errorMessage, "");
  ASSERT_EQ(res.minDistanceMap.at(node1.getId()), 0);
  ASSERT_EQ(res.minDistanceMap.at(node2.getId()),
            std::numeric_limits<long>::max());
  ASSERT_EQ(res.minDistanceMap.at(node3.getId()), 6);
}

/*
 * 4 Nodes
 * Node2 -> Node3 unweighted
 * Node1 <-> Node3 weight = 6
 * Only nodes which are a part of the edgeSet are a part of the graph (nodeSet)
 */
TEST(DialTest, test_5) {
  CXXGraph::Node<int> node1("1", 1);
  CXXGraph::Node<int> node2("2", 2);
  CXXGraph::Node<int> node3("3", 3);
  CXXGraph::Node<int> node4("4", 4);
  CXXGraph::DirectedEdge<int> edge2("2", node2, node3);
  CXXGraph::UndirectedWeightedEdge<int> edge3("3", node1, node3, 6);
  CXXGraph::T_EdgeSet<int> edgeSet;
  edgeSet.insert(make_shared<CXXGraph::DirectedWeightedEdge<int>>(edge2));
  edgeSet.insert(make_shared<CXXGraph::UndirectedWeightedEdge<int>>(edge3));
  CXXGraph::Graph<int> graph(edgeSet);
  auto res = graph.dial(node4, 6);
  ASSERT_FALSE(res.success);
  ASSERT_EQ(res.errorMessage, CXXGraph::ERR_SOURCE_NODE_NOT_IN_GRAPH);
  ASSERT_TRUE(res.minDistanceMap.empty());
}

/*
 * 3 Nodes, zero weight edges
 * Node1 -> Node2 weight = 0
 * Node2 -> Node3 weight = 0
 */
TEST(DialTest, test_6) {
  CXXGraph::Node<int> node1("1", 1);
  CXXGraph::Node<int> node2("2", 2);
  CXXGraph::Node<int> node3("3", 3);

  CXXGraph::DirectedWeightedEdge<int> edge12("1", node1, node2, 0);
  CXXGraph::DirectedWeightedEdge<int> edge23("1", node2, node3, 0);

  CXXGraph::T_EdgeSet<int> edgeSet;
  edgeSet.insert(make_shared<CXXGraph::DirectedWeightedEdge<int>>(edge12));
  edgeSet.insert(make_shared<CXXGraph::DirectedWeightedEdge<int>>(edge23));

  CXXGraph::Graph<int> graph(edgeSet);

  // Setting maxWeight = 0 causes an early exit
  // As a consequence all distances except source node are at infinity.
  auto res = graph.dial(node1, 1);
  ASSERT_TRUE(res.success);
  ASSERT_EQ(res.errorMessage, "");
  ASSERT_EQ(res.minDistanceMap.at(node1.getId()), 0);
  ASSERT_EQ(res.minDistanceMap.at(node2.getId()), 0);
  ASSERT_EQ(res.minDistanceMap.at(node3.getId()), 0);
}

/*
 * 2 Nodes, multi edges, same end points, choose smaller edge
 * Node1 -> Node2 weight = 3
 * Node1 -> Node2 weight = 5
 */
TEST(DialTest, test_7) {
  CXXGraph::Node<int> node1("1", 1);
  CXXGraph::Node<int> node2("2", 2);

  CXXGraph::DirectedWeightedEdge<int> edge12First("1", node1, node2, 3);
  CXXGraph::DirectedWeightedEdge<int> edge12Second("1", node1, node2, 5);

  CXXGraph::T_EdgeSet<int> edgeSet;
  edgeSet.insert(make_shared<CXXGraph::DirectedWeightedEdge<int>>(edge12First));
  edgeSet.insert(
      make_shared<CXXGraph::DirectedWeightedEdge<int>>(edge12Second));

  CXXGraph::Graph<int> graph(edgeSet);

  auto res = graph.dial(node1, 5);
  ASSERT_TRUE(res.success);
  ASSERT_EQ(res.errorMessage, "");
  ASSERT_EQ(res.minDistanceMap.at(node1.getId()), 0);
  ASSERT_EQ(res.minDistanceMap.at(node2.getId()), 3);
}

/*
 * 3 Nodes, multi edges with a cycle, cycle should not trap algorithm
 * Node1 -> Node2 weight = 3
 * Node2 -> Node3 weight = 5
 * Node3 -> Node1 weight = 8
 * Node1 -> Node3 weight = 2
 */
TEST(DialTest, test_8) {
  CXXGraph::Node<int> node1("1", 1);
  CXXGraph::Node<int> node2("2", 2);
  CXXGraph::Node<int> node3("3", 3);

  CXXGraph::DirectedWeightedEdge<int> edge12("1", node1, node2, 3);
  CXXGraph::DirectedWeightedEdge<int> edge23("1", node2, node3, 5);
  CXXGraph::DirectedWeightedEdge<int> edge31("1", node3, node1, 8);
  CXXGraph::DirectedWeightedEdge<int> edge13("1", node1, node3, 2);

  CXXGraph::T_EdgeSet<int> edgeSet;
  edgeSet.insert(make_shared<CXXGraph::DirectedWeightedEdge<int>>(edge12));
  edgeSet.insert(make_shared<CXXGraph::DirectedWeightedEdge<int>>(edge23));
  edgeSet.insert(make_shared<CXXGraph::DirectedWeightedEdge<int>>(edge31));
  edgeSet.insert(make_shared<CXXGraph::DirectedWeightedEdge<int>>(edge13));

  CXXGraph::Graph<int> graph(edgeSet);

  auto res = graph.dial(node1, 5);
  ASSERT_TRUE(res.success);
  ASSERT_EQ(res.errorMessage, "");
  ASSERT_EQ(res.minDistanceMap.at(node1.getId()), 0);
  ASSERT_EQ(res.minDistanceMap.at(node2.getId()), 3);
  ASSERT_EQ(res.minDistanceMap.at(node3.getId()), 2);
}

/*
 * 2 Nodes, self loop
 * Node1 -> Node1 weight = 3
 * Node1 -> Node2 weight = 5
 */
TEST(DialTest, test_9) {
  CXXGraph::Node<int> node1("1", 1);
  CXXGraph::Node<int> node2("2", 2);

  CXXGraph::DirectedWeightedEdge<int> edge11("1", node1, node1, 3);
  CXXGraph::DirectedWeightedEdge<int> edge12("1", node1, node2, 5);

  CXXGraph::T_EdgeSet<int> edgeSet;
  edgeSet.insert(make_shared<CXXGraph::DirectedWeightedEdge<int>>(edge11));
  edgeSet.insert(make_shared<CXXGraph::DirectedWeightedEdge<int>>(edge12));

  CXXGraph::Graph<int> graph(edgeSet);

  auto res = graph.dial(node1, 5);
  ASSERT_TRUE(res.success);
  ASSERT_EQ(res.errorMessage, "");
  ASSERT_EQ(res.minDistanceMap.at(node1.getId()), 0);
  ASSERT_EQ(res.minDistanceMap.at(node2.getId()), 5);
}

template <typename T>
class BadDirectedWeightedEdge : public CXXGraph::DirectedWeightedEdge<T> {
 public:
  using Base = CXXGraph::DirectedWeightedEdge<T>;
  // forward to existing ctor
  BadDirectedWeightedEdge(const std::string &id, const CXXGraph::Node<T> &n1,
                          const CXXGraph::Node<T> &n2, const double weight)
      : Base(id, n1, n2, weight) {}

  const std::optional<bool> isDirected() const override { return std::nullopt; }
};

/*
 * 2 Nodes, invalid directed weighted edge
 * The edge claims it's weighted but does not tell us direction
 * Node1 -> Node2 weight = 5
 */
TEST(DialTest, test_10) {
  CXXGraph::Node<int> node1("1", 1);
  CXXGraph::Node<int> node2("2", 2);

  auto badEdge =
      std::make_shared<BadDirectedWeightedEdge<int>>("1", node1, node2, 5);

  CXXGraph::T_EdgeSet<int> edgeSet;
  edgeSet.insert(badEdge);

  CXXGraph::Graph<int> graph(edgeSet);

  auto res = graph.dial(node1, 5);
  ASSERT_FALSE(res.success);
  ASSERT_EQ(res.errorMessage, CXXGraph::ERR_NO_DIR_OR_UNDIR_EDGE);
  ASSERT_TRUE(res.minDistanceMap.empty());
}
