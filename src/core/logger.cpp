#include <core/logger.hpp>

#include <iostream>

#include <core/io.hpp>

namespace engine {

void Logger::error(const char *msg) {
    std::cerr << io::reset << io::brightRed << io::bold << "[ERROR] " << msg << "\n" << io::reset;
}

void Logger::warn(const char *msg) {
    std::cerr << io::reset << io::brightYellow << io::bold << "[WARN] " << msg << "\n" << io::reset;
}

void Logger::info(const char *msg) {
    std::cerr << io::reset << io::bold << "[INFO] " << msg << "\n" << io::reset;
}

} // namespace engine