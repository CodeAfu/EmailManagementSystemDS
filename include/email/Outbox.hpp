#pragma once

#include "LLQueue.hpp"
#include "EmailRequest.hpp"

class User;

class Outbox {
public:
    Outbox() = default;
    ~Outbox() = default;

public:
    LLQueue<Email> getDraftEmails() const;
    LLQueue<Email>& getDraftEmails();
    LLQueue<Email> getSentEmails() const;
    LLQueue<Email>& getSentEmails();
    Email getSentById(int id);
    Email getDraftById(int id);

    void addDraft(Email& email);
    void addSentEmail(const Email& email);

    int editDraftEmail(int id);
    void sendEmail(Email& email, User& user);

    void updateDraftEmail(const Email& replace_email);

    bool removeDraftById(int id);
    bool removeSentById(int id);

    size_t size() const;
    size_t sizeDrafts() const;

private:
    LLQueue<Email> m_sentEmails;
    LLQueue<Email> m_draftEmails;
};