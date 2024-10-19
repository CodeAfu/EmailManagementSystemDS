#pragma once

// #include "DynArray.hpp"

template<typename T>
class Stack {
public:
    Stack(size_t size = 100);
    ~Stack();
    Stack(const Stack<T>& other);
    void push(const T& item);
    T pop();
    T peek() const;
    size_t getSize() const;
    bool isEmpty() const;

private:
    T* _arr;
    int _topIdx;
    int _size;
};
