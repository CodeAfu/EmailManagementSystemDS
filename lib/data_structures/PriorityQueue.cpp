#include "PriorityQueue.hpp"
#include <iostream>

#include "Email.hpp"
#include "Inbox.hpp"

// Constructor
PriorityQueue::PriorityQueue() {}

// Insert an email into the appropriate priority queue
void PriorityQueue::insert(Email* email) {
    // Insert email based on its priority
    switch (email->getPriority()) {
    case PriorityLevel::High:
        highPriorityQueue.insert(email);
        break;
    case PriorityLevel::Medium:
        mediumPriorityQueue.insert(email);
        break;
    case PriorityLevel::Low:
        lowPriorityQueue.insert(email);
        break;
    default:
        lowPriorityQueue.insert(email);
        break;
    }
}

void PriorityQueue::clearAll() {
    highPriorityQueue.~LinkedList();
    mediumPriorityQueue.~LinkedList();
    lowPriorityQueue.~LinkedList();

    highPriorityQueue = LinkedList();
    mediumPriorityQueue = LinkedList();
    lowPriorityQueue = LinkedList();
}
// Display emails in the high priority queue
void PriorityQueue::displayHighPriority() const {
    std::cout << "High Priority Emails:\n";
    highPriorityQueue.display();
}

// Display emails in the medium priority queue
void PriorityQueue::displayMediumPriority() const {
    std::cout << "Medium Priority Emails:\n";
    mediumPriorityQueue.display();
}

// Display emails in the low priority queue
void PriorityQueue::displayLowPriority() const {
    std::cout << "Low Priority Emails:\n";
    lowPriorityQueue.display();
}

// Display all emails in each priority queue
void PriorityQueue::displayAll() const {
    displayHighPriority();
    displayMediumPriority();
    displayLowPriority();
}

// Display a summary of subjects by priority
void PriorityQueue::displaySubjectSummary() const {
    std::cout << "Subject Summary:\n";
    highPriorityQueue.displaySubjectSummary();
    mediumPriorityQueue.displaySubjectSummary();
    lowPriorityQueue.displaySubjectSummary();
}

// Search emails by keyword within a specific priority queue
void PriorityQueue::searchEmailsByKeyword(PriorityLevel priority, const char* keyword) const {
    const LinkedList& queue = getQueueByPriority(priority);
    queue.searchByKeyword(keyword);
}

// Sort emails within a specific priority queue by sender
void PriorityQueue::sortEmailsBySender(PriorityLevel priority) {
    LinkedList& queue = getQueueByPriority(priority);
    std::cout << "Sorting emails by sender in ";
    switch (priority) {
    case PriorityLevel::High:
        std::cout << "High Priority Queue...\n";
        break;
    case PriorityLevel::Medium:
        std::cout << "Medium Priority Queue...\n";
        break;
    case PriorityLevel::Low:
        std::cout << "Low Priority Queue...\n";
        break;
    }
    queue.sortBySender();
    std::cout << "Emails sorted by sender.\n";
    queue.display(); // Display sorted emails for confirmation
}

// Mark all emails as read in a specific priority queue
void PriorityQueue::markAllAsRead(PriorityLevel priority) {
    LinkedList& queue = getQueueByPriority(priority);
    std::cout << "Marking all emails as read in ";
    switch (priority) {
    case PriorityLevel::High:
        std::cout << "High Priority Queue...\n";
        break;
    case PriorityLevel::Medium:
        std::cout << "Medium Priority Queue...\n";
        break;
    case PriorityLevel::Low:
        std::cout << "Low Priority Queue...\n";
        break;
    }
    queue.markAllAsRead();
    std::cout << "All emails marked as read.\n";
    queue.display(); // Display emails to confirm read status
}

// Mark all emails as unread in a specific priority queue
void PriorityQueue::markAllAsUnread(PriorityLevel priority) {
    LinkedList& queue = getQueueByPriority(priority);
    std::cout << "Marking all emails as unread in ";
    switch (priority) {
    case PriorityLevel::High:
        std::cout << "High Priority Queue...\n";
        break;
    case PriorityLevel::Medium:
        std::cout << "Medium Priority Queue...\n";
        break;
    case PriorityLevel::Low:
        std::cout << "Low Priority Queue...\n";
        break;
    }
    queue.markAllAsUnread();
    std::cout << "All emails marked as unread.\n";
    queue.display(); // Display emails to confirm unread status
}

// Helper function to get the appropriate LinkedList based on priority
LinkedList& PriorityQueue::getQueueByPriority(PriorityLevel priority) {
    switch (priority) {
    case PriorityLevel::High: return highPriorityQueue;
    case PriorityLevel::Medium: return mediumPriorityQueue;
    case PriorityLevel::Low:
    default: return lowPriorityQueue;
    }
}

// Const version of helper function to get the appropriate LinkedList based on priority
const LinkedList& PriorityQueue::getQueueByPriority(PriorityLevel priority) const {
    switch (priority) {
    case PriorityLevel::High: return highPriorityQueue;
    case PriorityLevel::Medium: return mediumPriorityQueue;
    case PriorityLevel::Low:
    default: return lowPriorityQueue;
    }
}
