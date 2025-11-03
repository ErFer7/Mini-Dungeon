#pragma once

#include <iostream>
#include <sstream>
#include <utility>

#include "definitions.hpp"

namespace utils {

template <typename... Args>
void log(Args... args) {
    std::ostringstream stream;
    (stream << ... << args);
    std::cout << stream.str() << std::endl;
}

template <typename... Args>
void log_info(Args... args) {
    if constexpr (!(DEBUGGED && DEBUG_INFO)) {
        return;
    }

    log("[INFO]: ", std::forward<Args>(args)...);
}

template <typename... Args>
void log_warn(Args... args) {
    if constexpr (!(DEBUGGED && DEBUG_WARN)) {
        return;
    }

    log("[WARN]: ", std::forward<Args>(args)...);
}

template <typename... Args>
void log_error(Args... args) {
    if constexpr (!(DEBUGGED && DEBUG_ERROR)) {
        return;
    }

    log("[ERROR]: ", std::forward<Args>(args)...);
}
}  // namespace utils
