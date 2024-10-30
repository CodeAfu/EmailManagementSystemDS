#pragma once

enum Color {
    Reset,
    Black,
    Red,
    Green,
    Yellow,
    Blue,
    Magenta,
    Cyan,
    White,
    BrightBlack,
    BrightRed,
    BrightGreen,
    BrightYellow,
    BrightBlue,
    BrightMagenta,
    BrightCyan,
    BrightWhite
};

namespace ColorFormat {
    std::string get(Color color);
    void println(const std::string& message, Color color);
    void print(const std::string& message, Color color);
}