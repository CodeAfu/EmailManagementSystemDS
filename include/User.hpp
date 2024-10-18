#pragma once

#include "Stack.hpp"
#include "Email.hpp"

class User {
public:
    User(int id, std::string name, std::string email_address);

    bool operator==(const User& other) const;

public:
    std::string getName() const;
    std::string getEmailAddress() const;
    Stack<Email> getInbox() const;
    Email getComposedEmail() const;

    void receiveEmail(Email& email);
    Email deleteEmail();
    void draftEmail(Email& email);
    void sendDraftEmail(User& receiver);
    void sendEmail(Email& email, User& receiver);

    std::string toString() const;
    void log();

private:
    bool isSendableEmail(Email& email) const;
    
private:
    int _id;
    std::string _name;
    std::string _emailAddress;
    Email* _draftEmail;
    Stack<Email> _inbox;

    // Flags
    bool _hasDraftEmail;
};