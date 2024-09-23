//
// Created by Eden_ on 2024/9/14.
//

#include <gtest/gtest.h>
#include "data_structure.h"

class AVLTreeTest : public testing::Test
{
protected:
    AVL_tree<int>* test_tree=nullptr;
    int a[10]={18, 42, 96, 80, 65, 56, 32, 64, 89, 85};

    void SetUp() override {
        test_tree=new AVL_tree(a,10);
    }

    void TearDown() override {
        delete test_tree;
    }
};

TEST_F(AVLTreeTest,InitTest)
{
    ASSERT_EQ(test_tree->to_string(TreeData::PREORDER),"65 42 18 32 56 64 89 80 85 96");

    ASSERT_EQ(test_tree->to_string(TreeData::INORDER),"18 32 42 56 64 65 80 85 89 96");

    ASSERT_EQ(test_tree->to_string(TreeData::POSTORDER),"32 18 64 56 42 85 80 96 89 65");
}

TEST_F(AVLTreeTest,ConstructorDefaultTest)
{
    const auto tree = new AVL_tree<int>();
    ASSERT_TRUE(tree->is_empty());
    delete tree;
}

TEST_F(AVLTreeTest,ConstructorWithSingleValueTest)
{
    const auto tree = new AVL_tree(10);
    ASSERT_EQ(tree->get_size(),1);
    ASSERT_EQ(*tree->begin(),10);
    delete tree;
}

TEST_F(AVLTreeTest,ConstructorWithArrayOfValuesTest)
{
    ASSERT_EQ(*test_tree->begin(),18);
}

TEST_F(AVLTreeTest,ConstructorWithLinkedListTest)
{
    const auto list = new linked_list(a,10);
    const auto tree = new AVL_tree<int>(*list);

    ASSERT_TRUE(*test_tree==*tree);

    delete tree;
    delete list;
}

TEST_F(AVLTreeTest,ConstructorCopyTest)
{
    const auto tree = new AVL_tree(*test_tree);

    ASSERT_TRUE(*test_tree==*tree);

    delete tree;
}

TEST_F(AVLTreeTest,ConstructorMoveTest)
{
    auto tree = new AVL_tree(*test_tree);
    const auto tree2 = new AVL_tree<int>(std::move(*tree));

    ASSERT_TRUE(*test_tree==*tree2);
    ASSERT_TRUE(tree->is_empty());

    delete tree;
    delete tree2;
}

TEST_F(AVLTreeTest,OperatorCopyTest)
{
    auto tree = *test_tree;
    tree = *test_tree;

    ASSERT_TRUE(*test_tree==tree);
}

TEST_F(AVLTreeTest,OperatorMoveTest)
{
    auto tree = new AVL_tree(*test_tree);
    auto tree2 = *tree;
    tree2 = std::move(*tree);

    ASSERT_TRUE(*test_tree==tree2);
    ASSERT_TRUE(tree->is_empty());

    delete tree;
}

TEST_F(AVLTreeTest,OperatorEqualTest)
{
    auto tree = new AVL_tree(*test_tree);
    ASSERT_TRUE(*test_tree==*tree);
    delete tree;
}

TEST_F(AVLTreeTest,FunctionInsertTest)
{
    test_tree->insert(11);

    ASSERT_EQ(test_tree->to_string(TreeData::PREORDER),"65 42 18 11 32 56 64 89 80 85 96");

    ASSERT_EQ(test_tree->to_string(TreeData::INORDER),"11 18 32 42 56 64 65 80 85 89 96");

    ASSERT_EQ(test_tree->to_string(TreeData::POSTORDER),"11 32 18 64 56 42 85 80 96 89 65");
}

TEST_F(AVLTreeTest,FunctionRemoveTest)
{
    test_tree->insert(11);
    test_tree->remove(11);

    ASSERT_EQ(test_tree->to_string(TreeData::PREORDER),"65 42 18 32 56 64 89 80 85 96");

    ASSERT_EQ(test_tree->to_string(TreeData::INORDER),"18 32 42 56 64 65 80 85 89 96");

    ASSERT_EQ(test_tree->to_string(TreeData::POSTORDER),"32 18 64 56 42 85 80 96 89 65");

    test_tree->remove(65);

    ASSERT_EQ(test_tree->to_string(TreeData::PREORDER),"80 42 18 32 56 64 89 85 96");

    ASSERT_EQ(test_tree->to_string(TreeData::INORDER),"18 32 42 56 64 80 85 89 96");

    ASSERT_EQ(test_tree->to_string(TreeData::POSTORDER),"32 18 64 56 42 85 96 89 80");
}

TEST_F(AVLTreeTest,FunctionGetDepthTest)
{
    ASSERT_EQ(test_tree->get_depth(),4);
}
