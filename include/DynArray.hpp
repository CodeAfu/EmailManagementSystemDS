#pragma once
#include <utility>
#include "ColorFormat.hpp"

template <typename T>
class DynArray {
public:
    DynArray(size_t capacity = 2) : m_arr(nullptr), m_size(0), m_capacity(capacity) {
        reAlloc(capacity);
    }

    ~DynArray() {
        // ColorFormat::print("DynArray Destroyed", Color::Red);
        clear();
    }

    DynArray(const DynArray& other) : m_size(other.m_size), m_capacity(other.m_capacity) {
        // ColorFormat::print("DynArray Copy Constructor Called", Color::Cyan);
        reAlloc(m_capacity);
        for (size_t i = 0; i < m_size; i++) {
            new (&m_arr[i]) T(other.m_arr[i]);
        }
    }

    DynArray(DynArray&& other) noexcept
        : m_arr(std::exchange(other.m_arr, nullptr)),
          m_size(std::exchange(other.m_size, 0)),
          m_capacity(std::exchange(other.m_capacity, 0)) {
        // ColorFormat::print("DynArray Move Constructor Called", Color::Blue);
    }

    DynArray& operator=(const DynArray& other) {
        // ColorFormat::print("DynArray Copy Assignment Operator Called", Color::Cyan);
        if (this != &other) {
            DynArray tmp(other);
            swap(tmp);
        }
        return *this;
    }

    DynArray& operator=(DynArray&& other) noexcept {
        // ColorFormat::print("DynArray Move Assignment Operator Called", Color::Blue);
        if (this != &other) {
            clear();
            m_arr = std::exchange(other.m_arr, nullptr);
            m_size = std::exchange(other.m_size, 0);
            m_capacity = std::exchange(other.m_capacity, 0);
        }
        return *this;
    }

    void pushBack(const T& data) {
        if (m_size >= m_capacity) {
            reAlloc(m_capacity + m_capacity / 2);
        }
        new (&m_arr[m_size]) T(data);
        m_size++;
    }

    void pushBack(T&& data) {
        if (m_size >= m_capacity) {
            reAlloc(m_capacity + m_capacity / 2);
        }
        new (&m_arr[m_size]) T(std::move(data));
        m_size++;
    }

    template<typename... Args>
    void emplaceBack(Args&&... args) {
        if (m_size >= m_capacity) {
            reAlloc(m_capacity + m_capacity / 2);
        }
        new (&m_arr[m_size]) T(std::forward<Args>(args)...);
        m_size++;
    }

    void popBack() {
        if (m_size > 0) {
            m_size--;
            m_arr[m_size].~T();
        }
    }

    T& operator[](size_t index) {
        return m_arr[index];
    }

    const T& operator[](size_t index) const {
        return m_arr[index];
    }

    size_t size() const { return m_size; }
    size_t capacity() const { return m_capacity; }

private:
    void reAlloc(size_t new_capacity) {
        T* new_arr = static_cast<T*>(::operator new(new_capacity * sizeof(T)));
        size_t items_to_copy = (new_capacity < m_size) ? new_capacity : m_size;
        
        for (size_t i = 0; i < items_to_copy; i++) {
            new (&new_arr[i]) T(std::move(m_arr[i]));
        }
        
        for (size_t i = 0; i < m_size; i++) {
            m_arr[i].~T();
        }
        
        ::operator delete(m_arr, m_capacity * sizeof(T));
        m_arr = new_arr;
        m_capacity = new_capacity;
        // ColorFormat::print("DynArray Reallocated: " + std::to_string(new_capacity), Color::Green);
    }

    void clear() {
        for (size_t i = 0; i < m_size; i++) {
            m_arr[i].~T();
        }
        ::operator delete(m_arr, m_capacity * sizeof(T));
        m_arr = nullptr;
        m_size = 0;
        m_capacity = 0;
    }

    void swap(DynArray& other) noexcept {
        std::swap(m_arr, other.m_arr);
        std::swap(m_size, other.m_size);
        std::swap(m_capacity, other.m_capacity);
    }

    T* m_arr;
    size_t m_size;
    size_t m_capacity;
};