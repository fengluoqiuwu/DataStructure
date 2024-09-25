//
// Created by Eden_ on 2024/9/18.
//

#ifndef HASH_SET_H
#define HASH_SET_H

#include "set_interface.h"

/**
 * @brief A generic set interface similar to Java's HashSet, which implement from Set.
 *
 * @tparam ValueType Type of the value stored in the set.
 */
template <typename ValueType>
class hash_set : public Set<ValueType>, protected basic_hash_map<ValueType, char>
{
public:
    /**
     * @brief Default constructor that creates an empty hash_set.
     */
    hash_set();

    /**
     * @brief Constructor that initializes the set with elements from an array.
     *
     * @param initialize_list Pointer to the array containing the elements.
     * @param size The number of elements in the array.
     */
    hash_set(ValueType *initialize_list, size_t size);

    /**
     * @brief Constructor that initializes the set with elements from a linked list.
     *
     * @param initialize_list The linked list containing the elements to initialize the set.
     */
    explicit hash_set(linked_list<ValueType> initialize_list);

    /**
     * @brief Copy constructor that creates a new hash_set as a copy of another.
     *
     * @param other The hash_set to copy from.
     */
    explicit hash_set(const Set<ValueType> &other);

    /**
     * @brief Move constructor that creates a new hash_set by moving another.
     *
     * @param other The hash_set to move from.
     */
    explicit hash_set(Set<ValueType> &&other) noexcept;

    /**
     * @brief Destructor for hash_set.
     */
    ~hash_set() override;

    /**
     * @brief Copy assignment operator that assigns the contents of another hash_set.
     *
     * @param other The hash_set to copy from.
     * @return hash_set& A reference to this hash_set.
     */
    hash_set &operator=(const Set<ValueType> &other);

    /**
     * @brief Move assignment operator that moves the contents of another hash_set.
     *
     * @param other The hash_set to move from.
     * @return hash_set& A reference to this hash_set.
     */
    hash_set &operator=(Set<ValueType> &&other) noexcept;

    /**
     * @brief Adds the specified element to the set if it is not already present.
     *
     * @param value The element to be added to this set.
     * @return true If this set did not already contain the specified element.
     * @return false If this set already contains the specified element.
     */
    bool add(const ValueType &value) override;

    /**
     * @brief Removes the specified element from this set if it is present.
     *
     * @param value The element to be removed from this set.
     * @return true If the set contained the specified element.
     * @return false If the set did not contain the specified element.
     */
    bool erase(const ValueType &value) override;

    /**
     * @brief Returns true if this set contains the specified element.
     *
     * @param value The element whose presence in this set is to be tested.
     * @return true If this set contains the specified element.
     * @return false If this set does not contain the specified element.
     */
    bool contains(const ValueType &value) const override;

    /**
     * @brief Returns the number of elements in this set (its cardinality).
     *
     * @return std::size_t The number of elements in this set.
     */
    [[nodiscard]] std::size_t get_size() const override;

    /**
     * @brief Returns true if this set contains no elements.
     *
     * @return true If this set contains no elements.
     * @return false If this set contains one or more elements.
     */
    [[nodiscard]] bool is_empty() const override;

    /**
     * @brief Removes all the elements from this set.
     *
     * The set will be empty after this call returns.
     */
    void clear() override;

    /**
     * @brief Returns a list containing all the elements in this set.
     *
     * @return linked_list<ValueType> A list view of the elements contained in this set.
     */
    linked_list<ValueType> to_list() const override;
};

#include "hash_set.tpp"

#endif //HASH_SET_H
