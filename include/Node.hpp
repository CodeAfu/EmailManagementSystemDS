#pragma once

template <typename T>
struct Node {
    T data;
    Node* next;

    Node() : next(nullptr) {}
    Node(T data) : data(data), next(nullptr) {}

    void clear() {
        Node* current = this;
        while (current != nullptr) {
            Node* tmp = current->next;
            delete current;
            current = tmp;
        }
    }
};
