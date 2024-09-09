//
// Created by Eden_ on 2024/9/9.
//

#include <gtest/gtest.h>
#include "data_structure.h"

// 测试类定义
class QueueTest : public ::testing::Test {
protected:
    queue<int>* test_queue=new queue<int>();

    void SetUp() override {
        for(int i=0;i<10;i++)
        {
            test_queue->enqueue(i);
        }
    }

    void TearDown() override {
        delete test_queue;
    }
};

TEST_F(QueueTest,SimpleConstructorTest)
{
    ASSERT_EQ(test_queue->front(), 0);
    ASSERT_EQ(test_queue->back(), 9);
}

TEST_F(QueueTest,CopyConstructorTest)
{
    auto q = new queue<int>(*test_queue);

    ASSERT_EQ(q->front(), 0);
    ASSERT_EQ(q->back(), 9);

    delete q;
}

TEST_F(QueueTest,MoveConstructorTest)
{
    auto q = new queue<int>(std::move(*test_queue));

    ASSERT_EQ(q->front(), 0);
    ASSERT_EQ(q->back(), 9);
    ASSERT_EQ(test_queue->get_size(), 0);

    delete q;
}

TEST_F(QueueTest,CopyOperatorTest)
{
    auto q = *test_queue;

    ASSERT_EQ(q.front(), 0);
    ASSERT_EQ(q.back(), 9);
}

TEST_F(QueueTest,MoveOperatorTest)
{
    auto q = std::move(*test_queue);

    ASSERT_EQ(q.front(), 0);
    ASSERT_EQ(q.back(), 9);
    ASSERT_EQ(test_queue->get_size(), 0);
}

TEST_F(QueueTest,FunctionEnqueueTest)
{
    auto q = *test_queue;

    q.enqueue(10);

    ASSERT_EQ(q.front(), 0);
    ASSERT_EQ(q.back(), 10);
}

TEST_F(QueueTest,FunctionDequeueTest)
{
    auto q = *test_queue;

    ASSERT_EQ(q.dequeue(), 0);
    ASSERT_EQ(q.front(), 1);
    ASSERT_EQ(q.back(), 9);
}

TEST_F(QueueTest,FunctionFront_and_BackTest)
{
    auto q = *test_queue;

    ASSERT_EQ(q.front(), 0);
    ASSERT_EQ(q.back(), 9);

    q.front()=1;
    q.back()=2;

    ASSERT_EQ(q.front(), 1);
    ASSERT_EQ(q.back(), 2);
}

TEST_F(QueueTest,ConstFunctionFront_and_BackTest)
{
    const auto q = *test_queue;

    ASSERT_EQ(q.front(), 0);
    ASSERT_EQ(q.back(), 9);
}

TEST_F(QueueTest,FunctionIsEmpty_GetSize_ClearTest)
{
    auto q = *test_queue;

    ASSERT_FALSE(q.is_empty());
    ASSERT_EQ(q.get_size(), 10);

    q.clear();

    ASSERT_TRUE(q.is_empty());
    ASSERT_EQ(q.get_size(), 0);
}
