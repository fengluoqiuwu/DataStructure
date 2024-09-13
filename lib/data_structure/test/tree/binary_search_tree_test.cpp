//
// Created by Eden_ on 2024/9/13.
//

#include <gtest/gtest.h>
#include "data_structure.h"

class BinarySearchTreeTest : public ::testing::Test {
protected:
    binary_search_tree<int>* test_tree=nullptr;
    int a[10]={18, 42, 96, 80, 65, 56, 32, 64, 89, 85};

    void SetUp() override {
        test_tree=new binary_search_tree(a,10);
    }

    void TearDown() override {
        delete test_tree;
    }
};

TEST_F(BinarySearchTreeTest,InitTest)
{
    ASSERT_EQ(test_tree->to_string(TreeData::PREORDER),"18 42 32 96 80 65 56 64 89 85");

    ASSERT_EQ(test_tree->to_string(TreeData::INORDER),"18 32 42 56 64 65 80 85 89 96");

    ASSERT_EQ(test_tree->to_string(TreeData::POSTORDER),"32 64 56 65 85 89 80 96 42 18");
}

TEST_F(BinarySearchTreeTest,ConstructorDefaultTest)
{
    const auto tree=new binary_search_tree<int>;

    ASSERT_TRUE(tree->is_empty());

    delete tree;
}

TEST_F(BinarySearchTreeTest,ConstructorWithSingleValueTest)
{
    auto tree = new binary_search_tree(0);

    ASSERT_EQ(tree->get_size(),1);
    ASSERT_EQ(*tree->begin(),0);

    delete tree;
}

TEST_F(BinarySearchTreeTest,ConstructorWithArrayOfValuesTest)
{
    ASSERT_EQ(test_tree->get_size(),10);
    ASSERT_EQ(*test_tree->begin(),18);
}

TEST_F(BinarySearchTreeTest,ConstructorWithLinkedListTest)
{
    const auto list = new linked_list(a,10);
    auto tree = new binary_search_tree<int>(*list);

    ASSERT_TRUE(*tree==*test_tree);

    delete tree;
    delete list;
}

TEST_F(BinarySearchTreeTest,ConstructorCopyTest)
{
    auto tree = new binary_search_tree(*test_tree);

    ASSERT_TRUE(*tree==*test_tree);

    delete tree;
}

TEST_F(BinarySearchTreeTest,ConstructorMoveTest)
{
    auto tree = new binary_search_tree(std::move(*test_tree));

    ASSERT_EQ(tree->to_string(TreeData::PREORDER),"18 42 32 96 80 65 56 64 89 85");

    ASSERT_EQ(tree->to_string(TreeData::INORDER),"18 32 42 56 64 65 80 85 89 96");

    ASSERT_EQ(tree->to_string(TreeData::POSTORDER),"32 64 56 65 85 89 80 96 42 18");

    ASSERT_TRUE(test_tree->is_empty());

    delete tree;
}

TEST_F(BinarySearchTreeTest,OperatorCopyTest)
{
    auto tree = *test_tree;
    tree = *test_tree;

    ASSERT_TRUE(tree==*test_tree);
}

TEST_F(BinarySearchTreeTest,OperatorMoveTest)
{
    auto tree = *test_tree;
    tree = std::move(*test_tree);

    ASSERT_EQ(tree.to_string(TreeData::PREORDER),"18 42 32 96 80 65 56 64 89 85");

    ASSERT_EQ(tree.to_string(TreeData::INORDER),"18 32 42 56 64 65 80 85 89 96");

    ASSERT_EQ(tree.to_string(TreeData::POSTORDER),"32 64 56 65 85 89 80 96 42 18");

    ASSERT_TRUE(test_tree->is_empty());
}

TEST_F(BinarySearchTreeTest,OperatorEqualTest)
{
    const auto tree = *test_tree;
    ASSERT_TRUE(tree==*test_tree);
}

TEST_F(BinarySearchTreeTest,FunctionInsertTest)
{
    test_tree->insert(5);

    ASSERT_EQ(test_tree->to_string(TreeData::PREORDER),"18 5 42 32 96 80 65 56 64 89 85");

    ASSERT_EQ(test_tree->to_string(TreeData::INORDER),"5 18 32 42 56 64 65 80 85 89 96");

    ASSERT_EQ(test_tree->to_string(TreeData::POSTORDER),"5 32 64 56 65 85 89 80 96 42 18");
}

TEST_F(BinarySearchTreeTest,FunctionRemoveTest)
{
    test_tree->remove(18);

    ASSERT_EQ(test_tree->to_string(TreeData::PREORDER),"42 32 96 80 65 56 64 89 85");

    ASSERT_EQ(test_tree->to_string(TreeData::INORDER),"32 42 56 64 65 80 85 89 96");

    ASSERT_EQ(test_tree->to_string(TreeData::POSTORDER),"32 64 56 65 85 89 80 96 42");

    test_tree->remove(42);

    ASSERT_EQ(test_tree->to_string(TreeData::PREORDER),"56 32 96 80 65 64 89 85");

    ASSERT_EQ(test_tree->to_string(TreeData::INORDER),"32 56 64 65 80 85 89 96");

    ASSERT_EQ(test_tree->to_string(TreeData::POSTORDER),"32 64 65 85 89 80 96 56");
}

TEST_F(BinarySearchTreeTest,FunctionGetMinTest)
{
    ASSERT_EQ(test_tree->get_min(),18);
}

TEST_F(BinarySearchTreeTest,FunctionGetMaxTest)
{
    ASSERT_EQ(test_tree->get_max(),96);
}