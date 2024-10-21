#include <iostream>
#include <sstream>
#include <utility>
#include <memory>

#include "Email.hpp"
#include "PrintColoring.hpp"

Email::Email() {}

Email::Email(int id, const std::string& sender, const std::string& receiver, 
        const std::string& subject, const std::string& body)
    : _id(id), _sender(sender), _receiver(receiver), _subject(subject), _body(body) {}


Email::~Email() {
    ColorFormat::print("Email Destroyed: " + std::to_string(_id), Color::Red);
}

Email::Email(const Email& other) :
    _id(other._id), _sender(other._sender), _receiver(other._receiver),
    _subject(other._subject), _body(other._body), 
    _isImportant(other._isImportant), _isSpam(other._isSpam), 
    _isSent(other._isSent), _isStarred(other._isStarred), 
    _isRead(other._isRead), _isPinned(other._isPinned), 
    _isDraft(other._isDraft), _timestamp(other._timestamp) {
    ColorFormat::print("Email Copy Constructor: " + std::to_string(other._id), Color::Cyan);
}

Email::Email(Email&& other) noexcept
    : _id(other._id), _sender(std::move(other._sender)), _receiver(std::move(other._receiver)),
    _subject(std::move(other._subject)), _body(std::move(other._body)), 
    _isImportant(other._isImportant), _isSpam(other._isSpam), 
    _isSent(other._isSent), _isStarred(other._isStarred), 
    _isRead(other._isRead), _isPinned(other._isPinned), 
    _isDraft(other._isDraft), _timestamp(std::move(other._timestamp)) {
    ColorFormat::print("Email Move Constructor: " + std::to_string(other._id), Color::Blue);
    *this = std::move(other);
}

Email& Email::operator=(const Email& other) {
    ColorFormat::print("Email Copy Assignment: " + std::to_string(other._id), Color::Cyan);
    if (this != &other) {
        _id = other._id;
        _sender = other._sender;\
        _receiver = other._receiver;
        _subject = other._subject;
        _body = other._body;
        _isImportant = other._isImportant;
        _isSpam = other._isSpam;
        _isSent = other._isSent;
        _isStarred = other._isStarred;
        _isRead = other._isRead;
        _isPinned = other._isPinned;
        _isDraft = other._isDraft;
        _timestamp = other._timestamp;
    }
    return *this;
}

Email& Email::operator=(Email&& other) noexcept {
    ColorFormat::print("Email Move Assignment: " + std::to_string(other._id), Color::Magenta); 
    if (this != &other) {
        _id = other._id;
        _sender = std::move(other._sender);
        _receiver = std::move(other._receiver);
        _subject = std::move(other._subject);
        _body = std::move(other._body);
        _isImportant = other._isImportant;
        _isSpam = other._isSpam;
        _isSent = other._isSent;
        _isStarred = other._isStarred;
        _isRead = other._isRead;
        _isPinned = other._isPinned;
        _isDraft = other._isDraft;
        _timestamp = std::move(other._timestamp);
    }
    return *this;
}

// // Copy constructor
// Email::Email(const Email& other)
//     : _id(other._id), _sender(other._sender), _receiver(other._receiver), 
//         _subject(other._subject), _body(other._body) {}

// // Move constructor
// Email::Email(Email&& other) noexcept
//     : _id(other._id), _sender(std::move(other._sender)), _receiver(std::move(other._receiver)),
//     _subject(std::move(other._subject)), _body(std::move(other._body)) {}

// // Copy assignment operator
// Email& Email::operator=(const Email& other) {
//     if (this != &other) {
//         Email tmp(other);
//         swap(tmp);
//     }
//     return *this;
// }

// // Move assignment operator
// Email& Email::operator=(Email&& other) noexcept {
//     if (this != &other) {
//         _id = other._id;
//         _sender = std::move(other._sender);
//         _receiver = std::move(other._receiver);
//         _subject = std::move(other._subject);
//         _body = std::move(other._body);
//     }
//     return *this;
// }


// Getters and Setters
int Email::getId() const { return _id; }
void Email::setId(int id) { _id = id; }

std::string Email::getSender() const { return _sender; }
void Email::setFrom(const std::string& from) { _sender = from; }

std::string Email::getReceiver() const { return _receiver; }
void Email::setTo(const std::string& to) { _receiver = to; }

std::string Email::getSubject() const { return _subject; }
void Email::setSubject(const std::string& subject) { _subject = subject; }

std::string Email::getBody() const { return _body; }
void Email::setBody(const std::string& body) { _body = body; }

std::string Email::getDate() const { return _timestamp.getDate(); }
std::string Email::getTime() const { return _timestamp.getTime(); }


// Helper Methods
void Email::display() const {
    std::cout << "ID: " << _id << std::endl;
    std::cout << "From: " << _sender << std::endl;
    std::cout << "To: " << _receiver << std::endl;
    std::cout << "Subject: " << _subject << std::endl;
    std::cout << "Body: " << _body << std::endl;
    std::cout << "Date: " << _timestamp.getDate() << std::endl;
    std::cout << "Time: " << _timestamp.getTime() << std::endl;
}


// Member Methods
void Email::swap(Email& other) noexcept {
    std::swap(_id, other._id);
    _sender.swap(other._sender);
    _receiver.swap(other._receiver);
    _subject.swap(other._subject);
    _body.swap(other._body);
    std::swap(_isImportant, other._isImportant);
    std::swap(_isSpam, other._isSpam);
    std::swap(_isSent, other._isSent);
    std::swap(_isStarred, other._isStarred);
    std::swap(_isRead, other._isRead);
    std::swap(_isPinned, other._isPinned);
    std::swap(_isDraft, other._isDraft);
}

std::string Email::toString() const {
    std::stringstream ss;
    ss << "{ID: " << _id << ", From: " << _sender 
       << ", To: " << _receiver << ", Subject: " << _subject 
       << ", Body: " << _body << ", Date: " 
       << _timestamp.getDate() << ", Time: " << _timestamp.getTime() 
       << "}";
    return ss.str();
}