#include <iostream>

#include "User.hpp"

User::User(int id, std::string name, std::string email_address) 
    : _id(id), _name(name), _emailAddress(email_address) {}

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

Stack<Email> User::getInbox() const {
    return _inbox;
}

Email User::getEmail() const {
    return *_composedEmail;
}

Email User::deleteEmail() const {
    return _inbox.pop();
}


void User::composeEmail(Email email) {
    *_composedEmail = email;
}