cmake_minimum_required(VERSION 3.13)

project(TimeTestUnitTests)

enable_testing()
find_package(GTest REQUIRED)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_CXX_COMPILER "/usr/bin/g++-11")

# Add compiler warning flags
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wpedantic")

# Enable debug symbols
set(CMAKE_BUILD_TYPE Debug)

# Include directory for header files
include_directories("${CMAKE_CURRENT_SOURCE_DIR}/../inc" "${CMAKE_CURRENT_SOURCE_DIR}/mocks")

# Create the test executable with all required source files
add_executable(TimeTestUnitTests 
    ${CMAKE_CURRENT_SOURCE_DIR}/../src/PressureReliever.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/PressureRelieverTest.cpp
)

# Link against GTest and GMock libraries
target_link_libraries(TimeTestUnitTests
    GTest::GTest
    GTest::Main
    gmock
    gmock_main
)

# Register the test
add_test(
    NAME TimeTestUnitTests
    COMMAND TimeTestUnitTests
)