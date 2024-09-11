//
// Created by Eden_ on 2024/9/6.
//

#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include "iterator.h"
#include "object.h"

/**
 * Linked List
 * @tparam T Type of the data
 */
template <typename T>
class linked_list : public object// TODO,add sublist()
{
public:

    /**
     * Simple constructor, Init it as an empty linked list
     * Complexity: O(1)
     */
    linked_list();

    /**
     * copy Constructor from another linked_list
     * Complexity: O(n)
     * @param other another Linked List
     */
    linked_list(const linked_list &other);

    /**
     * move Constructor from another linked_list
     * Complexity: O(1)
     * @param other another Linked List
     */
    linked_list(linked_list &&other) noexcept;

    /**
     * constructor copy from an array of T
     * Complexity: O(n)
     * @param other an array head of T
     * @param size array size
     */
    linked_list(T *other, size_t size);

    /**
     * destructor, we free space there
     * Complexity: O(n)
     */
    ~linked_list() override;

    /**
     * copy = operator
     * Complexity: O(n)
     */
    linked_list &operator=(const linked_list &other);

    /**
     * move = operator
     * Complexity: O(n)
     * @param other other linked_list
     * @return self
     */
    linked_list &operator=(linked_list &&other) noexcept;

    /**
     * compare == operator
     * Complexity: O(n)
     * @param other other linked_list
     * @return is it equals or not
     */
    bool operator==(const linked_list &other) const;

    /**
     * add value to the tail of linked list
     * Complexity: O(1)
     * @param value adding value
     */
    void add(T value);

    /**
     * add value to the given index of linked list
     * Complexity: O(n)
     * @param index adding index
     * @param value adding value
     */
    void add(size_t index, T value);

    /**
     * get data by giving index, you can rewrite the value
     * Complexity: O(n)
     * @param index getting index
     * @return data at given index,you can change it by overwrite operator =
     */
    T &get(size_t index);

    /**
     * get data by giving index, you can not rewrite the value
     * Complexity: O(n)
     * @param index getting index
     * @return data at given index,you can change it by overwrite operator =
     */
    const T &get(size_t index) const;

    /**
     * set data in given index to input value
     * Complexity: O(n)
     * @param index setting index
     * @param value setting value
     */
    void set(size_t index, T value);

    /**
     * remove node at given index
     * Complexity: O(n)
     * @param index remove index
     */
    void remove(size_t index);

    /**
     * remove all data equals to given value
     * Complexity: O(n)
     * @param value remove value
     */
    void remove(T value);

    /**
     * does linked_list contain value
     * Complexity: O(n)
     * @param value value to find
     * @return is it contained or not
     */
    [[nodiscard]] bool contains(T value) const;

    /**
     * get size of linked list
     * Complexity: O(1)
     * @return size of Linked list
     */
    [[nodiscard]] size_t get_size() const;

    /**
     * check is linked_list empty
     * Complexity: O(1)
     * @return is empty or not
     */
    [[nodiscard]] bool is_empty() const;

    /**
     * add a node at head of the linked_list
     * Complexity: O(1)
     * @param value adding value
     */
    void add_first(T value);

    /**
     * add a node at tail of the linked_list
     * Complexity: O(1)
     * @param value adding value
     */
    void add_last(T value);

    /**
     * remove a node at head
     * Complexity: O(1)
     */
    void remove_first();

    /**
     * remove a node at tail
     * Complexity: O(1)
     */
    void remove_last();

    /**
     * peek first object data, you can rewrite the value
     * Complexity: O(1)
     * @return first data object
     */
    T &get_first();

    /**
     * peek first object data, you can not rewrite the value
     * Complexity: O(1)
     * @return first data object
     */
    const T &get_first() const;

    /**
     * peek last object data, you can rewrite the value
     * Complexity: O(1)
     * @return last data object
     */
    T &get_last();

    /**
     * peek last object data, you can not rewrite the value
     * Complexity: O(1)
     * @return last data object
     */
    const T &get_last() const;

    /**
     * get copy of first data and remove it from linked_list
     * @return first data
     */
    T pop_first();

    /**
     * get copy of first data and remove it from linked_list
     * Complexity: O(1)
     * @return first data
     */
    T pop_last();

    /**
     * change linked list to string style
     * Only use the function if DataType is int,float,or string
     * Complexity: O(n)
     * @return (Maybe Json style)string of Linked list
     */
    [[nodiscard]] std::string to_string() const override;

    /**
     * change string style array to linked_list
     * Only use the function if DataType is int,float,or string
     * Complexity: O(n)
     * @param str (Maybe Json style)string of array of string
     * @return linked_list Object of string
     */
    [[nodiscard]] static linked_list<T> from_string(const std::string &str);

    /**
     * clear all data
     * Complexity: O(n)
     */
    void clear();

private:
    /**
     * Linked list node
     */
    class Node
    {
    public:
        T data;         /** data of the node */
        Node *next;     /** next node pointer */
        Node *previous; /** previous node pointer */

        /**
         * constructor of all coefficients
         * @param data data inside the node
         * @param next next Node pointer
         * @param previous previous Node pointer
         */
        Node(T data, Node *next, Node *previous) : data(data), next(next), previous(previous) {}

        /**
         * constructor of only data
         * @param data data inside the node
         */
        explicit Node(T data) : data(data)
        {
            next = nullptr;
            previous = nullptr;
        }

        /**
         * constructor of only pointer
         * @param next next Node pointer
         * @param previous previous Node pointer
         */
        Node(Node *next, Node *previous) : next(next), previous(previous) {}

        /**
         * Reset pointer to nullptr
         */
        ~Node()
        {
            next = nullptr;
            previous = nullptr;
        }
    };

    Node *head_node = new Node(nullptr,nullptr); /** Linked List Head */
    Node *tail_node = new Node(nullptr,nullptr); /** Linked List Tail */
    size_t size = 0;                             /** Linked List Length */

    /**
     * This function will return the Node has input index in previous linked_list.
     * Complexity: O(n)
     * @param index finding index
     * @param include_tail can it search for tail_node?
     * @return next node
     */
    [[nodiscard]] Node * get_node_pointer(size_t index, bool include_tail) const;

public:

    friend class Iterator;
    /**
     * Linked List iterator, for not const linked list
     */
    class Iterator
    {
    public:
        static constexpr iterator::type type=iterator::BIDIRECTIONAL;

        /**
         * This method allows you to access and modify the value at the current position of the iterator.
         * Complexity: O(1)
         * @return A reference to the value pointed to by the iterator
         */
        T& operator*() const;

        /**
         * This method provides access to the value pointed to by the iterator, similar to dereferencing the iterator.
         * Complexity: O(1)
         * @return A pointer to the value pointed to by the iterator.
         */
        T* operator->() const;

        /**
         * Equal operator
         * Complexity: O(1)
         * @param other other iterator
         * @return true if their currents are equal else false
         */
        bool operator==(const Iterator& other) const
        {
         return this->current == other.current;
        }

        /**
         * Not Equal operator
         * Complexity: O(1)
         * @param other other iterator
         * @return true if their currents are not equal else false
         */
        bool operator!=(const Iterator& other) const
        {
         return this->current != other.current;
        }

        /**
         * This is the pre-increment operator. It advances the iterator by one position and returns a reference to the modified iterator itself.
         * Complexity: O(1)
         * @return A reference to the updated iterator after it has been incremented.
         */
        Iterator& operator++();

        /**
         * This method moves the iterator backward by one position (pre-decrement) and returns the iterator itself.
         * Complexity: O(1)
         * @return  A reference to the updated iterator after it has been decremented.
         */
        Iterator& operator--();

        /**
         * destructor
         */
        ~Iterator();
    private:
        friend class linked_list;

        const linked_list& outer; /** reference of linked list */
        Node * current;     /** current pointer*/

        /**
         * Constructor only can use by LinkedList
         * Complexity: O(1)
         * @param node current node
         * @param outer reference of linked list
         */
        explicit Iterator(Node *node,const linked_list& outer): outer(outer)
        {
            this->current = node;
        }
    };

    friend class ConstIterator;
    /**
     * Linked List iterator, for const linked list
     */
    class ConstIterator
    {
    public:

        /**
         * This method allows you to access and modify the value at the current position of the iterator.
         * Complexity: O(1)
         * @return A reference to the value pointed to by the iterator
         */
        const T& operator*() const;

        /**
         * This method provides access to the value pointed to by the iterator, similar to dereferencing the iterator.
         * Complexity: O(1)
         * @return A pointer to the value pointed to by the iterator.
         */
        const T* operator->() const;

        /**
         * Equal operator
         * Complexity: O(1)
         * @param other other const iterator
         * @return true if their currents are equal else false
         */
        bool operator==(const ConstIterator& other) const
        {
         return this->current == other.current;
        }

        /**
         * Not Equal operator
         * Complexity: O(1)
         * @param other other const iterator
         * @return true if their currents are not equal else false
         */
        bool operator!=(const ConstIterator& other) const
        {
         return this->current != other.current;
        }

        /**
         * This is the pre-increment operator. It advances the iterator by one position and returns a reference to the modified iterator itself.
         * Complexity: O(1)
         * @return A reference to the updated iterator after it has been incremented.
         */
        ConstIterator& operator++();

        /**
         * This method moves the iterator backward by one position (pre-decrement) and returns the iterator itself.
         * Complexity: O(1)
         * @return  A reference to the updated iterator after it has been decremented.
         */
        ConstIterator& operator--();

        /**
         * destructor
         * Complexity: O(1)
         */
        ~ConstIterator();
    private:

        friend class linked_list;

        const linked_list& outer;     /** reference of linked list */
        const Node * current;         /** current pointer*/

        /**
         * Constructor only can use by LinkedList
         * Complexity: O(1)
         * @param node current node
         * @param outer reference of linked list
         */
        explicit ConstIterator(Node *node,const linked_list& outer): outer(outer)
        {
            this->current = node;
        }
    };

    /**
     * get begin iterator,which is pointing to index 0
     * Complexity: O(1)
     * @return begin iterator
     */
    Iterator begin();

    /**
     * get end iterator,which is pointing to index size
     * Complexity: O(1)
     * @return end iterator
     */
    Iterator end();

    /**
     * get const begin iterator,which is pointing to index 0
     * Complexity: O(1)
     * @return const begin iterator
     */
    ConstIterator begin() const;

    /**
     * get const end iterator,which is pointing to index size
     * Complexity: O(1)
     * @return const end iterator
     */
    ConstIterator end() const;
};


#include "linked_list.tpp"

#endif //LINKED_LIST_H
