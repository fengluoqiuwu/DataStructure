//
// Created by Eden_ on 2024/9/18.
//

#ifndef SET_INTERFACE_H
#define SET_INTERFACE_H

/**
 * @brief A generic set interface similar to Java's Set.
 *
 * @tparam ValueType Type of the values stored in the set.
 */
template<typename ValueType>
class Set {
public:
    /**
     * @brief Virtual destructor.
     */
    virtual ~Set() = default;

    /**
     * @brief Adds the specified element to the set if it is not already present.
     *
     * @param value The element to be added to this set.
     * @return true If this set did not already contain the specified element.
     * @return false If this set already contains the specified element.
     */
    virtual bool add(const ValueType& value) = 0;

    /**
     * @brief Removes the specified element from this set if it is present.
     *
     * @param value The element to be removed from this set.
     * @return true If the set contained the specified element.
     * @return false If the set did not contain the specified element.
     */
    virtual bool erase(const ValueType& value) = 0;

    /**
     * @brief Returns true if this set contains the specified element.
     *
     * @param value The element whose presence in this set is to be tested.
     * @return true If this set contains the specified element.
     * @return false If this set does not contain the specified element.
     */
    virtual bool contains(const ValueType& value) const = 0;

    /**
     * @brief Returns true if this set contains no elements.
     *
     * @return true If this set contains no elements.
     * @return false If this set contains one or more elements.
     */
    [[nodiscard]] virtual bool is_empty() const = 0;

    /**
     * @brief Returns the number of elements in this set (its cardinality).
     *
     * @return std::size_t The number of elements in this set.
     */
    [[nodiscard]] virtual std::size_t get_size() const = 0;

    /**
     * @brief Removes all the elements from this set.
     *
     * The set will be empty after this call returns.
     */
    virtual void clear() = 0;

    /**
     * @brief Returns a list containing all the elements in this set.
     *
     * @return linked_list<ValueType> A list view of the elements contained in this set.
     */
    virtual linked_list<ValueType> to_list() const = 0; // TODO,将其改为list的接口

    /**
     * @brief Const forward iterator for the Set.
     *
     * This iterator provides forward traversal capabilities for the Set,
     * with read-only access to the data.
     */
    class ConstIterator
    {
    public:
        static constexpr iterator::type type = iterator::FORWARD;

        /**
         * This method allows you to access and modify the value at the current position of the iterator.
         * @return A reference to the Pair pointed to by the iterator
         */
        virtual const ValueType &operator*() const =0;

        /**
         * This method provides access to the value pointed to by the iterator, similar to dereferencing the iterator.
         * @return A pointer to the Pair pointed to by the iterator.
         */
        virtual const ValueType *operator->() const =0;

        /**
         * This method checks if two iterators are pointing to the same element.
         * @param other other iterator
         * @return true if the current iterator is equal to the other iterator (i.e., they point to the same position);
         * otherwise, false.
         */
        virtual bool operator==(const ConstIterator &other) const =0;

        /**
         * This method checks if two iterators are pointing to different elements.
         * @param other other iterator
         * @return true if the current iterator is not equal to the other iterator (i.e., they point to different
         * positions); otherwise, false.
         */
        virtual bool operator!=(const ConstIterator &other) const =0;

        /**
         * This is the pre-increment operator. It advances the iterator by one position and returns a reference to the
         * modified iterator itself.
         * @return A reference to the updated iterator after it has been incremented.
         */
        virtual ConstIterator &operator++() =0;
    };
};

#endif // SET_INTERFACE_H

