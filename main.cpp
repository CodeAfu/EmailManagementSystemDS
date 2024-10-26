#include <iostream>
#include <string>
#include <array>
#include <cstdlib>
#include <ctime>
#include <limits> // For std::numeric_limits

#include "ColorFormat.hpp"
#include "IdxGen.hpp"
#include "Email.hpp"
#include "User.hpp"

#define LOG(x) std::cout << x << std::endl

// Sample color formatting utility (just as a placeholder, adjust as needed)
namespace ColorFormat {
    void print(const std::string& text, const std::string& color) {
        std::cout << color << text << "\033[0m" << std::endl;
    }
}

static IdxGen s_idxGen;  // Generates Index for User and Email objects

void viewInbox() {
    std::cout << "Viewing Inbox..." << std::endl;
    // TODO: Display all received emails
}

void viewOutbox() {
    std::cout << "Viewing Outbox..." << std::endl;
    // TODO: Display all sent emails
}

void searchAndRetrieval() {
    std::cout << "Searching Emails by Keyword..." << std::endl;
    // TODO: Implement search by keyword function
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
    ColorFormat::print("\nMain Menu", "\033[36m");
    std::cout << "1. View Inbox\n"
              << "2. View Outbox\n"
              << "3. Search and Retrieval\n"
              << "4. Spam Detection and Management\n"
              << "5. Priority Handling\n"
              << "6. Exit\n"
              << "Enter your choice: ";
}


void test();

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
                ColorFormat::print("END", "\033[36m");
                return 0;
            default:
                std::cout << "Invalid choice. Please try again.\n";
        }
	}

	ColorFormat::print("END", Cyan);
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