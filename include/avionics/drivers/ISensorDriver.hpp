#pragma once

#include <string_view>

namespace avionics::drivers
{

enum class SensorStatus
{
    uninitialized,
    ready,
    error
};

class ISensorDriver
{
public:
    virtual ~ISensorDriver() = default;

    virtual bool initialize() = 0;
    virtual bool selfTest() = 0;

    [[nodiscard]] virtual SensorStatus status() const = 0;
    [[nodiscard]] virtual std::string_view name() const = 0;
};

}  // namespace avionics::drivers