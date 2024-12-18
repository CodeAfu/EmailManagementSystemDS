#pragma once

#include <mutex>

#include "EmailRequest.hpp"
#include "ArrQueue.hpp"
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
    static void sendAllRequests();
    static void sendNextRequest();

    static void clear();
    static size_t size();
    static bool isEmpty();
    static EmailRequest getNext();
    static void displayAll();
    static void displayNext();
    static void subscribeUser(User* user);
    static void unsubscribeUser(User* user);
// -------------------------------
// Internal Methods
private:
    EmailService() {};
    static void enqueueRequest(EmailRequest&& request);

private:
    ArrQueue<EmailRequest> m_requests; // Has pointer to Email and User

    // std::mutex m_mutex;
};