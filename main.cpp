#include <iostream>
#include <string>
#include <array>
#include <cstdlib>
#include <ctime>
#include <limits> // For std::numeric_limits
#include <fstream>
#include <sstream>
#include <algorithm> // For std::find_if
#include <stack>
#include <queue>

#include "ColorFormat.hpp"
#include "IdxGen.hpp"
#include "Email.hpp"
#include "User.hpp"

#define LOG(x) std::cout << x << std::endl

// Sample color formatting utility (just as a placeholder, adjust as needed)
static IdxGen s_idxGen;  // Generates Index for User and Email objects

void test();

void viewInbox() {
    std::cout << "Viewing Inbox..." << std::endl;
    // TODO: Display all received emails
}

void viewOutbox() {
    std::cout << "Viewing Outbox..." << std::endl;
    // TODO: Display all sent emails
}

// Function to trim whitespace from the start and end of a string
std::string trim(const std::string &str) {
    auto start = str.find_first_not_of(" \t\n");
    auto end = str.find_last_not_of(" \t\n");
    return (start == std::string::npos || end == std::string::npos) ? "" : str.substr(start, end - start + 1);
}

// Function to convert a string to lowercase
std::string toLower(const std::string &str) {
    std::string lowerStr = str;
    std::transform(lowerStr.begin(), lowerStr.end(), lowerStr.begin(), ::tolower);
    return lowerStr;
}

// Function to display all users from the users.csv file
void displayUsers() {
    std::ifstream userFile("data/users.csv");
    if (!userFile.is_open()) {
        std::cerr << "Error opening data/users.csv. Please ensure the file exists in the correct directory." << std::endl;
        return;
    }

    std::string line;
    // Read and print each line, including the header
    while (std::getline(userFile, line)) {
        std::cout << line << std::endl; // Print every line
    }

    userFile.close();
}

// Function to display emails for a specific user
void displayEmails(const std::string &userEmail) {
    std::ifstream emailFile("data/emails.csv");
    if (!emailFile.is_open()) {
        std::cerr << "Error opening data/emails.csv. Please ensure the file exists in the correct directory." << std::endl;
        return;
    }

    std::queue<std::string> emailQueue;
    std::string emailLine;
    std::cout << "Displaying emails for: " << userEmail << std::endl;

    while (std::getline(emailFile, emailLine)) {
        std::stringstream ss(emailLine);
        std::string sender, receiver, subject, body;

        std::getline(ss, sender, ',');
        std::getline(ss, receiver, ',');
        std::getline(ss, subject, ',');
        std::getline(ss, body);

        // If the email matches the user's email, store it in the queue
        if (toLower(sender) == toLower(userEmail)) {
            std::string emailContent = "From: " + sender + "\n" +
                                        "To: " + receiver + "\n" +
                                        "Subject: " + subject + "\n" +
                                        "Body: " + body + "\n" +
                                        "------------------------------------";
            emailQueue.push(emailContent);
        }
    }

    // Display all stored emails from the queue
    while (!emailQueue.empty()) {
        std::cout << emailQueue.front() << std::endl;
        emailQueue.pop();
    }

    emailFile.close();
}

// Function to search and retrieve emails based on user input
void searchAndRetrieval() {
    std::cout << "Searching Emails by Keyword..." << std::endl;

    std::string searchName;
    std::cout << "Enter the name to search: ";

    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Clear any leftover newline
    if (!std::getline(std::cin, searchName)) {
        std::cerr << "Error reading input. Please try again." << std::endl;
        return;
    }

    searchName = trim(searchName); // Trim whitespace

    std::ifstream file("data/users.csv");
    if (!file.is_open()) {
        std::cerr << "Error opening data/users.csv. Please ensure the file exists in the correct directory." << std::endl;
        return;
    }

    std::string line;
    std::stack<std::pair<std::string, std::string>> userStack; // Stack to store users

    std::getline(file, line); // Skip header
    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string name, emailAddress;

        std::getline(ss, name, ',');
        std::getline(ss, emailAddress, ',');

        name = trim(name);

        // Store user details in the stack
        userStack.push({name, emailAddress});

        // Check for matching user
        if (toLower(name) == toLower(searchName)) {
            std::cout << "User found: " << name << " - " << emailAddress << std::endl;
            displayEmails(emailAddress); // Display emails for the found user
            file.close();
            return; // Exit after finding the user
        }
    }

    // If user not found, display users from the stack
    std::cout << "User not found." << std::endl;
    while (!userStack.empty()) {
        auto user = userStack.top();
        std::cout << user.first << " - " << user.second << std::endl; // Display user details
        userStack.pop();
    }

    file.close();
}

void spamDetection() {
    std::cout << "Managing Spam Folder..." << std::endl;
    // TODO: Implement spam detection options
}

void priorityHandling() {
    std::cout << "Managing Email Priority..." << std::endl;
    // TODO: Implement priority handling options
}

void displayMenu() {
    ColorFormat::print("\nMain Menu", Color::BrightYellow);
    std::cout << "1. View Inbox\n"
              << "2. View Outbox\n"
              << "3. Search and Retrieval\n"
              << "4. Spam Detection and Management\n"
              << "5. Priority Handling\n"
              << "6. users.csv\n"
              << "7. Exit\n"
              << "Enter your choice: ";
}


int main(int argc, char** argv) {
	system("cls");
	int choice;


	test();

	// TODO: Console Flow
	while (true) {
		 displayMenu();
        std::cin >> choice;
		if (std::cin.fail()) {
            std::cout << "Invalid input. Please enter a number between 1 and 6.\n";
            std::cin.clear(); // Clear the error state
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Discard invalid input
            continue; // Restart loop
        }
        switch (choice) {
            case 1:
                viewInbox();
                break;
            case 2:
                viewOutbox();
                break;
            case 3:
                searchAndRetrieval();
                break;
            case 4:
                spamDetection();
                break;
            case 5:
                priorityHandling();
                break;
            case 6:
                displayUsers();
                break;
            case 7:
                ColorFormat::print("END", Color::Cyan);
                return 0;
            default:
                std::cout << "Invalid choice. Please try again.\n";
        }
	}

	ColorFormat::print("END", Color::Cyan);
	std::cin.get();
	return 0;
}

void test() {
	User john(s_idxGen.nextUser(), "John", "j1@example.com");
	User potato(s_idxGen.nextUser(), "Potato", "j2@example.com");

	Email email_one(s_idxGen.nextEmail(), john.getEmailAddress(), potato.getEmailAddress(), 
		"First", "Hi there, I hope you are doing well. I wanted to invite you to a meeting on Friday at 2 PM to discuss the project. Let me know if you can make it.");
	Email email_two(s_idxGen.nextEmail(), john.getEmailAddress(), potato.getEmailAddress(), 
		"Second", "Hey there, I wanted to let you know that the meeting time has changed to 3 PM on Friday. Sorry for the inconvenience.");
	Email email_three(s_idxGen.nextEmail(), john.getEmailAddress(), potato.getEmailAddress(),
		"Third", "Hi there, I just wanted to let you know that the meeting on Friday has been cancelled. I apologize for any inconvenience this may have caused. We will be rescheduling the meeting at a later time.");
	Email email_four(s_idxGen.nextEmail(), john.getEmailAddress(), potato.getEmailAddress(),
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
	std::cout << std::endl;

}