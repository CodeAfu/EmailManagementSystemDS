#pragma once

#include "Inbox.hpp"
#include "Outbox.hpp"
#include "PriorityService.hpp"
#include "SpamDetectionService.hpp"
#include "SearchService.hpp"

struct Email;

class User {
public:
    User();
    User(int id, std::string name, std::string emailAddress);
    ~User();

public:
    /// Getters and Setters
    int getId() const;
    void setId(int id);

    std::string getName() const;
    void setName(std::string name);

    std::string getEmailAddress() const;
    void setEmailAddress(std::string emailAddress);

    /// Storage
    void receiveEmail(Email& email);
    void addToOutbox(Email& email, User& user);
    void sendEmail();
    void sendAllEmails();
    const Inbox& getInbox() const;
    Inbox& getInbox();
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
    Outbox* s_outbox = nullptr;

    /// Features
    SearchService m_searchService;
    SpamDetectionService m_spamDetectionService;
    PriorityService m_priorityService;
};