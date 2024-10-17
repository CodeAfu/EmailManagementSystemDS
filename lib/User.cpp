#include <iostream>

#include "User.hpp"

User::User(int id, std::string name, std::string email_address) 
    : _id(id), _name(name), _emailAddress(email_address), _composedEmail(nullptr) {}

bool User::operator==(const User& other) const {
    return _id == other._id
        && _name == other._name
        && _emailAddress == other._emailAddress;
}

void User::setStackConfig(size_t capacity, int increment_value) {
    _inbox.reserve(capacity);
    _inbox.setIncrementValue(increment_value);
}

std::string User::getName() const {
    return _name;
}

std::string User::getEmailAddress() const {
    return _emailAddress;
}

Stack<Email> User::getInbox() const {
    return _inbox;
}

Email User::getComposedEmail() const {
    return *_composedEmail;
}

void User::receiveEmail(Email& email) {
    _inbox.push(email);
    std::cout << this->getName() << " received an email from " << email.getFrom() << std::endl;
}

Email User::deleteEmail() {
    return _inbox.pop();
}

void User::composeEmail(Email email) {
    std::cout << "[" << this->getName() << "]: Added email to draft" << std::endl;
    email.setIsDraft(true);
    _composedEmail = &email;
}

void User::sendComposedEmail(User& receiver) {
    if (_composedEmail == nullptr) {
        std::cout << "No email to send" << std::endl;
        return;        
    }
    _composedEmail->setIsDraft(false);
    receiver.receiveEmail(*_composedEmail);
}

void User::sendEmail(Email email, User& receiver) {
    receiver.receiveEmail(email);
}

std::string User::toString() const {
    std::string composed_msg;
    if (_composedEmail != nullptr) {
        std::cout << _composedEmail->getSubject();
        composed_msg = _composedEmail->getSubject();
    } else {
        composed_msg = "No email composed.";
    }

    int num_emails = -1;
    if (!_inbox.isEmpty()) {
        num_emails = _inbox.getIndex() + 1;
    }
    
    std::string s = "User ID: " + std::to_string(_id) + "\n";
    s += "Name: " + _name + "\n";
    s += "Email Address: " + _emailAddress + "\n";
    s += "Composed Email: " + composed_msg + "\n";
    s += "Inbox: " + std::to_string(num_emails) + "\n";
    return s;
}

void User::log() {
    std::cout << toString() << std::endl;
}