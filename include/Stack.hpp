#pragma once

template<typename T>
class Stack {
public:
    Stack();
    Stack(size_t capacity, int incrementValue);
    ~Stack();

public:
    void reserve(size_t size);
    void setIncrementValue(int value);

public:
    void push(T item);
    T pop();
    T peek() const;
    bool isEmpty() const;

private:
    size_t _capacity = 20;
    int _incrementValue = 20;

private: 
    void changeCapacity(size_t newSize);
    bool isIndexOutOfBounds();

private:
    int _index;
    T _top;
    T* _arr;
};