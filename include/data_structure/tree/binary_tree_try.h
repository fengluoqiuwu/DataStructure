//
// Created by Eden_ on 2024/9/9.
//

#ifndef BINARY_TREE_H
#define BINARY_TREE_H

#include <functional>
#include <linked_list.h>


/**
 * @class binary_tree
 * @brief A class representing a binary tree data structure.
 *
 * This class provides methods to insert elements, search for elements,
 * and traverse the tree in different orders (in-order, pre-order, and post-order).
 * The tree is an unbalanced binary tree.
 *
 * Supported initialization types:
 * - For arrays: giving a ending label and rewrite the == operator..
 */
template<typename T>
class binary_tree {
protected:
    /**
     * Represents a node in a tree data structure.
     */
    struct TreeNode {
     T value;               /**< The value stored in the node. */
     TreeNode* left;     /**< Pointer to the left child node. */
     TreeNode* right;    /**< Pointer to the right child node. */

     /**
      * Constructs a TreeNode with a given value and null children.
      * Complexity: O(1)
      * @param value The value to be stored in the node.
      */
     explicit TreeNode(const T& value)
         : value(value), left(nullptr), right(nullptr) {}

     /**
      * Constructs a TreeNode with a given value and specified left and right children.
      * Complexity: O(1)
      * @param value The value to be stored in the node.
      * @param left Pointer to the left child node.
      * @param right Pointer to the right child node.
      */
     TreeNode(const T& value, TreeNode<T>* left, TreeNode<T>* right)
         : value(value), left(left), right(right) {}
    };

    TreeNode<T>* root; /**< Pointer to the root node of the tree. */

    /**
     * @brief Searches for a value in the subtree rooted at the given node.
     *
     * This method is used internally for searching a value within the binary tree.
     * It is a recursive function that traverses the tree starting from the given
     * node to find whether the specified value exists in the subtree.
     *
     * @param node The root of the subtree to search within.
     * @param value The value to search for.
     * @return True if the value is found in the subtree, false otherwise.
     */
    bool searchRec(TreeNode<T>* node, const T& value) const;

private:

    /**
     * @brief Recursively destroys all nodes in the subtree rooted at the given node.
     *
     * This method is used internally to clean up and deallocate memory for the entire
     * subtree starting from the given node. It is called recursively to ensure all nodes
     * are properly destroyed.
     *
     * @param node The root of the subtree to destroy.
     */
    void destroyRec(TreeNode<T>* node);

    /**
     * @brief Recursively performs an in-order traversal of the subtree rooted at the given node.
     *
     * This method is used internally to traverse the binary tree in in-order fashion
     * starting from the given node. For each node visited, the provided function is called
     * with the node's value.
     *
     * @param node The root of the subtree to traverse.
     * @param visit A function to apply to each node's value during traversal.
     */
    void inorderRec(TreeNode<T>* node, std::function<void(const T&)> visit) const;

    /**
     * @brief Recursively performs a pre-order traversal of the subtree rooted at the given node.
     *
     * This method is used internally to traverse the binary tree in pre-order fashion
     * starting from the given node. For each node visited, the provided function is called
     * with the node's value.
     *
     * @param node The root of the subtree to traverse.
     * @param visit A function to apply to each node's value during traversal.
     */
    void preorderRec(TreeNode<T>* node, std::function<void(const T&)> visit) const;

    /**
     * @brief Recursively performs a post-order traversal of the subtree rooted at the given node.
     *
     * This method is used internally to traverse the binary tree in post-order fashion
     * starting from the given node. For each node visited, the provided function is called
     * with the node's value.
     *
     * @param node The root of the subtree to traverse.
     * @param visit A function to apply to each node's value during traversal.
     */
    void postorderRec(TreeNode<T>* node, std::function<void(const T&)> visit) const;

    /**
     * @brief Recursively builds a binary tree from a sequence of values.
     *
     * This method is used internally to construct a binary tree by recursively
     * processing a sequence of values. The sequence is assumed to be provided
     * through iterators or pointers, and the method constructs the tree in a
     * manner defined by the `isChar` flag, which determines if the sequence is
     * composed of characters or other data types.
     *
     * @param node A pointer to the current node where the subtree will be attached.
     * @param begin An iterator or pointer to the beginning of the sequence of values.
     * @param end An iterator or pointer to the end of the sequence of values.
     * @tparam D pointer or iterator type
     *
     * This function processes the sequence of values starting from `begin` up to `end`, and
     * constructs the binary tree recursively. For each value, it creates a node and attaches
     * it to the subtree rooted at `node`. If `isChar` is `true`, values are interpreted as characters;
     * otherwise, they are interpreted as a different data type as specified by `T`.
     */
    template<typename D>
    void buildRec(TreeNode<T>*& node, D& begin, D& end);

    /**
     * @brief Recursively copies nodes from a source subtree to a destination subtree.
     *
     * This method is used internally to perform a deep copy of the binary tree. It copies
     * nodes from the subtree rooted at `src` and creates corresponding nodes in the subtree
     * rooted at `dst`. The function recursively copies the entire structure of the source subtree,
     * including all left and right children.
     *
     * @param src The root of the subtree to be copied. This is the source subtree from which
     *        nodes are copied.
     * @param dst The root of the subtree where nodes will be copied to. This is the destination
     *        subtree where new nodes will be created.
     *
     * This function does not create or delete the `dst` node itself but assumes that `dst` is
     * already a valid node. The function will recursively copy the left and right subtrees of `src`
     * and attach them to the corresponding children of `dst`.
     */
    void copyRec(TreeNode<T>*& src, TreeNode<T>*& dst);
public:
    /**
     * @brief Default constructor.
     */
    binary_tree();

    /**
     * @brief Constructor initializing the tree with a single value.
     * @param value The value to initialize the root of the tree.
     */
    explicit binary_tree(const T& value);

    /**
     * @brief Constructor initializing the tree from an array of values.
     *
     * Initializes the binary tree from a given array of values. The end of the array
     * is denoted by '#' for 'char' type or 'nullptr' for class pointers.
     *
     * @param initialize_list Pointer to an array of values.
     * @param size The number of elements in the array.
     */
    binary_tree(const T* initialize_list, const size_t& size);

    /**
     * @brief Constructor initializing the tree from a linked list.
     *
     * Initializes the binary tree from a given linked list. The list can be used to
     * populate the tree with elements.
     *
     * @param initialize_list The linked list containing values to initialize the tree.
     */
    explicit binary_tree(const linked_list<T>& initialize_list);

    /**
     * @brief Copy constructor.
     *
     * Creates a new binary tree as a copy of the provided binary tree. This involves
     * recursively copying each node from the other tree to ensure a deep copy.
     *
     * Complexity: O(n), where n is the number of nodes in the other tree.
     *
     * @param other The binary tree to copy.
     */
    binary_tree(const binary_tree& other);

    /**
     * @brief Move constructor.
     *
     * Moves the contents of another binary tree into this one. This involves transferring
     * ownership of the nodes from the other tree to this tree.
     *
     * @param other The binary tree to move from.
     */
    binary_tree(binary_tree&& other) noexcept;

    /**
     * @brief Destructor.
     *
     * Cleans up the binary tree by recursively destroying all its nodes to prevent memory leaks.
     */
    ~binary_tree();

    /**
     * @brief Copy assignment operator.
     *
     * Assigns the contents of another binary tree to this one. This involves copying
     * each node from the other tree to this tree, ensuring a deep copy.
     *
     * Complexity: O(n), where n is the number of nodes in the other tree.
     *
     * @param other The binary tree to copy.
     * @return Reference to this binary tree.
     */
    binary_tree& operator=(const binary_tree& other);

    /**
     * @brief Move assignment operator.
     *
     * Moves the contents of another binary tree into this one. This involves transferring
     * ownership of the nodes from the other tree to this tree.
     *
     * @param other The binary tree to move from.
     * @return Reference to this binary tree.
     */
    binary_tree& operator=(binary_tree&& other) noexcept;

    /**
     * @brief Equality operator.
     *
     * Compares this binary tree to another to check if they are equal. Trees are considered
     * equal if they have the same structure and contain the same values.
     *
     * @param other The binary tree to compare to.
     * @return True if the trees are equal, false otherwise.
     */
    bool operator==(const binary_tree& other) const;

    /**
     * @brief Inserts a value into the binary tree.
     *
     * Adds a new value to the binary tree. The position of the new node is determined
     * by the binary tree's insertion policy.
     *
     * @param value The value to insert into the tree.
     */
    void insert(const T& value);

    /**
     * @brief Searches for a value in the binary tree.
     *
     * Checks if a value exists in the binary tree.
     *
     * @param value The value to search for.
     * @return True if the value is found, false otherwise.
     */
    bool search(const T& value) const;

    /**
     * @brief Performs an in-order traversal of the binary tree.
     *
     * Visits all nodes in the tree using in-order traversal and applies the provided
     * function to each node's value.
     *
     * @param visit A function to apply to each node's value during traversal.
     */
    void inorder(std::function<void(const T&)> visit) const;

    /**
     * @brief Performs a pre-order traversal of the binary tree.
     *
     * Visits all nodes in the tree using pre-order traversal and applies the provided
     * function to each node's value.
     *
     * @param visit A function to apply to each node's value during traversal.
     */
    void preorder(std::function<void(const T&)> visit) const;

    /**
     * @brief Performs a post-order traversal of the binary tree.
     *
     * Visits all nodes in the tree using post-order traversal and applies the provided
     * function to each node's value.
     *
     * @param visit A function to apply to each node's value during traversal.
     */
    void postorder(std::function<void(const T&)> visit) const;

    /**
     * @brief Clears the entire binary tree by recursively destroying all its nodes.
     *
     * This method is used to delete all nodes in the binary tree, effectively freeing
     * up the memory used by the tree. It initiates the recursive destruction of all nodes
     * starting from the root of the tree, ensuring that no memory leaks occur.
     *
     * This function calls an internal helper function (e.g., `destroyRec`) that performs
     * the actual recursive deletion of nodes.
     *
     * After this method completes, the binary tree is empty and the memory previously
     * allocated for the nodes is released. The tree structure itself is no longer valid.
     */
    void clear();
};

#endif //BINARY_TREE_H
