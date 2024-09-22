//
// Created by Eden_ on 2024/9/18.
//
#pragma once

#include "tree_map.h"
#include "tree_set.h"

template <typename KeyType, typename ValueType>
basic_tree_map<KeyType, ValueType>::basic_tree_map() : red_black_tree<Pair<KeyType, ValueType>>()
{
}

template <typename KeyType, typename ValueType>
basic_tree_map<KeyType, ValueType>::basic_tree_map(std::pair<KeyType, ValueType> *initialize_list, const size_t size) : red_black_tree<Pair<KeyType, ValueType>>()
{
    for (size_t i = 0; i < size; i++)
    {
        this->insert(Pair(initialize_list[i].first, initialize_list[i].second));
    }
}

template <typename KeyType, typename ValueType>
basic_tree_map<KeyType, ValueType>::basic_tree_map(linked_list<std::pair<KeyType, ValueType>> initialize_list) : red_black_tree<Pair<KeyType, ValueType>>()
{
    for (auto it = initialize_list.begin(); it != initialize_list.end(); ++it)
    {
        this->insert(Pair(it->first, it->second));
    }
}

template <typename KeyType, typename ValueType>
basic_tree_map<KeyType, ValueType>::basic_tree_map(const basic_tree_map &other) : red_black_tree<Pair<KeyType, ValueType>>(other)
{
}

template <typename KeyType, typename ValueType>
basic_tree_map<KeyType, ValueType>::basic_tree_map(basic_tree_map &&other) noexcept : red_black_tree<Pair<KeyType, ValueType>>(std::move(other))
{
}

template <typename KeyType, typename ValueType>
basic_tree_map<KeyType, ValueType>::~basic_tree_map() = default;

template <typename KeyType, typename ValueType>
basic_tree_map<KeyType, ValueType> &basic_tree_map<KeyType, ValueType>::operator=(const basic_tree_map &other) {
    red_black_tree<Pair<KeyType, ValueType>> ::operator=(other);
    return *this;
}

template <typename KeyType, typename ValueType>
basic_tree_map<KeyType, ValueType> &basic_tree_map<KeyType, ValueType>::operator=(basic_tree_map &&other) noexcept {
    red_black_tree<Pair<KeyType, ValueType>> ::operator=(std::move(other));
    return *this;
}

template <typename KeyType, typename ValueType>
std::optional<ValueType> basic_tree_map<KeyType, ValueType>::put(const KeyType &key, const ValueType &value)
{
    auto temp = Pair<KeyType, ValueType>(key, value);
    if (auto result = this->try_insert(temp); result.has_value())
    {
        return result.value().value;
    }
    return std::nullopt;
}

template <typename KeyType, typename ValueType>
std::optional<ValueType> basic_tree_map<KeyType, ValueType>::get(const KeyType &key) const
{
    auto temp = Pair<KeyType,ValueType>(key);
    auto result = this->searchRec(this->root,temp);
    if (result!=nullptr)
    {
        return std::optional<ValueType>(result->data.value);
    }
    return std::nullopt;
}

template <typename KeyType, typename ValueType>
std::optional<ValueType> basic_tree_map<KeyType, ValueType>::remove(const KeyType &key)
{
    auto temp = Pair<KeyType,ValueType>(key);
    auto result = this->try_remove(temp);
    if (result!=std::nullopt)
    {
        return std::optional<ValueType>(result.value().value);
    }
    return std::nullopt;
}

template <typename KeyType, typename ValueType>
bool basic_tree_map<KeyType, ValueType>::contains_key(const KeyType &key) const
{
    auto temp = Pair<KeyType,ValueType>(key);
    return this->search(temp);
}

template <typename KeyType, typename ValueType>
bool basic_tree_map<KeyType, ValueType>::is_empty() const
{
    return red_black_tree<Pair<KeyType, ValueType>>::is_empty();
}

template <typename KeyType, typename ValueType>
std::size_t basic_tree_map<KeyType, ValueType>::get_size() const
{
    return red_black_tree<Pair<KeyType, ValueType>>::get_size();
}

template <typename KeyType, typename ValueType>
void basic_tree_map<KeyType, ValueType>::clear()
{
    red_black_tree<Pair<KeyType, ValueType>>::clear();
}

template <typename KeyType, typename ValueType>
std::unique_ptr<Set<KeyType>> basic_tree_map<KeyType, ValueType>::key_set() const
{
    return nullptr;
}

template <typename KeyType, typename ValueType>
std::unique_ptr<Set<ValueType>> basic_tree_map<KeyType, ValueType>::values() const
{
    return nullptr;
}

template <typename KeyType, typename ValueType>
std::unique_ptr<Set<std::pair<KeyType, ValueType>>> basic_tree_map<KeyType, ValueType>::entry_set() const
{
    return nullptr;
}

template <typename KeyType, typename ValueType>
std::unique_ptr<Set<KeyType>> tree_map<KeyType, ValueType>::key_set() const
{
    auto result = std::make_unique<tree_set<KeyType>>();

    for (auto it=this->begin(PREORDER);it!=this->end(PREORDER);++it)
    {
        result->add(it->key);
    }

    return result;
}

template <typename KeyType, typename ValueType>
std::unique_ptr<Set<ValueType>> tree_map<KeyType, ValueType>::values() const
{
    auto result = std::make_unique<tree_set<ValueType>>();

    for (auto it=this->begin(PREORDER);it!=this->end(PREORDER);++it)
    {
        result->add(it->value);
    }

    return result;
}

template <typename KeyType, typename ValueType>
std::unique_ptr<Set<std::pair<KeyType, ValueType>>> tree_map<KeyType, ValueType>::entry_set() const
{
    auto result = std::make_unique<tree_set<std::pair<KeyType, ValueType>>>();

    for (auto it=this->begin(PREORDER);it!=this->end(PREORDER);++it)
    {
        result->add(std::make_pair(it->key,it->value));
    }

    return result;
}