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

    // Function to trim whitespace and newline characters from the beginning and end of a string
    void trimWhitespace(char* str) {
        char* end;

        // Trim leading spaces
        while (isspace((unsigned char)*str)) str++;

        // Trim trailing spaces
        end = str + strlen(str) - 1;
        while (end > str && isspace((unsigned char)*end)) end--;

        // Null-terminate the trimmed string
        *(end + 1) = '\0';
    }

    // Enhanced CSV line parser with support for quoted fields and trimming whitespace
    bool parseCSVLine(char* line, char* sender, char* receiver, char* subject, char* body, PriorityLevel& priority) {
        int fieldIndex = 0;
        bool inQuotes = false;
        char currentField[MAX_FIELD_LENGTH] = "";
        int currentFieldLength = 0;

        // Traverse through each character in the line
        for (int i = 0; line[i] != '\0'; ++i) {
            char ch = line[i];

            if (ch == '"') {
                inQuotes = !inQuotes;  // Toggle quotes
            }
            else if (ch == ',' && !inQuotes) {
                currentField[currentFieldLength] = '\0';
                trimWhitespace(currentField);  // Trim whitespace from current field

                if (fieldIndex == 0) strcpy_s(sender, MAX_FIELD_LENGTH, currentField);
                else if (fieldIndex == 1) strcpy_s(receiver, MAX_FIELD_LENGTH, currentField);
                else if (fieldIndex == 2) strcpy_s(subject, MAX_FIELD_LENGTH, currentField);
                else if (fieldIndex == 3) strcpy_s(body, MAX_FIELD_LENGTH, currentField);
                else return false;

                fieldIndex++;
                currentFieldLength = 0;
            }
            else {
                if (currentFieldLength < MAX_FIELD_LENGTH - 1) {
                    currentField[currentFieldLength++] = ch;
                }
            }
        }
        currentField[currentFieldLength] = '\0';
        trimWhitespace(currentField);  // Trim whitespace from priority field

        // Determine priority level based on trimmed currentField content
        if (fieldIndex == 4) {
            if (strcmp(currentField, "High Priority") == 0) {
                priority = PriorityLevel::High;
            }
            else if (strcmp(currentField, "Medium Priority") == 0) {
                priority = PriorityLevel::Medium;
            }
            else if (strcmp(currentField, "Low Priority") == 0) {
                priority = PriorityLevel::Low;
            }
            else {
                priority = PriorityLevel::Low;  // Default to Low if unrecognized
            }
        }
        else {
            return false;
        }

        return true;
    }

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
        std::cout << "10. Exit\n";
        std::cout << "-----------------------------------------------\n";
        std::cout << "Enter your choice: ";
    }
    void run(User& user) {
        PriorityQueue pq;

    // Load emails from the specified absolute path

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
                pq.displayHighPriority();
                break;
            case 2:
                pq.displayMediumPriority();
                break;
            case 3:
                pq.displayLowPriority();
                break;
            case 4:
                pq.displayAll();
                break;
            case 5:
                pq.displaySubjectSummary();
                break;
            case 6: {
                int priorityLevel;
                std::cout << "Enter priority level (1 = Low, 2 = Medium, 3 = High): ";
                std::cin >> priorityLevel;
                priority = static_cast<PriorityLevel>(priorityLevel);
                std::cout << "Enter keyword to search: ";
                std::cin.ignore();
                std::cin.getline(keyword, MAX_FIELD_LENGTH);
                pq.searchEmailsByKeyword(priority, keyword);
                break;
            }
            case 7: {
                int priorityLevel;
                std::cout << "Enter priority level (1 = Low, 2 = Medium, 3 = High): ";
                std::cin >> priorityLevel;
                priority = static_cast<PriorityLevel>(priorityLevel);
                pq.sortEmailsBySender(priority);
                std::cout << "Emails sorted by sender.\n";
                break;
            }
            case 8: {
                int priorityLevel;
                std::cout << "Enter priority level (1 = Low, 2 = Medium, 3 = High): ";
                std::cin >> priorityLevel;
                priority = static_cast<PriorityLevel>(priorityLevel);
                pq.markAllAsRead(priority);
                std::cout << "All emails marked as read.\n";
                break;
            }
            case 9: {
                int priorityLevel;
                std::cout << "Enter priority level (1 = Low, 2 = Medium, 3 = High): ";
                std::cin >> priorityLevel;
                priority = static_cast<PriorityLevel>(priorityLevel);
                pq.markAllAsUnread(priority);
                std::cout << "All emails marked as unread.\n";
                break;
            }
            case 10:
                std::cout << "Exiting the program.\n";
                return;
            default:
                std::cout << "Invalid choice. Please enter a number between 1 and 10.\n";
            }
        }
    }
}
