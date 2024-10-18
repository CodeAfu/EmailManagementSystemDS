#pragma once
#include <memory>
#include <cstddef>

template <typename T>
class DynArrayUniquePtr {
public:
    DynArrayUniquePtr(size_t initial_capacity = 5, int increment_value = 5);
    DynArrayUniquePtr(const DynArrayUniquePtr<T>& other);
    DynArrayUniquePtr<T>& operator=(const DynArrayUniquePtr<T>& other);
    DynArrayUniquePtr(DynArrayUniquePtr&& other) noexcept = default;
    DynArrayUniquePtr& operator=(DynArrayUniquePtr&& other) noexcept = default;

    void push_back(const T& item);
    void reserve(size_t new_capacity);
    T& operator[](size_t index);
    const T& operator[](size_t index) const;
    size_t size() const;
    size_t capacity() const;

private:
    void resize();
    void swap(DynArrayUniquePtr& other) noexcept;

    std::unique_ptr<T[]> _arr;
    size_t _size;
    size_t _capacity;
    int _incrementValue;
};