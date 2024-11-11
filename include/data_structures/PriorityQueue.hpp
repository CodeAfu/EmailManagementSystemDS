#pragma once

#include "LinkedList.hpp"
#include "PriorityLevel.hpp"
class Inbox;

class PriorityQueue {
public:
    PriorityQueue();  // Constructor

    // Insert email based on priority
    void insert(Email* email);
    void refresh(Inbox* inbox);
    void clearAll();

    // Display functions
    void displayHighPriority() const;
    void displayMediumPriority() const;
    void displayLowPriority() const;
    void displayAll() const;

    // Other functionalities
    void displaySubjectSummary() const;
    void searchEmailsByKeyword(PriorityLevel priority, const char* keyword) const;
    void sortEmailsBySender(PriorityLevel priority);
    void markAllAsRead(PriorityLevel priority);
    void markAllAsUnread(PriorityLevel priority);

private:
    LinkedList& getQueueByPriority(PriorityLevel priority);
    const LinkedList& getQueueByPriority(PriorityLevel priority) const;

    // Custom LinkedLists for each priority level (no standard containers)
    LinkedList highPriorityQueue;
    LinkedList mediumPriorityQueue;
    LinkedList lowPriorityQueue;
};

