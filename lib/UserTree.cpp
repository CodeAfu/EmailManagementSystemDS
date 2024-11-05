
#include "BSTUserNode.hpp"
#include "UserTree.hpp"
#include "Helper.hpp"
#include "ResourceManager.hpp"

UserTree::UserTree() : m_root(nullptr) {}
UserTree::~UserTree() {
    m_root = nullptr;
}

void UserTree::insertUser(int id) {
    if (m_root == nullptr) {
        m_root = new BSTUserNode(id);
    } else {
        insertUserRecursive(m_root, id);
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
void UserTree::insertUserRecursive(BSTUserNode* node, int id) {
    User* new_user = ResourceManager::getUserByIdPtr(id);
    User* node_user = ResourceManager::getUserByIdPtr(node->userId);

    if (new_user == nullptr || node_user == nullptr) {
        throw std::runtime_error("[UserTree::insertUserRecursive] new_user or node_user is null");
    }

    if (Formatter::toLower(new_user->getEmailAddress()) < Formatter::toLower(node_user->getEmailAddress())) {
        // Insert in the left subtree
        if (node->left == nullptr) {
            node->left = new BSTUserNode(id);
        } else {
            insertUserRecursive(node->left, id);
        }
    } else {
        // Insert in the right subtree
        if (node->right == nullptr) {
            node->right = new BSTUserNode(id);
        } else {
            insertUserRecursive(node->right, id);
        }
    }
}

User* UserTree::searchUserRecursive(BSTUserNode* node, const std::string& email_address) {
    if (node == nullptr) {
        return nullptr;
    }

    User* node_user = ResourceManager::getUserByIdPtr(node->userId);
    if (node_user == nullptr) {
        throw std::runtime_error("[UserTree::searchUserRecursive] node_user is null");
    }
    
    if (Formatter::toLower(node_user->getEmailAddress()) == Formatter::toLower(email_address)) {
        return node_user;
    }
    if (Formatter::toLower(email_address) < Formatter::toLower(node_user->getEmailAddress())) {
        return searchUserRecursive(node->left, email_address);
    }
    return searchUserRecursive(node->right, email_address);
}

void UserTree::inOrderDisplayRecursive(BSTUserNode* node) {
    if (node == nullptr) return;  // Base case
    User* node_user = ResourceManager::getUserByIdPtr(node->userId);

    if (node_user == nullptr) {
        throw std::runtime_error("[UserTree:inOrderDisplayRecursive] node_user is null");
    }

    inOrderDisplayRecursive(node->left);  // Visit left subtree
    std::cout << "Name: " << node_user->getName() 
            << ", Email: " << node_user->getEmailAddress() << std::endl;  // Process current node
    inOrderDisplayRecursive(node->right);  // Visit right subtree
}
