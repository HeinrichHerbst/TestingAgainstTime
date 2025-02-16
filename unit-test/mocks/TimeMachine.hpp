#pragma once

#include <gmock/gmock.h>

/**
 * @brief The TimeMachine class is a mockable time machine that can be used to travel through time time.
 * @note Great Scott! This machine is broken and can only travel within a the second week of of July 1985.
 *       What a shame, we can't go back to the future. But we can still use it to test our time-dependent code.
 *       Can you fix it?
 */
class TimeMachine
{
public:
    TimeMachine()
    {
        ON_CALL(*this, now()).WillByDefault([this]() {
            return currentDayAndTime_;
        });
    }

    MOCK_METHOD(std::time_t, now, ());

    /**
     * @brief accelerateToEightyEight Travels in time to the specified temporal co-ordinates.
     * @param day The day of the week to travel to (0-7, Sunday to Saturday).
     * @param hour The hour of the day to travel to (0-23).
     * @param minute The minute of the hour to travel to (0-59).
     */
    void accelerateToEightyEight(int day, int hour, int minute)
    {
        currentDayAndTime_ = setDayAndTime(day, hour, minute);
    }

    /** Creates a function to return the current (mocked) dayAndTime.  */
    auto retrieveTemporalBarometer()
    {
        return [this]() {
            return now();
        };
    }

private:
    // Holder of information about the "current" dayAndTime.
    std::time_t currentDayAndTime_{};

    /**
     * @brief setDayAndTime Helper function to calculate a time_t time from supplied temporal co-ordinates.
     * @param day The day of the week to target (0-7, Sunday to Saturday).
     * @param hour The hour of the day to target (0-23).
     * @param minute The minute of the hour to target (0-59).
     */
    static std::time_t setDayAndTime(int day, int hour, int minute)
    {
        // Base time (Sunday, July 7th, 1985 00:00:00)
        std::tm tmStruct = {};
        tmStruct.tm_year = 1985 - 1900;  // Year since 1900 (epoch)
        tmStruct.tm_mon = 6;             // Month (0-11) (6 = July)
        tmStruct.tm_mday = 7 + day;      // Day of the month (1-31) (7 = Sunday)
        tmStruct.tm_hour = hour;
        tmStruct.tm_min = minute;
        tmStruct.tm_sec = 0;
        tmStruct.tm_isdst = -1;  // Let system determine DST

        return std::mktime(&tmStruct);
    }
};