#include "PriorityQueue.hpp"
#include <iostream>
#include <unordered_map>
#include <algorithm>

PriorityQueue::PriorityQueue(int capacity) : capacity(capacity) {
    highPriorityQueue.reserve(capacity / 3);
    mediumPriorityQueue.reserve(capacity / 3);
    lowPriorityQueue.reserve(capacity / 3);
}

void PriorityQueue::insert(const Email& email) {
    switch (email.getPriority()) {
        case PriorityLevel::High:
            highPriorityQueue.push_back(email);
            break;
        case PriorityLevel::Medium:
            mediumPriorityQueue.push_back(email);
            break;
        case PriorityLevel::Low:
            lowPriorityQueue.push_back(email);
            break;
        default:
            lowPriorityQueue.push_back(email);
            break;
    }

    currentSize++;
    if (currentSize > capacity) {
        balanceLoad();
    }
}

void PriorityQueue::balanceLoad() {
    capacity *= 2;
    highPriorityQueue.reserve(capacity / 3);
    mediumPriorityQueue.reserve(capacity / 3);
    lowPriorityQueue.reserve(capacity / 3);
}

void PriorityQueue::displayHighPriority() const {
    if (highPriorityQueue.empty()) {
        std::cout << "No high-priority emails in the queue.\n";
        return;
    }
    std::cout << "High Priority Emails:\n";
    for (const auto& email : highPriorityQueue) {
        email.display();
        std::cout << "-------------------\n";
    }
}

void PriorityQueue::displayMediumPriority() const {
    if (mediumPriorityQueue.empty()) {
        std::cout << "No medium-priority emails in the queue.\n";
        return;
    }
    std::cout << "Medium Priority Emails:\n";
    for (const auto& email : mediumPriorityQueue) {
        email.display();
        std::cout << "-------------------\n";
    }
}

void PriorityQueue::displayLowPriority() const {
    if (lowPriorityQueue.empty()) {
        std::cout << "No low-priority emails in the queue.\n";
        return;
    }
    std::cout << "Low Priority Emails:\n";
    for (const auto& email : lowPriorityQueue) {
        email.display();
        std::cout << "-------------------\n";
    }
}

void PriorityQueue::displayAll() const {
    std::cout << "Displaying All Emails by Priority:\n";
    displayHighPriority();
    displayMediumPriority();
    displayLowPriority();
}

void PriorityQueue::displaySubjectSummary() const {
    std::cout << "Subject Summary by Priority Level:\n";

    std::cout << "\nHigh Priority:\n";
    if (highPriorityQueue.empty()) {
        std::cout << "No emails in High Priority.\n";
    }
    else {
        std::unordered_map<std::string, int> subjectCount;
        for (const auto& email : highPriorityQueue) {
            subjectCount[email.getSubject()]++;
        }
        for (const auto& pair : subjectCount) {
            std::cout << "Subject: " << pair.first << " - " << pair.second << " emails\n";
        }
    }

    std::cout << "\nMedium Priority:\n";
    if (mediumPriorityQueue.empty()) {
        std::cout << "No emails in Medium Priority.\n";
    }
    else {
        std::unordered_map<std::string, int> subjectCount;
        for (const auto& email : mediumPriorityQueue) {
            subjectCount[email.getSubject()]++;
        }
        for (const auto& pair : subjectCount) {
            std::cout << "Subject: " << pair.first << " - " << pair.second << " emails\n";
        }
    }

    std::cout << "\nLow Priority:\n";
    if (lowPriorityQueue.empty()) {
        std::cout << "No emails in Low Priority.\n";
    }
    else {
        std::unordered_map<std::string, int> subjectCount;
        for (const auto& email : lowPriorityQueue) {
            subjectCount[email.getSubject()]++;
        }
        for (const auto& pair : subjectCount) {
            std::cout << "Subject: " << pair.first << " - " << pair.second << " emails\n";
        }
    }
}

void PriorityQueue::searchEmailsByKeyword(PriorityLevel priority, const std::string& keyword) const {
    const auto& queue = getQueueByPriority(priority);
    bool found = false;

    std::cout << "Searching for \"" << keyword << "\" in "
        << (priority == PriorityLevel::High ? "High" :
            priority == PriorityLevel::Medium ? "Medium" : "Low")
        << " Priority Emails:\n";

    for (const auto& email : queue) {
        if (email.getSubject().find(keyword) != std::string::npos ||
            email.getBody().find(keyword) != std::string::npos) {
            email.display();
            std::cout << "-------------------\n";

            found = true;
        }
    }

    if (!found) {
        std::cout << "No emails found containing the keyword \"" << keyword << "\".\n";
    }
}

void PriorityQueue::sortEmailsBySender(PriorityLevel priority) {
    auto& queue = getQueueByPriority(priority);
    std::sort(queue.begin(), queue.end(), [](const Email& a, const Email& b) {
        return a.getSender() < b.getSender();
        });
    std::cout << "Sorted "
        << (priority == PriorityLevel::High ? "High" :
            priority == PriorityLevel::Medium ? "Medium" : "Low")
        << " Priority Emails by Sender.\n";

    if (!queue.empty()) {
        for (const auto& email : queue) {
            email.display();
            std::cout << "-------------------\n";
        }
    }
    else {
        std::cout << "No emails in this priority level to sort.\n";
    }
}

void PriorityQueue::markAllAsRead(PriorityLevel priority) {
    auto& queue = getQueueByPriority(priority);
    for (Email email : queue) {
        email.setIsRead(true);
    }
    std::cout << "Marked all "
        << (priority == PriorityLevel::High ? "High" :
            priority == PriorityLevel::Medium ? "Medium" : "Low")
        << " Priority Emails as Read.\n";

    for (const auto& email : queue) {
        email.display();
        std::cout << "-------------------\n";

    }
}

void PriorityQueue::markAllAsUnread(PriorityLevel priority) {
    auto& queue = getQueueByPriority(priority);
    for (Email& email : queue) {
        email.setIsRead(false);
    }
    std::cout << "Marked all "
        << (priority == PriorityLevel::High ? "High" :
            priority == PriorityLevel::Medium ? "Medium" : "Low")
        << " Priority Emails as Unread.\n";

    for (const auto& email : queue) {
        email.display();
        std::cout << "-------------------\n";

    }
}

void PriorityQueue::clearAll() {
    highPriorityQueue.clear();
    mediumPriorityQueue.clear();
    lowPriorityQueue.clear();
    currentSize = 0;
}

std::vector<Email>& PriorityQueue::getQueueByPriority(PriorityLevel priority) {
    if (priority == PriorityLevel::High) return highPriorityQueue;
    if (priority == PriorityLevel::Medium) return mediumPriorityQueue;
    return lowPriorityQueue;
}

const std::vector<Email>& PriorityQueue::getQueueByPriority(PriorityLevel priority) const {
    if (priority == PriorityLevel::High) return highPriorityQueue;
    if (priority == PriorityLevel::Medium) return mediumPriorityQueue;
    return lowPriorityQueue;
}
