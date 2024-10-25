#pragma once

#include "Queue.hpp"
#include "OutRequest.hpp"

class User;

class Outbox {
public:
    Outbox() = default;
    ~Outbox() = default;

    void addEmail(Email& email, User& user);
    void removeEmail(int id);

private:
    Queue<OutRequest> m_sendRequests;
};