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
void searchAndRetrieval(const User& user) { // Ensure user is passed as a reference
    std::cout << "Enter the subject to search: ";
    std::string searchSubject;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Clear leftover newline
    std::getline(std::cin, searchSubject);
    searchSubject = Formatter::trim(searchSubject); // Trim input

    // Open the email CSV file
    std::ifstream emailFile("data/emails.csv");
    if (!emailFile.is_open()) {
        std::cerr << "Error opening data/emails.csv. Please ensure the file exists in the correct directory." << std::endl;
        return;
    }

    std::string emailLine;
    bool found = false;
    std::cout << "Searching for emails with subject: " << searchSubject << std::endl;

    // Loop through each line in the email file
    while (std::getline(emailFile, emailLine)) {
        std::stringstream ss(emailLine);
        std::string sender, receiver, subject, body;

        // Read the CSV line
        std::getline(ss, sender, ',');
        std::getline(ss, receiver, ',');
        std::getline(ss, subject, ',');
        std::getline(ss, body);

        // Trim the subject
        subject = Formatter::trim(subject);

        // Check for empty subject
        if (subject.empty()) {
            continue; // Skip if subject is empty
        }

        // Check if the email's subject matches the search subject
        if (Formatter::toLower(subject).find(Formatter::toLower(searchSubject)) != std::string::npos) {
            // Check if the user's email matches the sender or receiver
            if (user.getEmailAddress() == receiver || user.getEmailAddress() == sender) {
                found = true;
                // Display the email details
                std::cout << "From: " << sender 
                          << "\nTo: " << receiver 
                          << "\nSubject: " << subject 
                          << "\nBody: " << body 
                          << "\n------------------------------------" << std::endl;
            }
        }
    }

    if (!found) {
        std::cout << "No emails found with the subject containing: " << searchSubject << std::endl;
    }

    emailFile.close();
}

/// Inbox Menus
void viewLastFromInbox(User& user) {
    system("cls");
    user.viewLastFromInbox();

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

    Email email = user.getFromInbox(choice);
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

void replyFromInbox(User& user) {    
    system("cls");
    user.viewInbox();
    std::cout << std::endl;

    std::cout << "------------------------" << std::endl;
    int choice = Console::getIntUserInput("Select the ID of Email you want to reply: ");

    Email email = user.getFromInbox(choice);

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

    user.viewLastFromInbox();
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

    std::string choices[] = { 
        "1. View Last Email",
        "2. Select Email to View",
        "3. Reply Email",
        "4. Delete Top Email",
        "5. Delete Email",
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
            case 2: {}
                viewSelectedInboxEmail(user);
                break;
            case 3:
                replyFromInbox(user);
                break;
            case 4:
                deleteTopFromInbox(user);
                break;
            case 5:
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
void composeEmail(User& user) {
    system("cls");
    DynArray<User>& users = ResourceManager::getUsers();

    ColorFormat::println("----------------------------------------", Color::Cyan);
    ColorFormat::println("Compose a new email", Color::Cyan);
    ColorFormat::println("----------------------------------------", Color::Cyan);
    for (size_t i = 0; i < users.size(); i++) {
        ColorFormat::println(users[i].getName() + " - " + users[i].getEmailAddress(), Color::Cyan);
    }
    ColorFormat::println("----------------------------------------\n", Color::Cyan);

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

    std::string subject = Console::getStringUserInput("Subject: ");
    std::cout << std::endl;
    std::string body = Console::getStringUserInput("Body: ");
    std::cout << std::endl << std::endl; 

    Email email(ResourceManager::nextEmailId(), user.getEmailAddress(), receiver_str, subject, body);
    std::cout << "\n\n";
    bool valid = false;

    while (!valid) {
        system("cls");
        std::cout << "Email:" << std::endl;
        std::cout << "-----------------------------------" << std::endl;
        email.display();
        std::cout << "-----------------------------------" << std::endl;
        std::cout << "\n\n";
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

void selectFromSent(User& user) {
    system("cls");
    
    user.viewSentEmails();

    int choice = Console::getIntUserInput("\n\n Select the ID of Email you want to view: ");

    // Email email = user.getFromSent(choice);


    system("cls");
}

void deleteFromSent(User& user) {
    system("cls");

    system("cls");
}


void viewSentEmails(User& user) {
    system("cls");

    std::string choices[] = { 
        "1. Compose Email",
        "2. Select Email to View",
        "3. Delete Email",
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
                composeEmail(user);
                break;
            case 2:
                selectFromSent(user);
                break;
            case 3:
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
void viewDraftEmails(User& user) {
    system("cls");

    // if (user.getOutbox().getDraftEmails().isEmpty()) {
    //     std::cout << "No drafts found." << std::endl;
    //     std::cin.get();
    //     system("cls");
    //     return;
    // }

    std::string choices[] = { 
        "1. Edit Email",
        "2. Delete Email",
        "3. Send Email",
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
                break;
            case 2:
                break;
            case 3:
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
              << "2. View Draft Emails\n"
              << "3. Search and Retrieval\n"
              << "4. Spam Detection and Management\n"
              << "5. Priority Handling\n"
              << "0. Back to User Selection\n"
              << "Enter your choice: ";
}

User userSelectionMenu(DynArray<User>& users) {
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
    User user = userSelectionMenu(users);
    
	while (true) {
        ColorFormat::println("Welcome, " + user.getName() + "!", Color::BrightCyan);
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
                viewInbox(user);
                break;
            case 2:
                viewSentEmails(user);
                break;            
            case 3:
                viewDraftEmails(user);
                break;
            case 4:
                searchAndRetrieval(user); // Pass the selected user
                break;
            case 5:
                spamDetection(user);
                break;
            case 6:
                priorityHandling(user);
                break;
            case 0:
                system("cls");
                user = userSelectionMenu(users); // Update user reference
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
