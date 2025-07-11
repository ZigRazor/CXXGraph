/***********************************************************/
/***      ______  ____  ______                 _         ***/
/***     / ___\ \/ /\ \/ / ___|_ __ __ _ _ __ | |__	     ***/
/***    | |    \  /  \  / |  _| '__/ _` | '_ \| '_ \	 ***/
/***    | |___ /  \  /  \ |_| | | | (_| | |_) | | | |    ***/
/***     \____/_/\_\/_/\_\____|_|  \__,_| .__/|_| |_|    ***/
/***                                    |_|			     ***/
/***********************************************************/
/***     Header-Only C++ Library for Graph			     ***/
/***	 Representation and Algorithms				     ***/
/***********************************************************/
/***     Author: ZigRazor ***/
/***	 E-Mail: zigrazor@gmail.com 				     ***/
/***********************************************************/
/***	 Collaboration: ----------- 				     ***/
/***********************************************************/
/***	 License: MPL v2.0 ***/
/***********************************************************/

#ifndef __CXXGRAPH_NODE_IMPL_H__
#define __CXXGRAPH_NODE_IMPL_H__

#if __cplusplus >= 202004L
#include <bitset>
#else
#include <cstring>
#endif

#include <iomanip>
#include <limits>
#include <type_traits>

#include "Node_decl.h"

namespace CXXGraph {
// internals not intended to be accessed by the end user
namespace internals {
template <typename AnyUserID>
constexpr CXXGraph::id_t UserIdToId(const AnyUserID &id) {
  // in C++ 23 we have constexpr hashes
  if constexpr (__cplusplus >= 202302L) return std::hash<AnyUserID>{}(id);
  // hashing is trivial for integral types
  if constexpr (std::is_integral<AnyUserID>::value) {
    // assert nothing is greater than a size_t to avoid issues with GCC and
    // clang's 128 bit ints, a size_t is usually 64 bits
    static_assert(std::numeric_limits<CXXGraph::id_t>::max() >=
                  std::numeric_limits<AnyUserID>::max());

    if constexpr (std::is_signed<AnyUserID>::value) {
      // Add id to half max so that we have something unique
      return (std::numeric_limits<CXXGraph::id_t>::max() / 2) + id;
    }
    return static_cast<CXXGraph::id_t>(id);
  }
  // typepun the float into an int
  if constexpr (std::is_floating_point<AnyUserID>::value) {
    // static assert to avoid long double (80 bits rather than 64)
    static_assert(sizeof(CXXGraph::id_t) >= sizeof(AnyUserID));
// In C++20 we can do typepunning at compile time
#if __cplusplus >= 202004L
    return std::bit_cast<CXXGraph::id_t>(id);
#else   // < C++20
    // otherwise use memcpy (not compile time)
    CXXGraph::id_t result{};
    std::memcpy(&result, &id, sizeof(id));
    return result;
#endif  // >= C++20
  }
  // resort back to runtime hash
  return std::hash<AnyUserID>{}(id);
}
}  // namespace internals

template <typename T, typename UserID>
class Node;

template <typename T, typename UserID>
constexpr Node<T, UserID>::Node(const UserID &otherId, const T &otherData)
    : id(internals::UserIdToId(otherId)), userId(otherId), data(otherData) {
  static_assert(
      !std::is_pointer<UserID>::value,
      "Pointer is not allowed as an ID type, did you mean std::string?");
}

template <typename T, typename UserID>
constexpr Node<T, UserID>::Node(const UserID &otherId, T &&otherData) noexcept(
    std::is_nothrow_move_assignable<T>::value)
    : id(internals::UserIdToId(otherId)), userId(otherId), data(otherData) {
  static_assert(
      !std::is_pointer<UserID>::value,
      "Pointer is not allowed as an ID type, did you mean std::string?");
}

template <typename T, typename UserID>
constexpr void Node<T, UserID>::setId(const UserID &inputId) {
  this->id = UserIdToId(inputId);
}

template <typename T, typename UserID>
constexpr const CXXGraph::id_t &Node<T, UserID>::getId() const {
  return id;
}

template <typename T, typename UserID>
constexpr const UserID &Node<T, UserID>::getUserId() const {
  return userId;
}

template <typename T, typename UserID>
constexpr const T &Node<T, UserID>::getData() const {
  return data;
}

template <typename T, typename UserID>
constexpr T &Node<T, UserID>::getData() {
  return data;
}

template <typename T, typename UserID>
constexpr void Node<T, UserID>::setData(T &&new_data) {
  this->data = std::move(new_data);
}

// The data type T must have an overload of the equality operator
template <typename T, typename UserID>
constexpr bool Node<T, UserID>::operator==(const Node<T, UserID> &b) const {
  return (this->id == b.id && this->data == b.data);
}

template <typename T, typename UserID>
constexpr bool Node<T, UserID>::operator<(const Node<T, UserID> &b) const {
  return (this->id < b.id);
}

// ostream overload
// The data type T must have an overload of the ostream operator
template <typename T, typename UserID>
std::ostream &operator<<(std::ostream &os, const Node<T, UserID> &node) {
  os << "Node: {\n"
     << "  Id:\t" << node.userId << "\n  Data:\t" << node.data << "\n}";
  return os;
}

}  // namespace CXXGraph

#endif  // __CXXGRAPH_NODE_IMPL_H__
