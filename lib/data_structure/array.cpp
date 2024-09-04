//
// Created by Eden_ on 2024/9/4.
//

#include "DataStructure/data_structure.h"

Array::Array(const int size) {
    this->size = size;
    data = new int[size];
    std::fill(data, data + size, 0);
}

Array::Array(const Array &other) {
    this->size = other.size;
    data = new int[size];
    std::copy(other.data, other.data + size, this->data);
}

Array::Array(int *other, int size) {
    this->size = size;
    data = new int[size];
    std::copy(other, other + size, this->data);
}

Array::~Array() {
    clear();
    data = nullptr;
    size = 0;
}

void Array::sort(bool ascending) {
}

int Array::search(int key) {
}

int Array::binary_search(int key) {
}

Array * Array::subarray(int start, int end) {
}

bool Array::equals(const Array &other) {
}

void Array::fill(int value) {
}

LinkedList<int> * Array::toList() const {
}

void Array::clear() {
}
