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
    m_priorityQueue.clearAll();
    Stack<Email*> inbox = m_inbox->getEmailPtrs();

    while (!inbox.isEmpty()) {
        Email* inboxEmail = inbox.pop();
        if (inboxEmail->getId() != -1) {
            m_priorityQueue.insert(inboxEmail);
        }
    }
}

void PriorityService::refreshStorage(Inbox* inbox) {
    m_inbox = inbox;
}

