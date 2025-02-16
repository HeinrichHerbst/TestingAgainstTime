#include <gtest/gtest.h>

#include "../inc/PressureReliever.hpp"
#include "mocks/TimeTravellersClock.hpp"

TEST(PressureRelieverTest, TestFiveSeconds)
{
    // Arrange
    bool isReliefRequiredSignal = false;   // Input
    bool openValveSignalResponse = false;  // Output

    testing::NiceMock<TimeTravellersClock> timeTravellersClock;

    // Instead of asking the system clock for the time, we ask the time traveller's clock
    // We'll set up our PressureReliever to use this ask our timetraveller's clock.

    // After all, our computers don't know how far we jumped ;)
    PressureReliever pressureReliever{isReliefRequiredSignal, openValveSignalResponse,
                                      timeTravellersClock.retrieveTemporalBarometer()};

    // Act
    pressureReliever.controlPressure();

    // Assert
    EXPECT_FALSE(openValveSignalResponse);

    // Now we travel into the future by a second
    timeTravellersClock.fastForwardTheSpaceTimeContinuum(std::chrono::seconds(1));
    // And we request pressure relief
    isReliefRequiredSignal = true;

    pressureReliever.controlPressure();

    EXPECT_TRUE(isReliefRequiredSignal);
    EXPECT_TRUE(openValveSignalResponse);

    // In the next cycle (1 second later), the request for pressure relief is gone.
    timeTravellersClock.fastForwardTheSpaceTimeContinuum(std::chrono::seconds(1));
    isReliefRequiredSignal = false;

    pressureReliever.controlPressure();

    EXPECT_FALSE(isReliefRequiredSignal);
    EXPECT_TRUE(openValveSignalResponse);

    // Now we travel into the future by 3 seconds
    timeTravellersClock.fastForwardTheSpaceTimeContinuum(std::chrono::seconds(3));

    pressureReliever.controlPressure();

    // We should still have the valve open as only 4 seconds have passed since the last request for pressure relief was observed
    EXPECT_FALSE(isReliefRequiredSignal);
    EXPECT_TRUE(openValveSignalResponse);

    // Now jump into the future, where it has already been 5 seconds since the last request for pressure relief
    timeTravellersClock.fastForwardTheSpaceTimeContinuum(std::chrono::seconds(1));

    pressureReliever.controlPressure();

    // The valve should now be closed
    EXPECT_FALSE(isReliefRequiredSignal);
    EXPECT_FALSE(openValveSignalResponse);

    // And it should stay closed
    timeTravellersClock.fastForwardTheSpaceTimeContinuum(std::chrono::seconds(1));

    pressureReliever.controlPressure();

    EXPECT_FALSE(isReliefRequiredSignal);
    EXPECT_FALSE(openValveSignalResponse);
}

int main(int argc, char** argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}