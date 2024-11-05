#pragma once

#include "User.hpp"

struct BSTUserNode {
    int userId;
    BSTUserNode* left;
    BSTUserNode* right;

    BSTUserNode() : left(nullptr), right(nullptr) {}

    BSTUserNode(int id)
        : userId(id), left(nullptr), right(nullptr) {}

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