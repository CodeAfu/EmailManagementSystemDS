#pragma once

#include "Email.hpp"

class EmailQueue {
private:

    struct Node {
        Email* email;
        Node* next;
        Node(Email* e) : email(e), next(nullptr) {}
    };

    Node* front;
    Node* rear;
    size_t m_size;

public:
    EmailQueue();
    bool isEmpty();
    size_t size();
    void enqueue(Email* email);
    Email* dequeue();
    ~EmailQueue();
};