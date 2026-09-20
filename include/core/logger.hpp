#pragma once

namespace engine {

class Logger {
public:
    Logger() = default;

    // use const char * here because i cant be bothered withj std::string
    void info(const char *msg);
    void warn(const char *msg);
    void error(const char *msg);
};

} // namespace engine