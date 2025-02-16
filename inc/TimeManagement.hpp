#pragma once

#include <chrono>
#include <functional>

namespace TimeManagement {
using TimePointFunction = std::function<std::chrono::steady_clock::time_point()>;
static inline const auto DEFAULT_CURRENT_TIME = std::chrono::steady_clock::now;
}  // namespace TimeManagement