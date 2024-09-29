/*
 * Copyright (c) Sayyedhassan Shavarani 2023
 * All rights reserved. Unauthorized redistribution is prohibited.
 */
#include <iostream>
#include <stdexcept>
#include <cstdlib>
#include "tests/StackTests.h"
#include "tests/CircularQueueTests.h"
#include "tests/BookReservationTests.h"
/*
 * This is the driver file which directs the project on testing different modules.
 * For each new testing function add a new case with the next available "module_choice" to be able to test it out.
 */

int main(int argc, char* argv[]) {
    int module_choice = 0;

    if (argc > 1) {
        module_choice = atoi(argv[1]);
    }
    switch (module_choice) {
        case 0: // Testing Assignment 1:
            std::cout << ">> Stack:\t\t\t\t\t\t";
            stackTests();
            std::cout << ">> CircularQueue:\t\t\t\t";
            circularQueueTests();
            std::cout << ">> Book Reservation System: \t";
            bookReservationTests();
            break;
        default:
            throw std::invalid_argument("Invalid module choice");
            break;
    }
    return 0;
}
