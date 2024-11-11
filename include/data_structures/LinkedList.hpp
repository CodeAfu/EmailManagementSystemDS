#pragma once
#include <iostream>

class Email;

class LinkedList {
public:
    LinkedList();  // Default constructor
    ~LinkedList(); // Destructor

    void insert(Email* email);
    void display() const;
    void displaySubjectSummary() const;
    bool searchByKeyword(const std::string& keyword) const;
    void sortBySender();
    void markAllAsRead();
    void markAllAsUnread();

private:

    struct Node {
        Email* email;
        Node* next;

        // Constructor to initialize a new node with an email
        Node(Email* email) : email(email), next(nullptr) {}
    };

    Node* head;
};
