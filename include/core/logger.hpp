#pragma once

#include <string_view>

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
};

} // namespace engine