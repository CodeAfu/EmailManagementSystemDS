// TODO: Implement Later
#include <iostream>

#include "User.hpp"
#include "Email.hpp"
#include "Outbox.hpp"
#include "OutRequest.hpp"


/* Constructors & Destructors */
User::User() {}

User::User(int id, std::string name, std::string emailAddress) 
    : m_id(id), m_name(name), m_emailAddress(emailAddress), 
      s_outbox(&Outbox::GetInstance()) {}

User::~User() {
    s_outbox = nullptr;
    // std::cout << "User " << m_name << " deleted." << std::endl;
}

/* Getters and Setters */
int User::getId() const { return m_id; }
void User::setId(int id) { m_id = id; }

std::string User::getName() const { return m_name; }
void User::setName(std::string name) { m_name = name; }

std::string User::getEmailAddress() const { return m_emailAddress; }
void User::setEmailAddress(std::string emailAddress) { m_emailAddress = emailAddress; }

/* Storage */
/// @brief Use only for internal methods, avoid using in the CLI
void User::receiveEmail(Email& email) {
    // m_spamDetectionService.filter(email)
    m_inbox.push(email);
    
}

void User::sendEmail() {
    s_outbox->sendNext();
}
    
void User::sendAllEmails() {
    s_outbox->sendAll();
}

void User::addToOutbox(Email& email, User& receiver) {
    s_outbox->addRequest(&email, &receiver);
}

const Inbox& User::getInbox() const {
    return m_inbox;
}

Inbox& User::getInbox() {
    return m_inbox;
}

Email User::peekInbox() const {
    return m_inbox.peek();
}

Email User::popInbox() {
    return m_inbox.pop();
}

size_t User::getOutboxSize() const {
    return s_outbox->size();
}

/* Features */