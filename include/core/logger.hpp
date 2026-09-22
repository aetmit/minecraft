#pragma once

namespace engine {

enum class LogLevel {
    Verbose,  //!< Verbose logging level
    Debug,    //!< Debug logging level
    Info,     //!< Info logging level
    Warn,     //!< Warning logging level
    Error,    //!< Error logging level
    Off       //!< No logging
};

class Logger {
public:
    /// @brief Default logger constructor
    Logger() = default;

    void setLogLevel(LogLevel level);

    void verbose(const char *msg);
    void debug(const char *msg);
    void info(const char *msg);
    void warn(const char *msg);
    void error(const char *msg);

private:
    LogLevel logLevel;
};

} // namespace engine