#include <core/logger.hpp>  // NOLINT(misc-header-include-cycle)

#include <atomic>
#include <filesystem>
#include <ios>
#include <iostream>
#include <string_view>

#include <core/io.hpp>

namespace engine {

inline Logger::Logger() :
    logLevel(LogLevel::Debug)
{
}

inline Logger::Logger(const std::filesystem::path& file) :
    logLevel(LogLevel::Debug),
    fileStream(file, std::ios::app)
{
}

inline Logger::~Logger() {
    if (fileStream.is_open()) {
        fileStream.flush();
        fileStream.close();
    }
}

inline void Logger::setLogLevel(LogLevel level) {
    logLevel = level;
}

inline void Logger::verbose(const std::string_view& msg) {
    if (logLevel.load(std::memory_order_relaxed) <= LogLevel::Verbose) {
        std::clog << io::reset << io::bold << "[VERBOSE] " << io::reset << msg << "\n" << io::reset;
    }
    fileStream << "[VERBOSE] " << msg << "\n";
}

inline void Logger::debug(const std::string_view& msg) {
    if (logLevel.load(std::memory_order_relaxed) <= LogLevel::Debug) {
        std::clog << io::reset << io::bold << "[DEBUG] " << io::reset << msg << "\n" << io::reset;
    }
    fileStream << "[DEBUG] " << msg << "\n";
}

inline void Logger::info(const std::string_view& msg) {
    if (logLevel.load(std::memory_order_relaxed) <= LogLevel::Info) {
        std::clog << io::reset << io::bold << "[INFO] " << io::reset << msg << "\n" << io::reset;
    }
    fileStream << "[INFO] " << msg << "\n";
}

inline void Logger::warn(const std::string_view& msg) {
    if (logLevel.load(std::memory_order_relaxed) <= LogLevel::Warn) {
        std::cerr << io::reset << io::brightYellow << io::bold << "[WARN] " << io::reset << msg << "\n" << io::reset;
    }
    fileStream << "[WARN] " << msg << "\n";
    fileStream.flush();  // Flush so we don't lose critical logs
}

inline void Logger::error(const std::string_view& msg) {
    if (logLevel.load(std::memory_order_relaxed) <= LogLevel::Error) {
        std::cerr << io::reset << io::brightRed << io::bold << "[ERROR] " << io::reset << msg << "\n" << io::reset;
    }
    fileStream << "[ERROR] " << msg << "\n";
    fileStream.flush();  // Flush so we don't lose critical logs
}

// Template functions

template <typename... Args>
inline void Logger::verbose(const std::string_view& msg, Args&&... args) {
    if (logLevel.load(std::memory_order_relaxed) <= LogLevel::Verbose) {
        verbose(std::vformat(msg, std::make_format_args(args...)));
    }
}

template <typename... Args>
inline void Logger::debug(const std::string_view& msg, Args&&... args) {
    if (logLevel.load(std::memory_order_relaxed) <= LogLevel::Debug) {
        debug(std::vformat(msg, std::make_format_args(args...)));
    }
}

template <typename... Args>
inline void Logger::info(const std::string_view& msg, Args&&... args) {
    if (logLevel.load(std::memory_order_relaxed) <= LogLevel::Info) {
        info(std::vformat(msg, std::make_format_args(args...)));
    }
}

template <typename... Args>
inline void Logger::warn(const std::string_view& msg, Args&&... args) {
    if (logLevel.load(std::memory_order_relaxed) <= LogLevel::Warn) {
        warn(std::vformat(msg, std::make_format_args(args...)));
    }
}

template <typename... Args>
inline void Logger::error(const std::string_view& msg, Args&&... args) {
    if (logLevel.load(std::memory_order_relaxed) <= LogLevel::Error) {
        error(std::vformat(msg, std::make_format_args(args...)));
    }
}

}  // namespace engine
