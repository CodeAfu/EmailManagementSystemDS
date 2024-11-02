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

#define LOG(x) std::cout << x << std::endl


// Function to display emails for a specific user
void displayEmails(const std::string &userEmail) {
    std::ifstream emailFile("data/emails.csv");
    if (!emailFile.is_open()) {
        std::cerr << "Error opening data/emails.csv. Please ensure the file exists in the correct directory." << std::endl;
        return;
    }

    std::string emailLine;
    std::cout << "Displaying emails for: " << userEmail << std::endl;

    while (std::getline(emailFile, emailLine)) {
        std::stringstream ss(emailLine);
        std::string sender, receiver, subject, body;

        std::getline(ss, sender, ',');
        std::getline(ss, receiver, ',');
        std::getline(ss, subject, ',');
        std::getline(ss, body);

        if (Formatter::toLower(sender) == Formatter::toLower(userEmail) 
            || Formatter::toLower(receiver) == Formatter::toLower(userEmail)) {
            std::cout << "From: " << sender 
                      << "\nTo: " << receiver 
                      << "\nSubject: " << subject 
                      << "\nBody: " << body 
                      << "\n------------------------------------" << std::endl;
        }
    }
    emailFile.close();
}

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

/// Inbox Menus
void viewLastFromInbox(User& user) {
    system("cls");
    user.readLastFromInbox();

    std::cout << "\n\nPress any key to continue...";
    Console::clearCin();
    std::cin.get();
    system("cls");
}

void viewSelectedInboxEmail(User& user) {
    system("cls");

    user.viewInbox();
    std::cout << std::endl;

    std::cout << "------------------------" << std::endl;
    int choice = Console::getIntUserInput("Select the ID of Email you want to view: ");

    Email email = user.readFromInbox(choice);
    system("cls");
    if (email.getId() == -1) {
        ColorFormat::println("Please enter ID value for an email that exists.", Color::Yellow);
    }
    email.display();

    std::cout << "\n\nPress any key to continue...";
    Console::clearCin();
    std::cin.get();
    system("cls");
}

void viewUnreadEmails(User& user) {
    system("cls");

    Inbox& inbox = user.getInbox();
    Inbox temp;
    std::string choice = "";

    Console::clearCin();
    while (!inbox.isEmpty() && Formatter::toLower(choice) != "q") {
        Email email = inbox.pop();
        if (!email.isRead()) {
            email.display();
            email.setIsRead(true);
            choice = Console::getStringUserInput("\n\nPress any key to continue, Q to exit: ");
        }
        temp.push(email);
        system("cls");
    }

    while (!temp.isEmpty()) {
        inbox.push(temp.pop());
    }

    system("cls");
}

void replyFromInbox(User& user) {    
    system("cls");
    user.viewInbox();
    std::cout << std::endl;

    std::cout << "------------------------" << std::endl;
    int choice = Console::getIntUserInput("Select the ID of Email you want to reply: ");

    Email email = user.readFromInbox(choice);

    if (email.getId() == -1) {
        ColorFormat::println("Please enter ID value for an email that exists.", Color::Yellow);
        std::cin.get();
        system("cls");
        return;
    }

    system("cls");
    email.display();

    std::string receiver = email.getSender();
    const std::string new_subject = "Re: " + email.getSubject();
    std::string body;

    std::cout << "\n\nReply: \n";
    std::cout << "------------------------" << std::endl;
    std::cout << "To: " << email.getSender() << std::endl;
    std::cout << "Subject: " << new_subject << std::endl << std::endl;
    std::cout << "Body: " << std::endl;
    Console::clearCin();

    std::getline(std::cin, body);
    Formatter::trim(body);

    if (body.empty()) {
        ColorFormat::println("Please enter a message.", Color::Yellow);
        std::cin.get();
        system("cls");
        return;
    }

    std::string is_important;
    while (is_important != "Y" && is_important != "y" && is_important != "N" && is_important != "n") {
        is_important = Console::getStringUserInput("\nMark as Important? (Y/N): ");
        if (is_important == "Y" || is_important == "y") {
            email.setIsImportant(true);
        } else if (is_important == "N" || is_important == "n") {
            email.setIsImportant(false);
        } else {
            ColorFormat::println("Invalid input. Please enter Y or N.", Color::Yellow);
        }
    }

    auto& instance = ResourceManager::GetInstance();

    Email out = Email(ResourceManager::nextEmailId(), user.getEmailAddress(), receiver, new_subject, body);
    user.sendEmail(out);

    ColorFormat::println("Email sent", Color::Green);

    std::cout << "\n\nPress any key to continue...";
    std::cin.get();
    system("cls");
}

void deleteTopFromInbox(User& user) {
    system("cls");

    user.readLastFromInbox();
    std::cout << "\n\nDeleting email... Are you sure? (Y/N): ";

    while (true) {
        char res;
        Console::clearCin();
        std::cin >> res;

        if (res == 'Y' || res == 'y') {
            user.popFromInbox();
            ColorFormat::println("Email Deleted", Color::Red);
            Console::clearCin();
            std::cout << "\n\nPress any key to continue...";
            std::cin.get();
            break;
        } else if (res == 'N' || res == 'n') {
            break;
        } else {
            Console::clearCin();
            ColorFormat::println("Invalid input. Please enter 'Y' or 'N'.", Color::Yellow);
            continue;
        }
    }
    system("cls");
}

void deleteFromInbox(User& user) {
    system("cls");
    user.viewInbox();
    std::cout << std::endl;

    std::cout << "------------------------" << std::endl;
    int choice = Console::getIntUserInput("Select the ID of Email you want to delete: ");

    system("cls");
    Email email = user.getFromInbox(choice);

    if (email.getId() == -1) {
        ColorFormat::println("Please enter ID value for an email that exists.", Color::Yellow);
        std::cin.get();
        system("cls");
        return;
    }

    email.display();
    std::cout << "\nAre you sure you want to delete this email? (Y/N): ";

    while (true) {
        char res;
        Console::clearCin();
        std::cin >> res;

        if (res == 'Y' || res == 'y') {
            user.deleteFromInbox(choice);
            ColorFormat::println("Email Deleted", Color::Red);
            Console::clearCin();
            std::cout << "\n\nPress any key to continue...";
            std::cin.get();
            break;
        } else if (res == 'N' || res == 'n') {
            break;
        } else {
            Console::clearCin();
            ColorFormat::println("Invalid input. Please enter 'Y' or 'N'.", Color::Yellow);
            continue;
        }
    }
    system("cls");
}

void viewInbox(User& user) {
    system("cls");

    if (user.getInbox().isEmpty()) {
        Console::clearCin();
        ColorFormat::print("No Emails in Inbox.", Color::Yellow);
        std::cout << "\n\nPress any key to continue..." << std::endl;
        std::cin.get();
        system("cls");
        return;
    }

    std::string choices[] = { 
        "1. View Last Email",
        "2. Select Email to View",
        "3. Read Unread Emails",
        "4. Reply Email",
        "5. Delete Top Email",
        "6. Delete Email",
        "0. Go back" 
    };

    int size = sizeof(choices) / sizeof(choices[0]);

    while (true) {
        user.viewInbox();
        std::cout << std::endl;

        std::cout << "Menu" << std::endl;
        std::cout << "------------------------" << std::endl;
        for (size_t i = 0; i < size; i++) {
            std::cout << choices[i] << std::endl;
        }
        std::cout << "------------------------" << std::endl;

        int choice;
        std::cout << "Enter your choice: ";

        if (!Console::validateIntInput(choice)) {
            system("cls");
            std::cout << "Invalid input. Please enter a number between 1 and " << size - 1 << ".\n" << std::endl;
            continue;
        }

        switch (choice) {
            case 1:
                viewLastFromInbox(user);
                break;
            case 2:
                viewSelectedInboxEmail(user);
                break;
            case 3:
                viewUnreadEmails(user);
                break;
            case 4:
                replyFromInbox(user);
                break;
            case 5:
                deleteTopFromInbox(user);
                break;
            case 6:
                deleteFromInbox(user);
                break;
            case 0:
                system("cls");
                return;
            default:
                system("cls");
                std::cout << "Invalid input. Please enter a number between 1 and " << size - 1 << ".\n" << std::endl;
                break;
        }
    }

    std::cin.get();
    system("cls");
}

// Sent Emails Menu
void selectFromSent(User& user) {
    system("cls");

    user.viewSentEmails();

    int choice = Console::getIntUserInput("\n\nSelect the ID of Email you want to view: ");
    Email email = user.getFromSent(choice);
    
    if (email.getId() == -1) {
        ColorFormat::println("\nPlease enter ID value for an email that exists.", Color::Yellow);
        std::cin.get();
        system("cls");
        return;
    }

    system("cls");
    email.display();

    std::cout << "\n\nPress any key to continue..." << std::endl;
    Console::clearCin();
    std::cin.get();

    system("cls");
}

void deleteFromSent(User& user) {
    system("cls");

    user.viewSentEmails();

    int choice = Console::getIntUserInput("\n\nSelect the ID of Email you want to delete: ");

    Email email = user.getFromSent(choice);

    if (email.getId() == -1) {
        ColorFormat::println("Please enter ID value for an email that exists.", Color::Yellow);
        std::cin.get();
        system("cls");
        return;
    }

    system("cls");
    email.display();
    std::cout << "\nAre you sure you want to delete this email? (Y/N): ";

    while (true) {
        char res;
        bool deleted;
        Console::clearCin();
        std::cin >> res;

        if (res == 'Y' || res == 'y') {
            deleted = user.deleteFromSent(choice);
            if (!deleted) {
                throw std::runtime_error("Failed to delete email");
            }
            ColorFormat::println("Email Deleted", Color::Red);
            
            Console::clearCin();
            std::cout << "\n\nPress any key to continue...";
            std::cin.get();
            break;
        } else if (res == 'N' || res == 'n') {
            break;
        } else {
            Console::clearCin();
            ColorFormat::println("Invalid input. Please enter 'Y' or 'N'.", Color::Yellow);
            continue;
        }
    }
    system("cls");
}


void viewSentEmails(User& user) {
    system("cls");
    
    if (user.getOutbox().getSentEmails().isEmpty()) {
        Console::clearCin();
        ColorFormat::print("No Sent Emails", Color::Yellow);
        std::cout << "\n\nPress any key to continue..." << std::endl;
        std::cin.get();
        system("cls");
        return;
    }

    std::string choices[] = { 
        "1. Select Email to View",
        "2. Delete Email",
        "0. Go back" 
    };

    int size = sizeof(choices) / sizeof(choices[0]);

    while (true) {
        user.viewSentEmails();
        std::cout << std::endl;

        std::cout << "Menu" << std::endl;
        std::cout << "------------------------" << std::endl;
        for (size_t i = 0; i < size; i++) {
            std::cout << choices[i] << std::endl;
        }
        std::cout << "------------------------" << std::endl;

        int choice;
        std::cout << "Enter your choice: ";

        if (!Console::validateIntInput(choice)) {
            system("cls");
            std::cout << "Invalid input. Please enter a number between 1 and " << size - 1 << ".\n" << std::endl;
            continue;
        }

        switch (choice) {
            case 1:
                selectFromSent(user);
                break;
            case 2:
                deleteFromSent(user);
                break;
            case 0:
                system("cls");
                return;
            default:
                break;
        }
    }
    system("cls");
}

// Draft Emails Menu
void viewDraftEmail(User& user) {
    system("cls");

    user.viewDraftEmails();
    std::cout << std::endl;

    std::cout << "------------------------" << std::endl;
    int choice = Console::getIntUserInput("Select the ID of Email you want to view: ");

    Email email = user.getFromDraft(choice);
    system("cls");
    if (email.getId() == -1) {
        ColorFormat::println("Please enter ID value for an email that exists.", Color::Yellow);
    }

    email.display();

    std::cout << "\n\nPress any key to continue...";
    Console::clearCin();
    std::cin.get();

    system("cls");
}

void editDraftEmail(User& user) {
    system("cls");

    user.viewDraftEmails();

    int choice = Console::getIntUserInput("\n\nSelect the ID of Email you want to edit: ");

    system("cls");
    Email email = user.getFromDraft(choice);
    
    if (email.getId() == -1) {
        system("cls");
        ColorFormat::println("Please enter ID value for an email that exists.", Color::Yellow);
        std::cin.get();
        system("cls");
        return;
    }

    while (true) {
        std::cout << "----------------------------" << std::endl;
        email.display();
        std::cout << "----------------------------" << std::endl;

        std::cout << "\n\n";
        std::cout << "1. Edit Receiver" << std::endl;
        std::cout << "2. Edit Subject" << std::endl;
        std::cout << "3. Edit Body" << std::endl;
        std::cout << "4. Save Email" << std::endl;
        std::cout << "5. Send Email" << std::endl;
        std::cout << "0. Exit Without Saving" << std::endl;
        int edit_choice = Console::getIntUserInput("Enter your choice: ");
        Console::clearCin();

        if (edit_choice == 1) {
            system("cls");
            ResourceManager::printUserList();

            std::cout << "\n(Old) To: " << email.getReceiver() << std::endl << std::endl;

            std::string receiver_str = Console::getStringUserInput("To: ");
            receiver_str = Formatter::trim(receiver_str);
            User* receiver = ResourceManager::getReceiver(receiver_str);

            if (receiver == nullptr) {
                ColorFormat::println("Please enter email address of a valid user.", Color::Yellow);
                std::cin.get();
                system("cls");
                break;
            }

            email.setTo(receiver_str);
            system("cls");

        } else if (edit_choice == 2) {
            system("cls");
            std::cout << "(Old) Subject: " << email.getSubject() << std::endl << std::endl;
            std::string subject = Console::getStringUserInput("Subject: ");
            email.setSubject(subject);
            system("cls");

        } else if (edit_choice == 3) {
            system("cls");
            std::cout << "(Old) Body: " << email.getBody() << std::endl << std::endl;
            std::string body = Console::getStringUserInput("Body: ");
            email.setBody(body);
            system("cls");

        } else if (edit_choice == 4) {
            user.updateFromDraft(email);
            system("cls");
            break;

        } else if (edit_choice == 5) {
            system("cls");
            user.sendEmail(email);
            user.deleteFromDraft(email.getId());
            ColorFormat::println("Email Sent Successfully!", Color::Green);
            std::cin.get();
            break;

        } else if (edit_choice == 0) {
            break;

        } else {
            ColorFormat::println("Invalid input. Please enter a number between 1 and 3.\n", Color::Yellow);
        }
    }
    system("cls");
}

void deleteDraftEmail(User& user) {
    system("cls");

    user.viewDraftEmails();

    int choice = Console::getIntUserInput("\n\nSelect the ID of Email you want to delete: ");

    Email email = user.getFromDraft(choice);

    if (email.getId() == -1) {
        ColorFormat::println("Please enter ID value for an email that exists.", Color::Yellow);
        std::cin.get();
        system("cls");
        return;
    }

    system("cls");
    email.display();
    std::cout << "\nAre you sure you want to delete this email? (Y/N): ";

    while (true) {
        char res;
        bool deleted;
        Console::clearCin();
        std::cin >> res;

        if (res == 'Y' || res == 'y') {
            deleted = user.deleteFromDraft(choice);
            if (!deleted) {
                throw std::runtime_error("Failed to delete email");
            }
            ColorFormat::println("Email Deleted", Color::Red);
            
            Console::clearCin();
            std::cout << "\n\nPress any key to continue...";
            std::cin.get();
            break;
        } else if (res == 'N' || res == 'n') {
            break;
        } else {
            Console::clearCin();
            ColorFormat::println("Invalid input. Please enter 'Y' or 'N'.", Color::Yellow);
            continue;
        }
    }
    system("cls");
}

void sendDraftEmail(User& user) {
    system("cls");

    user.viewDraftEmails();
    std::cout << std::endl;

    std::cout << "------------------------" << std::endl;
    int choice = Console::getIntUserInput("Select the ID of Email you want to view: ");

    Email email = user.getFromDraft(choice);
    system("cls");
    if (email.getId() == -1) {
        ColorFormat::println("Please enter ID value for an email that exists.", Color::Yellow);
    }

    email.display();

    std::cout << "\nSend this email? (Y/N): ";

    while (true) {
        char res;
        Console::clearCin();
        std::cin >> res;

        if (res == 'Y' || res == 'y') {
            user.deleteFromDraft(email.getId());
            user.sendEmail(email);

            ColorFormat::println("Email Sent", Color::Green);
            Console::clearCin();
            std::cout << "\n\nPress any key to continue...";
            std::cin.get();
            break;

        } else if (res == 'N' || res == 'n') {   
            break;

        } else {
            Console::clearCin();
            ColorFormat::println("Invalid input. Please enter 'Y' or 'N'.", Color::Yellow);
            continue;
        }
    }

    system("cls");
}

void sendAllDraftEmails(User& user) {
    system("cls");

    user.viewDraftEmails();
    std::cout << std::endl;

    std::cout << "\nSending all draft emails. Are you sure? (Y/N): ";

    while (true) {
        char res;
        Console::clearCin();
        std::cin >> res;

        if (res == 'Y' || res == 'y') {
            user.sendAllDraftEmails();

            ColorFormat::println("Draft Emails Sent", Color::Green);
            Console::clearCin();
            std::cout << "\n\nPress any key to continue...";
            std::cin.get();
            break;

        } else if (res == 'N' || res == 'n') {   
            break;

        } else {
            Console::clearCin();
            ColorFormat::println("Invalid input. Please enter 'Y' or 'N'.", Color::Yellow);
            continue;
        }
    }

    system("cls");
}

void viewDraftEmails(User& user) {
    system("cls");

    if (user.getOutbox().getDraftEmails().isEmpty()) {
        Console::clearCin();
        ColorFormat::print("No Draft Emails", Color::Yellow);
        std::cout << "\n\nPress any key to continue..." << std::endl;
        std::cin.get();
        system("cls");
        return;
    }

    std::string choices[] = { 
        "1. View Email",
        "2. Edit Email",
        "3. Delete Email",
        "4. Send Email",
        "5. Send All Emails",
        "0. Go back" 
    };

    int size = sizeof(choices) / sizeof(choices[0]);

    while (true) {
        user.viewDraftEmails();
        std::cout << std::endl;

        std::cout << "Menu" << std::endl;
        std::cout << "------------------------" << std::endl;
        for (size_t i = 0; i < size; i++) {
            std::cout << choices[i] << std::endl;
        }
        std::cout << "------------------------" << std::endl;

        int choice;
        std::cout << "Enter your choice: ";

        if (!Console::validateIntInput(choice)) {
            system("cls");
            std::cout << "Invalid input. Please enter a number between 1 and " << size - 1 << ".\n" << std::endl;
            continue;
        }

        switch (choice) {
            case 1:
                viewDraftEmail(user);
                break;
            case 2:
                editDraftEmail(user);
                break;
            case 3:
                deleteDraftEmail(user);
                break;
            case 4:
                sendDraftEmail(user);
                break;
            case 5:
                sendAllDraftEmails(user);
                break;
            case 0:
                system("cls");
                return;
            default:
                break;
        }
    }

    system("cls");
}

void composeEmail(User& user) {
    system("cls");

    // Get receivers list
    ResourceManager::printUserList();

    // Search receiver
    Console::clearCin();
    std::string receiver_str = Console::getStringUserInput("To: ");
    receiver_str = Formatter::trim(receiver_str);
    User* receiver = ResourceManager::getReceiver(receiver_str);
    if (receiver == nullptr) {
        ColorFormat::println("Please enter email address of a valid user.", Color::Yellow);
        std::cin.get();
        system("cls");
        return;
    }

    // Get subject and body
    std::string subject = Console::getStringUserInput("Subject: ");
    std::cout << std::endl;
    std::string body = Console::getStringUserInput("Body: ");
    std::cout << std::endl << std::endl; 

    // Build Email
    Email email(ResourceManager::nextEmailId(), user.getEmailAddress(), receiver_str, subject, body);

    // Mark email as important?
    std::string is_important;
    while (is_important != "Y" && is_important != "y" && is_important != "N" && is_important != "n") {
        is_important = Console::getStringUserInput("Mark as Important? (Y/N): ");
        if (is_important == "Y" || is_important == "y") {
            email.setIsImportant(true);
        } else if (is_important == "N" || is_important == "n") {
            email.setIsImportant(false);
        } else {
            ColorFormat::println("Invalid input. Please enter Y or N.", Color::Yellow);
        }
    }

    // Save as draft or send email
    bool valid = false;
    while (!valid) {
        system("cls");
        std::cout << "Email:" << std::endl;
        std::cout << "-----------------------------------" << std::endl;
        email.display();
        std::cout << "-----------------------------------" << std::endl;
        std::cout << std::endl;
        std::cout << "1. Save as draft" << std::endl;
        std::cout << "2. Send email" << std::endl;
        int choice = Console::getIntUserInput("Enter your choice: ");

        if (choice == 1) {
            user.composeDraftEmail(email);
            ColorFormat::println("\nEmail Draft created successfully.", Color::Green);
            valid = true;
        } else if (choice == 2) {
            user.sendEmail(email);
            ColorFormat::println("\nEmail sent successfully.", Color::Green);
            valid = true;
        } else {
            ColorFormat::println("\nInvalid input. Please enter 1 or 2.", Color::Yellow);
        }
    }

    Console::clearCin();
    std::cin.get();
    system("cls");
}

void spamDetection(User& user) {
    std::cout << "Managing Spam Folder..." << std::endl;
    // TODO: Implement spam detection options
}

void priorityHandling(User& user) {
    std::cout << "Managing Email Priority..." << std::endl;
    // TODO: Implement priority handling options
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
            std::cout << "Invalid choice. Please enter a number between 1 and " << size + 1 << std::endl << std::endl;
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
                viewInbox(*current_user);
                break;
            case 2:
                viewSentEmails(*current_user);
                break;
            case 3:
                viewDraftEmails(*current_user);
                break;
            case 4:
                composeEmail(*current_user);
                break;
            case 5:
                searchAndRetrieval(*current_user);
                break;
            case 6:
                spamDetection(*current_user);
                break;
            case 7:
                priorityHandling(*current_user);
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
