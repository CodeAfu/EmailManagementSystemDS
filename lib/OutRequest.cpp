
#include "OutRequest.hpp"
#include "User.hpp"
#include "Email.hpp"
#include "ColorFormat.hpp"

OutRequest::OutRequest() 
    : receiver(nullptr) {}

OutRequest::OutRequest(Email* email, User* receiver)
    : email(email), receiver(receiver){}

OutRequest::~OutRequest() {
    ColorFormat::print("OutRequest Destroyed" , BrightYellow);
    setNullPtr();
}

void OutRequest::setNullPtr() {
    receiver = nullptr;
    email = nullptr;
}

void OutRequest::send() {
    if (receiver && email) {
        receiver->receiveEmail(*email);
    }
}