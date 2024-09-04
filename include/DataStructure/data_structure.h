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
     * assignment
     * @param other another Array Object
     * @return self object
     */
    Array& operator=(const Array& other);

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
     * equals function
     * @param other other Array
     * @return is them equals or not
     */
    bool equals(const Array& other);

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
class LinkedList : public Object {

};

#endif //DATA_STRUCTURE_H
