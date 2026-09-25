#pragma once

#include <core/io.hpp>

#include <atomic>
#include <condition_variable>
#include <filesystem>
#include <fstream>
#include <iostream>
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
    void verbose(const std::string_view& msg, Args&&... args) {
        if (logLevel.load(std::memory_order_relaxed) <= LogLevel::Verbose) {
            std::clog << io::reset << io::bold << "[VERBOSE] " << io::reset
            << std::vformat(msg, std::make_format_args(args...)) << io::reset;
        }
    }

    template <typename... Args>
    void debug(const std::string_view& msg, Args&&... args) {
        if (logLevel.load(std::memory_order_relaxed) <= LogLevel::Debug) {
            std::clog << io::reset << io::bold << "[DEBUG] " << io::reset
            << std::vformat(msg, std::make_format_args(args...)) << io::reset;
        }
    }

    template <typename... Args>
    void info(const std::string_view& msg, Args&&... args) {
        if (logLevel.load(std::memory_order_relaxed) <= LogLevel::Info) {
            std::clog << io::reset << io::bold << "[INFO] " << io::reset
            << std::vformat(msg, std::make_format_args(args...)) << io::reset;
        }
    }

    template <typename... Args>
    void warn(const std::string_view& msg, Args&&... args) {
        if (logLevel.load(std::memory_order_relaxed) <= LogLevel::Warn) {
            std::cerr << io::reset << io::brightYellow << io::bold << "[WARN] " << io::reset
            << std::vformat(msg, std::make_format_args(args...)) << io::reset;
        }
    }

    template <typename... Args>
    void error(const std::string_view& msg, Args&&... args) {
        if (logLevel.load(std::memory_order_relaxed) <= LogLevel::Error) {
            std::cerr << io::reset << io::brightRed << io::bold << "[ERROR] " << io::reset
            << std::vformat(msg, std::make_format_args(args...)) << io::reset;
        }
    }

private:
    std::atomic<LogLevel> logLevel;

    std::queue<LogMsg> logQueue;
    std::condition_variable condition;
    std::mutex mutex;

    bool endProcess;
    std::thread ioThread;

    void log(LogLevel level, const std::string_view& msg);

    void terminalOutput(const LogMsg& msg);

    void ioHandle();
};

} // namespace engine
