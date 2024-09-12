//
// Created by Eden_ on 2024/9/12.
//

#pragma once
#include "binary_search_tree.h"

template <typename T, typename D>
binary_search_tree<T, D>::binary_search_tree() : binary_tree<T, D>() {}

template <typename T, typename D>
binary_search_tree<T, D>::binary_search_tree(const T &value) : binary_tree<T, D>(value) {}

template <typename T, typename D>
binary_search_tree<T, D>::binary_search_tree(const T *initialize_list, const size_t &size)
{
    for (size_t i = 0; i < size; i++)
    {
        insert(initialize_list[i]);
    }
}

template <typename T, typename D>
binary_search_tree<T, D>::binary_search_tree(const linked_list<T> &initialize_list, const T &label)
{
    for (auto it = initialize_list.begin(); it != initialize_list.end(); it++)
    {
        insert(*it);
    }
}

template <typename T, typename D>
binary_search_tree<T, D>::binary_search_tree(const binary_search_tree &other) : binary_tree<T, D>(other) {}

template <typename T, typename D>
binary_search_tree<T, D>::binary_search_tree(binary_search_tree &&other) : binary_tree<T, D>(std::move(other)) {}

template <typename T, typename D>
binary_search_tree<T, D>::~binary_search_tree()=default;

template <typename T, typename D>
binary_search_tree<T, D> &binary_search_tree<T, D>::operator=(const binary_search_tree &other)
{
    if (this != &other)
    {
        binary_tree<T, D>::operator=(other);
    }
    return *this;
}

template <typename T, typename D>
binary_search_tree<T, D> &binary_search_tree<T, D>::operator=(binary_search_tree &&other)
{
    if (this != &other)
    {
        binary_tree<T, D>::operator=(std::move(other));
    }
    return *this;
}

template <typename T, typename D>
bool binary_search_tree<T, D>::operator==(const binary_search_tree &other) const
{
    return binary_tree<T, D>::operator==(other);
}

template <typename T, typename D>
void binary_search_tree<T, D>::insert(const T &value)// TODO
{
}

template <typename T, typename D>
void binary_search_tree<T, D>::search(const T &value)
{
}

template <typename T, typename D>
void binary_search_tree<T, D>::remove(const T &value)
{
}

template <typename T, typename D>
const T &binary_search_tree<T, D>::get_min()
{
}

template <typename T, typename D>
const T &binary_search_tree<T, D>::get_max()
{
}

template <typename T, typename D>
typename binary_tree<T, D>::ConstIterator binary_search_tree<T, D>::begin(traversal type) const
{
}

template <typename T, typename D>
typename binary_tree<T, D>::ConstIterator binary_search_tree<T, D>::end(traversal type) const
{
}

template <typename T, typename D>
void binary_search_tree<T, D>::rotate_left(typename binary_tree<T, D>::tree_node *node)
{
}

template <typename T, typename D>
void binary_search_tree<T, D>::rotate_right(typename binary_tree<T, D>::tree_node *node)
{
}
