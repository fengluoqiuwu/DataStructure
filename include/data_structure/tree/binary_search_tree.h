//
// Created by Eden_ on 2024/9/12.
//

#ifndef BINARY_SEARCH_TREE_H
#define BINARY_SEARCH_TREE_H

#include "binary_tree.h"

using namespace TreeData;

/**
 * @class binary_search_tree
 * @brief A binary search tree implementation.
 *
 * This class represents a binary search tree (BST), which is a binary tree where
 * each node has a key greater than all keys in its left subtree and less than
 * all keys in its right subtree. It provides methods for insertion, deletion, search,
 * and retrieval of minimum and maximum values, as well as tree traversal.
 * Same values are not supported.
 *
 * @tparam T Type of elements stored in the tree.
 * @tparam D Optional type parameter for additional data or behavior.
 */
template <typename T, typename D = void>
class binary_search_tree : protected binary_tree<T, D>
{
public:
    /**
     * @brief Default constructor for the binary search tree.
     *
     * Initializes an empty binary search tree.
     */
    binary_search_tree();

    /**
     * @brief Constructor that initializes the tree with a single value.
     *
     * @param value The value to initialize the root node with.
     */
    explicit binary_search_tree(const T &value);

    /**
     * @brief Constructor that initializes the tree with an array of values.
     *
     * @param initialize_list Pointer to the array of values.
     * @param size The number of elements in the array.
     */
    binary_search_tree(const T *initialize_list, const size_t &size);

    /**
     * @brief Constructor that initializes the tree from a linked list.
     *
     * @param initialize_list The linked list to initialize the tree with.
     */
    explicit binary_search_tree(const linked_list<T> &initialize_list);

    /**
     * @brief Copy constructor for the binary search tree.
     *
     * @param other The binary search tree to copy from.
     */
    binary_search_tree(const binary_search_tree &other);

    /**
     * @brief Move constructor for the binary search tree.
     *
     * @param other The binary search tree to move from.
     */
    binary_search_tree(binary_search_tree &&other) noexcept;

    /**
     * @brief Destructor for the binary search tree.
     *
     * Cleans up all allocated resources.
     */
    ~binary_search_tree() override;

    /**
     * @brief Copy assignment operator for the binary search tree.
     *
     * @param other The binary search tree to copy from.
     * @return A reference to this binary search tree.
     */
    binary_search_tree &operator=(const binary_search_tree &other);

    /**
     * @brief Move assignment operator for the binary search tree.
     *
     * @param other The binary search tree to move from.
     * @return A reference to this binary search tree.
     */
    binary_search_tree &operator=(binary_search_tree &&other) noexcept;

    /**
     * @brief Equality operator for comparing two binary search trees.
     *
     * @param other The binary search tree to compare with.
     * @return True if both binary search trees are equal; otherwise, false.
     */
    bool operator==(const binary_search_tree &other) const;

    /**
     * @brief Performs an in-order traversal of the tree.
     *
     * @param doSomething A function to apply to each node's data during traversal.
     */
    using binary_tree<T, D>::inorder;

    /**
     * @brief Performs a pre-order traversal of the tree.
     *
     * @param doSomething A function to apply to each node's data during traversal.
     */
    using binary_tree<T, D>::preorder;

    /**
     * @brief Performs a post-order traversal of the tree.
     *
     * @param doSomething A function to apply to each node's data during traversal.
     */
    using binary_tree<T, D>::postorder;

    /**
     * @brief Clears the tree, releasing all resources.
     *
     * @param doSomething A function to apply to each node's data during traversal.
     */
    using binary_tree<T, D>::clear;

    /**
     * @brief Checks if the tree is empty.
     *
     * @return True if the tree is empty, false otherwise.
     */
    using binary_tree<T, D>::is_empty;

    /**
     * @brief Gets the number of nodes in the tree.
     *
     * @return The size of the tree.
     */
    using binary_tree<T, D>::get_size;

    /**
     * @brief Gets the depth of the tree.
     *
     * @return The depth of the tree.
     */
    using binary_tree<T, D>::get_depth;

    /**
     * transform binary tree to string
     * @param type traversal type
     * @return traversal string
     */
    using binary_tree<T, D>::to_string;

    /**
     * @brief Inserts a new value into the binary search tree.
     *
     * @param value The value to be inserted.
     */
    void insert(const T &value);

    /**
     * @brief Searches for a value in the binary search tree.
     *
     * @param value The value to search for.
     */
    using binary_tree<T, D>::search;

    /**
     * @brief Removes a value from the binary search tree.
     *
     * @param value The value to be removed.
     * @param doSomething A function to apply to each node's data during delete.
     */
    // ReSharper disable once CppHiddenFunction
    void remove(const T &value, std::function<void(const T &)> doSomething = [](const T &) {});

    /**
     * @brief Retrieves the minimum value in the binary search tree.
     *
     * @return The minimum value in the tree.
     */
    const T &get_min();

    /**
     * @brief Retrieves the maximum value in the binary search tree.
     *
     * @return The maximum value in the tree.
     */
    const T &get_max();

    /**
     * @brief Const bidirectional iterator for the binary tree.
     *
     * This iterator provides bidirectional traversal capabilities for the binary tree,
     * with read-only access to the data.
     */
    using binary_tree<T, D>::ConstIterator;

    /**
     * @brief Returns an iterator to the beginning of the tree traversal.
     *
     * @param type The type of traversal to use (preorder, inorder, or postorder).
     * @return An iterator to the beginning of the traversal.
     */
    // ReSharper disable once CppHidingFunction
    typename binary_tree<T, D>::ConstIterator begin(traversal type = PREORDER) const;

    /**
     * @brief Returns an iterator to the end of the tree traversal.
     *
     * @param type The type of traversal to use (preorder, inorder, or postorder).
     * @return An iterator to the end of the traversal.
     */
    // ReSharper disable once CppHidingFunction
    typename binary_tree<T, D>::ConstIterator end(traversal type = PREORDER) const;

protected:
    using binary_tree<T, D>::root; ///< Pointer to the root node of the tree.

    /**
     * @brief A node in the binary tree.
     *
     * This structure represents a node in the binary tree, storing data and pointers to
     * its left and right children, as well as its parent.
     */
    using binary_tree<T, D>::tree_node;

    /**
     * @brief Performs a left rotation on the given node.
     *
     * @param node The node to rotate.
     */
    void rotate_left(typename binary_tree<T, D>::tree_node *node); // TODO, Test

    /**
     * @brief Performs a right rotation on the given node.
     *
     * @param node The node to rotate.
     */
    void rotate_right(typename binary_tree<T, D>::tree_node *node); // TODO, Test

    /**
     * @brief Recursively inserts for a value in the binary tree.
     *
     * @param node The node to start the insert.
     * @param value The value to insert.
     */
    virtual void insertRec(typename binary_tree<T, D>::tree_node *node, const T &value);

private:
    /**
     * @brief Recursively searches for a value in the binary tree.
     *
     * @param node The node to start the search from.
     * @param value The value to search for.
     * @return True if the value is found, false otherwise.
     */
    bool searchRec(typename binary_tree<T, D>::tree_node *node, const T &value) const override;
};

#include "binary_search_tree.tpp"

#endif // BINARY_SEARCH_TREE_H
