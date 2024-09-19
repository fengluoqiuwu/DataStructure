//
// Created by Eden_ on 2024/9/18.
//
#pragma once

#include "tree_set.h"


template <typename ValueType>
tree_set<ValueType>::tree_set() : tree_map<ValueType,char>()
{
}

template <typename ValueType>
tree_set<ValueType>::tree_set(ValueType *initialize_list, size_t size)
{
    for (size_t i = 0; i < size; i++)
    {
        this->insert(Pair(initialize_list[i]));
    }
}

template <typename ValueType>
tree_set<ValueType>::tree_set(linked_list<ValueType> initialize_list)
{
    for (auto it = initialize_list.begin(); it != initialize_list.end(); ++it)
    {
        this->insert(Pair(*it));
    }
}

template <typename ValueType>
tree_set<ValueType>::tree_set(const tree_set &other) : tree_map<ValueType,char>(other)
{
}

template <typename ValueType>
tree_set<ValueType>::tree_set(tree_set &&other) noexcept : tree_map<ValueType,char>(std::move(other))
{
}

template <typename ValueType>
tree_set<ValueType>::~tree_set() = default;

template <typename ValueType>
tree_set<ValueType> &tree_set<ValueType>::operator=(const tree_set &other)
{
    if (this != &other)
    {
        tree_map<ValueType, char>::operator=(other);
    }
    return *this;
}

template <typename ValueType>
tree_set<ValueType> &tree_set<ValueType>::operator=(tree_set &&other) noexcept
{
    if (this != &other)
    {
        typename tree_map<ValueType, char>::operator=std::move(other);
    }
    return *this;
}

template <typename ValueType>
bool tree_set<ValueType>::add(const ValueType &value)
{
    return typename tree_map<ValueType, char>::put(value,'\0')==std::nullopt;
}

template <typename ValueType>
bool tree_set<ValueType>::remove(const ValueType &value)
{
    return tree_map<ValueType, char>::remove(value);
}

template <typename ValueType>
bool tree_set<ValueType>::contains(const ValueType &value) const
{
    return tree_map<ValueType, char>::contains_key(value);
}

template <typename ValueType>
    std::size_t tree_set<ValueType>::get_size() const
{
    return tree_map<ValueType, char>::get_size();
}

template <typename ValueType>
bool tree_set<ValueType>::is_empty() const
{
    return tree_map<ValueType, char>::is_empty();
}

template <typename ValueType>
void tree_set<ValueType>::clear()
{
    tree_map<ValueType, char>::clear();
}


template <typename ValueType>
linked_list<ValueType> tree_set<ValueType>::to_list() const
{
    linked_list<ValueType> result;

    for (auto it = this->begin(TreeData::INORDER); it != this->end(TreeData::INORDER); ++it)
    {
        result.add(it->key);
    }

    return result;
}
