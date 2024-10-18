#pragma once

enum Color {
    Black,
    Red,
    Green,
    Yellow,
    Blue,
    Magenta,
    Cyan,
    White
};

namespace ColorFormat {
    std::string get(Color color);
    void print(const std::string& message, Color color);
}