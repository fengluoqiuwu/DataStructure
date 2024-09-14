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
