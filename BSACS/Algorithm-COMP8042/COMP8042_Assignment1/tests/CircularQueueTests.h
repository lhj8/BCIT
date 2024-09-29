/*
 * Copyright (c) Sayyedhassan Shavarani 2023
 * All rights reserved. Unauthorized redistribution is prohibited.
 */
#ifndef CIRCULARQUEUETESTS_H
#define CIRCULARQUEUETESTS_H
#include <iostream>
#include <cmath>
#include "../include/Utils.h"
#include "TestEnvironment.h"
#include "../include/CircularQueue.h"

std::pair<int, int> circularQueueTestForBookDataStructure() {
    int passedTests = 0;
    TestEnvironment env;
    CircularQueue<Book> bookQueue(10);
    passedTests += assert(bookQueue.isEmpty());
    bookQueue.enqueue(env.book10);
    bookQueue.enqueue(env.book9);
    bookQueue.enqueue(env.book8);
    bookQueue.enqueue(env.book7);
    bookQueue.enqueue(env.book6);
    bookQueue.enqueue(env.book5);
    bookQueue.enqueue(env.book4);
    bookQueue.enqueue(env.book3);
    bookQueue.enqueue(env.book2);
    bookQueue.enqueue(env.book1);
    passedTests += assert(bookQueue.size() == 10);
    passedTests += assert(bookQueue.front().ISBN == "0515118567");
    for (int i = 0; i < 5; i++)
        bookQueue.dequeue();
    passedTests += assert(bookQueue.size());
    passedTests += assert(bookQueue.front().author == "Michael Johnstone");
    bookQueue.dequeue();
    passedTests += assert(bookQueue.size() == 4);
    passedTests += assert(bookQueue.front().title == "Until the Sun Dies");
    bookQueue.dequeue();
    passedTests += assert(bookQueue.size() == 3);
    bookQueue.dequeue();
    bookQueue.dequeue();
    passedTests += assert(bookQueue.size() == 1);
    passedTests += assert(bookQueue.front().ISBN == "0486411044");
    bookQueue.dequeue();
    passedTests += assert(bookQueue.isEmpty());
    passedTests += assert(bookQueue.size() == 0);
    return std::make_pair(passedTests, 12);
}

std::pair<int, int> circularQueueTestForUserDataStructure() {
    int passedTests = 0;
    TestEnvironment env;
    CircularQueue<Patron> userQueue(10);
    passedTests += assert(userQueue.isEmpty());
    userQueue.enqueue(env.user10);
    userQueue.enqueue(env.user9);
    userQueue.enqueue(env.user8);
    userQueue.enqueue(env.user7);
    userQueue.enqueue(env.user6);
    userQueue.enqueue(env.user5);
    userQueue.enqueue(env.user4);
    userQueue.enqueue(env.user3);
    userQueue.enqueue(env.user2);
    userQueue.enqueue(env.user1);
    passedTests += assert(userQueue.size() == 10);
    passedTests += assert(userQueue.front().ID == "user10");
    for (int i = 0; i < 5; i++)
        userQueue.dequeue();
    passedTests += assert(userQueue.size() == 5);
    passedTests += assert(userQueue.front().name == "Charles Williams");
    userQueue.dequeue();
    passedTests += assert(userQueue.size() == 4);
    passedTests += assert(userQueue.front().email == "brandon.gillespie@morris.com");
    userQueue.dequeue();
    passedTests += assert(userQueue.size() == 3);
    userQueue.dequeue();
    userQueue.dequeue();
    passedTests += assert(userQueue.size() == 1);
    passedTests += assert(userQueue.front().ID == "user1");
    userQueue.dequeue();
    passedTests += assert(userQueue.isEmpty());
    passedTests += assert(userQueue.size() == 0);
    return std::make_pair(passedTests, 12);
}

std::pair<int, int> circularQueueTestForGeneralDataStructures() {
    int passedTests = 0;
    CircularQueue<int> intQueue(99999999);
    passedTests += assert(intQueue.isEmpty());
    for (int i = 0; i < 99999999; ++i)
        intQueue.enqueue(i);
    passedTests += assert(!intQueue.isEmpty());
    passedTests += assert(intQueue.size() == 99999999);
    for (int i = 0; i < 99999998; ++i)
        intQueue.dequeue();
    passedTests += assert(intQueue.front() == 99999998);
    intQueue.dequeue();
    passedTests += assert(intQueue.isEmpty());

    CircularQueue<std::string> strQueue(99999999);
    for (int i = 0; i < 99999999; ++i)
        strQueue.enqueue("# " + std::to_string(i));
    int all_passed = 0;
    for (int i = 0; i < 99999999; ++i) {
        all_passed += assert(strQueue.front() == "# " + std::to_string(i));
        strQueue.dequeue();
    }
    passedTests += assert(all_passed == 99999999);
    return std::make_pair(passedTests, 6);
}

int circularQueueTests() {
    int passedTests = 0;
    int totalTests = 0;
    std::pair<int, int> r1 = circularQueueTestForBookDataStructure();
    passedTests += r1.first;
    totalTests += r1.second;
    std::pair<int, int> r2 = circularQueueTestForUserDataStructure();
    passedTests += r2.first;
    totalTests += r2.second;
    std::pair<int, int> r3 = circularQueueTestForGeneralDataStructures();
    passedTests += r3.first;
    totalTests += r3.second;
    double grade = static_cast<double>(passedTests * 100) / totalTests;
    grade = std::round(grade * 10) / 10;
    std::cout << "Total tests passed: " << passedTests << " out of " << totalTests << " (" << grade << "%)"  << std::endl;
    return 0;
}

#endif //CIRCULARQUEUETESTS_H
