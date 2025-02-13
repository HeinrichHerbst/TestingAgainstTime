#include <chrono>    // sleep_for
#include <iostream>  // cout
#include <map>       // iterationSignals
#include <ranges>    // iota, transform, to
#include <thread>    // sleep_for

#include "PressureReliever.hpp"

namespace {

inline std::map<int, bool> createSimulationRunMap()
{
    std::map<int, bool> iterationSignals;
    for (int i = 1; i <= 30; i++) {
        iterationSignals[i] = false;
    }
    iterationSignals[10] = true;
    return iterationSignals;
}

}  // namespace

/**
 * @brief Main function simulating a polling loop that interacts with the PressureReliever class
 */
int main()
{
    bool isReliefRequiredSignal = true;
    bool openValveSignal = false;
    PressureReliever pressureReliever{isReliefRequiredSignal, openValveSignal};

    auto simulationMap = createSimulationRunMap();

    for (const auto& [iterationCount, isReliefRequestedThisIteration] : simulationMap) {
        isReliefRequiredSignal = isReliefRequestedThisIteration;

        pressureReliever.controlPressure();

        std::cout << "Iteration Count: " << iterationCount << ", IsReliefRequested: " << isReliefRequiredSignal
                  << ", IsValveActive: " << openValveSignal << '\n';

        std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }

    return 0;
}