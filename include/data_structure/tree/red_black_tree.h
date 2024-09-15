//
// Created by Eden_ on 2024/9/15.
//

#ifndef RED_BLACK_TREE_H
#define RED_BLACK_TREE_H

#include "binary_search_tree.h"

namespace TreeData
{
    enum Color
    {
        RED,BLACK
    };

    struct red_black_label
    {
        Color color = RED;

        bool operator==(const red_black_label&) const=default;
    };
}

using namespace TreeData;

/**
 * @class red_black_tree
 * @brief A red-black tree implementation.
 *
 * This class represents a red-black tree, a balanced binary search tree where each node has an additional color attribute (red or black)
 * that helps in maintaining the balance of the tree during insertions and deletions.
 *
 * @tparam T Type of elements stored in the tree.
 */
template <typename T>
class red_black_tree : protected binary_search_tree<T>
{
public:
    /**
     * @brief Default constructor for the red-black tree.
     *
     * Initializes an empty red-black tree.
     */
    red_black_tree();

    /**
     * @brief Constructor that initializes the tree with a single value.
     *
     * @param value The value to initialize the root node with.
     */
    explicit red_black_tree(const T &value);

    /**
     * @brief Constructor that initializes the tree with an array of values.
     *
     * @param initialize_list Pointer to the array of values.
     * @param size The number of elements in the array.
     */
    red_black_tree(const T *initialize_list, const size_t &size);

    /**
     * @brief Constructor that initializes the tree from a linked list.
     *
     * @param initialize_list The linked list to initialize the tree with.
     */
    explicit red_black_tree(const linked_list<T> &initialize_list);

    /**
     * @brief Copy constructor for the red-black tree.
     *
     * @param other The red-black tree to copy from.
     */
    red_black_tree(const red_black_tree &other);

    /**
     * @brief Move constructor for the red-black tree.
     *
     * @param other The red-black tree to move from.
     */
    red_black_tree(red_black_tree &&other) noexcept;

    /**
     * @brief Destructor for the red-black tree.
     *
     * Cleans up all allocated resources.
     */
    ~red_black_tree() override;

    /**
     * @brief Copy assignment operator for the red-black tree.
     *
     * @param other The red-black tree to copy from.
     * @return A reference to this red-black tree.
     */
    red_black_tree &operator=(const red_black_tree &other);

    /**
     * @brief Move assignment operator for the red-black tree.
     *
     * @param other The red-black tree to move from.
     * @return A reference to this red-black tree.
     */
    red_black_tree &operator=(red_black_tree &&other) noexcept;

    /**
     * @brief Equality operator for comparing two red-black trees.
     *
     * @param other The red-black tree to compare with.
     * @return True if both red-black trees are equal; otherwise, false.
     */
    bool operator==(const red_black_tree &other) const;

    /**
     * @brief Performs an in-order traversal of the tree.
     *
     * In-order traversal visits nodes in ascending order of value.
     *
     * @param visit A function to apply to each node's value during traversal.
     */
    using binary_search_tree<T, red_black_label>::inorder;

    /**
     * @brief Performs a pre-order traversal of the tree.
     *
     * Pre-order traversal visits the root node first, then recursively visits the left and right subtrees.
     *
     * @param visit A function to apply to each node's value during traversal.
     */
    using binary_search_tree<T, red_black_label>::preorder;

    /**
     * @brief Performs a post-order traversal of the tree.
     *
     * Post-order traversal recursively visits the left and right subtrees, then visits the root node.
     *
     * @param visit A function to apply to each node's value during traversal.
     */
    using binary_search_tree<T, red_black_label>::postorder;

    /**
     * @brief Clears the tree, removing all nodes.
     *
     * Deallocates memory used by the tree nodes and resets the tree to an empty state.
     */
    using binary_search_tree<T, red_black_label>::clear;

    /**
     * @brief Checks if the tree is empty.
     *
     * @return True if the tree is empty; otherwise, false.
     */
    using binary_search_tree<T, red_black_label>::is_empty;

    /**
     * @brief Returns the number of nodes in the tree.
     *
     * @return The size of the tree.
     */
    using binary_search_tree<T, red_black_label>::get_size;

    /**
     * @brief Returns the depth of the tree.
     *
     * The depth is the number of nodes along the longest path from the root to a leaf.
     *
     * @return The depth of the tree.
     */
    using binary_search_tree<T, red_black_label>::get_depth;

    /**
     * @brief Converts the tree to a string representation.
     *
     * @param traversal_type The type of traversal to use for constructing the string (in-order, pre-order, or
     * post-order).
     * @return A string representation of the tree based on the specified traversal.
     */
    using binary_search_tree<T, red_black_label>::to_string;

    /**
     * @brief Retrieves the minimum value in the tree.
     *
     * @return The minimum value stored in the tree.
     */
    using binary_search_tree<T, red_black_label>::get_min;

    /**
     * @brief Retrieves the maximum value in the tree.
     *
     * @return The maximum value stored in the tree.
     */
    using binary_search_tree<T, red_black_label>::get_max;

    /**
     * @brief Searches for a value in the tree.
     *
     * @param value The value to search for.
     * @return True if the value is found; otherwise, false.
     */
    using binary_search_tree<T, red_black_label>::search;

    /**
     * @brief Inserts a value into the tree.
     *
     * The red-black properties will be maintained after the insertion.
     *
     * @param value The value to insert.
     */
    void insert(const T &value) override;

    /**
     * @brief ConstIterator for tree traversal.
     *
     * Provides a way to traverse the tree in a read-only manner.
     */
    using binary_search_tree<T, red_black_label>::ConstIterator;

    /**
     * @brief Removes a value from the red-black tree.
     *
     * @param value The value to be removed.
     * @param doSomething A function to apply to each node's data during delete.
     */
    // ReSharper disable once CppHidingFunction
    void remove(const T &value, std::function<void(const T &)> doSomething = [](const T &) {});

protected:
    /**
     * @brief Root node of the tree.
     *
     * Points to the root node of the binary search tree.
     */
    using binary_search_tree<T, red_black_label>::root;

    /**
     * @brief Alias for a node in the binary search tree.
     *
     * Each node stores a value and links to its left and right children.
     */
    using binary_search_tree<T, red_black_label>::tree_node;

    /**
     * @brief Performs a left rotation on the given node.
     *
     * Left rotation is a tree operation that rotates the nodes to the left to maintain balance.
     *
     * @param node The node to perform the left rotation on.
     */
    using binary_search_tree<T, red_black_label>::rotate_left;

    /**
     * @brief Performs a right rotation on the given node.
     *
     * Right rotation is a tree operation that rotates the nodes to the right to maintain balance.
     *
     * @param node The node to perform the right rotation on.
     */
    using binary_search_tree<T, red_black_label>::rotate_right;

    /**
     * @brief Recursively inserts a value in the red-black tree, while maintaining balance.
     *
     * @param node The node to start the insert from.
     * @param value The value to insert.
     */
    void insertRec(typename binary_search_tree<T, red_black_label>::tree_node *node, const T &value) override;

private:
    /**
     * @brief Gets the color of the given node.
     *
     * @param node The node whose color is to be retrieved.
     * @return The color of the node.
     */
    static Color get_color(typename binary_search_tree<T, red_black_label>::tree_node *node);

    /**
     * @brief set the color of the given node.
     *
     * @param node The node whose color is to be set
     * @param c color to be set
     */
    static void set_color(typename binary_search_tree<T, red_black_label>::tree_node *node, Color c);

    /**
     * @brief Removes a node from the red-black tree and maintains balance.
     *
     * @param node The node to remove.
     */
    void remove(typename binary_search_tree<T, red_black_label>::tree_node *node);

    /**
     * @brief Fixes the tree after an insertion to maintain red-black properties.
     *
     * @param node The node to start fixing from.
     */
    void fix_insert(typename binary_search_tree<T, red_black_label>::tree_node *node);

    /**
     * @brief Fixes the tree after a removal to maintain red-black properties.
     *
     * @param node The node to start fixing from.
     */
    void fix_remove(typename binary_search_tree<T, red_black_label>::tree_node *node);
};

#include "red_black_tree.tpp"

#endif //RED_BLACK_TREE_H
