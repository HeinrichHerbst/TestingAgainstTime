#pragma once

// Requirement:
// The PressureReliever shall open the valve for 30 seconds
// After the isReliefRequired flag is set to true.

class PressureReliever
{
public:
    PressureReliever(const bool& isReliefRequired, bool& openValveSignal);

    /**
     * @brief Control the pressure in the system based on the isReliefRequired flag
     */
    void controlPressure();

private:
    const bool& isReliefRequired_;
    bool& openValveSignal_;
};