//
// Created by Eden_ on 2024/9/9.
//

#ifndef BASIC_BINARY_TREE_H
#define BASIC_BINARY_TREE_H
#include <functional>
#include "iterator.h"
#include "linked_list.h"

namespace TreeData
{
    enum traversal
    {
     PREORDER,
     INORDER,
     POSTORDER
    };
}

using namespace TreeData;

/**
 * @brief A template class for binary trees.
 *
 * This class implements a binary tree with basic functionalities such as insertion,
 * deletion, traversal, and search. It also includes iterators for traversing the tree
 * in a bidirectional manner.
 *
 * @tparam T The type of the data stored in the tree nodes.
 * @tparam D Label type for extend
 */
template <typename T, typename D = void>
class binary_tree // TODO,Add level traversal
{
    template <typename U, typename V>
    friend class binary_tree;
protected:
    /**
     * @brief A node in the binary tree.
     *
     * This structure represents a node in the binary tree, storing data and pointers to
     * its left and right children, as well as its parent.
     */
    struct tree_node
    {
        T data; ///< The data stored in the node.
        tree_node *left = nullptr; ///< Pointer to the left child node.
        tree_node *right = nullptr; ///< Pointer to the right child node.
        tree_node *parent = nullptr; ///< Pointer to the parent node.
        std::conditional_t<!std::is_void_v<D>, D, char> label; ///< label of the node only use
    };

    tree_node *root; ///< Pointer to the root node of the tree.

    /**
     * @brief Recursively searches for a value in the binary tree.
     *
     * @param node The node to start the search from.
     * @param value The value to search for.
     * @return Node pointer if the value is found, nullptr otherwise.
     */
    virtual tree_node *searchRec(tree_node *node, const T &value) const;

public:
    /**
     * @brief Default constructor.
     *
     * Creates an empty binary tree.
     */
    binary_tree();

    /**
     * @brief Constructor with a single value.
     *
     * Initializes the tree with a single node containing the specified value.
     *
     * @param value The value to initialize the root node with.
     */
    explicit binary_tree(const T &value);

    /**
     * @brief Constructor with an array of values.
     *
     * Initializes the tree with values from a preorder array.
     *
     * @param initialize_list Pointer to the array of values.
     * @param size The number of elements in the array.
     * @param label Ending label.
     */
    binary_tree(const T *initialize_list, const size_t &size, const T &label);

    /**
     * @brief Constructor with a linked list.
     *
     * Initializes the tree with values from a preorder linked list.
     *
     * @param initialize_list The linked list of values.
     * @param label Ending label.
     */
    explicit binary_tree(const linked_list<T> &initialize_list, const T &label);

    /**
     * @brief Copy constructor.
     *
     * Creates a new binary tree as a copy of the given tree.
     *
     * @param other The binary tree to copy.
     */
    binary_tree(const binary_tree &other);

    /**
     * @brief Move constructor.
     *
     * Transfers ownership of the resources from the given tree to this new tree.
     *
     * @param other The binary tree to move from.
     */
    binary_tree(binary_tree &&other) noexcept;

    /**
     * @brief Destructor.
     *
     * Releases all resources held by the tree.
     */
    virtual ~binary_tree();

    /**
     * @brief Copy assignment operator.
     *
     * Assigns the contents of another binary tree to this one. This involves:
     * 1. Clearing the current tree to release any resources.
     * 2. Performing a deep copy of each node from the `other` tree to this tree.
     * 3. Ensuring that all nodes are correctly copied to maintain the structure and data of the tree.
     *
     * Complexity: O(n), where n is the number of nodes in the other tree.
     *
     * @param other The binary tree to copy from.
     * @return Reference to this binary tree.
     */
    binary_tree &operator=(const binary_tree &other);

    /**
     * @brief Move assignment operator.
     *
     * Transfers ownership of the resources from the given tree to this tree.
     *
     * @param other The binary tree to move from.
     * @return Reference to this binary tree.
     */
    binary_tree &operator=(binary_tree &&other) noexcept;

    /**
     * @brief Equality operator.
     *
     * Compares this tree with another tree for equality.
     *
     * @param other The binary tree to compare with.
     * @return True if the trees are equal, false otherwise.
     */
    bool operator==(const binary_tree &other) const;

    /**
     * @brief Searches for a value in the binary tree.
     *
     * @param value The value to search for.
     * @return True if the value is found, false otherwise.
     */
    virtual bool search(const T &value) const;

    /**
     * @brief Performs an in-order traversal of the tree.
     *
     * @param doSomething A function to apply to each node's data during traversal.
     */
    void inorder(std::function<void(const T &)> doSomething = [](const T &) {}) const;

    /**
     * @brief Performs a pre-order traversal of the tree.
     *
     * @param doSomething A function to apply to each node's data during traversal.
     */
    void preorder(std::function<void(const T &)> doSomething = [](const T &) {}) const;

    /**
     * @brief Performs a post-order traversal of the tree.
     *
     * @param doSomething A function to apply to each node's data during traversal.
     */
    void postorder(std::function<void(const T &)> doSomething = [](const T &) {}) const;

    /**
     * @brief Clears the tree, releasing all resources.
     *
     * @param doSomething A function to apply to each node's data during traversal.
     */
    void clear(std::function<void(const T &)> doSomething = [](const T &) {});

    /**
     * @brief Checks if the tree is empty.
     *
     * @return True if the tree is empty, false otherwise.
     */
    [[nodiscard]] virtual bool is_empty() const;

    /**
     * @brief Gets the depth of the tree.
     *
     * @return The depth of the tree.
     */
    [[nodiscard]] virtual size_t get_depth() const;

    /**
     * @brief Gets the number of nodes in the tree.
     *
     * @return The size of the tree.
     */
    [[nodiscard]] virtual size_t get_size() const;

    /**
     * transform binary tree to string
     * @param type traversal type
     * @return traversal string
     */
    [[nodiscard]] std::string to_string(traversal type = PREORDER) const;

protected:
    /**
     * change data type of the tree to another type
     * @tparam NewType new data type
     * @param doSomething type changing function
     * @return new binary tree.
     */
    template <typename NewType>
    binary_tree<NewType, D> change_type(std::function<NewType(const T &)> doSomething) const;

private:
    /**
     * @brief Constructor with root.
     *
     * Initializes the tree with root node.
     *
     * @param root The root of binary tree.
     */
    explicit binary_tree(tree_node &root);

    /**
     * @brief Recursively destroys the tree.
     *
     * @param node The node to start destruction from.
     * @param doSomething A function to apply to each node's data during destruction.
     */
    static void destroyRec(tree_node *node, std::function<void(const T &)> doSomething = [](const T &) {});

    /**
     * @brief Recursively performs an in-order traversal.
     *
     * @param node The node to start traversal from.
     * @param doSomething A function to apply to each node's data during traversal.
     */
    static void inorderRec(tree_node *node, std::function<void(const T &)> doSomething = [](const T &) {});

    /**
     * @brief Recursively performs a pre-order traversal.
     *
     * @param node The node to start traversal from.
     * @param doSomething A function to apply to each node's data during traversal.
     */
    static void preorderRec(tree_node *node, std::function<void(const T &)> doSomething = [](const T &) {});

    /**
     * @brief Recursively performs a post-order traversal.
     *
     * @param node The node to start traversal from.
     * @param doSomething A function to apply to each node's data during traversal.
     */
    static void postorderRec(tree_node *node, std::function<void(const T &)> doSomething = [](const T &) {});

    /**
     * @brief Recursively builds the tree with an inorder list with end_label.
     * @tparam I pointer or iterator type
     * @param parent parent node pointer
     * @param node root node to build
     * @param begin start pointer or iterator
     * @param end end pointer or iterator
     * @param label end label, witch means it is nullptr
     */
    template <typename I>
    static void buildRec(tree_node *parent, tree_node *&node, I &begin, I &end, const T &label);

    /**
     * @brief Recursively compares this tree with another tree for equality.
     *
     * @param node The node to start comparison from.
     * @param other_node Other node to compare with.
     * @return Are they equal or not?
     */
    static bool equalRec(tree_node *node, tree_node *other_node);

    /**
     * @brief Recursively counts the number of nodes in the tree.
     *
     * @param node The node to start counting from.
     * @return The number of nodes in the subtree rooted at the given node.
     */
    static size_t sizeRec(tree_node *node);

    /**
     * @brief Recursively calculates the depth of the tree.
     *
     * @param node The node to start depth calculation from.
     * @return The depth of the subtree rooted at the given node.
     */
    static size_t depthRec(tree_node *node);

    /**
     * @brief Recursively copies nodes from another tree.
     *
     * @param parent Parent of the node,only for recursive.
     * @param node The node to start copying from.
     * @param other_node The tree to be copied.
     */
    static void copyRec(tree_node *parent, tree_node *&node, const tree_node *other_node);

    /**
     * Constructor to copies nodes and change their type.
     *
     * @tparam OldType Old data type.
     * @param other_node The tree to be copied.
     * @param doSomething type changing function
     */
    template <typename OldType>
    binary_tree(typename binary_tree<OldType, D>::tree_node *other_node,
                std::function<T(const OldType &)> doSomething);

    /**
     * @brief Recursively copies nodes from another tree and change their type.
     *
     * @tparam OldType Old data type.
     * @param parent Parent of the node,only for recursive.
     * @param node The node to start copying from.
     * @param other_node The tree to be copied.
     * @param doSomething type changing function
     */
    template <typename OldType>
    static void change_typeRec(tree_node *parent, tree_node *&node,
                               typename binary_tree<OldType, D>::tree_node *other_node,
                               std::function<T(const OldType &)> doSomething);

    /**
     * Get the first node of subtree in specific traversal type
     * @param node tree node as the root of the subtree
     * @param type traversal type
     * @return first node of the subtree of node by given traversal type
     */
    static tree_node *get_first(tree_node *node, traversal type = PREORDER);

    /**
     * Get the first node of subtree in specific traversal type
     * @param node tree node as the root of the subtree
     * @param type traversal type
     * @return first node of the subtree of node by given traversal type
     */
    static tree_node *get_last(tree_node *node, traversal type = PREORDER);

public:
    friend class Iterator;
    /**
     * @brief Bidirectional iterator for the binary tree.
     *
     * This iterator provides bidirectional traversal capabilities for the binary tree.
     */
    class Iterator
    {
    public:
        static constexpr iterator::type type = iterator::BIDIRECTIONAL;

        /**
         * @brief copy constructor
         * Complexity:O(1)
         * @param other other iterator
         */
        Iterator(const Iterator& other);

        /**
         * @brief Checks if the iterator has a left child.
         *
         * @return True if the iterator has a left child, false otherwise.
         */
        [[nodiscard]] bool has_left() const;

        /**
         * @brief Checks if the iterator has a right child.
         *
         * @return True if the iterator has a right child, false otherwise.
         */
        [[nodiscard]] bool has_right() const;

        /**
         * @brief Gets an iterator to the left child.
         *
         * @return An iterator to the left child.
         */
        Iterator get_left() const;

        /**
         * @brief Gets an iterator to the right child.
         *
         * @return An iterator to the right child.
         */
        Iterator get_right() const;

        /**
         * @brief Gets an iterator to the parent.
         *
         * @return An iterator to the parent.
         */
        Iterator get_parent() const;

        /**
         * @brief Moves the iterator to the left child.
         *
         * @return self
         */
        Iterator &left();

        /**
         * @brief Moves the iterator to the right child.
         *
         * @return self
         */
        Iterator &right();

        /**
         * @brief Moves the iterator to the parent node.
         *
         * @return self
         */
        Iterator &parent();

        /**
         * @brief Sets the value of the left child.
         *
         * @param value The new value for the left child.
         */
        void set_left(const T &value) const;

        /**
         * @brief Sets the value of the right child.
         *
         * @param value The new value for the right child.
         */
        void set_right(const T &value) const;

        /**
         * @brief Cuts the subtree rooted at the current node.
         *
         * @return The binary tree with the subtree removed.
         */
        binary_tree cut_subtree();

        /**
         * @brief Copies the subtree rooted at the current node.
         *
         * @return The binary tree with the copied subtree.
         */
        binary_tree copy_subtree() const;

        /**
         * @brief Dereferences the iterator to access the node's data.
         *
         * @return Reference to the data in the current node.
         */
        T &operator*() const;

        /**
         * @brief Accesses the node's data using arrow operator.
         *
         * @return Pointer to the data in the current node.
         */
        T *operator->() const;

        /**
         * @brief copy operator
         * Complexity:O(1)
         * @param other other iterator
         * @return self
         */
        Iterator & operator=(const Iterator& other);

        /**
         * Equal operator
         * @param other other iterator
         * @return true if their currents are equal else false
         */
        bool operator==(const Iterator &other) const { return this->current == other.current; }

        /**
         * Not Equal operator
         * @param other other iterator
         * @return true if their currents are not equal else false
         */
        bool operator!=(const Iterator &other) const { return this->current != other.current; }

        /**
         * @brief Advances the iterator to the next node in the traversal.
         *
         * @return Reference to this iterator.
         */
        Iterator &operator++();

        /**
         * @brief Moves the iterator to the previous node in the traversal.
         *
         * @return Reference to this iterator.
         */
        Iterator &operator--();

    private:
        friend class binary_tree;

        const binary_tree &outer; /** reference of linked list */
        const traversal it_type; /** iterator traversal type*/
        tree_node *current; /** current pointer*/

        /**
         * @brief Gets the node pointed to by the iterator.
         *
         * @return Pointer to the current node.
         */
        tree_node *get_node() const;

    protected:
        /**
         * @brief Constructor only can use by binary tree
         * Complexity: O(1)
         * @param node current node
         * @param outer reference of binary tree
         * @param type iterator traversal type
         */
        explicit Iterator(tree_node *node, const binary_tree &outer, const traversal type = PREORDER) :
            outer(outer), it_type(type)
        {
            this->current = node;
        }
    };

    friend class ConstIterator;
    /**
     * @brief Const bidirectional iterator for the binary tree.
     *
     * This iterator provides bidirectional traversal capabilities for the binary tree,
     * with read-only access to the data.
     */
    class ConstIterator
    {
    public:
        static constexpr iterator::type type = iterator::BIDIRECTIONAL;

        /**
         * @brief copy constructor
         * Complexity:O(1)
         * @param other other iterator
         */
        ConstIterator(const ConstIterator& other);

        /**
         * @brief copy constructor
         * Complexity:O(1)
         * @param other other iterator
         */
        explicit ConstIterator(const Iterator& other);

        /**
         * @brief Checks if the iterator has a left child.
         *
         * @return True if the iterator has a left child, false otherwise.
         */
        [[nodiscard]] bool has_left() const;

        /**
         * @brief Checks if the iterator has a right child.
         *
         * @return True if the iterator has a right child, false otherwise.
         */
        [[nodiscard]] bool has_right() const;

        /**
         * @brief Gets a const iterator to the left child.
         *
         * @return A const iterator to the left child.
         */
        ConstIterator get_left() const;

        /**
         * @brief Gets a const iterator to the right child.
         *
         * @return A const iterator to the right child.
         */
        ConstIterator get_right() const;

        /**
         * @brief Gets a const iterator to the parent.
         *
         * @return A const iterator to the parent.
         */
        ConstIterator get_parent() const;

        /**
         * @brief Moves the iterator to the left child.
         */
        ConstIterator &left();

        /**
         * @brief Moves the iterator to the right child.
         */
        ConstIterator &right();

        /**
         * @brief Moves the iterator to the parent node.
         */
        ConstIterator &parent();

        /**
         * @brief Sets the value of the left child.
         *
         * @param value The new value for the left child.
         */
        void set_left(const T &value) const;

        /**
         * @brief Sets the value of the right child.
         *
         * @param value The new value for the right child.
         */
        void set_right(const T &value) const;

        /**
         * @brief Copies the subtree rooted at the current node.
         *
         * @return The binary tree with the copied subtree.
         */
        binary_tree copy_subtree() const;

        /**
         * @brief Dereferences the iterator to access the node's data.
         *
         * @return Const reference to the data in the current node.
         */
        const T &operator*() const;

        /**
         * @brief Accesses the node's data using arrow operator.
         *
         * @return Const pointer to the data in the current node.
         */
        const T *operator->() const;

        /**
         * @brief copy operator
         * Complexity:O(1)
         * @param other other iterator
         * @return self
         */
        ConstIterator & operator=(const ConstIterator& other);

        /**
         * @brief copy operator
         * Complexity:O(1)
         * @param other other iterator
         * @return self
         */
        ConstIterator & operator=(const Iterator& other);

        /**
         * Equal operator
         * @param other other const iterator
         * @return true if their currents are equal else false
         */
        bool operator==(const ConstIterator &other) const { return this->current == other.current; }

        /**
         * Not Equal operator
         * @param other other const iterator
         * @return true if their currents are not equal else false
         */
        bool operator!=(const ConstIterator &other) const { return this->current != other.current; }

        /**
         * @brief Advances the iterator to the next node in the traversal.
         *
         * @return Reference to this const iterator.
         */
        ConstIterator &operator++();

        /**
         * @brief Moves the iterator to the previous node in the traversal.
         *
         * @return Reference to this const iterator.
         */
        ConstIterator &operator--();

    private:
        friend class binary_tree;

        const binary_tree &outer; /** reference of linked list */
        const traversal it_type; /** iterator traversal type*/
        const tree_node *current; /** current pointer*/

        /**
         * @brief Gets the node pointed to by the iterator.
         *
         * @return Pointer to the current node.
         */
        tree_node *get_node() const;

    protected:
        /**
         * Constructor only can use by binary tree
         * Complexity: O(1)
         * @param node current node
         * @param outer reference of binary tree
         * @param type traversal type
         */
        explicit ConstIterator(const tree_node *node, const binary_tree &outer, const traversal type = PREORDER) :
            outer(outer), it_type(type)
        {
            current = node;
        }
    };

    /**
     * get begin iterator,which is pointing to root
     * Complexity: O(1)
     *
     * @param type traversal type
     * @return begin iterator
     */
    Iterator begin(traversal type = PREORDER);

    /**
     * get end iterator,which is pointing to null
     * Complexity: O(1)
     *
     * @param type traversal type
     * @return end iterator
     */
    Iterator end(traversal type = PREORDER);

    /**
     * get const begin iterator,which is pointing to root
     * Complexity: O(1)
     *
     * @param type traversal type
     * @return const begin iterator
     */
    // ReSharper disable once CppHiddenFunction
    ConstIterator begin(traversal type = PREORDER) const;

    /**
     * get const end iterator,which is pointing to null
     * Complexity: O(1)
     *
     * @param type traversal type
     * @return const end iterator
     */
    // ReSharper disable once CppHiddenFunction
    ConstIterator end(traversal type = PREORDER) const;
};

#include "binary_tree.tpp"

#endif //BASIC_BINARY_TREE_H
