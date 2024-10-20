#pragma once

#include <fstream>

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
        int emailIndex = 0;

        while (std::getline(infile, line)) {
            if (line.find("email") != std::string::npos) {
                emailIndex = std::stoi(line.substr(line.find(",") + 1));
                break;
            }
        }

        infile.close();

        emailIndex++;

        std::ofstream outfile("index.csv");
        if (!outfile.is_open()) {
            throw std::runtime_error("Error opening output file");
        }

        outfile << "email," << emailIndex << "\n";
        outfile << "user," << _user << "\n";

        outfile.close();

        return emailIndex;
    }

    int nextUser() {
        std::ifstream infile("index.csv");
        if (!infile.is_open()) {
            throw std::runtime_error("Error opening input file");
        }

        std::string line;
        int emailIndex = 0;

        while (std::getline(infile, line)) {
            if (line.find("user") != std::string::npos) {
                emailIndex = std::stoi(line.substr(line.find(",") + 1));
                break;
            }
        }

        infile.close();

        emailIndex++;

        std::ofstream outfile("index.csv");
        if (!outfile.is_open()) {
            throw std::runtime_error("Error opening output file");
        }

        outfile << "email," << emailIndex << "\n";
        outfile << "user," << _user << "\n";

        outfile.close();

        return emailIndex;    
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