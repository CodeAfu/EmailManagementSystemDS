#include <iostream>

// #include "Email.hpp"
// #include "OutRequest.hpp"
#include "User.hpp"
#include "Outbox.hpp"
#include "Queue.hpp"
#include "ColorFormat.hpp"

void Outbox::addRequestImpl(const Email& email, User* user) {
    OutRequest request(email, user);
    _requests.enqueue(std::move(request));
    ColorFormat::print("Added Request to Outbox: " + std::to_string(_requests.size()), Color::Green);
}

void Outbox::sendAllImpl() {
    while (!_requests.size() > 0) {
        _requests.dequeue().send();
    }
    ColorFormat::print("Send all Requests from Outbox: " + std::to_string(_requests.size()), Color::Green);
}

void Outbox::sendNextImpl() {
    if (_requests.isEmpty()) {
        ColorFormat::print("Outbox is empty", Color::Yellow);
        return;
    }
    _requests.dequeue().send();
    ColorFormat::print("Sent First Request from Outbox: " + std::to_string(_requests.size()), Color::Green);
}


// TODO: implement the rest
void Outbox::clearImpl() {
    while (!_requests.isEmpty()) {
        _requests.dequeue().~OutRequest();
    }
    ColorFormat::print("Cleared Outbox: " + std::to_string(_requests.size()), Color::Green);
}

size_t Outbox::sizeImpl() const {
    return _requests.size();
}

bool Outbox::isEmptyImpl() const {
    return _requests.isEmpty();
}

OutRequest Outbox::getNextImpl() const {
    return _requests.getFront();
}

void Outbox::displayAllImpl() const {
    Queue<OutRequest> temp = _requests;
    while (!_requests.isEmpty()) {
        temp.dequeue().email.display();
    }
}
