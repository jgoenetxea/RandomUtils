#include <chrono>
#include <ctime>
#include <iostream>
#include <sstream>
#include <random>

class RandomNameGenerator {
public:
    RandomNameGenerator() {
        m_gen = std::mt19937(m_rd());
        m_d = std::uniform_int_distribution<>(10000, 99999);
    }

    ~RandomNameGenerator() {
        // delete(m_gen);
    }

    std::string getRandomName(const std::string& prev = "",
                              const std::string& post = "") {
        auto now = std::chrono::system_clock::now();
        m_now_c = std::chrono::system_clock::to_time_t(now);
        m_parts = std::localtime(&m_now_c);

        m_randomNumber = m_d(m_gen);

        std::stringstream ss;
        ss << prev
           << 1900 + m_parts->tm_year  << "_"
           << 1    + m_parts->tm_mon   << "_"
           <<        m_parts->tm_mday  << "_"
           <<        m_parts->tm_sec   << "_"
           << m_randomNumber
           << post;

        return ss.str();
    }

private:
    std::time_t m_now_c;
    struct tm *m_parts;

    std::random_device m_rd;
    std::mt19937 m_gen;
    std::uniform_int_distribution<> m_d;
    int m_randomNumber;
};
