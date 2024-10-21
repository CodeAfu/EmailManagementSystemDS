/// TODO: Implement Later
// #include <iostream>
// #include <sstream>
// #include <utility>
// #include <memory>

// #include "Email.hpp"
// #include "ColorFormat.hpp"


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


// Helper Methods



// Member Methods
