//
// Created by Eden_ on 2024/9/13.
//
#pragma once

#include "AVL_tree.h"


template <typename T>
AVL_tree<T>::AVL_tree() : binary_search_tree<T, AVL_label>()
{
}

template <typename T>
AVL_tree<T>::AVL_tree(const T &value) : binary_search_tree<T, AVL_label>(value)
{
}

template <typename T>
AVL_tree<T>::AVL_tree(const T *initialize_list, const size_t &size) :
    binary_search_tree<T, AVL_label>(initialize_list, size)
{
}

template <typename T>
AVL_tree<T>::AVL_tree(const linked_list<T> &initialize_list) :
    binary_search_tree<T, AVL_label>(initialize_list)
{
}

template <typename T>
AVL_tree<T>::AVL_tree(const AVL_tree &other) : binary_search_tree<T, AVL_label>(other)
{
}

template <typename T>
AVL_tree<T>::AVL_tree(AVL_tree &&other) noexcept : binary_search_tree<T, AVL_label>(std::move(other))
{
}

template <typename T>
AVL_tree<T>::~AVL_tree() = default;

template <typename T>
AVL_tree<T> &AVL_tree<T>::operator=(const AVL_tree &other)
{
    if (this != &other)
    {
        binary_search_tree<T, AVL_label>::operator=(other);
    }
    return *this;
}

template <typename T>
AVL_tree<T> &AVL_tree<T>::operator=(AVL_tree &&other) noexcept
{
    if (this != &other)
    {
        binary_search_tree<T, AVL_label>::operator=(std::move(other));
    }
    return *this;
}

template <typename T>
bool AVL_tree<T>::operator==(const AVL_tree &other) const
{
    return binary_search_tree<T, AVL_label>::operator==(other);
}

template <typename T>
size_t AVL_tree<T>::get_depth() const
{
    return get_depth(root);
}

template <typename T>
void AVL_tree<T>::remove(const T &value, std::function<void(const T &)> doSomething)
{
    remove(root, value, doSomething);
}

template <typename T>
void AVL_tree<T>::insertRec(tree_node *node, const T &value)
{
//TODO
}

template <typename T>
size_t AVL_tree<T>::get_depth(const tree_node *node) const
{
    return node ? node->label->depth : 0;
}

template <typename T>
void AVL_tree<T>::update_depth(const tree_node *node)
{
    node->label->depth = 1 + std::max(get_depth(node->left), get_depth(node->right));
}

template <typename T>
long long AVL_tree<T>::get_balance(const tree_node *node) const
{
    return get_depth(node->left) - get_depth(node->right);
}

template <typename T>
void AVL_tree<T>::removeRec(tree_node *node, const T &value, std::function<void(const T &)> doSomething)
{

}// TODO 注意root的处理
