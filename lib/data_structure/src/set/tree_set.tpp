//
// Created by Eden_ on 2024/9/18.
//
#pragma once

#include "tree_set.h"


template <typename ValueType>
tree_set<ValueType>::tree_set() : basic_tree_map<ValueType,char>()
{
}

template <typename ValueType>
tree_set<ValueType>::tree_set(ValueType *initialize_list, size_t size)
{
    for (size_t i = 0; i < size; i++)
    {
        basic_tree_map<ValueType, char>::put(initialize_list[i],'\0');
    }
}

template <typename ValueType>
tree_set<ValueType>::tree_set(linked_list<ValueType> initialize_list)
{
    for (auto it = initialize_list.begin(); it != initialize_list.end(); ++it)
    {
        basic_tree_map<ValueType, char>::put(*it,'\0');
    }
}

template <typename ValueType>
tree_set<ValueType>::tree_set(const Set<ValueType> &other)
{
    auto* temp = dynamic_cast<const tree_set *>(&other);
    if (!temp)
    {
        throw std::invalid_argument("tree_set constructor receive not tree_set Set reference. failed.");
    }
    basic_tree_map<ValueType, char>::operator=(*dynamic_cast<const Map<ValueType,char>*>(temp));
}

template <typename ValueType>
tree_set<ValueType>::tree_set(Set<ValueType> &&other) noexcept
{
    auto* temp = dynamic_cast<tree_set *>(std::addressof(other));
    if (!temp)
    {
        throw std::invalid_argument("tree_set constructor receive not tree_set Set reference. failed.");
    }
    basic_tree_map<ValueType, char>::operator=(std::move(*dynamic_cast<Map<ValueType,char>*>(temp)));
}

template <typename ValueType>
tree_set<ValueType>::~tree_set() = default;

template <typename ValueType>
tree_set<ValueType> &tree_set<ValueType>::operator=(const Set<ValueType> &other)
{
    auto* temp = dynamic_cast<const tree_set *>(&other);
    if (!temp)
    {
        throw std::invalid_argument("tree_set copy operator receive not tree_set Set reference. failed.");
    }
    if (this != temp)
    {
        basic_tree_map<ValueType, char>::operator=(*dynamic_cast<const Map<ValueType,char>*>(temp));
    }
    return *this;
}

template <typename ValueType>
tree_set<ValueType> &tree_set<ValueType>::operator=(Set<ValueType> &&other) noexcept
{
    auto* temp = dynamic_cast<tree_set *>(&other);
    if (!temp)
    {
        throw std::invalid_argument("tree_set move operator receive not tree_set Set reference. failed.");
    }
    if (this != temp)
    {
        basic_tree_map<ValueType, char>::operator=(std::move(*dynamic_cast<Map<ValueType,char>*>(temp)));
    }
    return *this;
}

template <typename ValueType>
bool tree_set<ValueType>::add(const ValueType &value)
{
    return basic_tree_map<ValueType, char>::put(value,'\0')==std::nullopt;
}

template <typename ValueType>
bool tree_set<ValueType>::erase(const ValueType &value)
{
    return basic_tree_map<ValueType, char>::remove(value)!=std::nullopt;
}

template <typename ValueType>
bool tree_set<ValueType>::contains(const ValueType &value) const
{
    return basic_tree_map<ValueType, char>::contains_key(value);
}

template <typename ValueType>
    std::size_t tree_set<ValueType>::get_size() const
{
    return basic_tree_map<ValueType, char>::get_size();
}

template <typename ValueType>
bool tree_set<ValueType>::is_empty() const
{
    return basic_tree_map<ValueType, char>::is_empty();
}

template <typename ValueType>
void tree_set<ValueType>::clear()
{
    basic_tree_map<ValueType, char>::clear();
}


template <typename ValueType>
linked_list<ValueType> tree_set<ValueType>::to_list() const
{
    linked_list<ValueType> result;

    for (auto it = basic_tree_map<ValueType>::begin(); it != basic_tree_map<ValueType>::end(); ++it)
    {
        result.add(it->key);
    }

    return result;
}
