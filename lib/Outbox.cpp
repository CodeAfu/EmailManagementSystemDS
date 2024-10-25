#include <iostream>

// #include "Email.hpp"
// #include "OutRequest.hpp"
#include "User.hpp"
#include "Outbox.hpp"
#include "Queue.hpp"
#include "ColorFormat.hpp"

void Outbox::addRequestImpl(Email* email, User* user) {
    OutRequest request(email, user);
    m_requests.enqueue(std::move(request));
    // ColorFormat::print("Added Request to Outbox: " + std::to_string(m_requests.size()), Color::Green);
}

void Outbox::sendAllImpl() {
    while (m_requests.size() > 0) {
        m_requests.dequeue().send();
    }
    // ColorFormat::print("Send all Requests from Outbox: " + std::to_string(_requests.size()), Color::Green);
}

void Outbox::sendNextImpl() {
    if (m_requests.isEmpty()) {
        ColorFormat::print("Outbox is empty", Color::Yellow);
        return;
    }
    m_requests.dequeue().send();
    ColorFormat::print("Sent First Request from Outbox: " + std::to_string(m_requests.size()), Color::Green);
}


// TODO: implement the rest
void Outbox::clearImpl() {
    while (!m_requests.isEmpty()) {
        m_requests.dequeue().~OutRequest();
    }
    ColorFormat::print("Cleared Outbox: " + std::to_string(m_requests.size()), Color::Yellow);
}

size_t Outbox::sizeImpl() const {
    return m_requests.size();
}

bool Outbox::isEmptyImpl() const {
    return m_requests.isEmpty();
}

OutRequest Outbox::getNextImpl() const {
    return m_requests.getFront();
}

void Outbox::displayAllImpl() const {
    Queue<OutRequest> temp = m_requests;
    while (!m_requests.isEmpty()) {
        temp.dequeue().email->display();
    }
}
