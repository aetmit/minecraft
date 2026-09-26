#include <core/logger.hpp>

#include <algorithm>
#include <atomic>
#include <chrono>
#include <cstddef>
#include <cstdint>
#include <filesystem>
#include <fstream>
#include <ios>
#include <iostream>
#include <mutex>
#include <string_view>

#include <core/io.hpp>

namespace engine {

LogFile::LogFile(const std::string_view& file, LogLevel level) :
    file(file),
    level(level)
{
}

LogFile::LogFile(const LogFile& other) :
    file(other.file),
    level(other.level)
{
}

LogFile& LogFile::operator=(const LogFile& other) {
    if (this != &other) {
        if (outStream.is_open()) {
            outStream.close();
        }

        file = other.file;
        level = other.level;
    }

    return *this;
}

Logger::Logger() :
    logLevel(LogLevel::Debug),
    ioThread(&Logger::ioHandle, this),
    endProcess{false},
    timeFormat{"{:%Y-%m-%d %H:%M:%S}"}
{
    if (!timeFormat.empty()) {
        timeFormat += " ";
    }
}

Logger::Logger(const std::vector<LogFile>& files) :
    logLevel(LogLevel::Debug),
    ioThread(&Logger::ioHandle, this),
    endProcess{false},
    logFiles(files),
    timeFormat{"{:%Y-%m-%d %H:%M:%S}"}
{
    // Create stream for each file
    for (LogFile& file : logFiles) {
        file.outStream = std::ofstream(file.file);
    }

    if (!timeFormat.empty()) {
        timeFormat += " ";
    }
}

Logger::Logger(const std::initializer_list<LogFile>& files) :
    logLevel(LogLevel::Debug),
    ioThread(&Logger::ioHandle, this),
    endProcess{false},
    logFiles(files),
    timeFormat{"{:%Y-%m-%d %H:%M:%S}"}
{
    // Create stream for each file
    for (LogFile& file : logFiles) {
        file.outStream = std::ofstream(file.file);
    }

    if (!timeFormat.empty()) {
        timeFormat += " ";
    }
}

Logger::~Logger() {
    {
        std::lock_guard<std::mutex> lock(mutex);
        endProcess = true;
    }

    condition.notify_one();

    if (ioThread.joinable()) {
        ioThread.join();
    }

    // Flush terminal buffers

    // cerr is not required because it flushes buffers after every insert
    // operation
    std::clog.flush();

    for (LogFile& file : logFiles) {
        file.outStream.flush();  // Flush buffers
        file.outStream.close();
    }
}

void Logger::setTimeFormat(const std::string_view& format) {
    timeFormat = format;
}

void Logger::setLogLevel(LogLevel level) {
    logLevel = level;
}

void Logger::trace(const std::string_view& msg) {
    std::uint64_t zulu_nanoseconds = currentTimestamp(); 

    log(LogLevel::Trace, msg, currentTimestamp());
}

void Logger::debug(const std::string_view& msg) {
    log(LogLevel::Debug, msg, currentTimestamp());
}

void Logger::info(const std::string_view& msg) {
    log(LogLevel::Info, msg, currentTimestamp());
}

void Logger::warn(const std::string_view& msg) {
    log(LogLevel::Warn, msg, currentTimestamp());
}

void Logger::error(const std::string_view& msg) {
    log(LogLevel::Error, msg, currentTimestamp());
}

std::uint64_t Logger::currentTimestamp() {
    const auto now = std::chrono::system_clock::now();
    const auto duration = now.time_since_epoch();
    return std::chrono::duration_cast<std::chrono::milliseconds>(duration).count();
}

void Logger::log(LogLevel level, const std::string_view& msg, std::uint64_t timestamp) {
    {
        std::lock_guard<std::mutex> lock(mutex);

        logQueue.push(LogMsg{level, std::string(msg), timestamp});
    }  // lock
    condition.notify_one();
}

void Logger::terminalOutput(const LogMsg& msg) {
    std::chrono::milliseconds ns(msg.timestamp);
    auto tp = std::chrono::time_point<std::chrono::system_clock, std::chrono::milliseconds>(ns);

    std::string formattedTime = std::vformat(timeFormat, std::make_format_args(tp));
    switch (msg.level) {
        case LogLevel::Trace:
            std::clog << formattedTime << io::reset << io::bold << "[TRACE] " << io::reset << msg.msg << "\n" << io::reset;
            break;
        case LogLevel::Debug:
            std::clog << formattedTime << io::reset << io::bold << "[DEBUG] " << io::reset << msg.msg << "\n" << io::reset;
            break;
        case LogLevel::Info:
            std::clog << formattedTime << io::reset << io::bold << "[INFO] " << io::reset << msg.msg << "\n" << io::reset;
            break;
        case LogLevel::Warn:
            std::cerr << formattedTime << io::reset << io::brightYellow << io::bold << "[WARN] " << io::reset << msg.msg << "\n" << io::reset;
            break;
        case LogLevel::Error:
            std::cerr << formattedTime << io::reset << io::brightRed << io::bold << "[ERROR] " << io::reset << msg.msg << "\n" << io::reset;
            break;
        default: // do nothing
    }
}

std::string Logger::formatOutput(const LogMsg& msg) {
    switch (msg.level) {
        case LogLevel::Trace: return "[TRACE] " + msg.msg + "\n";
        case LogLevel::Debug: return "[DEBUG] " + msg.msg + "\n";
        case LogLevel::Info:  return "[INFO] " + msg.msg + "\n";
        case LogLevel::Warn:  return "[WARN] " + msg.msg + "\n";
        case LogLevel::Error: return "[ERROR] " + msg.msg + "\n";
        default: // do nothing
    }
    return "";
}

void Logger::ioHandle() {
    while (true) {
        LogMsg message;
        {
            std::unique_lock<std::mutex> lock(mutex);

            condition.wait(lock, [this] {
                return endProcess || !logQueue.empty();
            });

            // End thread only if command is sent and nothing to do
            if (endProcess && logQueue.empty()) {
                return;
            }

            message = std::move(logQueue.front());
            logQueue.pop();
        }  // lock

        // Terminal I/O
        if (logLevel.load(std::memory_order_relaxed) <= message.level) {
            terminalOutput(message);
        }

        // File I/O
        for (LogFile& file : logFiles) {
            const auto logMsg = formatOutput(message);
            if (file.level <= message.level) {
                file.outStream << logMsg;
                if (file.level <= LogLevel::Warn) {
                    // Flush important logs so we don't lose it
                    file.outStream.flush();
                }
            }
        }
    }
}

}  // namespace engine
