//
// Created by Eden_ on 24-9-5.
//
#pragma once

#include <sstream>
#include "linked_list.h"
#include <nlohmann/json.hpp>

template <typename T>
linked_list<T>::linked_list(){
    head_node->next = tail_node;
    tail_node->previous = head_node;
    size=0;
}

template <typename T>
linked_list<T>::linked_list(const linked_list& other)
{
    head_node->next = tail_node;
    tail_node->previous = head_node;
    size=0;

    Node * temp = other.head_node;
    while (temp->next!=other.tail_node)
    {
        temp=temp->next;
        add(temp->data);
    }
}

template <typename T>
linked_list<T>::linked_list(linked_list&& other) noexcept {
    head_node = other.head_node;
    tail_node = other.tail_node;
    size = other.size;

    other.head_node = new Node(nullptr,nullptr);
    other.tail_node = new Node(nullptr,other.head_node);
    other.head_node->next = other.tail_node;
    other.size = 0;
}

template <typename T>
linked_list<T>::linked_list(T* other, const size_t size)
{
    head_node->next = tail_node;
    tail_node->previous = head_node;
    this->size=0;

    for (size_t i = 0; i < size; i++)
    {
        add(other[i]);
    }
}

template <typename T>
linked_list<T>::~linked_list()
{
    clear();
    head_node = nullptr;
    tail_node = nullptr;
}

template <typename T>
linked_list<T> &linked_list<T>::operator=(const linked_list &other)
{
    if (this != &other)
    {
        clear();
        Node * temp = other.head_node;
        while (temp->next!=other.tail_node)
        {
            temp=temp->next;
            add(temp->data);
        }
    }

    return *this;
}

template <typename T>
linked_list<T> &linked_list<T>::operator=(linked_list &&other) noexcept
{
    if (this != &other)
    {
        clear();
        head_node = other.head_node;
        tail_node = other.tail_node;
        size = other.size;

        other.head_node = new Node(nullptr,nullptr);
        other.tail_node = new Node(nullptr,other.head_node);
        other.head_node->next = other.tail_node;
        other.size = 0;
    }

    return *this;
}

template <typename T>
bool linked_list<T>::operator==(const linked_list &other) const
{
    if (this == &other) return true;

    if (this->size != other.size)
    {
        return false;
    }

    Node * self_temp = head_node->next;
    Node * other_temp = other.head_node->next;
    while (self_temp!=tail_node)
    {
        if (self_temp->data != other_temp->data)
        {
            return false;
        }
        self_temp = self_temp->next;
        other_temp = other_temp->next;
    }
    return true;
}

template <typename T>
void linked_list<T>::add(T value)
{
    tail_node->previous->next = new Node(value, tail_node,tail_node->previous);
    tail_node->previous = tail_node->previous->next;
    size++;
}

template <typename T>
void linked_list<T>::add(const size_t index, T value)
{
    Node * next_node = get_node_pointer(index,true);
    if (next_node == nullptr)
    {
        throw std::out_of_range("index out of range");
    }

    auto * new_node = new Node(value, next_node,next_node->previous);
    new_node->next->previous = new_node;
    new_node->previous->next = new_node;
    size++;
}

template <typename T>
T &linked_list<T>::get(const size_t index)
{
    Node * node = get_node_pointer(index,false);
    if (node == nullptr)
    {
        throw std::out_of_range("index out of range");
    }
    return node->data;
}

template <typename T>
const T &linked_list<T>::get(const size_t index) const
{
    Node * node = get_node_pointer(index,false);
    if (node == nullptr)
    {
        throw std::out_of_range("index out of range");
    }
    return node->data;
}

template <typename T>
void linked_list<T>::set(const size_t index, T value)
{
    Node * node = get_node_pointer(index,false);
    if (node == nullptr)
    {
        throw std::out_of_range("index out of range");
    }
    node->data = value;
}

template <typename T>
void linked_list<T>::remove(size_t index)
{
    Node * node = get_node_pointer(index,false);

    if (node == nullptr)
    {
        throw std::out_of_range("index out of range");
    }

    node->next->previous = node->previous;
    node->previous->next = node->next;
    delete node;
    size--;
}

template <typename T>
void linked_list<T>::remove(T value)
{
    Node * temp = head_node->next;
    Node * deleted_node = nullptr;

    while (temp!=tail_node)
    {
        if (temp->data == value)
        {
            temp->next->previous = temp->previous;
            temp->previous->next = temp->next;
            deleted_node = temp;
            temp = temp->next;
            delete deleted_node;
            size--;
        }
        else
        {
            temp = temp->next;
        }
    }
}

template <typename T>
bool linked_list<T>::contains(T value) const
{
    Node * temp = head_node->next;

    while (temp!=tail_node)
    {
        if (temp->data == value)
        {
            return true;
        }
        temp = temp->next;
    }
    return false;
}

template <typename T>
size_t linked_list<T>::get_size() const
{
    return size;
}

template <typename T>
bool linked_list<T>::is_empty() const
{
    return size == 0;
}

template <typename T>
void linked_list<T>::add_first(T value)
{
    auto * new_node = new Node(value, head_node->next,head_node);
    new_node->next->previous = new_node;
    new_node->previous->next = new_node;
    size++;
}

template <typename T>
void linked_list<T>::add_last(T value)
{
    add(value);
}

template <typename T>
void linked_list<T>::remove_first()
{
    if (is_empty())
    {
        std::cout <<"The list is empty."<< __FILE__ << " at line " << __LINE__ <<std::endl;
        throw std::out_of_range("Linked List is empty!");
    }

    Node * temp = head_node->next;
    head_node->next = temp->next;
    temp->next->previous = head_node;
    delete temp;
    size--;
}

template <typename T>
void linked_list<T>::remove_last()
{
    if (is_empty())
    {
        std::cout <<"The list is empty."<< __FILE__ << " at line " << __LINE__ <<std::endl;
        throw std::out_of_range("Linked List is empty!");
    }

    Node * temp = tail_node->previous;
    tail_node->previous = temp->previous;
    temp->previous->next = tail_node;
    delete temp;
    size--;
}

template <typename T>
T &linked_list<T>::get_first()
{
    if (is_empty())
    {
        std::cout <<"The list is empty."<< __FILE__ << " at line " << __LINE__ <<std::endl;
        throw std::out_of_range("Linked List is empty!");
    }

    return head_node->next->data;
}

template <typename T>
const T &linked_list<T>::get_first() const
{
    if (is_empty())
    {
        std::cout <<"The list is empty."<< __FILE__ << " at line " << __LINE__ <<std::endl;
        throw std::out_of_range("Linked List is empty!");
    }

    return head_node->next->data;
}

template <typename T>
T &linked_list<T>::get_last()
{
    if (is_empty())
    {
        std::cout <<"The list is empty."<< __FILE__ << " at line " << __LINE__ <<std::endl;
        throw std::out_of_range("Linked List is empty!");
    }

    return tail_node->previous->data;
}

template <typename T>
const T &linked_list<T>::get_last() const
{
    if (is_empty())
    {
        std::cout <<"The list is empty."<< __FILE__ << " at line " << __LINE__ <<std::endl;
        throw std::out_of_range("Linked List is empty!");
    }

    return tail_node->previous->data;
}

template <typename T>
T linked_list<T>::pop_first()
{
    if (is_empty())
    {
        std::cout <<"The list is empty."<< __FILE__ << " at line " << __LINE__ <<std::endl;
        throw std::out_of_range("Linked List is empty!");
    }

    T temp = get_first();
    remove_first();
    return temp;
}

template <typename T>
T linked_list<T>::pop_last()
{
    if (is_empty())
    {
        std::cout <<"The list is empty."<< __FILE__ << " at line " << __LINE__ <<std::endl;
        throw std::out_of_range("Linked List is empty!");
    }

    T temp = get_last();
    remove_last();
    return temp;
}

template <typename T>
linked_list<T> linked_list<T>::sublist(const size_t begin, const size_t end) const
{
    if (begin >= end)
    {
        return linked_list();
    }

    if(end > size)
    {
        throw std::out_of_range("sub_list:End is larger than size!");
    }

    auto temp = get_node_pointer(begin,false);
    linked_list result;

    for (auto i = begin; i != end; i++)
    {
        result.add(temp->data);
        temp = temp->next;
    }

    return result;
}

template <typename T>
void linked_list<T>::reverse(const size_t begin, const size_t end) const
{
    if (begin > end||end > size)
    {
        throw std::out_of_range("reverse:Invalid input!");
    }

    auto begin_node = get_node_pointer(begin,true);
    auto end_node = get_node_pointer(end,true)->previous;

    for (auto i = 1; i <= (end-begin)/2; i++)
    {
        std::swap(begin_node->data, end_node->data);
        begin_node = begin_node->next;
        end_node = end_node->previous;
    }
}

template <typename T>
void linked_list<T>::reverse() const
{
    reverse(0,size);
}

template <typename T>
std::string linked_list<T>::to_string() const
{
    // 仅支持特定类型
    if constexpr (!(std::is_same_v<T, int> ||
                    std::is_same_v<T, float> ||
                    std::is_same_v<T, std::string>)) {
        std::cout <<"The function only support int,float,double and string."<< __FILE__<< " at line " << __LINE__ <<std::endl;
        throw std::invalid_argument("Unsupported data type for JSON serialization.");
                    }
    else
    {
        std::ostringstream json_output;

        json_output << "[";  // 开始 JSON 数组
        Node* current = head_node->next;
        bool first = true;

        while (current!=tail_node) {
            if (!first) {
                json_output << ",";  // 分隔多个值
            } else {
                first = false;
            }

            // 判断类型并格式化输出
            if constexpr (std::is_same_v<T, std::string>) {
                json_output << "\"" << current->data << "\"";  // 字符串加双引号
            } else {
                json_output << current->data;  // 数字类型直接输出
            }

            current = current->next;
        }

        json_output << "]";  // 结束 JSON 数组

        return json_output.str();  // 返回 JSON 字符串
    }
}

template <typename T>
linked_list<T> linked_list<T>::from_string(const std::string &str)
{
    nlohmann::json json_array = nlohmann::json::parse(str);

    if (!json_array.is_array()) {
        std::cerr << "Invalid JSON string. Expected an array." << std::endl;
        throw std::invalid_argument("JSON is not an array");
    }

    linked_list list;

    for (const auto& item : json_array) {
        if constexpr (std::is_same_v<T, int>) {
            if (item.is_number_integer()) {
                list.add(item.get<int>());
            } else {
                std::cerr << "JSON value type mismatch for int." << std::endl;
                throw std::invalid_argument("JSON contains non-integer values.");
            }
        } else if constexpr (std::is_same_v<T, float>) {
            if (item.is_number_float()) {
                list.add(item.get<float>());
            } else {
                std::cerr << "JSON value type mismatch for float." << std::endl;
                throw std::invalid_argument("JSON contains non-float values.");
            }
        } else if constexpr (std::is_same_v<T, std::string>) {
            if (item.is_string()) {
                list.add(item.get<std::string>());
            } else {
                std::cerr << "JSON value type mismatch for string." << std::endl;
                throw std::invalid_argument("JSON contains non-string values.");
            }
        } else {
            std::cerr << "Unsupported type for template parameter T." << std::endl;
            throw std::invalid_argument("Unsupported type for JSON conversion.");
        }
    }

    return list;
}

template <typename T>
void linked_list<T>::clear()
{
    Node * temp = head_node->next;
    Node * deleted_node = nullptr;
    while (temp!=tail_node)
    {
        temp->next->previous = temp->previous;
        temp->previous->next = temp->next;
        deleted_node = temp;
        temp = temp->next;
        delete deleted_node;
    }
    size=0;
}

template <typename T>
typename linked_list<T>::Node * linked_list<T>::get_node_pointer(const size_t index, const bool include_tail) const
{
    if(include_tail)
    {
        if(index > size)
        {
            std::cerr << "Index out of range! " << __FILE__ << " at line " << __LINE__ << std::endl;
            return nullptr;
        }//In this situation, index equals to size is valid
    }
    else
    {
        if(index >= size)
        {
            std::cerr << "Index out of range! " << __FILE__ << " at line " << __LINE__ << std::endl;
            return nullptr;
        }//In this situation, index equals to size is not valid
    }

    Node * temp = nullptr;
    if(index<size/2)
    {
        temp = head_node->next;
        for(size_t i = 0; i < index; i++)
        {
            temp = temp->next;
        }
    }
    else {
        temp = tail_node;
        for(size_t i = size;i > index; i--)
        {
            temp = temp->previous;
        }
    }
    return temp;
}

template <typename T>
linked_list<T>::Iterator::Iterator(const Iterator &other): outer(other.outer)
{
    current = other.current;
}


template <typename T>
T& linked_list<T>::Iterator::operator*() const
{
    if (this->current == nullptr||this->current==outer.head_node||this->current==outer.tail_node) {
        throw std::out_of_range("Attempt to dereference an invalid iterator.");
    }
    return this->current->data;
}

template <typename T>
T* linked_list<T>::Iterator::operator->() const
{
    if (this->current == nullptr||this->current==outer.head_node||this->current==outer.tail_node) {
        throw std::out_of_range("Attempt to access an invalid iterator.");
    }
    return &(this->current->data);
}

template <typename T>
typename linked_list<T>::Iterator& linked_list<T>::Iterator::operator=(const Iterator &other)
{
    if (this != &other)
    {
        if (&this->outer!=&other.outer)
        {
            throw std::invalid_argument("Attempt to change outer of Iterator.");
        }
        this->current = other.current;
    }
    return *this;
}

template <typename T>
typename linked_list<T>::Iterator& linked_list<T>::Iterator::operator++()
{
    if (this->current == nullptr||this->current==outer.head_node) {
        throw std::out_of_range("Attempt to increment an invalid iterator.");
    }
    this->current = this->current->next;
    return *this;
}

template <typename T>
typename linked_list<T>::Iterator& linked_list<T>::Iterator::operator--()
{
    if (this->current == nullptr||this->current==outer.head_node || this->current->previous == nullptr) {
        throw std::out_of_range("Attempt to decrement an invalid iterator.");
    }
    this->current = this->current->previous;
    return *this;
}

template <typename T>
linked_list<T>::Iterator::~Iterator() = default;

template <typename T>
linked_list<T>::ConstIterator::ConstIterator(const ConstIterator &other): outer(other.outer)
{
    current = other.current;
}

template <typename T>
linked_list<T>::ConstIterator::ConstIterator(const Iterator &other): outer(other.outer)
{
    current = other.current;
}

template <typename T>
const T& linked_list<T>::ConstIterator::operator*() const
{
    if (this->current == nullptr||this->current==outer.head_node||this->current==outer.tail_node) {
        throw std::out_of_range("Attempt to dereference an invalid iterator.");
    }
    return this->current->data;
}

template <typename T>
const T* linked_list<T>::ConstIterator::operator->() const
{
    if (this->current == nullptr||this->current==outer.head_node||this->current==outer.tail_node) {
        throw std::out_of_range("Attempt to access an invalid iterator.");
    }
    return &(this->current->data);
}

template <typename T>
typename linked_list<T>::ConstIterator& linked_list<T>::ConstIterator::operator=(const ConstIterator &other)
{
    if (this != &other)
    {
        if (&this->outer!=&other.outer)
        {
            throw std::invalid_argument("Attempt to change outer of Iterator.");
        }
        this->current = other.current;
    }
    return *this;
}

template <typename T>
typename linked_list<T>::ConstIterator& linked_list<T>::ConstIterator::operator=(const Iterator &other)
{
    if (&this->outer!=&other.outer)
    {
        throw std::invalid_argument("Attempt to change outer of Iterator.");
    }
    this->current = other.current;
    return *this;
}

template <typename T>
typename linked_list<T>::ConstIterator& linked_list<T>::ConstIterator::operator++()
{
    if (this->current == nullptr||this->current==outer.head_node) {
        throw std::out_of_range("Attempt to increment an invalid iterator.");
    }
    this->current = this->current->next;
    return *this;
}

template <typename T>
typename linked_list<T>::ConstIterator& linked_list<T>::ConstIterator::operator--()
{
    if (this->current == nullptr||this->current==outer.head_node || this->current->previous == nullptr) {
        throw std::out_of_range("Attempt to decrement an invalid iterator.");
    }
    this->current = this->current->previous;
    return *this;
}

template <typename T>
linked_list<T>::ConstIterator::~ConstIterator() = default;

template <typename T>
typename linked_list<T>::Iterator linked_list<T>::begin()
{
    return Iterator(head_node->next,*this);
}

template <typename T>
typename linked_list<T>::Iterator linked_list<T>::end()
{
    return Iterator(tail_node,*this);
}

template <typename T>
typename linked_list<T>::ConstIterator linked_list<T>::begin() const
{
    return ConstIterator(head_node->next,*this);
}

template <typename T>
typename linked_list<T>::ConstIterator linked_list<T>::end() const
{
    return ConstIterator(tail_node,*this);
}

template <typename T>
void linked_list<T>::remove(const Iterator &it)
{
    Node * node = it.current;

    if (&it.outer!=this)
    {
        throw std::out_of_range("Attempt to remove an invalid class iterator.");
    }

    if (node == nullptr||node==head_node||node==tail_node)
    {
        throw std::out_of_range("index out of range");
    }

    node->next->previous = node->previous;
    node->previous->next = node->next;
    delete node;
    size--;
}

template <typename T>
void linked_list<T>::add(const Iterator &it, const T &value)
{
    Node * node = it.current;

    if (&it.outer!=this)
    {
        throw std::out_of_range("Attempt to remove an invalid class iterator.");
    }

    if (node == nullptr||node==tail_node)
    {
        throw std::out_of_range("index out of range");
    }

    auto * new_node = new Node(value, node->next,node);
    new_node->next->previous = new_node;
    new_node->previous->next = new_node;
    size++;
}