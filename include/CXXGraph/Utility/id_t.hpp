#pragma once

#ifdef CXXGRAPH_ID_TYPE
#include <type_traits>
#else
#include <cstddef>
#endif

namespace CXXGraph {
#ifdef CXXGRAPH_ID_TYPE
// Throw compiler error if the type is signed
static_assert(std::is_unsigned_v<CXXGRAPH_ID_TYPE>,
              "CXXGRAPH_ID_TYPE must be unsigned");

using id_t = CXXGRAPH_ID_TYPE;
#else
using id_t = std::size_t;
#endif
}  // namespace CXXGraph
