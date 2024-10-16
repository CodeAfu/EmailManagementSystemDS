#include <iostream>
#include <string>

#include "Email.hpp"

Email::Email() 
    : _id(0), _from(""), _to(""), _subject(""),
      _isRead(false), _isStarred(false), _isPinned(false), _isSpam(false), _isDraft(false),
      _type(Regular) {}

Email::Email(int id) 
    : _id(id), _from(""), _to(""), _subject(""), 
      _isRead(false), _isStarred(false), _isPinned(false), _isSpam(false), _isDraft(false),
      _type(Regular) {}

Email::Email(int id, std::string from, std::string to)
    : _id(id), _from(from), _to(to), _subject(""),
      _isRead(false), _isStarred(false), _isPinned(false), _isSpam(false), _isDraft(false),
      _type(Regular) {}
        
Email::Email(int id, std::string from, std::string to, std::string subject)
    : _id(id), _from(from), _to(to), _subject(subject),
      _isRead(false), _isStarred(false), _isPinned(false), _isSpam(false), _isDraft(false),
      _type(Regular) {}

bool Email::operator==(const Email& other) const {
    return _id == other._id
        && _from == other._from
        && _to == other._to
        && _subject == other._subject
        //TODO: compare messages stack
        && _isRead == other._isRead
        && _isStarred == other._isStarred
        && _isPinned == other._isPinned
        && _isSpam == other._isSpam
        && _isDraft == other._isDraft
        && _type == other._type;
}

void Email::read() {
    // std::cout << "From: " << *_from->getName() << std::endl;
    // std::cout << "To: " << _to.getName() << std::endl;
    std::cout << "Subject: " << _subject << std::endl;
    // TODO: Read messages stack
    // std::cout << "Message: " << messages.display() << std::endl;

}

void Email::create(std::string message) {
    // TODO: Add to the messages stack
    std::cout << "Sending email with message: " << message << std::endl;
}

std::string Email::getTime() {
    return _timestamp.getTime();
}

std::string Email::getDate() {
    return _timestamp.getDate();
}

std::string Email::toString() {
    std::string s = "ID: " + std::to_string(_id) + "\n";
    s += "From: " + _from + "\n";
    s += "To: " + _to + "\n";
    s += "Subject: " + _subject + "\n";
    // TODO: Add messages stack
    // s += "Message: " + message + "\n";
    s += "Date: " + getDate() + "\n";
    s += "Time: " + getTime() + "\n";
    return s;
}

void Email::display() {
    std::cout << toString();
}
