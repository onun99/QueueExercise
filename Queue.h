#ifndef QUEUE_H
#define QUEUE_H

#include <stdexcept>

template <typename T>
class Queue {
public:
    // Constructor: creates a queue with the given capacity.
    Queue(int size) : capacity(size), oldest(0), next(0), count(0) {
        content = new T[capacity]; //returns a pointer to the beginning of the allocated memory block
    }

    // Destructor: cleans up the allocated array.
    ~Queue() {
        delete[] content; //frees the memory that was previously allocated with new
    }

    // Push an element into the queue If the queue is full, the oldest element is dropped.
    void Push(T element) {

        if (count == capacity) {
            // The queue is full, so drop the oldest element.
            oldest = (oldest + 1) % capacity;
            count--;
        }

        content[next] = element; //inserts value
        next = (next + 1) % capacity; // defines next position to write in, while handling loop around
        count++; //increases the size of the Queue
    }

    // Pop and return the oldest element from the queue. Throws an exception if the queue is empty.
    T Pop(){

        if (count == 0) {
            throw std::runtime_error("Queue is empty");
        }

        T element = content[oldest];
        oldest = (oldest + 1) % capacity;
        count--;
        return(element);
    }

    int Count(){
        return(count);
    }

    int Size(){
        return(capacity);
    }

private:
    T* content;    // Pointer to the dynamically allocated array.
    int capacity;  // Maximum number of elements.
    int oldest;      // Index of the oldest element.
    int next;      // Index where the next element will be inserted.
    int count;     // Current number of elements.
};

#endif // QUEUE_H