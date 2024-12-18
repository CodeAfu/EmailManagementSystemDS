#pragma once

// #include "DynArray.hpp"
#include "User.hpp"

namespace Formatter {
    std::string trim(const std::string &str);
    std::string toLower(const std::string &str);
    std::string centerAlign(const std::string& value, int width);
}

namespace Console {
    void clearCin();
    bool validateIntInput(int& choice);
    int getIntUserInput(const std::string& message);
    std::string getStringUserInput(const std::string& message);
}

namespace Seed {
    DynArray<User> users();
    DynArray<Email> emails();
}