#include <core/logger.hpp>

#include <atomic>
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
    endProcess{false}
{
}

Logger::Logger(const std::vector<LogFile>& files) :
    logLevel(LogLevel::Debug),
    ioThread(&Logger::ioHandle, this),
    endProcess{false},
    logFiles(files)
{
    // Create stream for each file
    for (LogFile& file : logFiles) {
        file.outStream = std::ofstream(file.file);
    }
}

Logger::Logger(const std::initializer_list<LogFile>& files) :
    logLevel(LogLevel::Debug),
    ioThread(&Logger::ioHandle, this),
    endProcess{false},
    logFiles(files)
{
    // Create stream for each file
    for (LogFile& file : logFiles) {
        file.outStream = std::ofstream(file.file);
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

    for (LogFile& file : logFiles) {
        file.outStream.close();
    }
}

void Logger::setLogLevel(LogLevel level) {
    logLevel = level;
}

void Logger::trace(const std::string_view& msg) {
    log(LogLevel::Trace, msg);
}

void Logger::debug(const std::string_view& msg) {
    log(LogLevel::Debug, msg);
}

void Logger::info(const std::string_view& msg) {
    log(LogLevel::Info, msg);
}

void Logger::warn(const std::string_view& msg) {
    log(LogLevel::Warn, msg);
}

void Logger::error(const std::string_view& msg) {
    log(LogLevel::Error, msg);
}

void Logger::log(LogLevel level, const std::string_view& msg) {
    {
        std::lock_guard<std::mutex> lock(mutex);

        logQueue.push(LogMsg{level, std::string(msg)});
    }  // lock
    condition.notify_one();
}

void Logger::terminalOutput(const LogMsg& msg) {
    switch (msg.level) {
        case LogLevel::Trace:
            std::clog << io::reset << io::bold << "[TRACE] " << io::reset << msg.msg << "\n" << io::reset;
            break;
        case LogLevel::Debug:
            std::clog << io::reset << io::bold << "[DEBUG] " << io::reset << msg.msg << "\n" << io::reset;
            break;
        case LogLevel::Info:
            std::clog << io::reset << io::bold << "[INFO] " << io::reset << msg.msg << "\n" << io::reset;
            break;
        case LogLevel::Warn:
            std::cerr << io::reset << io::brightYellow << io::bold << "[WARN] " << io::reset << msg.msg << "\n" << io::reset;
            break;
        case LogLevel::Error:
            std::cerr << io::reset << io::brightRed << io::bold << "[ERROR] " << io::reset << msg.msg << "\n" << io::reset;
            break;
    }
}

std::string Logger::formatOutput(const LogMsg& msg) {
    switch (msg.level) {
        case LogLevel::Trace: return "[TRACE] " + msg.msg + "\n";
        case LogLevel::Debug: return "[DEBUG] " + msg.msg + "\n";
        case LogLevel::Info:  return "[INFO] " + msg.msg + "\n";
        case LogLevel::Warn:  return "[WARN] " + msg.msg + "\n";
        case LogLevel::Error: return "[ERROR] " + msg.msg + "\n";
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
