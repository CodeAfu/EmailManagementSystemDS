#include <iostream>
#include <limits>

#include "Helper.hpp"

namespace Console {
    
    void clearCin() {
        std::cin.clear(); // Clear the error state
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Discard invalid input
    }

    bool validateIntInput(int& choice) {
        std::cin >> choice;
        if (std::cin.fail()) {
            clearCin(); // Clear and discard invalid input
            return false;
        }
        return true;
    }

    int getIntUserInput(const std::string& message) {
        int choice;
        while (true) {
            std::cout << message;
            if (!validateIntInput(choice)) {
                std::cout << "Invalid input. Please enter a number." << std::endl;
                continue;
            }
            return choice;
        }
    }

    std::string getStringUserInput(const std::string& message) {
        std::string choice;
        std::cout << message;
        std::getline(std::cin, choice);
        return choice;
    }
}
