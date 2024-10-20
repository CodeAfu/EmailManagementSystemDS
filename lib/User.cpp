#include <iostream>

#include "User.hpp"

// Constructors, Destructors, & Operators
User::User() : _id(-1), _name(""), _emailAddress("") {}

User::User(int id, std::string name, std::string emailAddress) 
    : _id(id), _name(name), _emailAddress(emailAddress) {}

User::~User() {
    std::cout << "User " << _name << " deleted." << std::endl;
}


// Getters and Setters
int User::getId() const { return _id; }
void User::setId(int id) { _id = id; }

std::string User::getName() const { return _name; }
void User::setName(std::string name) { _name = name; }

std::string User::getEmailAddress() const { return _emailAddress; }
void User::setEmailAddress(std::string emailAddress) { _emailAddress = emailAddress; }



// Storage
void User::receiveEmail(const Email& email) {
    _inbox.addEmail(email);
}

void User::sendEmail(const Email& email, User& receiver) {
    // _outbox.addEmail(email);
    receiver.receiveEmail(email);
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


// Features
