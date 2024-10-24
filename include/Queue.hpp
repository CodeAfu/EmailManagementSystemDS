#pragma once
#include "ColorFormat.hpp"

#define MAX_SIZE 10

template<typename T>
class Queue {
public:
    Queue() : _front(-1), _rear(-1), _size(0) {
        ColorFormat::print("Queue Created", Color::BrightMagenta);
    }
    
    ~Queue() {
        ColorFormat::print("Queue Destroyed", Color::BrightMagenta);
    }
    
public:
    bool isEmpty() const {
        return _front < 0 || _front > _rear;
    }

    bool isFull() const {
        return _rear == MAX_SIZE - 1;
    }

    T getFront() const {
        if (isEmpty()) {
            throw std::out_of_range("Queue is empty");
        }
        return _arr[_front];
    }

    T getRear() const {
        if (isEmpty()) {
            throw std::out_of_range("Queue is empty");
        }
        return _arr[_rear];
    }

    void enqueue(const T& val) {
        if (isFull()) {
            ColorFormat::print("Queue is full", Color::Yellow);
            return;
        }
        if (isEmpty()) {
            _front = 0;
        }
        _size++;
        _arr[++_rear] = val;
    }

    void enqueue(T&& val) {
        if (isFull()) {
            ColorFormat::print("Queue is full", Color::Yellow);
            return;
        }
        if (isEmpty()) {
            _front = 0;
        }
        _size++;
        _arr[++_rear] = std::move(val);  // Move the object to avoid copying
    }

    T dequeue() {
        if (isEmpty()) {
            ColorFormat::print("Queue is empty", Color::Yellow);
            return T();
        }
        T res = _arr[_front++];

        if (isEmpty()) {
            _front = _rear = -1;
        }
        _size--;
        return res;
    }

    T& dequeueRef() {
        if (isEmpty()) {
            throw std::out_of_range("Queue is empty");
        }
        T& res = _arr[_front++];

        if (isEmpty()) {
            _front = _rear = -1;
        }
        _size--;
        return res;
    }

    size_t size() const {
        return _size;
    }

    void display() const {
        if (isEmpty()) {
            ColorFormat::print("Queue is empty", Color::Yellow);
            return;
        }

        std::string s;
        for (size_t i = _front; i <= _rear; i++) {
            s += _arr[i] + " ";
        }

        std::cout << s << std::endl;
    }

private:
    T _arr[MAX_SIZE];
    size_t _front = -1;
    size_t _rear = -1;
    size_t _size = 0;
};