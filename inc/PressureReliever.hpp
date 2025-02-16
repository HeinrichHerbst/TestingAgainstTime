#pragma once

#include <chrono>

#include "TimeManagement.hpp"

// Requirement:
// The PressureReliever shall open the valve for 5 seconds
// After the isReliefRequired flag is set to true.

class PressureReliever
{
public:
    constexpr static std::chrono::seconds RELIEF_DURATION{5};

    PressureReliever(const bool& isReliefRequired, bool& openValveSignal,
                     TimeManagement::TimePointFunction timePointFunction = TimeManagement::DEFAULT_CURRENT_TIME);

    /**
     * @brief Control the pressure in the system based on the isReliefRequired flag
     */
    void controlPressure();

private:
    // Input
    const bool& isReliefRequired_;

    // Output
    bool& openValveSignal_;

    // Dependency
    TimeManagement::TimePointFunction timePointFunction_;

    // State variables
    bool isReliefCycleActive_ = false;
    std::chrono::steady_clock::time_point latestActivationTime_{};
};