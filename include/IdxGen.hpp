#pragma once

#include <fstream>

/**
 * @brief Reads from "index.csv" and generates unique indices for emails and users.
 * @param nextEmail() Returns the next available email index.
 * @param nextUser() Returns the next available user index.
 */
class IdxGen {
public:
    IdxGen() : _email(0), _user(0) {
        reset();
    }

    int nextEmail() {
        std::ifstream infile("index.csv");
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

        std::ofstream outfile("index.csv");
        if (!outfile.is_open()) {
            throw std::runtime_error("Error opening output file");
        }

        outfile << "email," << email_index << "\n";
        outfile << "user," << _user << "\n";

        outfile.close();

        return email_index;
    }

    int nextUser() {
        std::ifstream infile("index.csv");
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

        std::ofstream outfile("index.csv");
        if (!outfile.is_open()) {
            throw std::runtime_error("Error opening output file");
        }

        outfile << "email," << _email << "\n";
        outfile << "user," << user_index << "\n";

        outfile.close();

        _user = user_index;

        return user_index;    
    }

private:
    void reset() {
        std::ofstream outfile("index.csv");
        if (!outfile.is_open()) {
            // std::cout << "Error opening output file" << std::endl;
            throw std::runtime_error("Error opening output file");
        }
        outfile << "email,0\n";
        outfile << "user,0\n";
        outfile.close();
    }

    int _email;
    int _user;
};