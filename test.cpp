
#include <iostream>

#include "DynArray.hpp"
#include "Email.hpp"

void addEmail(DynArray<Email>& emails) {
    Email email_one(1, "John", "j1@example.com", 
        "First", "Hi there, I hope you are doing well. I wanted to invite you to a meeting on Friday at 2 PM to discuss the project. Let me know if you can make it.");
    emails.pushBack(std::move(email_one));  
}

int main() {
    DynArray<Email> emails;
    addEmail(emails);
    std::cout << emails[0].getSubject() << std::endl;
}
