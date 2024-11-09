#pragma once

#include "Stack.hpp"

class Inbox {
public:
    Inbox() = default;
    ~Inbox() = default;

    Stack<Email> getEmails() const;
    Stack<Email>& getEmails();
    Stack<Email*> getEmailPtrs();
    void push(const Email& email);
    void removeEmail();
    Email peek() const;
    Email& peek(int idx);
    Email pop();
    void displayAll() const;
    size_t size() const;
    bool isEmpty() const;

private:
    Stack<Email> m_emails;
};