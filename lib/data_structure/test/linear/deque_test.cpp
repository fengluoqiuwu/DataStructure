//
// Created by Eden_ on 2024/9/9.
//

#include <gtest/gtest.h>
#include "data_structure.h"

// 测试类定义
class DequeTest : public ::testing::Test {
protected:
    deque<int>* test_deque=new deque<int>();

    void SetUp() override {
        for(int i=0;i<10;i++)
        {
            test_deque->push_back(i);
        }
    }

    void TearDown() override {
        delete test_deque;
    }
};

TEST_F(DequeTest,SimpleConstructorTest)
{
    ASSERT_EQ(test_deque->front(), 0);
    ASSERT_EQ(test_deque->back(), 9);
}

TEST_F(DequeTest,CopyConstructorTest)
{
    auto q = new deque<int>(*test_deque);

    ASSERT_EQ(q->front(), 0);
    ASSERT_EQ(q->back(), 9);

    delete q;
}

TEST_F(DequeTest,MoveConstructorTest)
{
    auto q = new deque<int>(std::move(*test_deque));

    ASSERT_EQ(q->front(), 0);
    ASSERT_EQ(q->back(), 9);
    ASSERT_EQ(test_deque->get_size(), 0);

    delete q;
}

TEST_F(DequeTest,CopyOperatorTest)
{
    auto q = *test_deque;

    ASSERT_EQ(q.front(), 0);
    ASSERT_EQ(q.back(), 9);
}

TEST_F(DequeTest,MoveOperatorTest)
{
    auto q = std::move(*test_deque);

    ASSERT_EQ(q.front(), 0);
    ASSERT_EQ(q.back(), 9);
    ASSERT_EQ(test_deque->get_size(), 0);
}

TEST_F(DequeTest,FunctionPushFrontTest)
{
    auto q = *test_deque;

    q.push_front(-1);

    ASSERT_EQ(q.front(), -1);
    ASSERT_EQ(q.back(), 9);
}

TEST_F(DequeTest,FunctionPushBackTest)
{
    auto q = *test_deque;

    q.push_back(10);

    ASSERT_EQ(q.front(), 0);
    ASSERT_EQ(q.back(), 10);
}

TEST_F(DequeTest,FunctionPopFrontTest)
{
    auto q = *test_deque;

    ASSERT_EQ(q.pop_front(), 0);
    ASSERT_EQ(q.front(), 1);
}

TEST_F(DequeTest,FunctionPopBackTest)
{
    auto q = *test_deque;
    ASSERT_EQ(q.pop_back(), 9);
    ASSERT_EQ(q.back(), 8);
}

TEST_F(DequeTest,FunctionFront_and_BackTest)
{
    auto q = *test_deque;

    ASSERT_EQ(q.front(), 0);
    ASSERT_EQ(q.back(), 9);

    q.front()=1;
    q.back()=2;

    ASSERT_EQ(q.front(), 1);
    ASSERT_EQ(q.back(), 2);
}

TEST_F(DequeTest,ConstFunctionFront_and_BackTest)
{
    const auto q = *test_deque;

    ASSERT_EQ(q.front(), 0);
    ASSERT_EQ(q.back(), 9);
}

TEST_F(DequeTest,FunctionIsEmpty_GetSize_ClearTest)
{
    auto q = *test_deque;

    ASSERT_FALSE(q.is_empty());
    ASSERT_EQ(q.get_size(), 10);

    q.clear();

    ASSERT_TRUE(q.is_empty());
    ASSERT_EQ(q.get_size(), 0);
}