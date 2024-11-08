// #include "Timestamp.hpp"
// #include <ctime>
// #include <mutex>

// // Define a static mutex to guard access to std::localtime
// static std::mutex localtime_mutex;

// Timestamp::Timestamp() : _time(std::chrono::high_resolution_clock::now()) {}

// Timestamp::Timestamp(const Timestamp& other) : _time(other._time) {}

// bool Timestamp::operator==(const Timestamp& other) const {
//     return _time == other._time;
// }

// std::string Timestamp::getDate() const {
//     auto now = std::chrono::system_clock::now();
//     time_t now_time_t = std::chrono::system_clock::to_time_t(now);
//     tm now_tm;
// // 
//     {
//         // Lock the mutex to ensure thread-safe access to std::localtime
//         std::lock_guard<std::mutex> lock(localtime_mutex);
//         now_tm = *std::localtime(&now_time_t);  // std::localtime is not thread-safe
//     }

//     char buffer[50];
//     strftime(buffer, sizeof(buffer), "%Y-%m-%d", &now_tm);
//     return std::string(buffer);
// }

// std::string Timestamp::getTime() const {
//     auto now = std::chrono::system_clock::now();
//     time_t now_time_t = std::chrono::system_clock::to_time_t(now);
//     tm now_tm;

//     {
//         // Lock the mutex to ensure thread-safe access to std::localtime
//         std::lock_guard<std::mutex> lock(localtime_mutex);
//         now_tm = *std::localtime(&now_time_t);
//     }

//     char buffer[50];
//     strftime(buffer, sizeof(buffer), "%H:%M:%S", &now_tm);
//     return std::string(buffer);
// }
