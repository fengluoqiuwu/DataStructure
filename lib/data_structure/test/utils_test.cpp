//
// Created by Eden_ on 2024/9/23.
//

#include "utils.h"
using namespace utils;

#include <gtest/gtest.h>
#include "data_structure.h"

TEST(UtilsTest,HasEqualTest)
{
    ASSERT_TRUE(has_equal<int>::value);
    class test_false;
    class test_true
    {
    public:
        bool operator==(const test_true& other) const {
            return true;
        }
    };
    ASSERT_FALSE(has_equal<test_false>::value);
    ASSERT_TRUE(has_equal<test_true>::value);
}

TEST(UtilsTest,HasAllComparisionsTest)
{
    ASSERT_TRUE(has_all_comparisons<int>::value);
    class test_false
    {
    public:
        bool operator==(const test_false& other) const
        {
            return true;
        }
        bool operator>(const test_false& other) const
        {
            return false;
        }
        bool operator<(const test_false& other) const
        {
            return false;
        }
        bool operator>=(const test_false& other) const
        {
            return false;
        }
    };
    class test_true
    {
    public:
        bool operator==(const test_true& other) const
        {
            return true;
        }
        bool operator>(const test_true& other) const
        {
            return false;
        }
        bool operator<(const test_true& other) const
        {
            return false;
        }
        bool operator>=(const test_true& other) const
        {
            return false;
        }
        bool operator<=(const test_true& other) const
        {
            return false;
        }
    };
    ASSERT_FALSE(has_all_comparisons<test_false>::value);
    ASSERT_TRUE(has_all_comparisons<test_true>::value);
}

TEST(UtilsTest,HasHashTest)
{
    ASSERT_TRUE(has_hash<int>::value);
    class test_false;
    class test_true
    {
    public:
        friend struct std::hash<test_true>;
    };
}
