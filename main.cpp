#include <iostream>
#include <string>
#include <limits>
#include <fstream>
#include <sstream>
#include <algorithm>

#include "ResourceManager.hpp"
#include "ColorFormat.hpp"
#include "Helper.hpp"
#include "Email.hpp"
#include "User.hpp"
#include "PriorityQueueMenu.hpp"
#include "InboxMenu.hpp"
#include "OutboxMenu.hpp"

#define LOG(x) std::cout << x << std::endl

// Function to search and retrieve emails based on subject
void searchAndRetrieval(const User& user) {
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
    std::cout << "Searching for emails with subject: " << searchSubject << std::endl;

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
}


void spamDetection(User& user) {
    std::cout << "Managing Spam Folder..." << std::endl;
    // TODO: Implement spam detection options
}

void displayMenu() {
    ColorFormat::println("Main Menu", Color::Cyan);
    std::cout << "1. View Inbox\n"
              << "2. View Sent Emails\n"
              << "3. View Draft Emails\n"
              << "4. Compose Email\n"
              << "5. Search and Retrieval\n"
              << "6. Spam Detection and Management\n"
              << "7. Priority Handling\n"
              << "0. Back to User Selection\n"
              << "Enter your choice: ";
}

User& userSelectionMenu(DynArray<User>& users) {
    size_t size = users.size();

    while (true) {
        ColorFormat::println("Select a user", Color::Cyan);
        for (int i = 0; i < size; i++) {
            std::cout << i + 1 << ". " << users[i].getName() << " - " << users[i].getEmailAddress() << std::endl;
        }
        
        std::cout << "0. Exit Application" << std::endl;
        std::cout << "Enter your choice: ";

        int choice;
        std::cin >> choice;

        if (std::cin.fail()) {
            std::cin.clear(); // Clear the error state
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Discard invalid input
            system("cls");
            std::cout << "Invalid choice. Please enter a number between 1 and " << size << std::endl << std::endl;
            continue; // Restart loop
        }

        if (choice > 0 && choice <= users.size()) {
            system("cls");
            return users[choice - 1];
        }

        if (choice == 0) {
            exit(0);
        }

        system("cls");
        std::cout << "Invalid choice. Please enter a number between 1 and " << users.size() << std::endl << std::endl;
    }
}

int main(int argc, char** argv) {
	system("cls");

    ResourceManager::seedInitialData();
    ResourceManager::populateData();
    DynArray<User>& users = ResourceManager::getUsers();

	int choice;
    User* current_user = &userSelectionMenu(users);
    
	while (true) {
        ColorFormat::println("Welcome, " + current_user->getName() + "!", Color::BrightCyan);
		displayMenu();

        std::cin >> choice;

		if (std::cin.fail()) {
            system("cls");
            std::cout << "Invalid input. Please enter a number between 1 and 6.\n";
            Console::clearCin();
            continue;
        }

        switch (choice) {
            case 1:
                InboxMenu::viewInbox(*current_user);
                break;
            case 2:
                OutboxMenu::viewSentEmails(*current_user);
                break;
            case 3:
                OutboxMenu::viewDraftEmails(*current_user);
                break;
            case 4:
                OutboxMenu::composeEmail(*current_user);
                break;
            case 5:
                searchAndRetrieval(*current_user);
                break;
            case 6:
                spamDetection(*current_user);
                break;
            case 7:
                PriorityQueueMenu::run(*current_user);
                break;
            case 0:
                system("cls");
                current_user = &userSelectionMenu(users); // Update user pointer
                break;
            default:
                system("cls");
                std::cout << "Invalid choice. Please try again.\n";
        }
	}

	ColorFormat::println("END", Color::Cyan);
	std::cin.get();

	return 0;
}
