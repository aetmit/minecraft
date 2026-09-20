#pragma once

namespace io {

// ansii escape codes for pretty printing to the terminal
constexpr const char* reset   = "\033[0m";

// colurs
constexpr const char* black   = "\033[30m";
constexpr const char* red     = "\033[31m";
constexpr const char* green   = "\033[32m";
constexpr const char* yellow  = "\033[33m";
constexpr const char* blue    = "\033[34m";
constexpr const char* magenta = "\033[35m";
constexpr const char* cyan    = "\033[36m";
constexpr const char* white   = "\033[37m";

// bright colours
constexpr const char* brightBlack   = "\033[90m";
constexpr const char* brightRed     = "\033[91m";
constexpr const char* brightGreen   = "\033[92m";
constexpr const char* brightYellow  = "\033[93m";
constexpr const char* brightBlue    = "\033[94m";
constexpr const char* brightMagenta = "\033[95m";
constexpr const char* brightCyan    = "\033[96m";
constexpr const char* brightWhite   = "\033[97m";

// text styles
constexpr const char* bold       = "\033[1m";
constexpr const char* dim        = "\033[2m";
constexpr const char* italic     = "\033[3m";
constexpr const char* underline  = "\033[4m";
constexpr const char* blink      = "\033[5m";
constexpr const char* reverse    = "\033[7m";
constexpr const char* hidden     = "\033[8m";
constexpr const char* strike     = "\033[9m";
} // namespace io