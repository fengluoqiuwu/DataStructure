//
// Created by Eden_ on 2024/9/13.
//
#pragma once

#include "AVL_tree.h"


template <typename T>
AVL_tree<T>::AVL_tree()
{
}

template <typename T>
AVL_tree<T>::AVL_tree(const T &value)
{
}

template <typename T>
AVL_tree<T>::AVL_tree(const T *initialize_list, const size_t &size)
{
}

template <typename T>
AVL_tree<T>::AVL_tree(const linked_list<T> &initialize_list)
{
}

template <typename T>
AVL_tree<T>::AVL_tree(const AVL_tree &other)
{
}

template <typename T>
AVL_tree<T>::AVL_tree(AVL_tree &&other) noexcept
{
}

template <typename T>
AVL_tree<T>::~AVL_tree()
{
}

template <typename T>
AVL_tree<T> &AVL_tree<T>::operator=(const AVL_tree &other)
{
}

template <typename T>
AVL_tree<T> &AVL_tree<T>::operator=(AVL_tree &&other) noexcept
{
}

template <typename T>
bool AVL_tree<T>::operator==(const AVL_tree &other) const
{
}

template <typename T>
size_t AVL_tree<T>::get_depth() const
{

}

template <typename T>
void AVL_tree<T>::remove(const T &value, std::function<void(const T &)> doSomething)
{
}

template <typename T>
typename binary_search_tree<T, AVL_label>::ConstIterator AVL_tree<T>::begin(traversal type) const
{
}

template <typename T>
typename binary_search_tree<T, AVL_label>::ConstIterator AVL_tree<T>::end(traversal type) const
{
}

template <typename T>
void AVL_tree<T>::insertRec(tree_node *node, const T &value)
{
    binary_search_tree<T, D>::insertRec(node, value);
}

template <typename T>
size_t AVL_tree<T>::get_depth(const tree_node *node) const
{
}

template <typename T>
void AVL_tree<T>::update_depth(const tree_node *node)
{
}

template <typename T>
long long AVL_tree<T>::get_balance(const tree_node *node) const
{
}

template <typename T>
void AVL_tree<T>::removeRec(tree_node *node, const T &value, std::function<void(const T &)> doSomething)
{
}
