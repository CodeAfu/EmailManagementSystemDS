#pragma once

template <typename T>
class DynArray {
public:
    DynArray(size_t initial_capacity = 5, int increment_value = 5);
    DynArray(const DynArray<T>& other);
    DynArray<T>& operator=(const DynArray<T>& other);
    ~DynArray();

    void push_back(const T& item);
    void reserve(size_t size);
    T& operator[](size_t index);
    const T& operator[](size_t index) const;
    size_t size() const;
    size_t capacity() const;

private:
    void resize();

private:
    T* _arr;
    size_t _size;
    size_t _capacity;
    int _incrementValue;
};
