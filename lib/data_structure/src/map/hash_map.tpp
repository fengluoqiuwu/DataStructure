//
// Created by Eden_ on 2024/9/18.
//
#pragma once

#include "hash_map.h"


template <typename KeyType, typename ValueType>
hash_map<KeyType, ValueType>::hash_map()
{
}

template <typename KeyType, typename ValueType>
hash_map<KeyType, ValueType>::hash_map(std::pair<KeyType, ValueType> *initialize_list, size_t size)
{
}

template <typename KeyType, typename ValueType>
hash_map<KeyType, ValueType>::hash_map(linked_list<std::pair<KeyType, ValueType>> initialize_list)
{
}

template <typename KeyType, typename ValueType>
hash_map<KeyType, ValueType>::hash_map(const hash_map &other)
{
}

template <typename KeyType, typename ValueType>
hash_map<KeyType, ValueType>::hash_map(hash_map &&other)
{
}

template <typename KeyType, typename ValueType>
hash_map<KeyType, ValueType> &hash_map<KeyType, ValueType>::operator=(const hash_map &other)
{
}

template <typename KeyType, typename ValueType>
hash_map<KeyType, ValueType> &hash_map<KeyType, ValueType>::operator=(hash_map &&other)
{
}

template <typename KeyType, typename ValueType>
hash_map<KeyType, ValueType>::~hash_map()
{
}

template <typename KeyType, typename ValueType>
std::optional<ValueType> hash_map<KeyType, ValueType>::put(const KeyType &key, const ValueType &value)
{
}

template <typename KeyType, typename ValueType>
std::optional<ValueType> hash_map<KeyType, ValueType>::get(const KeyType &key) const
{
}

template <typename KeyType, typename ValueType>
std::optional<ValueType> hash_map<KeyType, ValueType>::remove(const KeyType &key)
{

}

template <typename KeyType, typename ValueType>
bool hash_map<KeyType, ValueType>::containsKey(const KeyType &key) const
{
}

template <typename KeyType, typename ValueType>
bool hash_map<KeyType, ValueType>::isEmpty() const
{
}

template <typename KeyType, typename ValueType>
std::size_t hash_map<KeyType, ValueType>::size() const
{
}

template <typename KeyType, typename ValueType>
void hash_map<KeyType, ValueType>::clear()
{
}

template <typename KeyType, typename ValueType>
Set<KeyType> hash_map<KeyType, ValueType>::keySet() const
{
}

template <typename KeyType, typename ValueType>
Set<ValueType> hash_map<KeyType, ValueType>::values() const
{
}

template <typename KeyType, typename ValueType>
Set<std::pair<KeyType, ValueType>> hash_map<KeyType, ValueType>::entrySet() const
{
}