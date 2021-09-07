#include "gtest/gtest.h"
#include "CXXGraph.hpp"

TEST(NodeTest, Constructor_1)
{
    CXXGRAPH::Node<int> node(1, 1);
    ASSERT_EQ(node.getId(), 1);
    ASSERT_EQ(node.getData(), 1);
}

TEST(NodeTest, print_1)
{
    CXXGRAPH::Node<int> node(1, 1);
    std::cout << "Test Print Node" << std::endl;
    std::cout << node << std::endl;
}