#pragma once
template <typename T>
struct Node {
    T data;
    Node* next;

    Node() : next(nullptr) {}
    Node(T&& data) : data(std::move(data)), next(nullptr) {}
    Node(const T& data) : data(data), next(nullptr) {}
};
