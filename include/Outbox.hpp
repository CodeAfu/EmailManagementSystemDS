#pragma once

#include "LLQueue.hpp"
#include "OutRequest.hpp"

class User;

class Outbox {
public:
    Outbox() = default;
    ~Outbox() = default;

public:
    LLQueue<Email*> getDraftEmails() const;
    LLQueue<OutRequest> getDraftRequests() const;
    LLQueue<OutRequest>& getDraftRequests();
    LLQueue<Email*> getSentEmails() const;
    LLQueue<Email*>& getSentEmails();
    void addDraft(Email* email, User* user);
    void addSentEmail(Email* email);
    void sendEmail(Email* email, User* user);
    void removeByPlacement(int index); // TODO: give a better name
    void removeEmail(int id);

    size_t size() const;
    size_t sizeDrafts() const;

private:
    LLQueue<Email*> m_sentEmails;
    LLQueue<OutRequest> m_drafts;
};