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

        std::ifstream file("data/emails.csv");
        if (!file.is_open()) {
            ColorFormat::println("Error opening data/emails.csv. Please ensure the file exists in the correct directory.", Color::Red); 
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
            emails.emplaceBack(ResourceManager::nextEmailId(), sender, receiver, subject, body);
        }
        return emails;
    }
}