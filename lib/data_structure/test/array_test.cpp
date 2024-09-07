//
// Created by Eden_ on 2024/9/5.
//

#include <gtest/gtest.h>
#include "data_structure.h"

// 测试类定义
class ArrayTest : public ::testing::Test {
protected:
    void SetUp() override {
    }

    void TearDown() override {
    }
};

TEST_F(ArrayTest,SimpleConstructorInitTest)
{
    const auto* a=new array(10);
    ASSERT_EQ("[0,0,0,0,0,0,0,0,0,0]",a->to_string());
    delete a;
}

TEST_F(ArrayTest,CopyConstructorInitTest)
{
    const auto* a=new array(10);
    const auto* b=new array(*a);
    ASSERT_EQ("[0,0,0,0,0,0,0,0,0,0]",b->to_string());
    delete a;
    delete b;
}

TEST_F(ArrayTest,MoveConstructorInitTest)
{
    auto* a=new array(10);
    const auto* b=new array(std::move(*a));

    ASSERT_EQ("[0,0,0,0,0,0,0,0,0,0]",b->to_string());
    ASSERT_EQ(0,a->get_size());

    delete a;
    delete b;
}

TEST_F(ArrayTest,CopyConstructorFromIntegerArrayInitTest)
{
    int a[10]={1,2,3,4,5,6,7,8,9,10};
    const auto * b=new array(a,10);

    ASSERT_EQ("[1,2,3,4,5,6,7,8,9,10]",b->to_string());
    delete b;
}

TEST_F(ArrayTest,CopyOperatorTest)
{
    int a[10]={1,2,3,4,5,6,7,8,9,10};
    const auto * b=new array(a,10);
    const auto c=*b;
    ASSERT_EQ("[1,2,3,4,5,6,7,8,9,10]",c.to_string());

    delete b;
}

TEST_F(ArrayTest,MoveOperatorTest)
{
    int a[10]={1,2,3,4,5,6,7,8,9,10};
    auto * b=new array(a,10);
    const auto c=std::move(*b);
    ASSERT_EQ("[1,2,3,4,5,6,7,8,9,10]",c.to_string());
    ASSERT_EQ(0,b->get_size());

    delete b;
}

TEST_F(ArrayTest,EqualOperatorTest)
{
    int a[10]={1,2,3,4,5,6,7,8,9,10};
    const auto * b=new array(a,10);
    const auto * c=new array(a,10);

    ASSERT_EQ(true,*b==*c);

    delete b;
    delete c;
}

TEST_F(ArrayTest,SubscripOperatorTest)
{
    int a[10]={1,2,3,4,5,6,7,8,9,10};
    array b(a,10);
    const array c(a,10);

    ASSERT_EQ(1,b[0]);
    ASSERT_EQ(2,c[1]);

    b[0]=0;
    ASSERT_EQ(0,b[0]);
}

TEST_F(ArrayTest,FunctionGetSizeTest)
{
    int a[10]={1,2,3,4,5,6,7,8,9,10};
    const auto * b=new array(a,10);

    ASSERT_EQ(10,b->get_size());

    delete b;
}

TEST_F(ArrayTest,FunctionSortTest){}

TEST_F(ArrayTest,FunctionSearchTest)
{
    int a[10]={1,2,3,4,5,6,7,8,9,10};
    const auto * b=new array(a,10);

    ASSERT_EQ(2,b->search(3));

    delete b;
}

TEST_F(ArrayTest,FunctionBinarySearchTest)
{
    int a[10]={1,2,3,4,5,6,7,8,9,10};
    const auto * b=new array(a,10);

    ASSERT_EQ(2,b->binary_search(3));

    delete b;
}

TEST_F(ArrayTest,FunctionSubarrayTest)
{
    int a[10]={1,2,3,4,5,6,7,8,9,10};
    int b[5]={3,4,5,6,7};

    const auto * c=new array(a,10);
    const auto * d=new array(b,5);

    ASSERT_EQ(*c->subarray(2,7),*d);

    delete c;
    delete d;
}

TEST_F(ArrayTest,FunctionFillTest)
{
    int a[10]={1,2,3,4,5,6,7,8,9,10};
    int b[10]={0,0,0,0,0,0,0,0,0,0};

    const auto * c=new array(a,10);
    const auto * d=new array(b,10);

    c->fill(0);

    ASSERT_EQ(*c,*d);

    delete c;
    delete d;
}

TEST_F(ArrayTest,FunctionToListTest)
{
    int a[10]={1,2,3,4,5,6,7,8,9,10};
    const auto * b=new array(a,10);
    const auto * c=new linked_list<int>(a,10);
    const auto * d=b->to_list();

    ASSERT_EQ(true,*d==*c);
}

TEST_F(ArrayTest,FunctionFromStringAndToStringTest)
{
    const std::string a="[1,2,3,4,5,6,7,8,9,10]";
    const auto b = array::from_string(a);

    ASSERT_EQ(a,b.to_string());
}
