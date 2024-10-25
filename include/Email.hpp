#pragma once

#include <iostream>
#include <sstream>
#include <utility>
#include <memory>

#include "ColorFormat.hpp"
#include "Timestamp.hpp"

class Email {
public:
    Email() {};

    Email(int id, const std::string& sender, const std::string& receiver, 
          const std::string& subject, const std::string& body)
        : m_id(id), m_sender(sender), m_receiver(receiver), m_subject(subject), m_body(body) {
        // ColorFormat::print("Email Created: " + std::to_string(m_id), Color::Green);
    }

    ~Email() {
        // ColorFormat::print("Email Destroyed: " + std::to_string(m_id), Color::Red);
    }

    /// Copy constructor
    Email(const Email& other)
        : m_id(other.m_id), m_sender(other.m_sender), m_receiver(other.m_receiver),
        m_subject(other.m_subject), m_body(other.m_body), 
        m_isImportant(other.m_isImportant), m_isSpam(other.m_isSpam), 
        m_isSent(other.m_isSent), m_isRead(other.m_isRead), m_isDraft(other.m_isDraft) 
        // m_timestamp(other.m_timestamp) 
    {
        // ColorFormat::print("Email Copy Constructor: " + std::to_string(other.m_id), Color::Cyan);
    }

    /// Move constructor
    Email(Email&& other) noexcept
        : m_id(other.m_id), m_sender(std::move(other.m_sender)), m_receiver(std::move(other.m_receiver)),
        m_subject(std::move(other.m_subject)), m_body(std::move(other.m_body)), 
        m_isImportant(other.m_isImportant), m_isSpam(other.m_isSpam), 
        m_isSent(other.m_isSent), m_isRead(other.m_isRead), m_isDraft(other.m_isDraft)
        // m_timestamp(std::move(other.m_timestamp)) 
    {
        // ColorFormat::print("Email Move Constructor: " + std::to_string(other.m_id), Color::Blue);
        other.m_id = -1;
        other.m_isImportant = false;
        other.m_isSpam = false;
        other.m_isSent = false;
        other.m_isRead = false;
        other.m_isDraft = false;
        other.m_sender.clear();
        other.m_receiver.clear();
        other.m_subject.clear();
        other.m_body.clear();
    }

    /// Copy assignment operator
    Email& operator=(const Email& other) {
        // ColorFormat::print("Email Copy Assignment: " + std::to_string(other.m_id), Color::Cyan);
        if (this != &other) {
            m_id = other.m_id;
            m_sender = other.m_sender;\
            m_receiver = other.m_receiver;
            m_subject = other.m_subject;
            m_body = other.m_body;
            m_isImportant = other.m_isImportant;
            m_isSpam = other.m_isSpam;
            m_isSent = other.m_isSent;
            m_isRead = other.m_isRead;
            m_isDraft = other.m_isDraft;
            // m_timestamp = other.m_timestamp;
        }
        return *this;
    }

    /// Move assignment operator
    Email& operator=(Email&& other) noexcept {
        // ColorFormat::print("Email Move Assignment: " + std::to_string(other.m_id), Color::Magenta); 
        if (this != &other) {
            m_id = other.m_id;
            m_sender = std::move(other.m_sender);
            m_receiver = std::move(other.m_receiver);
            m_subject = std::move(other.m_subject);
            m_body = std::move(other.m_body);
            m_isImportant = other.m_isImportant;
            m_isSpam = other.m_isSpam;
            m_isSent = other.m_isSent;
            m_isRead = other.m_isRead;
            m_isDraft = other.m_isDraft;
            // m_timestamp = std::move(other.m_timestamp);
        }
        return *this;
    }

    /// Getters and Setters
    int getId() const { return m_id; }
    void setId(int id) { m_id = id; }

    std::string getSender() const { return m_sender; }
    void setFrom(const std::string& from) { m_sender = from; }

    std::string getReceiver() const { return m_receiver; }
    void setTo(const std::string& to) { m_receiver = to; }

    std::string getSubject() const { return m_subject; }
    void setSubject(const std::string& subject) { m_subject = subject; }

    std::string getBody() const { return m_body; }
    void setBody(const std::string& body) { m_body = body; }

    bool isSent() const { return m_isSent; }
    void setIsSent(bool flag) { m_isSent = flag; }

    bool isDraft() const { return m_isDraft; }
    void setIsDraft(bool flag) { m_isDraft = flag; }

    // std::string getDate() const { return m_timestamp.getDate(); }
    // std::string getTime() const { return m_timestamp.getTime(); }
    
    /// Helpers
    void display() const {
        std::cout << "ID: " << m_id << std::endl;
        std::cout << "From: " << m_sender << std::endl;
        std::cout << "To: " << m_receiver << std::endl;
        std::cout << "Subject: " << m_subject << std::endl;
        std::cout << "Body: " << m_body << std::endl;
        // std::cout << "Date: " << m_timestamp.getDate() << std::endl;
        // std::cout << "Time: " << m_timestamp.getTime() << std::endl;
    }

    std::string toString() const {
        std::stringstream ss;
        ss << "{ID: " << m_id << ", From: " << m_sender 
        << ", To: " << m_receiver << ", Subject: " << m_subject 
        << ", Body: " << m_body << ", Date: " 
        //    << m_timestamp.getDate() << ", Time: " << m_timestamp.getTime() 
        << "}";
        return ss.str();
    }

private:
    void swap(Email& other) noexcept {
        std::swap(m_id, other.m_id);
        m_sender.swap(other.m_sender);
        m_receiver.swap(other.m_receiver);
        m_subject.swap(other.m_subject);
        m_body.swap(other.m_body);
        std::swap(m_isImportant, other.m_isImportant);
        std::swap(m_isSpam, other.m_isSpam);
        std::swap(m_isSent, other.m_isSent);
        std::swap(m_isRead, other.m_isRead);
        std::swap(m_isDraft, other.m_isDraft);
    }

private:
    int m_id = -1;
    std::string m_sender = "";
    std::string m_receiver = "";
    std::string m_subject = "";
    std::string m_body = "";

    /// Flags
    bool m_isImportant = false;
    bool m_isSent = false;
    bool m_isSpam = false;
    bool m_isDraft = false;
    bool m_isRead = false;

    // Timestamp m_timestamp;
};