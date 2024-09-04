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
     * generate data from (Json style?) string
     * @param str input string
     */
    virtual void form_string(const std::string& str) = 0;

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
    explicit Array(int size);

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
    Array(int* other,int size);

    /**
     * destructor
     */
    ~Array() override;//TODO

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
    int search(int key);//TODO

    /**
     * searching for key in array, the array must be ascending
     * @param key searching key
     * @return if key is searched in the array, then return the index; and in the otherwise return -1
     */
    int binary_search(int key);//TODO

    /**
     * new a subarray, index end is not belong to subarray.
     * @param start start index
     * @param end end index
     * @return new subarray pointer
     */
    Array* subarray(int start, int end);//TODO

    /**
     * equals function
     * @param other other Array
     * @return is them equals or not
     */
    bool equals(const Array& other);//TODO

    /**
     * fill all array with input value
     * @param value fill value
     */
    void fill(int value);//TODO

    /**
     * new a LinkedList from array
     * @return LinkedList pointer
     */
    [[nodiscard]] LinkedList<int>* toList() const;//TODO

    [[nodiscard]] std::string to_string() const override;

    void form_string(const std::string &str) override;

private:
     /**
     * Size of the array
     */
    int size;
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
