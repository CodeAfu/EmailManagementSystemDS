#include "Timestamp.hpp"
#include <ctime>

Timestamp::Timestamp() : _time(std::chrono::high_resolution_clock::now()) {}

std::string Timestamp::getDate() const {
    auto now = std::chrono::system_clock::now();
    time_t now_time_t = std::chrono::system_clock::to_time_t(now);
    tm now_tm;
    localtime_s(&now_tm, &now_time_t);
    char buffer[50];
    strftime(buffer, sizeof(buffer), "%Y-%m-%d", &now_tm);
    return std::string(buffer);
}

std::string Timestamp::getTime() const {
    auto now = std::chrono::system_clock::now();
    time_t now_time_t = std::chrono::system_clock::to_time_t(now);
    tm now_tm;
    localtime_s(&now_tm, &now_time_t);
    char buffer[50];
    strftime(buffer, sizeof(buffer), "%H:%M:%S", &now_tm);
    return std::string(buffer);
}

bool Timestamp::operator==(const Timestamp& other) const {
    return _time == other._time;
}

