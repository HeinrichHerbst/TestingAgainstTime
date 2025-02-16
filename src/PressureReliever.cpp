#include "PressureReliever.hpp"

PressureReliever::PressureReliever(const bool& isReliefRequired, bool& openValveSignal,
                                   TimeManagement::TimePointFunction timePointFunction)
    : isReliefRequired_(isReliefRequired)
    , openValveSignal_(openValveSignal)
    , timePointFunction_(std::move(timePointFunction))
{
}

void PressureReliever::controlPressure()
{
    // Always keep valve open for RELIEF_DURATION seconds after _any_ isReliefRequired signal was detected.
    if (isReliefRequired_) {
        openValveSignal_ = true;
        isReliefCycleActive_ = true;
        latestActivationTime_ = timePointFunction_();
        return;
    }

    // Relief not required, however a cycle might still be active.
    if (isReliefCycleActive_) {
        const auto elapsedDuration =
            std::chrono::duration_cast<std::chrono::seconds>(timePointFunction_() - latestActivationTime_);
        if (elapsedDuration >= RELIEF_DURATION) {
            isReliefCycleActive_ = false;
            openValveSignal_ = false;
        }
    }
}