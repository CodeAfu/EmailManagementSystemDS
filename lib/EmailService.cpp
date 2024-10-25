#include <iostream>

// #include "Email.hpp"
// #include "OutRequest.hpp"
#include "User.hpp"
#include "EmailService.hpp"
#include "Queue.hpp"
#include "ColorFormat.hpp"
#include "OutRequest.hpp"


// Static Methods
void EmailService::addRequest(Email* email, User* user) {
    GetInstance().addRequestImpl(email, user); 
    if (GetInstance().m_autoSend) {
        GetInstance().sendAllImpl();
    }
}

void EmailService::sendAll() {
    GetInstance().sendAllImpl(); 
}

void EmailService::sendNext() {
    GetInstance().sendNextImpl(); 
}

void EmailService::clear() {
    GetInstance().clearImpl(); 
}

size_t EmailService::size() {
    return GetInstance().sizeImpl(); 
}

bool EmailService::isEmpty() {
    return GetInstance().isEmptyImpl(); 
}

OutRequest EmailService::getNext() {
    return GetInstance().getNextImpl(); 
}

void EmailService::displayAll() {
    GetInstance().displayAllImpl(); 
}

void EmailService::displayFirst() {
    GetInstance().getNextImpl().email->display(); 
}

void EmailService::subscribeUser(User* user) {
    GetInstance().m_subscribers.emplaceBack(user); 
}

void EmailService::unsubscribeUser(User* user) {
    auto& subscribers = GetInstance().m_subscribers;
    for (size_t i = 0; i < subscribers.size(); i++) {
        if (subscribers[i] == user) {
            subscribers[i] = nullptr;
            break;
        }
    }
}

void EmailService::setAutoSend(bool flag) {
    GetInstance().m_autoSend = flag;
}

bool EmailService::isAutoSend() {
    return GetInstance().m_autoSend;
}

bool EmailService::sendEmail(Email* email, User* user) {
    if (!email || !user) {
        return false;
    }
    addRequest(email, user);
    return true;
}


// Internal Methods
void EmailService::addRequestImpl(Email* email, User* user) {
    OutRequest request(email, user);
    m_requests.enqueue(std::move(request));

    if (m_autoSend) {
        sendAllImpl();
    }
    // ColorFormat::print("Added Request to EmailService: " + std::to_string(m_requests.size()), Color::Green);
}

void EmailService::sendAllImpl() {
    while (m_requests.size() > 0) {
        m_requests.dequeue().send();
    }
    // ColorFormat::print("Send all Requests from EmailService: " + std::to_string(_requests.size()), Color::Green);
}

void EmailService::sendNextImpl() {
    if (m_requests.isEmpty()) {
        ColorFormat::print("EmailService is empty", Color::Yellow);
        return;
    }
    m_requests.dequeue().send();
    ColorFormat::print("Sent First Request from EmailService: " + std::to_string(m_requests.size()), Color::Green);
}


void EmailService::clearImpl() {
    while (!m_requests.isEmpty()) {
        m_requests.dequeue().~OutRequest();
    }
    ColorFormat::print("Cleared EmailService: " + std::to_string(m_requests.size()), Color::Yellow);
}

size_t EmailService::sizeImpl() const {
    return m_requests.size();
}

bool EmailService::isEmptyImpl() const {
    return m_requests.isEmpty();
}

OutRequest EmailService::getNextImpl() const {
    return m_requests.getFront();
}

void EmailService::displayAllImpl() const {
    Queue<OutRequest> temp = m_requests;
    while (!m_requests.isEmpty()) {
        temp.dequeue().email->display();
    }
}
