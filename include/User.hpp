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

public:
    /// Getters and Setters
    int getId() const;
    std::string getName() const;
    std::string getEmailAddress() const;

    /// Storage
    void receiveEmail(Email& email);
    void composeEmail(Email& email, User& user);
    const Inbox& getInbox() const;
    Inbox& getInbox();
    void viewInbox() const;
    const Email getFromInbox(int index) const;
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