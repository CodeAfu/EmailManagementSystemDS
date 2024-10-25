#include <iostream>

#include "Outbox.hpp"
#include "OutRequest.hpp"
#include "EmailService.hpp"

void Outbox::addEmail(Email& email, User& user) {
    if (EmailService::GetInstance().isAutoSend()) {
        EmailService::GetInstance().sendEmail(&email, &user);
        return;
    }

    if (!m_sendRequests.isFull()) {
        m_sendRequests.enqueue(OutRequest(&email, &user));
        return;
    }
    std::cout << "Outbox limit has been reached. Please free up space by sending emails." << std::endl;
}

void Outbox::removeEmail(int id) {
    Queue<OutRequest> temp;
    bool removed = false;
    int size = m_sendRequests.size();

    for (size_t i = 0; i < size; i++) {
        if (m_sendRequests.peek().email->getId() == id) {
            m_sendRequests.dequeue();
            continue;
        }
        temp.enqueue(m_sendRequests.dequeue());
    }
    m_sendRequests = temp;
}