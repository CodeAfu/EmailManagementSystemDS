#include <iostream>

#include "ResourceManager.hpp"
#include "Helper.hpp"
#include "Email.hpp"
#include "User.hpp"

#include "InboxMenu.hpp"
#include "OutboxMenu.hpp"
#include "SearchAndRetrievalMenu.hpp"
#include "SpamDetectionMenu.hpp"
#include "PriorityQueueMenu.hpp"

#define LOG(x) std::cout << x << std::endl

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
                InboxMenu::run(*current_user);
                break;
            case 2:
                OutboxMenu::Sent::run(*current_user);
                break;
            case 3:
                OutboxMenu::Draft::run(*current_user);
                break;
            case 4:
                OutboxMenu::Compose::run(*current_user);
                break;
            case 5:
                SearchAndRetrievalMenu::run(*current_user);
                break;
            case 6:
                SpamDetectionMenu::run(*current_user);
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
	return 0;
}
