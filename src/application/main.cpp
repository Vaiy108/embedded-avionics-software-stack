#include "avionics/drivers/SimulatedImuDriver.hpp"
#include "avionics/middleware/LocalMessageBus.hpp"

#include <iomanip>
#include <iostream>

int main()
{
    avionics::drivers::SimulatedImuDriver imu{};
    avionics::middleware::LocalMessageBus message_bus{};

    message_bus.subscribeImu(
        [](const avionics::messages::ImuSample& sample)
        {
            std::cout
                << std::fixed
                << std::setprecision(3)
                << "IMU message"
                << " | t = "
                << sample.timestamp_us
                << " us"
                << " | accel = ("
                << sample.acceleration_mps2.x
                << ", "
                << sample.acceleration_mps2.y
                << ", "
                << sample.acceleration_mps2.z
                << ") m/s^2"
                << " | gyro = ("
                << sample.angular_velocity_rps.x
                << ", "
                << sample.angular_velocity_rps.y
                << ", "
                << sample.angular_velocity_rps.z
                << ") rad/s\n";
        });

    std::cout
        << "Embedded Avionics Software Stack\n";

    if (!imu.initialize() || !imu.selfTest())
    {
        std::cerr
            << "IMU initialization failed.\n";
        return 1;
    }

    std::cout
        << "Publishing IMU samples through middleware:\n\n";

    for (int sample_index = 0;
         sample_index < 5;
         ++sample_index)
    {
        const auto sample = imu.read();

        if (!sample.valid)
        {
            std::cerr
                << "Invalid IMU sample.\n";
            return 1;
        }

        message_bus.publish(sample);
    }

    return 0;
}