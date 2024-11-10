#include <iostream>

#include "Email.hpp"
#include "User.hpp"
#include "Helper.hpp"
#include "ResourceManager.hpp"
#include "EmailQueue.hpp"

namespace SpamDetectionMenu {
    void run(User& user) {
        system("cls");

        SpamDetectionService& spamDetectionService = user.getSpamDetectionServiceRef();
        spamDetectionService.filterSpam();

        EmailQueue& spamBox = spamDetectionService.getSpamBox();

        if (!spamBox.isEmpty()) {
            ColorFormat::println(std::to_string(spamBox.size()) + "Spam Emails Detected", Color::Yellow);
        } else {
            ColorFormat::println("No Spam Emails Detected", Color::Green);
        }

        while (!spamBox.isEmpty()) {
            Email* spam = spamBox.dequeue();
            std::cout << "Sender: " << spam->getSender() << ", Subject: " << spam->getSubject() << "\n";
        }

        std::cout << "\n\nPress any key to continue...";
        Console::clearCin();
        std::cin.get();
        system("cls");
    }
}