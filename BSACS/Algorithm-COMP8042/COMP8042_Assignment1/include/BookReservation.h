/*
 * Copyright (c) Sayyedhassan Shavarani 2023
 * All rights reserved. Unauthorized redistribution is prohibited.
 */
#ifndef BOOKRESERVATION_H
#define BOOKRESERVATION_H
/**
 * Implementation of the book reservation management system main class.
 */
#include <iostream>
#include <string>
#include <vector>
#include "Utils.h"
#include "CircularQueue.h"
#include "Stack.h"

class ReservationRecord {
public:
    std::string patronID;
    std::string bookISBN;

    ReservationRecord(std::string& patronID, std::string& bookISBN);
    ReservationRecord(const Patron& patron, const Book& book);
    ReservationRecord() = default;
};

class BookReservationManagementSystem {
public:
    explicit BookReservationManagementSystem(int maxPendingReservations);
    void indexBookToDB(const Book& book);
    void enqueueReservation(const Patron& patron, const Book& book);
    ReservationRecord processReservation();
    CircularQueue<ReservationRecord> pendingReservations;
    Stack<ReservationRecord> fulfilledReservations;
    std::vector<Book> booksDB;
private:
    void enqueueReservation(const ReservationRecord& reservation);
    int maxPendingReservations;
};


#endif //BOOKRESERVATION_H
