//
// Created by Eden_ on 2024/9/9.
//

#ifndef STACK_H
#define STACK_H

#include <stdexcept>
#include "linked_list.h"

/**
 * Stack using linked list as the underlying data structure
 * @tparam T Type of the data
 */
template <typename T>
class stack : private linked_list<T>
{
public:
    /**
     * Simple constructor, initializes as an empty stack
     * Complexity: O(1)
     */
    stack() = default;

    /**
     * Copy constructor from another stack
     * Complexity: O(n)
     * @param other another stack
     */
    stack(const stack &other) = default;

    /**
     * Move constructor from another stack
     * Complexity: O(1)
     * @param other another stack
     */
    stack(stack &&other) noexcept = default;

    /**
     * Copy assignment operator
     * Complexity: O(n)
     * @param other another stack
     * @return self
     */
    stack &operator=(const stack &other) = default;

    /**
     * Move assignment operator
     * Complexity: O(n)
     * @param other another stack
     * @return self
     */
    stack &operator=(stack &&other) noexcept = default;

    /**
     * Push a value onto the stack
     * Complexity: O(1)
     * @param value value to add
     */
    void push(const T &value)
    {
        linked_list<T>::add_last(value);
    }

    /**
     * Pop a value from the top of the stack
     * Complexity: O(1)
     * @return value removed from the top
     */
    T pop()
    {
        if (linked_list<T>::is_empty()) {
            throw std::out_of_range("Stack is empty");
        }
        T value = linked_list<T>::pop_last();
        return value;
    }

    /**
     * Peek the top value of the stack without removing it
     * Complexity: O(1)
     * @return top value
     */
    T &top()
    {
        if (linked_list<T>::is_empty()) {
            throw std::out_of_range("Stack is empty");
        }
        return linked_list<T>::get_last();
    }

    /**
     * Peek the top value of the stack without removing it
     * Complexity: O(1)
     * @return top value
     */
    const T &top() const
    {
     if (linked_list<T>::is_empty()) {
      throw std::out_of_range("Stack is empty");
     }
     return linked_list<T>::get_last();
    }

    /**
     * Check if the stack is empty
     * Complexity: O(1)
     * @return true if empty, false otherwise
     */
    using linked_list<T>::is_empty;

    /**
     * Get the size of the stack
     * Complexity: O(1)
     * @return size of the stack
     */
    using linked_list<T>::get_size;
};


#endif //STACK_H
