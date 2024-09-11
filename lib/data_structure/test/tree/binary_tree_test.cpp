//
// Created by Eden_ on 2024/9/11.
//

#include <gtest/gtest.h>
#include "data_structure.h"

class BinaryTreeTest : public ::testing::Test {
protected:
    binary_tree<int>* test_tree=nullptr;
    int a[17]={1,2,3,4,0,0,0,5,0,6,0,0,7,0,8,0,0};

    void SetUp() override {
        test_tree=new binary_tree<int>(a,17,0);
    }

    void TearDown() override {
        delete test_tree;
    }
};

TEST_F(BinaryTreeTest,InitTest){
    ASSERT_EQ(test_tree->to_string(TreeData::PREORDER),"1 2 3 4 6 5 8 7");

    ASSERT_EQ(test_tree->to_string(TreeData::INORDER),"4 3 2 5 6 1 7 8");

    ASSERT_EQ(test_tree->to_string(TreeData::POSTORDER),"4 3 6 5 2 8 7 1");
}

TEST_F(BinaryTreeTest,ConstructorDefaultTest)
{
    const auto tree = new binary_tree<int>();

    ASSERT_TRUE(tree->begin()==tree->end());

    delete tree;
}

TEST_F(BinaryTreeTest,ConstructorWithASingleValueTest)
{
    const auto tree = new binary_tree<int>(1);

    ASSERT_TRUE(*tree->begin()==1);
    binary_tree<int>::Iterator it=tree->begin();++it;
    ASSERT_TRUE(it==tree->end());

    delete tree;
}

TEST_F(BinaryTreeTest,ConstructorWithAPreorderArrayTest)
{
    ASSERT_EQ(test_tree->to_string(TreeData::PREORDER),"1 2 3 4 6 5 8 7");

    ASSERT_EQ(test_tree->to_string(TreeData::INORDER),"4 3 2 5 6 1 7 8");

    ASSERT_EQ(test_tree->to_string(TreeData::POSTORDER),"4 3 6 5 2 8 7 1");
}

TEST_F(BinaryTreeTest,ConstructorWithAPreorderLinkedListTest)
{
    const auto init_list = new linked_list<int>(a,17);
    const auto tree = new binary_tree<int>(*init_list,0);

    ASSERT_EQ(tree->to_string(TreeData::PREORDER),"1 2 3 4 6 5 8 7");

    ASSERT_EQ(tree->to_string(TreeData::INORDER),"4 3 2 5 6 1 7 8");

    ASSERT_EQ(tree->to_string(TreeData::POSTORDER),"4 3 6 5 2 8 7 1");

    delete init_list;
    delete tree;
}

TEST_F(BinaryTreeTest,ConstructorCopyTest)
{
    const auto tree = new binary_tree<int>(*test_tree);

    ASSERT_EQ(tree->to_string(TreeData::PREORDER),"1 2 3 4 6 5 8 7");

    ASSERT_EQ(tree->to_string(TreeData::INORDER),"4 3 2 5 6 1 7 8");

    ASSERT_EQ(tree->to_string(TreeData::POSTORDER),"4 3 6 5 2 8 7 1");

    delete tree;
}

TEST_F(BinaryTreeTest,ConstructorMoveTest)
{
    const auto tree = new binary_tree<int>(std::move(*test_tree));

    ASSERT_EQ(tree->to_string(TreeData::PREORDER),"1 2 3 4 6 5 8 7");

    ASSERT_EQ(tree->to_string(TreeData::INORDER),"4 3 2 5 6 1 7 8");

    ASSERT_EQ(tree->to_string(TreeData::POSTORDER),"4 3 6 5 2 8 7 1");

    ASSERT_TRUE(test_tree->is_empty());

    delete tree;
}

TEST_F(BinaryTreeTest,OperatorCopyTest)
{
    auto tree = *test_tree;
    tree = *test_tree;

    ASSERT_EQ(tree.to_string(TreeData::PREORDER),"1 2 3 4 6 5 8 7");

    ASSERT_EQ(tree.to_string(TreeData::INORDER),"4 3 2 5 6 1 7 8");

    ASSERT_EQ(tree.to_string(TreeData::POSTORDER),"4 3 6 5 2 8 7 1");
}

TEST_F(BinaryTreeTest,OperatorMoveTest)
{
    auto tree = *test_tree;
    tree = std::move(*test_tree);

    ASSERT_EQ(tree.to_string(TreeData::PREORDER),"1 2 3 4 6 5 8 7");

    ASSERT_EQ(tree.to_string(TreeData::INORDER),"4 3 2 5 6 1 7 8");

    ASSERT_EQ(tree.to_string(TreeData::POSTORDER),"4 3 6 5 2 8 7 1");
}

TEST_F(BinaryTreeTest,OperatorEqualTest)
{
    const auto tree = new binary_tree<int>(*test_tree);

    ASSERT_TRUE(*tree==*test_tree);

    delete tree;
}

TEST_F(BinaryTreeTest,FunctionSearchTest)
{
    ASSERT_TRUE(test_tree->search(1));
    ASSERT_FALSE(test_tree->search(0));
}

TEST_F(BinaryTreeTest,FunctionOrderTest)
{
    ASSERT_EQ(test_tree->to_string(TreeData::PREORDER),"1 2 3 4 6 5 8 7");

    ASSERT_EQ(test_tree->to_string(TreeData::INORDER),"4 3 2 5 6 1 7 8");

    ASSERT_EQ(test_tree->to_string(TreeData::POSTORDER),"4 3 6 5 2 8 7 1");
}

TEST_F(BinaryTreeTest,FunctionClearTest)
{
    test_tree->clear();

    ASSERT_TRUE(test_tree->is_empty());
}

TEST_F(BinaryTreeTest,FunctionIsEmptyTest)
{
    const auto tree = new binary_tree<int>();

    ASSERT_TRUE(tree->is_empty());

    delete tree;
}

TEST_F(BinaryTreeTest,FunctionGetDepthTest)
{
    ASSERT_EQ(test_tree->get_depth(),4);
}

TEST_F(BinaryTreeTest,FunctionGetSizeTest)
{
    ASSERT_EQ(test_tree->get_size(),8);
}

TEST_F(BinaryTreeTest,IteratorTest)
{
    auto it = test_tree->begin();
    *it=-1;
    ASSERT_EQ(*it,-1);
    ASSERT_TRUE(it.has_left());
    ASSERT_TRUE(it.has_right());

    const auto left=it.get_left();
    const auto right=it.get_right();
    ASSERT_EQ(*left,2);
    ASSERT_EQ(*right,7);
    ASSERT_FALSE(right.has_left());
    ASSERT_TRUE(right.get_parent()==it);

    it.left();
    ASSERT_EQ(*it,2);
    it.parent();
    ASSERT_EQ(*it,-1);
    it.right();
    ASSERT_EQ(*it,7);
    it.parent();

    it.set_left(0);
    it.set_right(0);

    ASSERT_EQ(*left,0);
    ASSERT_EQ(*right,0);

    auto right2=right.get_right();
    const binary_tree compare(8);
    const binary_tree<int> compare2=right2.copy_subtree();
    ASSERT_EQ(compare,compare2);
    ASSERT_EQ(*right2,8);

    const binary_tree<int> compare3=right2.cut_subtree();
    ASSERT_EQ(compare,compare3);
    ASSERT_EQ(*right2,0);
    ASSERT_FALSE(right2.has_right());

    auto it2=test_tree->begin();
    ASSERT_TRUE(it2==it);
    ASSERT_FALSE(it2!=it);
    it2.left();
    ASSERT_FALSE(it2==it);
    ASSERT_TRUE(it2!=it);

    auto it_4 = test_tree->begin().left().left().left();

    ++it_4;
    ASSERT_TRUE(*it_4==5);
    --it_4;
    ASSERT_TRUE(*it_4==4);
}

TEST_F(BinaryTreeTest,ConstIteratorTest)
{
    const auto tree = *test_tree;

    auto it = tree.begin();
    ASSERT_EQ(*it,1);
    ASSERT_TRUE(it.has_left());
    ASSERT_TRUE(it.has_right());

    const auto left=it.get_left();
    const auto right=it.get_right();
    ASSERT_EQ(*left,2);
    ASSERT_EQ(*right,7);
    ASSERT_FALSE(right.has_left());
    ASSERT_TRUE(right.get_parent()==it);

    it.left();
    ASSERT_EQ(*it,2);
    it.parent();
    ASSERT_EQ(*it,1);
    it.right();
    ASSERT_EQ(*it,7);
    it.parent();

    it.set_left(0);
    it.set_right(0);

    ASSERT_EQ(*left,0);
    ASSERT_EQ(*right,0);

    auto right2=right.get_right();
    const binary_tree compare(8);
    const binary_tree<int> compare2=right2.copy_subtree();
    ASSERT_EQ(compare,compare2);
    ASSERT_EQ(*right2,8);

    auto it2=tree.begin();
    ASSERT_TRUE(it2==it);
    ASSERT_FALSE(it2!=it);
    it2.left();
    ASSERT_FALSE(it2==it);
    ASSERT_TRUE(it2!=it);

    auto it_4 = test_tree->begin().left().left().left();

    ++it_4;
    ASSERT_TRUE(*it_4==5);
    --it_4;
    ASSERT_TRUE(*it_4==4);
}