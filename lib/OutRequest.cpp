#include "OutRequest.hpp"
#include "User.hpp"
#include "Email.hpp"
#include "ColorFormat.hpp"

OutRequest::OutRequest() 
    : receiver(nullptr), email(nullptr) {}

OutRequest::OutRequest(Email* email, User* receiver)
    : email(email), receiver(receiver) {}

OutRequest::~OutRequest() {
    // ColorFormat::print("OutRequest Destroyed" , BrightYellow);
    setNullPtr();
}

void OutRequest::setNullPtr() {
    receiver = nullptr;
    email = nullptr;
}

void OutRequest::send() {
    if (receiver && email) {
        email->setIsSent(true);
        email->setIsDraft(false);
        receiver->receiveEmail(*email);
    }
}