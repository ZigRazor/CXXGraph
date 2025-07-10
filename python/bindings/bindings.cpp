#include <pybind11/functional.h>  // for std::function support
#include <pybind11/operators.h>
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include "CXXGraph/CXXGraph.hpp"

namespace py = pybind11;

PYBIND11_MODULE(cxxgraph, m) {
  py::class_<CXXGraph::Node<int>>(m, "Node")
      .def(py::init<const std::string &, const int &>(), py::arg("user_id"),
           py::arg("data"))
      .def(py::init<const std::string &, int &&>(), py::arg("user_id"),
           py::arg("data"))

      // Read-only property accessors
      .def("get_id", &CXXGraph::Node<int>::getId)
      .def("get_user_id", &CXXGraph::Node<int>::getUserId)
      .def("get_data", static_cast<const int &(CXXGraph::Node<int>::*)() const>(
                           &CXXGraph::Node<int>::getData))
      .def("get_data_mut", static_cast<int &(CXXGraph::Node<int>::*)()>(
                               &CXXGraph::Node<int>::getData))

      // Mutator
      .def("set_data", &CXXGraph::Node<int>::setData)

      // Operators
      .def(py::self == py::self)
      .def(py::self < py::self)

      // String representation
      .def("__repr__", [](const CXXGraph::Node<int> &n) {
        std::ostringstream oss;
        oss << n;
        return oss.str();
      });

  py::class_<CXXGraph::Edge<int>>(m, "Edge").def(
      py::init<const CXXGraph::id_t, const CXXGraph::Node<int> &,
               const CXXGraph::Node<int> &>());  // default ctor,

  py::class_<CXXGraph::Graph<int>>(m, "Graph")
      .def(py::init<>())  // default ctor, no bool argument
      .def("add_node",
           static_cast<void (CXXGraph::Graph<int>::*)(
               const CXXGraph::Node<int> *)>(&CXXGraph::Graph<int>::addNode))
      .def("add_edge",
           static_cast<void (CXXGraph::Graph<int>::*)(
               const CXXGraph::Edge<int> *)>(&CXXGraph::Graph<int>::addEdge))

      .def("dfs", &CXXGraph::Graph<int>::depth_first_search);
}
