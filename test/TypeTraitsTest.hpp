
#ifndef test_type_traits_hpp
#define test_type_traits_hpp

#include <memory>

#include "CXXGraph/CXXGraph.hpp"

template <typename T>
using shared = std::shared_ptr<T>;

// test is_node
static_assert(CXXGraph::is_node<CXXGraph::Node<int>>::value);
static_assert(CXXGraph::is_node<const CXXGraph::Node<int>>::value);
static_assert(!CXXGraph::is_node<CXXGraph::Node<int>*>::value);
static_assert(!CXXGraph::is_node<const CXXGraph::Node<int>*>::value);
static_assert(!CXXGraph::is_node<shared<CXXGraph::Node<int>>>::value);
static_assert(!CXXGraph::is_node<shared<const CXXGraph::Node<int>>>::value);

static_assert(CXXGraph::is_node_v<CXXGraph::Node<int>>);
static_assert(CXXGraph::is_node_v<const CXXGraph::Node<int>>);
static_assert(!CXXGraph::is_node_v<CXXGraph::Node<int>*>);
static_assert(!CXXGraph::is_node_v<const CXXGraph::Node<int>*>);
static_assert(!CXXGraph::is_node_v<shared<CXXGraph::Node<int>>>);
static_assert(!CXXGraph::is_node_v<shared<const CXXGraph::Node<int>>>);

// test is_node_ptr
static_assert(CXXGraph::is_node_ptr<CXXGraph::Node<int>*>::value);
static_assert(CXXGraph::is_node_ptr<const CXXGraph::Node<int>*>::value);
static_assert(CXXGraph::is_node_ptr<shared<CXXGraph::Node<int>>>::value);
static_assert(CXXGraph::is_node_ptr<shared<const CXXGraph::Node<int>>>::value);

static_assert(CXXGraph::is_node_ptr_v<CXXGraph::Node<int>*>);
static_assert(CXXGraph::is_node_ptr_v<const CXXGraph::Node<int>*>);
static_assert(CXXGraph::is_node_ptr_v<shared<CXXGraph::Node<int>>>);
static_assert(CXXGraph::is_node_ptr_v<shared<const CXXGraph::Node<int>>>);

// test all_are_node_ptrs
static_assert(
    CXXGraph::all_are_node_ptrs<CXXGraph::Node<int>*, CXXGraph::Node<int>*,
                                CXXGraph::Node<int>*>::value);
static_assert(CXXGraph::all_are_node_ptrs<const CXXGraph::Node<int>*,
                                          const CXXGraph::Node<int>*,
                                          const CXXGraph::Node<int>*>::value);
static_assert(CXXGraph::all_are_node_ptrs<shared<CXXGraph::Node<int>>,
                                          shared<CXXGraph::Node<int>>,
                                          shared<CXXGraph::Node<int>>>::value);
static_assert(
    CXXGraph::all_are_node_ptrs<shared<const CXXGraph::Node<int>>,
                                shared<const CXXGraph::Node<int>>,
                                shared<const CXXGraph::Node<int>>>::value);

static_assert(
    CXXGraph::all_are_node_ptrs_v<CXXGraph::Node<int>*, CXXGraph::Node<int>*,
                                  CXXGraph::Node<int>*>);
static_assert(CXXGraph::all_are_node_ptrs_v<const CXXGraph::Node<int>*,
                                            const CXXGraph::Node<int>*,
                                            const CXXGraph::Node<int>*>);
static_assert(CXXGraph::all_are_node_ptrs_v<shared<CXXGraph::Node<int>>,
                                            shared<CXXGraph::Node<int>>,
                                            shared<CXXGraph::Node<int>>>);
static_assert(CXXGraph::all_are_node_ptrs_v<shared<const CXXGraph::Node<int>>,
                                            shared<const CXXGraph::Node<int>>,
                                            shared<const CXXGraph::Node<int>>>);

// test is_edge
static_assert(CXXGraph::is_edge<CXXGraph::Edge<int>>::value);
static_assert(CXXGraph::is_edge<CXXGraph::DirectedEdge<int>>::value);
static_assert(CXXGraph::is_edge<CXXGraph::DirectedWeightedEdge<int>>::value);
static_assert(CXXGraph::is_edge<CXXGraph::UndirectedEdge<int>>::value);
static_assert(CXXGraph::is_edge<CXXGraph::UndirectedWeightedEdge<int>>::value);
static_assert(CXXGraph::is_edge<const CXXGraph::Edge<int>>::value);
static_assert(CXXGraph::is_edge<const CXXGraph::DirectedEdge<int>>::value);
static_assert(
    CXXGraph::is_edge<const CXXGraph::DirectedWeightedEdge<int>>::value);
static_assert(CXXGraph::is_edge<const CXXGraph::UndirectedEdge<int>>::value);
static_assert(
    CXXGraph::is_edge<const CXXGraph::UndirectedWeightedEdge<int>>::value);
static_assert(!CXXGraph::is_edge<CXXGraph::Edge<int>*>::value);
static_assert(!CXXGraph::is_edge<CXXGraph::DirectedEdge<int>*>::value);
static_assert(!CXXGraph::is_edge<CXXGraph::DirectedWeightedEdge<int>*>::value);
static_assert(!CXXGraph::is_edge<CXXGraph::UndirectedEdge<int>*>::value);
static_assert(
    !CXXGraph::is_edge<CXXGraph::UndirectedWeightedEdge<int>*>::value);
static_assert(!CXXGraph::is_edge<const CXXGraph::Edge<int>*>::value);
static_assert(!CXXGraph::is_edge<const CXXGraph::DirectedEdge<int>*>::value);
static_assert(
    !CXXGraph::is_edge<const CXXGraph::DirectedWeightedEdge<int>*>::value);
static_assert(!CXXGraph::is_edge<const CXXGraph::UndirectedEdge<int>*>::value);
static_assert(
    !CXXGraph::is_edge<const CXXGraph::UndirectedWeightedEdge<int>*>::value);
static_assert(!CXXGraph::is_edge<shared<CXXGraph::Edge<int>>>::value);
static_assert(!CXXGraph::is_edge<shared<CXXGraph::DirectedEdge<int>>>::value);
static_assert(
    !CXXGraph::is_edge<shared<CXXGraph::DirectedWeightedEdge<int>>>::value);
static_assert(!CXXGraph::is_edge<shared<CXXGraph::UndirectedEdge<int>>>::value);
static_assert(
    !CXXGraph::is_edge<shared<CXXGraph::UndirectedWeightedEdge<int>>>::value);
static_assert(!CXXGraph::is_edge<shared<const CXXGraph::Edge<int>>>::value);
static_assert(
    !CXXGraph::is_edge<shared<const CXXGraph::DirectedEdge<int>>>::value);
static_assert(!CXXGraph::is_edge<
              shared<const CXXGraph::DirectedWeightedEdge<int>>>::value);
static_assert(
    !CXXGraph::is_edge<shared<const CXXGraph::UndirectedEdge<int>>>::value);
static_assert(!CXXGraph::is_edge<
              shared<const CXXGraph::UndirectedWeightedEdge<int>>>::value);

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
static_assert(!CXXGraph::is_edge_v<CXXGraph::Edge<int>*>);
static_assert(!CXXGraph::is_edge_v<CXXGraph::DirectedEdge<int>*>);
static_assert(!CXXGraph::is_edge_v<CXXGraph::DirectedWeightedEdge<int>*>);
static_assert(!CXXGraph::is_edge_v<CXXGraph::UndirectedEdge<int>*>);
static_assert(!CXXGraph::is_edge_v<CXXGraph::UndirectedWeightedEdge<int>*>);
static_assert(!CXXGraph::is_edge_v<const CXXGraph::Edge<int>*>);
static_assert(!CXXGraph::is_edge_v<const CXXGraph::DirectedEdge<int>*>);
static_assert(!CXXGraph::is_edge_v<const CXXGraph::DirectedWeightedEdge<int>*>);
static_assert(!CXXGraph::is_edge_v<const CXXGraph::UndirectedEdge<int>*>);
static_assert(
    !CXXGraph::is_edge_v<const CXXGraph::UndirectedWeightedEdge<int>*>);
static_assert(!CXXGraph::is_edge_v<shared<CXXGraph::Edge<int>>>);
static_assert(!CXXGraph::is_edge_v<shared<CXXGraph::DirectedEdge<int>>>);
static_assert(
    !CXXGraph::is_edge_v<shared<CXXGraph::DirectedWeightedEdge<int>>>);
static_assert(!CXXGraph::is_edge_v<shared<CXXGraph::UndirectedEdge<int>>>);
static_assert(
    !CXXGraph::is_edge_v<shared<CXXGraph::UndirectedWeightedEdge<int>>>);
static_assert(!CXXGraph::is_edge_v<shared<const CXXGraph::Edge<int>>>);
static_assert(!CXXGraph::is_edge_v<shared<const CXXGraph::DirectedEdge<int>>>);
static_assert(
    !CXXGraph::is_edge_v<shared<const CXXGraph::DirectedWeightedEdge<int>>>);
static_assert(
    !CXXGraph::is_edge_v<shared<const CXXGraph::UndirectedEdge<int>>>);
static_assert(
    !CXXGraph::is_edge_v<shared<const CXXGraph::UndirectedWeightedEdge<int>>>);

// test is_edge_ptr
static_assert(CXXGraph::is_edge_ptr<CXXGraph::Edge<int>*>::value);
static_assert(CXXGraph::is_edge_ptr<CXXGraph::DirectedEdge<int>*>::value);
static_assert(
    CXXGraph::is_edge_ptr<CXXGraph::DirectedWeightedEdge<int>*>::value);
static_assert(CXXGraph::is_edge_ptr<CXXGraph::UndirectedEdge<int>*>::value);
static_assert(
    CXXGraph::is_edge_ptr<CXXGraph::UndirectedWeightedEdge<int>*>::value);
static_assert(CXXGraph::is_edge_ptr<const CXXGraph::Edge<int>*>::value);
static_assert(CXXGraph::is_edge_ptr<const CXXGraph::DirectedEdge<int>*>::value);
static_assert(
    CXXGraph::is_edge_ptr<const CXXGraph::DirectedWeightedEdge<int>*>::value);
static_assert(
    CXXGraph::is_edge_ptr<const CXXGraph::UndirectedEdge<int>*>::value);
static_assert(
    CXXGraph::is_edge_ptr<const CXXGraph::UndirectedWeightedEdge<int>*>::value);
static_assert(CXXGraph::is_edge_ptr<shared<CXXGraph::Edge<int>>>::value);
static_assert(
    CXXGraph::is_edge_ptr<shared<CXXGraph::DirectedEdge<int>>>::value);
static_assert(
    CXXGraph::is_edge_ptr<shared<CXXGraph::DirectedWeightedEdge<int>>>::value);
static_assert(
    CXXGraph::is_edge_ptr<shared<CXXGraph::UndirectedEdge<int>>>::value);
static_assert(CXXGraph::is_edge_ptr<
              shared<CXXGraph::UndirectedWeightedEdge<int>>>::value);
static_assert(CXXGraph::is_edge_ptr<shared<const CXXGraph::Edge<int>>>::value);
static_assert(
    CXXGraph::is_edge_ptr<shared<const CXXGraph::DirectedEdge<int>>>::value);
static_assert(CXXGraph::is_edge_ptr<
              shared<const CXXGraph::DirectedWeightedEdge<int>>>::value);
static_assert(
    CXXGraph::is_edge_ptr<shared<const CXXGraph::UndirectedEdge<int>>>::value);
static_assert(CXXGraph::is_edge_ptr<
              shared<const CXXGraph::UndirectedWeightedEdge<int>>>::value);

static_assert(CXXGraph::is_edge_ptr_v<CXXGraph::Edge<int>*>);
static_assert(CXXGraph::is_edge_ptr_v<CXXGraph::DirectedEdge<int>*>);
static_assert(CXXGraph::is_edge_ptr_v<CXXGraph::DirectedWeightedEdge<int>*>);
static_assert(CXXGraph::is_edge_ptr_v<CXXGraph::UndirectedEdge<int>*>);
static_assert(CXXGraph::is_edge_ptr_v<CXXGraph::UndirectedWeightedEdge<int>*>);
static_assert(CXXGraph::is_edge_ptr_v<const CXXGraph::Edge<int>*>);
static_assert(CXXGraph::is_edge_ptr_v<const CXXGraph::DirectedEdge<int>*>);
static_assert(
    CXXGraph::is_edge_ptr_v<const CXXGraph::DirectedWeightedEdge<int>*>);
static_assert(CXXGraph::is_edge_ptr_v<const CXXGraph::UndirectedEdge<int>*>);
static_assert(
    CXXGraph::is_edge_ptr_v<const CXXGraph::UndirectedWeightedEdge<int>*>);
static_assert(CXXGraph::is_edge_ptr_v<shared<CXXGraph::Edge<int>>>);
static_assert(CXXGraph::is_edge_ptr_v<shared<CXXGraph::DirectedEdge<int>>>);
static_assert(
    CXXGraph::is_edge_ptr_v<shared<CXXGraph::DirectedWeightedEdge<int>>>);
static_assert(CXXGraph::is_edge_ptr_v<shared<CXXGraph::UndirectedEdge<int>>>);
static_assert(
    CXXGraph::is_edge_ptr_v<shared<CXXGraph::UndirectedWeightedEdge<int>>>);
static_assert(CXXGraph::is_edge_ptr_v<shared<const CXXGraph::Edge<int>>>);
static_assert(
    CXXGraph::is_edge_ptr_v<shared<const CXXGraph::DirectedEdge<int>>>);
static_assert(
    CXXGraph::is_edge_ptr_v<shared<const CXXGraph::DirectedWeightedEdge<int>>>);
static_assert(
    CXXGraph::is_edge_ptr_v<shared<const CXXGraph::UndirectedEdge<int>>>);
static_assert(CXXGraph::is_edge_ptr_v<
              shared<const CXXGraph::UndirectedWeightedEdge<int>>>);

// test all_are_edge_ptrs
static_assert(
    CXXGraph::all_are_edge_ptrs<CXXGraph::Edge<int>*, CXXGraph::Edge<int>*,
                                CXXGraph::Edge<int>*>::value);
static_assert(CXXGraph::all_are_edge_ptrs<CXXGraph::DirectedEdge<int>*,
                                          CXXGraph::DirectedEdge<int>*,
                                          CXXGraph::DirectedEdge<int>*>::value);
static_assert(
    CXXGraph::all_are_edge_ptrs<CXXGraph::DirectedWeightedEdge<int>*,
                                CXXGraph::DirectedWeightedEdge<int>*,
                                CXXGraph::DirectedWeightedEdge<int>*>::value);
static_assert(CXXGraph::all_are_edge_ptrs<
              CXXGraph::UndirectedEdge<int>*, CXXGraph::UndirectedEdge<int>*,
              CXXGraph::UndirectedEdge<int>*>::value);
static_assert(
    CXXGraph::all_are_edge_ptrs<CXXGraph::UndirectedWeightedEdge<int>*,
                                CXXGraph::UndirectedWeightedEdge<int>*,
                                CXXGraph::UndirectedWeightedEdge<int>*>::value);
static_assert(CXXGraph::all_are_edge_ptrs<const CXXGraph::Edge<int>*,
                                          const CXXGraph::Edge<int>*,
                                          const CXXGraph::Edge<int>*>::value);
static_assert(
    CXXGraph::all_are_edge_ptrs<const CXXGraph::DirectedEdge<int>*,
                                const CXXGraph::DirectedEdge<int>*,
                                const CXXGraph::DirectedEdge<int>*>::value);
static_assert(CXXGraph::all_are_edge_ptrs<
              const CXXGraph::DirectedWeightedEdge<int>*,
              const CXXGraph::DirectedWeightedEdge<int>*,
              const CXXGraph::DirectedWeightedEdge<int>*>::value);
static_assert(
    CXXGraph::all_are_edge_ptrs<const CXXGraph::UndirectedEdge<int>*,
                                const CXXGraph::UndirectedEdge<int>*,
                                const CXXGraph::UndirectedEdge<int>*>::value);
static_assert(CXXGraph::all_are_edge_ptrs<
              const CXXGraph::UndirectedWeightedEdge<int>*,
              const CXXGraph::UndirectedWeightedEdge<int>*,
              const CXXGraph::UndirectedWeightedEdge<int>*>::value);
static_assert(CXXGraph::all_are_edge_ptrs<shared<CXXGraph::Edge<int>>,
                                          shared<CXXGraph::Edge<int>>,
                                          shared<CXXGraph::Edge<int>>>::value);
static_assert(
    CXXGraph::all_are_edge_ptrs<shared<CXXGraph::DirectedEdge<int>>,
                                shared<CXXGraph::DirectedEdge<int>>,
                                shared<CXXGraph::DirectedEdge<int>>>::value);
static_assert(CXXGraph::all_are_edge_ptrs<
              shared<CXXGraph::DirectedWeightedEdge<int>>,
              shared<CXXGraph::DirectedWeightedEdge<int>>,
              shared<CXXGraph::DirectedWeightedEdge<int>>>::value);
static_assert(
    CXXGraph::all_are_edge_ptrs<shared<CXXGraph::UndirectedEdge<int>>,
                                shared<CXXGraph::UndirectedEdge<int>>,
                                shared<CXXGraph::UndirectedEdge<int>>>::value);
static_assert(CXXGraph::all_are_edge_ptrs<
              shared<CXXGraph::UndirectedWeightedEdge<int>>,
              shared<CXXGraph::UndirectedWeightedEdge<int>>,
              shared<CXXGraph::UndirectedWeightedEdge<int>>>::value);
static_assert(
    CXXGraph::all_are_edge_ptrs<shared<const CXXGraph::Edge<int>>,
                                shared<const CXXGraph::Edge<int>>,
                                shared<const CXXGraph::Edge<int>>>::value);
static_assert(CXXGraph::all_are_edge_ptrs<
              shared<const CXXGraph::DirectedEdge<int>>,
              shared<const CXXGraph::DirectedEdge<int>>,
              shared<const CXXGraph::DirectedEdge<int>>>::value);
static_assert(CXXGraph::all_are_edge_ptrs<
              shared<const CXXGraph::DirectedWeightedEdge<int>>,
              shared<const CXXGraph::DirectedWeightedEdge<int>>,
              shared<const CXXGraph::DirectedWeightedEdge<int>>>::value);
static_assert(CXXGraph::all_are_edge_ptrs<
              shared<const CXXGraph::UndirectedEdge<int>>,
              shared<const CXXGraph::UndirectedEdge<int>>,
              shared<const CXXGraph::UndirectedEdge<int>>>::value);
static_assert(CXXGraph::all_are_edge_ptrs<
              shared<const CXXGraph::UndirectedWeightedEdge<int>>,
              shared<const CXXGraph::UndirectedWeightedEdge<int>>,
              shared<const CXXGraph::UndirectedWeightedEdge<int>>>::value);

static_assert(
    CXXGraph::all_are_edge_ptrs_v<CXXGraph::Edge<int>*, CXXGraph::Edge<int>*,
                                  CXXGraph::Edge<int>*>);
static_assert(CXXGraph::all_are_edge_ptrs_v<CXXGraph::DirectedEdge<int>*,
                                            CXXGraph::DirectedEdge<int>*,
                                            CXXGraph::DirectedEdge<int>*>);
static_assert(
    CXXGraph::all_are_edge_ptrs_v<CXXGraph::DirectedWeightedEdge<int>*,
                                  CXXGraph::DirectedWeightedEdge<int>*,
                                  CXXGraph::DirectedWeightedEdge<int>*>);
static_assert(CXXGraph::all_are_edge_ptrs_v<CXXGraph::UndirectedEdge<int>*,
                                            CXXGraph::UndirectedEdge<int>*,
                                            CXXGraph::UndirectedEdge<int>*>);
static_assert(
    CXXGraph::all_are_edge_ptrs_v<CXXGraph::UndirectedWeightedEdge<int>*,
                                  CXXGraph::UndirectedWeightedEdge<int>*,
                                  CXXGraph::UndirectedWeightedEdge<int>*>);
static_assert(CXXGraph::all_are_edge_ptrs_v<const CXXGraph::Edge<int>*,
                                            const CXXGraph::Edge<int>*,
                                            const CXXGraph::Edge<int>*>);
static_assert(
    CXXGraph::all_are_edge_ptrs_v<const CXXGraph::DirectedEdge<int>*,
                                  const CXXGraph::DirectedEdge<int>*,
                                  const CXXGraph::DirectedEdge<int>*>);
static_assert(
    CXXGraph::all_are_edge_ptrs_v<const CXXGraph::DirectedWeightedEdge<int>*,
                                  const CXXGraph::DirectedWeightedEdge<int>*,
                                  const CXXGraph::DirectedWeightedEdge<int>*>);
static_assert(
    CXXGraph::all_are_edge_ptrs_v<const CXXGraph::UndirectedEdge<int>*,
                                  const CXXGraph::UndirectedEdge<int>*,
                                  const CXXGraph::UndirectedEdge<int>*>);
static_assert(CXXGraph::all_are_edge_ptrs_v<
              const CXXGraph::UndirectedWeightedEdge<int>*,
              const CXXGraph::UndirectedWeightedEdge<int>*,
              const CXXGraph::UndirectedWeightedEdge<int>*>);
static_assert(CXXGraph::all_are_edge_ptrs_v<shared<CXXGraph::Edge<int>>,
                                            shared<CXXGraph::Edge<int>>,
                                            shared<CXXGraph::Edge<int>>>);
static_assert(
    CXXGraph::all_are_edge_ptrs_v<shared<CXXGraph::DirectedEdge<int>>,
                                  shared<CXXGraph::DirectedEdge<int>>,
                                  shared<CXXGraph::DirectedEdge<int>>>);
static_assert(
    CXXGraph::all_are_edge_ptrs_v<shared<CXXGraph::DirectedWeightedEdge<int>>,
                                  shared<CXXGraph::DirectedWeightedEdge<int>>,
                                  shared<CXXGraph::DirectedWeightedEdge<int>>>);
static_assert(
    CXXGraph::all_are_edge_ptrs_v<shared<CXXGraph::UndirectedEdge<int>>,
                                  shared<CXXGraph::UndirectedEdge<int>>,
                                  shared<CXXGraph::UndirectedEdge<int>>>);
static_assert(CXXGraph::all_are_edge_ptrs_v<
              shared<CXXGraph::UndirectedWeightedEdge<int>>,
              shared<CXXGraph::UndirectedWeightedEdge<int>>,
              shared<CXXGraph::UndirectedWeightedEdge<int>>>);
static_assert(CXXGraph::all_are_edge_ptrs_v<shared<const CXXGraph::Edge<int>>,
                                            shared<const CXXGraph::Edge<int>>,
                                            shared<const CXXGraph::Edge<int>>>);
static_assert(
    CXXGraph::all_are_edge_ptrs_v<shared<const CXXGraph::DirectedEdge<int>>,
                                  shared<const CXXGraph::DirectedEdge<int>>,
                                  shared<const CXXGraph::DirectedEdge<int>>>);
static_assert(CXXGraph::all_are_edge_ptrs_v<
              shared<const CXXGraph::DirectedWeightedEdge<int>>,
              shared<const CXXGraph::DirectedWeightedEdge<int>>,
              shared<const CXXGraph::DirectedWeightedEdge<int>>>);
static_assert(
    CXXGraph::all_are_edge_ptrs_v<shared<const CXXGraph::UndirectedEdge<int>>,
                                  shared<const CXXGraph::UndirectedEdge<int>>,
                                  shared<const CXXGraph::UndirectedEdge<int>>>);
static_assert(CXXGraph::all_are_edge_ptrs_v<
              shared<const CXXGraph::UndirectedWeightedEdge<int>>,
              shared<const CXXGraph::UndirectedWeightedEdge<int>>,
              shared<const CXXGraph::UndirectedWeightedEdge<int>>>);

#endif
