//
// Created by Eden_ on 2024/9/18.
//
#pragma once

#include <utility>


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
            map = new tree_map<KeyType, ValueType>(*other.map);
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
        for (auto it = map->begin(); it != map->end(); ++it)
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
        for (auto it = map->begin(); it != map->end(); ++it)
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
void hash_node<KeyType, ValueType>::get_pairs(Pair<KeyType, ValueType> *ptr) const
{
    if constexpr(has_comparator) if (map != nullptr)
    {
        for (auto it = map->begin(); it != map->end(); ++it)
        {
            *ptr = Pair(it->key, it->value);
            ++ptr;
        }
        return;
    }

    for (auto it = list->begin(); it != list->end(); ++it)
    {
        *ptr = Pair(it->key, it->value);
        ++ptr;
    }
}

template <typename KeyType, typename ValueType>
void hash_node<KeyType, ValueType>::check_type_change(const bool& add)
{
    if constexpr(has_comparator)
    {
        if (add)
        {
            if (map == nullptr && size > up_limit)
            {
                map = new tree_map<KeyType, ValueType>();
                for (auto it = list->begin(); it != list->end(); ++it)
                {
                    map->put(it->key, it->value);
                }
                delete list;
                list = nullptr;
            }
            return;
        }
        if (map != nullptr && size < down_limit)
        {
            list = new linked_list<Pair<KeyType, ValueType>>;
            for (auto it = map->begin(); it != map->end(); ++it)
            {
                list->add(Pair<KeyType, ValueType>(it->key, it->value));
            }
            delete map;
            map = nullptr;
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
        basic_hash_map::put(it->first, it->second);
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

    auto arr = new Pair<KeyType, ValueType>[this->size];
    auto temp = arr;
    for (size_t i=0;i<temp_length;++i)
    {
        this->array[i].get_pairs(temp);
        temp+=this->array[i].get_size();
    }
    for (size_t i=0;i<this->size;++i)
    {
        new_array[get_index(arr[i].key)].put(arr[i].key, arr[i].value);
    }
    delete[] arr;

    delete[] array;
    array = new_array;
}

template <typename KeyType, typename ValueType>
linked_list<KeyType> basic_hash_map<KeyType, ValueType>::get_keys() const
{
    auto arr = new KeyType[this->size];
    auto temp = arr;
    for (size_t i=0;i<this->length;++i)
    {
        this->array[i].get_keys(temp);
        temp+=this->array[i].get_size();
    }
    auto result = linked_list<KeyType>(arr,this->size);
    delete[] arr;
    return result;
}

template <typename KeyType, typename ValueType>
basic_hash_map<KeyType, ValueType>::ConstIterator::ConstIterator(const ConstIterator &other) : outer(other.outer)
{
    current_index=other.current_index;

    if(outer.array[current_index].is_list())
    {
        list_it = other.list_it;
        list_end = other.list_end;
    }
    else
    {
        tree_it = other.tree_it;
        tree_end = other.tree_end;
    }
}

template <typename KeyType, typename ValueType>
const Pair<KeyType, ValueType> &basic_hash_map<KeyType, ValueType>::ConstIterator::operator*() const
{
    if(current_index==outer.length)
    {
        throw std::out_of_range("Iterator::operator*() it point to end iterator.");
    }
    if(outer.array[current_index].is_list())
    {
        return *list_it;
    }
    return *tree_it;
}

template <typename KeyType, typename ValueType>
const Pair<KeyType, ValueType> *basic_hash_map<KeyType, ValueType>::ConstIterator::operator->() const
{
    if(current_index==outer.length)
    {
        throw std::out_of_range("Iterator::operator*() it point to end iterator.");
    }
    if(outer.array[current_index].is_list())
    {
        return &(*list_it);
    }
    return &(*tree_it);
}

template <typename KeyType, typename ValueType>
typename basic_hash_map<KeyType, ValueType>::ConstIterator &
basic_hash_map<KeyType, ValueType>::ConstIterator::operator=(const ConstIterator &other)
{
    if(&outer!=&other.outer)
    {
        throw std::invalid_argument("Attempt to change outer of Iterator.");
    }

    current_index = other.current_index;
    if(outer.array[current_index].is_list())
    {
        list_it = other.list_it;
        list_end = other.list_end;
    }
    else
    {
        tree_it = other.tree_it;
        tree_end = other.tree_end;
    }

    return *this;
}

template <typename KeyType, typename ValueType>
bool basic_hash_map<KeyType, ValueType>::ConstIterator::operator==(const ConstIterator &other) const
{
    if(&outer==&other.outer&&current_index==other.current_index&&current_index==outer.length)
    {
        return true;
    }
    if(outer.array[current_index].is_list())
    {
        return list_it==other.list_it;
    }
    return tree_it==other.tree_it;
}

template <typename KeyType, typename ValueType>
bool basic_hash_map<KeyType, ValueType>::ConstIterator::operator!=(const ConstIterator &other) const
{
    if(&outer==&other.outer&&current_index==other.current_index&&current_index==outer.length)
    {
        return false;
    }
    if(outer.array[current_index].is_list())
    {
        return list_it!=other.list_it;
    }
    return tree_it!=other.tree_it;
}

template <typename KeyType, typename ValueType>
typename basic_hash_map<KeyType, ValueType>::ConstIterator &
basic_hash_map<KeyType, ValueType>::ConstIterator::operator++()
{
    if (outer.array[current_index].is_list())
    {
        ++list_it;
        if (list_it == list_end)
        {
            while (current_index != outer.length && !outer[current_index].is_empty())
            {
                ++current_index;
            }
            if(current_index == outer.length)
            {
                return *this;
            }

            if(outer.array[current_index].is_list())
            {
                list_it = outer.array[current_index].list.begin();
                list_end = outer.array[current_index].list.end();
            }
            else
            {
                tree_it = outer.array[current_index].tree_begin();
                tree_end = outer.array[current_index].tree_end();
            }
        }
    }
    return *this;
}

template <typename KeyType, typename ValueType>
basic_hash_map<KeyType, ValueType>::ConstIterator::ConstIterator(const basic_hash_map &outer, const size_t &current_index) : outer(outer)
{
    this->current_index = current_index;
    while(array[this->current_index].is_empty()&&this->current_index<=outer.length)
    {
        ++this->current_index;
    }
    if(this->current_index==outer.length)
    {
        return;
    }

    if(outer.array[this->current_index].is_list())
    {
        list_it = outer.array[this->current_index].list.begin();
        list_end = outer.array[this->current_index].list.end();
    }
}

template <typename KeyType, typename ValueType>
basic_hash_map<KeyType, ValueType>::ConstIterator::ConstIterator(
    const basic_hash_map &other, const typename linked_list<Pair<KeyType, ValueType>>::ConstIterator &it,
    const typename linked_list<Pair<KeyType, ValueType>>::ConstIterator &end_it, const size_t current_index) :
    current_index(current_index), outer(other)
{
    list_it=it;
    list_end=end_it;
}

template <typename KeyType, typename ValueType>
basic_hash_map<KeyType, ValueType>::ConstIterator::ConstIterator(
    const basic_hash_map &other, const typename tree_map<KeyType, ValueType>::ConstIterator &it,
    const typename tree_map<KeyType, ValueType>::ConstIterator &end_it, const size_t current_index) :
    current_index(current_index), outer(other)
{
    tree_it=it;
    tree_end=end_it;
}

template <typename KeyType, typename ValueType>
typename basic_hash_map<KeyType, ValueType>::ConstIterator basic_hash_map<KeyType, ValueType>::begin() const
{
    return ConstIterator(*this);
}

template <typename KeyType, typename ValueType>
typename basic_hash_map<KeyType, ValueType>::ConstIterator basic_hash_map<KeyType, ValueType>::end() const
{
    return ConstIterator(*this,length);
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
std::unique_ptr<Set<Pair<KeyType, ValueType>>> hash_map<KeyType, ValueType>::entry_set() const
{
    auto arr = new Pair<KeyType, ValueType>[this->size];
    auto temp = arr;
    for (size_t i=0;i<this->length;++i)
    {
        this->array[i].get_pairs(temp);
        temp+=this->array[i].get_size();
    }
    auto result = std::make_unique<hash_set<Pair<KeyType, ValueType>>>(arr,this->size);
    delete[] arr;
    return result;
}
