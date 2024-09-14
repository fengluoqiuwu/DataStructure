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
AVL_tree<T>::AVL_tree(const linked_list<T> &initialize_list) : binary_search_tree<T, AVL_label>(initialize_list)
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
    removeRec(root, value, doSomething);
}

template <typename T>
void AVL_tree<T>::rotate_left(typename binary_search_tree<T, AVL_label>::tree_node *node)
{
    binary_search_tree<T, AVL_label>::rotate_left(node);
    update_depth(node);
    update_depth(node->parent);
}

template <typename T>
void AVL_tree<T>::rotate_right(typename binary_search_tree<T, AVL_label>::tree_node *node)
{
    binary_search_tree<T, AVL_label>::rotate_right(node);
    update_depth(node);
    update_depth(node->parent);
}

template <typename T>
void AVL_tree<T>::insertRec(typename binary_search_tree<T, AVL_label>::tree_node *node, const T &value)
{
    if (node == nullptr)
    {
        throw std::invalid_argument("Node is null");
    }

    if (value == node->data)
    {
        std::cerr << "Error in insertion,Receive same values" << std::endl;
        return;
    }

    if (value < node->data)
    {
        if (node->left == nullptr)
        {
            node->left = new typename binary_search_tree<T, AVL_label>::tree_node(value, nullptr, nullptr, node);
        }
        else
        {
            insertRec(node->left, value);
        }
    }
    else
    {
        if (node->right == nullptr)
        {
            node->right = new typename binary_search_tree<T, AVL_label>::tree_node(value, nullptr, nullptr, node);
        }
        else
        {
            insertRec(node->right, value);
        }
    }

    balance(node);
}

template <typename T>
size_t AVL_tree<T>::get_depth(const typename binary_search_tree<T, AVL_label>::tree_node *node)
{
    return node ? node->label->depth : 0;
}

template <typename T>
void AVL_tree<T>::update_depth(const typename binary_search_tree<T, AVL_label>::tree_node *node)
{
    node->label->depth = 1 + std::max(get_depth(node->left), get_depth(node->right));
}

template <typename T>
long long AVL_tree<T>::get_balance(const typename binary_search_tree<T, AVL_label>::tree_node *node)
{
    return get_depth(node->left) - get_depth(node->right);
}

template <typename T>
void AVL_tree<T>::removeRec(typename binary_search_tree<T, AVL_label>::tree_node *node, const T &value, std::function<void(const T &)> doSomething)
{
    if (node == nullptr)
    {
        std::cerr << "value not founded." << std::endl;
        return;
    }

    if (value < node->data)
    {
        deleteRec(node->left, value, doSomething);
    }
    else if (value > node->data)
    {
        deleteRec(node->right, value, doSomething);
    }
    else
    {
        if (node->left != nullptr || node->right != nullptr)
        {
            auto temp = node->left ? node->left : node->right;

            if (node->parent != nullptr)
            {
                auto &child = node->parent->left == node ? node->parent->left : node->parent->right;
                child = temp;
            }
            else
            {
                root = temp;
            }
            temp->parent = node->parent;

            doSomething(node->data);
            delete node;
            return;
        }

        auto temp = node->right;
        while (temp->left != nullptr)
        {
            temp = temp->left;
        }

        doSomething(node->data);

        node->data = temp->data;

        removeRec(node, temp->data);
    }

    balance(node);
}

template <typename T>
void AVL_tree<T>::balance(typename binary_search_tree<T, AVL_label>::tree_node *node)
{
    if (node == nullptr)
    {
        return;
    }

    update_depth(node);

    const long long balance = get_balance(node);

    if (balance > 1)
    {
        if (get_balance(node->left) >= 0)
        {
            rotate_right(node);
        }
        else
        {
            rotate_left(node->left);
            rotate_right(node);
        }
    }

    if (balance < -1)
    {
        if (get_balance(node->right) <= 0)
        {
            rotate_left(node);
        }
        else
        {
            rotate_right(node->right);
            rotate_left(node);
        }
    }
}
