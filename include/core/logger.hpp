#pragma once

namespace engine {

class Logger {
public:
    /// @brief Default logger constructor
    Logger() = default;

    void debug(const char *msg);
    void info(const char *msg);
    void warn(const char *msg);
    void error(const char *msg);
};

} // namespace engine