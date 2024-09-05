//
// Created by Eden_ on 2024/9/4.
//

#include <sstream>
#include <vector>

#include "DataStructure/data_structure.h"

Array::Array(const size_t size)
{
    this->size = size;
    data = new int[size];
    std::fill(data, data + size, 0);
}

Array::Array(const Array& other)
{
    this->size = other.size;
    data = new int[size];
    std::copy(other.data, other.data + size, this->data);
}

Array::Array(Array&& other) noexcept
{
    this->size = other.size;
    this->data = other.data;
    other.data = nullptr;
}

Array::Array(int* other, size_t size)
{
    this->size = size;
    data = new int[size];
    std::copy(other, other + size, this->data);
}

Array::~Array()
{
    clear();
}

Array& Array::operator=(const Array& other)
{
    if (this != &other)
    {
        clear();
        this->size = other.size;
        this->data = new int[size];
        std::copy(other.data, other.data + size, this->data);
    }
    return *this;
}

Array& Array::operator=(Array&& other) noexcept
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

bool Array::operator==(const Array& other)
{
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

void Array::sort(bool ascending)
{

}

int Array::search(int key)
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

size_t Array::binary_search(int key) const
{
    int *left = data, *right = data + size, *mid = nullptr;
    while (left < right)
    {
        mid = left + (right - left) / 2;

        if (key == *mid)
        {
            return (int)(mid - left);
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

Array* Array::subarray(size_t start, size_t end)
{
    if (start >= end)
    {
        return new Array(0);
    }

    return new Array(data + start, end - start);
}

void Array::fill(int value) const
{
    std::fill(data, data + size, value);
}

LinkedList<int>* Array::toList() const
{
    return new LinkedList<int>(data,size);
}

void Array::clear()
{
    delete[] data;
    data = nullptr;
    size = 0;
}

std::string Array::to_string() const
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

Array Array::form_string(const std::string& str)
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
