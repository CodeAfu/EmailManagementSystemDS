#pragma once

#include "Stack.hpp"
#include "Email.hpp"

class User {
public:
    User(int id, std::string name, std::string email_address);

    bool operator==(const User& other) const;
    void setStackConfig(size_t capacity, int increment_value);
public:
    std::string getName() const;
    Stack<Email> getInbox() const;
    Email getEmail() const;
    Email deleteEmail() const;
    void composeEmail(Email email);
    void sendEmail(Email email, User receiver);

private:
    int _id;
    std::string _name;
    std::string _emailAddress;
    Email* _composedEmail;
    Stack<Email> _inbox;
};