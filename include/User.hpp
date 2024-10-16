#pragma once

#include "Stack.hpp"
#include "Email.hpp"

class User {
public:
    User(int id, std::string name, std::string email_address);

public:
    bool operator==(const User& other) const;
    std::string getName() const;
    Stack<Email> getInbox() const;
    Email getEmail() const;
    void composeEmail(Email email);
    void sendEmail(Email email, User receiver);

private:
    int _id;
    std::string _name;
    std::string _emailAddress;
    Email* _composedEmail;
    Stack<Email> _inbox;
};