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

TEST_F(BinaryTreeTest,InitTest)
{
    std::stringstream ss1,ss2,ss3;

    test_tree->preorder([&ss1](const int i)
    {
        ss1<<i<<' ';
    });
    ASSERT_EQ(ss1.str(),"1 2 3 4 6 5 8 7 ");

    test_tree->inorder([&ss2](const int i)
    {
        ss2<<i<<' ';
    });
    ASSERT_EQ(ss2.str(),"4 3 2 5 6 1 7 8 ");

    test_tree->postorder([&ss3](const int i)
    {
        ss3<<i<<' ';
    });
    ASSERT_EQ(ss3.str(),"4 3 6 5 2 8 7 1 ");
}