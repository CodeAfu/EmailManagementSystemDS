
#include "BSTUserNode.hpp"
#include "UserTree.hpp"
#include "Helper.hpp"
#include "ResourceManager.hpp"

UserTree::UserTree() : m_root(nullptr) {}
UserTree::~UserTree() {
}

void UserTree::insertUser(User& user) {
    if (m_root == nullptr) {
        m_root = new BSTUserNode(&user);
    } else {
        insertUserRecursive(m_root, user);
    }
}

User* UserTree::searchUser(const std::string& email_address) {
    return searchUserRecursive(m_root, email_address);
}

void UserTree::inOrderDisplay() {
    inOrderDisplayRecursive(m_root);
}

BSTUserNode* UserTree::getRoot() {
    return m_root;
}

// Recursive Methods
void UserTree::insertUserRecursive(BSTUserNode* node, User& user) {
    if (Formatter::toLower(user.getEmailAddress()) < Formatter::toLower(node->user->getEmailAddress())) {
        // Insert in the left subtree
        if (node->left == nullptr) {
            node->left = new BSTUserNode(&user);
        } else {
            insertUserRecursive(node->left, user);
        }
    } else {
        // Insert in the right subtree
        if (node->right == nullptr) {
            node->right = new BSTUserNode(&user);
        } else {
            insertUserRecursive(node->right, user);
        }
    }
}

User* UserTree::searchUserRecursive(BSTUserNode* node, const std::string& email_address) {
    if (node == nullptr) {
        throw std::runtime_error("User not found");  // Or handle the error as appropriate
    }
    if (Formatter::toLower(node->user->getEmailAddress()) == Formatter::toLower(email_address)) {
        return node->user;
    }
    if (Formatter::toLower(email_address) < Formatter::toLower(node->user->getEmailAddress())) {
        return searchUserRecursive(node->left, email_address);
    }
    return searchUserRecursive(node->right, email_address);
}

void UserTree::inOrderDisplayRecursive(BSTUserNode* node) {
    if (node == nullptr) return;  // Base case
    inOrderDisplayRecursive(node->left);  // Visit left subtree
    std::cout << "Name: " << node->user->getName() 
            << ", Email: " << node->user->getEmailAddress() << std::endl;  // Process current node
    inOrderDisplayRecursive(node->right);  // Visit right subtree
}
