#pragma once

#include "PriorityQueue.hpp"

class Inbox;
class Outbox;

class PriorityService {
public:
    PriorityService();
    PriorityService(Inbox* inbox, Outbox* outbox);
    ~PriorityService();

public:
    PriorityQueue& getPriorityQueueRef();
    void populatePriorityQueue();


    void refreshStorage(Inbox* inbox, Outbox* outbox);

private:
    Inbox* m_inbox;
    Outbox* m_outbox;
    PriorityQueue m_priorityQueue = PriorityQueue(100);
};