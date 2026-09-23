#pragma once

#include <atomic>
#include <string_view>

namespace engine {

enum class LogLevel {
    Verbose,
    Debug,
    Info,
    Warn,
    Error,
    Off
};

class Logger {
public:
    /// @brief Default logger constructor
    Logger();

    void setLogLevel(LogLevel level);

    void verbose(const std::string_view& msg);

    void debug(const std::string_view& msg);
    
    void info(const std::string_view& msg);

    void warn(const std::string_view& msg);

    void error(const std::string_view& msg);

    // Template functions

    template <typename... Args>
    void verbose(const std::string_view& msg, Args&&... args);

    template <typename... Args>
    void debug(const std::string_view& msg, Args&&... args);

    template <typename... Args>
    void info(const std::string_view& msg, Args&&... args);

    template <typename... Args>
    void warn(const std::string_view& msg, Args&&... args);

    template <typename... Args>
    void error(const std::string_view& msg, Args&&... args);

private:
    std::atomic<LogLevel> logLevel;
};

} // namespace engine

#include <core/logger.inl>
