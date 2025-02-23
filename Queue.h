#ifndef QUEUE_H
#define QUEUE_H

#include <stdexcept>
#include <mutex>
#include <condition_variable>

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
        std::unique_lock<std::mutex> lock(mtx);
        if (count == capacity) {
            // The queue is full, so drop the oldest element.
            oldest = (oldest + 1) % capacity;
            count--;
        }

        content[next] = element; //inserts value
        next = (next + 1) % capacity; // defines next position to write in, while handling loop around
        count++; //increases the size of the Queue

        cv.notify_one(); //Notify waiting threads that a new element is available
    }

    // Pop and return the oldest element from the queue. Blocks forever if the queue is empty.
    T Pop(){
        std::unique_lock<std::mutex> lock(mtx);
        cv.wait(lock, [this]() { return count > 0; }); //Thread only wakes up when count > 0

        T element = content[oldest];
        oldest = (oldest + 1) % capacity;
        count--;
        return(element);
    }

    // Pop and return the oldest element from the queue. Blocks for milliseconds if the queue is empty.
    T PopWithTimeout(int milliseconds) {
        std::unique_lock<std::mutex> lock(mtx);

        bool ready = cv.wait_for(lock, std::chrono::milliseconds(milliseconds), [this]() { return count > 0; });
        if (!ready) {
            throw std::runtime_error("Timeout waiting for element");
        }
        T element = content[oldest];
        oldest = (oldest + 1) % capacity;
        count--;
        return element;
    }

    int Count(){
        //std::unique_lock calls unlock on the mutex in its destructor if some exception occurs the mutex will be unlocked
        std::unique_lock<std::mutex> lock(mtx); // lock object to protect count 
        return(count);
    }

    int Size(){
        // No lock needed because capacity is not modified
        return(capacity);
    }

private:
    T* content;    // Pointer to the dynamically allocated array.
    int capacity;  // Maximum number of elements.
    int oldest;      // Index of the oldest element.
    int next;      // Index where the next element will be inserted.
    int count;     // Current number of elements.

    std::mutex mtx;             // Mutex to protect access to shared data.
    std::condition_variable cv; // Condition variable for blocking in Pop.
};

#endif // QUEUE_H