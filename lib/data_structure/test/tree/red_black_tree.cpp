//
// Created by Eden_ on 2024/9/15.
//

#include <gtest/gtest.h>
#include "data_structure.h"

class RedBlackTreeTest : public testing::Test
{
protected:
    red_black_tree<int>* test_tree=nullptr;
    int a[10]={18, 42, 96, 80, 65, 56, 32, 64, 89, 85};

    void SetUp() override {
        test_tree=new red_black_tree(a,10);
    }

    void TearDown() override {
        delete test_tree;
    }
};

TEST_F(RedBlackTreeTest,InitTest)
{
    ASSERT_EQ(test_tree->to_string(TreeData::PREORDER),"42 18 32 80 64 56 65 89 85 96");

    ASSERT_EQ(test_tree->to_string(TreeData::INORDER),"18 32 42 56 64 65 80 85 89 96");

    ASSERT_EQ(test_tree->to_string(TreeData::POSTORDER),"32 18 56 65 64 85 96 89 80 42");
}

TEST_F(RedBlackTreeTest,ConstructorDefaultTest)
{
    const auto tree = new red_black_tree<int>();
    ASSERT_TRUE(tree->is_empty());
    delete tree;
}

TEST_F(RedBlackTreeTest,ConstructorWithSingleValueTest)
{
    const auto tree = new red_black_tree(10);
    ASSERT_EQ(tree->get_size(),1);
    ASSERT_EQ(*tree->begin(),10);
    delete tree;
}

TEST_F(RedBlackTreeTest,ConstructorWithArrayOfValuesTest)
{
    ASSERT_EQ(*test_tree->begin(),18);
}

TEST_F(RedBlackTreeTest,ConstructorWithLinkedListTest)
{
    const auto list = new linked_list(a,10);
    const auto tree = new red_black_tree<int>(*list);

    ASSERT_TRUE(*test_tree==*tree);

    delete tree;
    delete list;
}

TEST_F(RedBlackTreeTest,ConstructorCopyTest)
{
    const auto tree = new red_black_tree(*test_tree);

    ASSERT_TRUE(*test_tree==*tree);

    delete tree;
}

TEST_F(RedBlackTreeTest,ConstructorMoveTest)
{
    auto tree = new red_black_tree(*test_tree);
    const auto tree2 = new red_black_tree<int>(std::move(*tree));

    ASSERT_TRUE(*test_tree==*tree2);
    ASSERT_TRUE(tree->is_empty());

    delete tree;
    delete tree2;
}

TEST_F(RedBlackTreeTest,OperatorCopyTest)
{
    auto tree = *test_tree;
    tree = *test_tree;

    ASSERT_TRUE(*test_tree==tree);
}

TEST_F(RedBlackTreeTest,OperatorMoveTest)
{
    auto tree = new red_black_tree(*test_tree);
    auto tree2 = *tree;
    tree2 = std::move(*tree);

    ASSERT_TRUE(*test_tree==tree2);
    ASSERT_TRUE(tree->is_empty());

    delete tree;
}

TEST_F(RedBlackTreeTest,OperatorEqualTest)
{
    auto tree = new red_black_tree(*test_tree);
    ASSERT_TRUE(*test_tree==*tree);
    delete tree;
}

TEST_F(RedBlackTreeTest,FunctionInsertTest)
{
    test_tree->insert(11);

    ASSERT_EQ(test_tree->to_string(TreeData::PREORDER),"42 18 11 32 80 64 56 65 89 85 96");

    ASSERT_EQ(test_tree->to_string(TreeData::INORDER),"11 18 32 42 56 64 65 80 85 89 96");

    ASSERT_EQ(test_tree->to_string(TreeData::POSTORDER),"11 32 18 56 65 64 85 96 89 80 42");
}

TEST_F(RedBlackTreeTest,FunctionRemoveTest)
{
    test_tree->insert(11);
    test_tree->remove(11);

    ASSERT_EQ(test_tree->to_string(TreeData::PREORDER),"42 18 32 80 64 56 65 89 85 96");

    ASSERT_EQ(test_tree->to_string(TreeData::INORDER),"18 32 42 56 64 65 80 85 89 96");

    ASSERT_EQ(test_tree->to_string(TreeData::POSTORDER),"32 18 56 65 64 85 96 89 80 42");

    test_tree->remove(65);
    test_tree->remove(56);
    test_tree->remove(64);

    ASSERT_EQ(test_tree->to_string(TreeData::PREORDER),"42 18 32 89 80 85 96");

    ASSERT_EQ(test_tree->to_string(TreeData::INORDER),"18 32 42 80 85 89 96");

    ASSERT_EQ(test_tree->to_string(TreeData::POSTORDER),"32 18 85 80 96 89 42");
}