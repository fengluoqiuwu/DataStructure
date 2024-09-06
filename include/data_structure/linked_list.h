//
// Created by Eden_ on 2024/9/6.
//

#ifndef LINKED_LIST_H
#define LINKED_LIST_H
#include "object.h"

template <typename T>
class LinkedList : public object
{
public:
    /**
     * Simple constructor, Init it as an empty linked list
     */
    LinkedList();

    /**
     * copy Constructor from another LinkedList
     * @param other another Linked List
     */
    LinkedList(const LinkedList &other);

    /**
     * move Constructor from another LinkedList
     * @param other another Linked List
     */
    LinkedList(LinkedList &&other) noexcept;

    /**
     * constructor copy from an array of T
     * @param other an array head of T
     * @param size array size
     */
    LinkedList(T *other, size_t size);

    /**
     * destructor, we free space there
     */
    ~LinkedList() override;

    /**
     * copy = operator
     */
    LinkedList &operator=(const LinkedList &other);

    /**
     * move = operator
     * @param other other LinkedList
     * @return self
     */
    LinkedList &operator=(LinkedList &&other) noexcept;

    /**
     * compare == operator
     * @param other other LinkedList
     * @return is it equals or not
     */
    bool operator==(const LinkedList &other);

    /**
     * add value to the tail of linked list
     * @param value adding value
     */
    void add(T value);

    /**
     * add value to the given index of linked list
     * @param index adding index
     * @param value adding value
     */
    void add(size_t index, T value);

    /**
     * get data by giving index
     * @param index getting index
     * @return data at given index,you can change it by overwrite operator =
     */
    T &get(size_t index) const;

    /**
     * set data in given index to input value
     * @param index setting index
     * @param value setting value
     */
    void set(size_t index, T value);

    /**
     * remove node at given index
     * @param index remove index
     */
    void remove(size_t index);

    /**
     * remove all data equals to given value
     * @param value remove value
     */
    void remove(T value);

    /**
     * does LinkedList contain value
     * @param value value to find
     * @return is it contained or not
     */
    [[nodiscard]] bool contains(T value) const;

    /**
     * get size of linked list
     * @return size of Linked list
     */
    [[nodiscard]] size_t get_size() const;

    /**
     * check is LinkedList empty
     * @return is empty or not
     */
    [[nodiscard]] bool is_empty() const;

    /**
     * add a node at head of the LinkedList
     * @param value adding value
     */
    void add_first(T value);

    /**
     * add a node at tail of the LinkedList
     * @param value adding value
     */
    void add_last(T value);

    /**
     * remove a node at head
     */
    void remove_first();

    /**
     * remove a node at tail
     */
    void remove_last();

    /**
     * peek first object
     * @return first data object
     */
    T &peek_first() const;

    /**
     * peek last object
     * @return last data object
     */
    T &peek_last() const;

    /**
     * get copy of first data and remove it from LinkedList
     * @return first data
     */
    T pop_first();

    /**
     * get copy of first data and remove it from LinkedList
     * @return first data
     */
    T pop_last();

    /**
     * change linked list to string style
     * Only use the function if DataType is int,float,double,or string
     * @return (Maybe Json style)string of Linked list
     */
    [[nodiscard]] std::string to_string() const override;

    /**
     * change string style array to LinkedList
     * Only use the function if DataType is int,float,double,or string
     * @param str (Maybe Json style)string of array of string
     * @return LinkedList Object of string
     */
    [[nodiscard]] static LinkedList<T> form_string(const std::string &str);

private:
    /**
     * Linked list node
     * @tparam D DataType
     */
    template <typename D>
    class Node
    {
    public:
        /**
         * data of the node
         */
        D data;
        /**
         * next node pointer
         */
        Node *next;
        /**
         * previous node pointer
         */
        Node *previous;

        /**
         * constructor of all coefficients
         * @param data data inside the node
         * @param next next Node pointer
         * @param previous previous Node pointer
         */
        Node(D data, Node *next, Node *previous) : data(data), next(next), previous(previous) {}

        /**
         * constructor of only data
         * @param data data inside the node
         */
        explicit Node(D data) : data(data)
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
    /**
     * Linked List Head
     */
    Node<T> *head_node = new Node<T>(nullptr,nullptr);
    /**
     * Linked List Tail
     */
    Node<T> *tail_node = new Node<T>(nullptr,nullptr);
    /**
     * Linked List Length
     */
    size_t size = 0;

    /**
     * clear all data
     */
    void clear();

    /**
     * This function will return the Node has input index in previous LinkedList.
     * @param index finding index
     * @param include_tail can it search for tail_node?
     * @return next node
     */
    Node<T> * get_node_pointer(size_t index, bool include_tail);
};

#include "linked_list.tpp"

#endif //LINKED_LIST_H
