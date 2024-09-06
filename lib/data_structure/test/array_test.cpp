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
    array a(10);
    ASSERT_EQ("[0,0,0,0,0,0,0,0,0,0]",a.to_string());
}
