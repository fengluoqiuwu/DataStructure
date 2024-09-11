//
// Created by Eden_ on 2024/9/11.
//

#include <gtest/gtest.h>
#include "data_structure.h"

class BinaryTreeTest : public ::testing::Test {
protected:
    binary_tree<int>* test_tree=nullptr;
    const int a[17]={1,2,3,4,0,0,0,5,0,6,0,0,7,0,8,0,0};

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

}

TEST_F(BinaryTreeTest,ConstructorWithAPreorderArrayTest){}

TEST_F(BinaryTreeTest,ConstructorWithAPreorderLinkedListTest){}

TEST_F(BinaryTreeTest,ConstructorCopyTest){}

TEST_F(BinaryTreeTest,ConstructorMoveTest){}

TEST_F(BinaryTreeTest,OperatorCopyTest){}

TEST_F(BinaryTreeTest,OperatorMoveTest){}

TEST_F(BinaryTreeTest,OperatorEqualTest){}

TEST_F(BinaryTreeTest,FunctionSearchTest){}

TEST_F(BinaryTreeTest,FunctionInorderTest){}

TEST_F(BinaryTreeTest,FunctionPreorderTest){}

TEST_F(BinaryTreeTest,FunctionPostorderTest){}

TEST_F(BinaryTreeTest,FunctionClearTest){}

TEST_F(BinaryTreeTest,FunctionIsEmptyTest){}

TEST_F(BinaryTreeTest,FunctionGetDepthTest){}

TEST_F(BinaryTreeTest,FunctionGetSizeTest){}

TEST_F(BinaryTreeTest,IteratorTest){}

TEST_F(BinaryTreeTest,ConstIteratorTest){}