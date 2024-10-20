#pragma once

#include "Inbox.hpp"
#include "Outbox.hpp"
#include "PriorityService.hpp"
#include "SpamDetectionService.hpp"
#include "SearchService.hpp"

class User {
public:
    User();
    User(int id, std::string name, std::string emailAddress);
    ~User();

public:
    // Getters and Setters
    int getId() const;
    void setId(int id);

    std::string getName() const;
    void setName(std::string name);

    std::string getEmailAddress() const;
    void setEmailAddress(std::string emailAddress);


    // Storage
    void receiveEmail(const Email& email);
    void sendEmail(const Email& email, User& receiver);

    const Inbox& getInbox() const;
    Inbox& getInbox();
    Email peekInbox() const;
    Email popInbox();

    // Features

private:
    /// User Information
    int _id = -1;
    std::string _name = "";
    std::string _emailAddress = "";
    
    /// Storage
    Inbox _inbox;
    Outbox _outbox;

    /// Features
    SearchService _searchService;
    SpamDetectionService _spamDetectionService;
    PriorityService _priorityService;
};