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
    void readLastFromInbox();
    void viewDraftEmails() const;
    void viewSentEmails() const;

    const Inbox& getInbox() const;
    Inbox& getInbox();

    Email getFromInbox(int id) const;
    Email readFromInbox(int id);
    // Email& getFromInbox(int id);
    // Email* getFromInboxPtr(int id);
    Email getFromSent(int id);
    Email getFromDraft(int id);
    PriorityQueue& getPriorityQueueRef();
    PriorityService& getPriorityServiceRef();
    SpamDetectionService& getSpamDetectionServiceRef();
    void updateFromDraft(const Email& email);
    const Outbox& getOutbox() const;
    Outbox& getOutbox();
    void popFromInbox();
    void deleteFromInbox(int id);
    bool deleteFromSent(int id);
    bool deleteFromDraft(int id);

    void composeDraftEmail(Email& email);
    void sendEmail(Email& email, User& receiver);
    void sendEmail(Email& email);
    void receiveEmail(Email& email);
    void sendAllDraftEmails();

    Email peekInbox() const;
    Email popInbox();
    size_t getOutboxSize() const;
    size_t getInboxSize() const;

    /// Features
    void addToImportantList(const std::string& email_address);

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
    
    DynArray<std::string> m_importantUserList;

    EmailService* s_emailService = nullptr; // Singleton
};