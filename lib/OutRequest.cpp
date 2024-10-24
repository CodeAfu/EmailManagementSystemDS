
#include "OutRequest.hpp"
#include "User.hpp"
#include "Email.hpp"
#include "ColorFormat.hpp"

OutRequest::OutRequest() 
    : receiver(nullptr) {}

OutRequest::OutRequest(const Email& email, User* receiver)
    : email(email), receiver(receiver){}

OutRequest::~OutRequest() {
    ColorFormat::print("OutRequest Destroyed: " + std::to_string(email.getId()), BrightYellow);
    setNullPtr();
}

void OutRequest::setNullPtr() {
    receiver = nullptr;
}

void OutRequest::send() {
    if (receiver && email.getId() != -1) {
        receiver->receiveEmail(email);
    }
}