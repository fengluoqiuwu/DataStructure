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

/**
 * @brief A generic map interface similar to Java's HashMap, which implement from Map.
 *
 * @tparam KeyType Type of the key used in the map.
 * @tparam ValueType Type of the value stored in the map.
 */
template <typename KeyType, typename ValueType = char>
class hash_node
{
public:
    static bool has_comparator; /** KeyType has comparator */

private:
    friend class basic_hash_map<KeyType, ValueType>;
    size_t size = 0; /** size of hash node */
    linked_list<Pair<KeyType, ValueType>> *list =
        new linked_list<Pair<KeyType, ValueType>>; /** pointer of list of data */
    tree_map<KeyType, ValueType> *map = nullptr; /** pointer of tree map */

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
    void get_keys(KeyType *ptr);

    /**
     * @brief write all values to array of ValueType
     *
     * @param ptr pointer begin to write
     */
    void get_values(ValueType *ptr);

    /**
     * @brief write all pairs to array of std::pair<KeyType,ValueType>
     *
     * @param ptr pointer begin to write
     */
    void get_pairs(std::pair<KeyType, ValueType> *ptr);

    /**
     * @brief check should it change between linked list and tree_map
     */
    void check_type_change();
};

template <typename KeyType, typename ValueType>
bool hash_node<KeyType,ValueType>::has_comparator = utils::has_all_comparisons<KeyType>::value;

/**
 * @brief A generic map similar to Java's HashMap, which implement from Map.
 *
 * @tparam KeyType Type of the key used in the map.
 * @tparam ValueType Type of the value stored in the map.
 */
template <typename KeyType, typename ValueType=char>
class basic_hash_map : public Map<KeyType, ValueType>
{
public:
    /**
     * @brief Default constructor for hash_map.
     * Initializes an empty hash_map.
     */
    basic_hash_map();

    /**
     * @brief Constructor that initializes the hash_map with a list of key-value pairs.
     *
     * @param initialize_list An array of key-value pairs to initialize the map.
     * @param size The size of the initialize_list.
     */
    basic_hash_map(std::pair<KeyType, ValueType> *initialize_list, size_t size);

    /**
     * @brief Constructor that initializes the hash_map from a linked list of key-value pairs.
     *
     * @param initialize_list A linked list of key-value pairs.
     */
    explicit basic_hash_map(linked_list<std::pair<KeyType, ValueType>> initialize_list);

    /**
     * @brief Copy constructor.
     * Initializes the hash_map as a copy of another hash_map.
     *
     * @param other The hash_map to copy from.
     */
    basic_hash_map(const basic_hash_map &other);

    /**
     * @brief Move constructor.
     * Initializes the hash_map by moving another hash_map.
     *
     * @param other The hash_map to move from.
     */
    basic_hash_map(basic_hash_map &&other) noexcept;

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
    basic_hash_map &operator=(const basic_hash_map &other);

    /**
     * @brief Move assignment operator.
     * Moves the contents of another hash_map to this hash_map.
     *
     * @param other The hash_map to move from.
     * @return hash_map& A reference to this hash_map.
     */
    basic_hash_map &operator=(basic_hash_map &&other) noexcept;

    /**
     * @brief Associates the specified value with the specified key in the map.
     *
     * If the map previously contained a mapping for the key, the old value is replaced.
     *
     * @param key The key with which the specified value is to be associated.
     * @param value The value to be associated with the specified key.
     * @return std::optional<ValueType> The previous value associated with key, or std::nullopt if there was no mapping for key.
     */
    std::optional<ValueType> put(const KeyType &key, const ValueType &value) override;

    /**
     * @brief Returns the value to which the specified key is mapped, or std::nullopt if this map contains no mapping for the key.
     *
     * @param key The key whose associated value is to be returned.
     * @return std::optional<ValueType> The value to which the specified key is mapped, or std::nullopt if there is no mapping for the key.
     */
    std::optional<ValueType> get(const KeyType &key) const override;

    /**
     * @brief Removes the mapping for the specified key from this map if present.
     *
     * @param key The key whose mapping is to be removed from the map.
     * @return std::optional<ValueType> The previous value associated with key, or std::nullopt if there was no mapping for key.
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
     * @return std::unique_ptr<Set<std::pair<KeyType, ValueType>>> A set view of the key-value pairs contained in this map.
     */
    [[nodiscard]] std::unique_ptr<Set<std::pair<KeyType, ValueType>>> entry_set() const override;
private:
    size_t size;
    size_t length=16;
    double alpha = 0.75;


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
    hash_map(const hash_map &other) : basic_hash_map<KeyType, ValueType>(other) {}

    /**
     * @brief Move constructor.
     * Initializes the hash_map by moving another hash_map.
     *
     * @param other The hash_map to move from.
     */
    hash_map(hash_map &&other) noexcept : basic_hash_map<KeyType, ValueType>(std::move(other)) {}

    /**
     * @brief Copy assignment operator.
     * Assigns the contents of another hash_map to this hash_map.
     *
     * @param other The hash_map to assign from.
     * @return hash_map& A reference to this hash_map.
     */
    hash_map &operator=(const hash_map &other)
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
    hash_map &operator=(hash_map &&other) noexcept
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
    [[nodiscard]] std::unique_ptr<Set<std::pair<KeyType, ValueType>>> entry_set() const override;
};

#include "hash_map.tpp"

#endif //HASH_MAP_H
