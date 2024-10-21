#pragma once

#include "Inbox.hpp"
#include "Outbox.hpp"
#include "PriorityService.hpp"
#include "SpamDetectionService.hpp"
#include "SearchService.hpp"

class User {
public:
    User() : _id(-1), _name(""), _emailAddress("") {}

    User(int id, std::string name, std::string emailAddress) 
        : _id(id), _name(name), _emailAddress(emailAddress) {}

    ~User() {
        std::cout << "User " << _name << " deleted." << std::endl;
    }

public:
    /// Getters and Setters
    int getId() const { return _id; }
    void setId(int id) { _id = id; }

    std::string getName() const { return _name; }
    void setName(std::string name) { _name = name; }

    std::string getEmailAddress() const { return _emailAddress; }
    void setEmailAddress(std::string emailAddress) { _emailAddress = emailAddress; }


    /// Storage
    void receiveEmail(const Email& email) {
        // _spamDetectionService.filter(email)
        _inbox.push(email);
    }

    void sendEmail(const Email& email, User& receiver) {
        // _priorityService.assert(email);
        // _outbox.addEmail(email);
        receiver.receiveEmail(email);
    }


    const Inbox& getInbox() const {
        return _inbox;
    }

    Inbox& getInbox() {
        return _inbox;
    }

    Email peekInbox() const {
        return _inbox.peek();
    }
    Email popInbox() {
        return _inbox.pop();
    }

    /// Features

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