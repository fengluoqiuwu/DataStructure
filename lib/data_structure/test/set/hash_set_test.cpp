//
// Created by Eden_ on 2024/9/19.
//

#include <gtest/gtest.h>
#include "data_structure.h"

class HashSetTest : public ::testing::Test
{
protected:
    Set<int> *test_set=nullptr;
    int a[10]={18, 42, 96, 80, 65, 56, 32, 64, 89, 85};

    void SetUp() override {
        test_set = new hash_set(a,10);
    }

    void TearDown() override {
        delete test_set;
    }
};

TEST_F(HashSetTest,ConstructorDefaultTest)
{
    const hash_set<int> set;
    ASSERT_TRUE(set.is_empty());
    ASSERT_EQ(set.get_size(), 0);
}

TEST_F(HashSetTest,ConstructorFromArrayOfDataTest)
{
    ASSERT_EQ(test_set->get_size(), 10);
    ASSERT_FALSE(test_set->is_empty());
    for(int i : a)
    {
        ASSERT_TRUE(test_set->contains(i));
    }
}

TEST_F(HashSetTest,ConstructorFromListTest)
{
    const linked_list list(a,10);
    const hash_set set(list);
    for(int i : a)
    {
        ASSERT_TRUE(set.contains(i));
    }
}

TEST_F(HashSetTest,ConstructorCopyTest)
{
    const auto set=hash_set(*test_set);

    for(int i : a)
    {
        ASSERT_TRUE(set.contains(i));
    }
}

TEST_F(HashSetTest,ConstructorMoveTest)
{
    const auto set=hash_set(std::move(*test_set));

    for(int i : a)
    {
        ASSERT_TRUE(set.contains(i));
    }
    ASSERT_EQ(test_set->get_size(), 0);
    ASSERT_TRUE(test_set->is_empty());
}

TEST_F(HashSetTest,OperatorCopyTest)
{
    hash_set<int> set;
    // ReSharper disable once CppJoinDeclarationAndAssignment
    set = (*test_set);

    for(int i : a)
    {
        ASSERT_TRUE(set.contains(i));
    }
}

TEST_F(HashSetTest,OperatorMoveTest)
{
    hash_set<int> set;
    // ReSharper disable once CppJoinDeclarationAndAssignment
    set = (std::move(*test_set));

    for(int i : a)
    {
        ASSERT_TRUE(set.contains(i));
    }
    ASSERT_EQ(test_set->get_size(), 0);
    ASSERT_TRUE(test_set->is_empty());
}

TEST_F(HashSetTest,FunctionAddTest)
{
    ASSERT_TRUE(test_set->add(1));
    ASSERT_TRUE(test_set->contains(1));
    ASSERT_EQ(test_set->get_size(), 11);

    ASSERT_FALSE(test_set->add(18));
    ASSERT_EQ(test_set->get_size(), 11);
}

TEST_F(HashSetTest,FunctionRemoveTest)
{
    ASSERT_TRUE(test_set->erase(18));
    ASSERT_FALSE(test_set->contains(18));
    ASSERT_EQ(test_set->get_size(), 9);

    ASSERT_FALSE(test_set->erase(1));
    ASSERT_EQ(test_set->get_size(), 9);
}

TEST_F(HashSetTest,FunctionContainsTest)
{
    for(int i : a)
    {
        ASSERT_TRUE(test_set->contains(i));
    }
}

TEST_F(HashSetTest,FunctionGetSizeTest)
{
    ASSERT_EQ(test_set->get_size(), 10);
    test_set->erase(18);
    ASSERT_EQ(test_set->get_size(), 9);
    test_set->clear();
    ASSERT_EQ(test_set->get_size(), 0);
}

TEST_F(HashSetTest,FunctionIsEmptyTest)
{
    ASSERT_FALSE(test_set->is_empty());
    test_set->clear();
    ASSERT_TRUE(test_set->is_empty());
}

TEST_F(HashSetTest,FunctionClearTest)
{
    ASSERT_FALSE(test_set->is_empty());
    test_set->clear();
    ASSERT_TRUE(test_set->is_empty());
    ASSERT_EQ(test_set->get_size(), 0);
}

TEST_F(HashSetTest,FunctionToListTest)
{
    const linked_list list=test_set->to_list();

    ASSERT_EQ(list.get_size(), 10);
}

TEST_F(HashSetTest,IteratorTest)
{
    for(auto it=test_set->begin();)
}