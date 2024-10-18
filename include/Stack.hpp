#pragma once

#include "DynArray.hpp"

template<typename T>
class Stack {
public:
    Stack();
    Stack(const Stack<T>& other);
    void push(const T& item);
    T pop();
    T peek() const;
    size_t getSize() const;
    bool isEmpty() const;

private:
    DynArray<T> _arr;
    int _topIdx;
};
