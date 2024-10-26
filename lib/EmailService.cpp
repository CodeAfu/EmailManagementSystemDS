#include <iostream>

#include "User.hpp"
#include "EmailService.hpp"
#include "ArrQueue.hpp"
#include "ColorFormat.hpp"
#include "OutRequest.hpp"

/// This makes more sense for a multithreaded application lol
// Static Methods
void EmailService::addRequest(Email* email, User* user) {
    OutRequest request(email, user);
    enqueueRequest(std::move(request));
    // ColorFormat::print("Added Request to EmailService: " + std::to_string(m_requests.size()), Color::Green);
}

void EmailService::sendAllRequests() {
    auto& instance = GetInstance();
    // std::lock_guard<std::mutex> lock(instance.m_mutex);
    while (instance.m_requests.size() > 0) {
        OutRequest& request = instance.m_requests.dequeueRef();
        ColorFormat::print(request.email->getSubject() + " sent to "
                           + request.receiver->getName(), Color::Cyan);
        request.send();
    }
    // ColorFormat::print("Send all Requests from EmailService: " + std::to_string(_requests.size()), Color::Green);
}

void EmailService::sendNextRequest() {
    auto& instance = GetInstance();
    // std::lock_guard<std::mutex> lock(instance.m_mutex);
    if (instance.m_requests.isEmpty()) {
        ColorFormat::print("EmailService is empty", Color::Yellow);
        return;
    }
    instance.m_requests.dequeue().send();
    ColorFormat::print("Sent a Request from EmailService: " + std::to_string(instance.m_requests.size()), Color::Green);
}

void EmailService::clear() {
    auto& instance = GetInstance();
    // std::lock_guard<std::mutex> lock(instance.m_mutex);
    while (!instance.m_requests.isEmpty()) {
        instance.m_requests.dequeue().~OutRequest();
    }
    ColorFormat::print("Cleared EmailService: " + std::to_string(instance.m_requests.size()), Color::Yellow);
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

OutRequest EmailService::getNext() {
    auto& instance = GetInstance();
    // std::lock_guard<std::mutex> lock(instance.m_mutex);
    return instance.m_requests.getFront();
}

void EmailService::displayAll() {
    auto& instance = GetInstance();
    // std::lock_guard<std::mutex> lock(instance.m_mutex);
    ArrQueue<OutRequest> temp = instance.m_requests;
    while (!instance.m_requests.isEmpty()) {
        temp.dequeue().email->display();
    }
}

void EmailService::displayNext() {
    auto& instance = GetInstance();
    // std::lock_guard<std::mutex> lock(instance.m_mutex);
    instance.getNext().email->display(); 
}

void EmailService::subscribeUser(User* user) {
    auto& instance = GetInstance();
    // std::lock_guard<std::mutex> lock(instance.m_mutex);
    instance.m_subscribers.emplaceBack(user); 
}

void EmailService::unsubscribeUser(User* user) {
    auto& instance = GetInstance();
    // std::lock_guard<std::mutex> lock(instance.m_mutex);
    for (size_t i = 0; i < instance.m_subscribers.size(); i++) {
        if (instance.m_subscribers[i] == user) {
            instance.m_subscribers[i] = nullptr;
            break;
        }
    }
}

// Internal Methods
void EmailService::enqueueRequest(OutRequest&& request) {
    auto& instance = GetInstance();
    // std::lock_guard<std::mutex> lock(instance.m_mutex);
    instance.m_requests.enqueue(std::move(request));
}
