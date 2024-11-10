#pragma once
class IdxGen {
public:
    IdxGen();

public:
    /// @brief Generates the next index for Email object
    int nextEmail();
    
    /// @brief Generates the next index for User object
    int nextUser();

private:
    void reset();

private:
    int m_email;
    int m_user;
};
