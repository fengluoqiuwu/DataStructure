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
    for (auto it = initialize_list.begin(); it != initialize_list.end(); ++it)
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
    insertRec(root,value);
}

template <typename T, typename D>
void binary_search_tree<T, D>::remove(const T &value, std::function<void(const T &)> doSomething)
{
    tree_node *temp = root;

    while (*temp!=value||temp!=nullptr)
    {
        temp= value > *temp ?temp->left:temp->right;
    }

    if (temp!=nullptr)
    {
        std::cerr<<"value not founded."<<std::endl;
        return;
    }

    if (temp->left == nullptr)
    {
        if(temp->parent != nullptr)
        {
            auto& child = temp->parent->left == temp ? temp->parent->left : temp->parent->right;
            child = temp->left;
        }

        temp->left->parent = temp->parent;

        delete temp;
        return;
    }

    if (temp->right == nullptr)
    {
        if(temp->parent != nullptr)
        {
            auto& child = temp->parent->left == temp ? temp->parent->left : temp->parent->right;
            child = temp->right;
        }

        temp->right->parent = temp->parent;

        delete temp;
        return;
    }

    tree_node *temp1 = temp->right;

    while (temp1->left != nullptr)
    {
        temp1 = temp1->left;
    }

    temp->data = temp1->data;

    if (temp1->parent->left == temp1)
    {
        temp1->parent->left = temp1->right;
        if (temp1->right != nullptr)
        {
            temp1->right->parent = temp1->parent;
        }
    }
    else //右子树为空
    {
        temp1->parent->right = nullptr;
    }

    delete temp1;
}

template <typename T, typename D>
const T &binary_search_tree<T, D>::get_min()
{
    tree_node temp_node = root;
    while (temp_node->left != nullptr)
    {
        temp_node = temp_node->left;
    }

    return temp_node->value;
}

template <typename T, typename D>
const T &binary_search_tree<T, D>::get_max()
{
    tree_node temp_node = root;
    while (temp_node.right != nullptr)
    {
        temp_node = temp_node.right;
    }

    return temp_node->value;
}

template <typename T, typename D>
typename binary_tree<T, D>::ConstIterator binary_search_tree<T, D>::begin(const traversal type) const
{
    return binary_tree<T, D>::begin();
}

template <typename T, typename D>
typename binary_tree<T, D>::ConstIterator binary_search_tree<T, D>::end(const traversal type) const
{
    return binary_tree<T, D>::end();
}

template <typename T, typename D>
void binary_search_tree<T, D>::rotate_left(typename binary_tree<T, D>::tree_node *node)
{
    if (node->right == nullptr)
    {
        throw std::invalid_argument("node right child is nullptr");
    }

    if (node->parent != nullptr)
    {
        auto& child = node->parent->left == node ? node->parent->left :node->parent->right;
        child = node->right;
    }

    node->right->parent = node->parent;
    tree_node *temp = node->right->left;
    node->right->left = node;
    node->parent = node->right;
    node->right = temp;
}

template <typename T, typename D>
void binary_search_tree<T, D>::rotate_right(typename binary_tree<T, D>::tree_node *node)
{
    if (node->left == nullptr)
    {
        throw std::invalid_argument("node left child is nullptr");
    }

    if (node->parent != nullptr)
    {
        auto& child = node->parent->left == node ? node->parent->left :node->parent->right;
        child = node->left;
    }

    node->left->parent = node->parent;
    tree_node *temp = node->left->right;
    node->left->right = node;
    node->parent = node->left;
    node->right = temp;
}

template <typename T, typename D>
bool binary_search_tree<T, D>::searchRec(tree_node *node, const T &value)
{
    if (node == nullptr)
    {
        return false;
    }

    if (node->value == value)
    {
        return true;
    }

    if (value > node->value)
    {
        return searchRec(node->left, value);
    }

    return searchRec(node->right, value);
}

template <typename T, typename D>
void binary_search_tree<T, D>::insertRec(tree_node *node, const T &value)
{
    if (node == nullptr)
    {
        throw std::invalid_argument("Node is null");
    }

    if (value == node->value)
    {
        std::cerr<<"Error in insertion,Receive same values"<<std::endl;
        return;
    }

    if constexpr (value > node->value)
    {
        if(node->left==nullptr)
        {
            node->left=new tree_node(value,nullptr,nullptr,node);
        }
        else
        {
            insertRec(node->left, value);
        }
    }
    else
    {
        if(node->right==nullptr)
        {
            node->right=new tree_node(value,nullptr,nullptr,node);
        }
        else
        {
            insertRec(node->right, value);
        }
    }
}
