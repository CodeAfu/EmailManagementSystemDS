#include <iostream>
#include <fstream>
#include <sstream>
#include <limits> // For std::numeric_limits
#include <cstring>

#include "User.hpp"
#include "PriorityQueueMenu.hpp"
#include "PriorityQueue.hpp"
#include "Email.hpp"

#define MAX_LINE_LENGTH 1024
#define MAX_FIELD_LENGTH 256

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
        char keyword[MAX_FIELD_LENGTH];

        switch (choice) {
            case 1:
                system("cls");
                user.getPriorityQueueRef().displayHighPriority();
                break;
            case 2:
                system("cls");
                user.getPriorityQueueRef().displayMediumPriority();
                break;
            case 3:
                system("cls");
                user.getPriorityQueueRef().displayLowPriority();
                break;
            case 4:
                system("cls");
                user.getPriorityQueueRef().displayAll();
                break;
            case 5:
                system("cls");
                user.getPriorityQueueRef().displaySubjectSummary();
                break;
            case 6: {
                system("cls");
                int priorityLevel;
                std::cout << "Enter priority level (1 = Low, 2 = Medium, 3 = High): ";
                std::cin >> priorityLevel;
                priority = static_cast<PriorityLevel>(priorityLevel);
                std::cout << "Enter keyword to search: ";
                std::cin.ignore();
                std::cin.getline(keyword, MAX_FIELD_LENGTH);
                user.getPriorityQueueRef().searchEmailsByKeyword(priority, keyword);
                break;
            }
            case 7: {
                system("cls");
                int priorityLevel;
                std::cout << "Enter priority level (1 = Low, 2 = Medium, 3 = High): ";
                std::cin >> priorityLevel;
                priority = static_cast<PriorityLevel>(priorityLevel);
                user.getPriorityQueueRef().sortEmailsBySender(priority);
                std::cout << "Emails sorted by sender.\n";
                break;
            }
            case 8: {
                system("cls");
                int priorityLevel;
                std::cout << "Enter priority level (1 = Low, 2 = Medium, 3 = High): ";
                std::cin >> priorityLevel;
                priority = static_cast<PriorityLevel>(priorityLevel);
                user.getPriorityQueueRef().markAllAsRead(priority);
                std::cout << "All emails marked as read.\n";
                break;
            }
            case 9: {
                system("cls");
                int priorityLevel;
                std::cout << "Enter priority level (1 = Low, 2 = Medium, 3 = High): ";
                std::cin >> priorityLevel;
                priority = static_cast<PriorityLevel>(priorityLevel);
                user.getPriorityQueueRef().markAllAsUnread(priority);
                std::cout << "All emails marked as unread.\n";
                break;
            }
            case 0:
                system("cls");
                std::cout << "Exiting the program.\n";
                return;
            default:
                system("cls");
                std::cout << "Invalid choice. Please enter a number between 1 and 9.\n";
            }
        }
    }
}
