
#include <fstream>
#include <string>

#include "IdxGen.hpp"

IdxGen::IdxGen() : m_email(0), m_user(0) {
    reset();
}

/// @brief Generates the next index for Email object
int IdxGen::nextEmail() {
    std::ifstream infile("data/index.csv");
    if (!infile.is_open()) {
        throw std::runtime_error("Error opening input file");
    }

    std::string line;
    int email_index = 0;

    while (std::getline(infile, line)) {
        if (line.find("email") != std::string::npos) {
            email_index = std::stoi(line.substr(line.find(",") + 1));
            break;
        }
    }

    infile.close();
    email_index++;

    std::ofstream outfile("data/index.csv");
    if (!outfile.is_open()) {
        throw std::runtime_error("Error opening output file");
    }

    outfile << "email," << email_index << "\n";
    outfile << "user," << m_user << "\n";

    outfile.close();

    return email_index;
}

/// @brief Generates the next index for User object
int IdxGen::nextUser() {
    std::ifstream infile("data/index.csv");
    if (!infile.is_open()) {
        throw std::runtime_error("Error opening input file");
    }

    std::string line;
    int user_index = 0;

    while (std::getline(infile, line)) {
        if (line.find("user") != std::string::npos) {
            user_index = std::stoi(line.substr(line.find(",") + 1));
            break;
        }
    }

    infile.close();
    user_index++;

    std::ofstream outfile("data/index.csv");
    if (!outfile.is_open()) {
        throw std::runtime_error("Error opening output file");
    }

    outfile << "email," << m_email << "\n";
    outfile << "user," << user_index << "\n";

    outfile.close();
    m_user = user_index;

    return user_index;    
}

void IdxGen::reset() {
    std::ofstream outfile("data/index.csv");
    if (!outfile.is_open()) {
        throw std::runtime_error("Error opening output file");
    }
    outfile << "email,0\n";
    outfile << "user,0\n";
    outfile.close();
}
