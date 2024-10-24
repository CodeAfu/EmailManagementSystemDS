#pragma once

#include "OutRequest.hpp"
#include "Email.hpp"
#include "Queue.hpp"

// struct OutRequest;
// class Email;
class User;

class Outbox {
// Singleton
public:
// Init
    static Outbox& GetInstance() {
        static Outbox instance;
        return instance;
    };

    Outbox(const Outbox&) = delete;
    Outbox& operator=(const Outbox&) = delete;

    ~Outbox() = default;

// Static methods
    static void addRequest(const Email& email, User* user) { GetInstance().addRequestImpl(email, user); }
    static void sendAll() { GetInstance().sendAllImpl(); }
    static void sendNext() { GetInstance().sendNextImpl(); }

    static void clear() { GetInstance().clearImpl(); }
    static size_t size() { return GetInstance().sizeImpl(); }
    static bool isEmpty() { return GetInstance().isEmptyImpl(); }
    static OutRequest getNext() { return GetInstance().getNextImpl(); }
    static void displayAll() { GetInstance().displayAllImpl(); }
    static void displayFirst() { GetInstance().getNextImpl().email.display(); }
// -------------------------------
// Internal Methods
private:
    Outbox() {};
    void addRequestImpl(const Email& email, User* user);
    void sendAllImpl();
    void sendNextImpl();

    void clearImpl();
    size_t sizeImpl() const;
    bool isEmptyImpl() const;
    OutRequest getNextImpl() const;
    void displayAllImpl() const;

private:
    Queue<OutRequest> _requests; // Has pointer to Email and User
    size_t _size = 0;
};