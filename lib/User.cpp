#include <iostream>
#include <iomanip>

#include "User.hpp"
#include "Helper.hpp"
#include "Email.hpp"
#include "OutRequest.hpp"
#include "Helper.hpp"
#include "ResourceManager.hpp"

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
    ColorFormat::println("[BAD] User " + m_name + " deleted.", Color::BrightRed);
}

User::User(const User& other) 
    : m_id(other.m_id),
        m_name(other.m_name),
        m_emailAddress(other.m_emailAddress),
        m_inbox(other.m_inbox),
        m_outbox(other.m_outbox),
        m_searchService(other.m_searchService),
        m_spamDetectionService(other.m_spamDetectionService),
        m_priorityService(other.m_priorityService) {}

User& User::operator=(const User& other) {
    if (this != &other) {
        m_id = other.m_id;
        m_name = other.m_name;
        m_emailAddress = other.m_emailAddress;
        m_inbox = other.m_inbox;
        m_outbox = other.m_outbox;
        m_searchService = other.m_searchService;
        m_spamDetectionService = other.m_spamDetectionService;
        m_priorityService = other.m_priorityService;
    }
    return *this;
}

User::User(User&& other) noexcept
    : m_id(other.m_id),
        m_name(std::move(other.m_name)),
        m_emailAddress(std::move(other.m_emailAddress)),
        m_inbox(std::move(other.m_inbox)),
        m_outbox(std::move(other.m_outbox)),
        m_searchService(std::move(other.m_searchService)),
        m_spamDetectionService(std::move(other.m_spamDetectionService)),
        m_priorityService(std::move(other.m_priorityService)) {}

User& User::operator=(User&& other) noexcept {
    if (this != &other) {
        m_id = other.m_id;
        m_name = std::move(other.m_name);
        m_emailAddress = std::move(other.m_emailAddress);
        m_inbox = std::move(other.m_inbox);
        m_outbox = std::move(other.m_outbox);
        m_searchService = std::move(other.m_searchService);
        m_spamDetectionService = std::move(other.m_spamDetectionService);
        m_priorityService = std::move(other.m_priorityService);
    }
    return *this;
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
    m_outbox.addDraft(email, receiver);
}

void User::viewDraftEmails() const {
    LLQueue<Email> temp = m_outbox.getDraftEmails();
    size_t size = temp.size();

    if (temp.isEmpty()) {
        std::cout << m_name << "'s Drafts are empty." << std::endl;
        return;
    }

    std::string header = m_name + "'s Draft Emails:";
    int len = 72 - header.length();

    std::cout << header << std::right << std::setw(len) << m_emailAddress << std::endl;
    std::cout << "------------------------------------------------------------------------\n";
    std::cout << "|  ID  | To                          | Subject                         |\n";
    std::cout << "------------------------------------------------------------------------\n";

    while (!temp.isEmpty()) {
        const Email email = temp.dequeue();
        const std::string receiver = email.getReceiver();
        const std::string& subject = email.getSubject();

        const std::string id_str = std::to_string(email.getId());
        std::cout << "| " << Formatter::centerAlign(id_str, 4) << " | "
                  << std::left << std::setw(28) << receiver
                  << "| " << std::setw(32) << subject << "|\n";
    }

    std::cout << "------------------------------------------------------------------------\n";
    std::cout << "Total Emails: " << std::to_string(size) << "\n";
}

void User::viewSentEmails() const {
    LLQueue<Email> temp = m_outbox.getSentEmails();
    size_t size = temp.size();

    if (temp.isEmpty()) {
        std::cout << m_name << "'s Sent Emails are empty." << std::endl;
        return;
    }

    std::string header = m_name + "'s Sent Emails:";
    int len = 72 - header.length();

    std::cout << header << std::right << std::setw(len) << m_emailAddress << std::endl;
    std::cout << "------------------------------------------------------------------------\n";
    std::cout << "|  ID  | To                          | Subject                         |\n";
    std::cout << "------------------------------------------------------------------------\n";

    while (!temp.isEmpty()) {
        const Email email = temp.dequeue();
        const std::string receiver = email.getReceiver();
        const std::string& subject = email.getSubject();

        const std::string id_str = std::to_string(email.getId());
        std::cout << "| " << Formatter::centerAlign(id_str, 4) << " | "
                  << std::left << std::setw(28) << receiver
                  << "| " << std::setw(32) << subject << "|\n";
    }

    std::cout << "------------------------------------------------------------------------\n";
    std::cout << "Total Emails: " << std::to_string(size) << "\n";
}


void User::sendDraftEmails() {
    auto& email_service = EmailService::GetInstance();
    LLQueue<OutRequest> drafts = m_outbox.getDraftRequests();

    while (!drafts.isEmpty()) {
        OutRequest request = drafts.dequeue();

        request.email->setIsDraft(false);
        request.email->setIsSent(true);

        m_outbox.addSentEmail(*request.email);
        ColorFormat::println(m_name + " sent a draft email " + request.email->getSubject() 
                                  + " to " + request.receiver->getName(), Color::BrightCyan);
        email_service.addRequest(request.email, request.receiver);
    }
    email_service.sendAllRequests(); // TODO: needs to be be revised, called inside main
}

void User::sendEmail(Email& email, User& receiver) {
    m_outbox.sendEmail(email, receiver);
}

void User::sendEmail(Email& email) {
    User* receiver = ResourceManager::getReceiver(email.getReceiver());

    if (!receiver) {
        ColorFormat::println("[ERROR] " + email.getReceiver() + " not found.", Color::Red);
        return;
    }

    m_outbox.sendEmail(email, *receiver);
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
    email.display();
    // std::cout << "From: " << email.getSender() << std::endl;
    // std::cout << "Subject: " << email.getSubject() << std::endl << std::endl;
    // std::cout << "Body: " << email.getBody() << std::endl;
}

Email User::getFromInbox(int id) const {
    Inbox temp = m_inbox;

    while (!temp.isEmpty()) {
        Email email = temp.pop();
        if (email.getId() == id) {
            return email;
        }
    }
    return Email(); // return null email, id = -1
}

// Email& User::getFromInbox(int id) {
//     int size = m_inbox.size();

//     Stack<Email>& inbox_ref = m_inbox.getEmails();
//     Stack<Email> temp;
//     Email* out = nullptr;

//     while (!inbox_ref.isEmpty()) {
//         Email email = inbox_ref.pop();
//         temp.push(email);

//         if (email.getId() == id) {
//             out = &email;
//             break;
//         }
//     }

//     while (!temp.isEmpty()) {
//         inbox_ref.push(temp.pop());
//     }

//     if (out) {
//         return *out;
//     } else {
//         throw std::runtime_error("GetFromInbox&: Email not found");
//     }
// }

// Email* User::getFromInboxPtr(int id) {
//     int size = m_inbox.size();

//     Stack<Email>& inbox_ref = m_inbox.getEmails();
//     Stack<Email> temp;
//     Email* out = nullptr;

//     while (!inbox_ref.isEmpty()) {
//         Email& email = inbox_ref.popRef();
//         temp.push(email);

//         if (email.getId() == id) {
//             out = &email;
//             break;
//         }
//     }

//     while (!temp.isEmpty()) {
//         inbox_ref.push(temp.pop());
//     }

//     return out;
// }

void User::deleteFromInbox(int id) {
    Stack<Email> temp;

    while (!m_inbox.isEmpty()) {
        Email email = m_inbox.pop();
        if (email.getId() == id) {
            break;
        }
        temp.push(email);
    }

    if (!temp.isEmpty()) {
        m_inbox.push(temp.pop());
    }
}

void User::replyFromInbox(int id) const {

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
