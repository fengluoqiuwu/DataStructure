//
// Created by Eden_ on 2024/9/13.
//

#ifndef AVL_TREE_H
#define AVL_TREE_H

#include "binary_search_tree.h"

namespace TreeData
{
    struct AVL_label
    {
        size_t depth=1;
    };
}

using namespace TreeData;

/**
 * @class AVL_tree
 * @brief An AVL tree implementation.
 *
 * This class represents an AVL tree, which is a self-balancing binary search tree.
 * In an AVL tree, the difference in heights between the left and right subtrees of
 * any node is at most one. It provides methods for insertion, deletion, search, and
 * retrieval of minimum and maximum values, as well as tree traversal.
 * Same values are not supported.
 *
 * @tparam T Type of elements stored in the tree.
 */
template <typename T>
class AVL_tree : protected binary_search_tree<T, AVL_label> // TODO Add Copy of label to binary_tree
{
public:
    /**
     * @brief Default constructor for the AVL tree.
     *
     * Initializes an empty AVL tree.
     */
    AVL_tree();

    /**
     * @brief Constructor that initializes the AVL tree with a single value.
     *
     * @param value The value to initialize the root node with.
     */
    explicit AVL_tree(const T &value);

    /**
     * @brief Constructor that initializes the AVL tree with an array of values.
     *
     * @param initialize_list Pointer to the array of values.
     * @param size The number of elements in the array.
     */
    AVL_tree(const T *initialize_list, const size_t &size);

    /**
     * @brief Constructor that initializes the AVL tree from a linked list.
     *
     * @param initialize_list The linked list to initialize the tree with.
     */
    explicit AVL_tree(const linked_list<T> &initialize_list);

    /**
     * @brief Copy constructor for the AVL tree.
     *
     * @param other The AVL tree to copy from.
     */
    AVL_tree(const AVL_tree &other);

    /**
     * @brief Move constructor for the AVL tree.
     *
     * @param other The AVL tree to move from.
     */
    AVL_tree(AVL_tree &&other) noexcept;

    /**
     * @brief Destructor for the AVL tree.
     *
     * Cleans up all allocated resources.
     */
    ~AVL_tree() override;

    /**
     * @brief Copy assignment operator for the AVL tree.
     *
     * @param other The AVL tree to copy from.
     * @return A reference to this AVL tree.
     */
    AVL_tree &operator=(const AVL_tree &other);

    /**
     * @brief Move assignment operator for the AVL tree.
     *
     * @param other The AVL tree to move from.
     * @return A reference to this AVL tree.
     */
    AVL_tree &operator=(AVL_tree &&other) noexcept;

    /**
     * @brief Equality operator for comparing two AVL trees.
     *
     * @param other The AVL tree to compare with.
     * @return True if both AVL trees are equal; otherwise, false.
     */
    bool operator==(const AVL_tree &other) const;

    /**
     * @brief Performs an in-order traversal of the tree.
     *
     * @param doSomething A function to apply to each node's data during traversal.
     */
    using binary_search_tree<T, AVL_label>::inorder;

    /**
     * @brief Performs a pre-order traversal of the tree.
     *
     * @param doSomething A function to apply to each node's data during traversal.
     */
    using binary_search_tree<T, AVL_label>::preorder;

    /**
     * @brief Performs a post-order traversal of the tree.
     *
     * @param doSomething A function to apply to each node's data during traversal.
     */
    using binary_search_tree<T, AVL_label>::postorder;

    /**
     * transform binary tree to string
     * @param type traversal type
     * @return traversal string
     */
    using binary_search_tree<T, AVL_label>::to_string;

    /**
     * @brief Clears the tree, releasing all resources.
     *
     * @param doSomething A function to apply to each node's data during traversal.
     */
    using binary_search_tree<T, AVL_label>::clear;

    /**
     * @brief Checks if the tree is empty.
     *
     * @return True if the tree is empty, false otherwise.
     */
    using binary_search_tree<T, AVL_label>::is_empty;

    /**
     * @brief Gets the number of nodes in the tree.
     *
     * @return The size of the tree.
     */
    using binary_search_tree<T, AVL_label>::get_size;

    /**
     * @brief Gets the depth of the tree.
     *
     * @return The depth of the tree.
     */
    [[nodiscard]] size_t get_depth() const override;

    /**
     * @brief Retrieves the minimum value in the AVL tree.
     *
     * @return The minimum value in the tree.
     */
    using binary_search_tree<T, AVL_label>::get_min;

    /**
     * @brief Retrieves the maximum value in the AVL tree.
     *
     * @return The maximum value in the tree.
     */
    using binary_search_tree<T, AVL_label>::get_max;

    /**
     * @brief Searches for a value in the AVL tree.
     *
     * @param value The value to search for.
     * @return True if the value is found, false otherwise.
     */
    using binary_search_tree<T, AVL_label>::search;

    /**
     * @brief Inserts a new value into the AVL tree.
     *
     * @param value The value to be inserted.
     */
    using binary_search_tree<T, AVL_label>::insert;

    /**
     * @brief Removes a value from the AVL tree.
     *
     * @param value The value to be removed.
     * @param doSomething A function to apply to each node's data during delete.
     */
    // ReSharper disable once CppHidingFunction
    void remove(const T &value, std::function<void(const T &)> doSomething = [](const T &) {});

    /**
     * @brief Const bidirectional iterator for the AVL tree.
     *
     * This iterator provides bidirectional traversal capabilities for the AVL tree,
     * with read-only access to the data.
     */
    using binary_search_tree<T, AVL_label>::ConstIterator;

    /**
     * @brief Returns an iterator to the beginning of the tree traversal.
     *
     * @param type The type of traversal to use (preorder, inorder, or postorder).
     * @return An iterator to the beginning of the traversal.
     */
    using binary_search_tree<T, AVL_label>::begin;

    /**
     * @brief Returns an iterator to the end of the tree traversal.
     *
     * @param type The type of traversal to use (preorder, inorder, or postorder).
     * @return An iterator to the end of the traversal.
     */
    using binary_search_tree<T, AVL_label>::end;

protected:
    using binary_search_tree<T, AVL_label>::root; ///< Pointer to the root node of the tree.
    using binary_search_tree<T, AVL_label>::tree_node; ///< A node in the binary tree.

    /**
     * @brief Performs a left rotation on the given node.
     *
     * @param node The node to rotate.
     */
    void rotate_left(typename binary_search_tree<T, AVL_label>::tree_node *node) override;

    /**
     * @brief Performs a right rotation on the given node.
     *
     * @param node The node to rotate.
     */
    void rotate_right(typename binary_search_tree<T, AVL_label>::tree_node *node) override;

    /**
     * @brief Recursively inserts a value into the AVL tree.
     *
     * @param node The node to start the insert.
     * @param value The value to insert.
     */
    void insertRec(typename binary_search_tree<T, AVL_label>::tree_node *node, const T &value) override;

private:
    /**
     * @brief Recursively calculates the depth of the subtree rooted at the given node.
     *
     * @param node The node to start the depth calculation from.
     * @return The depth of the subtree.
     */
    static size_t get_depth(const typename binary_search_tree<T, AVL_label>::tree_node *node);

    /**
     * @brief Updates the depth of the nodes in the tree.
     *
     * @param node The node to start updating from.
     */
    static void update_depth(typename binary_search_tree<T, AVL_label>::tree_node *node);

    /**
     * @brief Calculates the balance factor of the given node.
     *
     * @param node The node to calculate the balance factor for.
     * @return The balance factor of the node.
     */
    static long long get_balance(const typename binary_search_tree<T, AVL_label>::tree_node *node);

    /**
     * @brief Recursively removes a value from the AVL tree.
     *
     * @param node The node to start the removal from.
     * @param value The value to be removed.
     * @param doSomething A function to apply to each node's data during delete.
     */
    void removeRec(
        typename binary_search_tree<T, AVL_label>::tree_node *node, const T &value,
        std::function<void(const T &)> doSomething = [](const T &) {});


    /**
     * @brief Balance a node in the AVL tree.
     *
     * Recalculate the depth of node,
     * balance a node in the AVL tree by left and right rotate,
     * suppose its children are balanced before.
     *
     * @param node The node to balance.
     */
    void balance(typename binary_search_tree<T, AVL_label>::tree_node *node);
};

#include "AVL_tree.tpp"

#endif //AVL_TREE_H
