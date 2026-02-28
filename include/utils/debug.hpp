#pragma once

#include <iostream>
#include <utility>

#include "definitions.hpp"

namespace utils {

static const std::string TERM_RESET = "\033[0m";
static const std::string TERM_RED = "\033[31m";
static const std::string TERM_YELLOW = "\033[33m";
static const std::string TERM_BLUE = "\033[34m";
static const std::string TERM_MAGENTA = "\033[35m";

template <typename... Args>
void log(Args &&...args) {
    (std::cout << ... << std::forward<Args>(args)) << std::endl;
}

template <typename... Args>
void log_info(void *object_address, Args... args) {
    if constexpr (!(DEBUGGED && DEBUG_INFO)) {
        return;
    }

    log(TERM_MAGENTA, "[INFO ]:", TERM_RESET, " [", object_address, "] ", std::forward<Args>(args)...);
}

template <typename... Args>
void log_trace(void *object_address, std::string function, Args... args) {
    if constexpr (!(DEBUGGED && DEBUG_TRACE)) return;

    std::cout << TERM_BLUE << "[TRACE]: " << TERM_RESET << '[' << object_address << "] " << function << ": (";
    int n = 0;
    ((std::cout << (n++ == 0 ? "" : ", ") << args), ...);
    std::cout << ")" << std::endl;
}

template <typename... Args>
void log_warn(void *object_address, Args... args) {
    if constexpr (!(DEBUGGED && DEBUG_WARN)) {
        return;
    }

    log(TERM_YELLOW, "[WARN ]:", TERM_RESET, " [", object_address, "] ", std::forward<Args>(args)...);
}

template <typename... Args>
void log_error(void *object_address, Args... args) {
    if constexpr (!(DEBUGGED && DEBUG_ERROR)) {
        return;
    }

    log(TERM_RED, "[ERROR]:", TERM_RESET, " [", object_address, "] ", std::forward<Args>(args)...);
}
}  // namespace utils
