#include <iostream>
#include <string>
#include <limits>
#include <fstream>
#include <sstream>
#include <algorithm>

#include "ColorFormat.hpp"
#include "Helper.hpp"
#include "ResourceManager.hpp"
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
    Console::cinClear();
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
        ColorFormat::print("Please enter ID value for an email that exists.", Color::Yellow);
    }
    email.display();

    std::cout << "\n\nPress any key to continue...";
    Console::cinClear();
    std::cin.get();
    system("cls");
}

void replyFromInbox(User& user) {    
    system("cls");
    user.viewInbox();
    std::cout << std::endl;


    std::cout << "------------------------" << std::endl;
    int choice = Console::getIntUserInput("Select the ID of Email you want to reply: ");

    // system("cls");
    Email email = user.getFromInbox(choice);

    if (email.getId() == -1) {
        ColorFormat::print("Please enter ID value for an email that exists.", Color::Yellow);
        std::cin.get();
        system("cls");
        return;
    }

    system("cls");
    email.display();
    const std::string new_subject = "Re: " + email.getSubject();

    std::cout << "Reply: \n";
    std::cout << "------------------------" << std::endl;
    std::cout << "To: " << email.getSender() << std::endl;
    std::cout << "Subject: " << new_subject << std::endl << std::endl;
    std::cout << "Body: " << std::endl;
    std::cout << "------------------------" << std::endl;

    Console::cinClear();

    std::string body;
    std::getline(std::cin, body);
    Formatter::trim(body);

    if (body.empty()) {
        ColorFormat::print("Please enter a message.", Color::Yellow);
        std::cin.get();
        system("cls");
        return;
    }

    DynArray<User*>& users = ResourceManager::getUsers();

    // user.sendEmail(Email(ResourceManager::nextEmailId(), user.getEmailAddress(), 
    //                 email.getSender(), new_subject, body));

    ColorFormat::print("Email sent", Color::Green);

    std::cout << "\n\nPress any key to continue...";
    Console::cinClear();
    std::cin.get();
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
        ColorFormat::print("Please enter ID value for an email that exists.", Color::Yellow);
        std::cin.get();
        system("cls");
        return;
    }

    email.display();
    std::cout << "\nAre you sure you want to delete this email? (Y/N): ";

    while (true) {
        char res;
        Console::cinClear();
        std::cin >> res;

        if (res == 'Y' || res == 'y') {
            user.deleteFromInbox(choice);
            ColorFormat::print("Email Deleted", Color::Red);
            Console::cinClear();
            std::cout << "\n\nPress any key to continue...";
            std::cin.get();
            break;

        } else if (res == 'N' || res == 'n') {
            break;

        } else {
            Console::cinClear();
            ColorFormat::print("Invalid input. Please enter 'Y' or 'N'.", Color::Yellow);
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
        "4. Delete Email",
        "5. Go back" 
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
        int inner_choice;
        std::cout << "Enter your choice: ";

        if (!Console::validateIntInput(choice)) {
            system("cls");
            std::cout << "Invalid input. Please enter a number between 1 and " << size << ".\n" << std::endl;
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
                deleteFromInbox(user);
                break;

            case 5:
                system("cls");
                return;

            default:
                system("cls");
                std::cout << "Invalid input. Please enter a number between 1 and " << size << ".\n" << std::endl;
                break;
        }
    }

    std::cin.get();
    system("cls");
}

void viewOutbox(User& user) {
    system("cls");
    user.viewSentEmails();

    std::cout << "\nPress any key to continue..." << std::endl;
    std::cin.clear(); // Clear the error state
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Discard invalid input
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
    ColorFormat::print("Main Menu", Color::Cyan);
    std::cout << "1. View Inbox\n"
              << "2. View Outbox\n"
              << "3. Search and Retrieval\n"
              << "4. Spam Detection and Management\n"
              << "5. Priority Handling\n"
              << "6. Back to User Selection\n"
              << "Enter your choice: ";
}

User& userSelectionMenu(DynArray<User>& users) {
    size_t size = users.size();
    while (true) {
        ColorFormat::print("Select a user", Color::Cyan);
        for (int i = 0; i < size; i++) {
            std::cout << i + 1 << ". " << users[i].getName() << " - " << users[i].getEmailAddress() << std::endl;
        }
        std::cout << size + 1 << ". Exit Application" << std::endl;
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

        if (choice == size + 1) {
            exit(0);
        }

        system("cls");
        std::cout << "Invalid choice. Please enter a number between 1 and " << users.size() << std::endl << std::endl;
    }
}

void populateData(DynArray<User>& users, DynArray<Email>& emails);
void test();

int main(int argc, char** argv) {
	system("cls");

    DynArray<User> users = Seed::users();
    DynArray<Email> emails = Seed::emails();

    ResourceManager::populateUsers(users);

    if (users.size() > 0 || emails.size() > 0) {
        populateData(users, emails);
    }


	// TODO: Console Flow
	int choice;
    User& user = userSelectionMenu(users);
    
	while (true) {
        ColorFormat::print("Welcome, " + user.getName() + "!", Color::BrightCyan);
		displayMenu();
        std::cin >> choice;
		if (std::cin.fail()) {
            std::cout << "Invalid input. Please enter a number between 1 and 6.\n";
            Console::cinClear();
            continue; // Restart loop
        }
        switch (choice) {
            case 1:
                viewInbox(user);
                break;
            case 2:
                viewOutbox(user);
                break;
            case 3:
                searchAndRetrieval(user); // Pass the selected user
                break;
            case 4:
                spamDetection(user);
                break;
            case 5:
                priorityHandling(user);
                break;
            case 6:
                system("cls");
                user = userSelectionMenu(users); // Update user reference
                break;            
            default:
                std::cout << "Invalid choice. Please try again.\n";
        }
	}
	ColorFormat::print("END", Color::Cyan);
	std::cin.get();
	return 0;
}

void populateData(DynArray<User>& users, DynArray<Email>& emails) {
    User& emma = users[0];
    User& liam = users[1];
    User& sophia = users[2];
    User& noah = users[3];
    User& mia = users[4];

    emma.sendEmail(emails[0], liam);
    sophia.sendEmail(emails[1], noah);
    mia.sendEmail(emails[2], emma);
    liam.sendEmail(emails[3], sophia);
    noah.sendEmail(emails[4], mia);
    emma.sendEmail(emails[5], noah);
    sophia.sendEmail(emails[6], mia);
    noah.sendEmail(emails[7], liam);
    sophia.sendEmail(emails[8], noah);
    noah.sendEmail(emails[9], liam); 

    // emma.sendEmail(emails[0]);
    // sophia.sendEmail(emails[1]);
    // mia.sendEmail(emails[2]);
    // liam.sendEmail(emails[3]);
    // noah.sendEmail(emails[4]);
    // emma.sendEmail(emails[5]);
    // sophia.sendEmail(emails[6]);
    // noah.sendEmail(emails[7]);
    // sophia.sendEmail(emails[8]);
    // noah.sendEmail(emails[9]);

    ColorFormat::print("User Data populated!\n", Color::BrightGreen);
}

void test() {
	User john(ResourceManager::nextUserId(), "John", "j1@example.com");
	User potato(ResourceManager::nextUserId(), "Potato", "j2@example.com");

	Email email_one(ResourceManager::nextEmailId(), john.getEmailAddress(), potato.getEmailAddress(), 
		"First", "Hi there, I hope you are doing well. I wanted to invite you to a meeting on Friday at 2 PM to discuss the project. Let me know if you can make it.");
	Email email_two(ResourceManager::nextEmailId(), john.getEmailAddress(), potato.getEmailAddress(), 
		"Second", "Hey there, I wanted to let you know that the meeting time has changed to 3 PM on Friday. Sorry for the inconvenience.");
	Email email_three(ResourceManager::nextEmailId(), john.getEmailAddress(), potato.getEmailAddress(),
		"Third", "Hi there, I just wanted to let you know that the meeting on Friday has been cancelled. I apologize for any inconvenience this may have caused. We will be rescheduling the meeting at a later time.");
	Email email_four(ResourceManager::nextEmailId(), john.getEmailAddress(), potato.getEmailAddress(),
		"Fourth", "Hi there, I just wanted to make sure that you are aware that the meeting has been cancelled. I will let you know once it has been rescheduled.");

	john.composeDraftEmail(email_one, potato);
	john.composeDraftEmail(email_two, potato);
	john.composeDraftEmail(email_three, potato);
	john.composeDraftEmail(email_four, potato);

	potato.composeDraftEmail(email_three, john);
	potato.composeDraftEmail(email_four, john);

	john.viewDraftEmails();

	std::cout << std::endl;	
	std::cout << "Outbox Size: " << john.getOutboxSize() << std::endl;
	john.sendDraftEmails();
	std::cout << "Outbox Size: " << john.getOutboxSize() << std::endl;
	std::cout << std::endl;	
	
	std::cout << std::endl;
	john.viewDraftEmails();
	std::cout << std::endl;

	std::cout << std::endl;
	potato.viewInbox();
	std::cout << std::endl;

	std::cout << std::endl;
	john.viewSentEmails();
	std::cout << std::endl;

	// Email email = potato.getFromInbox(3);
	// email.display();
	// std::cout << std::endl;

}