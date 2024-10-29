#include <iostream>

#include "ColorFormat.hpp"

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
        case BrightBlack: return "\033[90m";
        case BrightRed: return "\033[91m";
        case BrightGreen: return "\033[92m";
        case BrightYellow: return "\033[93m";
        case BrightBlue: return "\033[94m";
        case BrightMagenta: return "\033[95m";
        case BrightCyan: return "\033[96m";
        case BrightWhite: return "\033[97m";
    }
    return "";
    }
    void println(const std::string& message, Color color) {
        std::cout << get(color) << message << "\033[0m" << std::endl;
    }
}