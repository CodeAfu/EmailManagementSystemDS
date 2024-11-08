#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <limits> // For std::numeric_limits

#include "User.hpp"
#include "PriorityQueueMenu.hpp"
#include "PriorityQueue.hpp"
#include "Email.hpp"

namespace PriorityQueueMenu {
    // Function to display the menu options
    void displayMenu() {
        std::cout << "Welcome to the Priority Email Management System\n";
        std::cout << "-----------------------------------------------\n";
        std::cout << "1. Display High-Priority Email\n";
        std::cout << "2. Display Medium-Priority Email\n";
        std::cout << "3. Display Low-Priority Email\n";
        std::cout << "4. Display All Emails by Priority\n";
        std::cout << "5. View Priority Summary Based on Subject\n";
        std::cout << "6. Search Emails by Keyword within Priority\n";
        std::cout << "7. Sort Emails within Priority by Sender\n";
        std::cout << "8. Mark All Emails as Read by Priority\n";
        std::cout << "9. Mark All Emails as Unread by Priority\n";
        std::cout << "0. Exit\n";
        std::cout << "-----------------------------------------------\n";
        std::cout << "Enter your choice: ";
    }

    void run(User& user) {
        system("cls");

        user.getPriorityServiceRef().populatePriorityQueue();

        int choice;
        while (true) {
            displayMenu();

            if (!(std::cin >> choice)) {
                std::cout << "Invalid input. Please enter a number between 1 and 10.\n";
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                continue;
            }

            PriorityLevel priority;
            std::string keyword;

            switch (choice) {
            case 1:
                user.getPriorityQueueRef().displayHighPriority();
                break;
            case 2:
                user.getPriorityQueueRef().displayMediumPriority();
                break;
            case 3:
                user.getPriorityQueueRef().displayLowPriority();
                break;
            case 4:
                user.getPriorityQueueRef().displayAll();
                break;
            case 5:
                user.getPriorityQueueRef().displaySubjectSummary();
                break;
            case 6:
                std::cout << "Enter priority level (1 = Low, 2 = Medium, 3 = High): ";
                int priorityLevel;
                std::cin >> priorityLevel;
                priority = static_cast<PriorityLevel>(priorityLevel);
                std::cout << "Enter keyword to search: ";
                std::cin >> keyword;
                user.getPriorityQueueRef().searchEmailsByKeyword(priority, keyword);
                break;
            case 7:
                std::cout << "Enter priority level (1 = Low, 2 = Medium, 3 = High): ";
                std::cin >> priorityLevel;
                priority = static_cast<PriorityLevel>(priorityLevel);
                user.getPriorityQueueRef().sortEmailsBySender(priority);
                std::cout << "Emails sorted by sender.\n";
                break;
            case 8:
                std::cout << "Enter priority level (1 = Low, 2 = Medium, 3 = High): ";
                std::cin >> priorityLevel;
                priority = static_cast<PriorityLevel>(priorityLevel);
                user.getPriorityQueueRef().markAllAsRead(priority);
                std::cout << "All emails marked as read.\n";
                break;
            case 9:
                std::cout << "Enter priority level (1 = Low, 2 = Medium, 3 = High): ";
                std::cin >> priorityLevel;
                priority = static_cast<PriorityLevel>(priorityLevel);
                user.getPriorityQueueRef().markAllAsUnread(priority);
                std::cout << "All emails marked as unread.\n";
                break;
            case 0:
                std::cout << "Exiting the program.\n";
                system("cls");
                return;
            default:
                std::cout << "Invalid choice. Please enter a number between 1 and 10.\n";
            }
        }
    }
}
