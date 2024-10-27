#pragma once

#include "Node.hpp"
#include "ColorFormat.hpp"

template <typename T>
class LLQueue {
public:
    LLQueue() : m_front(nullptr), m_rear(nullptr), m_size(0) {
        // ColorFormat::print("LLQueue Created", Color::BrightYellow   );
    }

    ~LLQueue() {
        // ColorFormat::print("LLQueue Destroyed", Color::Red);
        Node<T>* current = m_front;
        while (current != nullptr) {
            Node<T>* tmp = current->next;

            // if constexpr (std::is_pointer<T>::value) {
            //     current->data = nullptr;
            // }
            
            delete current;
            current = tmp;
        }
    }

    bool isEmpty() const {
        return m_front == nullptr;
    }

    T getFront() const {
        if (isEmpty()) {
            throw std::out_of_range("LLQueue is empty");
        }
        return m_front->data;
    }

    Node<T>* getFrontNode() const {
        if (isEmpty()) {
            throw std::out_of_range("LLQueue is empty");
        }
        return m_front;
    }

    T getRear() const {
        if (isEmpty()) {
            throw std::out_of_range("LLQueue is empty");
        }
        return m_rear->data;
    }

    void enqueue(const T& val) {
        Node<T>* n = new Node<T>(val);
        if (isEmpty()) {
            m_front = m_rear = n;
            m_size++;
            return;
        }

        m_rear->next = n;
        m_rear = n;
        m_size++;
    }

    void enqueue(T&& val) {
        Node<T>* n = new Node<T>(std::move(val));
        if (isEmpty()) {
            m_front = m_rear = n;
        }

        m_rear->next = n;
        m_rear = n;
        m_size++;
    }

    T dequeue() {
        if (isEmpty()) {
            throw std::out_of_range("LLQueue is empty");
        }
        Node<T>* temp = m_front;
        m_front = m_front->next;

        if (m_front == nullptr) {
            m_rear = nullptr;
        }

        T data = temp->data;
        delete temp;
        m_size--;
        return data;
    }

    size_t size() const {
        return m_size;
    }

    private:
    Node<T>* m_front;
    Node<T>* m_rear;
    size_t m_size;
};
