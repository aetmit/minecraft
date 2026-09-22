#include <core/logger.hpp>

#include <iostream>

#include <core/io.hpp>

namespace engine {

void Logger::setLogLevel(LogLevel level) {
    logLevel = level;
}

// We just use clog so it does not flushes buffer after every insertion,
// but we use cerr for critical logs.
// We use clog instead of cout so clog sends data to the error stream.

void Logger::verbose(const char *msg) {
    if (logLevel <= LogLevel::Verbose) {
        std::clog << io::reset << io::bold << "[VERBOSE]" << io::reset << msg << "\n" << io::reset;
    }
}

void Logger::debug(const char *msg) {
    if (logLevel <= LogLevel::Debug) {
        std::clog << io::reset << io::bold << "[DEBUG]" << io::reset << msg << "\n" << io::reset;
    }
}

void Logger::info(const char *msg) {
    if (logLevel <= LogLevel::Info) {
        std::clog << io::reset << io::bold << "[INFO] " << io::reset << msg << "\n" << io::reset;
    }
}

void Logger::warn(const char *msg) {
    if (logLevel <= LogLevel::Warn) {
        std::cerr << io::reset << io::brightYellow << io::bold << "[WARN] " << io::reset << msg << "\n" << io::reset;
    }
}

void Logger::error(const char *msg) {
    if (logLevel <= LogLevel::Error) {
        std::cerr << io::reset << io::brightRed << io::bold << "[ERROR] " << io::reset << msg << "\n" << io::reset;
    }
}

} // namespace engine