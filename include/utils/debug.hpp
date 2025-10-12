#pragma once

#include <iostream>
#include <sstream>
#include <string>
#include <utility>

#include "definitions.hpp"

using std::cout;
using std::endl;
using std::forward;
using std::ostringstream;
using std::string;

namespace utils {

template <typename... Args>
void log(Args... args) {
    ostringstream stream;
    (stream << ... << args);
    cout << stream.str() << endl;
}

template <typename... Args>
void log_info(Args... args) {
    if constexpr (!(DEBUGGED && DEBUG_INFO)) {
        return;
    }

    log("[INFO]: ", forward<Args>(args)...);
}

template <typename... Args>
void log_warn(Args... args) {
    if constexpr (!(DEBUGGED && DEBUG_WARN)) {
        return;
    }

    log("[WARN]: ", forward<Args>(args)...);
}

template <typename... Args>
void log_error(Args... args) {
    if constexpr (!(DEBUGGED && DEBUG_ERROR)) {
        return;
    }

    log("[ERROR]: ", forward<Args>(args)...);
}
}  // namespace utils