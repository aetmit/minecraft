#include <core/logger.hpp>

#include <iostream>
#include <string_view>

#include <core/io.hpp>

namespace engine {

// We just use clog so it does not flushes buffer after every insertion,
// but we use cerr for critical logs.
// We use clog instead of cout so clog sends data to the error stream.

void Logger::verbose(const std::string_view& msg) {
    std::clog << io::reset << io::bold << "[VERBOSE]" << io::reset << msg << "\n" << io::reset;
}

void Logger::debug(const std::string_view& msg) {
    std::clog << io::reset << io::bold << "[DEBUG]" << io::reset << msg << "\n" << io::reset;
}

void Logger::info(const std::string_view& msg) {
    std::clog << io::reset << io::bold << "[INFO] " << io::reset << msg << "\n" << io::reset;
}

void Logger::warn(const std::string_view& msg) {
    std::cerr << io::reset << io::brightYellow << io::bold << "[WARN] " << io::reset << msg << "\n" << io::reset;
}

void Logger::error(const std::string_view& msg) {
    std::cerr << io::reset << io::brightRed << io::bold << "[ERROR] " << io::reset << msg << "\n" << io::reset;
}

} // namespace engine