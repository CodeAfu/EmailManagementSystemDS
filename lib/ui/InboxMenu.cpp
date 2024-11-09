/// Inbox Menus
#include <iostream>

#include "Helper.hpp"
#include "ResourceManager.hpp"
#include "User.hpp"
#include "Email.hpp"

namespace InboxMenu {
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

        bool found = false;
        Inbox& inbox = user.getInbox();
        Inbox temp;
        std::string choice = "";

        // loop through inbox and display unread emails
        Console::clearCin();
        while (!inbox.isEmpty() && Formatter::toLower(choice) != "q") {
            // Iterate by popping emails from original inbox
            Email email = inbox.pop();
            if (!email.isRead()) {
                found = true;
                email.display();
                email.setIsRead(true);
                choice = Console::getStringUserInput("\n\nPress any key to continue, Q to exit: ");
            }
            temp.push(email);
            system("cls");
        }

        // Display error message if all emails are read
        if (!found) {
            ColorFormat::print("All Emails have been read.", Color::Yellow);
            std::cout << "\n\nPress any key to continue..." << std::endl;
            std::cin.get();
            system("cls");
        }

        // Populate original inbox with emails
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

}