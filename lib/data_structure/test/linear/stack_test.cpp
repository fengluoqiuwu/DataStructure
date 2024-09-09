//
// Created by Eden_ on 2024/9/9.
//

#include <gtest/gtest.h>
#include "data_structure.h"

// 测试类定义
class StackTest : public ::testing::Test {
protected:
    stack<int>* test_stack=new stack<int>();

    void SetUp() override {
        for(int i=0;i<10;i++)
        {
            test_stack->push(i);
        }
    }

    void TearDown() override {
        delete test_stack;
    }
};

TEST_F(StackTest,SimpleConstructorTest)
{
    ASSERT_EQ(test_stack->get_size(), 10);
    ASSERT_EQ(test_stack->top(), 9);
}

TEST_F(StackTest,CopyConstructorTest)
{
    auto q = new stack<int>(*test_stack);

    ASSERT_EQ(q->get_size(), 10);
    ASSERT_EQ(q->top(), 9);

    delete q;
}

TEST_F(StackTest,MoveConstructorTest)
{
    auto q = new stack<int>(std::move(*test_stack));

    ASSERT_EQ(q->get_size(), 10);
    ASSERT_EQ(q->top(), 9);
    ASSERT_EQ(test_stack->get_size(), 0);

    delete q;
}

TEST_F(StackTest,CopyOperatorTest)
{
    auto q = *test_stack;

    ASSERT_EQ(q.get_size(), 10);
    ASSERT_EQ(q.top(), 9);
}

TEST_F(StackTest,MoveOperatorTest)
{
    auto q = std::move(*test_stack);

    ASSERT_EQ(q.get_size(), 10);
    ASSERT_EQ(q.top(), 9);
    ASSERT_EQ(test_stack->get_size(), 0);
}

TEST_F(StackTest,FunctionPushTest)
{
    auto q = *test_stack;

    q.push(10);

    ASSERT_EQ(q.get_size(), 11);
    ASSERT_EQ(q.top(), 10);
}

TEST_F(StackTest,FunctionPopTest)
{
    auto q = *test_stack;

    ASSERT_EQ(q.pop(), 9);
    ASSERT_EQ(q.get_size(), 9);
    ASSERT_EQ(q.top(), 8);
}

TEST_F(StackTest,FunctionTopTest)
{
    auto q = *test_stack;

    ASSERT_EQ(q.get_size(), 10);
    ASSERT_EQ(q.top(), 9);

    q.top()=10;

    ASSERT_EQ(q.get_size(), 10);
    ASSERT_EQ(q.top(), 10);
}

TEST_F(StackTest,ConstFunctionTopTest)
{
    const auto q = *test_stack;

    ASSERT_EQ(q.get_size(), 10);
    ASSERT_EQ(q.top(), 9);
}

TEST_F(StackTest,FunctionIsEmpty_GetSize_ClearTest)
{
    auto q = *test_stack;

    ASSERT_FALSE(q.is_empty());
    ASSERT_EQ(q.get_size(), 10);

    q.clear();

    ASSERT_TRUE(q.is_empty());
    ASSERT_EQ(q.get_size(), 0);
}
