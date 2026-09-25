#include <core/logger.hpp>

#include <atomic>
#include <filesystem>
#include <ios>
#include <iostream>
#include <mutex>
#include <string_view>

#include <core/io.hpp>

namespace engine {

Logger::Logger() :
    logLevel(LogLevel::Debug),
    ioThread(&Logger::ioHandle, this),
    endProcess{false}
{
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
}

void Logger::setLogLevel(LogLevel level) {
    logLevel = level;
}

void Logger::verbose(const std::string_view& msg) {
    log(LogLevel::Verbose, msg);
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
    }
    condition.notify_one();
}

void Logger::terminalOutput(const LogMsg& msg) {
    switch (msg.level) {
        case LogLevel::Verbose:
            std::clog << io::reset << io::bold << "[VERBOSE] " << io::reset << msg.msg << "\n" << io::reset;
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

void Logger::ioHandle() {
    while (true) {
        LogMsg message;
        {
            std::unique_lock<std::mutex> lock(mutex);

            condition.wait(lock, [this] {
                return endProcess || !logQueue.empty();
            });

            if (endProcess && logQueue.empty()) {
                return;
            }

            message = std::move(logQueue.front());
            logQueue.pop();
        }

        if (logLevel.load(std::memory_order_relaxed) <= message.level) {
            
            terminalOutput(message);
        }
    }
}

}  // namespace engine
