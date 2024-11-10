#include <iostream>

#include "ResourceManager.hpp"
#include "IdxGen.hpp"
#include "UserTree.hpp"
#include "Helper.hpp"
#include "Email.hpp"
#include "User.hpp"


ResourceManager& ResourceManager::GetInstance() {
    static ResourceManager instance;
    return instance;
}

void ResourceManager::seedInitialData() {
    auto& instance = GetInstance();
    DynArray<User> users = Seed::users();

    for (int i = 0; i < users.size(); i++) {
        int id = users[i].getId();
        std::string name = users[i].getName();
        std::string email = users[i].getEmailAddress();

        instance.m_users.emplaceBack(id, name, email);
        User& user = instance.m_users[i];
        instance.m_userTree.insertUser(id);
    }
}

void ResourceManager::populateData() {
    DynArray<User>& users = GetInstance().getUsers();

    // Exit if no users
    if (users.isEmpty()) {
        ColorFormat::println("[ERROR] No users found. Please seed the data first.", Color::Red);
        return;
    } 

    DynArray<Email> emails = Seed::emails();

    // Print Users
    for (int i = 0; i < users.size(); i++) {
        ColorFormat::println(users[i].getName() + " - " + users[i].getEmailAddress(), Color::BrightGreen);
    }
    
    // Send Emails
    for (int i = 0; i < emails.size(); i++) {
        ResourceManager::sendEmail(emails[i]);
    }

    ColorFormat::println("User Data populated!\n", Color::BrightGreen);
}

int ResourceManager::nextUserId() {
    return GetInstance().m_idxGen.nextUser();
}

int ResourceManager::nextEmailId() {
    return GetInstance().m_idxGen.nextEmail();
}

BSTUserNode* ResourceManager::getBSTRoot() {
    return GetInstance().m_userTree.getRoot();
}

void ResourceManager::addUser(const User& user) {
    GetInstance().m_users.emplaceBack(user.getId(), user.getName(), user.getEmailAddress());
}

DynArray<User>& ResourceManager::getUsers() {
    return GetInstance().m_users;
}

User* ResourceManager::getUserByIdPtr(int id) {
    DynArray<User>& users = GetInstance().getUsers();

    for (int i = 0; i < users.size(); i++) {
        if (users[i].getId() == id) {
            return &users[i];
        }
    }

    return nullptr;
}

void ResourceManager::sendEmail(Email& email) {
    const std::string sender_address = email.getSender();
    const std::string receiver_address = email.getReceiver();

    auto& instance = GetInstance();

    User* sender = instance.getUser(sender_address);
    if (sender == nullptr) {
        ColorFormat::print("[ERROR] Sender not found: " + sender_address, Color::Red);
        return;
    }

    sender->sendEmail(email);
}

void ResourceManager::printUserList() {
    DynArray<User>& users = ResourceManager::getUsers();
    ColorFormat::println("----------------------------------------", Color::Cyan);
    for (size_t i = 0; i < users.size(); i++) {
        ColorFormat::println(users[i].getName() + " - " + users[i].getEmailAddress(), Color::Cyan);
    }
    ColorFormat::println("----------------------------------------\n", Color::Cyan);
}


User* ResourceManager::getUser(const std::string& email_address) {
    auto& tree = GetInstance().m_userTree;
    return tree.searchUser(email_address);;
}

ResourceManager::ResourceManager() : m_idxGen(), m_userTree() {};
ResourceManager::~ResourceManager() {}