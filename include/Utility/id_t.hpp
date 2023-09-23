#pragma once

#include <type_traits>

#define IS_UNSIGNED(T) !(((T)-1) < 0)

namespace CXXGraph {
#ifdef CXXGRAPH_ID_TYPE
    // Throw compiler error if the type is signed
    static_assert(IS_UNSIGNED(CXXGRAPH_ID_TYPE), "CXXGRAPH_ID_TYPE must be unsigned");

    typedef CXXGRAPH_ID_TYPE id_t;
#else
    typedef size_t id_t;
#endif
}
