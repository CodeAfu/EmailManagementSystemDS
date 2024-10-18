#pragma once

#include "Timestamp.hpp"
#include "Stack.hpp"

enum EmailType {
    Regular, Promotion, Social
};

class Email {
public:
    Email();
    Email(int id);
    Email(int id, std::string from, std::string to, std::string subject);
    Email(int id, std::string from, std::string to, std::string subject, std::string body);
    ~Email();
    Email(const Email& other);
    Email& operator=(const Email& other);
    bool operator==(const Email& other) const;

    void create(std::string message);
    void read();
    void reply(Email& email, std::string message);

    // Getters
    int getId() const;
    std::string getFrom() const;
    std::string getTo() const;
    std::string getSubject() const;
    std::string getBody() const;
    Email* getTopEmail() const;
    Email* getReply() const;
    std::string getTime() const;
    std::string getDate() const;
    int getNumReplies() const;
    bool getIsUsed() const;

    // Setters
    void setTopEmail(Email& email);
    void setReply(Email& email);
    void setIsRead(bool status);
    void setIsStarred(bool status);
    void setIsPinned(bool status);
    void setIsSpam(bool status);
    void setIsDraft(bool status);
    void setIsUsed(bool status);

    std::string toString();
    void display(); // DEBUG

private:
    int _id;
    std::string _from; // Email Address of User
    std::string _to; // Email Address of User
    std::string _subject;
    std::string _body;

    Email* _topEmail;
    Email* _reply;
    Stack<std::string> _childReplies;

    bool _isRead;
    bool _isStarred;
    bool _isPinned;
    bool _isSent;
    bool _isSpam;
    bool _isDraft;
    bool _isImportant;
    EmailType _type;

    bool _isUsed;

    Timestamp _timestamp;
};
