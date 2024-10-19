#include <iostream>

#include "DynArray.hpp"
#include "Email.hpp"

template<typename T>
DynArray<T>::DynArray(size_t initial_capacity)
    : _arr(new T[initial_capacity]), _size(0), _capacity(initial_capacity) {}

template<typename T>
DynArray<T>::DynArray(const DynArray<T>& other)
    : _arr(new T[other._capacity]), _size(other._size), _capacity(other._capacity) {
    std::copy(other._arr, other._arr + other._size, _arr);
}

template<typename T>
DynArray<T>& DynArray<T>::operator=(const DynArray<T>& other) {
    if (this != &other) {
        T* new_arr = new T[other._capacity];
        std::copy(other._arr, other._arr + other._size, new_arr);
        delete[] _arr;
        _arr = new_arr;
        _size = other._size;
        _capacity = other._capacity;
    }
    return *this;
}

template<typename T>
DynArray<T>::~DynArray() {
    delete[] _arr;
}

template<typename T>
void DynArray<T>::pushBack(const T& item) {
    if (_size >= _capacity) {
        reAlloc(_capacity + _capacity / 2);
    }
    _arr[_size++] = item;
}

template<typename T>
void DynArray<T>::reAlloc(size_t new_capacity) {
    // Allocate Memory
    T* new_block = (T*)::operator new(new_capacity * sizeof(T));

    // For Shrink
    if (new_capacity < _size) {
        _size = new_capacity;
    }

    // Move
    for (size_t i = 0; i < _size; i++) {
        // new_block[i] = std::move(_arr[i]);
        new (new_block + i) T(std::move(_arr[i])); // <-- Use placement new to construct the object
    }
    
    // Clear
    //for (size_t i = 0; i < _size; i++) {
    //    _arr[i].~T();
    //}

    // Delete Old Arr Memory Space
    // ::operator delete(_arr, _capacity * sizeof(T));
    ::operator delete(_arr);

    // Reallocate Arr
    _arr = new_block;
    _capacity = new_capacity;
}

template<typename T>
T& DynArray<T>::operator[](size_t index) {
    return _arr[index];
}

template<typename T>
const T& DynArray<T>::operator[](size_t index) const {
    return _arr[index];
}

template<typename T>
size_t DynArray<T>::size() const {
    return _size;
}

template<typename T>
size_t DynArray<T>::capacity() const {
    return _capacity;
}


template class DynArray<std::string>;
template class DynArray<Email>;