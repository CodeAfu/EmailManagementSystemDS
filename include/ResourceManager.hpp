#pragma once

#include "IdxGen.hpp"
#include "BSTUserNode.hpp"

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

    static BSTUserNode* getBSTUserNode() {
        return GetInstance().m_userNode;
    }

    static void addUser(User* user) {

    }

private:
    ResourceManager(const ResourceManager&) = delete;
    ResourceManager& operator=(const ResourceManager&) = delete;
    ResourceManager(ResourceManager&&) = delete;
    ResourceManager& operator=(ResourceManager&&) = delete;

private:
    ResourceManager() : m_idxGen(), m_userNode() {};
    ~ResourceManager() {
        for (int i = 0; i < m_users.size(); i++) {
            m_users[i] = nullptr; // TODO: Review memory stuff
        }    
    }

private:
    DynArray<User*> m_users;
    IdxGen m_idxGen;
    BSTUserNode* m_userNode;
};