#pragma once

#include "IdxGen.hpp"
#include "UserTree.hpp"

class ResourceManager {
public:
    static ResourceManager& GetInstance() {
        static ResourceManager instance;
        return instance;
    }

    static int nextUserId() {
        return GetInstance().m_idxGen.nextUser();
    }

    static int nextEmailId() {
        return GetInstance().m_idxGen.nextEmail();
    }

    static BSTUserNode* getBSTRoot() {
        return GetInstance().m_userTree.getRoot();
    }

    static void addUser(User* user) {
        GetInstance().m_users.emplaceBack(user);
    }

    static DynArray<User*>& getUsers() {
        return GetInstance().m_users;
    }

    static void populateUsers(DynArray<User>& users) {
        auto& instance = GetInstance();
        for (int i = 0; i < users.size(); i++) {
            instance.m_users.emplaceBack(&users[i]);
            instance.m_userTree.insertUser(users[i]);
        }
    }

    static User& getReceiver(const std::string email_address) {
        auto& tree = GetInstance().m_userTree;
        return tree.searchUser(email_address);
    }

private:
    ResourceManager(const ResourceManager&) = delete;
    ResourceManager& operator=(const ResourceManager&) = delete;
    ResourceManager(ResourceManager&&) = delete;
    ResourceManager& operator=(ResourceManager&&) = delete;

private:
    ResourceManager() : m_idxGen(), m_userTree() {};
    ~ResourceManager() {}

private:
    DynArray<User*> m_users;
    UserTree m_userTree;
    IdxGen m_idxGen;
};