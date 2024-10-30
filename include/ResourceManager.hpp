#pragma once

#include "IdxGen.hpp"
#include "UserTree.hpp"
#include "Helper.hpp"

class ResourceManager {
public:

    static ResourceManager& GetInstance() {
        static ResourceManager instance;
        return instance;
    }

    static void seedInitialData() {
        auto& instance = GetInstance();
        DynArray<User> users = Seed::users();
        // DynArray<Email> emails = Seed::emails();

        for (int i = 0; i < users.size(); i++) {
            int id = users[i].getId();
            std::string name = users[i].getName();
            std::string email = users[i].getEmailAddress();

            instance.m_users.emplaceBack(id, name, email);
            User& user = instance.m_users[i];
            instance.m_userTree.insertUser(user);
        }
    }

    static void populateData() {
        DynArray<User>& users = GetInstance().getUsers();

        if (users.isEmpty()) {
            ColorFormat::println("[ERROR] No users found. Please seed the data first.", Color::Red);
            return;
        } 

        User& emma = users[0];
        User& liam = users[1];
        User& sophia = users[2];
        User& noah = users[3];
        User& mia = users[4];

        DynArray<Email> emails = Seed::emails();

        for (int i = 0; i < users.size(); i++) {
            ColorFormat::println(users[i].getName() + " - " + users[i].getEmailAddress(), Color::BrightGreen);
        }

        emma.sendEmail(emails[0]);
        sophia.sendEmail(emails[1]);
        mia.sendEmail(emails[2]);
        liam.sendEmail(emails[3]);
        noah.sendEmail(emails[4]);
        emma.sendEmail(emails[5]);
        sophia.sendEmail(emails[6]);
        noah.sendEmail(emails[7]);
        sophia.sendEmail(emails[8]);
        noah.sendEmail(emails[9]);

        ColorFormat::println("User Data populated!\n", Color::BrightGreen);
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

    static void addUser(const User& user) {
        GetInstance().m_users.emplaceBack(user.getId(), user.getName(), user.getEmailAddress());
    }

    static DynArray<User>& getUsers() {
        return GetInstance().m_users;
    }
    
    static void printUserList() {
        DynArray<User>& users = ResourceManager::getUsers();
        ColorFormat::println("----------------------------------------", Color::Cyan);
        for (size_t i = 0; i < users.size(); i++) {
            ColorFormat::println(users[i].getName() + " - " + users[i].getEmailAddress(), Color::Cyan);
        }
        ColorFormat::println("----------------------------------------\n", Color::Cyan);
    }

    // static void populateUserBST() {
    //     auto& instance = GetInstance();

    //     instance.m_userTree.~UserTree();
    //     instance.m_userTree = UserTree();

    //     for (int i = 0; i < instance.m_users.size(); i++) {
    //         instance.m_userTree.insertUser(instance.m_users[i]);
    //     }
    // }

    static User* getReceiver(const std::string& email_address) {
        auto& tree = GetInstance().m_userTree;
        return tree.searchUser(email_address);;
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
    DynArray<User> m_users;
    UserTree m_userTree;
    IdxGen m_idxGen;
};