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
- Stack Data Structure [🔨]
- Queue Data Structure (Expecting different types) [❓]
- Other Data Structures (Search) [❓]
- User Inbox System: Stack [🔨]
- Email Sending System: Queue [❓]
- Email Search and Retrieval: Refer below for DS [❓]
- Spam Email Detection: Priority Queue [❓]
- Prioritize Email: Priority Queue [❓]

## Responsibilities (According to the Assignment Specification)
- Inbox Management (Stack) [❓]
- Outbox Management (Queue) [❓]
- Search and Retrieval (Hash Map / Binary Search Tree / Trie / you can be creative) [❓]
- Spam Detection (Priority Queue) [❓]
- Priority Handling (Priority Queue) [❓]

## Object Model Mappings
```cpp
class Email {
private: // Fields
    int _id; // Unique ID
    std::string _from; // Email Address of User
    std::string _to; // Email Address of User
    std::string _subject; // Subject of Email
    std::string _body; // Body of Email

    Email* _reply; // Reply to this email
    Stack<std::string> _childReplies; // List of replies this and subsequent emails 

    // Flags
    bool _isRead;
    bool _isStarred;
    bool _isPinned;
    bool _isSent;
    bool _isSpam;
    bool _isDraft;
    EmailType _type;

    // Date and Time
    Timestamp _timestamp;
}
```
![Email Object Mapping](https://i.imgur.com/HBBDRlU.png)