#include <core/logger.hpp>

#include <iostream>

#include <core/io.hpp>

namespace engine {

void Logger::debug(const char *msg) {
    // We just use clog so it does not flushes buffer after every insertion.
    // We use clog instead of cout so clog sends data to the error stream.
    std::clog << io::reset << io::bold << "[DEBUG]" << io::reset << msg << "\n" << io::reset;
}

void Logger::info(const char *msg) {
    // We just use clog so it does not flushes buffer after every insertion.
    // We use clog instead of cout so clog sends data to the error stream.
    std::clog << io::reset << io::bold << "[INFO] " << io::reset << msg << "\n" << io::reset;
}

void Logger::warn(const char *msg) {
    std::cerr << io::reset << io::brightYellow << io::bold << "[WARN] " << io::reset << msg << "\n" << io::reset;
}

void Logger::error(const char *msg) {
    std::cerr << io::reset << io::brightRed << io::bold << "[ERROR] " << io::reset << msg << "\n" << io::reset;
}

} // namespace engine