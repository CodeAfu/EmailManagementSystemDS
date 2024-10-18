#include <iostream>

#include "User.hpp"

User::User(int id, std::string name, std::string email_address)
    : _id(id), _name(name), _emailAddress(email_address), _draftEmail(nullptr), _hasDraftEmail(false) {}

bool User::operator==(const User& other) const {
    return _id == other._id
        && _name == other._name
        && _emailAddress == other._emailAddress
        && _draftEmail == other._draftEmail
        && _hasDraftEmail == other._hasDraftEmail;
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
    // TODO: Handle null case
    return *_draftEmail;
}

void User::receiveEmail(Email& email) {
    _inbox.push(email);
    std::cout << this->getName() << " received an email from " << email.getFrom() << std::endl;
}

Email User::deleteEmail() {
    return _inbox.pop();
}

void User::draftEmail(Email& email) {
    // Limitation: only 1 composed email at a time.
    std::cout << "[" << this->getName() << "]: Added email to draft" << std::endl;
    email.setIsDraft(true);
    _draftEmail = &email;
    _hasDraftEmail = true;
}

void User::sendDraftEmail(User& receiver) {
    // TODO: Possible better way to handle this than using flags. 
    if (_draftEmail == nullptr) {
        std::cout << "No draft email to send" << std::endl;
        return;        
    }
    sendEmail(*_draftEmail, receiver);
    _draftEmail->setIsDraft(false);
}

void User::sendEmail(Email& email, User& receiver) {
    if (isSendableEmail(email)) {
        receiver.receiveEmail(email);
    }
}

std::string User::toString() const {
    std::string composed_msg;
    // TODO: Possible better way to handle this than using flags. 
    if (_draftEmail) {
        composed_msg = _draftEmail->getSubject();
    } else {
        composed_msg = "No email composed.";
    }

    int num_emails = -1;
    if (!_inbox.isEmpty()) {
        num_emails = static_cast<int>(_inbox.getSize());
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

bool User::isSendableEmail(Email& email) const {
    return email.getBody() != "" 
        && email.getSubject() != "" 
        && email.getTo() != "" 
        && email.getFrom() != "";
}
