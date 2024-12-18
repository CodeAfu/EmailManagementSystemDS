#pragma once

#include "Email.hpp"
#include "ColorFormat.hpp"
#include "DynArray.hpp"

template <typename T>
class Stack {
public:
    Stack(size_t capacity = 2) : m_arr(capacity), m_topIdx(-1) {}

    ~Stack() {
        // ColorFormat::println("Stack Destroyed", Color::Red);
    }

    Stack(const Stack& other) = default;
    Stack(Stack&& other) noexcept = default;
    Stack& operator=(const Stack& other) = default;
    Stack& operator=(Stack&& other) noexcept = default;

public:

    size_t size() const {
        return m_arr.size();
    }

    bool isEmpty() const {
        return m_topIdx < 0;
    }

    void push(const T& data) {
        m_topIdx++;
        m_arr.pushBack(data);
        // ColorFormat::println("Pushed", Color::Cyan);
    }

    void push(T&& data) {
        m_topIdx++;
        m_arr.pushBack(std::move(data));
        // ColorFormat::println("Pushed", Color::Cyan);
    }

    template<typename... Args>
    void emplace(Args&&... args) {
        m_topIdx++;
        m_arr.emplaceBack(std::forward<Args>(args)...);
        // ColorFormat::println("Emplaced", Color::Cyan);
    }

    T pop() {
        if (isEmpty()) {
            throw std::out_of_range("Stack is empty");
        }

        T result = m_arr[m_topIdx];
        m_arr.popBack();
        m_topIdx--;
        return result;
    }

    T& popRef() { // Not recommended
        if (isEmpty()) {
            throw std::out_of_range("Stack is empty");
        }
        T& result = m_arr[m_topIdx];
        m_arr.popBack();
        m_topIdx--;
        return result;
    }

    T peek() const {
        if (isEmpty()) {
            throw std::out_of_range("Stack is empty");
        }
        return m_arr[m_topIdx];
    }

    T& peek() {
        if (isEmpty()) {
            throw std::out_of_range("Stack is empty");
        }
        return m_arr[m_topIdx];
    }

    T& operator[](size_t index) {
        return m_arr[index];
    }

    const T& operator[](size_t index) const {
        return m_arr[index];
    }

private:
    DynArray<T> m_arr;
    int m_topIdx = -1;
};