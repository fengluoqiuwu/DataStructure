//
// Created by Eden_ on 2024/9/18.
//

#ifndef TREE_MAP_H
#define TREE_MAP_H

#include <optional>
#include "map_interface.h"
#include "red_black_tree.h"

/**
 * @brief A generic map interface similar to Java's TreeMap, which implement from Map.
 *
 * @tparam KeyType Type of the key used in the map.
 * @tparam ValueType Type of the value stored in the map.
 */
template <typename KeyType, typename ValueType>
class tree_map : public Map<KeyType, ValueType> , red_black_tree<Pair<KeyType, ValueType>>
{
public:
    tree_map();
    tree_map(std::pair<KeyType, ValueType> *initialize_list, size_t size);
    explicit tree_map(linked_list<std::pair<KeyType, ValueType>> initialize_list);
    tree_map(const tree_map &other);
    tree_map(tree_map &&other) noexcept;
    tree_map &operator=(const tree_map &other);
    tree_map &operator=(tree_map &&other) noexcept;
    ~tree_map() override;
    std::optional<ValueType> put(const KeyType &key, const ValueType &value) override;
    std::optional<ValueType> get(const KeyType &key) const override;
    std::optional<ValueType> remove(const KeyType &key) override;
    bool contains_key(const KeyType &key) const override;
    using red_black_tree<Pair<KeyType, ValueType>>::is_empty;
    using red_black_tree<Pair<KeyType, ValueType>>::get_size;
    using red_black_tree<Pair<KeyType, ValueType>>::clear;
    [[nodiscard]] Set<KeyType> key_set() const override;
    [[nodiscard]] Set<ValueType> values() const override;
    [[nodiscard]] Set<std::pair<KeyType, ValueType>> entry_set() const override;
};

#include "tree_map.tpp"

#endif //TREE_MAP_H
