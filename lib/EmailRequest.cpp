#include "EmailRequest.hpp"
#include "User.hpp"
#include "ColorFormat.hpp"

EmailRequest::EmailRequest() 
    : receiver(nullptr), email(nullptr) {}

EmailRequest::EmailRequest(Email* email, User* receiver)
    : email(email), receiver(receiver) {}

EmailRequest::~EmailRequest() {
    // setNullPtr();
}

void EmailRequest::setNullPtr() {
    receiver = nullptr;
    email = nullptr;
}

void EmailRequest::send() {
    if (receiver && email) {
        email->setIsSent(true);
        email->setIsDraft(false);
        email->setIsRead(false);
        receiver->receiveEmail(*email);
    }
}