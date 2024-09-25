//
// Created by Eden_ on 2024/9/18.
//

#ifndef HASH_MAP_H
#define HASH_MAP_H

#include <optional>
#include <utility> // For std::pair
#include "map_interface.h"
#include "linked_list.h"
#include "utils.h"

template <typename KeyType, typename ValueType>
class basic_hash_map;

template <typename KeyType, typename ValueType>
class hash_map;

/**
 * @brief hash_node of basic_hash_map.
 *
 * @tparam KeyType Type of the key used in the map.
 * @tparam ValueType Type of the value stored in the map.
 */
template <typename KeyType, typename ValueType = char>
class hash_node
{
public:
    static constexpr bool has_comparator = utils::has_all_comparisons<KeyType>::value; /** KeyType has comparator */

    /**
     * @brief Default constructor
     */
    hash_node() = default;

    /**
     * @brief Copy operator
     *
     * @param other hash_node to copy from
     */
    hash_node& operator=(const hash_node &other);

    /**
     * @brief check if it data structure is list or not
     * @return if it data structure is list or not
     */
    bool is_list(){ return map==nullptr;}

private:
    friend class basic_hash_map<KeyType, ValueType>;
    friend class hash_map<KeyType, ValueType>;
    size_t size = 0; /** size of hash node */
    linked_list<Pair<KeyType, ValueType>> *list =
        new linked_list<Pair<KeyType, ValueType>>; /** pointer of list of data */
    tree_map<KeyType, ValueType> *map = nullptr; /** pointer of tree map */
    static constexpr size_t up_limit = 8; /** up limit to change linked_list to tree */
    static constexpr size_t down_limit = 6; /** down limit to change tree to linked_list */

    /**
     * @brief Associates the specified value with the specified key in the map.
     *
     * If the map previously contained a mapping for the key, the old value is replaced.
     *
     * @param key The key with which the specified value is to be associated.
     * @param value The values to be associated with the specified key.
     * @return std::optional<ValueType> The previous value associated with key, or std::nullopt if there was no mapping
     * for key.
     */
    std::optional<ValueType> put(const KeyType &key, const ValueType &value);

    /**
     * @brief Returns the value to which the specified key is mapped, or std::nullopt if this map contains no mapping
     * for the key.
     *
     * @param key The key whose associated value is to be returned.
     * @return std::optional<ValueType> The value to which the specified key is mapped, or std::nullopt if there is no
     * mapping for the key.
     */
    std::optional<ValueType> get(const KeyType &key) const;

    /**
     * @brief Removes the mapping for the specified key from this map if present.
     *
     * @param key The key whose mapping is to be removed from the map.
     * @return std::optional<ValueType> The previous value associated with key, or std::nullopt if there was no mapping
     * for key.
     */
    std::optional<ValueType> remove(const KeyType &key);

    /**
     * @brief Returns true if this map contains a mapping for the specified key.
     *
     * @param key The key whose presence in this map is to be tested.
     * @return true If this map contains a mapping for the specified key.
     * @return false If this map does not contain a mapping for the specified key.
     */
    bool contains_key(const KeyType &key) const;

    /**
     * @brief Returns true if this map contains no key-value mappings.
     *
     * @return true If this map contains no key-value mappings.
     * @return false If this map contains one or more key-value mappings.
     */
    [[nodiscard]] bool is_empty() const;

    /**
     * @brief Returns the number of key-value mappings in this map.
     *
     * @return std::size_t The number of key-value mappings in this map.
     */
    [[nodiscard]] std::size_t get_size() const;

    /**
     * @brief Removes all the mappings from this map.
     *
     * The map will be empty after this call returns.
     */
    void clear();

    /**
     * @brief write all keys to array of KeyType
     *
     * @param ptr pointer begin to write
     */
    void get_keys(KeyType *ptr) const;

    /**
     * @brief write all values to array of ValueType
     *
     * @param ptr pointer begin to write
     */
    void get_values(ValueType *ptr) const;

    /**
     * @brief write all pairs to array of Pair<KeyType,ValueType>
     *
     * @param ptr pointer begin to write
     */
    void get_pairs(Pair<KeyType, ValueType> *ptr) const;

    /**
     * @brief check should it change between linked list and tree_map
     *
     * @param add True if it is adding fix, False if it is removing fix.
     */
    void check_type_change(const bool& add);
};

/**
 * @brief A generic map similar to Java's HashMap, which implement from Map.
 *
 * @tparam KeyType Type of the key used in the map.
 * @tparam ValueType Type of the value stored in the map.
 */
template <typename KeyType, typename ValueType = char>
class basic_hash_map : public Map<KeyType, ValueType>
{
    static_assert(utils::has_hash<KeyType>::value, "KeyType must support std::hash");
public:
    /**
     * @brief Default constructor for hash_map.
     * Initializes an empty hash_map.
     *
     * @param alpha load factor
     */
    explicit basic_hash_map(const double &alpha = 0.75);

    /**
     * @brief Constructor that initializes the hash_map with a list of key-value pairs.
     *
     * @param initialize_list An array of key-value pairs to initialize the map.
     * @param size The size of the initialize_list.
     * @param alpha load factor
     */
    basic_hash_map(std::pair<KeyType, ValueType> *initialize_list, size_t size, const double &alpha = 0.75);

    /**
     * @brief Constructor that initializes the hash_map from a linked list of key-value pairs.
     *
     * @param initialize_list A linked list of key-value pairs.
     * @param alpha load factor
     */
    explicit basic_hash_map(linked_list<std::pair<KeyType, ValueType>> initialize_list, const double &alpha = 0.75);

    /**
     * @brief Copy constructor.
     * Initializes the hash_map as a copy of another hash_map.
     *
     * @param other The hash_map to copy from.
     */
    explicit basic_hash_map(const Map<KeyType,ValueType> &other);

    /**
     * @brief Move constructor.
     * Initializes the hash_map by moving another hash_map.
     *
     * @param other The hash_map to move from.
     */
    explicit basic_hash_map(Map<KeyType,ValueType> &&other) noexcept;

    /**
     * @brief Destructor for the hash_map.
     * Cleans up all resources used by the hash_map.
     */
    ~basic_hash_map() override;

    /**
     * @brief Copy assignment operator.
     * Assigns the contents of another hash_map to this hash_map.
     *
     * @param other The hash_map to assign from.
     * @return hash_map& A reference to this hash_map.
     */
    virtual basic_hash_map &operator=(const Map<KeyType,ValueType> &other);

    /**
     * @brief Move assignment operator.
     * Moves the contents of another hash_map to this hash_map.
     *
     * @param other The hash_map to move from.
     * @return hash_map& A reference to this hash_map.
     */
    virtual basic_hash_map &operator=(Map<KeyType,ValueType> &&other) noexcept;

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
    [[nodiscard]] std::unique_ptr<Set<KeyType>> key_set() const override { return nullptr; }

    /**
     * @brief Returns a vector containing all the values in this map.
     *
     * @return std::unique_ptr<Set<ValueType>> A set view of the values contained in this map.
     */
    [[nodiscard]] std::unique_ptr<Set<ValueType>> values() const override { return nullptr; }

    /**
     * @brief Returns a vector containing all the key-value pairs in this map.
     *
     * @return std::unique_ptr<Set<std::pair<KeyType, ValueType>>> A set view of the key-value pairs contained in this
     * map.
     */
    [[nodiscard]] std::unique_ptr<Set<Pair<KeyType, ValueType>>> entry_set() const override
    {
        return nullptr;
    }

protected:
    size_t size = 0; /** size of hash map */
    size_t length = 16; /** length of hash table */
    double alpha; /** load factor */
    hash_node<KeyType, ValueType> *array; /** hash_node array */

    /**
     * @brief get hash_node index from key
     *
     * @param key key_value
     * @return hash_node index
     */
    size_t get_index(const KeyType &key) const;

    /**
     * @brief fix (resize) hash table to double length
     */
    void fix_load_factor();

    /**
     * @brief get linked list of key
     * @return linked list of key in the map
     */
    linked_list<KeyType> get_keys() const;

public:
    friend class ConstIterator;
    /**
     * @brief Const forward iterator for the hash map.
     *
     * This iterator provides forward traversal capabilities for the hash map,
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
        friend class basic_hash_map;
        size_t current_index;                                                   /** current index in hash table */
        const basic_hash_map &outer;                                            /** outer class object */
        std::optional<typename linked_list<Pair<KeyType, ValueType>>::ConstIterator> list_it;  /** iterator of linked list */
        std::optional<typename linked_list<Pair<KeyType, ValueType>>::ConstIterator> list_end; /** end iterator of linked list */
        std::optional<typename tree_map<KeyType, ValueType>::ConstIterator> tree_it;           /** iterator of tree map */
        std::optional<typename tree_map<KeyType, ValueType>::ConstIterator> tree_end;          /** end iterator of tree map */

        explicit ConstIterator(const basic_hash_map &outer, const size_t &current_index=0);
        ConstIterator(const basic_hash_map &other,
                      const typename linked_list<Pair<KeyType, ValueType>>::ConstIterator &it,
                      const typename linked_list<Pair<KeyType, ValueType>>::ConstIterator &end_it,
                      size_t current_index = 0);
        ConstIterator(const basic_hash_map &other,
                      const typename tree_map<KeyType, ValueType>::ConstIterator &it,
                      const typename tree_map<KeyType, ValueType>::ConstIterator &end_it,
                      size_t current_index = 0);
    };

    /**
     * @brief Returns an iterator to the beginning of the hash map traversal.
     *
     * @return An iterator to the beginning of the traversal.
     */
    ConstIterator begin() const;

    /**
     * @brief Returns an iterator to the ending of the hash map traversal.
     *
     * @return An iterator to the ending of the traversal.
     */
    ConstIterator end() const;
};

template <typename KeyType, typename ValueType=char>
class hash_map : public basic_hash_map<KeyType, ValueType>
{
public:

    using basic_hash_map<KeyType, ValueType>::basic_hash_map;

    /**
     * @brief Copy constructor.
     * Initializes the hash_map as a copy of another hash_map.
     *
     * @param other The hash_map to copy from.
     */
    explicit hash_map(const Map<KeyType,ValueType> &other) : basic_hash_map<KeyType, ValueType>(other) {}

    /**
     * @brief Move constructor.
     * Initializes the hash_map by moving another hash_map.
     *
     * @param other The hash_map to move from.
     */
    explicit hash_map(Map<KeyType,ValueType> &&other) noexcept : basic_hash_map<KeyType, ValueType>(std::move(other)) {}

    /**
     * @brief Copy assignment operator.
     * Assigns the contents of another hash_map to this hash_map.
     *
     * @param other The hash_map to assign from.
     * @return hash_map& A reference to this hash_map.
     */
    hash_map &operator=(const Map<KeyType, ValueType> &other) override
    {
        basic_hash_map<KeyType, ValueType>::operator=(other);
        return *this;
    }

    /**
     * @brief Move assignment operator.
     * Moves the contents of another hash_map to this hash_map.
     *
     * @param other The hash_map to move from.
     * @return hash_map& A reference to this hash_map.
     */
    hash_map &operator=(Map<KeyType, ValueType> &&other) noexcept override
    {
        basic_hash_map<KeyType, ValueType>::operator=(std::move(other));
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

#include "hash_map.tpp"

#endif //HASH_MAP_H
