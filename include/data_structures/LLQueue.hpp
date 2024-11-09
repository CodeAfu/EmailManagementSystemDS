#pragma once

#include "Node.hpp"
#include "ColorFormat.hpp"

template <typename T>
class LLQueue {
public:
    LLQueue() : m_front(nullptr), m_rear(nullptr), m_size(0) {
        // ColorFormat::println("LLQueue Created", Color::BrightYellow   );
    }

    ~LLQueue() {
        // ColorFormat::println("LLQueue Destroyed", Color::Red);
        clear();
    }

        // Copy constructor
    LLQueue(const LLQueue& other) : m_front(nullptr), m_rear(nullptr), m_size(0) {
        // Deep copy by enqueueing each element
        Node<T>* current = other.m_front;
        while (current != nullptr) {
            enqueue(current->data);  // This will copy the data
            current = current->next;
        }
    }

    // Copy assignment
    LLQueue& operator=(const LLQueue& other) {
        if (this != &other) {
            // Clear existing nodes
            clear();
            
            // Deep copy from other
            Node<T>* current = other.m_front;
            while (current != nullptr) {
                enqueue(current->data);
                current = current->next;
            }
        }
        return *this;
    }

    // Move constructor
    LLQueue(LLQueue&& other) noexcept 
        : m_front(other.m_front)
        , m_rear(other.m_rear)
        , m_size(other.m_size) {
        // Nullify other
        other.m_front = nullptr;
        other.m_rear = nullptr;
        other.m_size = 0;
    }

    // Move assignment
    LLQueue& operator=(LLQueue&& other) noexcept {
        if (this != &other) {
            // Clear existing nodes
            clear();
            
            // Take ownership
            m_front = other.m_front;
            m_rear = other.m_rear;
            m_size = other.m_size;
            
            // Nullify other
            other.m_front = nullptr;
            other.m_rear = nullptr;
            other.m_size = 0;
        }
        return *this;
    }

    bool isEmpty() const {
        return m_front == nullptr;
    }

    T getFront() const {
        if (isEmpty()) {
            ColorFormat::println("LLQueue is empty", Color::Yellow);
            return T();
            // throw std::out_of_range("LLQueue is empty");
        }
        return m_front->data;
    }

    Node<T>* getFrontNode() const {
        if (isEmpty()) {
            // ColorFormat::println("LLQueue is empty", Color::Yellow);
            return nullptr;
            // throw std::out_of_range("LLQueue is empty");
        }
        return m_front;
    }

    T getRear() const {
        if (isEmpty()) {
            ColorFormat::println("LLQueue is empty", Color::Yellow);
            return T();
            // throw std::out_of_range("LLQueue is empty");
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
            m_size++;
            return;
        }
        m_rear->next = n;
        m_rear = n;
        m_size++;
    }

    T dequeue() {
        if (isEmpty()) {
            std::cout << "[LLQueue] Queue is Empty\n";
            return T();
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
    void clear() {
        Node<T>* current = m_front;
        while (current != nullptr) {
            Node<T>* tmp = current->next;
            delete current;
            current = tmp;
        }
        m_front = nullptr;
        m_rear = nullptr;
        m_size = 0;
    }

private:
    Node<T>* m_front;
    Node<T>* m_rear;
    size_t m_size;
};
