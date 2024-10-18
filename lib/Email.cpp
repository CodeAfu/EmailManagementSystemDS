#include <iostream>
#include <string>

#include "Email.hpp"

Email::Email() 
    : _id(-1), _from(""), _to(""), _subject(""), _body(""),
      _isSent(false), _isRead(false), _isStarred(false), _isPinned(false), 
      _isSpam(false), _isDraft(false), _isImportant(false), _isUsed(false),
      _topEmail(nullptr), _reply(nullptr),
      _type(Regular) {}

Email::Email(int id) 
    : _id(id), _from(""), _to(""), _subject(""),  _body(""),
      _isSent(false), _isRead(false), _isStarred(false), _isPinned(false), 
      _isSpam(false), _isDraft(false), _isImportant(false), _isUsed(false),
      _topEmail(nullptr), _reply(nullptr),
      _type(Regular) {}
        
Email::Email(int id, std::string from, std::string to, std::string subject)
    : _id(id), _from(from), _to(to), _subject(subject), _body(""),
      _isSent(false), _isRead(false), _isStarred(false), _isPinned(false), 
      _isSpam(false), _isDraft(false), _isImportant(false), _isUsed(false),
      _topEmail(nullptr), _reply(nullptr),
      _type(Regular) {}

Email::Email(int id, std::string from, std::string to, std::string subject, std::string body)
    : _id(id), _from(from), _to(to), _subject(subject), _body(body),
      _isSent(false), _isRead(false), _isStarred(false), _isPinned(false), 
      _isSpam(false), _isDraft(false), _isImportant(false), _isUsed(false),
      _topEmail(nullptr), _reply(nullptr),
      _type(Regular) {

    std::cout << "Email Created: " << _id << std::endl;
}

Email::~Email() {
    delete _topEmail;
    delete _reply;
}

Email::Email(const Email& other)
    : _id(other._id),
    _from(other._from),
    _to(other._to),
    _subject(other._subject),
    _body(other._body),
    _topEmail(other._topEmail ? new Email(*other._topEmail) : nullptr),
    _reply(other._reply ? new Email(*other._reply) : nullptr),
    _childReplies(other._childReplies), // Assuming Stack has a valid copy constructor
    _isRead(other._isRead),
    _isStarred(other._isStarred),
    _isPinned(other._isPinned),
    _isSent(other._isSent),
    _isSpam(other._isSpam),
    _isDraft(other._isDraft),
    _isImportant(other._isImportant),
    _isUsed(other._isUsed),
    _type(other._type),
    _timestamp(other._timestamp) {}

Email& Email::operator=(const Email& other) {
    if (this != &other) {
        delete _topEmail;
        delete _reply;

        _id = other._id;
        _from = other._from;
        _to = other._to;
        _subject = other._subject;
        _body = other._body;
        _topEmail = other._topEmail ? new Email(*other._topEmail) : nullptr;
        _reply = other._reply ? new Email(*other._reply) : nullptr;
        _childReplies = other._childReplies;
        _isRead = other._isRead;
        _isStarred = other._isStarred;
        _isPinned = other._isPinned;
        _isSent = other._isSent;
        _isSpam = other._isSpam;
        _isDraft = other._isDraft;
        _isImportant = other._isImportant;
        _isUsed = other._isUsed;
        _type = other._type;
        _timestamp = other._timestamp;
    }
    return *this;
}

bool Email::operator==(const Email& other) const {
    return _id == other._id
        && _from == other._from
        && _to == other._to
        && _subject == other._subject
        && _body == other._body
        && _reply == other._reply
        //TODO: compare _childReplies stack
        && _type == other._type
        && _timestamp == other._timestamp;
        // TODO: Add boolean fields later
}

void Email::create(std::string message) {
    // TODO: Add to the _childReplies stack
    std::cout << "Sending email with message: " << message << std::endl;
}

void Email::read() {
    // std::cout << "From: " << *_from->getName() << std::endl;
    // std::cout << "To: " << _to.getName() << std::endl;
    std::cout << "Subject: " << _subject << std::endl;
    // TODO: Read _childReplies stack
    // std::cout << "Message: " << _childReplies.display() << std::endl;

    this->_isRead = true;
}

void Email::reply(Email& parent_email, std::string message) {
    // Build new email
    const int& id = parent_email.getId() + 1;
    const std::string& from = parent_email.getTo();
    const std::string& to = parent_email.getFrom();
    const std::string& subject = "Re: " + parent_email.getSubject();
    Email email(id, from, to, subject, message);

    // Retrive top-level email
    Email topEmail;
    if (parent_email.getTopEmail() != nullptr) {
        topEmail = *parent_email.getTopEmail();
    } else {
        topEmail = parent_email;
    }

    email.setTopEmail(topEmail);
    parent_email._reply = &email;
}

// Getters
int Email::getId() const {
    return _id;
}

std::string Email::getFrom() const {
    return _from;
}

std::string Email::getTo() const {
    return _to;
}

std::string Email::getSubject() const {
    return _subject;
}

std::string Email::getBody() const {
    return _body;
}

Email* Email::getTopEmail() const {
    return _topEmail;
}

Email* Email::getReply() const {
    return _reply;
}

std::string Email::getTime() const {
    return _timestamp.getTime();
}

std::string Email::getDate() const {
    return _timestamp.getDate();
}

int Email::getNumReplies() const {
    Email* reply = _reply;
    int count = 0;
    while (reply != nullptr) {
        reply = reply->_reply;
        count++;
    }
    return count;
}

bool Email::getIsUsed() const {
    return _isUsed;
}

// Setters
void Email::setTopEmail(Email& email) {
    this->_topEmail = &email;
}

void Email::setReply(Email& email) {
    this->_reply = &email;
}

void Email::setIsRead(bool status) {
    _isRead = status;    
}

void Email::setIsStarred(bool status) {
    _isStarred = status;    
}

void Email::setIsPinned(bool status) {
    _isPinned = status;    
}

void Email::setIsSpam(bool status) {
    _isSpam = status;    
}

void Email::setIsDraft(bool status) {
    _isDraft = status;    
}

void Email::setIsUsed(bool status) {
    _isUsed = status;
}


std::string Email::toString() {
    std::string replyExpression;
    if (getNumReplies() > 1) {
        replyExpression = "See " + std::to_string(getNumReplies()) + " replies";
    } else if (getNumReplies() == 1) {
        replyExpression = "See 1 reply";
    } else {
        replyExpression = "No replies";
    }

    std::string s = "ID: " + std::to_string(_id) + "\n";
    s += "From: " + _from + "\n";
    s += "To: " + _to + "\n";
    s += "Subject: " + _subject + "\n";
    s += "Body: " + _body + "\n";
    s += "Date: " + getDate() + "\n";
    s += "Time: " + getTime() + "\n";
    s += replyExpression + "\n";
    return s;
}

void Email::display() {
    std::cout << toString();
}
