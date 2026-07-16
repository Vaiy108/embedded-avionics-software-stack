#pragma once

#include "avionics/drivers/ISensorDriver.hpp"
#include "avionics/messages/SensorMessages.hpp"

namespace avionics::drivers
{

class SimulatedImuDriver final : public ISensorDriver
{
public:
    bool initialize() override;
    bool selfTest() override;

    [[nodiscard]] SensorStatus status() const override;
    [[nodiscard]] std::string_view name() const override;

    [[nodiscard]] messages::ImuSample read();

private:
    SensorStatus status_{SensorStatus::uninitialized};
    messages::TimestampUs timestamp_us_{0};
};

}  // namespace avionics::drivers