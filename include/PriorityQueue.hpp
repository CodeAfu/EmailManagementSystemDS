#pragma once

#include <vector>

#include "Email.hpp"

class PriorityQueue {
public:
    // Constructor
    explicit PriorityQueue(int capacity = 100);

    // Insert an email into the appropriate priority queue
    void insert(const Email& email);

    // Check if there are emails in each priority queue
    bool hasHighPriority() const { return !highPriorityQueue.empty(); }
    bool hasMediumPriority() const { return !mediumPriorityQueue.empty(); }
    bool hasLowPriority() const { return !lowPriorityQueue.empty(); }

    // Display functions
    void displayHighPriority() const;
    void displayMediumPriority() const;
    void displayLowPriority() const;
    void displayAll() const;

    // New functionalities
    void displaySubjectSummary() const; // Display subject summary by priority
    void searchEmailsByKeyword(PriorityLevel priority, const std::string& keyword) const; // Search emails
    void sortEmailsBySender(PriorityLevel priority); // Sort emails by sender
    void markAllAsRead(PriorityLevel priority); // Mark all emails as read
    void markAllAsUnread(PriorityLevel priority); // Mark all emails as unread
    void clearAll();

private:
    // Helper methods
    void displaySubjectSummaryForQueue(const std::vector<Email>& queue) const;

    // Helper method to get queue by priority (non-const and const versions)
    std::vector<Email>& getQueueByPriority(PriorityLevel priority);
    const std::vector<Email>& getQueueByPriority(PriorityLevel priority) const; // Const version for read-only access

    // Separate priority queues
    std::vector<Email> highPriorityQueue;
    std::vector<Email> mediumPriorityQueue;
    std::vector<Email> lowPriorityQueue;

    // Capacity limit for emails
    int capacity;
    int currentSize = 0;

    // Helper method to balance queues if needed
    void balanceLoad();
};
