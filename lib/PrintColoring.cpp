#include <iostream>

#include "PrintColoring.hpp"

namespace ColorFormat {
    std::string get(Color color) {
    switch (color) {
        case Black: return "\033[30m";
        case Red: return "\033[31m";
        case Green: return "\033[32m";
        case Yellow: return "\033[33m";
        case Blue: return "\033[34m";
        case Magenta: return "\033[35m";
        case Cyan: return "\033[36m";
        case White: return "\033[37m";
    }
    return "";
    }
    void print(const std::string& message, Color color) {
        std::cout << get(color) << message << "\033[0m" << std::endl;
    }
}