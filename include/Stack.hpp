#pragma once

template<typename T>
class Stack {
public:
    Stack();
    Stack(size_t capacity, int increment_value);
    ~Stack();

public:
    void reserve(size_t size);
    void setIncrementValue(int value);

public:
    void push(T item);
    T pop() const;
    T peek() const;
    bool isEmpty() const;

private:
    size_t _capacity = 10;
    int _incrementValue = 10;

private: 
    void changeCapacity(size_t new_size);
    bool isIndexOutOfBounds();

private:
    int _index;
    T _top;
    T* _arr;
};
