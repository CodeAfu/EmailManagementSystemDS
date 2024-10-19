#pragma once

template <typename T>
class DynArray {
public:
    DynArray(size_t initial_capacity = 2);
    DynArray(const DynArray<T>& other);
    DynArray<T>& operator=(const DynArray<T>& other);
    ~DynArray();

    void pushBack(const T& item);
    T& operator[](size_t index);
    const T& operator[](size_t index) const;
    size_t size() const;
    size_t capacity() const;

private:
    void reAlloc(size_t new_capacity);

private:
    T* _arr;
    size_t _size;
    size_t _capacity;
};
