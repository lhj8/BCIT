cmake_minimum_required(VERSION 3.25)
project(8042_Assignment_1)

set(CMAKE_CXX_STANDARD 14)

add_executable(8042_Assignment_1
        include/Date.h
        include/Utils.h
        include/LExceptions.h
        include/Stack.h
        include/CircularQueue.h
        src/BookReservation.cpp
        tests/TestEnvironment.h
        tests/StackTests.h
        tests/CircularQueueTests.h
        tests/BookReservationTests.h
        main.cpp)
