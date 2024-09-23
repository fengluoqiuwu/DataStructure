//
// Created by Eden_ on 2024/9/18.
//
#pragma once

#include "hash_map.h"

template <typename KeyType, typename ValueType>
std::optional<ValueType> hash_node<KeyType, ValueType>::put(const KeyType &key, const ValueType &value)
{
    if (map == nullptr)
    {
        for (auto it = list->begin(); it != list->end(); ++it)
        {
            if (it->key == key)
            {
                auto temp = it->value;
                it->value = value;
                return std::optional<ValueType>(temp);
            }
        }
        list->add(Pair<KeyType, ValueType>(key, value));
        return std::nullopt;
    }
    return map->put(key, value);
}

template <typename KeyType, typename ValueType>
std::optional<ValueType> hash_node<KeyType, ValueType>::get(const KeyType &key) const
{
    if (map == nullptr)
    {
        for (auto it = list->begin(); it != list->end(); ++it)
        {
            if (it->key == key)
            {
                return std::optional<ValueType>(it->value);
            }
        }
        return std::nullopt;
    }
    return map->get(key);
}

template <typename KeyType, typename ValueType>
std::optional<ValueType> hash_node<KeyType, ValueType>::remove(const KeyType &key)
{
    if (map == nullptr)
    {
        for (auto it = list->begin(); it != list->end(); ++it)
        {
            if (it->key == key)
            {
                auto temp = it->value;
                list->remove(it);
                return std::optional<ValueType>(temp);
            }
        }
        return std::nullopt;
    }
}

template <typename KeyType, typename ValueType>
bool hash_node<KeyType, ValueType>::contains_key(const KeyType &key) const
{
}

template <typename KeyType, typename ValueType>
bool hash_node<KeyType, ValueType>::is_empty() const
{
}

template <typename KeyType, typename ValueType>
std::size_t hash_node<KeyType, ValueType>::get_size() const
{
}

template <typename KeyType, typename ValueType>
void hash_node<KeyType, ValueType>::clear()
{
}

template <typename KeyType, typename ValueType>
void hash_node<KeyType, ValueType>::get_keys(KeyType *ptr)
{
}

template <typename KeyType, typename ValueType>
void hash_node<KeyType, ValueType>::get_values(ValueType *ptr)
{
}

template <typename KeyType, typename ValueType>
void hash_node<KeyType, ValueType>::get_pairs(std::pair<KeyType, ValueType> *ptr)
{
}

template <typename KeyType, typename ValueType>
void hash_node<KeyType, ValueType>::check_type_change()
{
}

template <typename KeyType, typename ValueType>
basic_hash_map<KeyType, ValueType>::basic_hash_map()
{
}

template <typename KeyType, typename ValueType>
basic_hash_map<KeyType, ValueType>::basic_hash_map(std::pair<KeyType, ValueType> *initialize_list, size_t size)
{
}

template <typename KeyType, typename ValueType>
basic_hash_map<KeyType, ValueType>::basic_hash_map(linked_list<std::pair<KeyType, ValueType>> initialize_list)
{
}

template <typename KeyType, typename ValueType>
basic_hash_map<KeyType, ValueType>::basic_hash_map(const basic_hash_map &other)
{
}

template <typename KeyType, typename ValueType>
basic_hash_map<KeyType, ValueType>::basic_hash_map(basic_hash_map &&other) noexcept
{
}

template <typename KeyType, typename ValueType>
basic_hash_map<KeyType, ValueType>::~basic_hash_map()
{
}

template <typename KeyType, typename ValueType>
basic_hash_map<KeyType, ValueType> &basic_hash_map<KeyType, ValueType>::operator=(const basic_hash_map &other)
{
}

template <typename KeyType, typename ValueType>
basic_hash_map<KeyType, ValueType> &basic_hash_map<KeyType, ValueType>::operator=(basic_hash_map &&other) noexcept
{
}

template <typename KeyType, typename ValueType>
std::optional<ValueType> basic_hash_map<KeyType, ValueType>::put(const KeyType &key, const ValueType &value)
{
}

template <typename KeyType, typename ValueType>
std::optional<ValueType> basic_hash_map<KeyType, ValueType>::get(const KeyType &key) const
{
}

template <typename KeyType, typename ValueType>
std::optional<ValueType> basic_hash_map<KeyType, ValueType>::remove(const KeyType &key)
{
}

template <typename KeyType, typename ValueType>
bool basic_hash_map<KeyType, ValueType>::contains_key(const KeyType &key) const
{
}

template <typename KeyType, typename ValueType>
bool basic_hash_map<KeyType, ValueType>::is_empty() const
{
}

template <typename KeyType, typename ValueType>
std::size_t basic_hash_map<KeyType, ValueType>::get_size() const
{
}

template <typename KeyType, typename ValueType>
void basic_hash_map<KeyType, ValueType>::clear()
{
}

template <typename KeyType, typename ValueType>
std::unique_ptr<Set<KeyType>> basic_hash_map<KeyType, ValueType>::key_set() const
{
}

template <typename KeyType, typename ValueType>
std::unique_ptr<Set<ValueType>> basic_hash_map<KeyType, ValueType>::values() const
{
}

template <typename KeyType, typename ValueType>
std::unique_ptr<Set<std::pair<KeyType, ValueType>>> basic_hash_map<KeyType, ValueType>::entry_set() const
{
}

template <typename KeyType, typename ValueType>
std::unique_ptr<Set<KeyType>> hash_map<KeyType, ValueType>::key_set() const
{
    return basic_hash_map<KeyType, ValueType>::key_set();
}

template <typename KeyType, typename ValueType>
std::unique_ptr<Set<ValueType>> hash_map<KeyType, ValueType>::values() const
{
    return basic_hash_map<KeyType, ValueType>::values();
}

template <typename KeyType, typename ValueType>
std::unique_ptr<Set<std::pair<KeyType, ValueType>>> hash_map<KeyType, ValueType>::entry_set() const
{
    return basic_hash_map<KeyType, ValueType>::entry_set();
}
