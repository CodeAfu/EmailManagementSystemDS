#pragma once

#include "BSTUserNode.hpp"

class UserTree {
public:
    UserTree();
    ~UserTree();

public:
    void insertUser(User& user);
    User* searchUser(const std::string& name);
    void inOrderDisplay();
    BSTUserNode* getRoot();

private:
    void insertUserRecursive(BSTUserNode* node, User& user);
    User* searchUserRecursive(BSTUserNode* node, const std::string& name);
    void inOrderDisplayRecursive(BSTUserNode* node);

private:
    BSTUserNode* m_root;
};