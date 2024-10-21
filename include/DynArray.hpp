#pragma once
#include <utility>
#include "PrintColoring.hpp"

template <typename T>
class DynArray {
public:
    DynArray(size_t capacity = 2) : _arr(nullptr), _size(0), _capacity(capacity) {
        reAlloc(capacity);
    }

    ~DynArray() {
        clear();
        ColorFormat::print("DynArray Destroyed", Color::Red);
    }

    DynArray(const DynArray& other) : _size(other._size), _capacity(other._capacity) {
        reAlloc(_capacity);
        for (size_t i = 0; i < _size; i++) {
            new (&_arr[i]) T(other._arr[i]);
        }
    }

    DynArray(DynArray&& other) noexcept
        : _arr(std::exchange(other._arr, nullptr)),
          _size(std::exchange(other._size, 0)),
          _capacity(std::exchange(other._capacity, 0)) {}

    DynArray& operator=(const DynArray& other) {
        if (this != &other) {
            DynArray tmp(other);
            swap(tmp);
        }
        return *this;
    }

    DynArray& operator=(DynArray&& other) noexcept {
        if (this != &other) {
            clear();
            _arr = std::exchange(other._arr, nullptr);
            _size = std::exchange(other._size, 0);
            _capacity = std::exchange(other._capacity, 0);
        }
        return *this;
    }

    void pushBack(const T& data) {
        if (_size >= _capacity) {
            reAlloc(_capacity + _capacity / 2);
        }
        new (&_arr[_size]) T(data);
        _size++;
    }

    void pushBack(T&& data) {
        if (_size >= _capacity) {
            reAlloc(_capacity + _capacity / 2);
        }
        new (&_arr[_size]) T(std::move(data));
        _size++;
    }

    template<typename... Args>
    void emplaceBack(Args&&... args) {
        if (_size >= _capacity) {
            reAlloc(_capacity + _capacity / 2);
        }
        new (&_arr[_size]) T(std::forward<Args>(args)...);
        _size++;
    }

    void popBack() {
        if (_size > 0) {
            _size--;
            _arr[_size].~T();
        }
    }

    T& operator[](size_t index) {
        return _arr[index];
    }

    const T& operator[](size_t index) const {
        return _arr[index];
    }

    size_t size() const { return _size; }
    size_t capacity() const { return _capacity; }

private:
    void reAlloc(size_t new_capacity) {
        T* new_arr = static_cast<T*>(::operator new(new_capacity * sizeof(T)));
        size_t items_to_copy = (new_capacity < _size) ? new_capacity : _size;
        
        for (size_t i = 0; i < items_to_copy; i++) {
            new (&new_arr[i]) T(std::move(_arr[i]));
        }
        
        for (size_t i = 0; i < _size; i++) {
            _arr[i].~T();
        }
        
        ::operator delete(_arr, _capacity * sizeof(T));
        _arr = new_arr;
        _capacity = new_capacity;
        ColorFormat::print("DynArray Reallocated: " + std::to_string(new_capacity), Color::Green);
    }

    void clear() {
        for (size_t i = 0; i < _size; i++) {
            _arr[i].~T();
        }
        ::operator delete(_arr, _capacity * sizeof(T));
        _arr = nullptr;
        _size = 0;
        _capacity = 0;
    }

    void swap(DynArray& other) noexcept {
        std::swap(_arr, other._arr);
        std::swap(_size, other._size);
        std::swap(_capacity, other._capacity);
    }

    T* _arr;
    size_t _size;
    size_t _capacity;
};