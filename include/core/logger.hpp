#pragma once

#include <core/io.hpp>

#include <atomic>
#include <condition_variable>
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
    Verbose,  //!< Verbose log
    Debug,    //!< Debug log
    Info,     //!< Info log 
    Warn,     //!< Warning log
    Error,    //!< Error log
    Off       //!< Logging off
};

struct LogMsg {
    LogLevel level;
    std::string msg;
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
        log(LogLevel::Verbose, std::vformat(msg, std::make_format_args(args...)));
    }

    template <typename... Args>
    void debug(const std::string_view& msg, Args&&... args) {
        log(LogLevel::Debug, std::vformat(msg, std::make_format_args(args...)));
    }

    template <typename... Args>
    void info(const std::string_view& msg, Args&&... args) {
        log(LogLevel::Info, std::vformat(msg, std::make_format_args(args...)));
    }

    template <typename... Args>
    void warn(const std::string_view& msg, Args&&... args) {
        log(LogLevel::Warn, std::vformat(msg, std::make_format_args(args...)));
    }

    template <typename... Args>
    void error(const std::string_view& msg, Args&&... args) {
        log(LogLevel::Error, std::vformat(msg, std::make_format_args(args...)));
    }

private:
    std::atomic<LogLevel> logLevel;

    std::vector<LogFile> logFiles;

    std::queue<LogMsg> logQueue;
    std::condition_variable condition;
    std::mutex mutex;

    bool endProcess;
    std::thread ioThread;

    void log(LogLevel level, const std::string_view& msg);

    void terminalOutput(const LogMsg& msg);

    std::string formatOutput(const LogMsg& msg);

    void ioHandle();
};

} // namespace engine
