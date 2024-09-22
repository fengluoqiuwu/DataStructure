//
// Created by Eden_ on 2024/9/18.
//
#pragma once

#include "hash_set.h"

template <typename ValueType>
hash_set<ValueType>::hash_set() : basic_hash_map<ValueType,char>()
{
}

template <typename ValueType>
hash_set<ValueType>::hash_set(ValueType *initialize_list, size_t size)
{
    for (size_t i = 0; i < size; i++)
    {
        this->insert(Pair<ValueType,char>(initialize_list[i]));
    }
}

template <typename ValueType>
hash_set<ValueType>::hash_set(linked_list<ValueType> initialize_list)
{
    for (auto it = initialize_list.begin(); it != initialize_list.end(); ++it)
    {
        this->insert(Pair<ValueType,char>(*it));
    }
}

template <typename ValueType>
hash_set<ValueType>::hash_set(const hash_set &other) : basic_hash_map<ValueType,char>(other)
{
}

template <typename ValueType>
hash_set<ValueType>::hash_set(hash_set &&other) noexcept : basic_hash_map<ValueType,char>(std::move(other))
{
}

template <typename ValueType>
hash_set<ValueType>::~hash_set() = default;

template <typename ValueType>
hash_set<ValueType> &hash_set<ValueType>::operator=(const hash_set &other)
{
    if (this != &other)
    {
        basic_hash_map<ValueType, char>::operator=(other);
    }
    return *this;
}

template <typename ValueType>
hash_set<ValueType> &hash_set<ValueType>::operator=(hash_set &&other) noexcept
{
    if (this != &other)
    {
        basic_hash_map<ValueType, char>::operator=(std::move(other));
    }
    return *this;
}

template <typename ValueType>
bool hash_set<ValueType>::add(const ValueType &value)
{
    return basic_hash_map<ValueType, char>::put(value,'\0')==std::nullopt;
}

template <typename ValueType>
bool hash_set<ValueType>::erase(const ValueType &value)
{
    return basic_hash_map<ValueType, char>::remove(value)!=std::nullopt;
}

template <typename ValueType>
bool hash_set<ValueType>::contains(const ValueType &value) const
{
    return basic_hash_map<ValueType, char>::contains_key(value);
}

template <typename ValueType>
    std::size_t hash_set<ValueType>::get_size() const
{
    return basic_hash_map<ValueType, char>::get_size();
}

template <typename ValueType>
bool hash_set<ValueType>::is_empty() const
{
    return basic_hash_map<ValueType, char>::is_empty();
}

template <typename ValueType>
void hash_set<ValueType>::clear()
{
    basic_hash_map<ValueType, char>::clear();
}


template <typename ValueType>
linked_list<ValueType> hash_set<ValueType>::to_list() const
{
    linked_list<ValueType> result;

    //TODO

    return result;
}
