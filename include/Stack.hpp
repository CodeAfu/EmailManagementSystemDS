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
    T pop();
    T peek() const;
    bool isEmpty() const;
    int getIndex() const;

private:
    // TODO: Test resizing of the array (default = 10:10)
    size_t _capacity = 10;
    int _incrementValue = 10;

private: 
    void updateCapacity(size_t new_size);
    bool isIndexOutOfBounds();

private:
    int _index;
    T _top;
    T* _arr;
};
