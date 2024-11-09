#include <iostream>
#include <sstream>

#include "Inbox.hpp"

Stack<Email> Inbox::getEmails() const {
    return m_emails;
}

Stack<Email>& Inbox::getEmails() {
    return m_emails;
}

Stack<Email*> Inbox::getEmailPtrs() {
    Stack<Email*> ptrs;

    for (size_t i = 0; i < m_emails.size(); i++) {
        ptrs.push(&m_emails[i]);
    }
    
    return ptrs;
}

void Inbox::push(const Email& email) {
    m_emails.emplace(email.getId(), email.getSender(), email.getReceiver(), 
                     email.getSubject(), email.getBody(), email.getPriority(),
                     email.isImportant(), email.isSent(), email.isSpam(), email.isDraft(), email.isRead());
}

void Inbox::removeEmail() {
    m_emails.pop();
}

Email Inbox::peek() const {
    return m_emails.peek();
}

Email& Inbox::peek(int idx) {
    return m_emails[idx];        
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

size_t Inbox::size() const {
    return m_emails.size();
}

bool Inbox::isEmpty() const {
    return m_emails.isEmpty();
}