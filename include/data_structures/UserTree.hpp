#pragma once

#include "BSTUserNode.hpp"

class UserTree {
public:
    UserTree();
    ~UserTree();

public:
    void insertUser(int id);
    User* searchUser(const std::string& email_address);
    void inOrderDisplay();
    BSTUserNode* getRoot();

private:
    void insertUserRecursive(BSTUserNode* node, int id);
    User* searchUserRecursive(BSTUserNode* node, const std::string& email_address);
    void inOrderDisplayRecursive(BSTUserNode* node);

private:
    BSTUserNode* m_root;
};