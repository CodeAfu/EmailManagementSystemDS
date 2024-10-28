#include <iostream>
#include <iomanip>

#include "User.hpp"
#include "Helper.hpp"
#include "Email.hpp"
#include "OutRequest.hpp"
#include "Helper.hpp"

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

void User::composeDraftEmail(Email& email, User& receiver) {
    m_outbox.addDraft(&email, &receiver);
}

void User::viewDraftEmails() const {
    LLQueue<Email*> temp = m_outbox.getDraftEmails();
    size_t size = temp.size();

    if (temp.isEmpty()) {
        std::cout << m_name << "'s Drafts are empty." << std::endl;
        return;
    }

    std::string header = m_name + "'s Draft Emails:";
    int len = 72 - header.length();

    std::cout << header << std::right << std::setw(len) << m_emailAddress << std::endl;
    std::cout << "------------------------------------------------------------------------\n";
    std::cout << "|  ID  | From                        | Subject                         |\n";
    std::cout << "------------------------------------------------------------------------\n";

    while (!temp.isEmpty()) {
        const Email* email = temp.dequeue();
        const std::string sender = email->getSender();
        const std::string& subject = email->getSubject();

        const std::string id_str = std::to_string(email->getId());
        std::cout << "| " << Formatter::centerAlign(id_str, 4) << " | "
                  << std::left << std::setw(28) << sender
                  << "| " << std::setw(32) << subject << "|\n";
    }

    std::cout << "------------------------------------------------------------------------\n";
    std::cout << "Total Emails: " << std::to_string(size) << "\n";
}

void User::viewSentEmails() const {
    LLQueue<Email*> temp = m_outbox.getSentEmails();
    size_t size = temp.size();

    if (temp.isEmpty()) {
        std::cout << m_name << "'s Sent Emails are empty." << std::endl;
        return;
    }

    std::string header = m_name + "'s Sent Emails:";
    int len = 72 - header.length();

    std::cout << header << std::right << std::setw(len) << m_emailAddress << std::endl;
    std::cout << "------------------------------------------------------------------------\n";
    std::cout << "|  ID  | From                        | Subject                         |\n";
    std::cout << "------------------------------------------------------------------------\n";

    while (!temp.isEmpty()) {
        const Email* email = temp.dequeue();
        const std::string sender = email->getSender();
        const std::string& subject = email->getSubject();

        const std::string id_str = std::to_string(email->getId());
        std::cout << "| " << Formatter::centerAlign(id_str, 4) << " | "
                  << std::left << std::setw(28) << sender
                  << "| " << std::setw(32) << subject << "|\n";
    }

    std::cout << "------------------------------------------------------------------------\n";
    std::cout << "Total Emails: " << std::to_string(size) << "\n";
}


void User::sendDraftEmails() {
    auto& email_service = EmailService::GetInstance();
    LLQueue<OutRequest>& drafts = m_outbox.getDraftRequests();

    while (!drafts.isEmpty()) {
        OutRequest request = drafts.dequeue();

        request.email->setIsDraft(false);
        request.email->setIsSent(true);

        m_outbox.addSentEmail(request.email);
        ColorFormat::print(m_name + " sent a draft email " + request.email->getSubject() 
                                  + " to " + request.receiver->getName(), Color::BrightCyan);
        email_service.addRequest(request.email, request.receiver);
    }
    email_service.sendAllRequests(); // TODO: needs to be be revised, called inside main
}

void User::sendEmail(Email& email, User& receiver) {
    m_outbox.sendEmail(&email, &receiver);
}

const Inbox& User::getInbox() const {
    return m_inbox;
}

Inbox& User::getInbox() {
    return m_inbox;
}

const Outbox& User::getOutbox() const {
    return m_outbox;
}

Outbox& User::getOutbox() {
    return m_outbox;
};

void User::viewInbox() const {
    if (m_inbox.isEmpty()) {
        std::cout << "Inbox is empty." << std::endl;
        return;
    }
    Inbox temp = m_inbox;

    std::string header = m_name + "'s Inbox:";
    int len = 72 - header.length();

    std::cout << header << std::right << std::setw(len) << m_emailAddress << std::endl;
    std::cout << "------------------------------------------------------------------------\n";
    std::cout << "|  ID  | From                        | Subject                         |\n";
    std::cout << "------------------------------------------------------------------------\n";

    int count = 1;
    while (!temp.isEmpty()) {
        Email email = temp.pop();
        const std::string& sender = email.getSender();
        const std::string& subject = email.getSubject();

        const std::string id_str = std::to_string(email.getId());
        std::cout << "| " << Formatter::centerAlign(id_str, 4) << " | "
                  << std::left << std::setw(28) << sender
                  << "| " << std::setw(32) << subject << "|\n";
    }
    std::cout << "------------------------------------------------------------------------\n";
    std::cout << "Total Emails: " << std::to_string(m_inbox.size()) << "\n";
}

void User::viewLastFromInbox() const {
    if (m_inbox.isEmpty()) {
        std::cout << "Inbox is empty." << std::endl;
        return;
    }
    Email email = m_inbox.peek();
    std::cout << "From: " << email.getSender() << std::endl;
    std::cout << "Subject: " << email.getSubject() << std::endl << std::endl;
    std::cout << "Body: " << email.getBody() << std::endl;
}

const Email User::getFromInbox(int index) const {
    int size = m_inbox.size();
    if (index > size - 1) {
        throw std::out_of_range("GetFromInbox: Index out of range");
    }
    Inbox temp = m_inbox;

    for (int i = 0; i < index; i++) {
        temp.pop();
    }

    return temp.peek();
}

Email& User::getFromInbox(int index) {
    int size = m_inbox.size();
    if (index > size - 1) {
        throw std::out_of_range("GetFromInbox: Index out of range");
    }
    Stack<Email>& inbox_ref = m_inbox.getEmails();
    Stack<Email> temp;

    for (int i = 0; i < index; i++) {
        temp.push(inbox_ref.pop());
    }

    Email& out = inbox_ref.peek();

    while (!temp.isEmpty()) {
        inbox_ref.push(temp.pop());
    }

    return out;
}

void User::deleteFromInbox(int index) {

}

void User::replyFromInbox(int index) const {

}



Email User::peekInbox() const {
    return m_inbox.peek();
}

Email User::popInbox() {
    return m_inbox.pop();
}

size_t User::getOutboxSize() const {
    return m_outbox.size();
}

/* Features */
