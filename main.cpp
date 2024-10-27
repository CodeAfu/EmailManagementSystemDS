#include <iostream>
#include <string>
#include <array>
#include <cstdlib>
#include <ctime>
#include <limits>
#include <fstream>
#include <sstream>
#include <algorithm>

#include "ColorFormat.hpp"
#include "IdxGen.hpp"
#include "Email.hpp"
#include "User.hpp"

#define LOG(x) std::cout << x << std::endl

static IdxGen s_idxGen;  // Generates Index for User and Email objects


void viewInbox(User& user) {
    std::cout << "Viewing Inbox..." << std::endl;
    // TODO: Display all received emails
}

void viewOutbox(User& user) {
    std::cout << "Viewing Outbox..." << std::endl;
    // TODO: Display all sent emails
}

// Node structure for Binary Search Tree
struct UserNode {
    std::string name;
    std::string email;
    UserNode* left;
    UserNode* right;

    UserNode(const std::string& n, const std::string& e)
        : name(n), email(e), left(nullptr), right(nullptr) {}
};

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

// Insert a new user into the BST
UserNode* insertUser(UserNode* root, const std::string& name, const std::string& email) {
    if (root == nullptr) {
        return new UserNode(name, email);
    }
    if (toLower(name) < toLower(root->name)) {
        root->left = insertUser(root->left, name, email);
    } else {
        root->right = insertUser(root->right, name, email);
    }
    return root;
}

// Search for a user by name in the BST
UserNode* searchUser(UserNode* root, const std::string& name) {
    if (root == nullptr || toLower(root->name) == toLower(name)) {
        return root;
    }
    if (toLower(name) < toLower(root->name)) {
        return searchUser(root->left, name);
    }
    return searchUser(root->right, name);
}

void inOrderDisplay(UserNode* root) {
    if (root == nullptr) return;
    inOrderDisplay(root->left);
    std::cout << "Name: " << root->name << ", Email: " << root->email << std::endl;
    inOrderDisplay(root->right);
}

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

        if (toLower(sender) == toLower(userEmail) || toLower(receiver) == toLower(userEmail)) {
            std::cout << "From: " << sender 
                      << "\nTo: " << receiver 
                      << "\nSubject: " << subject 
                      << "\nBody: " << body 
                      << "\n------------------------------------" << std::endl;
        }
    }

    emailFile.close();
}

// Function to search and retrieve emails based on user input
void searchAndRetrieval(UserNode* root) {
    std::cout << "Enter the name to search: ";
    std::string searchName;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Clear leftover newline
    std::getline(std::cin, searchName);
    searchName = trim(searchName);

    UserNode* user = searchUser(root, searchName);
    if (user) {
        std::cout << "User found: " << user->name << " - " << user->email << std::endl;
        displayEmails(user->email);
    } else {
        std::cout << "User not found." << std::endl;
        inOrderDisplay(root);

    }
}

// Load users from CSV file and build the BST
UserNode* loadUsersToBST(DynArray<User>& users) {
    UserNode* root = nullptr;
    
    for (int i = 0; i < users.size(); i++) {
        std::string name = users[i].getName();
        std::string emailAddress = users[i].getEmailAddress();      
        name = trim(name);
        root = insertUser(root, name, emailAddress);
    }

    return root;
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
              << "6. users.csv\n"
              << "7. Exit\n"
              << "Enter your choice: ";
}

User& selectUserMenu(DynArray<User>& users) {
    while (true) {
        ColorFormat::print("Select a user", Color::Cyan);
        for (int i = 0; i < users.size(); i++) {
            std::cout << i + 1 << ". " << users[i].getName() << " - " << users[i].getEmailAddress() << std::endl;
        }
        std::cout << "Enter your choice: ";

        int choice;
        std::cin >> choice;

        if (std::cin.fail()) {
            std::cin.clear(); // Clear the error state
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Discard invalid input
            continue; // Restart loop
        }

        if (choice > 0 && choice <= users.size()) {
            system("cls");
            return users[choice - 1];
        }

        std::cout << "Invalid choice. Please enter a number between 1 and " << users.size() << std::endl << std::endl;
    }
}

DynArray<User> seedUsers() {
    DynArray<User> users;

    std::ifstream file("data/users.csv");
    if (!file.is_open()) {
        std::cerr << "Error opening data/users.csv. Please ensure the file exists in the correct directory." << std::endl;
        return users;
    }

    std::string line;
    std::getline(file, line); // Skip header
    while (std::getline(file, line)) {
        std::stringstream ss(line);
        if (line.empty()) 
            continue;

        std::string name, email;
        std::getline(ss, name, ',');
        std::getline(ss, email, ',');
        users.emplaceBack(s_idxGen.nextUser(), name, email);
    }

    return users;
}

DynArray<Email> seedEmails() {
    DynArray<Email> emails;

    std::ifstream file("data/emails.csv");
    if (!file.is_open()) {
        std::cerr << "Error opening data/emails.csv. Please ensure the file exists in the correct directory." << std::endl;
        return emails;
    }

    std::string line;
    std::getline(file, line); // Skip header
    while (std::getline(file, line)) {
        std::stringstream ss(line);
        if (line.empty()) 
            continue;

        std::string sender, receiver, subject, body;
        std::getline(ss, sender, ',');
        std::getline(ss, receiver, ',');
        std::getline(ss, subject, ',');
        std::getline(ss, body);
        emails.emplaceBack(s_idxGen.nextEmail(), sender, receiver, subject, body);
    }

    return emails;
}

void test();

int main(int argc, char** argv) {
	system("cls");
	// test();

    DynArray<User> users = seedUsers();
    DynArray<Email> emails = seedEmails();

    // Load users into the BST
    UserNode* root = loadUsersToBST(users);
    if (root == nullptr) {
        return 1; // Exit if users could not be loaded
    }
	int choice;

	// TODO: Console Flow
	while (true) {
        User& user = selectUserMenu(users);
        ColorFormat::print("Welcome, " + user.getName() + "!", Color::BrightCyan);
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
                viewInbox(user);
                break;
            case 2:
                viewOutbox(user);
                break;
            case 3:
                searchAndRetrieval(root);
                break;
            case 4:
                spamDetection(user);
                break;
            case 5:
                priorityHandling(user);
                break;
            case 6:
                inOrderDisplay(root);
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
	// std::cout << std::endl;

}