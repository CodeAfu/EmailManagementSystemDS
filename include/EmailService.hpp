#pragma once

#include "OutRequest.hpp"
#include "Queue.hpp"
#include "DynArray.hpp"

// class Email;
class User;

/// @brief Singleton Service Class to send Emails
class EmailService {
public:
// Initialize
    static EmailService& GetInstance() {
        static EmailService instance;
        return instance;
    };

    EmailService(const EmailService&) = delete;
    EmailService(EmailService&&) = delete;
    EmailService& operator=(const EmailService&) = delete;
    EmailService& operator=(EmailService&&) = delete;

    ~EmailService() = default;
// -------------------------------
// Static methods
public:
    static void addRequest(Email* email, User* user);
    static void sendAll();
    static void sendNext();

    static void clear();
    static size_t size();
    static bool isEmpty();
    static OutRequest getNext();
    static void displayAll();
    static void displayFirst();
    static void subscribeUser(User* user);
    static void unsubscribeUser(User* user);
    static void setAutoSend(bool flag);
    static bool isAutoSend();
    static bool sendEmail(Email* email, User* user);
// -------------------------------
// Internal Methods
private:
    EmailService() {};
    void addRequestImpl(Email* email, User* user);
    void sendAllImpl();
    void sendNextImpl();

    void clearImpl();
    size_t sizeImpl() const;
    bool isEmptyImpl() const;
    OutRequest getNextImpl() const;
    void displayAllImpl() const;

private:
    Queue<OutRequest> m_requests; // Has pointer to Email and User
    DynArray<User*> m_subscribers;
    bool m_autoSend = false;
};