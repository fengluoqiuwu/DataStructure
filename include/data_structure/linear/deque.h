//
// Created by Eden_ on 2024/9/9.
//

#ifndef DEQUE_H
#define DEQUE_H

#include <stdexcept>
#include "linked_list.h"

/**
 * Deque (Double-ended Queue) using linked list as the underlying data structure
 * @tparam T Type of the data
 */
template <typename T>
class deque : private linked_list<T>
{
public:
    /**
     * Simple constructor, initializes as an empty deque
     * Complexity: O(1)
     */
    deque() = default;

    /**
     * Copy constructor from another deque
     * Complexity: O(n)
     * @param other another deque
     */
    deque(const deque &other) = default;

    /**
     * Move constructor from another deque
     * Complexity: O(1)
     * @param other another deque
     */
    deque(deque &&other) noexcept = default;

    /**
     * Copy assignment operator
     * Complexity: O(n)
     * @param other another deque
     * @return self
     */
    deque &operator=(const deque &other) = default;

    /**
     * Move assignment operator
     * Complexity: O(n)
     * @param other another deque
     * @return self
     */
    deque &operator=(deque &&other) noexcept = default;

    /**
     * Add a value to the front of the deque
     * Complexity: O(1)
     * @param value value to add
     */
    void push_front(const T &value)
    {
        linked_list<T>::add_first(value);
    }

    /**
     * Add a value to the back of the deque
     * Complexity: O(1)
     * @param value value to add
     */
    void push_back(const T &value)
    {
        linked_list<T>::add_last(value);
    }

    /**
     * Remove a value from the front of the deque
     * Complexity: O(1)
     * @return value removed from the front
     */
    T pop_front()
    {
        if (linked_list<T>::is_empty()) {
            throw std::out_of_range("Deque is empty");
        }
        T value = linked_list<T>::pop_first();
        return value;
    }

    /**
     * Remove a value from the back of the deque
     * Complexity: O(1)
     * @return value removed from the back
     */
    T pop_back()
    {
        if (linked_list<T>::is_empty()) {
            throw std::out_of_range("Deque is empty");
        }
        T value = linked_list<T>::pop_last();
        return value;
    }

    /**
     * Peek the front value of the deque without removing it
     * Complexity: O(1)
     * @return front value
     */
    T &front()
    {
        if (linked_list<T>::is_empty()) {
            throw std::out_of_range("Deque is empty");
        }
        return linked_list<T>::get_first();
    }

    /**
     * Peek the front value of the deque without removing it, const
     * Complexity: O(1)
     * @return front value
     */
    const T &front() const
    {
        if (linked_list<T>::is_empty()) {
            throw std::out_of_range("Deque is empty");
        }
        return linked_list<T>::get_first();
    }

    /**
     * Peek the back value of the deque without removing it
     * Complexity: O(1)
     * @return back value
     */
    T &back()
    {
        if (linked_list<T>::is_empty()) {
            throw std::out_of_range("Deque is empty");
        }
        return linked_list<T>::get_last();
    }

    /**
     * Peek the back value of the deque without removing it
     * Complexity: O(1)
     * @return back value
     */
    const T &back() const
    {
        if (linked_list<T>::is_empty()) {
            throw std::out_of_range("Deque is empty");
        }
        return linked_list<T>::get_last();
    }

    /**
     * Check if the deque is empty
     * Complexity: O(1)
     * @return true if empty, false otherwise
     */
    using linked_list<T>::is_empty;

    /**
     * Get the size of the deque
     * Complexity: O(1)
     * @return size of the deque
     */
    using linked_list<T>::get_size;

    /**
     * Clear the deque
     * Complexity: O(n)
     */
    using linked_list<T>::clear;
};


#endif //DEQUE_H
