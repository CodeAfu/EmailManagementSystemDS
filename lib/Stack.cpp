#include <iostream>

#include "Stack.hpp"
#include "Email.hpp"

template<typename T>
Stack<T>::Stack() 
    : _arr(new T[_capacity]), _index(-1) {}

template<typename T>
Stack<T>::Stack(size_t initial_capacity, int increment_value) 
    : _arr(new T[initial_capacity]), _index(-1), _capacity(initial_capacity), _incrementValue(increment_value) {}

template<typename T>
Stack<T>::~Stack() {
    delete[] _arr;
}

template<typename T>
void Stack<T>::reserve(size_t size) {
    _capacity = size;
}

template<typename T>
void Stack<T>::setIncrementValue(int value) {
    _incrementValue = value;
}

template<typename T>
void Stack<T>::push(T item) {
    _index++;
    updateCapacity(_capacity + _incrementValue);

    _arr[_index] = item;
    _top = item;
}

template<typename T>
T Stack<T>::pop() const {
    if (isEmpty()) {
        throw std::out_of_range("Stack is empty.");
    }
    T poppedValue = _arr[_index];
    _index--;
    return poppedValue;
}

template<typename T>
T Stack<T>::peek() const{
    return _top;
}

template<typename T>
bool Stack<T>::isEmpty() const {
    return _index < 0;
}

template<typename T>
void Stack<T>::updateCapacity(size_t newSize) {
    if (!isIndexOutOfBounds()) {
        return;
    }

    T* newArr = new T[newSize];
    std::copy(_arr, _arr + _index + 1, newArr);
    delete[] _arr;
    _arr = newArr;
    _capacity = newSize;
}

template<typename T>
bool Stack<T>::isIndexOutOfBounds() {
    return _index >= _capacity - 1;
}

template class Stack<Email>;
template class Stack<std::string>;