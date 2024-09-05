//
// Created by Eden_ on 2024/9/4.
//

#ifndef DATA_STRUCTURE_H
#define DATA_STRUCTURE_H

#include <iostream>
#include <ostream>
#include <string>

/**
 * Basic data structure class
 */
class Object;

/**
 * Class of integer array
 */
class Array;

/**
 * Class of linked list
 */
template <typename T>
class LinkedList;

class Object {
public:
    virtual ~Object() = default;

    /**
     * change the data to (Json style?) string of the data structure
     * @return (Json style?) string of the data structure
     */
    [[nodiscard]] virtual std::string to_string() const = 0;

    /**
     * print (Json style?) string of the data structure
     */
    void print() const {
        std::cout << to_string() << std::endl;
    }
};

class Array : public Object {
public:

    /**
     * Simple constructor , init the array with 0
     * @param size Size of the array
     */
    explicit Array(size_t size);

    /**
     * copy constructor
     * @param other other class Array
     */
    Array(const Array& other);

    /**
     * move constructor
     * @param other other class Array
     */
    Array(Array&& other) noexcept ;

    /**
     * copy constructor from integer array
     * @param other an integer array head pointer
     * @param size size of the target array
     */
    Array(int* other,size_t size);

    /**
     * destructor
     */
    ~Array() override;

    /**
     * copy = operator
     * @param other another Array Object
     * @return self object
     */
    Array& operator=(const Array& other);

    /**
     * move = operator
     * @param other another Array Object
     * @return self object
     */
    Array& operator=(Array&& other) noexcept ;

    /**
     * equals
     * @param other another Array Object
     * @return self object
     */
    bool operator==(const Array& other);

    /**
     * sort function , using Dual-Pivot Quicksort
     * @param ascending is ascending or not
     */
    void sort(bool ascending);//TODO

    /**
     * searching for key in array
     * @param key searching key
     * @return if key is searched in the array, then return the index; and in the otherwise return -1
     */
    int search(int key);

    /**
     * searching for key in array, the array must be ascending
     * @param key searching key
     * @return if key is searched in the array, then return the index; and in the otherwise return -1
     */
    [[nodiscard]] size_t binary_search(int key) const;

    /**
     * new a subarray, index end is not belong to subarray.
     * @param start start index
     * @param end end index
     * @return new subarray pointer
     */
    Array* subarray(size_t start, size_t end);

    /**
     * fill all array with input value
     * @param value fill value
     */
    void fill(int value) const;

    /**
     * new a LinkedList from array
     * @return LinkedList pointer
     */
    [[nodiscard]] LinkedList<int>* toList() const;//TODO

    [[nodiscard]] std::string to_string() const override;

    static Array* form_string(const std::string &str);

private:
    /**
     * Size of the array
     */
    size_t size;
    /**
     * head pointer of the array
     */
    int* data;

    /**
     * clear data and release space
     */
    void clear();

};

template <typename T>
class LinkedList : public Object
{
public:
    /**
     * Simple constructor, Init it as a empty linked list
     */
    LinkedList();

    /**
     * copy Constructor from another LinkedList
     * @param other another Linked List
     */
    LinkedList(const LinkedList &other); // TODO

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
    LinkedList(T *other, size_t size); // TODO

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
    void add(int index, T value);

    /**
     * get data by giving index
     * @param index getting index
     * @return data at given index,you can change it by overwrite operator =
     */
    T &get(int index) const;

    /**
     * set data in given index to input value
     * @param index setting index
     * @param value setting value
     */
    void set(int index, T value);

    /**
     * remove node at given index
     * @param index remove index
     */
    void remove(int index);

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
    bool contains(T value);

    /**
     * get size of linked list
     * @return size of Linked list
     */
    size_t get_size() const;

    /**
     * check is LinkedList empty
     * @return is empty or not
     */
    bool is_empty() const;

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
    Node<T> *head_node = new Node<T>();
    /**
     * Linked List Tail
     */
    Node<T> *tail_node = new Node<T>();
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
     * It can return tail_node but can't return head_note.
     * @param index finding index
     * @return next node
     */
    Node<T> * get_node_pointer(size_t index);
};

#endif //DATA_STRUCTURE_H
