#include <iostream>

#include "User.hpp"
#include "Email.hpp"
#include "Helper.hpp"

namespace SearchAndRetrievalMenu {
    void run(const User& user) {
        system("cls");
        std::cout << "Enter the subject to search: ";
        std::string searchSubject;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Clear leftover newline
        std::getline(std::cin, searchSubject);
        searchSubject = Formatter::trim(searchSubject); // Trim input

        const Inbox& userInbox = user.getInbox(); // Get the user's inbox
        Stack<Email> emailStack = userInbox.getEmails(); // Get a copy of the emails for iteration
        const Outbox& userOutbox = user.getOutbox(); // Get the user's outbox
        LLQueue<Email> draftEmails = userOutbox.getDraftEmails(); // Get draft emails
        LLQueue<Email> sentEmails = userOutbox.getSentEmails(); // Get sent emails

        bool found = false;
        system("cls");
        std::cout << "Searching for emails with subject: " << searchSubject << std::endl << std::endl;

        // Function to search emails in a stack (inbox)
        while (!emailStack.isEmpty()) {
            Email email = emailStack.pop(); // Pop the email from the stack
            if (Formatter::toLower(email.getSubject()).find(Formatter::toLower(searchSubject)) != std::string::npos) {
                found = true;
                // Display the email details
                std::cout << "From: " << email.getSender()
                        << "\nTo: " << email.getReceiver()
                        << "\nSubject: " << email.getSubject()
                        << "\nBody: " << email.getBody()
                        << "\n------------------------------------" << std::endl;
            }
        }

        // Search in the user's sent emails
        while (!sentEmails.isEmpty()) {
            Email email = sentEmails.dequeue(); // Assuming dequeue method is available
            if (Formatter::toLower(email.getSubject()).find(Formatter::toLower(searchSubject)) != std::string::npos) {
                found = true;
                // Display the email details
                std::cout << "From: " << email.getSender() 
                        << "\nTo: " << email.getReceiver() 
                        << "\nSubject: " << email.getSubject() 
                        << "\nBody: " << email.getBody() 
                        << "\n------------------------------------" << std::endl;
            }
        }

        // Search in the user's draft emails
        while (!draftEmails.isEmpty()) {
            Email email = draftEmails.dequeue(); // Assuming dequeue method is available
            if (Formatter::toLower(email.getSubject()).find(Formatter::toLower(searchSubject)) != std::string::npos) {
                found = true;
                // Display the email details
                std::cout << "Draft From: " << email.getSender() 
                        << "\nTo: " << email.getReceiver() 
                        << "\nSubject: " << email.getSubject() 
                        << "\nBody: " << email.getBody() 
                        << "\n------------------------------------" << std::endl;
            }
        }

        if (!found) {
            std::cout << "No emails found with the subject containing: " << searchSubject << std::endl;
        }

        std::cout << "\n\nPress any key to continue...";
        std::cin.get();
        system("cls");
    }
}