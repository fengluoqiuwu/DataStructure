//
// Created by Eden_ on 2024/9/6.
//

#ifndef ARRAY_H
#define ARRAY_H
#include "object.h"
#include "iterator.h"
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
    size_t size; /** Size of the array */

    int* data;   /** head pointer of the array */

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
    class Iterator
    {
    public:
        static constexpr iterator::type type=iterator::RANDOM_ACCESS;

        /**
         * @brief copy constructor
         * Complexity:O(1)
         * @param other other iterator
         */
        Iterator(const Iterator& other);

        /**
         * This method allows you to access and modify the value at the current position of the iterator.
         * Complexity: O(1)
         * @return A reference to the value pointed to by the iterator
         */
        int& operator*() const;

        /**
         * This method provides access to the value pointed to by the iterator, similar to dereferencing the iterator.
         * Complexity: O(1)
         * @return A pointer to the value pointed to by the iterator.
         */
        int* operator->() const;

        /**
         * @brief copy operator
         * Complexity:O(1)
         * @param other other iterator
         * @return self
         */
        Iterator & operator=(const Iterator& other);

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
         * Complexity: O(1)
         */
        ~Iterator();

        /**
         * This method advances the iterator by 'n' positions and returns the iterator itself.
         * Complexity: O(1)
         * @param n moving distance
         * @return A reference to the updated iterator after advancing it by 'n' positions.
         */
        Iterator& operator+=(size_t n);

        /**
         * This method moves the iterator backward by 'n' positions and returns the iterator itself.
         * Complexity: O(1)
         * @param n moving distance
         * @return A reference to the updated iterator after moving it back by 'n' positions.
         */
        Iterator& operator-=(size_t n);

        /**
         * This method creates a copy of the iterator advanced by 'n' positions.
         * Complexity: O(1)
         * @param n moving distance
         * @return An iterator pointing to the position 'n' steps ahead of the current iterator.
         */
        Iterator operator+(size_t n) const;

        /**
         * This method creates a copy of the iterator moved back by 'n' positions.
         * Complexity: O(1)
         * @param n moving distance
         * @return An iterator pointing to the position 'n' steps behind the current iterator.
         */
        Iterator operator-(size_t n) const;

        /**
         * This method compares if the current iterator is before the other iterator.
         * Complexity: O(1)
         * @param other other iterator
         * @return true if the current iterator is less than the other iterator; otherwise, false.
         */
        bool operator<(const Iterator& other) const;

        /**
         * This method compares if the current iterator is after the other iterator.
         * Complexity: O(1)
         * @param other other iterator
         * @return true if the current iterator is greater than the other iterator; otherwise, false.
         */
        bool operator>(const Iterator& other) const;

        /**
         * This method checks if the current iterator is before or at the same position as the other iterator.
         * Complexity: O(1)
         * @param other other iterator
         * @return true if the current iterator is less than or equal to the other iterator; otherwise, false.
         */
        bool operator<=(const Iterator& other) const;

        /**
         * This method checks if the current iterator is after or at the same position as the other iterator.
         * Complexity: O(1)
         * @param other other iterator
         * @return true if the current iterator is greater than or equal to the other iterator; otherwise, false.
         */
        bool operator>=(const Iterator& other) const;

        /**
         * This method calculates the distance between the current iterator and the other iterator.
         * Complexity: O(1)
         * @param other other iterator
         * @return The number of positions between the current iterator and the other iterator.
         */
        size_t operator-(const Iterator& other) const;

    private:
        friend class array;

        const array& outer; /** reference of linked list */
        int* current;       /** current pointer*/

    protected:
        /**
         * Constructor only can use by array
         * Complexity: O(1)
         * @param node current node
         * @param outer array reference
         */
        explicit Iterator(int *node,const array& outer) : outer(outer)
        {
            this->current = node;
        }
    };

    friend class ConstIterator;
    /**
     * Array iterator, for const linked list
     */
    class ConstIterator
    {
    public:
        static constexpr iterator::type type=iterator::RANDOM_ACCESS;

        /**
         * @brief copy constructor
         * Complexity:O(1)
         * @param other other iterator
         */
        ConstIterator(const ConstIterator& other);

        /**
         * This method allows you to access and modify the value at the current position of the iterator.
         * Complexity: O(1)
         * @return A reference to the value pointed to by the iterator
         */
        const int& operator*() const;

        /**
         * This method provides access to the value pointed to by the iterator, similar to dereferencing the iterator.
         * Complexity: O(1)
         * @return A pointer to the value pointed to by the iterator.
         */
        const int* operator->() const;

        /**
         * @brief copy operator
         * Complexity:O(1)
         * @param other other iterator
         * @return self
         */
        ConstIterator & operator=(const ConstIterator& other);

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

        /**
         * This method advances the iterator by 'n' positions and returns the iterator itself.
         * Complexity: O(1)
         * @param n moving distance
         * @return A reference to the updated iterator after advancing it by 'n' positions.
         */
        ConstIterator& operator+=(size_t n);

        /**
         * This method moves the iterator backward by 'n' positions and returns the iterator itself.
         * Complexity: O(1)
         * @param n moving distance
         * @return A reference to the updated iterator after moving it back by 'n' positions.
         */
        ConstIterator& operator-=(size_t n);

        /**
         * This method creates a copy of the iterator advanced by 'n' positions.
         * Complexity: O(1)
         * @param n moving distance
         * @return An iterator pointing to the position 'n' steps ahead of the current iterator.
         */
        ConstIterator operator+(size_t n) const;

        /**
         * This method creates a copy of the iterator moved back by 'n' positions.
         * Complexity: O(1)
         * @param n moving distance
         * @return An iterator pointing to the position 'n' steps behind the current iterator.
         */
        ConstIterator operator-(size_t n) const;

        /**
         * This method compares if the current iterator is before the other iterator.
         * Complexity: O(1)
         * @param other other iterator
         * @return true if the current iterator is less than the other iterator; otherwise, false.
         */
        bool operator<(const ConstIterator& other) const;

        /**
         * This method compares if the current iterator is after the other iterator.
         * Complexity: O(1)
         * @param other other iterator
         * @return true if the current iterator is greater than the other iterator; otherwise, false.
         */
        bool operator>(const ConstIterator& other) const;

        /**
         * This method checks if the current iterator is before or at the same position as the other iterator.
         * Complexity: O(1)
         * @param other other iterator
         * @return true if the current iterator is less than or equal to the other iterator; otherwise, false.
         */
        bool operator<=(const ConstIterator& other) const;

        /**
         * This method checks if the current iterator is after or at the same position as the other iterator.
         * Complexity: O(1)
         * @param other other iterator
         * @return true if the current iterator is greater than or equal to the other iterator; otherwise, false.
         */
        bool operator>=(const ConstIterator& other) const;

        /**
         * This method calculates the distance between the current iterator and the other iterator.
         * Complexity: O(1)
         * @param other other iterator
         * @return The number of positions between the current iterator and the other iterator.
         */
        size_t operator-(const ConstIterator& other) const;
    private:

        friend class array;

        const array& outer; /** reference of linked list */
        const int* current; /** current pointer*/

    protected:
        /**
         * Constructor only can use by array
         * Complexity: O(1)
         * @param node current node
         * @param outer reference of array
         */
        explicit ConstIterator(const int *node, const array& outer): outer(outer)
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
