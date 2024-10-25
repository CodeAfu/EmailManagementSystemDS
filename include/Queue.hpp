#pragma once
#include "ColorFormat.hpp"

#define MAX_SIZE 30

template<typename T>
class Queue {
public:
    Queue() : m_front(-1), m_rear(-1), m_size(0) {
        // ColorFormat::print("Queue Created", Color::BrightMagenta);
    }
    
    ~Queue() {
        // ColorFormat::print("Queue Destroyed", Color::BrightMagenta);
    }
    
public:
    bool isEmpty() const {
        return m_size <= 0;
    }

    bool isFull() const {
        return m_rear == MAX_SIZE - 1;
    }

    T getFront() const {
        if (isEmpty()) {
            throw std::out_of_range("Queue is empty");
        }
        return m_arr[m_front];
    }

    T getRear() const {
        if (isEmpty()) {
            throw std::out_of_range("Queue is empty");
        }
        return m_arr[m_rear];
    }

    T peek() const {
        if (isEmpty()) {
            throw std::out_of_range("Queue is empty");
        }
        return m_arr[m_front];
    }

    void enqueue(const T& val) {
        if (isFull()) {
            ColorFormat::print("Queue is full", Color::Yellow);
            return;
        }
        if (isEmpty()) {
            m_front = 0;
        }
        m_size++;
        m_arr[++m_rear] = val;
    }

    void enqueue(T&& val) {
        if (isFull()) {
            ColorFormat::print("Queue is full", Color::Yellow);
            return;
        }
        if (isEmpty()) {
            m_front = 0;
        }
        m_size++;
        m_arr[++m_rear] = std::move(val);  // Move the object to avoid copying
    }

    T dequeue() {
        if (isEmpty()) {
            ColorFormat::print("Queue is empty", Color::Yellow);
            return T();
        }
        T res = m_arr[m_front++];

        if (isEmpty()) {
            m_front = m_rear = -1;
        }
        m_size--;
        return res;
    }

    T& dequeueRef() {
        if (isEmpty()) {
            throw std::out_of_range("Queue is empty");
        }
        T& res = m_arr[m_front++];

        if (isEmpty()) {
            m_front = m_rear = -1;
        }
        m_size--;
        return res;
    }

    size_t size() const {
        return m_size;
    }

    void display() const {
        if (isEmpty()) {
            ColorFormat::print("Queue is empty", Color::Yellow);
            return;
        }

        std::string s;
        for (size_t i = m_front; i <= m_rear; i++) {
            s += m_arr[i] + " ";
        }

        std::cout << s << std::endl;
    }

private:
    T m_arr[MAX_SIZE];
    size_t m_front = -1;
    size_t m_rear = -1;
    size_t m_size = 0;
};