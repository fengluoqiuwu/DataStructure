//
// Created by Eden_ on 2024/9/6.
//

#ifndef ARRAY_H
#define ARRAY_H
#include "object.h"
#include "linked_list.h"

class array : public object {
public:

    /**
     * Simple constructor , init the array with 0
     * @param size Size of the array
     */
    explicit array(size_t size);

    /**
     * copy constructor
     * @param other other class Array
     */
    array(const array& other);

    /**
     * move constructor
     * @param other other class Array
     */
    array(array&& other) noexcept ;

    /**
     * copy constructor from integer array
     * @param other an integer array head pointer
     * @param size size of the target array
     */
    array(int* other,size_t size);

    /**
     * destructor
     */
    ~array() override;

    /**
     * copy = operator
     * @param other another Array Object
     * @return self object
     */
    array& operator=(const array& other);

    /**
     * move = operator
     * @param other another Array Object
     * @return self object
     */
    array& operator=(array&& other) noexcept ;

    /**
     * equals
     * @param other another Array Object
     * @return self object
     */
    bool operator==(const array& other) const;

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
    [[nodiscard]] int search(int key) const;

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
    [[nodiscard]] array* subarray(size_t start, size_t end) const;

    /**
     * fill all array with input value
     * @param value fill value
     */
    void fill(int value) const;

    /**
     * new a LinkedList from array
     * @return LinkedList pointer
     */
    [[nodiscard]] LinkedList<int>* toList() const;

    /**
     * change array to String style
     * @return (Maybe Json style) string of the array
     */
    [[nodiscard]] std::string to_string() const override;

    /**
     * change string style array to Array object
     * @param str (Maybe Json style) string of the array
     * @return Array from string style
     */
    static array form_string(const std::string &str);

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


#endif //ARRAY_H
