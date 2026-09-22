#pragma once

#include <format>
#include <string_view>
#include <utility>

namespace engine {

class Logger {
public:
    /// @brief Default logger constructor
    Logger() = default;

    void verbose(const std::string_view& msg);
    void debug(const std::string_view&);
    void info(const std::string_view& msg);
    void warn(const std::string_view& msg);
    void error(const std::string_view& msg);

    // Template functions

    template <typename... Args>
    void verbose(const std::string_view& msg, Args&&... args) {
        verbose(std::vformat(msg, std::make_format_args(args...)));
    }

    template <typename... Args>
    void debug(const std::string_view& msg, Args&&... args) {
        debug(std::vformat(msg, std::make_format_args(args...)));
    }

    template <typename... Args>
    void info(const std::string_view& msg, Args&&... args) {
        info(std::vformat(msg, std::make_format_args(args...)));
    }

    template <typename... Args>
    void warn(const std::string_view& msg, Args&&... args) {
        warn(std::vformat(msg, std::make_format_args(args...)));
    }

    template <typename... Args>
    void error(const std::string_view& msg, Args&&... args) {
        error(std::vformat(msg, std::make_format_args(args...)));
    }
};

} // namespace engine