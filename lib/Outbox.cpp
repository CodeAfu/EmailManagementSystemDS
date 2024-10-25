#include <iostream>

#include "Outbox.hpp"
#include "OutRequest.hpp"
#include "EmailService.hpp"

LLQueue<Email*> Outbox::getDraftEmails() const {
    LLQueue<Email*> emails;
    if (m_drafts.isEmpty()) 
        return emails;
    Node<OutRequest>* current = m_drafts.getFrontNode();
    while (current != nullptr) {
        emails.enqueue(current->data.email);
        current = current->next;
    }
    return emails;
}

LLQueue<OutRequest> Outbox::getDraftRequests() const {
    LLQueue<OutRequest> requests;
    if (m_drafts.isEmpty())
        return requests;
    
    Node<OutRequest>* current = m_drafts.getFrontNode();
    while (current != nullptr) {
        requests.enqueue(current->data);
        current = current->next;
    }
    return requests;
}

LLQueue<OutRequest>& Outbox::getDraftRequests() {
    return m_drafts;
}

LLQueue<Email*> Outbox::getSentEmails() const {
    LLQueue<Email*> emails;
    if (m_sentEmails.isEmpty())
        return emails;
    
    Node<Email*>* current = m_sentEmails.getFrontNode();
    while (current != nullptr) {
        emails.enqueue(current->data);
        current = current->next;
    }
    return emails;
}

LLQueue<Email*>& Outbox::getSentEmails() {
    return m_sentEmails;
}

void Outbox::addDraft(Email* email, User* user) {
    email->setIsDraft(true);
    email->setIsSent(false);

    m_drafts.enqueue(OutRequest(email, user));
}

void Outbox::addSentEmail(Email* email) {
    m_sentEmails.enqueue(email);
}

void Outbox::sendEmail(Email* email, User* receiver) {
    auto& email_service = EmailService::GetInstance();

    email->setIsDraft(false);
    email->setIsSent(true);

    email_service.addRequest(email, receiver);
    m_sentEmails.enqueue(email);
}


void Outbox::removeEmail(int id) {
    LLQueue<Email*> temp;
    bool removed = false;
    int size = m_sentEmails.size();

    for (size_t i = 0; i < size; i++) {
        if (m_sentEmails.getFront()->getId() == id) {
            m_sentEmails.dequeue();
            continue;
        }
        temp.enqueue(m_sentEmails.dequeue());
    }
    m_sentEmails = temp;
}

size_t Outbox::size() const {
    return m_sentEmails.size();
}

size_t Outbox::sizeDrafts() const {
    return m_drafts.size();
}