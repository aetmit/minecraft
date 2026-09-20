#include <core/logger.hpp>

#include <iostream>

#include <core/io.hpp>

namespace engine {

void Logger::error(const char *msg) {
    std::cerr << io::reset << io::brightRed << io::bold << "[ERROR] " << io::reset << msg << "\n" << io::reset;
}

void Logger::warn(const char *msg) {
    std::cerr << io::reset << io::brightYellow << io::bold << "[WARN] " << io::reset << msg << "\n" << io::reset;
}

void Logger::info(const char *msg) {
    std::cerr << io::reset << io::bold << "[INFO] " << io::reset << msg << "\n" << io::reset;
}

void Logger::debug(const char *msg) {
    std::cerr << io::reset << io::bold << "[DEBUG]" << io::reset << msg << "\n" << io::reset;
}

} // namespace engine