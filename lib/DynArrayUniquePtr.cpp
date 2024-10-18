#include <algorithm>
#include <stdexcept>

#include "DynArrayUniquePtr.hpp"
#include "Email.hpp"

template <typename T>
DynArrayUniquePtr<T>::DynArrayUniquePtr(size_t initial_capacity, int increment_value)
    : _arr(std::make_unique<T[]>(initial_capacity)), 
      _size(0), 
      _capacity(initial_capacity), 
      _incrementValue(increment_value) {}

template <typename T>
DynArrayUniquePtr<T>::DynArrayUniquePtr(const DynArrayUniquePtr<T>& other)
    : _arr(std::make_unique<T[]>(other._capacity)),
      _size(other._size),
      _capacity(other._capacity),
      _incrementValue(other._incrementValue) {
    std::copy(other._arr.get(), other._arr.get() + other._size, _arr.get());
}

template <typename T>
DynArrayUniquePtr<T>& DynArrayUniquePtr<T>::operator=(const DynArrayUniquePtr<T>& other) {
    if (this != &other) {
        DynArrayUniquePtr tmp(other);
        swap(tmp);
    }
    return *this;
}

template <typename T>
void DynArrayUniquePtr<T>::push_back(const T& item) {
    if (_size >= _capacity) {
        resize();
    }
    _arr[_size++] = item;
}

template <typename T>
void DynArrayUniquePtr<T>::reserve(size_t new_capacity) {
    if (new_capacity > _capacity) {
        auto new_arr = std::make_unique<T[]>(new_capacity);
        std::copy(_arr.get(), _arr.get() + _size, new_arr.get());
        _arr = std::move(new_arr);
        _capacity = new_capacity;
    }
}

template <typename T>
T& DynArrayUniquePtr<T>::operator[](size_t index) {
    if (index >= _size) throw std::out_of_range("Index out of bounds");
    return _arr[index];
}

template <typename T>
const T& DynArrayUniquePtr<T>::operator[](size_t index) const {
    if (index >= _size) throw std::out_of_range("Index out of bounds");
    return _arr[index];
}

template <typename T>
size_t DynArrayUniquePtr<T>::size() const { return _size; }

template <typename T>
size_t DynArrayUniquePtr<T>::capacity() const { return _capacity; }

template <typename T>
void DynArrayUniquePtr<T>::resize() {
    reserve(_capacity + _incrementValue);
}

template <typename T>
void DynArrayUniquePtr<T>::swap(DynArrayUniquePtr& other) noexcept {
    using std::swap;
    swap(_arr, other._arr);
    swap(_size, other._size);
    swap(_capacity, other._capacity);
    swap(_incrementValue, other._incrementValue);
}

template class DynArrayUniquePtr<Email>;
template class DynArrayUniquePtr<std::string>;