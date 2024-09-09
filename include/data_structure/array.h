//
// Created by Eden_ on 2024/9/6.
//

#ifndef ARRAY_H
#define ARRAY_H
#include "object.h"
#include "linked_list.h"
#include "iterator.h"

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

public:

    friend class Iterator;
    /**
     * Array iterator, for not const linked list
     */
    class Iterator : iterator::RandomAccessIterator<int,int>
    {
    public:

        /**
         * This method allows you to access and modify the value at the current position of the iterator.
         * Complexity: O(1)
         * @return A reference to the value pointed to by the iterator
         */
        int& operator*() const override;

        /**
         * This method provides access to the value pointed to by the iterator, similar to dereferencing the iterator.
         * Complexity: O(1)
         * @return A pointer to the value pointed to by the iterator.
         */
        int* operator->() const override;

        /**
         * This is the pre-increment operator. It advances the iterator by one position and returns a reference to the modified iterator itself.
         * Complexity: O(1)
         * @return A reference to the updated iterator after it has been incremented.
         */
        iterator::ForwardIterator<int,int>& operator++() override;

        /**
         * This method moves the iterator backward by one position (pre-decrement) and returns the iterator itself.
         * Complexity: O(1)
         * @return  A reference to the updated iterator after it has been decremented.
         */
        iterator::BidirectionalIterator<int,int>& operator--() override;

        /**
         * destructor
         * Complexity: O(1)
         */
        ~Iterator() override;

        /**
         * This method advances the iterator by 'n' positions and returns the iterator itself.
         * Complexity: O(1)
         * @param n moving distance
         * @return A reference to the updated iterator after advancing it by 'n' positions.
         */
        RandomAccessIterator<int, int>& operator+=(size_t n) override;

        /**
         * This method moves the iterator backward by 'n' positions and returns the iterator itself.
         * Complexity: O(1)
         * @param n moving distance
         * @return A reference to the updated iterator after moving it back by 'n' positions.
         */
        RandomAccessIterator<int, int>& operator-=(size_t n) override;

        /**
         * This method creates a copy of the iterator advanced by 'n' positions.
         * Complexity: O(1)
         * @param n moving distance
         * @return An iterator pointing to the position 'n' steps ahead of the current iterator.
         */
        RandomAccessIterator<int, int>* operator+(size_t n) const override;

        /**
         * This method creates a copy of the iterator moved back by 'n' positions.
         * Complexity: O(1)
         * @param n moving distance
         * @return An iterator pointing to the position 'n' steps behind the current iterator.
         */
        RandomAccessIterator<int, int>* operator-(size_t n) const override;

        /**
         * This method compares if the current iterator is before the other iterator.
         * Complexity: O(1)
         * @param other other iterator
         * @return true if the current iterator is less than the other iterator; otherwise, false.
         */
        bool operator<(const RandomAccessIterator<int, int>& other) const override;
        bool operator<(const Iterator& other) const;

        /**
         * This method compares if the current iterator is after the other iterator.
         * Complexity: O(1)
         * @param other other iterator
         * @return true if the current iterator is greater than the other iterator; otherwise, false.
         */
        bool operator>(const RandomAccessIterator<int, int>& other) const override;
        bool operator>(const Iterator& other) const;

        /**
         * This method checks if the current iterator is before or at the same position as the other iterator.
         * Complexity: O(1)
         * @param other other iterator
         * @return true if the current iterator is less than or equal to the other iterator; otherwise, false.
         */
        bool operator<=(const RandomAccessIterator<int, int>& other) const override;
        bool operator<=(const Iterator& other) const;

        /**
         * This method checks if the current iterator is after or at the same position as the other iterator.
         * Complexity: O(1)
         * @param other other iterator
         * @return true if the current iterator is greater than or equal to the other iterator; otherwise, false.
         */
        bool operator>=(const RandomAccessIterator<int, int>& other) const override;
        bool operator>=(const Iterator& other) const;

        /**
         * This method calculates the distance between the current iterator and the other iterator.
         * Complexity: O(1)
         * @param other other iterator
         * @return The number of positions between the current iterator and the other iterator.
         */
        size_t operator-(const RandomAccessIterator<int, int>& other) const override;
        size_t operator-(const Iterator& other) const;

    private:
        friend class array;

        /**
         * reference of array
         */
        array& outer;

    protected:
        /**
         * Constructor only can use by array
         * Complexity: O(1)
         * @param node current node
         * @param outer array reference
         */
        explicit Iterator(int *node,array& outer) : outer(outer)
        {
            this->current = node;
        }
    };

    friend class ConstIterator;
    /**
     * Array iterator, for const linked list
     */
    class ConstIterator : iterator::RandomAccessConstIterator<int,int>
    {
    public:

        /**
         * This method allows you to access and modify the value at the current position of the iterator.
         * Complexity: O(1)
         * @return A reference to the value pointed to by the iterator
         */
        const int& operator*() const override;

        /**
         * This method provides access to the value pointed to by the iterator, similar to dereferencing the iterator.
         * Complexity: O(1)
         * @return A pointer to the value pointed to by the iterator.
         */
        const int* operator->() const override;

        /**
         * This is the pre-increment operator. It advances the iterator by one position and returns a reference to the modified iterator itself.
         * Complexity: O(1)
         * @return A reference to the updated iterator after it has been incremented.
         */
        iterator::ForwardConstIterator<int,int>& operator++() override;

        /**
         * This method moves the iterator backward by one position (pre-decrement) and returns the iterator itself.
         * Complexity: O(1)
         * @return  A reference to the updated iterator after it has been decremented.
         */
        iterator::BidirectionalConstIterator<int,int>& operator--() override;

        /**
         * destructor
         * Complexity: O(1)
         */
        ~ConstIterator() override;

        /**
         * This method advances the iterator by 'n' positions and returns the iterator itself.
         * Complexity: O(1)
         * @param n moving distance
         * @return A reference to the updated iterator after advancing it by 'n' positions.
         */
        RandomAccessConstIterator& operator+=(size_t n) override;

        /**
         * This method moves the iterator backward by 'n' positions and returns the iterator itself.
         * Complexity: O(1)
         * @param n moving distance
         * @return A reference to the updated iterator after moving it back by 'n' positions.
         */
        RandomAccessConstIterator& operator-=(size_t n) override;

        /**
         * This method creates a copy of the iterator advanced by 'n' positions.
         * Complexity: O(1)
         * @param n moving distance
         * @return An iterator pointing to the position 'n' steps ahead of the current iterator.
         */
        RandomAccessConstIterator* operator+(size_t n) const override;

        /**
         * This method creates a copy of the iterator moved back by 'n' positions.
         * Complexity: O(1)
         * @param n moving distance
         * @return An iterator pointing to the position 'n' steps behind the current iterator.
         */
        RandomAccessConstIterator* operator-(size_t n) const override;

        /**
         * This method compares if the current iterator is before the other iterator.
         * Complexity: O(1)
         * @param other other iterator
         * @return true if the current iterator is less than the other iterator; otherwise, false.
         */
        bool operator<(const RandomAccessConstIterator& other) const override;
        bool operator<(const ConstIterator& other) const;

        /**
         * This method compares if the current iterator is after the other iterator.
         * Complexity: O(1)
         * @param other other iterator
         * @return true if the current iterator is greater than the other iterator; otherwise, false.
         */
        bool operator>(const RandomAccessConstIterator& other) const override;
        bool operator>(const ConstIterator& other) const;

        /**
         * This method checks if the current iterator is before or at the same position as the other iterator.
         * Complexity: O(1)
         * @param other other iterator
         * @return true if the current iterator is less than or equal to the other iterator; otherwise, false.
         */
        bool operator<=(const RandomAccessConstIterator& other) const override;
        bool operator<=(const ConstIterator& other) const;

        /**
         * This method checks if the current iterator is after or at the same position as the other iterator.
         * Complexity: O(1)
         * @param other other iterator
         * @return true if the current iterator is greater than or equal to the other iterator; otherwise, false.
         */
        bool operator>=(const RandomAccessConstIterator& other) const override;
        bool operator>=(const ConstIterator& other) const;

        /**
         * This method calculates the distance between the current iterator and the other iterator.
         * Complexity: O(1)
         * @param other other iterator
         * @return The number of positions between the current iterator and the other iterator.
         */
        size_t operator-(const RandomAccessConstIterator& other) const override;
        size_t operator-(const ConstIterator& other) const;
    private:

        friend class array;

        /**
         * reference of array
         */
        const array& outer;

    protected:
        /**
         * Constructor only can use by array
         * Complexity: O(1)
         * @param node current node
         * @param outer reference of array
         */
        explicit ConstIterator(int *node, const array& outer): outer(outer)
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
    [[nodiscard]] ConstIterator begin() const;

    /**
     * get const end iterator,which is pointing to index size
     * Complexity: O(1)
     * @return const end iterator
     */
    [[nodiscard]] ConstIterator end() const;
};
#endif //ARRAY_H
