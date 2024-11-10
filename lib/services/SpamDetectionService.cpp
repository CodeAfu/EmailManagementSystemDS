#include <iostream>

#include "Helper.hpp"
#include "EmailQueue.hpp"
#include "Email.hpp"

SpamDetectionService::SpamDetectionService() {}

SpamDetectionService::SpamDetectionService(Inbox* inbox) {
    refresh(inbox);
}

SpamDetectionService::~SpamDetectionService() {

}

void SpamDetectionService::refresh(Inbox* inbox) {
    this->clear();
    m_userInboxPtr = inbox;

    m_inbox = EmailQueue();
    m_spamBox = EmailQueue();

    Stack<Email*> emailPtrs = inbox->getEmailPtrs();

    while (!emailPtrs.isEmpty()) {
        if (detectSpam(*emailPtrs.peek())) {
            emailPtrs.peek()->setIsSpam(true);
            m_spamBox.enqueue(emailPtrs.pop());
        } else {
            m_inbox.enqueue(emailPtrs.pop());
        }
    }
}

void SpamDetectionService::clear() {
    m_inbox.~EmailQueue();
    m_spamBox.~EmailQueue();

}

EmailQueue& SpamDetectionService::getInbox() {
    return m_inbox;
}

EmailQueue& SpamDetectionService::getSpamBox() {
    return m_spamBox;
}

bool SpamDetectionService::detectSpam(const Email& email) {
    std::string spamKeywords[] = {"lottery", "win", "prize", "free", "urgent", "click here"};
    for (const std::string& keyword : spamKeywords) {
        if (Formatter::toLower(email.getSubject()).find(keyword) != std::string::npos 
            || Formatter::toLower(email.getBody()).find(keyword) != std::string::npos) {
            return true;
        }
    }
    return false;
}

void SpamDetectionService::filterSpam() {
    EmailQueue tempQueue;
    while (!m_inbox.isEmpty()) {
        Email* emailPtr = m_inbox.dequeue();

        if (emailPtr == nullptr) {
            continue;
        }
        
        if (detectSpam(*emailPtr)) {
            emailPtr->setIsSpam(true);
            m_spamBox.enqueue(emailPtr);
        } else {
            tempQueue.enqueue(emailPtr);
        }
    }
    while (!tempQueue.isEmpty()) {
        m_inbox.enqueue(tempQueue.dequeue());
    }
}
