#include "PressureReliever.hpp"

PressureReliever::PressureReliever(const bool& isReliefRequired, bool& openValveSignal)
    : isReliefRequired_(isReliefRequired)
    , openValveSignal_(openValveSignal)
{
}

void PressureReliever::controlPressure()
{
    openValveSignal_ = isReliefRequired_;
}