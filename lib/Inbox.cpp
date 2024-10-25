#include <iostream>
#include <sstream>

#include "Inbox.hpp"

void Inbox::push(const Email& email) {
    m_emails.emplace(email.getId(), email.getSender(), email.getReceiver(), 
                    email.getSubject(), email.getBody());
}

void Inbox::removeEmail() {
    m_emails.pop();
}

Email Inbox::peek() const {
    return m_emails.peek();
}

Email Inbox::pop() {
    return m_emails.pop();
}

void Inbox::displayAll() const {
    Stack<Email> temp = m_emails;
    std::stringstream ss;

    while (!temp.isEmpty()) {
        ss << temp.pop().toString() << std::endl;
    }

    std::cout << ss.str();
}