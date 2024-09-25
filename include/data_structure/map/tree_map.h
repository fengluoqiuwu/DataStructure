//
// Created by Eden_ on 2024/9/18.
//

#ifndef TREE_MAP_H
#define TREE_MAP_H

#include <optional>
#include "map_interface.h"
#include "red_black_tree.h"

/**
 * @brief A generic map similar to Java's TreeMap, which implement from Map.
 *
 * @tparam KeyType Type of the key used in the map.
 * @tparam ValueType Type of the value stored in the map.
 */
template <typename KeyType, typename ValueType = char>
class basic_tree_map : public Map<KeyType, ValueType>, red_black_tree<Pair<KeyType, ValueType>>
{
public:
    /**
     * @brief Default constructor for tree_map.
     * Initializes an empty tree_map.
     */
    basic_tree_map();

    /**
     * @brief Constructor that initializes the tree_map with a list of key-value pairs.
     *
     * @param initialize_list An array of key-value pairs to initialize the map.
     * @param size The size of the initialize_list.
     */
    basic_tree_map(std::pair<KeyType, ValueType> *initialize_list, size_t size);

    /**
     * @brief Constructor that initializes the tree_map from a linked list of key-value pairs.
     *
     * @param initialize_list A linked list of key-value pairs.
     */
    explicit basic_tree_map(linked_list<std::pair<KeyType, ValueType>> initialize_list);

    /**
     * @brief Copy constructor.
     * Initializes the tree_map as a copy of another tree_map.
     *
     * @param other The tree_map to copy from.
     */
    explicit basic_tree_map(const Map<KeyType, ValueType> &other);

    /**
     * @brief Move constructor.
     * Initializes the tree_map by moving another tree_map.
     *
     * @param other The tree_map to move from.
     */
    explicit basic_tree_map(Map<KeyType,ValueType> &&other) noexcept;

    /**
     * @brief Destructor for the tree_map.
     * Cleans up all resources used by the tree_map.
     */
    ~basic_tree_map() override;

    /**
     * @brief Copy assignment operator.
     * Assigns the contents of another tree_map to this tree_map.
     *
     * @param other The tree_map to assign from.
     * @return tree_map& A reference to this tree_map.
     */
    virtual basic_tree_map &operator=(const Map<KeyType,ValueType> &other);

    /**
     * @brief Move assignment operator.
     * Moves the contents of another tree_map to this tree_map.
     *
     * @param other The tree_map to move from.
     * @return tree_map& A reference to this tree_map.
     */
    virtual basic_tree_map &operator=(Map<KeyType,ValueType> &&other) noexcept;

    /**
     * @brief Associates the specified value with the specified key in the map.
     *
     * If the map previously contained a mapping for the key, the old value is replaced.
     *
     * @param key The key with which the specified value is to be associated.
     * @param value The value to be associated with the specified key.
     * @return std::optional<ValueType> The previous value associated with key, or std::nullopt if there was no mapping
     * for key.
     */
    std::optional<ValueType> put(const KeyType &key, const ValueType &value) override;

    /**
     * @brief Returns the value to which the specified key is mapped, or std::nullopt if this map contains no mapping
     * for the key.
     *
     * @param key The key whose associated value is to be returned.
     * @return std::optional<ValueType> The value to which the specified key is mapped, or std::nullopt if there is no
     * mapping for the key.
     */
    std::optional<ValueType> get(const KeyType &key) const override;

    /**
     * @brief Removes the mapping for the specified key from this map if present.
     *
     * @param key The key whose mapping is to be removed from the map.
     * @return std::optional<ValueType> The previous value associated with key, or std::nullopt if there was no mapping
     * for key.
     */
    std::optional<ValueType> remove(const KeyType &key) override;

    /**
     * @brief Returns true if this map contains a mapping for the specified key.
     *
     * @param key The key whose presence in this map is to be tested.
     * @return true If this map contains a mapping for the specified key.
     * @return false If this map does not contain a mapping for the specified key.
     */
    bool contains_key(const KeyType &key) const override;

    /**
     * @brief Returns true if this map contains no key-value mappings.
     *
     * @return true If this map contains no key-value mappings.
     * @return false If this map contains one or more key-value mappings.
     */
    [[nodiscard]] bool is_empty() const override;

    /**
     * @brief Returns the number of key-value mappings in this map.
     *
     * @return std::size_t The number of key-value mappings in this map.
     */
    [[nodiscard]] std::size_t get_size() const override;

    /**
     * @brief Removes all the mappings from this map.
     *
     * The map will be empty after this call returns.
     */
    void clear() override;

    /**
     * @brief Returns a vector containing all the keys in this map.
     *
     * @return std::unique_ptr<Set<KeyType>> A set view of the keys contained in this map.
     */
    [[nodiscard]] std::unique_ptr<Set<KeyType>> key_set() const override;

    /**
     * @brief Returns a vector containing all the values in this map.
     *
     * @return std::unique_ptr<Set<ValueType>> A set view of the values contained in this map.
     */
    [[nodiscard]] std::unique_ptr<Set<ValueType>> values() const override;

    /**
     * @brief Returns a vector containing all the key-value pairs in this map.
     *
     * @return std::unique_ptr<Set<std::pair<KeyType, ValueType>>> A set view of the key-value pairs contained in this
     * map.
     */
    [[nodiscard]] std::unique_ptr<Set<Pair<KeyType, ValueType>>> entry_set() const override;

    /**
     * @brief Const forward iterator for the tree map.
     *
     * This iterator provides forward traversal capabilities for the tree map,
     * with read-only access to the data.
     */
    class ConstIterator : public Map<KeyType, ValueType>::ConstIterator
    {
    public:
        static constexpr iterator::type type = iterator::FORWARD;

        /**
         * @brief copy constructor
         * Complexity:O(1)
         * @param other other iterator
         */
        ConstIterator(const ConstIterator& other);

        /**
         * This method allows you to access and modify the value at the current position of the iterator.
         * @return A reference to the Pair pointed to by the iterator
         */
        const Pair<KeyType, ValueType> &operator*() const override;

        /**
         * This method provides access to the value pointed to by the iterator, similar to dereferencing the iterator.
         * @return A pointer to the Pair pointed to by the iterator.
         */
        const Pair<KeyType, ValueType> *operator->() const override;

        /**
         * This method copy data from another ConstIterator.
         * @param other other iterator
         * @return self
         */
        ConstIterator &operator=(const ConstIterator &other);

        /**
         * This method checks if two iterators are pointing to the same element.
         * @param other other iterator
         * @return true if the current iterator is equal to the other iterator (i.e., they point to the same position);
         * otherwise, false.
         */
        bool operator==(const typename Map<KeyType, ValueType>::ConstIterator &other) const override;

        /**
         * This method checks if two iterators are pointing to different elements.
         * @param other other iterator
         * @return true if the current iterator is not equal to the other iterator (i.e., they point to different
         * positions); otherwise, false.
         */
        bool operator!=(const typename Map<KeyType, ValueType>::ConstIterator &other) const override;

        /**
         * This is the pre-increment operator. It advances the iterator by one position and returns a reference to the
         * modified iterator itself.
         * @return A reference to the updated iterator after it has been incremented.
         */
        ConstIterator &operator++() override;

    private:
        friend class basic_tree_map;
        typename red_black_tree<Pair<KeyType, ValueType>>::ConstIterator m_it;  /** red black tree iterator */

        /**
         * Constructor for outer
         *
         * Because outer message is contained in m_it, so there is no need to save it there again.
         */
        explicit ConstIterator(const typename red_black_tree<Pair<KeyType, ValueType>>::ConstIterator &it);
    };

    /**
     * @brief Returns an iterator to the beginning of the tree map traversal.
     *
     * @return An iterator to the beginning of the traversal.
     */
    ConstIterator begin() const;

    /**
     * @brief Returns an iterator to the ending of the tree map traversal.
     *
     * @return An iterator to the ending of the traversal.
     */
    ConstIterator end() const;
};

template <typename KeyType, typename ValueType=char>
class tree_map : public basic_tree_map<KeyType, ValueType>
{
public:

    using basic_tree_map<KeyType, ValueType>::basic_tree_map;

    /**
     * @brief Copy assignment operator.
     * Assigns the contents of another tree_map to this tree_map.
     *
     * @param other The tree_map to assign from.
     * @return tree_map& A reference to this tree_map.
     */
    explicit tree_map(const Map<KeyType,ValueType> &other) : basic_tree_map<KeyType, ValueType>(other) {}

    /**
     * @brief Move constructor.
     * Initializes the tree_map by moving another tree_map.
     *
     * @param other The tree_map to move from.
     */
    explicit tree_map(Map<KeyType,ValueType> &&other) noexcept : basic_tree_map<KeyType, ValueType>(std::move(other)) {}

    /**
     * @brief Copy assignment operator.
     * Assigns the contents of another tree_map to this tree_map.
     *
     * @param other The tree_map to assign from.
     * @return tree_map& A reference to this tree_map.
     */
    tree_map &operator=(const Map<KeyType, ValueType> &other) override
    {
        basic_tree_map<KeyType, ValueType>::operator=(other);
        return *this;
    }

    /**
     * @brief Move assignment operator.
     * Moves the contents of another tree_map to this tree_map.
     *
     * @param other The tree_map to move from.
     * @return tree_map& A reference to this tree_map.
     */
    tree_map &operator=(Map<KeyType, ValueType> &&other) noexcept override
    {
        basic_tree_map<KeyType, ValueType>::operator=(std::move(other));
        return *this;
    }

    /**
     * @brief Returns a vector containing all the keys in this map.
     *
     * @return std::unique_ptr<Set<KeyType>> A set view of the keys contained in this map.
     */
    [[nodiscard]] std::unique_ptr<Set<KeyType>> key_set() const override;

    /**
     * @brief Returns a vector containing all the values in this map.
     *
     * @return std::unique_ptr<Set<ValueType>> A set view of the values contained in this map.
     */
    [[nodiscard]] std::unique_ptr<Set<ValueType>> values() const override;

    /**
     * @brief Returns a vector containing all the key-value pairs in this map.
     *
     * @return std::unique_ptr<Set<std::pair<KeyType, ValueType>>> A set view of the key-value pairs contained in this map.
     */
    [[nodiscard]] std::unique_ptr<Set<Pair<KeyType, ValueType>>> entry_set() const override;
};

#include "tree_map.tpp"

#endif //TREE_MAP_H
