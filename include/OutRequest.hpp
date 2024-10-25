#pragma once

#include "Email.hpp"
// struct Email;
class User;

struct OutRequest {
    OutRequest();
    OutRequest(Email* email, User* receiver);
    ~OutRequest();

    void setNullPtr(); 
    void send();
    
    User* receiver;
    Email* email;
};