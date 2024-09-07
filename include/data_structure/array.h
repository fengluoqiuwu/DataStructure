//
// Created by Eden_ on 2024/9/6.
//

#ifndef ARRAY_H
#define ARRAY_H
#include "object.h"
#include "linked_list.h"

class array final : public object {
public:

    /**
     * Simple constructor , init the array with 0
     * Complexity: O(n)
     * @param size Size of the array
     */
    explicit array(size_t size);

    /**
     * copy constructor
     * Complexity: O(n)
     * @param other other class Array
     */
    array(const array& other);

    /**
     * move constructor
     * Complexity: O(1)
     * @param other other class Array
     */
    array(array&& other) noexcept ;

    /**
     * copy constructor from integer array
     * Complexity: O(n)
     * @param other an integer array head pointer
     * @param size size of the target array
     */
    array(int* other,size_t size);

    /**
     * destructor
     * Complexity: O(n)
     */
    ~array() override;

    /**
     * copy = operator
     * Complexity: O(n)
     * @param other another Array Object
     * @return self object
     */
    array& operator=(const array& other);

    /**
     * move = operator
     * Complexity: O(n)
     * @param other another Array Object
     * @return self object
     */
    array& operator=(array&& other) noexcept ;

    /**
     * equals operator
     * Complexity: O(n)
     * @param other another Array Object
     * @return self object
     */
    bool operator==(const array& other) const;

    /**
     * [] operator
     * @param index getting index
     * @return reference of data[index]
     */
    int& operator[](size_t index);

    /**
     * [] operator const
     * @param index getting by index
     * @return const reference of data[index]
     */
    const int& operator[](size_t index) const;

    /**
     * get size of array
     * Complexity: O(n)
     * @return size of array
     */
    [[nodiscard]] size_t get_size() const;

    /**
     * sort function , using Dual-Pivot Quicksort
     * Complexity: O(?)
     * @param ascending is ascending or not
     */
    void sort(bool ascending);

    /**
     * searching for key in array
     * Complexity: O(n)
     * @param key searching key
     * @return if key is searched in the array, then return the index; and in the otherwise return -1
     */
    [[nodiscard]] int search(int key) const;

    /**
     * searching for key in array, the array must be ascending
     * Complexity: O(log2_n)
     * @param key searching key
     * @return if key is searched in the array, then return the index; and in the otherwise return -1
     */
    [[nodiscard]] size_t binary_search(int key) const;

    /**
     * new a subarray, index end is not belong to subarray.
     * Complexity: O(n)
     * @param start start index
     * @param end end index
     * @return new subarray pointer
     */
    [[nodiscard]] array* subarray(size_t start, size_t end) const;

    /**
     * fill all array with input value
     * Complexity: O(n)
     * @param value fill value
     */
    void fill(int value) const;

    /**
     * new a linked_list from array
     * Complexity: O(n)
     * @return linked_list pointer
     */
    [[nodiscard]] linked_list<int>* to_list() const;

    /**
     * change array to String style
     * Complexity: O(n)
     * @return (Maybe Json style) string of the array
     */
    [[nodiscard]] std::string to_string() const override;

    /**
     * change string style array to Array object
     * Complexity: O(n)
     * @param str (Maybe Json style) string of the array
     * @return Array from string style
     */
    static array from_string(const std::string &str);

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
     * Complexity: O(n)
     */
    void clear();

};


#endif //ARRAY_H
