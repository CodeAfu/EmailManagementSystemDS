#ifndef TIMESTAMP_HPP
#define TIMESTAMP_HPP

//TODO: Try to remove these includes
#include <chrono>
#include <string>
#include <ctime>

class Timestamp {
public:
    Timestamp();

    bool operator==(const Timestamp& other) const;
    
public:
    std::string getDate() const;
    std::string getTime() const;

private: 
    std::chrono::time_point<std::chrono::high_resolution_clock> _time;
};

#endif // TIMESTAMP_HPP

