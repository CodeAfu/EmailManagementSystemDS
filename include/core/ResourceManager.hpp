#pragma once

#include "IdxGen.hpp"
#include "UserTree.hpp"
// #include "Helper.hpp"

class ResourceManager {
public:
    static ResourceManager& GetInstance();

    static void seedInitialData();
    static void populateData();

    static int nextUserId();
    static int nextEmailId();
    static BSTUserNode* getBSTRoot();
    static void addUser(const User& user);
    static DynArray<User>& getUsers();
    static User* getUserByIdPtr(int id);
    static void sendEmail(Email& email);
    static void printUserList();
    static User* getUser(const std::string& email_address);

private:
    ResourceManager();
    ~ResourceManager();
    
private:
    ResourceManager(const ResourceManager&) = delete;
    ResourceManager& operator=(const ResourceManager&) = delete;
    ResourceManager(ResourceManager&&) = delete;
    ResourceManager& operator=(ResourceManager&&) = delete;

private:
    DynArray<User> m_users;
    UserTree m_userTree;
    IdxGen m_idxGen;
};