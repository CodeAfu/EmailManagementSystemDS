#include <iostream>

#include "Stack.hpp"
#include "Email.hpp"

template<typename T>
Stack<T>::Stack() : _arr(), _topIdx(-1) {}

template<typename T>
Stack<T>::Stack(const Stack<T>& other)
    : _arr(other._arr), _topIdx(other._topIdx) {}

template<typename T>
void Stack<T>::push(const T& item) {
    _arr.push_back(item);
    _topIdx++;
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