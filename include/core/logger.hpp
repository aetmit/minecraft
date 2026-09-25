#pragma once

#include <atomic>
#include <condition_variable>
#include <filesystem>
#include <fstream>
#include <mutex>
#include <queue>
#include <string>
#include <string_view>
#include <thread>

namespace engine {

/// @brief Log Levels
enum class LogLevel {
    Verbose,  //!< Verbose log
    Debug,    //!< Debug log
    Info,     //!< Info log 
    Warn,     //!< Warning log
    Error,    //!< Error log
    Off       //!< Logging off
};

// TODO: Worker thread to handle I/O operations

struct LogMsg {
    LogLevel level;
    std::string msg;
};

class Logger {
public:
    /// @brief Default logger constructor
    Logger();

    Logger(const std::filesystem::path& file);

    ~Logger();

    /// @brief Sets the logging level threshold for logs
    ///
    /// Only logs that have a level at or above the threshold will display,
    /// any logs that have a level below the threshold will not display.
    ///
    /// @param level Logging level threshold
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

    std::ofstream fileStream;

    std::queue<LogMsg> logQueue;
    std::condition_variable condition;
    std::mutex mutex;

    bool endProcess;
    std::thread ioThread;

    void log(LogLevel level, const std::string_view& msg);
};

} // namespace engine

#include <core/logger.inl>
