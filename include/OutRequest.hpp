#pragma once

#include "Email.hpp"
// struct Email;
struct User;

struct OutRequest {
    OutRequest();
    OutRequest(const Email& email, User* receiver);
    ~OutRequest();

    void setNullPtr(); 
    void send();
    
    User* receiver;
    Email email;
};