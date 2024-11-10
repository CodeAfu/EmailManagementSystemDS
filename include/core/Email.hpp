#pragma once

#include <iostream>
#include <sstream>
#include <utility>
#include <memory>

#include "ColorFormat.hpp"
#include "Timestamp.hpp"
#include "PriorityLevel.hpp"

class Email {
public:
    Email();
    Email(int id, const std::string& sender, const std::string& receiver, 
          const std::string& subject, const std::string& body);
    Email(int id, const std::string& sender, const std::string& receiver, 
          const std::string& subject, const std::string& body, PriorityLevel priority);
    Email(int id, const std::string& sender, const std::string& receiver, 
          const std::string& subject, const std::string& body, PriorityLevel priority,
          bool is_important, bool is_sent, bool is_spam, bool is_draft, bool is_read);
    ~Email();
    

    /// Getters and Setters
    int getId() const;
    void setId(int id);

    std::string getSender() const;
    void setFrom(const std::string& from);

    std::string getReceiver() const;
    void setTo(const std::string& to);

    std::string getSubject() const;
    void setSubject(const std::string& subject);

    std::string getBody() const;
    void setBody(const std::string& body);

    PriorityLevel getPriority() const;
    void setPriority(PriorityLevel priority);

    // std::string getDate() const { return m_timestamp.getDate(); }
    // std::string getTime() const { return m_timestamp.getTime(); }
    
    // Boolean Flags
    bool isImportant() const;
    void setIsImportant(bool flag);

    bool isRead() const;
    void setIsRead(bool flag);

    bool isSent() const;
    void setIsSent(bool flag);

    bool isDraft() const;
    void setIsDraft(bool flag);

    bool isSpam() const;
    void setIsSpam(bool flag);

    /// Helpers
    void display() const;
    std::string toString() const;

private:
    void swap(Email& other) noexcept;

private:
    int m_id = -1;
    std::string m_sender = "";
    std::string m_receiver = "";
    std::string m_subject = "";
    std::string m_body = "";
    PriorityLevel m_priority = PriorityLevel::Low;

    /// Flags
    bool m_isImportant = false;
    bool m_isSent = false;
    bool m_isSpam = false;
    bool m_isDraft = false;
    bool m_isRead = false;

    // Timestamp m_timestamp;
};