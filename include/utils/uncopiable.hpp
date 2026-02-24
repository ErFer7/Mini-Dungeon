#pragma once

namespace utils {

class Uncopiable {
   public:
    Uncopiable() = default;

    virtual ~Uncopiable() = default;

    Uncopiable(const Uncopiable &other) = delete;

    Uncopiable &operator=(const Uncopiable &other) = delete;

    Uncopiable(Uncopiable &&other) noexcept = default;

    Uncopiable &operator=(Uncopiable &&other) noexcept = default;
};

}  // namespace utils
