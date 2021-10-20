#include "gtest/gtest.h"
#include "CXXGraph.hpp"

// Struct for testing Node as a template of different items
struct testStruct {
    int testInt = 0;
    bool testBool = true;
    std::string testString = "abc";

    testStruct() = default; 
    explicit testStruct(int a, bool b, const std::string& c)
    : testInt(a), testBool(b), testString(c){};      
    
	bool operator==(const testStruct &b) const {
        return (
            this->testInt == b.testInt &&
            this->testBool == b.testBool &&
            this->testString == b.testString);
    };
};

std::ostream &operator<<(std::ostream &os, const testStruct &TestStruct)
{
	os << TestStruct.testInt << " " << TestStruct.testBool<< " " << TestStruct.testString;
	return os;
}


TEST(NodeTest, Constructor)
{
    // Testing constructor and getters with different types of data
    int intTest = 42;
    float floatTest = 3.14;
    double doubleTest = 3.1416;
    bool boolTest = true;
    char charTest = 'w';
    std::string stringTest = "myStr";
    std::vector<int> vectorTest = {1,2,3,4};
    std::map<int,int> mapTest = {{1,2},{3,4},{5,6},{7,8}};
    testStruct structTest(42, true, "abc");

    CXXGRAPH::Node<int> intNode(1, intTest);
    CXXGRAPH::Node<float> floatNode(2, floatTest);
    CXXGRAPH::Node<double> doubleNode(3, doubleTest);
    CXXGRAPH::Node<bool> boolNode(4, boolTest);
    CXXGRAPH::Node<char> charNode(5, charTest);
    CXXGRAPH::Node<std::string> stringNode(6, stringTest);
    CXXGRAPH::Node<std::vector<int>> vectorNode(7, vectorTest);
    CXXGRAPH::Node<std::map<int,int>> mapNode(8, mapTest);
    CXXGRAPH::Node<testStruct> structNode(9, structTest);

    ASSERT_EQ(intNode.getId(), 1);
    ASSERT_EQ(intNode.getData(), intTest);
    ASSERT_EQ(floatNode.getId(), 2);
    ASSERT_EQ(floatNode.getData(), floatTest);
    ASSERT_EQ(doubleNode.getId(), 3);
    ASSERT_EQ(doubleNode.getData(), doubleTest);
    ASSERT_EQ(boolNode.getId(), 4);
    ASSERT_EQ(boolNode.getData(), boolTest);
    ASSERT_EQ(charNode.getId(), 5);
    ASSERT_EQ(charNode.getData(), charTest);
    ASSERT_EQ(stringNode.getId(), 6);
    ASSERT_EQ(stringNode.getData(), stringTest);
    ASSERT_EQ(vectorNode.getId(), 7);
    ASSERT_EQ(vectorNode.getData(), vectorTest);
    ASSERT_EQ(mapNode.getId(), 8);
    ASSERT_EQ(mapNode.getData(), mapTest);
    ASSERT_EQ(structNode.getId(), 9);
    ASSERT_EQ(structNode.getData(), structTest);
}

TEST(NodeTest, eqOperator)
{
    // Testing equal operator with different types of data
    int int1 = 2;
    int int2 = 2;
    double double1 = 4.3210;
    double double2 = 0.1234;
    std::string string1 = "abc";
    std::string string2 = "abc";
    testStruct struct1(42, true, "abc");
    testStruct struct2(41, true, "cba");

    CXXGRAPH::Node<int> nodeInt1(1, int1);
    CXXGRAPH::Node<int> nodeInt2(1, int2);
    CXXGRAPH::Node<double> nodeDouble1(2, double1);
    CXXGRAPH::Node<double> nodeDouble2(2, double2);
    CXXGRAPH::Node<std::string> nodeString1(1, string1);
    CXXGRAPH::Node<std::string> nodeString2(2, string2);
    CXXGRAPH::Node<testStruct> nodeStruct1(1, struct1);
    CXXGRAPH::Node<testStruct> nodeStruct2(2, struct2);

    ASSERT_TRUE(nodeInt1 == nodeInt2); // Equal nodes
    ASSERT_FALSE(nodeDouble1 == nodeDouble2);   // different data
    ASSERT_FALSE(nodeString1 == nodeString2);   // different id
    ASSERT_FALSE(nodeStruct1 == nodeStruct2);   // completely different
}

TEST(NodeTest, ltOperator)
{
    // Testing Less Than operator with different types of data
    int int1 = 2;
    int int2 = 2;
    double double1 = 4.321;
    double double2 = 1.234;
    std::string string1 = "abc";
    std::string string2 = "abc";
    testStruct struct1(42, true, "abc");
    testStruct struct2(41, true, "cba");

    CXXGRAPH::Node<int> nodeInt1(1, int1);
    CXXGRAPH::Node<int> nodeInt2(1, int2);
    CXXGRAPH::Node<double> nodeDouble1(2, double1);
    CXXGRAPH::Node<double> nodeDouble2(2, double2);
    CXXGRAPH::Node<std::string> nodeString1(1, string1);
    CXXGRAPH::Node<std::string> nodeString2(2, string2);
    CXXGRAPH::Node<testStruct> nodeStruct1(2, struct1);
    CXXGRAPH::Node<testStruct> nodeStruct2(1, struct2);

    ASSERT_FALSE(nodeInt1 < nodeInt2); // Same id same data
    ASSERT_FALSE(nodeDouble1 < nodeDouble2);   // Same id different data
    ASSERT_TRUE(nodeString1 < nodeString2);   // Different id different id
    ASSERT_FALSE(nodeStruct1 < nodeStruct2);   // completely different
}

TEST(NodeTest, printOperator)
{
    // Testing << operator with different types of data
    int nodesId = 1;
    int testInt = 2;
    double testDouble = 4.321;
    std::string testString = "abc";
    testStruct TestStruct(42, true, "abc");
    std::ostringstream expectedInt, expectedDouble, expectedString, expectedStruct;
    expectedInt << "Node: {\n  Id:\t1\n  Data:\t2\n}";
    expectedDouble << "Node: {\n  Id:\t1\n  Data:\t4.321\n}";
    expectedString << "Node: {\n  Id:\t1\n  Data:\tabc\n}";
    expectedStruct << "Node: {\n  Id:\t1\n  Data:\t42 1 abc\n}";

    CXXGRAPH::Node<int> intNode(nodesId, testInt);
    CXXGRAPH::Node<double> doubleNode(nodesId, testDouble);
    CXXGRAPH::Node<std::string> stringNode(nodesId, testString);
    CXXGRAPH::Node<testStruct> structNode(nodesId, TestStruct);

    std::ostringstream resultInt, resultDouble, resultString, resultStruct;
    resultInt << intNode;
    resultDouble << doubleNode;
    resultString << stringNode;
    resultStruct << structNode;
    ASSERT_EQ(resultInt.str(), expectedInt.str());
    ASSERT_EQ(resultDouble.str(), expectedDouble.str());
    ASSERT_EQ(resultString.str(), expectedString.str());
    ASSERT_EQ(resultStruct.str(), expectedStruct.str());
}