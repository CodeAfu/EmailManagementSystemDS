
#include <iostream>

#include "ColorFormat.hpp"
#include "Timestamp.hpp"
#include "PriorityLevel.hpp"
#include "Email.hpp"

Email::Email() {};

Email::Email(int id, const std::string& sender, const std::string& receiver, 
        const std::string& subject, const std::string& body)
    : m_id(id), m_sender(sender), m_receiver(receiver), 
        m_subject(subject), m_body(body), m_priority(PriorityLevel::Low) { }

Email::Email(int id, const std::string& sender, const std::string& receiver, 
        const std::string& subject, const std::string& body, PriorityLevel priority)
    : m_id(id), m_sender(sender), m_receiver(receiver), 
        m_subject(subject), m_body(body), m_priority(priority) { }

Email::Email(int id, const std::string& sender, const std::string& receiver, 
        const std::string& subject, const std::string& body, PriorityLevel priority,
        bool is_important, bool is_sent, bool is_spam, bool is_draft, bool is_read)
    : m_id(id), m_sender(sender), m_receiver(receiver), m_subject(subject), m_body(body), m_priority(priority),
        m_isImportant(is_important), m_isSent(is_sent), m_isSpam(is_spam), 
        m_isDraft(is_draft), m_isRead(is_read) {

}

Email::~Email() {
}

/// Getters and Setters
int Email::getId() const { return m_id; }
void Email::setId(int id) { m_id = id; }

std::string Email::getSender() const { return m_sender; }
void Email::setFrom(const std::string& from) { m_sender = from; }

std::string Email::getReceiver() const { return m_receiver; }
void Email::setTo(const std::string& to) { m_receiver = to; }

std::string Email::getSubject() const { return m_subject; }
void Email::setSubject(const std::string& subject) { m_subject = subject; }

std::string Email::getBody() const { return m_body; }
void Email::setBody(const std::string& body) { m_body = body; }

PriorityLevel Email::getPriority() const { return m_priority; }
void Email::setPriority(PriorityLevel priority) { m_priority = priority; }


// Boolean Flags
bool Email::isImportant() const { return m_isImportant; }
void Email::setIsImportant(bool flag) {
    if (flag != m_isImportant && flag) {
        if (m_priority == PriorityLevel::Low) {
            m_priority = PriorityLevel::Medium;
        } else if (m_priority == PriorityLevel::Medium) {
            m_priority = PriorityLevel::High;
        }
    } else if (flag != m_isImportant && !flag) {
        if (m_priority == PriorityLevel::High) {
            m_priority = PriorityLevel::Medium;
        } else if (m_priority == PriorityLevel::Medium) {
            m_priority = PriorityLevel::Low;
        }
    }
    m_isImportant = flag;
}

bool Email::isRead() const { return m_isRead; }
void Email::setIsRead(bool flag) { m_isRead = flag; }

bool Email::isSent() const { return m_isSent; }
void Email::setIsSent(bool flag) { m_isSent = flag; }

bool Email::isDraft() const { return m_isDraft; }
void Email::setIsDraft(bool flag) { m_isDraft = flag; }

bool Email::isSpam() const { return m_isSpam; }
void Email::setIsSpam(bool flag) { m_isSpam = flag; }

/// Helpers
void Email::display() const {
    if (this == nullptr || m_id == -1) {
        return;
    }
    std::cout << "From: " << m_sender << std::endl;
    std::cout << "To: " << m_receiver << std::endl;
    std::cout << "Subject: " << m_subject << std::endl << std::endl;
    std::cout << "Body: " << m_body << std::endl;
    // std::cout << "Date: " << m_timestamp.getDate() << std::endl;
    // std::cout << "Time: " << m_timestamp.getTime() << std::endl;
}

std::string Email::toString() const {
    std::stringstream ss;
    ss << "{ID: " << m_id << ", From: " << m_sender 
    << ", To: " << m_receiver << ", Subject: " << m_subject 
    << ", Body: " << m_body << ", Date: " 
    //    << m_timestamp.getDate() << ", Time: " << m_timestamp.getTime() 
    << "}";
    return ss.str();
}

void Email::swap(Email& other) noexcept {
    std::swap(m_id, other.m_id);
    m_sender.swap(other.m_sender);
    m_receiver.swap(other.m_receiver);
    m_subject.swap(other.m_subject);
    m_body.swap(other.m_body);
    std::swap(m_priority, other.m_priority);
    std::swap(m_isImportant, other.m_isImportant);
    std::swap(m_isSpam, other.m_isSpam);
    std::swap(m_isSent, other.m_isSent);
    std::swap(m_isRead, other.m_isRead);
    std::swap(m_isDraft, other.m_isDraft);
}

