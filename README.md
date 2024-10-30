# Email Management System
- Visual Studio C++ CLI project (C++17)
- Compatible with VSCode Debug
- gcc version: 8.x and higher (Recommended)
- Use "run.bat" to run the project on terminal

## Development Tasks
- User Class [🔨] 
- Email Class [🔨]
- Load Sample Data [✅]
    - data/emails.csv [✅]
    - data/user.csv [✅]
- Console Application Flow [🔨]
- User Inbox System [✅]
    - Stack Data Structure [✅]
- Email Sending System: Queue [🔨]
    - Queue Data Structure [✅]
- Email Search and Retrieval [❓]
    - (Refer below for DS) [❓]
- Spam Email Detection [❓]
    - Priority Queue [❓]
- Prioritize Email [❓]
    - Priority Queue [❓]

## Responsibilities (According to the Assignment Specification)
- Main Menu - **[Kee Gene]**
- Inbox Management (Stack) &emsp; **[Afzal]**
- Outbox Management (Queue) &emsp; **[Afzal]**
- Search and Retrieval (Hash Map / **Binary Search Tree** / Trie / you can be creative) &emsp; **[Kee Gene]**
- Spam Detection (Priority Queue) &emsp; **[Zaman]**
- Priority Handling (Priority Queue) &emsp; **[Osama]**

## Contribution Instructions
- Make sure your part uses the relevant data structure
- Use the predefined Email and User classes
- Feel free to use the DynArray class if you want, but dont trust it to be as optimized as std::vector
- Keep Code Clean and Readable
- Make sure the project runs before you contribute your code. If possible, test with the latest changes on Github.
- **You can refer below for the <ins>design pattern</ins> I have in mind. However if you have your our own idea that can work with this application, feel free to go for it.**

## Target Functionality
1. Select User
    1. View User's Inbox
        - Read Email
        - Search For Email
            - Email Address of Sender
            - Email Subject
        - Delete Email
        - Mark Email as Spam
        - Mark Email as Important
    2. View User's Outbox
        - Send Email
        - Search For Email
            - Email Address of Receiver
            - Email Subject
        - Delete Email from Sent Emails list
        - Mark Email as Important
    3. View Spam Folder
    4. View Important Folder

## Object Ownership
- Email - Inbox, Outbox
- User - ResourceManager

## Index Generation for User and Email
```cpp
#include "ResourceManager.hpp"

void sample() {
    User user_one(ResourceManager::nextUserId(), "John", "j1@example.com"); // ID=0
    User user_two(ResourceManager::nextUserId(), "Jane", "j2@example.com"); // ID=1

    Email email_one(ResourceManager::nextEmailId(), user_one.getEmailAddress(), user_two.getEmailAddress(), "First", "Body One."); // ID=0
    Email email_two(ResourceManager::nextEmailId(), user_one.getEmailAddress(), user_two.getEmailAddress(), "Second", "Body Two."); // ID=1
}
```

## Design Pattern
#### The project uses an Object Oriented approach so we can work on our own part without affecting others. Take a look at the User class:
```cpp
class User {
private:
    /// Storage
    Inbox m_inbox;
    Outbox m_outbox;

    /// Features
    SearchService m_searchService;
    SpamDetectionService m_spamDetectionService;
    PriorityService m_priorityService;
};
```
#### Each member is responsible for developing their part by selecting which field to modify based on the responsibility you choose. This field can then be used inside the User class to do various operations.

### Example
Inbox Class
```cpp
// Inbox.hpp
class Inbox {
public:
    Inbox() = default;
    ~Inbox() = default;

    void push(const Email& email);
    void removeEmail();
    Email peek() const;
    Email pop();
    void displayAll() const;

private:
    Stack<Email> m_emails;
};
```

Inbox uses the Stack Data Structure, used as a field variable
```cpp
// Stack.hpp
template <typename T>
class Stack {
public:
    Stack(size_t capacity = 2);
    ~Stack();
    Stack(const Stack& other) = default;
    Stack(Stack&& other) noexcept = default;
    Stack& operator=(const Stack& other) = default;
    Stack& operator=(Stack&& other) noexcept = default;

public:
    bool isEmpty() const;
    void push(const T& data);
    void push(T&& data);
    template<typename... Args>
    void emplace(Args&&... args);
    T pop();
    T peek() const;

private:
    DynArray<T> _arr;
    int _topIdx = -1;
};

```
The Inbox _inbox field is then used inside the User class
```cpp
// User.cpp
class User {
public:

    // Other methods...

    void receiveEmail(const Email& email) {
        m_inbox.push(email);
    }

    void sendEmail(const Email& email, User& receiver) {
        receiver.receiveEmail(email);
    }

private:
    Inbox m_inbox;
    // Other fields...
};
```




