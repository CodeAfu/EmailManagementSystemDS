#include <iostream>

#include "DynArray.hpp"
#include "Email.hpp"

template<typename T>
DynArray<T>::DynArray(size_t initial_capacity, int increment_value)
    : _arr(new T[initial_capacity]), _size(0), _capacity(initial_capacity), _incrementValue(increment_value) {}

template<typename T>
DynArray<T>::DynArray(const DynArray<T>& other)
    : _arr(new T[other._capacity]), _size(other._size), _capacity(other._capacity), _incrementValue(other._incrementValue) {
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
        _incrementValue = other._incrementValue;
    }
    return *this;
}

template<typename T>
DynArray<T>::~DynArray() {
    delete[] _arr;
}

template<typename T>
void DynArray<T>::push_back(const T& item) {
    if (_size >= _capacity) {
        resize();
    }
    _arr[_size++] = item;
}

template<typename T>
void DynArray<T>::reserve(size_t new_capacity) {
    if (new_capacity > _capacity) {
        T* newArr = new T[new_capacity];
        std::copy(_arr, _arr + _size, newArr);
        delete[] _arr;
        _arr = newArr;
        _capacity = new_capacity;
        //std::cout << "[RESIZE] Size: " << _size << " Cap: " << _capacity << std::endl;
    }
}

template<typename T>
void DynArray<T>::resize() {
    reserve(_capacity + _incrementValue);
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