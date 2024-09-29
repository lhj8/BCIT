#include "../include/BookReservation.h"
#include "../include/LExceptions.h"


/**
 * Constructs a ReservationRecord with patron and book information.
 *
 * @param patronID The ID of the patron making the reservation.
 * @param bookISBN The ISBN of the book being reserved.
 */
ReservationRecord::ReservationRecord(std::string &patronID, std::string &bookISBN) {
    this->patronID = patronID;
    this->bookISBN = bookISBN;
}


/**
 * Constructs a ReservationRecord with patron and book information.
 *
 * @param patron The Patron object making the reservation.
 * @param book The Book object being reserved.
 */
ReservationRecord::ReservationRecord(const Patron &patron, const Book &book) {
    this->patronID = patron.ID;
    this->bookISBN = book.ISBN;
}


/**
 * Constructs a BookReservationManagementSystem with a maximum number of pending reservations.
 *
 * @param maxPendingReservations The maximum number of pending reservations allowed.
 */
BookReservationManagementSystem::BookReservationManagementSystem(int maxPendingReservations)
    : maxPendingReservations(maxPendingReservations), pendingReservations(maxPendingReservations) {}


/**
* Indexes a book into the system's book database.
*
* @param book The Book object to be added to the database.
*/
void BookReservationManagementSystem::indexBookToDB(const Book &book) {
    booksDB.push_back(book);
}


/**
 * Enqueues a new reservation into the reservation system.
 *
 * creates a new reservation record for a given patron and book and then enqueues it into the reservation system.
 *
 * @param patron The Patron object making the reservation.
 * @param book The Book object being reserved.
 */
void BookReservationManagementSystem::enqueueReservation(const Patron &patron, const Book &book) {
    ReservationRecord newReservation(patron, book);
    enqueueReservation(newReservation);
}


/**
 * Enqueue a reference of the reservation record into the pending reservations queue.
 * If the queue is already at its capacity (i.e., has reached 'maxPendingReservations'),
 * the reservation will not be added, and print out the message
 *
 * @param reservation The ReservationRecord object to be added to pending reservations.
 */
void BookReservationManagementSystem::enqueueReservation(const ReservationRecord &reservation) {
    if (pendingReservations.size() < maxPendingReservations) { // assuming the CircularQueue has a size method
        pendingReservations.enqueue(reservation); // assuming the CircularQueue has an enqueue method
    }
    else
        std::cout << "Maximum pending reservations reached! Cannot enqueue the reservation." << std::endl;

}


/**
 * Processes the next reservation from the 'pendingReservations' queue.
 *
 * Attempts to fulfill the next reservation in the queue by searching for
 * the requested book in the 'booksDB' database. If the book is found and has available copies,
 * the reservation is fulfilled, the book's copy count is decremented, and the reservation
 * is moved to the 'fulfilledReservations' queue.
 *
 * If the book is unavailable, the reservation is moved to the end of the 'pendingReservations' queue
 * and the next reservation is then processed. This continues until a reservation is fulfilled or all
 * reservations in the queue have been checked without fulfillment.
 *
 * @return ReservationRecord The reservation record that has been successfully processed and fulfilled.
 *
 * @throws ReservationRecordUnavailable Thrown if:
 *      - The 'pendingReservations' queue is empty from the start.
 *      - No reservations in the queue can be fulfilled after checking all of them.
 */
ReservationRecord BookReservationManagementSystem::processReservation() {
    int rotationCount = 0;

    if (pendingReservations.isEmpty()) {
        throw ReservationRecordUnavailable();
    }
    else {
        while (!pendingReservations.isEmpty()) {
            ReservationRecord currentReservation = pendingReservations.front();
            // Search copies of pending reservation's book is available in booksDB
            for (auto &i : booksDB) {
                if (currentReservation.bookISBN == i.ISBN && i.copies >= 1) {
                    fulfilledReservations.push(currentReservation);
                    pendingReservations.dequeue();
                    i.copies--;
                    return currentReservation;
                }
            }
            // Add currentReservation to the end of queue if it's not exist in booksDB(copies = 0)
            pendingReservations.enqueue(currentReservation);
            pendingReservations.dequeue();
            rotationCount++;
            if (rotationCount == pendingReservations.size())
                // if rotated queue more than queue size, throw exception
                throw ReservationRecordUnavailable();
        }
    }
}



