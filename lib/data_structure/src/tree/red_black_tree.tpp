//
// Created by Eden_ on 2024/9/15.
//
#pragma once

#include "red_black_tree.h"

template <typename T>
red_black_tree<T>::red_black_tree() : binary_search_tree<T, red_black_label>()
{
}

template <typename T>
red_black_tree<T>::red_black_tree(const T &value) : binary_search_tree<T, red_black_label>(value)
{
    root->label.color = BLACK;
}

template <typename T>
red_black_tree<T>::red_black_tree(const T *initialize_list, const size_t &size)
{
    root = nullptr;

    if (initialize_list == nullptr || size == 0)
    {
        return;
    }

    for (size_t i = 0; i < size; i++)
    {
        red_black_tree::insert(initialize_list[i]);
    }
}

template <typename T>
red_black_tree<T>::red_black_tree(const linked_list<T> &initialize_list)
{
    root = nullptr;
    for (auto it = initialize_list.begin(); it != initialize_list.end(); ++it)
    {
        red_black_tree::insert(*it);
    }
}

template <typename T>
red_black_tree<T>::red_black_tree(const red_black_tree &other) : binary_search_tree<T, red_black_label>(other)
{
}

template <typename T>
red_black_tree<T>::red_black_tree(red_black_tree &&other) noexcept :
    binary_search_tree<T, red_black_label>(std::move(other))
{
}

template <typename T>
red_black_tree<T>::~red_black_tree() = default;

template <typename T>
red_black_tree<T> &red_black_tree<T>::operator=(const red_black_tree &other)
{
    if (this != &other)
    {
        binary_search_tree<T, red_black_label>::operator=(other);
    }
    return *this;
}

template <typename T>
red_black_tree<T> &red_black_tree<T>::operator=(red_black_tree &&other) noexcept
{
    if (this != &other)
    {
        binary_search_tree<T, red_black_label>::operator=(std::move(other));
    }
    return *this;
}

template <typename T>
bool red_black_tree<T>::operator==(const red_black_tree &other) const
{
    return binary_search_tree<T, red_black_label>::operator==(other);
}

template <typename T>
void red_black_tree<T>::insert(const T &value)
{
    if (root == nullptr)
    {
        root = new tree_node(value);
        set_color(root, BLACK);
    }
    else
    {
        insertRec(root, value);
    }
}

template <typename T>
void red_black_tree<T>::remove(const T &value, std::function<void(const T &)> doSomething)
{
    auto temp = root;

    while (temp->data!=value&&temp!=nullptr)
    {
        temp= value > temp->data ?temp->left:temp->right;
    }

    if (temp==nullptr)
    {
        std::cerr<<"value not founded."<<std::endl;
        return;
    }

    doSomething(temp->data);
    remove(temp);
}

template <typename T>
void red_black_tree<T>::insertRec(tree_node *node, const T &value)
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
            node->left = new typename binary_search_tree<T, red_black_label>::tree_node(value, nullptr, nullptr, node);
            fix_insert(node->left);
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
            node->right = new typename binary_search_tree<T, red_black_label>::tree_node(value, nullptr, nullptr, node);
            fix_insert(node->right);
        }
        else
        {
            insertRec(node->right, value);
        }
    }
}

template <typename T>
Color red_black_tree<T>::get_color(tree_node *node)
{
    if (node == nullptr)
    {
        return BLACK;
    }

    return node->label.color;
}

template <typename T>
void red_black_tree<T>::set_color(tree_node *node, Color c)
{
    if (node == nullptr)
    {
        throw std::invalid_argument("red_black_tree<T>::set_color: node is null");
    }
    node->label.color = c;
}

template <typename T>
void red_black_tree<T>::remove(tree_node *node)
{
    // Case 0 : 若待删除节点为树中唯一的节点的话，直接删除即可.
    if (node==root&&is_empty())
    {
        delete root;
        return;
    }

    // Case 1 : 若待删除节点N既有左子节点又有右子节点，则需找到它的后继节点进行替换
    // （仅替换数据，不改变节点颜色和内部引用关系），则后续操作中只需要将后继节点删除即可。
    if (node->left!=nullptr&&node->right!=nullptr)
    {
        auto temp = node->right;
        while (temp->left!=nullptr)
        {
            temp = temp->left;
        }

        node->data = temp->data;
        remove(temp);
    }

    // Case 2 : 若待删除节点为叶子节点，若该节点为红色，直接删除即可，
    // 删除后仍能保证红黑树的性质。若为黑色，删除后性质4被打破，需要重新进行维护。
    if(node->left==nullptr&&node->right==nullptr)
    {
        if(get_color(node)==BLACK)
        {
            fix_remove(node);
            if(get_color(root)==RED)
            {
                set_color(root, BLACK);
            }
        }
        auto &child = node->parent->left==node ? node->parent->left : node->parent->right;
        child = nullptr;
        delete node;
    }

    // Case 4 : 若待删除节点N有且仅有一个非NIL子节点，则子节点S一定为红色。
    // 则待删除节点N为黑色，直接使用子节点S替代N并将其染黑后即可满足性质4。
    else
    {
        auto sub = node->right != nullptr ? node->right : node->left;
        auto &child = node->parent->right==node ? node->parent->right : node->parent->left;
        child = sub;
        sub->parent = node->parent;
        set_color(sub, BLACK);
        delete node;
    }
}

template <typename T>
void red_black_tree<T>::fix_insert(tree_node *node)
{
    if (node == nullptr)
    {
        throw std::invalid_argument("red_black_tree<T>::fix_insert: node is null");
    }

    // Case 1 : 该树原先为空，插入第一个节点后不需要进行修正。
    if (node->parent == nullptr)
    {
        return;
    }

    // Case 2 : 当前的节点的父节点为黑色，这时性质已经满足，不需要进行修正。
    if (get_color(node->parent) == BLACK)
    {
        return;
    }

    // Case 3 : 当前节点N的父节点P和叔节点U均为红色,这种情况的维护需要：
    // 1. 将P,U节点染黑，将G节点染红（可以保证每条路径上黑色节点个数不发生改变）。
    // 2. 递归维护G节点（因为不确定G的父节点的状态，递归维护可以确保性质3成立）。
    auto parent = node->parent;
    auto uncle = parent->parent->left == parent ? parent->parent->right:parent->parent->left;
    auto grand_parent = parent->parent;

    if (get_color(uncle) == RED)
    {
        set_color(parent, BLACK);
        set_color(uncle, BLACK);
        set_color(grand_parent, RED);
        fix_insert(grand_parent);
        return;
    }

    // Case 4: 当前节点N的父节点P为红色,叔节点为黑色，且节点N与节点P的方向相反。
    // 该种情况无法直接进行维护，需要通过旋转操作将子树结构调整为Case 5的初始状态并进入Case 5进行后续维护。
    if (parent->right ==node && grand_parent->left == parent)
    {
        rotate_left(parent);
        node = parent;
        parent = node->parent;
    }
    if (parent->left == node && grand_parent->right == parent)
    {
        rotate_right(parent);
        node = parent;
        parent = node->parent;
    }

    // Case 5 : 当前节点N的父节点P为红色,叔节点为黑色，且节点N与节点P的方向相同。
    // 这种情况的维护需要：
    // 1. 若N为左子节点则右旋祖父节点G,否则左旋祖父节点G.
    // (该操作使得旋转过后P-N这条路径上的黑色节点个数比P-G-U这条路径上1,暂时打破性质4)
    // 2. 重新染色,将P染黑,将G染红,同时满足了性质3和4。
    if (parent->left == node)
    {
        rotate_right(grand_parent);
    }
    else
    {
        rotate_left(grand_parent);
    }
    set_color(parent, BLACK);
    set_color(grand_parent, RED);
}

template <typename T>
void red_black_tree<T>::fix_remove(tree_node *node)
{
    //待删除节点为黑色叶子节点
    auto parent = node->parent;
    auto brother = parent->left == node ? parent->right : parent->left;

    // Case 1 : 若兄弟节点S为红色，则父节P和侄节点C和D必为黑色(否则违反性质3).这种情况的维护需要：
    // 1. 若待删除节点N为左子节点，左旋P; 若为右子节点，右旋P。
    // 2. 将S染黑，P染红（保证S节点的父节点满足性质4）。
    // 3. 此时只需根据结构，在以P节点为根的子树中，继续对节点N进行维护即可（无需再考虑旋转染色后的S和D节点）。
    if (get_color(brother) == RED)
    {
        if(parent->left == node)
        {
            rotate_left(parent);
        }
        else
        {
            rotate_right(parent);
        }
        set_color(parent, RED);
        set_color(brother, BLACK);
        brother = parent->left == node ? parent->right : parent->left;
    }

    auto nephew_c = parent->left == node ? brother->left : brother->right;
    auto nephew_d = parent->left == node ? brother->right : brother->left;

    // Case 2 : 若兄弟节点S和侄节点C,D均为黑色，父节点P为红色。
    // 此时只需将S染红，将P染黑即可满足性质3和4。
    if (get_color(nephew_c) == BLACK&&get_color(nephew_d) == BLACK&&get_color(parent) == RED)
    {
        set_color(parent, BLACK);
        set_color(brother, RED);
        return;
    }

    // Case 3 : 若兄弟节点S，父节点P以及侄节点C,D均为黑色。
    // 此时也无法通过一步操作同时满足性质3和4，因此选择将S染红，
    // 优先满足局部性质4的成立，再递归维护P节点根据上部结构进行后续维护。
    if (get_color(nephew_c) == BLACK&&get_color(nephew_d) == BLACK&&get_color(parent) == BLACK)
    {
        set_color(brother, RED);
        fix_remove(parent);
        return;
    }

    // Case 4 : 若兄弟节点是黑色，且与N同向的侄节点C为红色，与N反向的侄节点D为黑色，父节点既可为红色又可为黑色。
    // 此时同样无法通过一步操作使其满足性质，因此优先选择将其转变为Case 5的状态利用后续Case 5的维护过程进行修正。
    // 该过程分为三步：
    // 1. 若N为左子节点，右旋S，否则左旋S。
    // 2. 将节点S染红，将节点C染黑。
    // 3. 此时已满足Case 5的条件，进入Case 5完成后续维护。
    if(get_color(nephew_c) == RED&&get_color(nephew_d) == BLACK)
    {
        if(parent->left == node)
        {
            rotate_right(brother);
        }
        else
        {
            rotate_left(parent);
        }
        set_color(brother, RED);
        set_color(nephew_c, BLACK);

        brother = parent->left == node ? parent->right : parent->left;
        nephew_c = parent->left == node ? brother->left : brother->right;
        nephew_d = parent->left == node ? brother->right : brother->left;
    }

    // Case 5 : 若兄弟节点是黑色，且与N反向的侄节点D为红色，父节点既可为红色又可为黑色。
    // 具体步骤如下：
    // 1. 若N为左子节点，左旋P，反之右旋P。
    // 2. 交换父节点P和兄弟节点S的颜色，此时性质3可能被打破。
    // 3. 将节点D染黑，同时保证了性质3和4。
    if (parent->left == node)
    {
        rotate_left(parent);
    }
    else
    {
        rotate_right(parent);
    }

    Color temp_c=get_color(parent);
    set_color(parent, get_color(brother));
    set_color(brother, temp_c);
}
