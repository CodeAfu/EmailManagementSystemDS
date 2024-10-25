#include <iostream>
#include <iomanip>

#include "User.hpp"
#include "Email.hpp"
#include "OutRequest.hpp"

/* Constructors & Destructors */
User::User() {}

User::User(int id, std::string name, std::string emailAddress) 
    : m_id(id), m_name(name), m_emailAddress(emailAddress), 
      s_emailService(&EmailService::GetInstance()) {
    
    s_emailService->subscribeUser(this);
}

User::~User() {
    // std::cout << "User " << m_name << " deleted." << std::endl;
    s_emailService->unsubscribeUser(this);
    s_emailService = nullptr;
}

/* Getters and Setters */
int User::getId() const { return m_id; }
std::string User::getName() const { return m_name; }
std::string User::getEmailAddress() const { return m_emailAddress; }

/* Storage */
/// @brief Use only for internal methods, avoid using in the CLI
void User::receiveEmail(Email& email) {
    // m_spamDetectionService.filter(email)
    m_inbox.push(email);
    
}

void User::composeEmail(Email& email, User& receiver) {
    s_emailService->addRequest(&email, &receiver);
}

const Inbox& User::getInbox() const {
    return m_inbox;
}

Inbox& User::getInbox() {
    return m_inbox;
}

void User::viewInbox() const {
    if (m_inbox.isEmpty()) {
        std::cout << "Inbox is empty." << std::endl;
        return;
    }
    Inbox temp = m_inbox;

    std::cout << m_name << "'s Inbox:" << std::right << std::setw(56) << m_emailAddress << std::endl;
    std::cout << "---------------------------------------------------------------------\n";
    std::cout << "| # | From                        | Subject                         |\n";
    std::cout << "---------------------------------------------------------------------\n";

    int count = 1;
    while (!temp.isEmpty()) {
        Email email = temp.pop();
        const std::string& sender = email.getSender();
        const std::string& subject = email.getSubject();

        std::cout << "| " << count++ << " | "
                  << std::left << std::setw(28) << sender
                  << "| " << std::setw(32) << subject << "|\n";
    }
    std::cout << "---------------------------------------------------------------------\n";
    std::cout << "Total messages: " << std::to_string(m_inbox.size()) << "\n";
}

const Email User::getFromInbox(int index) const {
    int size = m_inbox.size();
    if (index > m_inbox.size() - 1) {
        throw std::out_of_range("GetFromInbox: Index out of range");
    }
    Inbox temp = m_inbox;

    for (int i = 0; i < index; i++) {
        temp.pop();
    }

    return temp.peek();
}


Email User::peekInbox() const {
    return m_inbox.peek();
}

Email User::popInbox() {
    return m_inbox.pop();
}

size_t User::getOutboxSize() const {
    return s_emailService->size();
}

/* Features */
