#pragma once

#include "EmailQueue.hpp"
#include "Email.hpp"

class SpamDetectionService {
public:
    SpamDetectionService();
    SpamDetectionService(Inbox* inbox);
    ~SpamDetectionService();

    void refresh(Inbox* inbox);
    void clear();

    EmailQueue& getInbox();
    EmailQueue& getSpamBox();

    bool detectSpam(const Email& email);
    void filterSpam();

private:
    Inbox* m_userInboxPtr;

    EmailQueue m_inbox;
    EmailQueue m_spamBox;
};