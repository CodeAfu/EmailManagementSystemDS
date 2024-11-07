#include <iostream>
#include <fstream>
#include <string>

#include "ResourceManager.hpp"
#include "ColorFormat.hpp"
#include "Helper.hpp"
#include "User.hpp"

namespace Seed {
    
    DynArray<User> users() {
        DynArray<User> users;

        std::ifstream file("data/users.csv");
        if (!file.is_open()) {
            ColorFormat::println("Error opening data/users.csv. Please ensure the file exists in the correct directory.", Color::Red); 
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
            users.emplaceBack(ResourceManager::nextUserId(), name, email);
        }
        return users;
    }

    DynArray<Email> emails() {
        DynArray<Email> emails;

        // Open the CSV file
        std::ifstream file("data/emails.csv");
        if (!file.is_open()) {
            ColorFormat::println("Error opening data/emails.csv. Please ensure the file exists in the correct directory.", Color::Red); 
            return emails;
        }

        std::string line;
        std::getline(file, line); // Skip the header line

        while (std::getline(file, line)) {
            if (line.empty()) 
                continue;

            std::string sender, receiver, subject, body, priorityStr;
            PriorityLevel priority;

            std::stringstream ss(line);

            std::getline(ss, sender, ',');
            std::getline(ss, receiver, ',');
            std::getline(ss, subject, ',');

            // Parse body, which may be enclosed in quotes
            if (line.find('"', ss.tellg()) == ss.tellg()) {
                // Remove the initial quote
                ss.ignore();
                std::getline(ss, body, '"');
                // Ignore the following comma after the closing quote
                ss.ignore();
            } else {
                // Read body if not enclosed in quotes
                std::getline(ss, body, ',');
            }

            std::getline(ss, priorityStr);
            
            // Convert priority string to PriorityLevel
            try {
                int priorityInt = std::stoi(priorityStr);
                priority = static_cast<PriorityLevel>(priorityInt);
            } catch (...) {
                ColorFormat::println("Error parsing priority level in data/emails.csv. Defaulting to Low.", Color::Yellow);
                priority = PriorityLevel::Low;
            }

            emails.emplaceBack(ResourceManager::nextEmailId(), sender, receiver, subject, body, priority);
        }

        return emails;
    }
}