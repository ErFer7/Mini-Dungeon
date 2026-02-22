#pragma once

#include <iostream>
#include <utility>

#include "definitions.hpp"

namespace utils {

template <typename... Args>
void log(Args &&...args) {
    (std::cout << ... << std::forward<Args>(args)) << std::endl;
}

template <typename... Args>
void log_info(void *object_address, Args... args) {
    if constexpr (!(DEBUGGED && DEBUG_INFO)) {
        return;
    }

    log("[INFO ]: [", object_address, "] ", std::forward<Args>(args)...);
}

template <typename... Args>
void log_trace(void *object_address, std::string function, Args... args) {
    if constexpr (!(DEBUGGED && DEBUG_TRACE)) return;

    std::cout << "[TRACE]: " << '[' << object_address << "] " << function << ": (";
    int n = 0;
    ((std::cout << (n++ == 0 ? "" : ", ") << args), ...);
    std::cout << ")" << std::endl;
}

template <typename... Args>
void log_warn(void *object_address, Args... args) {
    if constexpr (!(DEBUGGED && DEBUG_WARN)) {
        return;
    }

    log("[WARN ]: [", object_address, "] ", std::forward<Args>(args)...);
}

template <typename... Args>
void log_error(void *object_address, Args... args) {
    if constexpr (!(DEBUGGED && DEBUG_ERROR)) {
        return;
    }

    log("[ERROR]: [", object_address, "] ", std::forward<Args>(args)...);
}
}  // namespace utils
