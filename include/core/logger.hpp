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

    Logger(const std::vector<LogFile>& files);

    Logger(const std::initializer_list<LogFile>& files);

    ~Logger();

    void setTimeFormat(const std::string_view& format);

    /// @brief Sets the logging level threshold for logs
    ///
    /// Only logs that have a level at or above the threshold will display,
    /// any logs that have a level below the threshold will not display.
    ///
    /// @param level Logging level threshold
    void setLogLevel(LogLevel level);

    void trace(const std::string_view& msg);

    void debug(const std::string_view& msg);
    
    void info(const std::string_view& msg);

    void warn(const std::string_view& msg);

    void error(const std::string_view& msg);

    // Template functions

    template <typename... Args>
    void trace(const std::string_view& msg, Args&&... args) {
        log(LogLevel::Trace, std::vformat(msg, std::make_format_args(args...)), currentTimestamp());
    }

    template <typename... Args>
    void debug(const std::string_view& msg, Args&&... args) {
        log(LogLevel::Debug, std::vformat(msg, std::make_format_args(args...)), currentTimestamp());
    }

    template <typename... Args>
    void info(const std::string_view& msg, Args&&... args) {
        log(LogLevel::Info, std::vformat(msg, std::make_format_args(args...)), currentTimestamp());
    }

    template <typename... Args>
    void warn(const std::string_view& msg, Args&&... args) {
        log(LogLevel::Warn, std::vformat(msg, std::make_format_args(args...)), currentTimestamp());
    }

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
