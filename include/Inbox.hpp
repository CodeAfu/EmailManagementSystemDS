#pragma once

#include "Stack.hpp"

class Inbox {
public:
    void addEmail(const Email& email) {
        _emails.emplace(email.getId(), email.getSender(), email.getReceiver(), 
                        email.getSubject(), email.getBody());
    }

    void removeEmail() {
        _emails.pop();
    }

    Email peek() const {
        return _emails.peek();
    }

    Email pop() {
        return _emails.pop();
    }

private:
    Stack<Email> _emails;
};