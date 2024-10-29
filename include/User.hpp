#pragma once

#include "Inbox.hpp"
#include "Outbox.hpp"
#include "EmailService.hpp"
#include "PriorityService.hpp"
#include "SpamDetectionService.hpp"
#include "SearchService.hpp"

class Email;

class User {
public:
    User();
    User(int id, std::string name, std::string emailAddress);
    
    ~User();
    
    User(const User& other);
    User& operator=(const User& other);
    User(User&& other) noexcept;
    User& operator=(User&& other) noexcept;

public:
    /// Getters and Setters
    int getId() const;
    std::string getName() const;
    std::string getEmailAddress() const;

    /// Storage
    void viewInbox() const;
    void viewLastFromInbox() const;
    void viewDraftEmails() const;
    void viewSentEmails() const;

    const Inbox& getInbox() const;
    Inbox& getInbox();
    const Outbox& getOutbox() const;
    Outbox& getOutbox();

    Email getFromInbox(int id) const;
    // Email& getFromInbox(int id);
    // Email* getFromInboxPtr(int id);
    void popFromInbox();
    void deleteFromInbox(int index);
    void replyFromInbox(int index) const;

    void composeDraftEmail(Email& email, User& user);
    void sendEmail(Email& email, User& receiver);
    void sendEmail(Email& email);
    void receiveEmail(Email& email);
    void sendDraftEmails();

    Email peekInbox() const;
    Email popInbox();
    size_t getOutboxSize() const;

    /// Features

private:
    /// User Information
    int m_id = -1;
    std::string m_name = "";
    std::string m_emailAddress = "";
    
    /// Storage
    Inbox m_inbox;
    Outbox m_outbox;

    /// Features
    SearchService m_searchService;
    SpamDetectionService m_spamDetectionService;
    PriorityService m_priorityService;
    EmailService* s_emailService = nullptr; // Singleton
};