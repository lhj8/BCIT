/*
 * Copyright (c) Sayyedhassan Shavarani 2023
 * All rights reserved. Unauthorized redistribution is prohibited.
 */
#ifndef CIRCULAR_QUEUE_H
#define CIRCULAR_QUEUE_H
/**
 * Implementation of a circular queue.
 */
#include <vector>
#include <cstddef>

template <typename T>
class CircularQueue {
public:
    // TODO implement the following functions in ../src/CircularQueue.cpp
    explicit CircularQueue(int capacity);
    CircularQueue();
    bool isEmpty() const;
    bool isFull() const;
    size_t size() const;
    void enqueue(const T& element);
    void dequeue();
    T& front();
    const T& front() const;

private:
    std::vector<T> buffer;
    size_t capacity;
    size_t frontIndex;
    size_t rearIndex;
    size_t currentSize;
};


#include "../src/CircularQueue.cpp"

#endif //CIRCULAR_QUEUE_H
