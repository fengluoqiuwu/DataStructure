//
// Created by Eden_ on 2024/9/9.
//
#pragma once
#include "binary_tree.h"

template <typename T, typename D>
bool binary_tree<T,D>::Iterator::has_left() const
{
    if (current == nullptr)
    {
        throw std::invalid_argument("Error in has_left() ,where current is nullptr.");
    }
    return current->left != nullptr;
}

template <typename T, typename D>
bool binary_tree<T,D>::Iterator::has_right() const
{
    if (current == nullptr)
    {
        throw std::invalid_argument("Error in has_right() ,where current is nullptr.");
    }
    return current->right != nullptr;
}

template <typename T, typename D>
typename binary_tree<T,D>::Iterator binary_tree<T,D>::Iterator::get_left() const
{
    if (current == nullptr)
    {
        throw std::invalid_argument("Error in get_left() ,where current is nullptr.");
    }
    if (current->left == nullptr)
    {
        std::cerr << "Error in get_left() which left_child is nullptr" << std::endl;
        throw std::invalid_argument("Error in get_left()");
    }

    return Iterator(current->left,outer,it_type);
}

template <typename T, typename D>
typename binary_tree<T,D>::Iterator binary_tree<T,D>::Iterator::get_right() const
{
    if (current == nullptr)
    {
        throw std::invalid_argument("Error in get_right() ,where current is nullptr.");
    }
    if (current->right == nullptr)
    {
        std::cerr << "Error get_right() which right_child is nullptr" << std::endl;
        throw std::invalid_argument("Error get_right()");
    }

    return Iterator(current->right,outer,it_type);
}

template <typename T, typename D>
typename binary_tree<T,D>::Iterator binary_tree<T,D>::Iterator::get_parent() const
{
    if (current == nullptr)
    {
        throw std::invalid_argument("Error in get_parent() ,where current is nullptr.");
    }
    if (current->parent == nullptr)
    {
        std::cerr << "Error get_parent() which parent is nullptr,maybe it is the root of a binary tree." << std::endl;
        throw std::invalid_argument("Error get_parent()");
    }

    return Iterator(current->parent,outer,it_type);
}

template <typename T, typename D>
typename binary_tree<T,D>::Iterator& binary_tree<T,D>::Iterator::left()
{
    if (current == nullptr)
    {
        throw std::invalid_argument("Error in left() ,where current is nullptr.");
    }
    if (current->left == nullptr)
    {
        std::cerr << "Error in left() which left child is nullptr" << std::endl;
        throw std::invalid_argument("Error in left()");
    }

    current = current->left;

    return *this;
}

template <typename T, typename D>
typename binary_tree<T,D>::Iterator& binary_tree<T,D>::Iterator::right()
{
    if (current == nullptr)
    {
        throw std::invalid_argument("Error in right() ,where current is nullptr.");
    }
    if (current->right == nullptr)
    {
        std::cerr << "Error in right() which right child is nullptr" << std::endl;
        throw std::invalid_argument("Error in right()");
    }

    current = current->right;

    return *this;
}

template <typename T, typename D>
typename binary_tree<T,D>::Iterator& binary_tree<T,D>::Iterator::parent()
{
    if (current == nullptr)
    {
        throw std::invalid_argument("Error in parent() ,where current is nullptr.");
    }
    if (current->parent == nullptr)
    {
        std::cerr << "Error in parent() which parent is nullptr" << std::endl;
        throw std::invalid_argument("Error in parent()");
    }

    current = current->parent;

    return *this;
}

template <typename T, typename D>
void binary_tree<T,D>::Iterator::set_left(const T& value) const
{
    if(current == nullptr)
    {
        throw std::invalid_argument("Error in set_left() ,where current is nullptr.");
    }
    if (current->left != nullptr)
    {
        current->left->data = value;
    }
    else
    {
        current->left = new tree_node(value);
    }
}

template <typename T, typename D>
void binary_tree<T,D>::Iterator::set_right(const T& value) const
{
    if (current == nullptr)
    {
        throw std::invalid_argument("Error in set_right() ,where current is nullptr.");
    }
    if (current->right != nullptr)
    {
        current->right->data = value;
    }
    else
    {
        current->right = new tree_node(value);
    }
}

template <typename T, typename D>
binary_tree<T,D> binary_tree<T,D>::Iterator::cut_subtree()
{
    if(current == nullptr)
    {
        return binary_tree();
    }

    if(current->parent == nullptr)
    {
        binary_tree temp=std::move(outer);

        return temp;
    }

    binary_tree temp(*current);

    if(current->parent->left!=nullptr)
    {
        if(current->parent->left==current)
        {
            current->parent->left=nullptr;
        }
        else
        {
            current->parent->right=nullptr;
        }
    }
    else
    {
        current->parent->right = nullptr;
    }

    tree_node* temp2 = current->parent;
    current->parent = nullptr;
    current = temp2;

    return temp;
}

template <typename T, typename D>
binary_tree<T,D> binary_tree<T,D>::Iterator::copy_subtree() const
{
    if(current == nullptr)
    {
        return binary_tree();
    }

    if(current->parent == nullptr)
    {
        binary_tree temp=outer;
        return temp;
    }

    binary_tree temp;
    copyRec(nullptr,temp.root,current);


    return temp;
}

template <typename T, typename D>
T& binary_tree<T,D>::Iterator::operator*() const
{
    if (current == nullptr)
    {
        throw std::invalid_argument("Error in operator*(),where current is nullptr.");
    }
    return current->data;
}

template <typename T, typename D>
T* binary_tree<T,D>::Iterator::operator->() const
{
    if (current == nullptr)
    {
        throw std::invalid_argument("Error in operator->(),where current is nullptr.");
    }
    return &(current->data);
}

template <typename T, typename D>
typename binary_tree<T,D>::Iterator& binary_tree<T,D>::Iterator::operator++()
{
    if(current == nullptr)
    {
        throw std::invalid_argument("Error in operator++(),where current is nullptr.");
    }

    switch(it_type)
    {
    case PREORDER:
    {
        if(has_left())
        {
            left();
            break;
        }

        if(has_right())
        {
            right();
            break;
        }

        while(
            current->parent != nullptr
            &&(current->parent->right==nullptr||current->parent->right==current)
            )
        {
            parent();
        }

        if(current->parent == nullptr)
        {
            current=nullptr;
        }
        else
        {
            current=get_first(current->parent->right,PREORDER);
        }

        break;
    }

    case INORDER:
    {
        if (has_right())
        {
            current=get_first(current->right,INORDER);
            break;
        }

        while (current->parent != nullptr && current->parent->right == current)
        {
            parent();
        }

        if (current->parent == nullptr)
        {
            current = nullptr;
        }
        else
        {
            parent();
        }

        break;
    }

    case POSTORDER:
    {
        if (current->parent == nullptr)
        {
            current = nullptr;
            break;
        }

        if (current->parent->right == current || current->parent->right == nullptr)
        {
            parent();
            break;
        }

        current = get_first(current->parent->right,POSTORDER);
        break;
    }
    }

    return *this;
}

template <typename T, typename D>
typename binary_tree<T,D>::Iterator& binary_tree<T,D>::Iterator::operator--()
{
    if (current==nullptr)
    {
        throw std::invalid_argument("Error in operator--(),where current is nullptr.");
    }

    switch(it_type)
    {
    case PREORDER:
    {
        if (current->parent == nullptr)
        {
            current = nullptr;
            break;
        }

        if (current->parent->left != nullptr && current->parent->left != current)
        {
            current = get_last(current->parent->left,PREORDER);
        }
        else
        {
            parent();
        }

        break;
    }

    case INORDER:
    {
        if (current->left !=nullptr)
        {
            current = get_last(current->left,INORDER);
            break;
        }

        while (current->parent != nullptr && current->parent->right!=current)
        {
            parent();
        }

        if (current->parent == nullptr)
        {
            current = nullptr;
        }
        else
        {
            parent();
        }

        break;
    }

    case POSTORDER:
    {
        if(has_right())
        {
            right();
            break;
        }

        if (has_left())
        {
            left();
            break;
        }

        while (
            current->parent!=nullptr
            &&(current->parent->left==nullptr||current->parent->left==current)
        )
        {
            parent();
        }

        if (current->parent == nullptr)
        {
            current = nullptr;
        }
        else
        {
            current = get_last(current->parent->left,POSTORDER);
        }

        break;
    }
    }

    return *this;
}

template <typename T, typename D>
typename binary_tree<T,D>::tree_node* binary_tree<T,D>::Iterator::get_node() const
{
    return current;
}

template <typename T, typename D>
bool binary_tree<T,D>::ConstIterator::has_left() const
{
    if (current == nullptr)
    {
        throw std::invalid_argument("Error in has_left() ,where current is nullptr.");
    }
    return current->left != nullptr;
}

template <typename T, typename D>
bool binary_tree<T,D>::ConstIterator::has_right() const
{
    if (current == nullptr)
    {
        throw std::invalid_argument("Error in has_right() ,where current is nullptr.");
    }
    return current->right != nullptr;
}

template <typename T, typename D>
typename binary_tree<T,D>::ConstIterator binary_tree<T,D>::ConstIterator::get_left() const
{
    if (current == nullptr)
    {
        throw std::invalid_argument("Error in get_left() ,where current is nullptr.");
    }
    if (current->left == nullptr)
    {
        std::cerr << "Error in get_left() which left_child is nullptr" << std::endl;
        throw std::invalid_argument("Error in get_left()");
    }

    return ConstIterator(current->left,outer,it_type);
}

template <typename T, typename D>
typename binary_tree<T,D>::ConstIterator binary_tree<T,D>::ConstIterator::get_right() const
{
    if (current == nullptr)
    {
        throw std::invalid_argument("Error in get_right() ,where current is nullptr.");
    }
    if (current->right == nullptr)
    {
        std::cerr << "Error get_right() which right_child is nullptr" << std::endl;
        throw std::invalid_argument("Error get_right()");
    }

    return ConstIterator(current->right,outer,it_type);
}

template <typename T, typename D>
typename binary_tree<T,D>::ConstIterator binary_tree<T,D>::ConstIterator::get_parent() const
{
    if (current == nullptr)
    {
        throw std::invalid_argument("Error in get_parent() ,where current is nullptr.");
    }
    if (current->parent == nullptr)
    {
        std::cerr << "Error get_parent() which parent is nullptr,maybe it is the root of a binary tree." << std::endl;
        throw std::invalid_argument("Error get_parent()");
    }

    return ConstIterator(current->parent,outer,it_type);
}

template <typename T, typename D>
typename binary_tree<T,D>::ConstIterator& binary_tree<T,D>::ConstIterator::left()
{
    if (current == nullptr)
    {
        throw std::invalid_argument("Error in left() ,where current is nullptr.");
    }
    if (current->left == nullptr)
    {
        std::cerr << "Error in left() which left child is nullptr" << std::endl;
        throw std::invalid_argument("Error in left()");
    }

    current = current->left;

    return *this;
}

template <typename T, typename D>
typename binary_tree<T,D>::ConstIterator& binary_tree<T,D>::ConstIterator::right()
{
    if (current == nullptr)
    {
        throw std::invalid_argument("Error in right() ,where current is nullptr.");
    }
    if (current->right == nullptr)
    {
        std::cerr << "Error in right() which right child is nullptr" << std::endl;
        throw std::invalid_argument("Error in right()");
    }

    current = current->right;

    return *this;
}

template <typename T, typename D>
typename binary_tree<T,D>::ConstIterator& binary_tree<T,D>::ConstIterator::parent()
{
    if (current == nullptr)
    {
        throw std::invalid_argument("Error in parent() ,where current is nullptr.");
    }
    if (current->parent == nullptr)
    {
        std::cerr << "Error in parent() which parent is nullptr" << std::endl;
        throw std::invalid_argument("Error in parent()");
    }

    current = current->parent;

    return *this;
}

template <typename T, typename D>
void binary_tree<T,D>::ConstIterator::set_left(const T& value) const
{
    if(current == nullptr)
    {
        throw std::invalid_argument("Error in set_left() ,where current is nullptr.");
    }
    if (current->left != nullptr)
    {
        current->left->data = value;
    }
    else
    {
        throw std::invalid_argument("Error in set_left() which left child is nullptr");
    }
}

template <typename T, typename D>
void binary_tree<T,D>::ConstIterator::set_right(const T& value) const
{
    if (current == nullptr)
    {
        throw std::invalid_argument("Error in set_right() ,where current is nullptr.");
    }
    if (current->right != nullptr)
    {
        current->right->data = value;
    }
    else
    {
        throw std::invalid_argument("Error in set_right() which right child is nullptr");
    }
}

template <typename T, typename D>
binary_tree<T,D> binary_tree<T,D>::ConstIterator::copy_subtree() const
{
    if(current == nullptr)
    {
        return binary_tree();
    }

    if(current->parent == nullptr)
    {
        binary_tree temp=outer;
        return temp;
    }

    binary_tree temp;
    copyRec(nullptr,temp.root,current);

    return temp;
}

template <typename T, typename D>
const T& binary_tree<T,D>::ConstIterator::operator*() const
{
    if (current == nullptr)
    {
        throw std::invalid_argument("Error in operator*(),where current is nullptr.");
    }
    return current->data;
}

template <typename T, typename D>
const T* binary_tree<T,D>::ConstIterator::operator->() const
{
    if (current == nullptr)
    {
        throw std::invalid_argument("Error in operator->(),where current is nullptr.");
    }
    return &(current->data);
}

template <typename T, typename D>
typename binary_tree<T,D>::ConstIterator& binary_tree<T,D>::ConstIterator::operator++()
{
    if(current == nullptr)
    {
        throw std::invalid_argument("Error in operator++(),where current is nullptr.");
    }

    switch(it_type)
    {
    case PREORDER:
    {
        if(has_left())
        {
            left();
            break;
        }

        if(has_right())
        {
            right();
            break;
        }

        while(
            current->parent != nullptr
            &&(current->parent->right==nullptr||current->parent->right==current)
            )
        {
            parent();
        }

        if(current->parent == nullptr)
        {
            current=nullptr;
        }
        else
        {
            current=get_first(current->parent->right,PREORDER);
        }

        break;
    }

    case INORDER:
    {
        if (has_right())
        {
            current=get_first(current->right,INORDER);
            break;
        }

        while (current->parent != nullptr && current->parent->right == current)
        {
            parent();
        }

        if (current->parent == nullptr)
        {
            current = nullptr;
        }
        else
        {
            parent();
        }

        break;
    }

    case POSTORDER:
    {
        if (current->parent == nullptr)
        {
            current = nullptr;
            break;
        }

        if (current->parent->right == current || current->parent->right == nullptr)
        {
            parent();
            break;
        }

        current = get_first(current->parent->right,POSTORDER);
        break;
    }
    }

    return *this;
}

template <typename T, typename D>
typename binary_tree<T,D>::ConstIterator& binary_tree<T,D>::ConstIterator::operator--()
{
    if (current==nullptr)
    {
        throw std::invalid_argument("Error in operator--(),where current is nullptr.");
    }

    switch(it_type)
    {
    case PREORDER:
    {
        if (current->parent == nullptr)
        {
            current = nullptr;
            break;
        }

        if (current->parent->left != nullptr && current->parent->left != current)
        {
            current = get_last(current->parent->left,PREORDER);
        }
        else
        {
            parent();
        }

        break;
    }

    case INORDER:
    {
        if (current->left !=nullptr)
        {
            current = get_last(current->left,INORDER);
            break;
        }

        while (current->parent != nullptr && current->parent->right!=current)
        {
            parent();
        }

        if (current->parent == nullptr)
        {
            current = nullptr;
        }
        else
        {
            parent();
        }

        break;
    }

    case POSTORDER:
    {
        if(has_right())
        {
            right();
            break;
        }

        if (has_left())
        {
            left();
            break;
        }

        while (
            current->parent!=nullptr
            &&(current->parent->left==nullptr||current->parent->left==current)
        )
        {
            parent();
        }

        if (current->parent == nullptr)
        {
            current = nullptr;
        }
        else
        {
            current = get_last(current->parent->left,POSTORDER);
        }

        break;
    }
    }

    return *this;
}

template <typename T, typename D>
typename binary_tree<T,D>::tree_node* binary_tree<T,D>::ConstIterator::get_node() const
{
    return current;
}

template <typename T, typename D>
bool binary_tree<T,D>::searchRec(tree_node* node, const T& value) const
{
    if (node == nullptr)
    {
        return false;
    }
    if (node->data == value)
    {
        return true;
    }

    return searchRec(node->left,value)||searchRec(node->right,value);
}

template <typename T, typename D>
binary_tree<T,D>::binary_tree()
{
    root = nullptr;
}

template <typename T, typename D>
binary_tree<T,D>::binary_tree(const T& value)
{
    root = new tree_node(value);
}

template <typename T, typename D>
binary_tree<T,D>::binary_tree(const T* initialize_list, const size_t& size, const T& label)
{

    root=nullptr;

    if(initialize_list==nullptr||*initialize_list == label||size == 0)
    {
        return;
    }

    const T* begin=initialize_list;
    const T* end=initialize_list+size;

    buildRec<const T*>(nullptr, root,begin,end, label);
}

template <typename T, typename D>
binary_tree<T,D>::binary_tree(const linked_list<T>& initialize_list, const T& label)
{
    root=nullptr;

    if(initialize_list.get_first() == label)
    {
        return;
    }

    auto begin=initialize_list.begin();
    auto end=initialize_list.end();

    buildRec<typename linked_list<T>::ConstIterator>(nullptr, root,begin,end,label);
}

template <typename T, typename D>
binary_tree<T,D>::binary_tree(const binary_tree& other)
{
    root = nullptr;
    copyRec(nullptr,root,other.root);
}

template <typename T, typename D>
binary_tree<T,D>::binary_tree(binary_tree&& other) noexcept
{
    root = other.root;
    other.root = nullptr;
}

template <typename T, typename D>
binary_tree<T,D>::~binary_tree()
{
    clear();
    root = nullptr;
}

template <typename T, typename D>
binary_tree<T,D>& binary_tree<T,D>::operator=(const binary_tree& other)
{
    if (this == &other) return *this;
    clear();
    copyRec(nullptr,root,other.root);
    return *this;
}

template <typename T, typename D>
binary_tree<T,D>& binary_tree<T,D>::operator=(binary_tree&& other) noexcept
{
    if (this == &other) return *this;
    clear();
    root = other.root;
    other.root = nullptr;
    return *this;
}

template <typename T, typename D>
bool binary_tree<T,D>::operator==(const binary_tree& other) const
{
    if (this == &other) return true;

    return equalRec(root,other.root);
}

template <typename T, typename D>
bool binary_tree<T,D>::search(const T& value) const
{
    return searchRec(root,value);
}

template <typename T, typename D>
void binary_tree<T,D>::inorder(std::function<void(const T&)> doSomething) const
{
    inorderRec(root,doSomething);
}

template <typename T, typename D>
void binary_tree<T,D>::preorder(std::function<void(const T&)> doSomething) const
{
    preorderRec(root,doSomething);
}

template <typename T, typename D>
void binary_tree<T,D>::postorder(std::function<void(const T&)> doSomething) const
{
    postorderRec(root,doSomething);
}

template <typename T, typename D>
void binary_tree<T,D>::clear(std::function<void(const T&)> doSomething)
{
    destroyRec(root,doSomething);
    root = nullptr;
}

template <typename T, typename D>
bool binary_tree<T,D>::is_empty() const
{
    return root == nullptr;
}

template <typename T, typename D>
size_t binary_tree<T,D>::get_depth() const
{
    return depthRec(root);
}

template <typename T, typename D>
size_t binary_tree<T,D>::get_size() const
{
    return sizeRec(root);
}

template <typename T, typename D>
std::string binary_tree<T,D>::to_string(const traversal type) const
{
    if (root == nullptr)
    {
        return "";
    }

    std::stringstream ss;

    switch (type)
    {
    case INORDER:
        inorder([&ss](const int i)
        {
            ss<<i<<' ';
        });
        break;
    case PREORDER:
        preorder([&ss](const int i)
        {
            ss<<i<<' ';
        });
        break;
    case POSTORDER:
        postorder([&ss](const int i)
        {
            ss<<i<<' ';
        });
        break;
    }

    std::string result = ss.str();
    result.pop_back();

    return result;
}

template <typename T, typename D>
binary_tree<T,D>::binary_tree(tree_node& root)
{
    this->root = &root;
}

template <typename T, typename D>
void binary_tree<T,D>::destroyRec(tree_node* node, std::function<void(const T&)> doSomething)
{
    if (node == nullptr)
    {
        return;
    }

    destroyRec(node->left,doSomething);
    destroyRec(node->right,doSomething);

    doSomething(node->data);

    delete node;
}

template <typename T, typename D>
void binary_tree<T,D>::inorderRec(tree_node* node, std::function<void(const T&)> doSomething)
{
    if (node == nullptr)
    {
        return;
    }

    inorderRec(node->left,doSomething);
    doSomething(node->data);
    inorderRec(node->right,doSomething);
}

template <typename T, typename D>
void binary_tree<T,D>::preorderRec(tree_node* node, std::function<void(const T&)> doSomething)
{
    if (node == nullptr)
    {
        return;
    }

    doSomething(node->data);
    preorderRec(node->left,doSomething);
    preorderRec(node->right,doSomething);
}

template <typename T, typename D>
void binary_tree<T,D>::postorderRec(tree_node* node, std::function<void(const T&)> doSomething)
{
    if (node == nullptr)
    {
        return;
    }

    postorderRec(node->left,doSomething);
    postorderRec(node->right,doSomething);
    doSomething(node->data);
}

template <typename T, typename D>
template <typename I>
void binary_tree<T,D>::buildRec(tree_node* parent, tree_node*& node, I& begin, I& end, const T& label)
{
    if(begin!=end)
    {
        if(*begin!=label)
        {
            node = new tree_node(*begin,nullptr,nullptr,parent);
            ++begin;
            buildRec(node,node->left,begin,end,label);
            buildRec(node,node->right,begin,end,label);
        }
        else
        {
            ++begin;
        }
    }
}

template <typename T, typename D>
bool binary_tree<T,D>::equalRec(tree_node* node, tree_node* other_node)
{
    if (node == nullptr)
    {
        if (other_node == nullptr)
        {
            return true;
        }

        return false;
    }

    if (node->data != other_node->data)
    {
        return false;
    }

    return equalRec(node->left,other_node->left) && equalRec(node->right,other_node->right);
}

template <typename T, typename D>
size_t binary_tree<T,D>::sizeRec(tree_node* node)
{
    if (node == nullptr)
    {
        return 0;
    }

    return 1 + sizeRec(node->left) + sizeRec(node->right);
}

template <typename T, typename D>
size_t binary_tree<T,D>::depthRec(tree_node* node)
{
    if (node == nullptr)
    {
        return 0;
    }

    return 1 + std::max(depthRec(node->left), depthRec(node->right));
}

template <typename T, typename D>
void binary_tree<T,D>::copyRec(tree_node* parent,tree_node*& node,const tree_node* other_node)
{
    if (node != nullptr)
    {
        throw std::invalid_argument("copyRec: node already exists");
    }
    if(other_node == nullptr)
    {
        return;
    }

    if constexpr (std::is_void_v<D>)
    {
        node = new tree_node(other_node->data,nullptr,nullptr,parent);
    }
    else
    {
        node = new tree_node(other_node->data,nullptr,nullptr,parent,other_node->label);
    }

    copyRec(node,node->left,other_node->left);
    copyRec(node,node->right,other_node->right);
}

template <typename T, typename D>
typename binary_tree<T,D>::tree_node *binary_tree<T,D>::get_first(tree_node *node, const traversal type)
{
    if (node == nullptr)
    {
        throw std::invalid_argument("get_first: node is nullptr.");
    }

    tree_node* result = node;

    switch (type)
    {
    case PREORDER:
        break;
    case INORDER:
        while (result->left != nullptr)
        {
            result = result->left;
        }
        break;
    case POSTORDER:
        while (result->left != nullptr||result->right != nullptr)
        {
            if (result->left != nullptr)
            {
                result = result->left;
            }
            else
            {
                result = result->right;
            }
        }
        break;
    }

    return result;
}

template <typename T, typename D>
typename binary_tree<T,D>::tree_node *binary_tree<T,D>::get_last(tree_node *node, traversal type)
{
    if (node == nullptr)
    {
        throw std::invalid_argument("get_last: node is nullptr.");
    }

    tree_node* result = node;

    switch (type)
    {
    case PREORDER:
        while (result->left != nullptr||result->right != nullptr)
        {
            if (result->right != nullptr)
            {
                result = result->right;
            }
            else
            {
                result = result->left;
            }
        }
        break;
    case INORDER:
        while (result->right != nullptr)
        {
            result = result->right;
        }
        break;
    case POSTORDER:
        break;
    }

    return result;
}

template <typename T, typename D>
typename binary_tree<T,D>::Iterator binary_tree<T,D>::begin(const traversal type)
{
    return Iterator(get_first(root,type),*this,type);
}

template <typename T, typename D>
typename binary_tree<T,D>::Iterator binary_tree<T,D>::end(const traversal type)
{
    return Iterator(nullptr,*this,type);
}

template <typename T, typename D>
typename binary_tree<T,D>::ConstIterator binary_tree<T,D>::begin(const traversal type) const
{
    return ConstIterator(get_first(root,type),*this,type);
}

template <typename T, typename D>
typename binary_tree<T,D>::ConstIterator binary_tree<T,D>::end(const traversal type) const
{
    return ConstIterator(nullptr,*this,type);
}
