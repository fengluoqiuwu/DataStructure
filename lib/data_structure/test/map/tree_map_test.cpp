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

    void SetUp() override {
        std::pair<int,int> b[10];

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
