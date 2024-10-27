#pragma once

#include <iostream>
#include <string>
#include <algorithm>

namespace Helper {
    std::string trim(const std::string &str) {
        auto start = str.find_first_not_of(" \t\n");
        auto end = str.find_last_not_of(" \t\n");
        return (start == std::string::npos || end == std::string::npos) ? "" : str.substr(start, end - start + 1);
    }

    std::string toLower(const std::string &str) {
        std::string lowerStr = str;
        std::transform(lowerStr.begin(), lowerStr.end(), lowerStr.begin(), ::tolower);
        return lowerStr;
    }
}