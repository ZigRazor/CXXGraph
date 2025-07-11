
#include <memory>

#include "CXXGraph/CXXGraph.hpp"
#include "gtest/gtest.h"

// Boolean results will always be true
//  functions are only here to test that this compiles
constexpr bool IsConstexprContextCreateable() {
	CXXGraph::Node<int, size_t> node1(1, 1);
	return true;
}

constexpr bool IsConstexprCreateable() {
	constexpr CXXGraph::Node<int, size_t> node1(1, 1);
	return true;
}


TEST(ConstexprTests, IsConstexprContextCreateable) {
	ASSERT_TRUE(IsConstexprContextCreateable());
}

TEST(ConstexprTests, IsConstexprCreateable) {
	ASSERT_TRUE(IsConstexprCreateable());
}