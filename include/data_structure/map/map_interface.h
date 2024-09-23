//
// Created by Eden_ on 2024/9/18.
//

#ifndef MAP_INTERFACE_H
#define MAP_INTERFACE_H

#include <optional> // For std::optional
#include "set_interface.h"

/**
 * @brief A pair for map.
 *
 * @tparam KeyType Type of the key used in the map.
 * @tparam ValueType Type of the value stored in the map.
 */
template <typename KeyType, typename ValueType=char>
class Pair
{
public:
    KeyType key;
    ValueType value;

    Pair()= default;
    explicit Pair(const KeyType &key) : key(key) {}
    explicit Pair(const KeyType &key, const ValueType &value) : key(key), value(value) {}

    bool operator==(const Pair &other) const {
        return key == other.key;
    }

    bool operator<(const Pair &other) const {
        return key < other.key;
    }

    bool operator<=(const Pair &other) const {
        return (*this < other) || (*this == other);
    }

    bool operator>(const Pair &other) const {
        return !(*this <= other);
    }

    bool operator>=(const Pair &other) const {
        return !(*this < other);
    }
};

template <typename KeyType, typename ValueType>
struct std::hash<Pair<KeyType, ValueType>>
{
    std::size_t operator()(const Pair<KeyType, ValueType> &s) const { return std::hash<KeyType>()(s.key); }
};

/**
 * @brief A generic map interface similar to Java's Map.
 *
 * @tparam KeyType Type of the key used in the map.
 * @tparam ValueType Type of the value stored in the map.
 */
template<typename KeyType, typename ValueType>
class Map {
public:
    /**
     * @brief Virtual destructor.
     */
    virtual ~Map() = default;

    /**
     * @brief Associates the specified value with the specified key in the map.
     *
     * If the map previously contained a mapping for the key, the old value is replaced.
     *
     * @param key The key with which the specified value is to be associated.
     * @param value The value to be associated with the specified key.
     * @return std::optional<ValueType> The previous value associated with key, or std::nullopt if there was no mapping for key.
     */
    virtual std::optional<ValueType> put(const KeyType& key, const ValueType& value) = 0;

    /**
     * @brief Returns the value to which the specified key is mapped, or std::nullopt if this map contains no mapping for the key.
     *
     * @param key The key whose associated value is to be returned.
     * @return std::optional<ValueType> The value to which the specified key is mapped, or std::nullopt if there is no mapping for the key.
     */
    virtual std::optional<ValueType> get(const KeyType& key) const = 0;

    /**
     * @brief Removes the mapping for the specified key from this map if present.
     *
     * @param key The key whose mapping is to be removed from the map.
     * @return std::optional<ValueType> The previous value associated with key, or std::nullopt if there was no mapping for key.
     */
    virtual std::optional<ValueType> remove(const KeyType& key) = 0;

    /**
     * @brief Returns true if this map contains a mapping for the specified key.
     *
     * @param key The key whose presence in this map is to be tested.
     * @return true If this map contains a mapping for the specified key.
     * @return false If this map does not contain a mapping for the specified key.
     */
    virtual bool contains_key(const KeyType& key) const = 0;

    /**
     * @brief Returns true if this map contains no key-value mappings.
     *
     * @return true If this map contains no key-value mappings.
     * @return false If this map contains one or more key-value mappings.
     */
    [[nodiscard]] virtual bool is_empty() const = 0;

    /**
     * @brief Returns the number of key-value mappings in this map.
     *
     * @return std::size_t The number of key-value mappings in this map.
     */
    [[nodiscard]] virtual std::size_t get_size() const = 0;

    /**
     * @brief Removes all the mappings from this map.
     *
     * The map will be empty after this call returns.
     */
    virtual void clear() = 0;

    /**
     * @brief Returns a vector containing all the keys in this map.
     *
     * @return std::unique_ptr<Set<KeyType>> A unique_ptr of set view of the keys contained in this map.
     */
    [[nodiscard]] virtual std::unique_ptr<Set<KeyType>> key_set() const = 0;

    /**
     * @brief Returns a vector containing all the values in this map.
     *
     * @return std::unique_ptr<Set<ValueType>> A unique_ptr of set view of the values contained in this map.
     */
    [[nodiscard]] virtual std::unique_ptr<Set<ValueType>> values() const = 0;

    /**
     * @brief Returns a vector containing all the key-value pairs in this map.
     *
     * @return std::unique_ptr<Set<std::pair<KeyType, ValueType>>> A unique_ptr of set view of the key-value pairs contained in this map.
     */
    [[nodiscard]] virtual std::unique_ptr<Set<Pair<KeyType, ValueType>>> entry_set() const = 0;
};

#endif // MAP_INTERFACE_H
