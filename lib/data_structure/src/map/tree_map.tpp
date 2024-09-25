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
basic_tree_map<KeyType, ValueType>::basic_tree_map(const Map<KeyType,ValueType> &other)
{
    auto* temp = dynamic_cast<const basic_tree_map<KeyType, ValueType> *>(&other);
    if (!temp)
    {
        throw std::invalid_argument("basic_tree_map constructor receive not basic_tree_map Map reference. failed.");
    }
    red_black_tree<Pair<KeyType, ValueType>> ::operator=(*temp);
}

template <typename KeyType, typename ValueType>
basic_tree_map<KeyType, ValueType>::basic_tree_map(Map<KeyType,ValueType> &&other) noexcept
{
    auto* temp = dynamic_cast<basic_tree_map<KeyType, ValueType> *>(std::addressof(other));
    if (!temp)
    {
        throw std::invalid_argument("basic_tree_map constructor receive not basic_tree_map Map reference. failed.");
    }
    red_black_tree<Pair<KeyType, ValueType>> ::operator=(std::move(*temp));
}

template <typename KeyType, typename ValueType>
basic_tree_map<KeyType, ValueType>::~basic_tree_map() = default;

template <typename KeyType, typename ValueType>
basic_tree_map<KeyType, ValueType> &basic_tree_map<KeyType, ValueType>::operator=(const Map<KeyType,ValueType> &other) {
    auto* temp = dynamic_cast<const basic_tree_map<KeyType, ValueType> *>(&other);
    if (!temp)
    {
        throw std::invalid_argument("basic_tree_map copy operator receive not basic_tree_map Map reference. failed.");
    }
    red_black_tree<Pair<KeyType, ValueType>> ::operator=(*temp);
    return *this;
}

template <typename KeyType, typename ValueType>
basic_tree_map<KeyType, ValueType> &basic_tree_map<KeyType, ValueType>::operator=(Map<KeyType,ValueType> &&other) noexcept {
    auto* temp = dynamic_cast<basic_tree_map<KeyType, ValueType> *>(std::addressof(other));
    if (!temp)
    {
        throw std::invalid_argument("basic_tree_map move operator receive not basic_tree_map Map reference. failed.");
    }
    red_black_tree<Pair<KeyType, ValueType>> ::operator=(std::move(*temp));
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
std::unique_ptr<Set<Pair<KeyType, ValueType>>> basic_tree_map<KeyType, ValueType>::entry_set() const
{
    return nullptr;
}

template <typename KeyType, typename ValueType>
basic_tree_map<KeyType, ValueType>::ConstIterator::ConstIterator(const ConstIterator &other) : m_it(other.m_it)
{
}

template <typename KeyType, typename ValueType>
const Pair<KeyType, ValueType> &basic_tree_map<KeyType, ValueType>::ConstIterator::operator*() const
{
    return *m_it;
}

template <typename KeyType, typename ValueType>
const Pair<KeyType, ValueType> *basic_tree_map<KeyType, ValueType>::ConstIterator::operator->() const
{
    return &(*m_it);
}

template <typename KeyType, typename ValueType>
typename basic_tree_map<KeyType, ValueType>::ConstIterator &
basic_tree_map<KeyType, ValueType>::ConstIterator::operator=(const ConstIterator &other)=default;

template <typename KeyType, typename ValueType>
bool basic_tree_map<KeyType, ValueType>::ConstIterator::operator==(
    const typename Map<KeyType, ValueType>::ConstIterator &other) const
{
    const auto* temp = dynamic_cast<const ConstIterator*>(&other);
    if (!temp) return false;
    return m_it == temp->m_it;
}

template <typename KeyType, typename ValueType>
bool basic_tree_map<KeyType, ValueType>::ConstIterator::operator!=(
    const typename Map<KeyType, ValueType>::ConstIterator &other) const
{
    return !(*this==other);
}

template <typename KeyType, typename ValueType>
typename basic_tree_map<KeyType, ValueType>::ConstIterator &
basic_tree_map<KeyType, ValueType>::ConstIterator::operator++()
{
    ++m_it;
    return *this;
}

template <typename KeyType, typename ValueType>
basic_tree_map<KeyType, ValueType>::ConstIterator::ConstIterator(
    const typename red_black_tree<Pair<KeyType, ValueType>>::ConstIterator &it) : m_it(it){}

template <typename KeyType, typename ValueType>
typename basic_tree_map<KeyType, ValueType>::ConstIterator basic_tree_map<KeyType, ValueType>::begin() const
{
    return ConstIterator(red_black_tree<Pair<KeyType, ValueType>>::begin());
}

template <typename KeyType, typename ValueType>
typename basic_tree_map<KeyType, ValueType>::ConstIterator basic_tree_map<KeyType, ValueType>::end() const
{
    return ConstIterator(red_black_tree<Pair<KeyType, ValueType>>::end());
}

template <typename KeyType, typename ValueType>
std::unique_ptr<Set<KeyType>> tree_map<KeyType, ValueType>::key_set() const
{
    auto result = std::make_unique<tree_set<KeyType>>();

    for (auto it=this->begin();it!=this->end();++it)
    {
        result->add(it->key);
    }

    return result;
}

template <typename KeyType, typename ValueType>
std::unique_ptr<Set<ValueType>> tree_map<KeyType, ValueType>::values() const
{
    auto result = std::make_unique<tree_set<ValueType>>();

    for (auto it=this->begin();it!=this->end();++it)
    {
        result->add(it->value);
    }

    return result;
}

template <typename KeyType, typename ValueType>
std::unique_ptr<Set<Pair<KeyType, ValueType>>> tree_map<KeyType, ValueType>::entry_set() const
{
    auto result = std::make_unique<tree_set<Pair<KeyType, ValueType>>>();

    for (auto it=this->begin();it!=this->end();++it)
    {
        result->add(Pair(it->key,it->value));
    }

    return result;
}