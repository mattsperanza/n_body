cmake_minimum_required(VERSION 3.15)
project(coulomb_cpu LANGUAGES CXX)

# Collect all source files in this directory
file(GLOB SOURCES "*.cpp")

# Define the executable
add_executable(coulomb_cpu ${SOURCES})

# Require C++17
target_compile_features(coulomb_cpu PRIVATE cxx_std_17)

# Detect build type (default to Debug if none specified)
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug CACHE STRING "Choose the build type (Debug or Release)" FORCE)
endif()

message(STATUS "Build type: ${CMAKE_BUILD_TYPE}")

# Compiler flags depending on build type
if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    target_compile_definitions(coulomb_cpu PRIVATE DEBUG_MODE=1)
    target_compile_options(coulomb_cpu PRIVATE -g -O0 -Wall -Wextra -pedantic)
elseif (CMAKE_BUILD_TYPE STREQUAL "Release")
    target_compile_definitions(coulomb_cpu PRIVATE DEBUG_MODE=0)
    target_compile_options(coulomb_cpu PRIVATE -O3 -march=native -funroll-loops)
endif()
