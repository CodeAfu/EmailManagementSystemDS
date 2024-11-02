#pragma once

#include "Email.hpp"
// struct Email;
class User;

struct EmailRequest {
    EmailRequest();
    EmailRequest(Email* email, User* receiver);
    ~EmailRequest();

    void setNullPtr(); 
    void send();
    
    User* receiver;
    Email* email;
};