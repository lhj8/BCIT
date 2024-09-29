cmake_minimum_required(VERSION 3.10)
project(COMP7402_Assignment1)


### Require out-of-source builds
# this still creates a CMakeFiles directory and CMakeCache.txt- can we delete them?
file(TO_CMAKE_PATH "${PROJECT_BINARY_DIR}/CMakeLists.txt" LOC_PATH)
if (EXISTS "${LOC_PATH}")
    message(FATAL_ERROR "You cannot build in a source directory (or any directory with a CMakeLists.txt file). Please make a build subdirectory. Feel free to remove CMakeCache.txt and CMakeFiles.")
endif ()


# Add subdirectories for each project
add_subdirectory(des)
add_subdirectory(aes)
add_subdirectory(avalanche)