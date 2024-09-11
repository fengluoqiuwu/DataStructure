//
// Created by Eden_ on 2024/9/4.
//

#include <sstream>
#include <vector>
#include <algorithm>

#include "array.h"

array::array(const size_t size)
{
    this->size = size;
    data = new int[size];
    std::fill_n(data, size, 0);
}

array::array(const array& other)
{
    this->size = other.size;
    data = new int[size];
    std::copy_n(other.data, size, this->data);
}

array::array(array&& other) noexcept
{
    this->size = other.size;
    this->data = other.data;
    other.data = nullptr;
    other.size = 0;
}

array::array(int* other, size_t size)
{
    this->size = size;
    data = new int[size];
    std::copy_n(other, size, this->data);
}

array::~array()
{
    clear();
}

array& array::operator=(const array& other)
{
    if (this != &other)
    {
        clear();
        this->size = other.size;
        this->data = new int[size];
        std::copy_n(other.data, size, this->data);
    }
    return *this;
}

array& array::operator=(array&& other) noexcept
{
    if (this != &other)
    {
        clear();
        this->size = other.size;
        this->data = other.data;
        other.data = nullptr;
    }

    return *this;
}

bool array::operator==(const array& other) const
{
    if (this == &other) return true;

    if (this->size != other.size)
    {
        return false;
    }
    for (int i = 0; i < this->size; i++)
    {
        if (this->data[i] != other.data[i])
        {
            return false;
        }
    }
    return true;
}

int& array::operator[](const size_t index) {
    if (index >= size) {
        throw std::out_of_range("Index out of range");
    }
    return data[index];
}

const int& array::operator[](const size_t index) const {
    if (index >= size) {
        throw std::out_of_range("Index out of range");
    }
    return data[index];
}

size_t array::get_size() const
{
    return this->size;
}

// ReSharper disable once CppMemberFunctionMayBeConst
void array::sort(const bool ascending)
{
    if (ascending)
    {
        std::sort(data, data + size);
    }
    else
    {
        std::sort(data, data + size, std::greater<>());
    }
}

int array::search(const int key) const
{
    for (auto i = 0; i < size; i++)
    {
        if (data[i] == key)
        {
            return i;
        }
    }
    return -1;
}

size_t array::binary_search(const int key) const
{
    int *left = data, *right = data + size, *mid = nullptr;
    while (left < right)
    {
        mid = left + (right - left) / 2;

        if (key == *mid)
        {
            return static_cast<int>(mid - left);
        }
        if (key < *mid)
        {
            right = mid;
        }
        else
        {
            left = mid + 1;
        }
    }
    return -1;
}

array* array::subarray(const size_t start, const size_t end) const
{
    if (start >= end)
    {
        return new array(0);
    }

    return new array(data + start, end - start);
}

void array::fill(const int value) const
{
    std::fill_n(data, size, value);
}

linked_list<int>* array::to_list() const
{
    return new linked_list<int>(data,size);
}

void array::clear()
{
    delete[] data;
    data = nullptr;
    size = 0;
}

std::string array::to_string() const
{
    std::ostringstream oss;
    oss << "[";
    for (size_t i = 0; i < size; ++i) {
        oss << data[i];
        if (i < size - 1) {
            oss << ",";
        }
    }
    oss << "]";
    return oss.str();
}

array array::from_string(const std::string& str)
{
    std::vector<int> arr;
    std::string number;
    bool isNumber = false;
    bool insideArray = false;

    for (char c : str) {
        if (c == '[') {
            if (insideArray) {
                throw std::runtime_error("Error: Nested arrays are not supported.");
            }
            insideArray = true;
        } else if (c == ']') {
            if (!insideArray) {
                throw std::runtime_error("Error: Closing bracket ']' without opening bracket '['.");
            }
            if (isNumber) {
                arr.push_back(std::stoi(number));
                number.clear();
                isNumber = false;
            }
            insideArray = false;
        } else if (isdigit(c) || c == '-') {
            if (!insideArray) {
                throw std::runtime_error("Error: Numbers found outside of an array.");
            }
            number += c;
            isNumber = true;
        } else if (c == ',') {
            if (!insideArray) {
                throw std::runtime_error("Error: Comma found outside of an array.");
            }
            if (!isNumber) {
                throw std::runtime_error("Error: Comma found without preceding number.");
            }
            arr.push_back(std::stoi(number));
            number.clear();
            isNumber = false;
        } else if (!isspace(c)) {
            throw std::runtime_error("Error: Invalid character found in JSON string.");
        }
    }

    if (insideArray) {
        throw std::runtime_error("Error: Missing closing bracket ']' for array.");
    }

    int array[arr.size()];

    for (size_t i = 0; i < arr.size(); i++)
    {
        array[i] = arr[i];
    }

    return {array, arr.size()};
}

int& array::Iterator::operator*() const
{
    if (this->current<outer.data||this->current >= outer.data+outer.size)
    {
        throw std::runtime_error("Error: Iterator out of range.");
    }

    return *(this->current);
}

int* array::Iterator::operator->() const
{
    if (this->current<outer.data||this->current>=outer.data+outer.size)
    {
        throw std::runtime_error("Error: Iterator out of range.");
    }

    return this->current;
}

array::Iterator& array::Iterator::operator++()
{
    if (this->current<outer.data||this->current>outer.data+outer.size)
    {
        throw std::runtime_error("Error: Iterator out of range.");
    }

    ++(this->current);
    return *this;
}

array::Iterator& array::Iterator::operator--()
{
    if (this->current<outer.data||this->current>outer.data+outer.size)
    {
        throw std::runtime_error("Error: Iterator out of range.");
    }

    --(this->current);
    return *this;
}

array::Iterator::~Iterator() = default;

array::Iterator& array::Iterator::operator+=(size_t n)
{
    if (this->current<outer.data||this->current>outer.data+outer.size)
    {
        throw std::runtime_error("Error: Iterator out of range.");
    }

    this->current += n;
    return *this;
}

array::Iterator& array::Iterator::operator-=(const size_t n)
{
    if (this->current<outer.data||this->current>outer.data+outer.size)
    {
        throw std::runtime_error("Error: Iterator out of range.");
    }

    this->current -= n;
    return *this;
}

array::Iterator array::Iterator::operator+(const size_t n) const
{
    if (this->current<outer.data||this->current>outer.data+outer.size)
    {
        throw std::runtime_error("Error: Iterator out of range.");
    }

    return Iterator(current+n,outer);
}

array::Iterator array::Iterator::operator-(size_t n) const
{
    if (this->current<outer.data||this->current>outer.data+outer.size)
    {
        throw std::runtime_error("Error: Iterator out of range.");
    }

    return Iterator(current-n,outer);
}

bool array::Iterator::operator<(const Iterator& other) const
{
    if (&this->outer!=&other.outer)
    {
        throw std::runtime_error("Error: Can not compare between different array.");
    }
    if (this->current<outer.data||this->current>outer.data+outer.size)
    {
        throw std::runtime_error("Error: Iterator out of range.");
    }
    if (other.current<other.outer.data||other.current>=other.outer.data+other.outer.size)
    {
        throw std::runtime_error("Error: Input Iterator out of range.");
    }

    return this->current < other.current;
}

bool array::Iterator::operator>(const Iterator& other) const
{
    if (&this->outer!=&other.outer)
    {
        throw std::runtime_error("Error: Can not compare between different array.");
    }
    if (this->current<outer.data||this->current>outer.data+outer.size)
    {
        throw std::runtime_error("Error: Iterator out of range.");
    }
    if (other.current<other.outer.data||other.current>=other.outer.data+other.outer.size)
    {
        throw std::runtime_error("Error: Input Iterator out of range.");
    }

    return this->current > other.current;
}

bool array::Iterator::operator<=(const Iterator& other) const
{
    if (&this->outer!=&other.outer)
    {
        throw std::runtime_error("Error: Can not compare between different array.");
    }
    if (this->current<outer.data||this->current>outer.data+outer.size)
    {
        throw std::runtime_error("Error: Iterator out of range.");
    }
    if (other.current<other.outer.data||other.current>=other.outer.data+other.outer.size)
    {
        throw std::runtime_error("Error: Input Iterator out of range.");
    }

    return this->current <= other.current;
}

bool array::Iterator::operator>=(const Iterator& other) const
{
    if (&this->outer!=&other.outer)
    {
        throw std::runtime_error("Error: Can not compare between different array.");
    }
    if (this->current<outer.data||this->current>outer.data+outer.size)
    {
        throw std::runtime_error("Error: Iterator out of range.");
    }
    if (other.current<other.outer.data||other.current>=other.outer.data+other.outer.size)
    {
        throw std::runtime_error("Error: Input Iterator out of range.");
    }

    return this->current >= other.current;
}

size_t array::Iterator::operator-(const Iterator& other) const
{
    if (&this->outer!=&other.outer)
    {
        throw std::runtime_error("Error: Can not minus between different array.");
    }
    if (this->current<outer.data||this->current>outer.data+outer.size)
    {
        throw std::runtime_error("Error: Iterator out of range.");
    }
    if (other.current<other.outer.data||other.current>=other.outer.data+other.outer.size)
    {
        throw std::runtime_error("Error: Input Iterator out of range.");
    }

    return static_cast<size_t>(this->current - other.current);
}

const int& array::ConstIterator::operator*() const
{
    if (this->current<outer.data||this->current>=outer.data+outer.size)
    {
        throw std::runtime_error("Error: Iterator out of range.");
    }

    return *(this->current);
}

const int* array::ConstIterator::operator->() const
{
    if (this->current<outer.data||this->current>=outer.data+outer.size)
    {
        throw std::runtime_error("Error: Iterator out of range.");
    }

    return this->current;
}

array::ConstIterator& array::ConstIterator::operator++()
{
    if (this->current<outer.data||this->current>outer.data+outer.size)
    {
        throw std::runtime_error("Error: Iterator out of range.");
    }

    ++(this->current);
    return *this;
}

array::ConstIterator& array::ConstIterator::operator--()
{
    if (this->current<outer.data||this->current>outer.data+outer.size)
    {
        throw std::runtime_error("Error: Iterator out of range.");
    }

    --(this->current);
    return *this;
}

array::ConstIterator::~ConstIterator() = default;

array::ConstIterator& array::ConstIterator::operator+=(size_t n)
{
    if (this->current<outer.data||this->current>outer.data+outer.size)
    {
        throw std::runtime_error("Error: Iterator out of range.");
    }

    this->current += n;
    return *this;
}

array::ConstIterator& array::ConstIterator::operator-=(size_t n)
{
    if (this->current<outer.data||this->current>outer.data+outer.size)
    {
        throw std::runtime_error("Error: Iterator out of range.");
    }

    this->current -= n;
    return *this;
}

array::ConstIterator array::ConstIterator::operator+(const size_t n) const
{
    if (this->current<outer.data||this->current>outer.data+outer.size)
    {
        throw std::runtime_error("Error: Iterator out of range.");
    }

    return ConstIterator(current+n,outer);
}

array::ConstIterator array::ConstIterator::operator-(const size_t n) const
{
    if (this->current<outer.data||this->current>outer.data+outer.size)
    {
        throw std::runtime_error("Error: Iterator out of range.");
    }

    return ConstIterator(current-n,outer);
}

bool array::ConstIterator::operator<(const ConstIterator& other) const
{
    if (&this->outer!=&other.outer)
    {
        throw std::runtime_error("Error: Can not compare between different array.");
    }
    if (this->current<outer.data||this->current>outer.data+outer.size)
    {
        throw std::runtime_error("Error: Iterator out of range.");
    }
    if (other.current<other.outer.data||other.current>=other.outer.data+other.outer.size)
    {
        throw std::runtime_error("Error: Input Iterator out of range.");
    }

    return this->current < other.current;
}

bool array::ConstIterator::operator>(const ConstIterator& other) const
{
    if (&this->outer!=&other.outer)
    {
        throw std::runtime_error("Error: Can not compare between different array.");
    }
    if (this->current<outer.data||this->current>outer.data+outer.size)
    {
        throw std::runtime_error("Error: Iterator out of range.");
    }
    if (other.current<other.outer.data||other.current>=other.outer.data+other.outer.size)
    {
        throw std::runtime_error("Error: Input Iterator out of range.");
    }

    return this->current > other.current;
}

bool array::ConstIterator::operator<=(const ConstIterator& other) const
{
    if (&this->outer!=&other.outer)
    {
        throw std::runtime_error("Error: Can not compare between different array.");
    }
    if (this->current<outer.data||this->current>outer.data+outer.size)
    {
        throw std::runtime_error("Error: Iterator out of range.");
    }
    if (other.current<other.outer.data||other.current>=other.outer.data+other.outer.size)
    {
        throw std::runtime_error("Error: Input Iterator out of range.");
    }

    return this->current <= other.current;
}

bool array::ConstIterator::operator>=(const ConstIterator& other) const
{
    if (&this->outer!=&other.outer)
    {
        throw std::runtime_error("Error: Can not compare between different array.");
    }
    if (this->current<outer.data||this->current>outer.data+outer.size)
    {
        throw std::runtime_error("Error: Iterator out of range.");
    }
    if (other.current<other.outer.data||other.current>=other.outer.data+other.outer.size)
    {
        throw std::runtime_error("Error: Input Iterator out of range.");
    }

    return this->current >= other.current;
}

size_t array::ConstIterator::operator-(const ConstIterator& other) const
{
    if (&this->outer!=&other.outer)
    {
        throw std::runtime_error("Error: Can not compare between different array.");
    }
    if (this->current<outer.data||this->current>outer.data+outer.size)
    {
        throw std::runtime_error("Error: Iterator out of range.");
    }
    if (other.current<other.outer.data||other.current>=other.outer.data+other.outer.size)
    {
        throw std::runtime_error("Error: Input Iterator out of range.");
    }

    return static_cast<size_t>(this->current - other.current);
}

array::Iterator array::begin()
{
    return Iterator(data,*this);
}

array::Iterator array::end()
{
    return Iterator(data+size,*this);
}

array::ConstIterator array::begin() const
{
    return ConstIterator(data,*this);
}

array::ConstIterator array::end() const
{
    return ConstIterator(data+size,*this);
}