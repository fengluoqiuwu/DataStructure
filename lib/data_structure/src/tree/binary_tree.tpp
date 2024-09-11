//
// Created by Eden_ on 2024/9/9.
//
#pragma once
#include "binary_tree.h"

template <typename T>
bool binary_tree<T>::Iterator::has_left() const
{
    if (current == nullptr)
    {
        throw std::invalid_argument("Error in has_left() ,where current is nullptr.");
    }
    return current->left != nullptr;
}

template <typename T>
bool binary_tree<T>::Iterator::has_right() const
{
    if (current == nullptr)
    {
        throw std::invalid_argument("Error in has_right() ,where current is nullptr.");
    }
    return current->right != nullptr;
}

template <typename T>
typename binary_tree<T>::Iterator binary_tree<T>::Iterator::get_left() const
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

    return Iterator(current->left,*this);
}

template <typename T>
typename binary_tree<T>::Iterator binary_tree<T>::Iterator::get_right() const
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

    return Iterator(current->right,*this);
}

template <typename T>
typename binary_tree<T>::Iterator binary_tree<T>::Iterator::get_parent() const
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

    return Iterator(current->parent,*this);
}

template <typename T>
void binary_tree<T>::Iterator::left()
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
}

template <typename T>
void binary_tree<T>::Iterator::right()
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
}

template <typename T>
void binary_tree<T>::Iterator::parent()
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
}

template <typename T>
void binary_tree<T>::Iterator::set_left(T& value) const
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

template <typename T>
void binary_tree<T>::Iterator::set_right(T& value) const
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

template <typename T>
binary_tree<T> binary_tree<T>::Iterator::cut_subtree() const
{
    if(current == nullptr)
    {
        return binary_tree<T>();
    }

    if(current->parent == nullptr)
    {
        binary_tree temp=std::move(*this);

        return temp;
    }

    binary_tree temp(*current);

    if(current->parent->has_left())
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

template <typename T>
binary_tree<T> binary_tree<T>::Iterator::copy_subtree() const
{
    if(current == nullptr)
    {
        return binary_tree<T>();
    }

    if(current->parent == nullptr)
    {
        binary_tree temp=*this;
        return temp;
    }

    binary_tree temp;
    copyRec(nullptr,temp.root,current);


    return temp;
}

template <typename T>
T& binary_tree<T>::Iterator::operator*() const
{
    if (current == nullptr)
    {
        throw std::invalid_argument("Error in operator*(),where current is nullptr.");
    }
    return current->data;
}

template <typename T>
T* binary_tree<T>::Iterator::operator->() const
{
    if (current == nullptr)
    {
        throw std::invalid_argument("Error in operator->(),where current is nullptr.");
    }
    return &(current->data);
}

template <typename T>
iterator::ForwardIterator<T, typename binary_tree<T>::tree_node>& binary_tree<T>::Iterator::operator++()
{
    if(current == nullptr)
    {
        throw std::invalid_argument("Error in operator++(),where current is nullptr.");
    }
    //中序遍历
    if (has_left())//如果有左子节点就返回左子节点的迭代器
    {
        left();
        return *this;
    }

    if(has_right())//如过有右子节点就返回右子节点的迭代器
    {
        right();
        return *this;
    }

    //如果既没有左子节点也没有右子节点就回溯parent，
    //直到回到根节点或者找到子节点满足其有未遍历过的右子节点
    while (current->parent != nullptr&&current->parent->right!=nullptr&&current->parent->right!=current)
    {
        parent();
    }

    if (current->left == nullptr)
    {
        current=nullptr;
    }
    else
    {
        parent();right();
    }

    return *this;
}

template <typename T>
iterator::BidirectionalIterator<T, typename binary_tree<T>::tree_node>& binary_tree<T>::Iterator::operator--()
{
    if (current==nullptr)
    {
        throw std::invalid_argument("Error in operator--(),where current is nullptr.");
    }
    if (current->parent == nullptr)//如果是根节点就返回空的迭代器
    {
        current=nullptr;
        return *this;
    }

    // 回到父节点，如果是从右节点回溯的且父节点有左节点，则返回左子树的最右下节点，否则返回自身（父节点）
    parent();
    if (current->parent->left != nullptr&&current->parent->right == current)
    {
        left();
        while (has_right()||has_left())
        {
            if (has_right())
            {
                right();
            }
            else
            {
                left();
            }
        }
    }

    return *this;
}

template <typename T>
typename binary_tree<T>::tree_node* binary_tree<T>::Iterator::get_node() const
{
    return current;
}

template <typename T>
bool binary_tree<T>::ConstIterator::has_left() const
{
    if (current == nullptr)
    {
        throw std::invalid_argument("Error in has_left() ,where current is nullptr.");
    }
    return current->left != nullptr;
}

template <typename T>
bool binary_tree<T>::ConstIterator::has_right() const
{
    if (current == nullptr)
    {
        throw std::invalid_argument("Error in has_right() ,where current is nullptr.");
    }
    return current->right != nullptr;
}

template <typename T>
typename binary_tree<T>::ConstIterator binary_tree<T>::ConstIterator::get_left() const
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

    return ConstIterator(current->left,*this);
}

template <typename T>
typename binary_tree<T>::ConstIterator binary_tree<T>::ConstIterator::get_right() const
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

    return ConstIterator(current->right,*this);
}

template <typename T>
typename binary_tree<T>::ConstIterator binary_tree<T>::ConstIterator::get_parent() const
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

    return ConstIterator(current->parent,*this);
}

template <typename T>
void binary_tree<T>::ConstIterator::left()
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
}

template <typename T>
void binary_tree<T>::ConstIterator::right()
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
}

template <typename T>
void binary_tree<T>::ConstIterator::parent()
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
}

template <typename T>
void binary_tree<T>::ConstIterator::set_left(T& value) const
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

template <typename T>
void binary_tree<T>::ConstIterator::set_right(T& value) const
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

template <typename T>
binary_tree<T> binary_tree<T>::ConstIterator::copy_subtree() const
{
    if(current == nullptr)
    {
        return binary_tree<T>();
    }

    if(current->parent == nullptr)
    {
        binary_tree temp=*this;
        return temp;
    }

    binary_tree temp;
    copyRec(nullptr,temp.root,current);

    return temp;
}

template <typename T>
const T& binary_tree<T>::ConstIterator::operator*() const
{
    if (current == nullptr)
    {
        throw std::invalid_argument("Error in operator*(),where current is nullptr.");
    }
    return current->data;
}

template <typename T>
const T* binary_tree<T>::ConstIterator::operator->() const
{
    if (current == nullptr)
    {
        throw std::invalid_argument("Error in operator->(),where current is nullptr.");
    }
    return &(current->data);
}

template <typename T>
iterator::ForwardConstIterator<T, typename binary_tree<T>::tree_node>& binary_tree<T>::ConstIterator::operator++()
{
    if(current == nullptr)
    {
        throw std::invalid_argument("Error in operator++(),where current is nullptr.");
    }

    //中序遍历
    if (has_left())//如果有左子节点就返回左子节点的迭代器
    {
        left();
        return *this;
    }

    if(has_right())//如过有右子节点就返回右子节点的迭代器
    {
        right();
        return *this;
    }

    //如果既没有左子节点也没有右子节点就回溯parent，
    //直到回到根节点或者找到子节点满足其有未遍历过的右子节点
    while (current->parent != nullptr&&current->parent->right!=nullptr&&current->parent->right!=current)
    {
        parent();
    }

    if (current->left == nullptr)
    {
        current=nullptr;
    }
    else
    {
        parent();right();
    }

    return *this;
}

template <typename T>
iterator::BidirectionalConstIterator<T, typename binary_tree<T>::tree_node>& binary_tree<T>::ConstIterator::operator--()
{
    if (current==nullptr)
    {
        throw std::invalid_argument("Error in operator--(),where current is nullptr.");
    }
    if (current->parent == nullptr)//如果是根节点就返回空的迭代器
    {
        current=nullptr;
        return *this;
    }

    // 回到父节点，如果是从右节点回溯的且父节点有左节点，则返回左子树的最右下节点，否则返回自身（父节点）
    parent();
    if (current->parent->left != nullptr&&current->parent->right == current)
    {
        left();
        while (has_right()||has_left())
        {
            if (has_right())
            {
                right();
            }
            else
            {
                left();
            }
        }
    }

    return *this;
}

template <typename T>
typename binary_tree<T>::tree_node* binary_tree<T>::ConstIterator::get_node() const
{
    return current;
}

template <typename T>
bool binary_tree<T>::searchRec(tree_node* node, T& value)
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

template <typename T>
binary_tree<T>::binary_tree()
{
    root = nullptr;
}

template <typename T>
binary_tree<T>::binary_tree(const T& value)
{
    root = new tree_node(value);
}

template <typename T>
binary_tree<T>::binary_tree(const T* initialize_list, const size_t& size, const T& label)
{
    root=nullptr;

    if(*initialize_list == label)
    {
        return;
    }

    const T* begin=initialize_list;
    const T* end=initialize_list+size;

    buildRec<const T*>(nullptr, root,begin,end, label);
}

template <typename T>
binary_tree<T>::binary_tree(const linked_list<T>& initialize_list, const T& label)
{
    root=nullptr;

    if(initialize_list.get_first() == label)
    {
        return;
    }

    auto begin=initialize_list.begin();
    auto end=initialize_list.end();

    buildRec<linked_list<T>::ConstIterator>(nullptr, root,begin,end,label);
}

template <typename T>
binary_tree<T>::binary_tree(const binary_tree& other)
{
    root = new tree_node();

    copyRec(nullptr,root,other.root);
}

template <typename T>
binary_tree<T>::binary_tree(binary_tree&& other) noexcept
{
    root = other.root;
    other.root = nullptr;
}

template <typename T>
binary_tree<T>::~binary_tree()
{
    clear([](const T&) {});
}

template <typename T>
binary_tree<T>& binary_tree<T>::operator=(const binary_tree& other)
{
    if (this == &other) return *this;
    clear();
    root = new tree_node();
    copyRec(nullptr,root,other.root);
    return *this;
}

template <typename T>
binary_tree<T>& binary_tree<T>::operator=(binary_tree&& other) noexcept
{
    if (this == &other) return *this;
    clear();
    root = other.root;
    other.root = nullptr;
    return *this;
}

template <typename T>
bool binary_tree<T>::operator==(const binary_tree& other) const
{
    if (this == &other) return true;

    return equalRec(root,other.root);
}

template <typename T>
bool binary_tree<T>::search(const T& value) const
{
    return searchRec(root,value);
}

template <typename T>
void binary_tree<T>::inorder(std::function<void(const T&)> doSomething) const
{
    inorderRec(root,doSomething);
}

template <typename T>
void binary_tree<T>::preorder(std::function<void(const T&)> doSomething) const
{
    preorderRec(root,doSomething);
}

template <typename T>
void binary_tree<T>::postorder(std::function<void(const T&)> doSomething) const
{
    postorderRec(root,doSomething);
}

template <typename T>
void binary_tree<T>::clear(std::function<void(const T&)> doSomething)
{
    destroyRec(root,doSomething);
    root = nullptr;
}

template <typename T>
bool binary_tree<T>::is_empty() const
{
    return root == nullptr;
}

template <typename T>
size_t binary_tree<T>::get_depth() const
{
    return depthRec(root);
}

template <typename T>
size_t binary_tree<T>::get_size() const
{
    return size_Rec(root);
}

template <typename T>
std::string binary_tree<T>::to_string(traversal type) const
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

template <typename T>
binary_tree<T>::binary_tree(const tree_node& root)
{
    this->root = &root;
}

template <typename T>
void binary_tree<T>::destroyRec(tree_node* node, std::function<void(const T&)> doSomething)
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

template <typename T>
void binary_tree<T>::inorderRec(tree_node* node, std::function<void(const T&)> doSomething)
{
    if (node == nullptr)
    {
        return;
    }

    inorderRec(node->left,doSomething);
    doSomething(node->data);
    inorderRec(node->right,doSomething);
}

template <typename T>
void binary_tree<T>::preorderRec(tree_node* node, std::function<void(const T&)> doSomething)
{
    if (node == nullptr)
    {
        return;
    }

    doSomething(node->data);
    preorderRec(node->left,doSomething);
    postorderRec(node->right,doSomething);
}

template <typename T>
void binary_tree<T>::postorderRec(tree_node* node, std::function<void(const T&)> doSomething)
{
    if (node == nullptr)
    {
        return;
    }

    postorderRec(node->left,doSomething);
    postorderRec(node->right,doSomething);
    doSomething(node->data);
}

template <typename T>
template <typename D>
void binary_tree<T>::buildRec(tree_node* parent, tree_node*& node, D& begin, D& end, const T& label)
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

template <typename T>
bool binary_tree<T>::equalRec(tree_node* node, tree_node* other_node)
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

template <typename T>
size_t binary_tree<T>::sizeRec(tree_node* node)
{
    if (node == nullptr)
    {
        return 0;
    }

    return 1 + sizeRec(node->left) + sizeRec(node->right);
}

template <typename T>
size_t binary_tree<T>::depthRec(tree_node* node)
{
    if (node == nullptr)
    {
        return 0;
    }

    return 1 + min(depthRec(node->left), depthRec(node->right));
}

template <typename T>
void binary_tree<T>::copyRec(const tree_node* parent,tree_node*& node,const tree_node* other_node)
{
    if (node != nullptr)
    {
        throw std::invalid_argument("copyRec: node already exists");
    }
    if(other_node == nullptr)
    {
        return;
    }

    node = new tree_node(other_node->data,nullptr,nullptr,parent);

    copyRec(node,node->left,other_node->left);
    copyRec(node,node->right,other_node->right);
}

template <typename T>
typename binary_tree<T>::Iterator binary_tree<T>::begin()
{
    return Iterator(root,*this);
}

template <typename T>
typename binary_tree<T>::Iterator binary_tree<T>::end()
{
    return Iterator(nullptr,*this);
}

template <typename T>
typename binary_tree<T>::ConstIterator binary_tree<T>::begin() const
{
    return ConstIterator(root,*this);
}

template <typename T>
typename binary_tree<T>::ConstIterator binary_tree<T>::end() const
{
    return ConstIterator(nullptr,*this);
}
