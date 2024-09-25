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
hash_set<ValueType>::hash_set(ValueType *initialize_list, const size_t size)
{
    for (size_t i = 0; i < size; i++)
    {
        this->put(initialize_list[i],'\0');
    }
}

template <typename ValueType>
hash_set<ValueType>::hash_set(linked_list<ValueType> initialize_list)
{
    for (auto it = initialize_list.begin(); it != initialize_list.end(); ++it)
    {
        this->put(*it,'\0');
    }
}

template <typename ValueType>
hash_set<ValueType>::hash_set(const Set<ValueType> &other)
{
    auto* temp = dynamic_cast<const hash_set *>(&other);
    if (!temp)
    {
        throw std::invalid_argument("hash_set constructor receive not hash_set Set reference. failed.");
    }
    basic_hash_map<ValueType, char>::operator=(*dynamic_cast<const Map<ValueType,char>*>(temp));
}

template <typename ValueType>
hash_set<ValueType>::hash_set(Set<ValueType> &&other) noexcept
{
    auto* temp = dynamic_cast<hash_set *>(std::addressof(other));
    if (!temp)
    {
        throw std::invalid_argument("hash_set constructor receive not hash_set Set reference. failed.");
    }
    basic_hash_map<ValueType, char>::operator=(std::move(*dynamic_cast<Map<ValueType,char>*>(temp)));
}

template <typename ValueType>
hash_set<ValueType>::~hash_set() = default;

template <typename ValueType>
hash_set<ValueType> &hash_set<ValueType>::operator=(const Set<ValueType> &other)
{
    auto* temp = dynamic_cast<const hash_set *>(&other);
    if (!temp)
    {
        throw std::invalid_argument("hash_set copy operator receive not hash_set Set reference. failed.");
    }
    if (this != temp)
    {
        basic_hash_map<ValueType, char>::operator=(*dynamic_cast<const Map<ValueType,char>*>(temp));
    }
    return *this;
}

template <typename ValueType>
hash_set<ValueType> &hash_set<ValueType>::operator=(Set<ValueType> &&other) noexcept
{
    auto* temp = dynamic_cast<hash_set *>(&other);
    if (!temp)
    {
        throw std::invalid_argument("hash_set move operator receive not hash_set Set reference. failed.");
    }
    if (this != temp)
    {
        basic_hash_map<ValueType, char>::operator=(std::move(*dynamic_cast<Map<ValueType,char>*>(temp)));
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
    return basic_hash_map<ValueType, char>::get_keys();
}
