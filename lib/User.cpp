// TODO: Implement Later
#include <iostream>

#include "User.hpp"
#include "Email.hpp"
#include "Outbox.hpp"
#include "OutRequest.hpp"


/* Constructors & Destructors */
User::User() {}

User::User(int id, std::string name, std::string emailAddress) 
    : _id(id), _name(name), _emailAddress(emailAddress), 
      _outbox(&Outbox::GetInstance()) {}

User::~User() {
    _outbox = nullptr;
    // std::cout << "User " << _name << " deleted." << std::endl;
}

/* Getters and Setters */
int User::getId() const { return _id; }
void User::setId(int id) { _id = id; }

std::string User::getName() const { return _name; }
void User::setName(std::string name) { _name = name; }

std::string User::getEmailAddress() const { return _emailAddress; }
void User::setEmailAddress(std::string emailAddress) { _emailAddress = emailAddress; }

/* Storage */
/// @brief Use only for internal methods, avoid using in the CLI
void User::receiveEmail(Email& email) {
    // _spamDetectionService.filter(email)
    _inbox.push(email);
    
}
    
void User::sendEmails() {
    _outbox->sendAll();
}

void User::addToOutbox(Email& email, User& receiver) {
    _outbox->addRequest(&email, &receiver);
}

const Inbox& User::getInbox() const {
    return _inbox;
}

Inbox& User::getInbox() {
    return _inbox;
}

Email User::peekInbox() const {
    return _inbox.peek();
}
Email User::popInbox() {
    return _inbox.pop();
}


/* Features */