#include <iostream>

#include "Outbox.hpp"
#include "User.hpp"
#include "Helper.hpp"
#include "ResourceManager.hpp"

namespace OutboxMenu::Sent {

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

}


namespace OutboxMenu::Draft {
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
                User* receiver = ResourceManager::getUser(receiver_str);

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

}

namespace OutboxMenu::Compose {
    void composeEmail(User& user) {
        system("cls");

        // Get receivers list
        ResourceManager::printUserList();

        // Search receiver
        Console::clearCin();
        std::string receiver_str = Console::getStringUserInput("To: ");
        receiver_str = Formatter::trim(receiver_str);
        User* receiver = ResourceManager::getUser(receiver_str);
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
        PriorityLevel priority = email.getPriority();

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
}