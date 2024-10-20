#pragma once

//TODO: Try to remove these includes
#include <chrono>
#include <string>
#include <ctime>

class Timestamp {
public:
    Timestamp();
    Timestamp(const Timestamp& other);
    bool operator==(const Timestamp& other) const;
    
public:
    std::string getDate() const;
    std::string getTime() const;

private: 
    std::chrono::time_point<std::chrono::high_resolution_clock> _time;
};
