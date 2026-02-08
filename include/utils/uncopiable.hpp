#pragma once

namespace utils {

class Uncopiable {
   public:
    Uncopiable() = default;

    Uncopiable(const Uncopiable &other) noexcept = delete;

    virtual ~Uncopiable() = default;

    Uncopiable &operator=(const Uncopiable &other) noexcept = delete;
};

}  // namespace utils
