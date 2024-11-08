#include <iostream>

#include "User.hpp"
#include "EmailService.hpp"
#include "ArrQueue.hpp"
#include "ColorFormat.hpp"
#include "EmailRequest.hpp"

/// This makes more sense for a multithreaded application lol
// Static Methods
void EmailService::addRequest(Email* email, User* user) {
    EmailRequest request(email, user);
    enqueueRequest(std::move(request));
    // ColorFormat::println("Added Request to EmailService: " + std::to_string(m_requests.size()), Color::Green);
}

void EmailService::sendAllRequests() {
    auto& instance = GetInstance();
    // std::lock_guard<std::mutex> lock(instance.m_mutex);
    while (instance.m_requests.size() > 0) {
        EmailRequest request = instance.m_requests.dequeue();
        ColorFormat::println("[EmailService] \'" + request.email->getSubject() + "\' sent to \'"
                           + request.receiver->getName() + "\'", Color::BrightCyan);
        request.send();
    }
    // ColorFormat::println("Send all Requests from EmailService: " + std::to_string(_requests.size()), Color::Green);
}

void EmailService::sendNextRequest() {
    auto& instance = GetInstance();
    // std::lock_guard<std::mutex> lock(instance.m_mutex);
    if (instance.m_requests.isEmpty()) {
        ColorFormat::println("EmailService is empty", Color::Yellow);
        return;
    }
    instance.m_requests.dequeue().send();
    ColorFormat::println("[EmailService] Sent a Request from EmailService: " 
                       + std::to_string(instance.m_requests.size()), Color::BrightCyan);
}

void EmailService::clear() {
    auto& instance = GetInstance();
    // std::lock_guard<std::mutex> lock(instance.m_mutex);
    while (!instance.m_requests.isEmpty()) {
        instance.m_requests.dequeue().~EmailRequest();
    }
    ColorFormat::println("Cleared EmailService: " + std::to_string(instance.m_requests.size()), Color::Yellow);
}

size_t EmailService::size() {
    auto& instance = GetInstance();
    // std::lock_guard<std::mutex> lock(instance.m_mutex);
    return instance.m_requests.size();
}

bool EmailService::isEmpty() {
    auto& instance = GetInstance();
    // std::lock_guard<std::mutex> lock(instance.m_mutex);
    return instance.m_requests.isEmpty();
}

EmailRequest EmailService::getNext() {
    auto& instance = GetInstance();
    // std::lock_guard<std::mutex> lock(instance.m_mutex);
    return instance.m_requests.getFront();
}

void EmailService::displayAll() {
    auto& instance = GetInstance();
    // std::lock_guard<std::mutex> lock(instance.m_mutex);
    ArrQueue<EmailRequest> temp = instance.m_requests;
    while (!instance.m_requests.isEmpty()) {
        temp.dequeue().email->display();
    }
}

void EmailService::displayNext() {
    auto& instance = GetInstance();
    // std::lock_guard<std::mutex> lock(instance.m_mutex);
    instance.getNext().email->display(); 
}

// void EmailService::subscribeUser(User* user) {
//     auto& instance = GetInstance();
//     // std::lock_guard<std::mutex> lock(instance.m_mutex);
//     instance.m_subscribers.emplaceBack(user); 
// }

// void EmailService::unsubscribeUser(User* user) {
//     auto& instance = GetInstance();
//     // std::lock_guard<std::mutex> lock(instance.m_mutex);
//     for (size_t i = 0; i < instance.m_subscribers.size(); i++) {
//         if (instance.m_subscribers[i] == user) {
//             instance.m_subscribers[i] = nullptr;
//             break;
//         }
//     }
// }

// Internal Methods
void EmailService::enqueueRequest(EmailRequest&& request) {
    auto& instance = GetInstance();
    // std::lock_guard<std::mutex> lock(instance.m_mutex);
    instance.m_requests.enqueue(std::move(request));
}
