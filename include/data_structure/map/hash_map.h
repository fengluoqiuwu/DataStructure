//
// Created by Eden_ on 2024/9/18.
//

#ifndef HASH_MAP_H
#define HASH_MAP_H

#include <optional>
#include <utility> // For std::pair
#include "map_interface.h"
#include "linked_list.h"

/**
 * @brief A generic map interface similar to Java's HashMap, which implement from Map.
 *
 * @tparam KeyType Type of the key used in the map.
 * @tparam ValueType Type of the value stored in the map.
 */
template <typename KeyType, typename ValueType>
class hash_map : public Map<KeyType, ValueType>
{
public:
    hash_map();
    hash_map(std::pair<KeyType, ValueType> *initialize_list, size_t size);
    explicit hash_map(linked_list<std::pair<KeyType, ValueType>> initialize_list);
    hash_map(const hash_map &other);
    hash_map(hash_map &&other) noexcept ;
    hash_map &operator=(const hash_map &other);
    hash_map &operator=(hash_map &&other);
    ~hash_map();
    std::optional<ValueType> put(const KeyType &key, const ValueType &value) override;
    std::optional<ValueType> get(const KeyType &key) const override;
    std::optional<ValueType> remove(const KeyType &key) override;
    bool containsKey(const KeyType &key) const override;
    [[nodiscard]] bool isEmpty() const override;
    [[nodiscard]] std::size_t size() const override;
    void clear() override;
    [[nodiscard]] Set<KeyType> keySet() const override;
    [[nodiscard]] Set<ValueType> values() const override;
    [[nodiscard]] Set<std::pair<KeyType, ValueType>> entrySet() const override;
private:
    struct hash_head_node
    {
    public:
        linked_list<std::pair<KeyType, ValueType>> *list;

        size_t size=0;
    };
};

#include "hash_map.tpp"

#endif //HASH_MAP_H
