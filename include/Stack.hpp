#pragma once

#include "Email.hpp"
#include "ColorFormat.hpp"
#include "DynArray.hpp"

template <typename T>
class Stack {
public:
    Stack(size_t capacity = 2) : _arr(capacity), _topIdx(-1) {}

    ~Stack() {
        ColorFormat::print("Stack Destroyed", Color::Red);
    }

    Stack(const Stack& other) = default;
    Stack(Stack&& other) noexcept = default;
    Stack& operator=(const Stack& other) = default;
    Stack& operator=(Stack&& other) noexcept = default;

public:
    bool isEmpty() const {
        return _topIdx < 0;
    }

    void push(const T& data) {
        _topIdx++;
        _arr.pushBack(data);
        ColorFormat::print("Pushed", Color::Cyan);
    }

    void push(T&& data) {
        _topIdx++;
        _arr.pushBack(std::move(data));
        ColorFormat::print("Pushed", Color::Cyan);
    }

    template<typename... Args>
    void emplace(Args&&... args) {
        _topIdx++;
        _arr.emplaceBack(std::forward<Args>(args)...);
        ColorFormat::print("Emplaced", Color::Cyan);
    }

    T pop() {
        if (isEmpty()) {
            throw std::out_of_range("Stack is empty");
        }
        T result = std::move(_arr[_topIdx]);
        _arr.popBack();
        _topIdx--;
        return result;
    }

    T peek() const {
        if (isEmpty()) {
            throw std::out_of_range("Stack is empty");
        }
        return _arr[_topIdx];
    }

private:
    DynArray<T> _arr;
    int _topIdx = -1;
};