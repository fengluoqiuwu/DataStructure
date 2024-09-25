//
// Created by Eden_ on 2024/9/21.
//

#include <gtest/gtest.h>
#include "data_structure.h"

class TreeMapTest : public ::testing::Test
{
protected:
    Map<int,int> *test_map=nullptr;
    int a[10]={18, 42, 96, 80, 65, 56, 32, 64, 89, 85};
    std::pair<int,int> b[10];

    void SetUp() override {
        for(int i=0;i<10;i++)
        {
            b[i]=std::make_pair(a[i],i);
        }

        test_map = new tree_map<int,int>(b,10);
    }

    void TearDown() override {
        delete test_map;
    }
};

TEST_F(TreeMapTest,ConstructorDefaultTest)
{
    const tree_map<int,int> map;
    ASSERT_EQ(map.get_size(),0);
    ASSERT_TRUE(map.is_empty());
}

TEST_F(TreeMapTest,ConstructorWithArryTest)
{
    for(int i : a)
    {
        ASSERT_TRUE(test_map->contains_key(i));
    }
    ASSERT_EQ(test_map->get_size(),10);
}

TEST_F(TreeMapTest,ConstructorWithListTest)
{
    const linked_list list(b, 10);
    const tree_map<int,int> map(list);

    for(int i : a)
    {
        ASSERT_TRUE(map.contains_key(i));
    }
    ASSERT_EQ(map.get_size(),10);
}

TEST_F(TreeMapTest,ConstructorCopyTest)
{
    const tree_map<int,int> map(*test_map);

    for(int i : a)
    {
        ASSERT_TRUE(map.contains_key(i));
    }
    ASSERT_EQ(map.get_size(),10);
}

TEST_F(TreeMapTest,ConstructorMoveTest)
{
    const tree_map<int,int> map(std::move(*test_map));

    for(int i : a)
    {
        ASSERT_TRUE(map.contains_key(i));
    }
    ASSERT_EQ(map.get_size(),10);
    ASSERT_TRUE(test_map->is_empty());
}

TEST_F(TreeMapTest,OperatorCopyTest)
{
    tree_map<int,int> map(*test_map);
    map=*test_map;

    for(int i : a)
    {
        ASSERT_TRUE(map.contains_key(i));
    }
    ASSERT_EQ(map.get_size(),10);
}

TEST_F(TreeMapTest,OperatorMoveTest)
{
    tree_map<int,int> map(*test_map);
    map= std::move(*test_map);

    for(int i : a)
    {
        ASSERT_TRUE(map.contains_key(i));
    }
    ASSERT_EQ(map.get_size(),10);
    ASSERT_TRUE(test_map->is_empty());
}

TEST_F(TreeMapTest,FunctionPutTest)
{
    ASSERT_EQ(test_map->get_size(),10);
    ASSERT_EQ(test_map->put(18,-1).value(),0);
    ASSERT_EQ(test_map->get_size(),10);
    ASSERT_EQ(test_map->get(18).value(),-1);

    ASSERT_EQ(test_map->put(17,1),std::nullopt);
    ASSERT_EQ(test_map->get_size(),11);
    ASSERT_EQ(test_map->get(17).value(),1);
}

TEST_F(TreeMapTest,FunctionGetTest)
{
    for(int i=0;i<10;i++)
    {
        ASSERT_EQ(test_map->get(a[i]).value(),i);
    }
    ASSERT_EQ(test_map->get(0),std::nullopt);
}

TEST_F(TreeMapTest,FunctionRemoveTest)
{
    ASSERT_EQ(test_map->get_size(),10);
    ASSERT_EQ(test_map->remove(18),0);
    ASSERT_EQ(test_map->get_size(),9);

    ASSERT_EQ(test_map->remove(0),std::nullopt);
    ASSERT_EQ(test_map->get_size(),9);
}

TEST_F(TreeMapTest,FunctionContainsKeyTest)
{
    for(int i : a)
    {
        ASSERT_TRUE(test_map->contains_key(i));
    }
}

TEST_F(TreeMapTest,FunctionIsEmptyTest)
{
    ASSERT_FALSE(test_map->is_empty());
    test_map->clear();
    ASSERT_TRUE(test_map->is_empty());
}

TEST_F(TreeMapTest,FunctionGetSizeTest)
{
    ASSERT_EQ(test_map->get_size(),10);
    test_map->clear();
    ASSERT_EQ(test_map->get_size(),0);
}

TEST_F(TreeMapTest,FunctionClearTest)
{
    ASSERT_EQ(test_map->get_size(),10);
    test_map->clear();
    ASSERT_EQ(test_map->get_size(),0);
}

TEST_F(TreeMapTest,FunctionKeySetTest)
{
    const auto test_set =test_map->key_set();

    for(int i : a)
    {
        ASSERT_TRUE(test_set->contains(i));
    }
}

TEST_F(TreeMapTest,FunctionValuesTest)
{
    const auto test_set =test_map->values();

    for(int i=0;i<10;i++)
    {
        ASSERT_TRUE(test_set->contains(i));
    }
}

TEST_F(TreeMapTest,FunctionEntrySetTest)
{
    const auto test_set =test_map->entry_set();

    for(int i=0;i<10;i++)
    {
        ASSERT_TRUE(test_set->contains(Pair(a[i],i)));
    }
}

TEST_F(TreeMapTest,IteratorTest)
{
    const auto test =tree_map<int,int>(*test_map);

    for(auto it = test.begin(); it != test.end(); ++it)
    {
        ASSERT_TRUE(test_map->contains_key(it->key));
        ASSERT_EQ(test_map->get(it->key).value(),it->value);
    }
}
