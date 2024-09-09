//
// Created by Eden_ on 2024/9/9.
//

#ifndef QUEUE_H
#define QUEUE_H

#include "linked_list.h"

/**
 * Queue using linked list as the underlying data structure
 * @tparam T Type of the data
 */
template <typename T>
class queue : private linked_list<T>
{
public:
    /**
     * Simple constructor, initializes as an empty queue
     * Complexity: O(1)
     */
    queue() = default;

    /**
     * Copy constructor from another queue
     * Complexity: O(n)
     * @param other another queue
     */
    queue(const queue &other) = default;

    /**
     * Move constructor from another queue
     * Complexity: O(1)
     * @param other another queue
     */
    queue(queue &&other) noexcept = default;

    /**
     * Copy assignment operator
     * Complexity: O(n)
     * @param other another queue
     * @return self
     */
    queue &operator=(const queue &other) = default;

    /**
     * Move assignment operator
     * Complexity: O(n)
     * @param other another queue
     * @return self
     */
    queue &operator=(queue &&other) noexcept = default;

    /**
     * Enqueue a value to the end of the queue
     * Complexity: O(1)
     * @param value value to add
     */
    void enqueue(const T &value)
    {
        linked_list<T>::add_last(value);
    }

    /**
     * Dequeue a value from the front of the queue
     * Complexity: O(1)
     * @return value removed from the front
     */
    T dequeue()
    {
        if (linked_list<T>::is_empty()) {
            throw std::out_of_range("Queue is empty");
        }
        T value = linked_list<T>::pop_first();
        return value;
    }

    /**
     * Peek the front value of the queue without removing it
     * Complexity: O(1)
     * @return front value
     */
    T &front()
    {
        if (linked_list<T>::is_empty()) {
            throw std::out_of_range("Queue is empty");
        }
        return linked_list<T>::get_first();
    }

    /**
     * Peek the front value of the queue without removing it, const
     * Complexity: O(1)
     * @return front value
     */
    const T &front() const
    {
     if (linked_list<T>::is_empty()) {
      throw std::out_of_range("Queue is empty");
     }
     return linked_list<T>::get_first();
    }

    /**
     * Peek the back value of the queue without removing it
     * Complexity: O(1)
     * @return front value
     */
    T &back()
       {
        if (linked_list<T>::is_empty()) {
         throw std::out_of_range("Queue is empty");
        }
        return linked_list<T>::get_last();
       }

    /**
     * Peek the front back of the queue without removing it, const
     * Complexity: O(1)
     * @return front value
     */
    const T &back() const
       {
        if (linked_list<T>::is_empty()) {
         throw std::out_of_range("Queue is empty");
        }
        return linked_list<T>::get_last();
       }

    /**
     * Check if the queue is empty
     * Complexity: O(1)
     * @return true if empty, false otherwise
     */
    using linked_list<T>::is_empty;

    /**
     * Get the size of the queue
     * Complexity: O(1)
     * @return size of the queue
     */
    using linked_list<T>::get_size;
};


#endif //QUEUE_H
