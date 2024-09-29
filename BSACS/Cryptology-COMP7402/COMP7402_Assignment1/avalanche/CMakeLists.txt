cmake_minimum_required(VERSION 3.10)
project(Avalancheeffect)

# Include directories
set(INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/include")
set(SOURCE_DIR  "${CMAKE_CURRENT_SOURCE_DIR}/src")

# Find all source files in the src directory
file(GLOB_RECURSE PROJECT_FILES
        "${INCLUDE_DIR}/*.h"
        "${SOURCE_DIR}/*.cpp"
)

# Add executable for this project
add_executable(avalanche ${PROJECT_FILES}
        include/avalanche.h
        src/avalanche.cpp)

target_include_directories(avalanche PRIVATE ${INCLUDE_DIR})