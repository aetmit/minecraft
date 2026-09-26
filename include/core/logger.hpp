#pragma once

#include <core/io.hpp>

#include <atomic>
#include <condition_variable>
#include <cstddef>
#include <filesystem>
#include <fstream>
#include <initializer_list>
#include <iostream>
#include <mutex>
#include <queue>
#include <string>
#include <string_view>
#include <thread>
#include <tuple>
#include <vector>

namespace engine {

/// @brief Log Levels
enum class LogLevel {
    Trace,  //!< Trace log
    Debug,  //!< Debug log
    Info,   //!< Info log 
    Warn,   //!< Warning log
    Error,  //!< Error log
    Off     //!< Logging off
};

struct LogMsg {
    LogLevel level;
    std::string msg;
    std::uint64_t timestamp;
};

struct LogFile {
public:
    std::filesystem::path file;
    LogLevel level;

    friend class Logger;

    LogFile(const std::string_view& file, LogLevel level);

    LogFile(const LogFile&);
    LogFile& operator=(const LogFile&);

protected:
    std::ofstream outStream;
};

class Logger {
public:
    /// @brief Default logger constructor
    Logger();

    /// @brief Logger constructor
    ///
    /// @param files Log files to record to
    Logger(const std::vector<LogFile>& files);

    /// @brief Logger constructor
    ///
    /// @param files Log files to record to
    Logger(const std::initializer_list<LogFile>& files);

    /// @brief Logger destructor
    ~Logger();

    /// @brief Sets the time format
    ///
    /// Default: YYYY-MM-DD HH:MM:SS.ms
    ///
    /// Formatter:
    ///
    /// %Y - Year
    /// %m - Month
    /// %d - Day
    /// %H - hour
    /// %M - Minute
    /// %S - Second
    ///
    /// @param format Formatter to format time
    void setTimeFormat(const std::string_view& format);

    /// @brief Sets the logging level threshold for logs
    ///
    /// Only logs that have a level at or above the threshold will display,
    /// any logs that have a level below the threshold will not display.
    ///
    /// @param level Logging level threshold
    void setLogLevel(LogLevel level);

    /// @brief Trace log
    ///
    /// Log detailed implementation
    ///
    /// @param msg Message
    ///
    /// @note Trace logs are hidden by terminal by default
    void trace(const std::string_view& msg);

    /// @brief Debug log
    ///
    /// Log debug messages
    ///
    /// @param msg Message
    void debug(const std::string_view& msg);
    
    /// @brief Information log
    ///
    /// Log informations
    ///
    /// @param msg Message
    void info(const std::string_view& msg);

    /// @brief Warning log
    ///
    /// Log warning messages
    ///
    /// @param msg Message
    void warn(const std::string_view& msg);

    /// @brief Error log
    ///
    /// Log error messages
    ///
    /// @param msg Message
    void error(const std::string_view& msg);

    // Template functions

    /// @brief Trace log
    ///
    /// Log detailed implementation
    ///
    /// @param msg Format message
    /// @param ...args Arguments
    ///
    /// @note Trace logs are hidden by terminal by default
    /// @note This function always formats, can cause performance drops
    template <typename... Args>
    void trace(const std::string_view& msg, Args&&... args) {
        log(LogLevel::Trace, std::vformat(msg, std::make_format_args(args...)), currentTimestamp());
    }

    /// @brief Debug log
    ///
    /// Log debug messages
    ///
    /// @param msg Format message
    /// @param ...args Arguments
    ///
    /// @note This function always formats, can cause performance drops
    template <typename... Args>
    void debug(const std::string_view& msg, Args&&... args) {
        log(LogLevel::Debug, std::vformat(msg, std::make_format_args(args...)), currentTimestamp());
    }

    /// @brief Information log
    ///
    /// Log informations
    ///
    /// @param msg Format message
    /// @param ...args Arguments
    ///
    /// @note This function always formats, can cause performance drops
    template <typename... Args>
    void info(const std::string_view& msg, Args&&... args) {
        log(LogLevel::Info, std::vformat(msg, std::make_format_args(args...)), currentTimestamp());
    }

    /// @brief Warning log
    ///
    /// Log warning messages
    ///
    /// @param msg Format message
    /// @param ...args Arguments
    ///
    /// @note This function always formats, can cause performance drops
    template <typename... Args>
    void warn(const std::string_view& msg, Args&&... args) {
        log(LogLevel::Warn, std::vformat(msg, std::make_format_args(args...)), currentTimestamp());
    }

    /// @brief Error log
    ///
    /// Log error messages
    ///
    /// @param msg Format message
    /// @param ...args Arguments
    ///
    /// @note This function always formats, can cause performance drops
    template <typename... Args>
    void error(const std::string_view& msg, Args&&... args) {
        log(LogLevel::Error, std::vformat(msg, std::make_format_args(args...)), currentTimestamp());
    }

private:
    std::atomic<LogLevel> logLevel;

    std::vector<LogFile> logFiles;

    std::queue<LogMsg> logQueue;
    std::condition_variable condition;
    std::mutex mutex;

    bool endProcess;
    std::thread ioThread;

    std::string timeFormat;

    std::uint64_t currentTimestamp();

    void log(LogLevel level, const std::string_view& msg, std::uint64_t timestamp);

    void terminalOutput(const LogMsg& msg);

    std::string formatOutput(const LogMsg& msg);

    void ioHandle();
};

} // namespace engine
