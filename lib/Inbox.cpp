#include <iostream>
#include <sstream>

#include "Inbox.hpp"

void Inbox::push(const Email& email) {
    _emails.emplace(email.getId(), email.getSender(), email.getReceiver(), 
                    email.getSubject(), email.getBody());
}

void Inbox::removeEmail() {
    _emails.pop();
}

Email Inbox::peek() const {
    return _emails.peek();
}

Email Inbox::pop() {
    return _emails.pop();
}

void Inbox::displayAll() const {
    Stack<Email> temp = _emails;
    std::stringstream ss;

    while (!temp.isEmpty()) {
        ss << temp.pop().toString() << std::endl;
    }

    std::cout << ss.str();
}