#pragma once

namespace utils {

class RestrictedInstance {
   public:
    RestrictedInstance() = default;

    RestrictedInstance(const RestrictedInstance &other) noexcept = delete;

    // RestrictedInstance(RestrictedInstance &&other) noexcept = delete;

    // virtual ~RestrictedInstance() = default;

    RestrictedInstance &operator=(const RestrictedInstance &other) noexcept = delete;

    RestrictedInstance(RestrictedInstance &&other) noexcept = default;
    RestrictedInstance &operator=(RestrictedInstance &&other) noexcept = default;
    // RestrictedInstance &operator=(RestrictedInstance &&other) noexcept = delete;

    // RestrictedInstance operator*() = delete;

    // const RestrictedInstance operator*() const = delete;
};

}  // namespace utils
