#pragma once
#include "ColorFormat.hpp"

#define MAX_SIZE 30

template<typename T>
class ArrQueue {
public:
    ArrQueue() : m_front(-1), m_rear(-1), m_size(0) {
        // ColorFormat::print("ArrQueue Created", Color::BrightMagenta);
    }
    
    ~ArrQueue() {
        // ColorFormat::print("ArrQueue Destroyed", Color::BrightMagenta);
    }
    
public:
    bool isEmpty() const {
        return m_front < 0 || m_front > m_rear;
    }

    bool isFull() const {
        return m_rear == MAX_SIZE - 1;
    }

    T getFront() const {
        if (isEmpty()) {
            throw std::out_of_range("ArrQueue is empty");
        }
        return m_arr[m_front];
    }

    T getRear() const {
        if (isEmpty()) {
            throw std::out_of_range("ArrQueue is empty");
        }
        return m_arr[m_rear];
    }

    void enqueue(const T& val) {
        if (isFull()) {
            ColorFormat::print("ArrQueue is full", Color::Yellow);
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
            ColorFormat::print("ArrQueue is full", Color::Yellow);
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
            ColorFormat::print("ArrQueue is empty", Color::Yellow);
            return T();
        }

        T res = m_arr[m_front];
        m_front++;
        m_size--;

        if (isEmpty()) {
            m_front = m_rear = -1;
        }

        return res;
    }

    T& dequeueRef() {
        if (isEmpty()) {
            throw std::out_of_range("ArrQueue is empty");
        }

        T& res = m_arr[m_front];
        m_front++;
        m_size--;

        if (isEmpty()) {
            m_front = m_rear = -1;
        }

        return res;
    }

    size_t size() const {
        return m_size;
    }

    void display() const {
        if (isEmpty()) {
            ColorFormat::print("ArrQueue is empty", Color::Yellow);
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
    int m_front = -1;
    int m_rear = -1;
    size_t m_size = 0;
};