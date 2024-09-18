//
// Created by Eden_ on 2024/9/18.
//

#ifndef SET_INTERFACE_H
#define SET_INTERFACE_H

#include <vector>

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
    virtual bool remove(const ValueType& value) = 0;

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
    [[nodiscard]] virtual bool isEmpty() const = 0;

    /**
     * @brief Returns the number of elements in this set (its cardinality).
     *
     * @return std::size_t The number of elements in this set.
     */
    [[nodiscard]] virtual std::size_t size() const = 0;

    /**
     * @brief Removes all the elements from this set.
     *
     * The set will be empty after this call returns.
     */
    virtual void clear() = 0;

    /**
     * @brief Returns a vector containing all the elements in this set.
     *
     * @return std::vector<ValueType> A vector view of the elements contained in this set.
     */
    virtual std::vector<ValueType> toVector() const = 0;
};

#endif // SET_INTERFACE_H

