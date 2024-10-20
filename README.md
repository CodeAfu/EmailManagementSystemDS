# Email Management System
- Visual Studio C++ CLI project (C++17) 
- Compatible with VSCode Debug features
- Use "run.bat" to run the project on terminal

## Contribution Instructions
- Keep Code Clean and Readable
- Use the predefined Email and User classes
- **Do NOT add pointer fields to the Email class** (its for our sanity, trust me)
- Use the predefined Stack and Queue data structures. Feel free to modify or create a new one if necessary
- Make sure the project runs before you contribute your code. If possible, test with the latest changes on Github.

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
- Inbox Management (Stack) &emsp; **[Name]**
- Outbox Management (Queue) &emsp; **[Name]**
- Search and Retrieval (Hash Map / Binary Search Tree / Trie / you can be creative) &emsp; **[Name]**
- Spam Detection (Priority Queue) &emsp; **[Name]**
- Priority Handling (Priority Queue) &emsp; **[Name]**

## Object Model Mappings
```cpp
class Email {
private: // Fields
    int _id; // Unique ID
    std::string _from; // Email Address of User
    std::string _to; // Email Address of User
    std::string _subject; // Subject of Email
    std::string _body; // Body of Email

    // Flags
    bool _isRead;
    bool _isStarred;
    bool _isPinned;
    bool _isSent;
    bool _isSpam;
    bool _isDraft;

    // Date and Time
    Timestamp _timestamp;
}
```