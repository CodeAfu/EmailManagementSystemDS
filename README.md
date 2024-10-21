# Email Management System
- Visual Studio C++ CLI project (C++17) 
- Compatible with VSCode Debug features
- Use "run.bat" to run the project on terminal

## Development Tasks
- User Class [🔨] 
- Email Class [🔨]
- User Inbox System [🔨]
    - Stack Data Structure [✅]
- Email Sending System: Queue [❓]
    - Queue Data Structure [❓]
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
- Search and Retrieval (Hash Map / Binary Search Tree / Trie / you can be creative) &emsp; **[Kee Gene]**
- Spam Detection (Priority Queue) &emsp; **[Name]**
- Priority Handling (Priority Queue) &emsp; **[Name]**

## Contribution Instructions
- Make sure your part uses the relevant data structure
- Use the predefined Email and User classes
- **Do NOT add pointer fields to the Email class** (its for our sanity, trust me)
- Feel free to use the DynArray class if you want, but dont trust it to be as optimized as std::vector
- Keep Code Clean and Readable
- Make sure the project runs before you contribute your code. If possible, test with the latest changes on Github.

#### The project uses an Object Oriented approach so we can work on our own part without affecting others. Take a look at the User class:
```cpp
public class User {
private:
    /// Storage
    Inbox _inbox;
    Outbox _outbox;

    /// Features
    SearchService _searchService;
    SpamDetectionService _spamDetectionService;
    PriorityService _priorityService;
};
```
#### Each member is responsible for developing their part by selecting which field to modify based on the responsibility you choose. This field can then be used inside the User class to do various operations.

### Example
Inbox Class
```cpp
// Inbox.hpp
#pragma once

#include "Stack.hpp"

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
    Stack<Email> _emails;
};
```

Inbox uses Stack Data its own defined Data Strcuture
```cpp
// Stack.hpp
#pragma once

#include "Email.hpp"
#include "PrintColoring.hpp"
#include "DynArray.hpp"

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

    // Other methods..
    .
    void receiveEmail(const Email& email) {
        _inbox.push(email);
    }

    void sendEmail(const Email& email, User& receiver) {
        receiver.receiveEmail(email);
    }

private:
    Inbox _inbox;
    // Other fields...
};
```
