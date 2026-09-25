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
    logLevel(LogLevel::Debug)
{
}

Logger::Logger(const std::filesystem::path& file) :
    logLevel(LogLevel::Debug),
    fileStream(file, std::ios::app)
{
}

Logger::~Logger() {
    if (fileStream.is_open()) {
        fileStream.flush();
        fileStream.close();
    }
}

void Logger::setLogLevel(LogLevel level) {
    logLevel = level;
}

void Logger::verbose(const std::string_view& msg) {
    if (logLevel.load(std::memory_order_relaxed) <= LogLevel::Verbose) {
        std::clog << io::reset << io::bold << "[VERBOSE] " << io::reset << msg << "\n" << io::reset;
    }
    fileStream << "[VERBOSE] " << msg << "\n";
}

void Logger::debug(const std::string_view& msg) {
    if (logLevel.load(std::memory_order_relaxed) <= LogLevel::Debug) {
        std::clog << io::reset << io::bold << "[DEBUG] " << io::reset << msg << "\n" << io::reset;
    }
    fileStream << "[DEBUG] " << msg << "\n";
}

void Logger::info(const std::string_view& msg) {
    if (logLevel.load(std::memory_order_relaxed) <= LogLevel::Info) {
        std::clog << io::reset << io::bold << "[INFO] " << io::reset << msg << "\n" << io::reset;
    }
    fileStream << "[INFO] " << msg << "\n";
}

void Logger::warn(const std::string_view& msg) {
    if (logLevel.load(std::memory_order_relaxed) <= LogLevel::Warn) {
        std::cerr << io::reset << io::brightYellow << io::bold << "[WARN] " << io::reset << msg << "\n" << io::reset;
    }
    fileStream << "[WARN] " << msg << "\n";
    fileStream.flush();  // Flush so we don't lose critical logs
}

void Logger::error(const std::string_view& msg) {
    if (logLevel.load(std::memory_order_relaxed) <= LogLevel::Error) {
        std::cerr << io::reset << io::brightRed << io::bold << "[ERROR] " << io::reset << msg << "\n" << io::reset;
    }
    fileStream << "[ERROR] " << msg << "\n";
    fileStream.flush();  // Flush so we don't lose critical logs
}

void Logger::log(LogLevel level, const std::string_view& msg) {
    std::lock_guard<std::mutex> lock(mutex);

    logQueue.push(LogMsg{level, std::string(msg)});

    mutex.unlock();
}

}  // namespace engine
