#pragma once

#include "Timestamp.hpp"
#include "Stack.hpp"

enum EmailType {
    Regular, Important, Promotion, Social
};

class Email {
public:
    Email();
    Email(int id);
    Email(int id, std::string from, std::string to);
    Email(int id, std::string from, std::string to, std::string subject);
    bool operator==(const Email& other) const;

    void create(std::string message);
    void read();
    void reply(std::string message);
    std::string getTime();
    std::string getDate();

    std::string toString();
    void display(); // DEBUG

private:
    int _id;
    std::string _from; // Email Address of User
    std::string _to; // Email Address of User
    std::string _subject;
    Email* _reply;
    Stack<std::string> messages;

    bool _isRead;
    bool _isStarred;
    bool _isPinned;
    bool _isSpam;
    bool _isDraft;
    EmailType _type;

    Timestamp _timestamp;
};