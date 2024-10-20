#pragma once

#include <utility>
#include <memory>
#include "PrintColoring.hpp"
#include "Timestamp.hpp"

class Email {
public:
    Email() {}

    Email(int id, const std::string& sender, const std::string& receiver, 
          const std::string& subject, const std::string& body)
        : _id(id), _sender(sender), _receiver(receiver), _subject(subject), _body(body) {}


    ~Email() {
        ColorFormat::print("Email Destroyed: " + std::to_string(_id), Color::Red);
    }

    // // Copy constructor
    // Email(const Email& other)
    //     : _id(other._id), _sender(other._sender), _receiver(other._receiver), 
    //       _subject(other._subject), _body(other._body) {}

    // // Move constructor
    // Email(Email&& other) noexcept
    //     : _id(other._id), _sender(std::move(other._sender)), _receiver(std::move(other._receiver)),
    //     _subject(std::move(other._subject)), _body(std::move(other._body)) {}

    // // Copy assignment operator
    // Email& operator=(const Email& other) {
    //     if (this != &other) {
    //         Email tmp(other);
    //         swap(tmp);
    //     }
    //     return *this;
    // }

    // // Move assignment operator
    // Email& operator=(Email&& other) noexcept {
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
    int getId() const { return _id; }
    void setId(int id) { _id = id; }

    std::string getSender() const { return _sender; }
    void setFrom(const std::string& from) { _sender = from; }

    std::string getReceiver() const { return _receiver; }
    void setTo(const std::string& to) { _receiver = to; }

    std::string getSubject() const { return _subject; }
    void setSubject(const std::string& subject) { _subject = subject; }

    std::string getBody() const { return _body; }
    void setBody(const std::string& body) { _body = body; }

    std::string getDate() const { return _timestamp.getDate(); }
    std::string getTime() const { return _timestamp.getTime(); }

    void display() const {
        std::cout << "ID: " << _id << std::endl;
        std::cout << "From: " << _sender << std::endl;
        std::cout << "To: " << _receiver << std::endl;
        std::cout << "Subject: " << _subject << std::endl;
        std::cout << "Body: " << _body << std::endl;
        std::cout << "Date: " << _timestamp.getDate() << std::endl;
        std::cout << "Time: " << _timestamp.getTime() << std::endl;
    }

private:
    void swap(Email& other) noexcept {
        std::swap(_id, other._id);
        _sender.swap(other._sender);
        _receiver.swap(other._receiver);
        _subject.swap(other._subject);
        _body.swap(other._body);
        std::swap(isImportant, other.isImportant);
        std::swap(isSpam, other.isSpam);
        std::swap(isSent, other.isSent);
        std::swap(isStarred, other.isStarred);
        std::swap(isRead, other.isRead);
        std::swap(isPinned, other.isPinned);
        std::swap(isDraft, other.isDraft);
    }

private:
    int _id = -1;
    std::string _sender = "";
    std::string _receiver = "";
    std::string _subject = "";
    std::string _body = "";

    // Flags
    bool isImportant = false;
    bool isSent = false;
    bool isSpam = false;
    bool isDraft = false;
    bool isRead = false;
    bool isPinned = false;
    bool isStarred = false;

    Timestamp _timestamp;
};