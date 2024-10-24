#pragma once

#include "Email.hpp"
// struct Email;
struct User;

struct OutRequest {
    OutRequest();
    OutRequest(const Email& email, User* receiver);
    ~OutRequest();

    // OutRequest(const OutRequest& other) {
    //     email = other.email;
    //     receiver = other.receiver;
    // }
    
    // OutRequest(OutRequest&& other) {
    //     email = std::move(other.email);
    //     receiver = other.receiver;
    // }

    // OutRequest& operator=(const OutRequest& other) {
    //     if (this != &other) {
    //         email = other.email;
    //         receiver = other.receiver;
    //     }
    //     return *this;
    // }

    // OutRequest& operator=(OutRequest&& other) {
    //     if (this != &other) {
    //         email = std::move(other.email);
    //         receiver = other.receiver;
    //     }
    //     return *this;
    // }


    void setNullPtr(); 
    void send();
    
    User* receiver;
    Email email;
};