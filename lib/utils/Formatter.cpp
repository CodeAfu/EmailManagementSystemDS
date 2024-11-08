#include <iostream>
#include <algorithm>
#include <iomanip>

#include "Helper.hpp"

namespace Formatter {
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

    std::string centerAlign(const std::string& value, int width) {
        std::ostringstream oss;
        int padding = (width - value.size()) / 2;

        oss << std::setw(padding + value.size()) << value << std::setw(width - padding - value.size()) << "";
        return oss.str();
    }
}
