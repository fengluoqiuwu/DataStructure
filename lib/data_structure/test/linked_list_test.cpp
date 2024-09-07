//
// Created by Eden_ on 2024/9/6.
//

#include <gtest/gtest.h>
#include <data_structure.h>

class LinkedListTest : public ::testing::Test
{
protected:
    void SetUp() override {
    }

    void TearDown() override {
    }
};

TEST_F(LinkedListTest,SimpleConstructorTest)
{
    const auto* list = new linked_list<int>();
    const auto* list2 = new linked_list<int>();

    ASSERT_EQ(list->get_size(),0);
    ASSERT_EQ(*list==*list2,true);

    delete list;
    delete list2;
}

TEST_F(LinkedListTest,CopyConstructorFromArrayTest)
{
    int a[10] = {1,2,3,4,5,6,7,8,9,10};
    const auto* list = new linked_list<int>(a,10);

    ASSERT_EQ(list->to_string(),"[1,2,3,4,5,6,7,8,9,10]");

    delete list;
}

TEST_F(LinkedListTest,CopyConstructorTest)
{
    int a[10] = {1,2,3,4,5,6,7,8,9,10};
    const auto* list = new linked_list<int>(a,10);
    const auto* list2 = new linked_list<int>(*list);

    ASSERT_EQ(list2->to_string(),"[1,2,3,4,5,6,7,8,9,10]");

    delete list;
    delete list2;
}

TEST_F(LinkedListTest,MoveConstructorTest)
{
    int a[10] = {1,2,3,4,5,6,7,8,9,10};
    auto* list = new linked_list<int>(a,10);
    const auto* list2 = new linked_list<int>(std::move(*list));

    ASSERT_EQ(list2->to_string(),"[1,2,3,4,5,6,7,8,9,10]");
    ASSERT_EQ(list->is_empty(),true);

    delete list;
    delete list2;
}

TEST_F(LinkedListTest,CopyOperatorTest)
{
    int a[10] = {1,2,3,4,5,6,7,8,9,10};
    const auto* list = new linked_list<int>(a,10);
    const auto list2 = *list;

    ASSERT_EQ(list2.to_string(),"[1,2,3,4,5,6,7,8,9,10]");

    delete list;
}

TEST_F(LinkedListTest,MoveOperatorTest)
{
    int a[10] = {1,2,3,4,5,6,7,8,9,10};
    auto* list = new linked_list<int>(a,10);
    const auto list2 = std::move(*list);

    ASSERT_EQ(list2.to_string(),"[1,2,3,4,5,6,7,8,9,10]");
    ASSERT_EQ(list->is_empty(),true);

    delete list;
}

TEST_F(LinkedListTest,EqualOperatorTest)
{
    int a[10] = {1,2,3,4,5,6,7,8,9,10};
    const auto* list = new linked_list<int>(a,10);
    const auto list2 = *list;

    ASSERT_EQ(*list==list2,true);

    delete list;
}

TEST_F(LinkedListTest,FunctionAdd_value_Test)
{
    int a[10] = {1,2,3,4,5,6,7,8,9,10};
    auto* list = new linked_list<int>(a,10);
    list ->add(11);

    ASSERT_EQ(list->to_string(),"[1,2,3,4,5,6,7,8,9,10,11]");

    delete list;
}

TEST_F(LinkedListTest,FunctionAdd_index_value_Test)
{
    int a[10] = {1,2,3,4,5,6,7,8,9,10};
    auto* list = new linked_list<int>(a,10);
    list ->add(0,0);

    ASSERT_EQ(list->to_string(),"[0,1,2,3,4,5,6,7,8,9,10]");

    delete list;
}

TEST_F(LinkedListTest,FunctionGetTest)
{
    int a[10] = {1,2,3,4,5,6,7,8,9,10};
    auto* list = new linked_list<int>(a,10);

    ASSERT_EQ(list->get(1),2);
    list->get(0)=0;
    ASSERT_EQ(list->to_string(),"[0,2,3,4,5,6,7,8,9,10]");

    const auto* list2 = new linked_list<int>(a,10);
    ASSERT_EQ(list2->get(1),2);
    ASSERT_EQ(list2->to_string(),"[1,2,3,4,5,6,7,8,9,10]");
}

TEST_F(LinkedListTest,FunctionSetTest)
{
    int a[10] = {1,2,3,4,5,6,7,8,9,10};
    auto* list = new linked_list<int>(a,10);
    list->set(0,0);

    ASSERT_EQ(list->to_string(),"[0,2,3,4,5,6,7,8,9,10]");
}

TEST_F(LinkedListTest,FunctionRemove_index_Test)
{
    int a[10] = {1,2,3,4,5,6,7,8,9,10};
    auto* list = new linked_list<int>(a,10);
    list->remove(static_cast<size_t>(0));

    ASSERT_EQ(list->to_string(),"[2,3,4,5,6,7,8,9,10]");

    delete list;
}

TEST_F(LinkedListTest,FunctionRemove_value_Test)
{
    int a[10] = {1,2,3,4,5,6,7,8,9,1};
    auto* list = new linked_list<int>(a,10);
    list->remove(1);

    ASSERT_EQ(list->to_string(),"[2,3,4,5,6,7,8,9]");

    delete list;
}

TEST_F(LinkedListTest,FunctionContainsTest)
{
    int a[10] = {1,2,3,4,5,6,7,8,9,10};
    const auto* list = new linked_list<int>(a,10);

    ASSERT_TRUE(list->contains(1));
    ASSERT_FALSE(list->contains(0));

    delete list;
}

TEST_F(LinkedListTest,FunctionGetSizeTest)
{
    int a[10] = {1,2,3,4,5,6,7,8,9,10};
    const auto* list = new linked_list<int>(a,10);

    ASSERT_EQ(list->get_size(),10);

    delete list;
}

TEST_F(LinkedListTest,FunctionIsEmptyTest)
{
    const auto* list = new linked_list<int>();

    ASSERT_TRUE(list->is_empty());

    delete list;
}

TEST_F(LinkedListTest,FunctionAddFirstTest)
{
    int a[10] = {1,2,3,4,5,6,7,8,9,10};
    auto* list = new linked_list<int>(a,10);
    list->add_first(0);

    ASSERT_EQ(list->to_string(),"[0,1,2,3,4,5,6,7,8,9,10]");

    delete list;
}

TEST_F(LinkedListTest,FunctionAddLastTest)
{
    int a[10] = {1,2,3,4,5,6,7,8,9,10};
    auto* list = new linked_list<int>(a,10);
    list->add_last(11);

    ASSERT_EQ(list->to_string(),"[1,2,3,4,5,6,7,8,9,10,11]");

    delete list;
}

TEST_F(LinkedListTest,FunctionRemoveFirstTest)
{
    int a[10] = {1,2,3,4,5,6,7,8,9,10};
    auto* list = new linked_list<int>(a,10);
    list->remove_first();

    ASSERT_EQ(list->to_string(),"[2,3,4,5,6,7,8,9,10]");

    delete list;
}

TEST_F(LinkedListTest,FunctionRemoveLastTest)
{
    int a[10] = {1,2,3,4,5,6,7,8,9,10};
    auto* list = new linked_list<int>(a,10);
    list->remove_last();

    ASSERT_EQ(list->to_string(),"[1,2,3,4,5,6,7,8,9]");

    delete list;
}

TEST_F(LinkedListTest,FunctionGetFirstTest)
{
    int a[10] = {1,2,3,4,5,6,7,8,9,10};
    auto* list = new linked_list<int>(a,10);
    const auto* list2 = new linked_list<int>(a,10);

    ASSERT_EQ(list->get_first(),1);
    ASSERT_EQ(list2->get_first(),1);

    list->get_first()=0;
    ASSERT_EQ(list->to_string(),"[0,2,3,4,5,6,7,8,9,10]");
    ASSERT_EQ(list2->to_string(),"[1,2,3,4,5,6,7,8,9,10]");

    delete list;
    delete list2;
}

TEST_F(LinkedListTest,FunctionGetLastTest)
{
    int a[10] = {1,2,3,4,5,6,7,8,9,10};
    auto* list = new linked_list<int>(a,10);
    const auto* list2 = new linked_list<int>(a,10);

    ASSERT_EQ(list->get_last(),10);
    ASSERT_EQ(list2->get_last(),10);

    list->get_last()=0;
    ASSERT_EQ(list->to_string(),"[1,2,3,4,5,6,7,8,9,0]");
    ASSERT_EQ(list2->to_string(),"[1,2,3,4,5,6,7,8,9,10]");

    delete list;
    delete list2;
}

TEST_F(LinkedListTest,FunctionPopFirstTest)
{
    int a[10] = {1,2,3,4,5,6,7,8,9,10};
    auto* list = new linked_list<int>(a,10);

    ASSERT_EQ(list->pop_first(),1);
    ASSERT_EQ(list->to_string(),"[2,3,4,5,6,7,8,9,10]");

    delete list;
}

TEST_F(LinkedListTest,FunctionPopLastTest)
{
    int a[10] = {1,2,3,4,5,6,7,8,9,10};
    auto* list = new linked_list<int>(a,10);

    ASSERT_EQ(list->pop_last(),10);
    ASSERT_EQ(list->to_string(),"[1,2,3,4,5,6,7,8,9]");

    delete list;
}

TEST_F(LinkedListTest,FunctionToStringAndFromStringTest)
{
    const std::string test_int = "[1,2,3,4,5]";
    const std::string test_float = "[1.1,2.2,3.3,4.4,5.5]";
    const std::string test_string = R"(["apple","apple","apple","apple"])";

    ASSERT_EQ(linked_list<int>::from_string(test_int).to_string(),test_int);
    ASSERT_EQ(linked_list<float>::from_string(test_float).to_string(),test_float);
    ASSERT_EQ(linked_list<std::string>::from_string(test_string).to_string(),test_string);
}

TEST_F(LinkedListTest,IteratorTest)
{
    int a[10] = {1,2,3,4,5,6,7,8,9,10};
    auto* list = new linked_list<int>(a,10);

    linked_list<int>::Iterator it = list->begin();
    linked_list<int>::Iterator it2 = list->end();

    ASSERT_EQ(*it,1);
    *it = 2;
    ASSERT_EQ(*it,2);
    ++it;
    ASSERT_EQ(*it,2);
    --it2;
    ASSERT_EQ(*it2,10);

    delete list;

    class test
    {
        public:
        int data;
    };

    test* t = new test[5];
    t[0].data = 1;t[1].data = 2;t[2].data = 3;t[3].data = 4;t[4].data = 5;

    auto* list1 = new linked_list<test>(t,5);

    ASSERT_EQ(list1->begin()->data,1);

    delete list1;
}

TEST_F(LinkedListTest,ConstIteratorTest)
{
    int a[10] = {1,2,3,4,5,6,7,8,9,10};
    const auto* list = new linked_list<int>(a,10);

    linked_list<int>::ConstIterator it = list->begin();
    linked_list<int>::ConstIterator it2 = list->end();

    ASSERT_EQ(*it,1);
    ++it;
    ASSERT_EQ(*it,2);
    --it2;
    ASSERT_EQ(*it2,10);

    delete list;

    class test
    {
    public:
        int data;
    };

    test* t = new test[5];
    t[0].data = 1;t[1].data = 2;t[2].data = 3;t[3].data = 4;t[4].data = 5;

    auto* list1 = new linked_list<test>(t,5);

    ASSERT_EQ(list1->begin()->data,1);

    delete list1;
}