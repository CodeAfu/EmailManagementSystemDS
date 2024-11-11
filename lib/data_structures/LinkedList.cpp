#define _CRT_SECURE_NO_WARNINGS  // Suppress warnings about unsafe functions
#include <iostream>
#include <cstring> // For strcpy_s, strcmp, and strstr
#include "LinkedList.hpp"
#include "Email.hpp"

// Helper structure to store subject counts in a linked list
struct SubjectCountNode {
    char subject[256];
    int count;
    SubjectCountNode* next;

    SubjectCountNode(const char* subj) : count(1), next(nullptr) {
        strcpy_s(subject, sizeof(subject), subj);
    }
};

LinkedList::LinkedList() : head(nullptr) {}

LinkedList::~LinkedList() {
    while (head) {
        Node* temp = head;
        head = head->next;
        delete temp;
    }
    // Removed debug statement for LinkedList destruction
}

void LinkedList::insert(Email* email) {
    Node* newNode = new Node(email);
    if (!head || static_cast<int>(head->email->getPriority()) <= static_cast<int>(email->getPriority())) {
        newNode->next = head;
        head = newNode;
    }
    else {
        Node* current = head;
        while (current->next && static_cast<int>(current->next->email->getPriority()) > static_cast<int>(email->getPriority())) {
            current = current->next;
        }
        newNode->next = current->next;
        current->next = newNode;
    }
}

void LinkedList::display() const {
    Node* current = head;
    if (!current) {
        std::cout << "No emails to display." << std::endl;
        return;
    }
    while (current) {
        current->email->display();
        current = current->next;
    }
}

void LinkedList::displaySubjectSummary() const {
    SubjectCountNode* subjectHead = nullptr;

    Node* current = head;
    while (current) {
        const char* currentSubject = current->email->getSubject();
        SubjectCountNode* subjectCurrent = subjectHead;
        SubjectCountNode* prev = nullptr;
        bool found = false;

        while (subjectCurrent) {
            if (strcmp(subjectCurrent->subject, currentSubject) == 0) {
                subjectCurrent->count++;
                found = true;
                break;
            }
            prev = subjectCurrent;
            subjectCurrent = subjectCurrent->next;
        }

        if (!found) {
            SubjectCountNode* newNode = new SubjectCountNode(currentSubject);
            if (!subjectHead) {
                subjectHead = newNode;
            }
            else {
                prev->next = newNode;
            }
        }
        current = current->next;
    }

    SubjectCountNode* temp = subjectHead;
    while (temp) {
        std::cout << "Subject: " << temp->subject << " - " << temp->count << " emails\n";
        temp = temp->next;
    }

    while (subjectHead) {
        SubjectCountNode* temp = subjectHead;
        subjectHead = subjectHead->next;
        delete temp;
    }
}

bool LinkedList::searchByKeyword(const char* keyword) const {
    Node* current = head;
    bool found = false;

    while (current) {
        if (strstr(current->email->getSubject(), keyword) || strstr(current->email->getBody(), keyword)) {
            current->email->display();
            found = true;
        }
        current = current->next;
    }

    if (!found) {
        std::cout << "No emails found containing the keyword \"" << keyword << "\".\n";
    }
    return found;
}

void LinkedList::sortBySender() {
    if (!head || !head->next) return;

    Node* sorted = nullptr;

    while (head) {
        Node* current = head;
        head = head->next;

        if (!sorted || strcmp(current->email->getSender(), sorted->email->getSender()) < 0) {
            current->next = sorted;
            sorted = current;
        }
        else {
            Node* s = sorted;
            while (s->next && strcmp(s->next->email->getSender(), current->email->getSender()) < 0) {
                s = s->next;
            }
            current->next = s->next;
            s->next = current;
        }
    }
    head = sorted;
}

void LinkedList::markAllAsRead() {
    Node* current = head;
    while (current) {
        current->email->setIsRead(true);
        current = current->next;
    }
}

void LinkedList::markAllAsUnread() {
    Node* current = head;
    while (current) {
        current->email->setIsRead(false);
        current = current->next;
    }
}
