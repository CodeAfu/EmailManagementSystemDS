#include <iostream>

#include "Email.hpp"
#include "EmailQueue.hpp"


EmailQueue::EmailQueue() : front(nullptr), rear(nullptr) {}

bool EmailQueue::isEmpty() {
    return front == nullptr;
}

size_t EmailQueue::size() {
    return m_size;
}

void EmailQueue::enqueue(Email* email) {
    Node* newNode = new Node(email);
    if (rear == nullptr) {
        front = rear = newNode;
        m_size++;
    } else {
        rear->next = newNode;
        rear = newNode;
        m_size++;
    }
}

Email* EmailQueue::dequeue() {
    if (isEmpty()) {
        ColorFormat::println("[Spam Detection] Queue is empty", Color::Yellow);
        return nullptr;
    }
    Node* temp = front;
    Email* email = front->email;
    front = front->next;
    if (front == nullptr) {
        rear = nullptr;
    }
    delete temp;
    m_size--;
    return email;
}

EmailQueue::~EmailQueue() {
    while (!isEmpty()) {
        dequeue();
    }
}

