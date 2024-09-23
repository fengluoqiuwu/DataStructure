//
// Created by Eden_ on 2024/9/18.
//
#pragma once

#include "hash_map.h"
#include "hash_set.h"

template <typename KeyType, typename ValueType>
hash_node<KeyType,ValueType>& hash_node<KeyType, ValueType>::operator=(const hash_node &other)
{
    if (this != &other)
    {
        size=other.size;
        if constexpr(has_comparator) if (map != nullptr){
            delete map;
            map = new hash_map<KeyType, ValueType>(*other.map);
            return *this;
        }

        delete list;
        list = new linked_list(*other.list);
    }
    return *this;
}

template <typename KeyType, typename ValueType>
std::optional<ValueType> hash_node<KeyType, ValueType>::put(const KeyType &key, const ValueType &value)
{
    if constexpr(has_comparator) if (map != nullptr)
    {

        std::optional<ValueType> result = map->put(key, value);
        if (result==std::nullopt)
        {
            size++;
        }
        return result;
    }

    for (auto it = list->begin(); it != list->end(); ++it)
    {
        if (it->key == key)
        {
            auto temp = it->value;
            it->value = value;
            return std::optional<ValueType>(temp);
        }
    }
    list->add(Pair<KeyType, ValueType>(key, value));
    size++;
    check_type_change(true);
    return std::nullopt;
}

template <typename KeyType, typename ValueType>
std::optional<ValueType> hash_node<KeyType, ValueType>::get(const KeyType &key) const
{
    if constexpr(has_comparator) if (map != nullptr)
    {
        return map->get(key);
    }
    for (auto it = list->begin(); it != list->end(); ++it)
    {
        if (it->key == key)
        {
            return std::optional<ValueType>(it->value);
        }
    }
    return std::nullopt;
}

template <typename KeyType, typename ValueType>
std::optional<ValueType> hash_node<KeyType, ValueType>::remove(const KeyType &key)
{
    if constexpr(has_comparator) if (map != nullptr)
    {
        std::optional<ValueType> result = map->remove(key);
        if (result!=std::nullopt)
        {
            size--;
            check_type_change(false);
        }
        return result;
    }

    for (auto it = list->begin(); it != list->end(); ++it)
    {
        if (it->key == key)
        {
            auto temp = it->value;
            list->remove(it);
            size--;
            return std::optional<ValueType>(temp);
        }
    }
    return std::nullopt;
}

template <typename KeyType, typename ValueType>
bool hash_node<KeyType, ValueType>::contains_key(const KeyType &key) const
{
    if constexpr(has_comparator) if (map != nullptr)
    {
        return map->contains_key(key);
    }
    for (auto it = list->begin(); it != list->end(); ++it)
    {
        if (it->key == key)
        {
            return true;
        }
    }
    return false;
}

template <typename KeyType, typename ValueType>
bool hash_node<KeyType, ValueType>::is_empty() const
{
    return size==0;
}

template <typename KeyType, typename ValueType>
std::size_t hash_node<KeyType, ValueType>::get_size() const
{
    return size;
}

template <typename KeyType, typename ValueType>
void hash_node<KeyType, ValueType>::clear()
{
    size = 0;

    if constexpr(has_comparator) if (map != nullptr)
    {
        delete map;
        map=nullptr;
        list=new linked_list<Pair<KeyType, ValueType>>;
        return;
    }
    list->clear();

}

template <typename KeyType, typename ValueType>
void hash_node<KeyType, ValueType>::get_keys(KeyType *ptr) const
{
    if constexpr(has_comparator) if (map != nullptr)
    {
        for (auto it = map->begin(INORDER); it != map->end(INORDER); ++it)
        {
            *ptr = it->key;
            ++ptr;
        }
        return;
    }

    for (auto it = list->begin(); it != list->end(); ++it)
    {
        *ptr = it->key;
        ++ptr;
    }
}

template <typename KeyType, typename ValueType>
void hash_node<KeyType, ValueType>::get_values(ValueType *ptr) const
{
    if constexpr(has_comparator) if (map != nullptr)
    {
        for (auto it = map->begin(INORDER); it != map->end(INORDER); ++it)
        {
            *ptr = it->value;
            ++ptr;
        }
        return;
    }

    for (auto it = list->begin(); it != list->end(); ++it)
    {
        *ptr = it->value;
        ++ptr;
    }
}

template <typename KeyType, typename ValueType>
void hash_node<KeyType, ValueType>::get_pairs(std::pair<KeyType, ValueType> *ptr) const
{
    if constexpr(has_comparator) if (map != nullptr)
    {
        for (auto it = map->begin(INORDER); it != map->end(INORDER); ++it)
        {
            *ptr = std::make_pair(it->key, it->value);
            ++ptr;
        }
        return;
    }

    for (auto it = list->begin(); it != list->end(); ++it)
    {
        *ptr = std::make_pair(it->key, it->value);
        ++ptr;
    }
}

template <typename KeyType, typename ValueType>
void hash_node<KeyType, ValueType>::check_type_change(const bool& add)
{
    if constexpr(has_comparator)
    {
        if constexpr(add)
        {
            if (map==nullptr&&size>up_limit)
            {
                map = new tree_map<KeyType, ValueType>();
                for (auto it = list->begin(); it != list->end(); ++it)
                {
                    map->put(it->key, it->value);
                }
                delete list;
                list = nullptr;
            }
        }
        else
        {
            if (map!=nullptr&&size<down_limit)
            {
                if (size < down_limit)
                {
                    list = new linked_list<Pair<KeyType, ValueType>>;
                    for (auto it = map->begin(INORDER); it != map->end(INORDER); ++it)
                    {
                        list->add(Pair<KeyType, ValueType>(it->key, it->value));
                    }
                    delete map;
                    map = nullptr;
                }
            }
        }
    }
}

template <typename KeyType, typename ValueType>
basic_hash_map<KeyType, ValueType>::basic_hash_map(const double &alpha) : alpha(alpha)
{
    if(alpha<=0)
    {
        throw std::invalid_argument("alpha must be greater than zero");
    }
    array = new hash_node<KeyType, ValueType>[length];
}

template <typename KeyType, typename ValueType>
basic_hash_map<KeyType, ValueType>::basic_hash_map(std::pair<KeyType, ValueType> *initialize_list, size_t size, const double &alpha) : alpha(alpha)
{
    if(alpha<=0)
    {
        throw std::invalid_argument("alpha must be greater than zero");
    }
    length=length*std::exp2(std::max<size_t>(0,std::ceil(std::log2(static_cast<double>(size) /length/alpha))));
    array = new hash_node<KeyType, ValueType>[length];

    for (size_t i=0;i<size;++i)
    {
        basic_hash_map::put(initialize_list[i].first, initialize_list[i].second);
    }
}

template <typename KeyType, typename ValueType>
basic_hash_map<KeyType, ValueType>::basic_hash_map(linked_list<std::pair<KeyType, ValueType>> initialize_list, const double &alpha) : alpha(alpha)
{
    if(alpha<=0)
    {
        throw std::invalid_argument("alpha must be greater than zero");
    }
    length=length*std::exp2(std::max<size_t>(0,std::ceil(std::log2(static_cast<double>(initialize_list.get_size()) /length/alpha))));
    array = new hash_node<KeyType, ValueType>[length];

    for (auto it = initialize_list.begin(); it != initialize_list.end(); ++it)
    {
        basic_hash_map::put(it->key, it->value);
    }
}

template <typename KeyType, typename ValueType>
basic_hash_map<KeyType, ValueType>::basic_hash_map(const basic_hash_map &other)
{
    length=other.length;
    size=other.size;
    alpha=other.alpha;
    array = new hash_node<KeyType, ValueType>[length];

    for (size_t i=0;i<length;++i)
    {
        array[i] = other.array[i];
    }
}

template <typename KeyType, typename ValueType>
basic_hash_map<KeyType, ValueType>::basic_hash_map(basic_hash_map &&other) noexcept
{
    length=other.length;
    size=other.size;
    alpha=other.alpha;
    array=other.array;

    other.length=16;
    other.size=0;
    other.alpha=0.75;
    other.array=new hash_node<KeyType, ValueType>[other.length];
}

template <typename KeyType, typename ValueType>
basic_hash_map<KeyType, ValueType>::~basic_hash_map()
{
    delete[] array;
    array = nullptr;
}

template <typename KeyType, typename ValueType>
basic_hash_map<KeyType, ValueType> &basic_hash_map<KeyType, ValueType>::operator=(const basic_hash_map &other)
{
    if (this != &other)
    {
        delete[] array;

        length=other.length;
        size=other.size;
        alpha=other.alpha;
        array = new hash_node<KeyType, ValueType>[length];

        for (size_t i=0;i<length;++i)
        {
            array[i] = other.array[i];
        }
    }

    return *this;
}

template <typename KeyType, typename ValueType>
basic_hash_map<KeyType, ValueType> &basic_hash_map<KeyType, ValueType>::operator=(basic_hash_map &&other) noexcept
{
    if (this != &other)
    {
        delete[] array;

        length=other.length;
        size=other.size;
        alpha=other.alpha;
        array=other.array;

        other.length=16;
        other.size=0;
        other.alpha=0.75;
        other.array=new hash_node<KeyType, ValueType>[other.length];
    }

    return *this;
}

template <typename KeyType, typename ValueType>
std::optional<ValueType> basic_hash_map<KeyType, ValueType>::put(const KeyType &key, const ValueType &value)
{
    std::optional<ValueType> result = array[get_index(key)].put(key, value);
    if(result==std::nullopt)
    {
        ++size;
        fix_load_factor();
    }
    return result;
}

template <typename KeyType, typename ValueType>
std::optional<ValueType> basic_hash_map<KeyType, ValueType>::get(const KeyType &key) const
{
    return array[get_index(key)].get(key);
}

template <typename KeyType, typename ValueType>
std::optional<ValueType> basic_hash_map<KeyType, ValueType>::remove(const KeyType &key)
{
    std::optional<ValueType> result = array[get_index(key)].remove(key);
    if(result!=std::nullopt)
    {
        --size;
    }
    return result;
}

template <typename KeyType, typename ValueType>
bool basic_hash_map<KeyType, ValueType>::contains_key(const KeyType &key) const
{
    return array[get_index(key)].contains_key(key);
}

template <typename KeyType, typename ValueType>
bool basic_hash_map<KeyType, ValueType>::is_empty() const
{
    return size == 0;
}

template <typename KeyType, typename ValueType>
std::size_t basic_hash_map<KeyType, ValueType>::get_size() const
{
    return size;
}

template <typename KeyType, typename ValueType>
void basic_hash_map<KeyType, ValueType>::clear()
{
    delete[] array;

    length=16;
    size=0;
    array = new hash_node<KeyType, ValueType>[length];
}

template <typename KeyType, typename ValueType>
size_t basic_hash_map<KeyType, ValueType>::get_index(const KeyType &key) const
{
    return std::hash<KeyType>()(key) % length;
}

template <typename KeyType, typename ValueType>
void basic_hash_map<KeyType, ValueType>::fix_load_factor()
{
    if (size < length * alpha)
    {
        return;
    }

    const size_t temp_length=length;
    length*=2;
    auto *new_array = new hash_node<KeyType, ValueType>[length];

    auto arr = new std::pair<KeyType, ValueType>[this->size];
    auto temp = arr;
    for (size_t i=0;i<temp_length;++i)
    {
        this->array[i].get_pairs(temp);
        temp+=this->array[i].get_size();
    }
    for (size_t i=0;i<this->size;++i)
    {
        new_array[get_index(arr[i].first)].put(arr[i].first, arr[i].second);
    }
    delete[] arr;

    delete[] array;
    array = new_array;
}

template <typename KeyType, typename ValueType>
std::unique_ptr<Set<KeyType>> hash_map<KeyType, ValueType>::key_set() const
{
    auto arr = new KeyType[this->size];
    auto temp = arr;
    for (size_t i=0;i<this->length;++i)
    {
        this->array[i].get_keys(temp);
        temp+=this->array[i].get_size();
    }
    auto result = std::make_unique<hash_set<KeyType>>(arr,this->size);
    delete[] arr;
    return result;
}

template <typename KeyType, typename ValueType>
std::unique_ptr<Set<ValueType>> hash_map<KeyType, ValueType>::values() const
{
    auto arr = new ValueType[this->size];
    auto temp = arr;
    for (size_t i=0;i<this->length;++i)
    {
        this->array[i].get_values(temp);
        temp+=this->array[i].get_size();
    }
    auto result = std::make_unique<hash_set<ValueType>>(arr,this->size);
    delete[] arr;
    return result;
}

template <typename KeyType, typename ValueType>
std::unique_ptr<Set<std::pair<KeyType, ValueType>>> hash_map<KeyType, ValueType>::entry_set() const
{
    auto arr = new std::pair<KeyType, ValueType>[this->size];
    auto temp = arr;
    for (size_t i=0;i<this->length;++i)
    {
        this->array[i].get_pairs(temp);
        temp+=this->array[i].get_size();
    }
    auto result = std::make_unique<hash_set<std::pair<KeyType, ValueType>>>(arr,this->size);
    delete[] arr;
    return result;
}
