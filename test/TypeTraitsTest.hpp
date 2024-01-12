
#ifndef test_type_traits_hpp
#define test_type_traits_hpp

#include "CXXGraph/CXXGraph.hpp"
#include <memory>

template <typename T>
using shared = std::shared_ptr<T>;

// test is_node
static_assert(CXXGraph::is_node<CXXGraph::Node<int>>::value);
static_assert(CXXGraph::is_node<const CXXGraph::Node<int>>::value);
static_assert(CXXGraph::is_node<CXXGraph::Node<int>*>::value);
static_assert(CXXGraph::is_node<const CXXGraph::Node<int>*>::value);
static_assert(CXXGraph::is_node<shared<CXXGraph::Node<int>>>::value);
static_assert(CXXGraph::is_node<shared<const CXXGraph::Node<int>>>::value);

static_assert(CXXGraph::is_node_v<CXXGraph::Node<int>>);
static_assert(CXXGraph::is_node_v<const CXXGraph::Node<int>>);
static_assert(CXXGraph::is_node_v<CXXGraph::Node<int>*>);
static_assert(CXXGraph::is_node_v<const CXXGraph::Node<int>*>);
static_assert(CXXGraph::is_node_v<shared<CXXGraph::Node<int>>>);
static_assert(CXXGraph::is_node_v<shared<const CXXGraph::Node<int>>>);

// test is_node_ptr
static_assert(CXXGraph::is_node_ptr<CXXGraph::Node<int>*>::value);
static_assert(CXXGraph::is_node_ptr<const CXXGraph::Node<int>*>::value);
static_assert(CXXGraph::is_node_ptr<shared<CXXGraph::Node<int>>>::value);
static_assert(CXXGraph::is_node_ptr<shared<const CXXGraph::Node<int>>>::value);

static_assert(CXXGraph::is_node_ptr_v<CXXGraph::Node<int>*>);
static_assert(CXXGraph::is_node_ptr_v<const CXXGraph::Node<int>*>);
static_assert(CXXGraph::is_node_ptr_v<shared<CXXGraph::Node<int>>>);
static_assert(CXXGraph::is_node_ptr_v<shared<const CXXGraph::Node<int>>>);

// test is_edge
static_assert(CXXGraph::is_edge<CXXGraph::Edge<int>>::value);
static_assert(CXXGraph::is_edge<CXXGraph::DirectedEdge<int>>::value);
static_assert(CXXGraph::is_edge<CXXGraph::DirectedWeightedEdge<int>>::value);
static_assert(CXXGraph::is_edge<CXXGraph::UndirectedEdge<int>>::value);
static_assert(CXXGraph::is_edge<CXXGraph::UndirectedWeightedEdge<int>>::value);
static_assert(CXXGraph::is_edge<const CXXGraph::Edge<int>>::value);
static_assert(CXXGraph::is_edge<const CXXGraph::DirectedEdge<int>>::value);
static_assert(CXXGraph::is_edge<const CXXGraph::DirectedWeightedEdge<int>>::value);
static_assert(CXXGraph::is_edge<const CXXGraph::UndirectedEdge<int>>::value);
static_assert(CXXGraph::is_edge<const CXXGraph::UndirectedWeightedEdge<int>>::value);
static_assert(CXXGraph::is_edge<CXXGraph::Edge<int>*>::value);
static_assert(CXXGraph::is_edge<CXXGraph::DirectedEdge<int>*>::value);
static_assert(CXXGraph::is_edge<CXXGraph::DirectedWeightedEdge<int>*>::value);
static_assert(CXXGraph::is_edge<CXXGraph::UndirectedEdge<int>*>::value);
static_assert(CXXGraph::is_edge<CXXGraph::UndirectedWeightedEdge<int>*>::value);
static_assert(CXXGraph::is_edge<const CXXGraph::Edge<int>*>::value);
static_assert(CXXGraph::is_edge<const CXXGraph::DirectedEdge<int>*>::value);
static_assert(CXXGraph::is_edge<const CXXGraph::DirectedWeightedEdge<int>*>::value);
static_assert(CXXGraph::is_edge<const CXXGraph::UndirectedEdge<int>*>::value);
static_assert(CXXGraph::is_edge<const CXXGraph::UndirectedWeightedEdge<int>*>::value);
static_assert(CXXGraph::is_edge<shared<CXXGraph::Edge<int>>>::value);
static_assert(CXXGraph::is_edge<shared<CXXGraph::DirectedEdge<int>>>::value);
static_assert(CXXGraph::is_edge<shared<CXXGraph::DirectedWeightedEdge<int>>>::value);
static_assert(CXXGraph::is_edge<shared<CXXGraph::UndirectedEdge<int>>>::value);
static_assert(CXXGraph::is_edge<shared<CXXGraph::UndirectedWeightedEdge<int>>>::value);
static_assert(CXXGraph::is_edge<shared<const CXXGraph::Edge<int>>>::value);
static_assert(CXXGraph::is_edge<shared<const CXXGraph::DirectedEdge<int>>>::value);
static_assert(CXXGraph::is_edge<shared<const CXXGraph::DirectedWeightedEdge<int>>>::value);
static_assert(CXXGraph::is_edge<shared<const CXXGraph::UndirectedEdge<int>>>::value);
static_assert(CXXGraph::is_edge<shared<const CXXGraph::UndirectedWeightedEdge<int>>>::value);

static_assert(CXXGraph::is_edge_v<CXXGraph::Edge<int>>);
static_assert(CXXGraph::is_edge_v<CXXGraph::DirectedEdge<int>>);
static_assert(CXXGraph::is_edge_v<CXXGraph::DirectedWeightedEdge<int>>);
static_assert(CXXGraph::is_edge_v<CXXGraph::UndirectedEdge<int>>);
static_assert(CXXGraph::is_edge_v<CXXGraph::UndirectedWeightedEdge<int>>);
static_assert(CXXGraph::is_edge_v<const CXXGraph::Edge<int>>);
static_assert(CXXGraph::is_edge_v<const CXXGraph::DirectedEdge<int>>);
static_assert(CXXGraph::is_edge_v<const CXXGraph::DirectedWeightedEdge<int>>);
static_assert(CXXGraph::is_edge_v<const CXXGraph::UndirectedEdge<int>>);
static_assert(CXXGraph::is_edge_v<const CXXGraph::UndirectedWeightedEdge<int>>);
static_assert(CXXGraph::is_edge_v<CXXGraph::Edge<int>*>);
static_assert(CXXGraph::is_edge_v<CXXGraph::DirectedEdge<int>*>);
static_assert(CXXGraph::is_edge_v<CXXGraph::DirectedWeightedEdge<int>*>);
static_assert(CXXGraph::is_edge_v<CXXGraph::UndirectedEdge<int>*>);
static_assert(CXXGraph::is_edge_v<CXXGraph::UndirectedWeightedEdge<int>*>);
static_assert(CXXGraph::is_edge_v<const CXXGraph::Edge<int>*>);
static_assert(CXXGraph::is_edge_v<const CXXGraph::DirectedEdge<int>*>);
static_assert(CXXGraph::is_edge_v<const CXXGraph::DirectedWeightedEdge<int>*>);
static_assert(CXXGraph::is_edge_v<const CXXGraph::UndirectedEdge<int>*>);
static_assert(CXXGraph::is_edge_v<const CXXGraph::UndirectedWeightedEdge<int>*>);
static_assert(CXXGraph::is_edge_v<shared<CXXGraph::Edge<int>>>);
static_assert(CXXGraph::is_edge_v<shared<CXXGraph::DirectedEdge<int>>>);
static_assert(CXXGraph::is_edge_v<shared<CXXGraph::DirectedWeightedEdge<int>>>);
static_assert(CXXGraph::is_edge_v<shared<CXXGraph::UndirectedEdge<int>>>);
static_assert(CXXGraph::is_edge_v<shared<CXXGraph::UndirectedWeightedEdge<int>>>);
static_assert(CXXGraph::is_edge_v<shared<const CXXGraph::Edge<int>>>);
static_assert(CXXGraph::is_edge_v<shared<const CXXGraph::DirectedEdge<int>>>);
static_assert(CXXGraph::is_edge_v<shared<const CXXGraph::DirectedWeightedEdge<int>>>);
static_assert(CXXGraph::is_edge_v<shared<const CXXGraph::UndirectedEdge<int>>>);
static_assert(CXXGraph::is_edge_v<shared<const CXXGraph::UndirectedWeightedEdge<int>>>);

// test is_edge_ptr
static_assert(CXXGraph::is_edge_ptr<CXXGraph::Edge<int>*>::value);
static_assert(CXXGraph::is_edge_ptr<CXXGraph::DirectedEdge<int>*>::value);
static_assert(CXXGraph::is_edge_ptr<CXXGraph::DirectedWeightedEdge<int>*>::value);
static_assert(CXXGraph::is_edge_ptr<CXXGraph::UndirectedEdge<int>*>::value);
static_assert(CXXGraph::is_edge_ptr<CXXGraph::UndirectedWeightedEdge<int>*>::value);
static_assert(CXXGraph::is_edge_ptr<const CXXGraph::Edge<int>*>::value);
static_assert(CXXGraph::is_edge_ptr<const CXXGraph::DirectedEdge<int>*>::value);
static_assert(CXXGraph::is_edge_ptr<const CXXGraph::DirectedWeightedEdge<int>*>::value);
static_assert(CXXGraph::is_edge_ptr<const CXXGraph::UndirectedEdge<int>*>::value);
static_assert(CXXGraph::is_edge_ptr<const CXXGraph::UndirectedWeightedEdge<int>*>::value);
static_assert(CXXGraph::is_edge_ptr<shared<CXXGraph::Edge<int>>>::value);
static_assert(CXXGraph::is_edge_ptr<shared<CXXGraph::DirectedEdge<int>>>::value);
static_assert(CXXGraph::is_edge_ptr<shared<CXXGraph::DirectedWeightedEdge<int>>>::value);
static_assert(CXXGraph::is_edge_ptr<shared<CXXGraph::UndirectedEdge<int>>>::value);
static_assert(CXXGraph::is_edge_ptr<shared<CXXGraph::UndirectedWeightedEdge<int>>>::value);
static_assert(CXXGraph::is_edge_ptr<shared<const CXXGraph::Edge<int>>>::value);
static_assert(CXXGraph::is_edge_ptr<shared<const CXXGraph::DirectedEdge<int>>>::value);
static_assert(CXXGraph::is_edge_ptr<shared<const CXXGraph::DirectedWeightedEdge<int>>>::value);
static_assert(CXXGraph::is_edge_ptr<shared<const CXXGraph::UndirectedEdge<int>>>::value);
static_assert(CXXGraph::is_edge_ptr<shared<const CXXGraph::UndirectedWeightedEdge<int>>>::value);

static_assert(CXXGraph::is_edge_ptr_v<CXXGraph::Edge<int>*>);
static_assert(CXXGraph::is_edge_ptr_v<CXXGraph::DirectedEdge<int>*>);
static_assert(CXXGraph::is_edge_ptr_v<CXXGraph::DirectedWeightedEdge<int>*>);
static_assert(CXXGraph::is_edge_ptr_v<CXXGraph::UndirectedEdge<int>*>);
static_assert(CXXGraph::is_edge_ptr_v<CXXGraph::UndirectedWeightedEdge<int>*>);
static_assert(CXXGraph::is_edge_ptr_v<const CXXGraph::Edge<int>*>);
static_assert(CXXGraph::is_edge_ptr_v<const CXXGraph::DirectedEdge<int>*>);
static_assert(CXXGraph::is_edge_ptr_v<const CXXGraph::DirectedWeightedEdge<int>*>);
static_assert(CXXGraph::is_edge_ptr_v<const CXXGraph::UndirectedEdge<int>*>);
static_assert(CXXGraph::is_edge_ptr_v<const CXXGraph::UndirectedWeightedEdge<int>*>);
static_assert(CXXGraph::is_edge_ptr_v<shared<CXXGraph::Edge<int>>>);
static_assert(CXXGraph::is_edge_ptr_v<shared<CXXGraph::DirectedEdge<int>>>);
static_assert(CXXGraph::is_edge_ptr_v<shared<CXXGraph::DirectedWeightedEdge<int>>>);
static_assert(CXXGraph::is_edge_ptr_v<shared<CXXGraph::UndirectedEdge<int>>>);
static_assert(CXXGraph::is_edge_ptr_v<shared<CXXGraph::UndirectedWeightedEdge<int>>>);
static_assert(CXXGraph::is_edge_ptr_v<shared<const CXXGraph::Edge<int>>>);
static_assert(CXXGraph::is_edge_ptr_v<shared<const CXXGraph::DirectedEdge<int>>>);
static_assert(CXXGraph::is_edge_ptr_v<shared<const CXXGraph::DirectedWeightedEdge<int>>>);
static_assert(CXXGraph::is_edge_ptr_v<shared<const CXXGraph::UndirectedEdge<int>>>);
static_assert(CXXGraph::is_edge_ptr_v<shared<const CXXGraph::UndirectedWeightedEdge<int>>>);

#endif

