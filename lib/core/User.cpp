#include <iostream>
#include <iomanip>

#include "User.hpp"
#include "Helper.hpp"
#include "Email.hpp"
#include "EmailRequest.hpp"
#include "Helper.hpp"
#include "ResourceManager.hpp"

/* Constructors & Destructors */
User::User() {}

User::User(int id, std::string name, std::string emailAddress) 
    : m_id(id), m_name(name), m_emailAddress(emailAddress), 
      s_emailService(&EmailService::GetInstance()) {
    
    m_priorityService = PriorityService(&m_inbox);
    m_spamDetectionService = SpamDetectionService(&m_inbox);

    this->addToImportantList("manager@workplace.com");
}

User::~User() {
    s_emailService = nullptr;
}

User::User(const User& other) 
    : m_id(other.m_id),
        m_name(other.m_name),
        m_emailAddress(other.m_emailAddress),
        m_inbox(other.m_inbox),
        m_outbox(other.m_outbox),
        m_searchService(other.m_searchService),
        m_spamDetectionService(other.m_spamDetectionService),
        m_priorityService(other.m_priorityService),
        m_importantUserList(other.m_importantUserList) {}

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
        m_importantUserList = other.m_importantUserList;
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
        m_priorityService(std::move(other.m_priorityService)),
        m_importantUserList(std::move(other.m_importantUserList)) {}

User& User::operator=(User&& other) noexcept {
    if (this != &other) {
        m_id = other.m_id;
        m_name = std::move(other.m_name);
        m_emailAddress = std::move(other.m_emailAddress);
        m_inbox = std::move(other.m_inbox);
        m_outbox = std::move(other.m_outbox);
        m_searchService = std::move(other.m_searchService);
        m_spamDetectionService = std::move(other.m_spamDetectionService);
        m_priorityService = std::move(other.m_priorityService),
        m_importantUserList = std::move(other.m_importantUserList);
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
    const std::string sender = email.getSender();

    if (m_importantUserList.contains(sender)) {
        if (email.getPriority() == PriorityLevel::Low) {
            email.setPriority(PriorityLevel::Medium);
        } else if (email.getPriority() == PriorityLevel::Medium) {
            email.setPriority(PriorityLevel::High);
        }
    }
    m_inbox.push(email);
}

void User::composeDraftEmail(Email& email) {
    m_outbox.addDraft(email);
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


void User::sendAllDraftEmails() {
    auto& email_service = EmailService::GetInstance();
    LLQueue<Email>& drafts = m_outbox.getDraftEmails();

    while (!drafts.isEmpty()) {
        Email email = drafts.dequeue();
        this->sendEmail(email);
    }

    email_service.sendAllRequests();
}

void User::sendEmail(Email& email, User& receiver) {
    m_outbox.sendEmail(email, receiver);
}

void User::sendEmail(Email& email) {
    User* receiver = ResourceManager::getUser(email.getReceiver());

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
    int len = 79 - header.length();

    std::cout << header << std::right << std::setw(len) << m_emailAddress << std::endl;
    std::cout << "-------------------------------------------------------------------------------\n";
    std::cout << "|  ID  | From                        | Subject                         | Read |\n";
    std::cout << "-------------------------------------------------------------------------------\n";

    int count = 1;
    while (!temp.isEmpty()) {
        Email email = temp.pop();
        bool is_read = email.isRead();
        const std::string& sender = email.getSender();
        const std::string& subject = email.getSubject();

        const std::string id_str = std::to_string(email.getId());
        const std::string& is_read_char = is_read ? "Y" : "N";
        std::cout << "| " << Formatter::centerAlign(id_str, 4) << " | "
                  << std::left << std::setw(28) << sender
                  << "| " << std::setw(32) << subject
                  << "|  " << is_read_char << "   |\n";
    }
    std::cout << "-------------------------------------------------------------------------------\n";
    std::cout << "Total Emails: " << std::to_string(m_inbox.size()) << "\n";
}

void User::readLastFromInbox() {
    if (m_inbox.isEmpty()) {
        std::cout << "Inbox is empty." << std::endl;
        return;
    }
    Email email = m_inbox.peek();
    email.display();

    email.setIsRead(true);
    m_inbox.pop();
    m_inbox.push(email);
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

Email User::readFromInbox(int id) {
    Inbox temp;
    Email res;
    
    while (!m_inbox.isEmpty()) {
        Email email = m_inbox.pop();
        if (email.getId() == id) {
            email.setIsRead(true);
            res = email;
        }
        temp.push(email);
    }

    while (!temp.isEmpty()) {
        m_inbox.push(temp.pop());
    }

    return res;
}

Email User::getFromSent(int id) {
    return m_outbox.getSentById(id);
}

Email User::getFromDraft(int id) {
    return m_outbox.getDraftById(id);
}

PriorityQueue& User::getPriorityQueueRef() {
    m_priorityService.refreshStorage(&m_inbox);
    m_priorityService.populatePriorityQueue();
    return m_priorityService.getPriorityQueueRef();
}

PriorityService& User::getPriorityServiceRef() {
    m_priorityService.refreshStorage(&m_inbox);
    m_priorityService.populatePriorityQueue();
    return m_priorityService;
}

SpamDetectionService& User::getSpamDetectionServiceRef() {
    m_spamDetectionService.refresh(&m_inbox);
    return m_spamDetectionService;
}

void User::updateFromDraft(const Email& email) {
    m_outbox.updateDraftEmail(email);
}

void User::popFromInbox() {
    m_inbox.pop();
    ColorFormat::println(std::to_string(m_inbox.size()) + " emails left in inbox", Color::BrightCyan);
}

void User::deleteFromInbox(int id) {
    Stack<Email> temp;

    while (!m_inbox.isEmpty()) {
        Email email = m_inbox.pop();
        if (email.getId() == id) {
            continue;
        }
        temp.push(email);
    }

    while (!temp.isEmpty()) {
        m_inbox.push(temp.pop());
    }
}

bool User::deleteFromSent(int id) {
    return m_outbox.removeSentById(id);
}

bool User::deleteFromDraft(int id) {
    return m_outbox.removeDraftById(id);
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

size_t User::getInboxSize() const {
    return m_inbox.size();
}

/* Features */
void User::addToImportantList(const std::string& email_address) {
    if (m_importantUserList.contains(email_address)) {
        std::cout << "[AddToImportantList] User already in list." << std::endl;
        return;
    }
    if (m_emailAddress == email_address) {
        std::cout << "[AddToImportantList] You cannot add yourself to the important list." << std::endl;
    }

    m_importantUserList.pushBack(email_address);
}
