#include "avionics/drivers/SimulatedImuDriver.hpp"

#include <iomanip>
#include <iostream>

int main()
{
    avionics::drivers::SimulatedImuDriver imu{};

    std::cout << "Embedded Avionics Software Stack\n";
    std::cout << "Initializing " << imu.name() << "...\n";

    if (!imu.initialize())
    {
        std::cerr << "IMU initialization failed.\n";
        return 1;
    }

    if (!imu.selfTest())
    {
        std::cerr << "IMU self-test failed.\n";
        return 1;
    }

    std::cout << "IMU ready. Reading samples:\n\n";

    for (int sample_index = 0; sample_index < 5; ++sample_index)
    {
        const auto sample = imu.read();

        if (!sample.valid)
        {
            std::cerr << "Invalid IMU sample received.\n";
            return 1;
        }

        std::cout << std::fixed << std::setprecision(3)
                  << "t = " << sample.timestamp_us << " us"
                  << " | accel = ("
                  << sample.acceleration_mps2.x << ", "
                  << sample.acceleration_mps2.y << ", "
                  << sample.acceleration_mps2.z << ") m/s^2"
                  << " | gyro = ("
                  << sample.angular_velocity_rps.x << ", "
                  << sample.angular_velocity_rps.y << ", "
                  << sample.angular_velocity_rps.z << ") rad/s\n";
    }

    return 0;
}