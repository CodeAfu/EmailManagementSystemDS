#include <iostream>

#include "Stack.hpp"
#include "Email.hpp"

template<typename T>
Stack<T>::Stack(size_t size) : _arr(), _size(size), _topIdx(-1) {
    _arr = new T[_size];
}

template<typename T>
Stack<T>::~Stack() {
    delete[] _arr;    
}

template<typename T>
Stack<T>::Stack(const Stack<T>& other)
    : _arr(other._arr), _topIdx(other._topIdx) {}

template<typename T>
void Stack<T>::push(const T& item) {
    if (_topIdx >= _size - 1) {
        std::cout << "Stack Overflow" << std::endl;
        return;
    }
    _arr[++_topIdx] = item;
}

template<typename T>
T Stack<T>::pop() {
    if (isEmpty()) throw std::out_of_range("Stack underflow");
    return _arr[_topIdx--];
}

template<typename T>
T Stack<T>::peek() const {
    if (isEmpty()) throw std::out_of_range("Stack underflow");
    return _arr[_topIdx];
}

template<typename T>
size_t Stack<T>::getSize() const {
    return _topIdx + 1;
}

template<typename T>
bool Stack<T>::isEmpty() const {
    return _topIdx < 0;
}

template class Stack<std::string>;
template class Stack<Email>;