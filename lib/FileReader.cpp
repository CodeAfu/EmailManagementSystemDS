#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include "FileReader.hpp"

std::vector<std::string> readFile(std::string path) {
    std::ifstream file(path);
    if (!file.is_open()) {
        std::cerr << "Error: Could not open file: " << path << std::endl;
        return;
    }

    std::string line;
    while (std::getline(file, line)) {
        std::cout << line << std::endl;
    }

    file.close();

}
