#pragma once

#include "Timestamp.hpp"

class Email {
public:
    Email();
    Email(int id, const std::string& sender, const std::string& receiver, 
          const std::string& subject, const std::string& body);
    ~Email();

    // // Copy constructor
    Email(const Email& other);
    // // Move constructor
    Email(Email&& other) noexcept;
    // // Copy assignment operator
    Email& operator=(const Email& other);
    // // Move assignment operator
    Email& operator=(Email&& other) noexcept;

    // Getters and Setters
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

    std::string getDate() const;
    std::string getTime() const;

    void display() const;
    std::string toString() const;

private:
    void swap(Email& other) noexcept;

private:
    int _id = -1;
    std::string _sender = "";
    std::string _receiver = "";
    std::string _subject = "";
    std::string _body = "";

    // Flags
    bool _isImportant = false;
    bool _isSent = false;
    bool _isSpam = false;
    bool _isDraft = false;
    bool _isRead = false;
    bool _isPinned = false;
    bool _isStarred = false;

    Timestamp _timestamp;
};