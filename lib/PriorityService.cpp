#include <iostream>

#include "PriorityService.hpp"
#include "Inbox.hpp"
#include "Outbox.hpp"

PriorityService::PriorityService() { }

PriorityService::PriorityService(Inbox* inbox, Outbox* outbox) : m_inbox(inbox), m_outbox(outbox) { }

PriorityService::~PriorityService() { 
    m_inbox = nullptr;
    m_outbox = nullptr;
}

PriorityQueue& PriorityService::getPriorityQueueRef() {
    return m_priorityQueue;
}

void PriorityService::populatePriorityQueue() {
    Stack<Email> inbox = m_inbox->getEmails();
    LLQueue<Email> draftEmails = m_outbox->getDraftEmails();
    LLQueue<Email> sentEmails = m_outbox->getSentEmails();

    for (int i = 0; i < inbox.size(); i++) {
        Email inboxEmail = inbox.pop();
        Email draftEmail = draftEmails.dequeue();
        Email sentEmail = sentEmails.dequeue();

        if (inboxEmail.getId() != -1) {
            m_priorityQueue.insert(inboxEmail);
        }

        if (draftEmail.getId() != -1) {
            m_priorityQueue.insert(draftEmail);
        }

        if (sentEmail.getId() != -1) {
            m_priorityQueue.insert(sentEmail);
        }
    }
}

void PriorityService::refreshStorage(Inbox* inbox, Outbox* outbox) {
    m_inbox = inbox;
    m_outbox = outbox;
}

