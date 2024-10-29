#pragma once

#include "User.hpp"

struct BSTUserNode {
    User* user;
    BSTUserNode* left;
    BSTUserNode* right;

    BSTUserNode() : left(nullptr), right(nullptr) {}

    BSTUserNode(const User& user)
        : user(new User(user)), left(nullptr), right(nullptr) {}

    BSTUserNode(User& user)
        : user(&user), left(nullptr), right(nullptr) {}

    BSTUserNode(User* user)
        : user(user), left(nullptr), right(nullptr) {}

    ~BSTUserNode() {
        deleteSubtree(left);
        deleteSubtree(right);
    }

private:
    void deleteSubtree(BSTUserNode* node) {
        if (node != nullptr) {
            deleteSubtree(node->left);
            deleteSubtree(node->right);
            delete node;
        }
    }
};