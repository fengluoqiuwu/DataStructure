//
// Created by Eden_ on 2024/9/18.
//

#ifndef MAP_INTERFACE_H
#define MAP_INTERFACE_H

#include <utility>  // For std::pair
#include <optional> // For std::optional

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
    virtual bool containsKey(const KeyType& key) const = 0;

    /**
     * @brief Returns true if this map contains no key-value mappings.
     *
     * @return true If this map contains no key-value mappings.
     * @return false If this map contains one or more key-value mappings.
     */
    [[nodiscard]] virtual bool isEmpty() const = 0;

    /**
     * @brief Returns the number of key-value mappings in this map.
     *
     * @return std::size_t The number of key-value mappings in this map.
     */
    [[nodiscard]] virtual std::size_t size() const = 0;

    /**
     * @brief Removes all the mappings from this map.
     *
     * The map will be empty after this call returns.
     */
    virtual void clear() = 0;

    /**
     * @brief Returns a vector containing all the keys in this map.
     *
     * @return std::vector<KeyType> A vector view of the keys contained in this map.
     */
    [[nodiscard]] virtual std::vector<KeyType> keySet() const = 0;

    /**
     * @brief Returns a vector containing all the values in this map.
     *
     * @return std::vector<ValueType> A vector view of the values contained in this map.
     */
    [[nodiscard]] virtual std::vector<ValueType> values() const = 0;

    /**
     * @brief Returns a vector containing all the key-value pairs in this map.
     *
     * @return std::vector<std::pair<KeyType, ValueType>> A vector view of the key-value pairs contained in this map.
     */
    [[nodiscard]] virtual std::vector<std::pair<KeyType, ValueType>> entrySet() const = 0;
};

#endif // MAP_INTERFACE_H
