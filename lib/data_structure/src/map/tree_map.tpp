//
// Created by Eden_ on 2024/9/18.
//
#pragma once

#include "tree_map.h"

template <typename KeyType, typename ValueType>
tree_map<KeyType, ValueType>::tree_map() : red_black_tree<Pair<KeyType, ValueType>>()
{
}

template <typename KeyType, typename ValueType>
tree_map<KeyType, ValueType>::tree_map(std::pair<KeyType, ValueType> *initialize_list, const size_t size) : red_black_tree<Pair<KeyType, ValueType>>()
{
    for (size_t i = 0; i < size; i++)
    {
        this->insert(Pair(initialize_list[i].first, initialize_list[i].second));
    }
}

template <typename KeyType, typename ValueType>
tree_map<KeyType, ValueType>::tree_map(linked_list<std::pair<KeyType, ValueType>> initialize_list) : red_black_tree<Pair<KeyType, ValueType>>()
{
    for (auto it = initialize_list.begin(); it != initialize_list.end(); ++it)
    {
        this->insert(Pair(it->first, it->second));
    }
}

template <typename KeyType, typename ValueType>
tree_map<KeyType, ValueType>::tree_map(const tree_map &other) : red_black_tree<Pair<KeyType, ValueType>>(other)
{
}

template <typename KeyType, typename ValueType>
tree_map<KeyType, ValueType>::tree_map(tree_map &&other) noexcept : red_black_tree<Pair<KeyType, ValueType>>(std::move(other))
{
}

template <typename KeyType, typename ValueType>
tree_map<KeyType, ValueType> &tree_map<KeyType, ValueType>::operator=(const tree_map &other) noexcept {
    if (this != &other)
    {
        red_black_tree<Pair<KeyType, ValueType>>::operator=(other);
    }
    return *this;
}

template <typename KeyType, typename ValueType>
tree_map<KeyType, ValueType> &tree_map<KeyType, ValueType>::operator=(tree_map &&other) noexcept {
    if (this != &other)
    {
        red_black_tree<Pair<KeyType, ValueType>>::operator=(std::move(other));
    }
    return *this;
}

template <typename KeyType, typename ValueType>
tree_map<KeyType, ValueType>::~tree_map() = default;

template <typename KeyType, typename ValueType>
std::optional<ValueType> tree_map<KeyType, ValueType>::put(const KeyType &key, const ValueType &value)
{
    auto temp = Pair<KeyType, ValueType>(key, value);
    if (auto result = try_insert(temp); result.has_value())
    {
        return result.value().value;
    }
    return std::nullopt;
}

template <typename KeyType, typename ValueType>
std::optional<ValueType> tree_map<KeyType, ValueType>::get(const KeyType &key) const
{
    auto temp = Pair(key);
    auto result = searchRec(this->root,temp);
    if (result!=nullptr)
    {
        return std::optional<ValueType>(result->data.value);
    }
    return std::nullopt;
}

template <typename KeyType, typename ValueType>
std::optional<ValueType> tree_map<KeyType, ValueType>::remove(const KeyType &key)
{
    auto temp = Pair(key);
    auto result = try_remove(this->root,temp);
    if (result!=nullptr)
    {
        return std::optional<ValueType>(result->data.value);
    }
    return std::nullopt;
}

template <typename KeyType, typename ValueType>
bool tree_map<KeyType, ValueType>::contains_key(const KeyType &key) const
{
    auto temp = Pair(key);
    return search(temp);
}

template <typename KeyType, typename ValueType>
Set<KeyType> tree_map<KeyType, ValueType>::key_set() const
{

}

template <typename KeyType, typename ValueType>
Set<ValueType> tree_map<KeyType, ValueType>::values() const
{

}

template <typename KeyType, typename ValueType>
Set<std::pair<KeyType, ValueType>> tree_map<KeyType, ValueType>::entry_set() const
{

}