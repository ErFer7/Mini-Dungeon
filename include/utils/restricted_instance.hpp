#pragma once

class RestrictedInstance {
   public:
    RestrictedInstance() = default;

    RestrictedInstance(const RestrictedInstance &other) noexcept = delete;

    RestrictedInstance(RestrictedInstance &&other) noexcept = delete;

    virtual ~RestrictedInstance() = default;

    RestrictedInstance &operator=(const RestrictedInstance &other) noexcept = delete;

    RestrictedInstance &operator=(RestrictedInstance &&other) noexcept = delete;

    RestrictedInstance operator*() = delete;

    const RestrictedInstance operator*() const = delete;
};
