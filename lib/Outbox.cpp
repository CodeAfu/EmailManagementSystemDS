#include <iostream>

#include "Outbox.hpp"
#include "OutRequest.hpp"
#include "EmailService.hpp"

// LLQueue<Email> Outbox::getDraftEmails() const {
//     LLQueue<Email> emails;


//     Node<OutRequest>* current = m_drafts.getFrontNode();
//     while (current != nullptr) {
//         emails.enqueue(*current->data.email);
//         current = current->next;
//     }

//     return emails;
// }

LLQueue<Email> Outbox::getDraftEmails() const {
    return m_draftEmails;
}

LLQueue<Email>& Outbox::getDraftEmails() {
    return m_draftEmails;
}

LLQueue<Email> Outbox::getSentEmails() const {
    // LLQueue<Email> emails;
    // if (m_sentEmails.isEmpty())
    //     return emails;
    
    // Node<Email>* current = m_sentEmails.getFrontNode();
    // while (current != nullptr) {
    //     emails.enqueue(current->data);
    //     current = current->next;
    // }

    // return emails;
    return m_sentEmails;
}

LLQueue<Email>& Outbox::getSentEmails() {
    return m_sentEmails;
}

Email Outbox::getSentById(int id) {
    Email email;
    Email temp;
    LLQueue<Email> temp_list;

    while (!m_sentEmails.isEmpty()) {
        temp = m_sentEmails.dequeue();
        temp_list.enqueue(temp);

        if (temp.getId() == id) {
            email = temp;
        }
    }
    m_sentEmails = temp_list;
    return email;
}

Email Outbox::getDraftById(int id) {
    Email email;
    Email temp;
    LLQueue<Email> temp_list;

    while (!m_draftEmails.isEmpty()) {
        temp = m_draftEmails.dequeue();
        temp_list.enqueue(temp);

        if (temp.getId() == id) {
            email = temp;
        }
    }
    m_draftEmails = temp_list;
    return email;
}


void Outbox::addDraft(Email& email) {
    email.setIsDraft(true);
    email.setIsSent(false);

    m_draftEmails.enqueue(email);
}

void Outbox::addSentEmail(const Email& email) {
    m_sentEmails.enqueue(email);
}

void Outbox::sendEmail(Email& email, User& receiver) {
    auto& email_service = EmailService::GetInstance();

    email.setIsDraft(false);

    email_service.addRequest(&email, &receiver);
    m_sentEmails.enqueue(email);
    email_service.sendAllRequests(); // TODO: needs to be be revised, called inside main
}

void Outbox::updateDraftEmail(const Email& replace_email) {
    LLQueue<Email> temp;
    
    while (!m_draftEmails.isEmpty()) {
        Email email = m_draftEmails.dequeue();
        if (email.getId() == replace_email.getId()) {
            temp.enqueue(replace_email);
            continue;
        }
        temp.enqueue(email);
    }
    m_draftEmails = temp;
}


bool Outbox::removeDraftById(int id) {
    LLQueue<Email> temp;
    int size = m_draftEmails.size();
    bool removed = false;

    for (size_t i = 0; i < size; i++) {
        if (m_draftEmails.getFront().getId() == id) {
            m_draftEmails.dequeue();
            removed = true;
            continue;
        }
        temp.enqueue(m_draftEmails.dequeue());
    }

    m_draftEmails = temp;
    return removed;
}

bool Outbox::removeSentById(int id) {
    LLQueue<Email> temp;
    int size = m_sentEmails.size();
    bool removed = false;

    for (size_t i = 0; i < size; i++) {
        if (m_sentEmails.getFront().getId() == id) {
            m_sentEmails.dequeue();
            removed = true;
            continue;
        }
        temp.enqueue(m_sentEmails.dequeue());
    }

    m_sentEmails = temp;
    return removed;
}

size_t Outbox::size() const {
    return m_sentEmails.size();
}

size_t Outbox::sizeDrafts() const {
    return m_draftEmails.size();
}