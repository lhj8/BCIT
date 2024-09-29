#include "../include/CircularQueue.h"


/**
 * Constructs a circular queue with a specified capacity.
 *
 * Initializes a CircularQueue with the specified capacity.
 * Both the 'frontIndex' and 'rearIndex' are set to 0, and the 'currentSize' (number of elements in the queue)
 * is also initialized to 0. The underlying storage, 'buffer', is initialized as an empty std::vector of type T.
 *
 * @param capacity The maximum number of elements that the CircularQueue can hold.
 */
template<typename T>
CircularQueue<T>::CircularQueue(int capacity) {
    buffer = std::vector<T>();
    this->capacity = capacity;
    frontIndex = 0;
    rearIndex = 0;
    currentSize = 0;
}



/**
 * @Feedback:The default constructor for CircularQueue() is not necessary to redefine, and causes the program to crash.
 *
 * Default constructor for the CircularQueue.
 *
 * Initializes an empty CircularQueue with a capacity of 0.
 * Both the 'frontIndex' and 'rearIndex' are set to 0, and the 'currentSize' (number of elements in the queue)
 * is also initialized to 0. The underlying storage, 'buffer', is initialized as an empty std::vector of type T.
 */
//template<typename T>
//CircularQueue<T>::CircularQueue(): capacity(0), frontIndex(0), rearIndex(0), currentSize(0) {
//    buffer = std::vector<T>();
//}


/**
 * Checks if the CircularQueue is empty.
 *
 * @return True if the CircularQueue is empty, false otherwise.
 */
template<typename T>
bool CircularQueue<T>::isEmpty() const {
    return currentSize == 0;
}


/**
 * Checks if the CircularQueue is full.
 *
 * @return True if the CircularQueue is full, false otherwise.
 */
template<typename T>
bool CircularQueue<T>::isFull() const {
    return currentSize == capacity;
}


/**
 * Returns the number of elements in the CircularQueue.
 *
 * @return The number of elements currently in the CircularQueue.
 */
template<typename T>
size_t CircularQueue<T>::size() const {
    return currentSize;
}


/**
 * Adds a new element to the rear of the CircularQueue.
 *
 * Add the provided element to the rear end of the queue.
 * If the queue is not full, it appends the element to the stack 'buffer',updates the 'rearIndex'
 * to the next position, and increments the 'currentSize' to reflect the addition.
 *
 * If the queue is already full, an informative message is printed to the standard output
 * indicating the full state of the queue.
 *
 * @param element The element to be added to the queue.
 */
template<typename T>
void CircularQueue<T>::enqueue(const T &element) {
    if (!isFull()) {
        buffer.push_back(element);
        rearIndex = (rearIndex + 1) % capacity;
        currentSize++;
    }
    else std::cout << "Queue is currently FULL" << std::endl;
}


/**
 * Removes the front element from the CircularQueue.
 *
 * Remove the front element from the queue.
 * If the queue is not empty, it updates the 'frontIndex' to the next position and
 * decrements the 'currentSize' to reflect the removal.
 *
 * If the queue is empty, an informative message is printed to the standard output
 * indicating the empty state of the queue.
 */
template<typename T>
void CircularQueue<T>::dequeue() {
    if (!isEmpty()) {
        frontIndex = (frontIndex + 1) % capacity;
        currentSize--;
    }
    else {
        std::cout << "Queue is currently EMPTY" << std::endl;
    }
}


/**
 * Returns a reference to the front element of the CircularQueue.
 *
 * Retrieves the front element of the CircularQueue without removing it.
 * If the queue is not empty, it returns the element at the front index.
 * Otherwise, it returns the element at index 0, but this behavior might not be as expected
 * since the caller assumes that the queue isn't empty when calling this method.
 *
 * @return T& A reference to the front element.
 */
template<typename T>
T &CircularQueue<T>::front() {
    if (!isEmpty())
        return buffer.at(frontIndex);
    else
        return buffer.at(0);
}


/**
 * Returns a constant reference to the front element of the CircularQueue.
 *
 * Retrieves the front element of the CircularQueue without removing it.
 * If the queue is not empty, it returns the element at the front index.
 * Otherwise, it returns the element at index 0, but this behavior might not be as expected
 * since the caller assumes that the queue isn't empty when calling this method.
 *
 * @return const T& A constant reference to the front element.
 */
template<typename T>
const T &CircularQueue<T>::front() const {
    if (!isEmpty())
        return buffer.at(frontIndex);
    else
        return buffer.at(0);
}


