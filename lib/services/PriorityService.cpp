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
    // LLQueue<Email*> draftEmails = m_outbox->getDraftEmailPtrs();
    // LLQueue<Email*> sentEmails = m_outbox->getSentEmailPtrs();

    while (!inbox.isEmpty()) {
        Email* inboxEmail = inbox.pop();
        if (inboxEmail->getId() != -1) {
            m_priorityQueue.insert(*inboxEmail);
        }
    }

    // for (int i = 0; i < draftEmails.size(); i++) {
    //     Email* draftEmail = draftEmails.dequeue();
    //     if (draftEmail->getId() != -1) {
    //         m_priorityQueue.insert(*draftEmail);
    //     }
    // }

    // for (int i = 0; i < sentEmails.size(); i++) {
    //     Email* sentEmail = sentEmails.dequeue();
    //     if (sentEmail->getId() != -1) {
    //         m_priorityQueue.insert(*sentEmail);
    //     }
    // }
}

void PriorityService::refreshStorage(Inbox* inbox, Outbox* outbox) {
    m_inbox = inbox;
    m_outbox = outbox;
}

