#pragma once

#include <gmock/gmock.h>

#include <chrono>

class TimeTravellersClock
{
public:
    TimeTravellersClock()
    {
        ON_CALL(*this, now()).WillByDefault([this]() {
            return configuredTimePoint_;
        });
    }

    /**
     * @brief Advance time as we know it. Be careful of skipping in too large steps.
     */
    void fastForwardTheSpaceTimeContinuum(const std::chrono::steady_clock::duration& temporalQuantity)
    {
        configuredTimePoint_ += temporalQuantity;
    }

    /**
     * @brief Retrieve a temporal barometer that can be used to measure the passage of time.
     * More simply, this just tells you the current progression of time since you started travelling.
     */
    auto retrieveTemporalBarometer()
    {
        return [this]() {
            return now();
        };
    }

    MOCK_METHOD(std::chrono::steady_clock::time_point, now, ());

private:
    std::chrono::steady_clock::time_point configuredTimePoint_;
};