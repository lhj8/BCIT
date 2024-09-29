cmake_minimum_required(VERSION 3.10)
project(task2)

# Include directories
set(INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/include")
set(SOURCE_DIR  "${CMAKE_CURRENT_SOURCE_DIR}/src")

# Find all source files in the src directory
file(GLOB_RECURSE PROJECT_FILES
        "${INCLUDE_DIR}/*.h"
        "${SOURCE_DIR}/*.cpp"
        "${SOURCE_DIR}/*.c"
)

# Add executable for this project
add_executable(task2 ${PROJECT_FILES})

target_include_directories(task2 PRIVATE ${INCLUDE_DIR})
target_compile_features(task2 PRIVATE cxx_std_17)

